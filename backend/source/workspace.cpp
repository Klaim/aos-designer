#include <aosdesigner/backend/workspace.hpp>

#include <utilcpp/make_unique.hpp>


namespace aosd {
namespace backend {

	Workspace::Workspace( TaskExecutor executor )
		: m_executor( std::move(executor) )
		, pimpl( std::make_unique<Impl>( *this ) )
	{

	}

	Workspace::~Workspace()
	{

	}


	class Workspace::Impl
	{
	public:
		Impl( Workspace& workspace ) 
			: m_workspace( workspace )
		{

		}

	private:
		Workspace& m_workspace;

	};

}}