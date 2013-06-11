#ifndef HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__
#define HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__

#include <typeindex>
#include <type_traits>
#include <tbb/concurrent_unordered_map.h>
#include <boost/signals2/signal.hpp>
#include <boost/signals2/connection.hpp>

#include <utilcpp/assert.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/id.hpp>

namespace aosd {
namespace backend {

	enum class EventPriority
	{
		HIGH				= boost::signals2::connect_position::at_front
	,	LOW					= boost::signals2::connect_position::at_back
	};

	class EventDispatcher
	{
	public:
		typedef boost::signals2::connection Connection;		
		typedef boost::signals2::scoped_connection ScopedConnection;


		EventDispatcher(){} // = default

		template< class EventType >
		void dispatch( const EventType& event )
		{
			if( auto observers = find_observers<EventType>() )
			{
				observers->dispatch( event );
			}			
		}

		template< class SubjectId, class EventType >
		void dispatch( const Id<SubjectId>& source_id, const EventType& event )
		{
			if( auto observers = find_observers<EventType>() )
			{
				observers->dispatch( source_id, event );
			}			
		}

		template< class EventType, class ObserverType >
		Connection on( ObserverType&& observer, EventPriority priority = EventPriority::LOW )
		{
			auto observers = find_or_create_observers<EventType>();
			return observers->connect( priority, std::forward<ObserverType>(observer) );
		}

		template< class EventType, class SourceType, class ObserverType >
		Connection on( const Id<SourceType>& source_id, ObserverType&& observer, EventPriority priority = EventPriority::LOW )
		{
			auto observers = find_or_create_observers<EventType>();
			return observers->connect( priority, source_id, std::forward<ObserverType>(observer) );
		}

		class ObservationAPI
		{
			friend class EventDispatcher;
			EventDispatcher& m_event_dispatcher;
			explicit ObservationAPI( EventDispatcher& dispatcher ) : m_event_dispatcher( dispatcher ){ }
		public:
			// TODO: replace these functions by variadic templates so that it can forward attributes

			template< class EventType, class ObserverType >
			Connection on( ObserverType&& observer, EventPriority priority = EventPriority::LOW )
			{ return m_event_dispatcher.on<EventType>( std::forward<ObserverType>(observer), priority ); }

			template< class EventType, class SourceType, class ObserverType >
			Connection on( const Id<SourceType>& source_id, ObserverType&& observer, EventPriority priority = EventPriority::LOW )
			{ return m_event_dispatcher.on<EventType>( source_id, std::forward<ObserverType>(observer), priority ); }

		};

		ObservationAPI observation_api() { return ObservationAPI(*this); }

	private:
		EventDispatcher( const EventDispatcher& ); // = delete;
		EventDispatcher& operator=( const EventDispatcher& ); // = delete;

		class ObserverGroup 
		{ 
			ObserverGroup( const ObserverGroup& ); // = delete;
			ObserverGroup& operator=( const ObserverGroup& ); // = delete;
		protected:
			ObserverGroup(){} // = default;
		};
		typedef std::shared_ptr<ObserverGroup> ObserverGroupPtr;

		typedef tbb::concurrent_unordered_map< std::type_index, ObserverGroupPtr > ObserversIndex;
		ObserversIndex m_observers_index;


		template< class EventType >
		class EventObservers : public ObserverGroup
		{
			static const EventType* dummy() { return nullptr; }
			typedef boost::signals2::signal< void( EventType )> Signal;

			template< class TaskType >
			static Connection connection_impl( Signal& signal, EventPriority priority, TaskType&& task )
			{
				const auto connection_pos = static_cast< boost::signals2::connect_position >( priority );
				return signal.connect( connection_pos, std::forward<TaskType>(task) ); 
			}

			class SignalSlot // this is because concurrent_unordered_map can't accept move-only types like signal
			{ 
				std::shared_ptr<Signal> signal;
				
			public:
				SignalSlot() : signal( std::make_shared<Signal>() ) {}
				
