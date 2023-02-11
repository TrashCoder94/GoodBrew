#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

namespace GB
{
	struct WindowProperties
	{
		std::string m_Title;
		uint32_t m_Width;
		uint32_t m_Height;

		WindowProperties(const std::string& title = "GBEngine",
			uint32_t width = 1600,
			uint32_t height = 900) :
			m_Title(title),
			m_Width(width),
			m_Height(height)
		{}
	};

	class Window
	{
	public:
		//using EventCallbackFn = std::function<void(Event&)>;
		Window(const WindowProperties& properties);
		~Window();

	private:
		void Init(const WindowProperties& properties);
		void Shutdown();

	public:
		void OnUpdate();

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		void* GetNativeWindow() const;

		static UniquePtr<Window> Create(const WindowProperties& properties = WindowProperties());

	protected:
		GLFWwindow* m_pWindow;
	};
}
