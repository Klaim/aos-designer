#ifndef HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#pragma once

#include <sstream>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/tools/async.hpp>

namespace aosd { 
namespace backend {

	/** CRTP base for types managed by the Workspace.
		Inject several public and protected services common to all 
		objects into the workspace:
		 - event dispatching (into the related workspace event dispatcher);
		 - access to the related workspace;
		 - a work queue automatically scheduling execution ASAP through the workspace update cycle;

		@remark Unless explicitly specified, all the member functions are thread-safe.
	*/
	template< class T >
	class WorkspaceObject
	{
		static T* dummy() { return nullptr; }
	public:

		/** @return Unique identifier of this object. */
		const Id<T>& id() const { return m_id; }

		template< class EventType, class ObserverType >
		EventDispatcher::Connection on( ObserverType&& observer );

		Workspace& workspace() { return m_workspace; }

		template< class TaskType >
		auto on_next_update( TaskType task ) -> future< decltype(task( *dummy() )) >;

	protected:
		explicit WorkspaceObject( Workspace& workspace, Id<T> new_id )
			: m_workspace( workspace )
			, m_id( std::move(new_id) )
		{
			if( !is_valid(m_id) )
			{
				std::stringstream error_message;
				error_message << "Tried to build a '" << typeid(T).name() << '\''
				<< " (inheriting from WorkspaceObject<" << typeid(T).name() << '>'
				<< " with an invalid ID : " << to_string(m_id);
				throw std::invalid_argument( error_message.str() );
			}
		}

		virtual ~WorkspaceObject(){} // = default;

		template< class TaskType >
		auto schedule( TaskType&& task ) -> future< decltype(task()) >;

		template< class TaskType >
		auto async( TaskType&& task ) -> future< decltype(task()) >;

		friend class Workspace::Impl;
		void update();
		virtual void after_update() = 0;
		
		template< class EventType >
		void publish( EventType&& e );
		
	private:
		WorkspaceObject( const WorkspaceObject& ); // = delete;
		WorkspaceObject& operator=( const WorkspaceObject& ); // = delete;

		mutable WorkQueue<void> m_work_queue;
		const Id<T> m_id;
		Workspace& m_workspace;
		
	};

	template< class T >
	template< class EventType, class ObserverType >
	EventDispatcher::Connection WorkspaceObject<T>::on( ObserverType&& observer )
	{
		return m_workspace.m_event_dispatcher.on<EventType>( id(), std::forward<ObserverType>(observer) );
	}

	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::on_next_update( TaskType task ) -> future< decltype(task( *dummy() )) >
	{
		return schedule( [this,task]{
			return task( *static_cast<T*>(this) );
		});
	}

	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::schedule( TaskType&& task ) -> future< decltype(task()) >
	{
		auto result = async_impl( m_work_queue, std::forward<TaskType>(task) );
		m_workspace.request_update();
		return result;
	}

	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::async( TaskType&& task ) -> future< decltype(task()) > 
	{ 
		return m_workspace.async( std::forward<TaskType>(task) ); 
	}

	template< class T >
	void WorkspaceObject<T>::update()
	{ 
		m_work_queue.execute();
		after_update();
		if( !m_work_queue.empty() )
			m_workspace.request_update();
	}


	template< class T >
	template< class EventType >
	void WorkspaceObject<T>::publish( EventType&& ev )
	{
		m_workspace.m_event_dispatcher.publish( id(), std::forward<EventType>(ev) );
	}


}}

#endif