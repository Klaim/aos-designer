#ifndef HGUARD_AOSD_BACKEND_EDITOR_HPP__
#define HGUARD_AOSD_BACKEND_EDITOR_HPP__
#pragma once

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>
#include <aosdesigner/backend/editorinfo.hpp>

namespace aosd {
namespace backend {

	class Project;

	class AOSD_BACKEND_API Editor
		: public WorkspaceObject<Editor>
	{
	public:
		~Editor();

		EditorInfo info() const;

	private:
		friend class Project;
		explicit Editor( Project& project );

		class Impl;
		std::unique_ptr<Impl> impl;

	};

}}


#endif