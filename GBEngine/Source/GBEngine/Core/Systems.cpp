#include "gbpch.h"
#include "Systems.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Renderer/RendererAPI.h"
#include "GBEngine/Timer/TimerSystem.h"
#include "Log.h"

#include <GBReflect.h>

//extern void reflect::InitReflectionSystem();

namespace GB
{
	std::unique_ptr<EventSystem> Systems::s_pEventSystem = nullptr;
	std::unique_ptr<TimerSystem> Systems::s_pTimerSystem = nullptr;

	void Systems::Init()
	{
		GB::Log::Init();

		// Is this the best place for this to live?
		RendererAPI::SetAPI(RendererAPI::EAPI::SFML);

		s_pEventSystem = std::make_unique<EventSystem>();
		s_pTimerSystem = std::make_unique<TimerSystem>();

		//reflect::InitReflectionSystem();
	}

	void Systems::Update(const float deltaTime)
	{
		s_pTimerSystem->Update(deltaTime);
	}

	void Systems::Shutdown()
	{
		s_pTimerSystem->Shutdown();
	}
}