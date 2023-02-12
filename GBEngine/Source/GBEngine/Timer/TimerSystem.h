#pragma once

namespace GB
{
	class BaseObject;
	class Timer;

	class TimerSystem
	{
		friend class GBSystems;

	public:
		TimerSystem();
		~TimerSystem();

		static TimerSystem& Get();

		int AddTimer(BaseObject* pObject, const std::function<void()>& function, const float time);
		void ClearTimer(const int timerHandle);

	private:
		void Update(const float deltaTime);
		void Shutdown();

		static TimerSystem* s_pInstance;

		std::vector<Timer> m_Timers;
		std::vector<size_t> m_TimersToRemove;
	};
}