#pragma once

#include <memory>

int main(int argc, char** argv);

namespace GB
{
	class EventSystem;

	class GBSystems
	{
		friend int ::main(int argc, char** argv);

	private:
		static void Init();
		static void Shutdown();

		// Add any new global systems below here and initialize them in the .cpp
		static std::unique_ptr<EventSystem> s_pEventSystem;
	};
}