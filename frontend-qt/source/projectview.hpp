#ifndef HGUARD_AOSD_VIEW_PROJECTVIEW_HPP__
#define HGUARD_AOSD_VIEW_PROJECTVIEW_HPP__
#pragma once

#include <memory>

#include <QDockWidget>

class QTabWidget;

namespace aosd
{
	namespace backend { class Project; }

namespace view
{
	class SequenceListView;

	/** Display the basic information about a Project and the Sequences it contains.
		Allows edition of those information.
	*/
	class ProjectView
		: public QDockWidget
	{
		Q_OBJECT
	public:
		
		ProjectView();
		~ProjectView();
		
	
	private slots:

		void react_project_open( const backend::Project& );
		void react_project_closed( const backend::Project& );

	private:
		
		/// Tabs with different views of the information of this project.
		std::unique_ptr<QTabWidget> m_tabs;
		
	};


}
}


#endif
