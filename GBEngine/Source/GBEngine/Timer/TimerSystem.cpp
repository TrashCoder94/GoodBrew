#include "gbpch.h"
#include "TimerSystem.h"
#include "Timer.h"

namespace GB
{
	TimerSystem* TimerSystem::s_pInstance = nullptr;

	TimerSystem::TimerSystem() : 
		m_Timers(),
		m_TimersToRemove()
	{
		GB_CORE_ASSERT(!s_pInstance, "TimerSystem already exists!");
		s_pInstance = this;
	}

	TimerSystem::~TimerSystem()
	{
		s_pInstance = nullptr;
	}

	TimerSystem& TimerSystem::Get()
	{
		return *s_pInstance;
	}

	int TimerSystem::AddTimer(BaseObject* pObject, const std::function<void()>& function, const float time)
	{
		static int timerHandles = 0;
		++timerHandles;
		Timer timer(time, timerHandles);
		timer.m_Function = function;
		
		m_Timers.push_back(timer);

		return timerHandles;
	}

	void TimerSystem::ClearTimer(const int timerHandle)
	{
		for (size_t iT = m_Timers.size() - 1; iT > 0; --iT)
		{
			Timer& timer = m_Timers[iT];
			if (timer.m_Handle == timerHandle)
			{
				m_Timers.erase(m_Timers.begin() + iT);
				break;
			}
		}
	}

	void TimerSystem::Update(const float deltaTime)
	{
		if (m_Timers.empty())
		{
			return;
		}

		// Tick any active timers
		for (size_t iT = 0; iT < m_Timers.size(); ++iT)
		{
			Timer& timer = m_Timers[iT];
			timer.m_CurrentTime -= deltaTime;

			if (timer.m_CurrentTime <= 0.0f)
			{
				timer.m_Function();
				m_TimersToRemove.push_back(iT);
			}
		}

		// Remove any timers that have finished
		if (!m_TimersToRemove.empty())
		{
			for (size_t iT : m_TimersToRemove)
			{
				m_Timers.erase(m_Timers.begin() + iT);
			}

			m_TimersToRemove.clear();
		}
	}

	void TimerSystem::Shutdown()
	{
		m_Timers.clear();
		m_TimersToRemove.clear();
	}
}