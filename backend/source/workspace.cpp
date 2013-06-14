#include <aosdesigner/backend/workspace.hpp>

#include <atomic>
#include <memory>
#include <boost/container/flat_map.hpp>
#include <tbb/concurrent_unordered_map.h>

#include <utilcpp/make_unique.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/library.hpp>

#include "workspaceinternalapi.hpp"

namespace aosd {
namespace backend {



	template< class T >
	class WeakRegistry
	{
	public:
		WeakRegistry(){} // = default;

		void add( Id<T> id, std::shared_ptr<T> object )
		{
			// TODO: add some checks
			m_index.insert( std::make_pair( std::move(id), std::move(object) ) );
		}

		std::shared_ptr<T> find( const Id<T>& id ) const
		{
			auto find_it = m_index.find( id );
			if( find_it != end(m_index) )
			{
				if( auto object = find_it->second.lock() )
				{
					return object;
				}
			}

			return nullptr;
		}

	private:
		WeakRegistry( const WeakRegistry& ); // = delete;
		WeakRegistry& operator=( const WeakRegistry& ); // = delete;

		tbb::concurrent_unordered_map< Id<T>, std::weak_ptr<T> > m_index; 

	};

	using boost::container::flat_map;

	class Workspace::Impl
	{
	public:
		Impl( Workspace& workspace );
		~Impl(){} // = default

		void request_update();

		void register_editor( std::shared_ptr<Editor> editor ) { register_impl( editor, m_editor_registry ); }
		void register_library( std::shared_ptr<Library> library ) { register_impl( library, m_library_registry ); }
		void register_sequence( std::shared_ptr<Sequence> sequence ) { register_impl( sequence, m_sequence_registry ); }

		

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		friend class WorkspaceInternalAPI;

		Workspace& m_workspace;

		WorkQueue<void> m_work_queue;
		std::atomic<unsigned long> m_update_request_count;

		WeakRegistry<Project>	m_project_registry;
		WeakRegistry<Editor>	m_editor_registry;
		WeakRegistry<Library>	m_library_registry;
		WeakRegistry<Sequence>	m_sequence_registry;

		
		flat_map< ProjectId, std::shared_ptr<Project> > m_project_index;

		void update_loop();
		void update();

		template< class T >
		void register_impl( std::shared_ptr<T> object, WeakRegistry<T>& registry )
		{
			registry.add( object->id(), object );
		}

	};

	Workspace::Impl::Impl( Workspace& workspace ) 
		: m_workspace( workspace )
		, m_update_request_count( 0 )
	{

	}

	void Workspace::Impl::request_update()
	{
		if( m_update_request_count > 0 )
		{
			++m_update_request_count;
		}
		else
		{
			m_workspace.async( [&]{ update_loop(); } );
		}
	}

	void Workspace::Impl::update_loop()
	{
		++m_update_request_count;
		while( m_update_request_count > 0 )
		{
			const auto request_count_on_begin = m_update_request_count.load();
			update();
			m_update_request_count -= request_count_on_begin;			
		}
	}

	void Workspace::Impl::update()
	{
		m_work_queue.execute();
		
		// TODO: update all projects using async()
		for( auto& project_slot : m_project_index )
		{
			auto& project = project_slot.second;
			m_workspace.async( [project]{ project->update(); } );
		}

		if( !m_work_queue.empty() )
			request_update();

	}

	///////////////////////

	Workspace::InternalAPI::InternalAPI( Workspace::Impl& workspace_impl )
		: m_workspace_impl( workspace_impl )
	{

	}

	void Workspace::InternalAPI::add_to_registry( std::shared_ptr<Sequence> sequence )
	{
		m_workspace_impl.register_sequence( std::move(sequence) );
	}


	///////////////////////

	Workspace::Workspace( TaskExecutor executor )
		: m_executor( std::move(executor) )
		, pimpl( std::make_unique<Impl>( *this ) )
	{

	}

	Workspace::~Workspace()
	{

	}

	void Workspace::dispatch_events()
	{
		m_event_dispatcher.dispatch();
	}


	void Workspace::request_update()
	{
		pimpl->request_update();
	}

	Workspace::InternalAPI Workspace::internal_api()
	{
		return InternalAPI(*pimpl);
	}

	

}}