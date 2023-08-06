#include "gbpch.h"
#include "Application.h"
#include "GBEngine/Core/GBSystems.h"
#include "GBEngine/Core/Window.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/EventTypes.h"
#include "GBEngine/Events/WindowEvents.h"
#include <SFML/Window.hpp>
#if GB_IMGUI_ENABLED
#include "GBEngine/ImGui/ImGuiLayer.h"
#endif

namespace GB
{
	Application* Application::s_pInstance = nullptr;

	Application::Application(const std::string& name /*= "GB Application"*/) :
		m_pWindow(nullptr),
		m_LayerStack(),
#if GB_IMGUI_ENABLED
		m_pImGuiLayer(nullptr),
#endif
		m_Running(true),
		m_Minimized(false),
		m_IsFocused(true),
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

#if GB_IMGUI_ENABLED
		m_pImGuiLayer = new ImGuiLayer();
		PushOverlay(m_pImGuiLayer);
#endif
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
	}

	void Application::PushOverlay(Layer* overlay)
	{
		GB_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		GB_PROFILE_FUNCTION();

		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		GB_PROFILE_FUNCTION();

		m_LayerStack.PopOverlay(overlay);
	}

	void Application::Close()
	{
		m_Running = false;

#if GB_IMGUI_ENABLED
		if (m_pImGuiLayer)
		{
			PopOverlay(m_pImGuiLayer);
			m_pImGuiLayer = nullptr;
		}
#endif
	}

	void Application::Run()
	{
		GB_PROFILE_FUNCTION();

		// TODO: Think of a neat way to abstract this logic out
		// Needed for SFML+ImGui...
		sf::Clock deltaClock;

		while (m_Running)
		{
			GB_PROFILE_SCOPE("RunLoop");
			
			m_pWindow->Update();

			if (m_pWindow)
			{
				m_pWindow->Begin();
				{
					const sf::Time& sfDeltaTime = deltaClock.restart();
					const float deltaTime = sfDeltaTime.asSeconds();

					if (m_IsFocused)
					{
						if (!m_Minimized)
						{
							{
								GB_PROFILE_SCOPE("LayerStack OnUpdate");

								for (Layer* layer : m_LayerStack)
								{
									layer->OnUpdate(deltaTime);
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

						GBSystems::Update(deltaTime);
					}

#if GB_IMGUI_ENABLED
					if (m_pImGuiLayer)
					{
						// Specific ImGui Layer update function to pass along sf::Time for ImGui SFML implementation
						m_pImGuiLayer->Update(sfDeltaTime);

						m_pImGuiLayer->Begin();
						{
							GB_PROFILE_SCOPE("LayerStack OnImGuiRender");

							for (Layer* layer : m_LayerStack)
							{
								layer->OnImGuiRender();
							}
						}
						m_pImGuiLayer->End();
					}
#endif
				}
				m_pWindow->End();
			}
		}
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