#pragma once

#include <string>
#include "LayerStack.h"
#include "GBEngine/Objects/BaseObject.h"

int main(int argc, char** argv);

namespace GB
{
	class Event;
#if GB_IMGUI_ENABLED
	class ImGuiLayer;
#endif
	class Window;

	class Application : public BaseObject
	{
	public:
		Application(const std::string& name = "GB Application");
		virtual ~Application();

		Window& GetWindow();
		static Application& Get();

	protected:
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void Close();

	private:
		void Run();

		bool OnWindowClose(Event* e);
		bool OnWindowResized(Event* e);
		bool OnWindowFocus(Event* e);
		bool OnWindowLostFocus(Event* e);

		UniquePtr<Window> m_pWindow;
		LayerStack m_LayerStack;
#if GB_IMGUI_ENABLED
		ImGuiLayer* m_pImGuiLayer;
#endif
		bool m_Running;
		bool m_Minimized;
		bool m_IsFocused;
		bool m_WaitForFullFocus;

		static Application* s_pInstance;

		// Used so we can keep Run() private and not expose it to client applications.
		// This may need to change if there are any updates to EntryPoint.h
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
