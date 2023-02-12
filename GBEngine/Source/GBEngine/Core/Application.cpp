#include "gbpch.h"
#include "Application.h"
#include "GBEngine/Core/GBSystems.h"
#include "GBEngine/Core/Window.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/EventTypes.h"
#include "GBEngine/Events/WindowEvents.h"

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

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
		GB_BIND_EVENT(EEventType::WindowClose, this, Application::OnWindowClose);
		GB_BIND_EVENT(EEventType::WindowResize, this, Application::OnWindowResized);
		GB_BIND_EVENT(EEventType::WindowFocus, this, Application::OnWindowFocus);
		GB_BIND_EVENT(EEventType::WindowLostFocus, this, Application::OnWindowLostFocus);
	}

	Application::~Application()
	{
		GB_PROFILE_FUNCTION();

		GB_UNBIND_EVENT(EEventType::WindowClose, this);
		GB_UNBIND_EVENT(EEventType::WindowResize, this);
		GB_UNBIND_EVENT(EEventType::WindowFocus, this);
		GB_UNBIND_EVENT(EEventType::WindowLostFocus, this);
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
			
				GBSystems::Update(m_DeltaTime);
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
		
		const bgfx::ViewId kClearView = 0;
		bgfx::reset((uint32_t)newWidth, (uint32_t)newHeight, BGFX_RESET_VSYNC);
		bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
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