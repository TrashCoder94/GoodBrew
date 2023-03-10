#include "gbpch.h"
#include "Application.h"
#include "GBEngine/Core/GBSystems.h"
#include "GBEngine/Core/Window.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/EventTypes.h"
#include "GBEngine/Events/WindowEvents.h"
#include "GBEngine/ImGui/ImGuiLayer.h"

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>

namespace GB
{
	Application* Application::s_pInstance = nullptr;

	Application::Application(const std::string& name /*= "GB Application"*/) :
		m_pWindow(nullptr),
		m_LayerStack(),
		m_pImGuiLayer(nullptr),
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

		m_pImGuiLayer = new ImGuiLayer();
		PushOverlay(m_pImGuiLayer);
	}

	Application::~Application()
	{
		GB_PROFILE_FUNCTION();

		GB_UNBIND_EVENT(EEventType::WindowClose, this);
		GB_UNBIND_EVENT(EEventType::WindowResize, this);
		GB_UNBIND_EVENT(EEventType::WindowFocus, this);
		GB_UNBIND_EVENT(EEventType::WindowLostFocus, this);
	}

	Window& Application::GetWindow()
	{
		return *m_pWindow;
	}

	Application& Application::Get()
	{
		return *s_pInstance;
	}

	void Application::PushLayer(Layer* layer)
	{
		GB_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		GB_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		GB_PROFILE_FUNCTION();

		while (m_Running)
		{
			GB_PROFILE_SCOPE("RunLoop");

			m_pWindow->OnUpdate();

			if (m_IsFocused)
			{
				float time = GetTime();
				m_DeltaTime = time - m_LastFrameTime;
				m_LastFrameTime = time;
				
				if (!m_Minimized)
				{
					{
						GB_PROFILE_SCOPE("LayerStack OnUpdate");

						for (Layer* layer : m_LayerStack)
						{
							layer->OnUpdate(m_DeltaTime);
						}
					}

					{
						GB_PROFILE_SCOPE("LayerStack OnRender");

						for (Layer* layer : m_LayerStack)
						{
							layer->OnRender();
						}
					}
				}
			
				GBSystems::Update(m_DeltaTime);
			}

			m_pImGuiLayer->Begin();
			{
				GB_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}
			m_pImGuiLayer->End();

			// This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
			static constexpr bgfx::ViewId kClearView = 0;
			bgfx::touch(kClearView);

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