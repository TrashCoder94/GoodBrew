#include "gbpch.h"
#include "Application.h"
#include "GBEngine/Core/Window.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/EventTypes.h"
#include "GBEngine/Events/WindowEvents.h"

#include <GLFW/glfw3.h>

namespace GB
{
	Application* Application::s_pInstance = nullptr;

	Application::Application(const std::string& name /*= "GB Application"*/) :
		m_pWindow(nullptr),
		m_Running(true),
		m_Minimized(false),
		m_IsFocused(true),
		m_DeltaTime(0.0f),
		m_LastFrameTime(0.0f),
		m_WaitForFullFocus(false)
	{
		GB_PROFILE_FUNCTION();

		GB_CORE_ASSERT(!s_pInstance, "Application already exists!");
		s_pInstance = this;
		
		m_pWindow = Window::Create(WindowProperties(name));
		EventSystem::Get().Bind(EEventType::WindowClose, this, GB_EVENT_FUNCTION(Application::OnWindowClose));
		EventSystem::Get().Bind(EEventType::WindowResize, this, GB_EVENT_FUNCTION(Application::OnWindowResized));
		EventSystem::Get().Bind(EEventType::WindowFocus, this, GB_EVENT_FUNCTION(Application::OnWindowFocus));
		EventSystem::Get().Bind(EEventType::WindowLostFocus, this, GB_EVENT_FUNCTION(Application::OnWindowLostFocus));
	}

	Application::~Application()
	{
		GB_PROFILE_FUNCTION();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	Window& Application::GetWindow()
	{
		return *m_pWindow;
	}

	Application& Application::Get()
	{
		return *s_pInstance;
	}

	void Application::Run()
	{
		GB_PROFILE_FUNCTION();

		while (m_Running)
		{
			GB_PROFILE_SCOPE("RunLoop");

			if (m_IsFocused)
			{
				float time = GetTime();
				m_DeltaTime = time - m_LastFrameTime;
				m_LastFrameTime = time;

				if (!m_Minimized)
				{
					// TODO: Update/Render calls here...
				}
			}

			m_pWindow->OnUpdate();
			bgfx::frame();
		}
	}

	float Application::GetTime()
	{
		float time{ (float)glfwGetTime() };
		if (m_WaitForFullFocus)
		{
			m_LastFrameTime = time - m_LastFrameTime;
			m_WaitForFullFocus = false;
		}
		return time;
	}

	bool Application::OnWindowClose(Event* e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResized(Event* e)
	{
		GB_PROFILE_FUNCTION();

		WindowResizeEvent* pWindowResizeEvent = static_cast<WindowResizeEvent*>(e);
		const int newWidth = pWindowResizeEvent->GetWidth();
		const int newHeight = pWindowResizeEvent->GetHeight();
		if (pWindowResizeEvent->GetWidth() == 0 || pWindowResizeEvent->GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		int width, height;
		glfwGetWindowSize(static_cast<GLFWwindow*>(m_pWindow->GetNativeWindow()), &width, &height);
		
		GB_CORE_ASSERT(width == newWidth && height == newHeight, "WindowResizeEvent width and height do not match window width and height");

		const bgfx::ViewId kClearView = 0;
		bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
		bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

		return false;
	}

	bool Application::OnWindowFocus(Event* e)
	{
		m_IsFocused = true;
		return false;
	}

	bool Application::OnWindowLostFocus(Event* e)
	{
		m_IsFocused = false;
		m_WaitForFullFocus = true;
		return false;
	}
}