				void operator()( const EventType& e ) 
				{ 
					auto& s = *signal;
					s( e );
				}

				template< class ObserverType >
				Connection on( EventPriority priority, ObserverType&& observer )
				{
					return connection_impl( *signal, priority, std::forward<ObserverType>(observer) );
				}
			};
			typedef tbb::concurrent_unordered_map< IdValueType, SignalSlot > SourceSignalIndex;

			SourceSignalIndex m_specifics_signals;
			Signal m_global_signal;

			
			
		public:

			void dispatch( const EventType& event )
			{
				m_global_signal( event );
			}

			void dispatch( const IdValueType& source_id, const EventType& event )
			{
				auto find_it = m_specifics_signals.find( source_id );
				if( find_it != end(m_specifics_signals) )
				{
					find_it->second( event );
				}
				dispatch( event );
			}

			template< class ObserverType >
			auto connect( EventPriority priority, ObserverType&& observer )
				-> typename std::conditional< true, Connection, decltype( observer( *dummy() ) ) >::type
			{
				return connection_impl( m_global_signal, priority, std::forward<ObserverType>(observer) );
			}

			template< class ObserverType >
			auto connect( EventPriority priority, ObserverType observer ) 
				-> typename std::conditional< true, Connection, decltype( observer() ) >::type
			{
				return connection_impl( m_global_signal, priority, [=]( const EventType& ){ observer(); } );
			}

			template< class SourceType, class ObserverType >
			auto connect( EventPriority priority, const Id<SourceType>& id, ObserverType&& observer ) 
				-> typename std::conditional< true, Connection, decltype( observer( *dummy() ) ) >::type
			{
				return m_specifics_signals[id.value()].on( priority, std::forward<ObserverType>(observer) );
			}

			template< class SourceType, class ObserverType >
			auto connect( EventPriority priority, const Id<SourceType>& id, ObserverType observer ) 
				-> typename std::conditional< true, Connection, decltype( observer() ) >::type
			{
				return m_specifics_signals[id.value()].on( priority, [=]( const EventType& ){ observer(); } );
			}


		};

		

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> find_observers()
		{
			auto find_it = m_observers_index.find( typeid(EventType) );
			if( find_it != end(m_observers_index) )
				return std::static_pointer_cast< EventObservers<EventType> >( find_it->second );
			else
				return nullptr;
		}

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> create_observer_group()
		{
			auto new_group = std::make_shared<EventObservers<EventType>>();
			auto insert_info = m_observers_index.insert( std::make_pair( std::type_index(typeid(EventType)), new_group ) );
			UTILCPP_ASSERT( insert_info.second == true, "Tried to register a new observer group but there is already an observer group! Type: " 
				<< typeid(EventType).name() );
			return std::static_pointer_cast< EventObservers<EventType> >( insert_info.first->second );
		}

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> find_or_create_observers()
		{
			auto observers = find_observers<EventType>();
			if( !observers )
				observers = create_observer_group<EventType>();
			UTILCPP_ASSERT_NOT_NULL( observers );
			return observers;
		}

		
	};

	class EventQueueDispatcher
		: private EventDispatcher
	{
	public:
		
		template< class EventType >
		void publish( EventType event )
		{
			m_event_queue.push( [=]{ dispatch( event );	} );			
		}

		template< class EventType, class SourceType >
		void publish( Id<SourceType> source_id,  EventType event )
		{
			m_event_queue.push( [=]{ dispatch( source_id, event );	} );
		}

		void dispatch()
		{
			m_event_queue.execute();
		}

		using EventDispatcher::on;
		using EventDispatcher::observation_api;

	private:
		
		WorkQueue<void> m_event_queue;
		using EventDispatcher::dispatch;
	};

}}

namespace tbb
{
	inline size_t tbb_hasher( const std::type_index& idx )
	{ 
		return std::hash<std::type_index>()( idx );
	}

}

#endif
