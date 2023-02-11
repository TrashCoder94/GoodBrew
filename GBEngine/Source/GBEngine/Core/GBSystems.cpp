#include "gbpch.h"
#include "GBSystems.h"
#include "GBEngine/Events/EventSystem.h"
#include "Log.h"

namespace GB
{
	std::unique_ptr<EventSystem> GBSystems::s_pEventSystem = nullptr;

	void GBSystems::Init()
	{
		GB::Log::Init();
		s_pEventSystem = std::make_unique<EventSystem>();
	}

	void GBSystems::Shutdown()
	{
	}
}