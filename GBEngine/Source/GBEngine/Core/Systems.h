#pragma once

#include <memory>

int main(int argc, char** argv);

namespace GB
{
	class EventSystem;
	class TimerSystem;

	class Systems
	{
		friend int ::main(int argc, char** argv);
		friend class Application;

	private:
		static void Init();
		static void Update(const float deltaTime);
		static void Shutdown();

		// Add any new global systems below here and initialize them in the .cpp
		static std::unique_ptr<EventSystem> s_pEventSystem;
		static std::unique_ptr<TimerSystem> s_pTimerSystem;
	};
}