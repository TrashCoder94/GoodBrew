#include "gbpch.h"
#include "SFMLWindow.h"

#include <SFML/Window/Event.hpp>

#if GB_IMGUI_ENABLED
#include <imgui-SFML.h>
#endif

#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/KeyEvents.h"
#include "GBEngine/Events/MouseEvents.h"
#include "GBEngine/Events/WindowEvents.h"
#include "GBEngine/Renderer/Renderer.h"

namespace GB
{
	static uint8_t s_SFMLWindowCount = 0;

	SFMLWindow::SFMLWindow(const WindowProperties& properties) : Window(properties),
		m_pWindow(nullptr)
	{
		GB_PROFILE_FUNCTION();
		Init(properties);
	}

	SFMLWindow::~SFMLWindow()
	{
		GB_CORE_LOG_INFO("SFML Window shutdown being called...");

		GB_PROFILE_FUNCTION();
		Shutdown();
	}

	uint32_t SFMLWindow::GetWidth() const
	{
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		return m_pWindow->getSize().x;
	}

	uint32_t SFMLWindow::GetHeight() const
	{
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		return m_pWindow->getSize().y;
	}

	void* SFMLWindow::GetNativeWindow() const
	{
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		return m_pWindow;
	}

	void SFMLWindow::Init(const WindowProperties& properties)
	{
		GB_PROFILE_FUNCTION();
		
		GB_CORE_LOG_INFO("Creating window {0} ({1}, {2})", properties.m_Title, properties.m_Width, properties.m_Height);
		{
			GB_PROFILE_SCOPE("SFML Create Window");
		
			m_pWindow = new sf::RenderWindow(sf::VideoMode(properties.m_Width, properties.m_Height), properties.m_Title);
			GB_CORE_ASSERT(m_pWindow, "Failed to create SFML window!");
			++s_SFMLWindowCount;
		}

		// First window has just been created, initialize the Renderer since we need to start work now
		if (s_SFMLWindowCount == 1)
		{
			Renderer::Initialize(m_pWindow);
		}
	}

	void SFMLWindow::OnBegin()
	{
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		m_pWindow->clear();
	}

	void SFMLWindow::OnUpdate()
	{
		sf::Event event;
		while (m_pWindow->pollEvent(event) && m_pWindow->isOpen())
		{
#if GB_IMGUI_ENABLED
			ImGui::SFML::ProcessEvent(*m_pWindow, event);
#endif

			switch (event.type)
			{
				case sf::Event::Resized:
				{
					WindowResizeEvent e(event.size.width, event.size.height);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::Closed:
				{
					WindowCloseEvent e;
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::KeyPressed:
				{
					KeyPressedEvent e((int)event.key.code, 0);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::KeyReleased:
				{
					KeyReleasedEvent e((int)event.key.code);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					MouseButtonPressedEvent e((int)event.mouseButton.button);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					MouseButtonReleasedEvent e((int)event.mouseButton.button);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::MouseWheelScrolled:
				{
					MouseScrolledEvent e((float)event.mouseWheel.x, (float)event.mouseWheel.y); // Might just have to use delta instead?
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::MouseMoved:
				{
					MouseMovedEvent e((float)event.mouseMove.x, (float)event.mouseMove.y);
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::GainedFocus:
				{
					WindowFocusEvent e;
					EventSystem::Get().Broadcast(&e);
					break;
				}
				case sf::Event::LostFocus:
				{
					WindowLostFocusEvent e;
					EventSystem::Get().Broadcast(&e);
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}

	void SFMLWindow::OnEnd()
	{
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		m_pWindow->display();
	}

	void SFMLWindow::Shutdown()
	{
		GB_PROFILE_FUNCTION();

		GB_CORE_LOG_INFO("SFML Window about to call close");
		m_pWindow->close();

		GB_CORE_LOG_INFO("SFML Window ptr about to be cleaned up");
		if (m_pWindow)
		{
			delete m_pWindow;
			m_pWindow = nullptr;
		}

		--s_SFMLWindowCount;

		if (s_SFMLWindowCount == 0)
		{
			GB_CORE_LOG_INFO("Renderer::Deinitialize being called");
			Renderer::Deinitialize();
		}
	}
}