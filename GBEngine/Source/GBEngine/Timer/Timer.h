#pragma once

namespace GB
{
	class Timer
	{
		friend class TimerSystem;

	public:
		Timer(const float targetTime, const int handle);
		~Timer();

	private:
		float m_CurrentTime;
		int m_Handle;
		std::function<void()> m_Function;
	};
}