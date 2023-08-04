#include "gbpch.h"
#include "GBSystems.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Renderer/RendererAPI.h"
#include "GBEngine/Timer/TimerSystem.h"
#include "Log.h"

namespace GB
{
	std::unique_ptr<EventSystem> GBSystems::s_pEventSystem = nullptr;
	std::unique_ptr<TimerSystem> GBSystems::s_pTimerSystem = nullptr;

	void GBSystems::Init()
	{
		GB::Log::Init();

		// Is this the best place for this to live?
		RendererAPI::SetAPI(RendererAPI::EAPI::SFML);

		s_pEventSystem = std::make_unique<EventSystem>();
		s_pTimerSystem = std::make_unique<TimerSystem>();
	}

	void GBSystems::Update(const float deltaTime)
	{
		s_pTimerSystem->Update(deltaTime);
	}

	void GBSystems::Shutdown()
	{
		s_pTimerSystem->Shutdown();
	}
}