#ifndef HGUARD_AOSD_BACKEND_WORKSPACE_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACE_HPP__

#include <functional>
#include <memory>
#include <type_traits>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/taskexecutor.hpp>
#include <aosdesigner/backend/tools/eventdispatcher.hpp>
#include <aosdesigner/backend/tools/async.hpp>
#include <aosdesigner/backend/tools/uri.hpp>


namespace aosd {
namespace backend {

	class AOSD_BACKEND_API Workspace
	{
	public:
				
		explicit Workspace( TaskExecutor executor ); // THINK: set a default task executor?
		~Workspace();

		

		EventDispatcher::ObservationAPI& event_dispatcher() const { return m_event_dispatcher.observation_api(); }

		// Dispatch queued events to observers using the calling thread.
		void dispatch_events();
		
		void request_update();

		// TODO: project, sequence, editor, library thread-safe access - must occur in the workspace queue or async?
		//template< class ObjectType, class TaskType >
		//auto async( Id<ObjectType> id, TaskType task ) -> future< boost::optional<decltype(task( *dummy() ))> >
		//{
		//	return async( [=]{
		//			if( auto object = object_registry.find( id ) ) // return a shared_ptr if it managed to lock it
		//			{
		//				return task( *object );
		//			}
		//			return {};
		//		});
		//}

		//SequenceInfo get_sequence_info( SequenceId sequence_id );
		//ProjectInfo get_project_info( ProjectId project_id );
		//EditorInfo get_editeditor_info( EditorId edit_editor_id );

		//future<ProjectId> create_project();
		//future<ProjectId> open_project( URI project_address );
		//future<void> close_project( ProjectId project_id );

		
		

	private:
		Workspace( const Workspace& ); // = delete;
		Workspace& operator=( const Workspace& ); // = delete;

		template<class T> friend class WorkspaceObject;

		TaskExecutor m_executor;
		mutable EventQueueDispatcher m_event_dispatcher;
		
		template< class TaskType >
		auto async( TaskType&& task ) -> future<decltype(task())>
		{
			return async_impl( m_executor, std::forward<TaskType>(task) );
		}

		void add_to_registry( std::weak_ptr<Project> project );
		void add_to_registry( std::weak_ptr<Sequence> sequence );
		void add_to_registry( std::weak_ptr<Editor> editor );
		void add_to_registry( std::weak_ptr<Library> library );

		class Impl;
		std::unique_ptr<Impl> pimpl;

	};


}}


#endif
