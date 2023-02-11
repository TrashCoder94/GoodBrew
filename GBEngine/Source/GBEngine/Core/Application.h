#pragma once

#include "GBEngine/Objects/BaseObject.h"
#include <string>

int main(int argc, char** argv);

namespace GB
{
	class Window;
	class Event;

	class Application : public BaseObject
	{
	public:
		Application(const std::string& name = "GB Application");
		virtual ~Application();

		void Close();

		Window& GetWindow();
		static Application& Get();
	private:
		void Run();
		float GetTime();

		bool OnWindowClose(Event* e);
		bool OnWindowResized(Event* e);
		bool OnWindowFocus(Event* e);
		bool OnWindowLostFocus(Event* e);

		UniquePtr<Window> m_pWindow;

		bool m_Running;
		bool m_Minimized;
		bool m_IsFocused;
		float m_DeltaTime;
		float m_LastFrameTime;
		bool m_WaitForFullFocus;

		static Application* s_pInstance;

		// Used so we can keep Run() private and not expose it to client applications.
		// This may need to change if there are any updates to EntryPoint.h
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
