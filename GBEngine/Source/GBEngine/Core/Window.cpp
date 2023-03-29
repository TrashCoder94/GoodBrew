#include "gbpch.h"
#include "Window.h"

#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Events/KeyEvents.h"
#include "GBEngine/Events/MouseEvents.h"
#include "GBEngine/Events/WindowEvents.h"
#include "GBEngine/Renderer/Renderer.h"

#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace GB
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* message)
	{
		GB_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, message);
	}

	UniquePtr<Window> Window::Create(const WindowProperties& properties)
	{
		return CreateUniquePtr<Window>(properties);
	}

	Window::Window(const WindowProperties& properties)
	{
		GB_PROFILE_FUNCTION();
		Init(properties);
	}

	Window::~Window()
	{
		GB_PROFILE_FUNCTION();
		Shutdown();
	}

	void Window::Init(const WindowProperties& properties)
	{
		GB_PROFILE_FUNCTION();

		GB_CORE_LOG_INFO("Creating window {0} ({1}, {2})", properties.m_Title, properties.m_Width, properties.m_Height);

		if (s_GLFWWindowCount == 0)
		{
			GB_PROFILE_SCOPE("glfwInit");
			
			GB_CORE_LOG_INFO("Initialising GLFW!");
			const int glfwInitSuccess = glfwInit();
			GB_CORE_ASSERT(glfwInitSuccess, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			GB_PROFILE_SCOPE("glfwCreateWindow");

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			m_pWindow = glfwCreateWindow((int)properties.m_Width, (int)properties.m_Height, properties.m_Title.c_str(), nullptr, nullptr);
			GB_CORE_ASSERT(m_pWindow, "Failed to create GLFW window!");
			++s_GLFWWindowCount;
		}

		Renderer::Initialize(m_pWindow);

		// Callbacks
		// Window Resize Event
		glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			EventSystem::Get().Broadcast(&event);
		});

		// Window Close Event
		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window)
		{
			WindowCloseEvent event;
			EventSystem::Get().Broadcast(&event);
		});

		// Key Event
		glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// Creating and dispatching the event.
			switch (action)
			{
				// Key press.
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					EventSystem::Get().Broadcast(&event);
					break;
				}
				// Key release.
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					EventSystem::Get().Broadcast(&event);
					break;
				}
				// Key repeat.
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					EventSystem::Get().Broadcast(&event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			// Creating and dispatching the event.
			switch (action)
			{
				// Mouse button press.
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					EventSystem::Get().Broadcast(&event);
					break;
				}
				// Mouse button release.
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					EventSystem::Get().Broadcast(&event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_pWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			// Creating and dispatching the event.
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			EventSystem::Get().Broadcast(&event);
		});

		glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			// Creating and dispatching the event.
			MouseMovedEvent event((float)xPos, (float)yPos);
			EventSystem::Get().Broadcast(&event);
		});

		glfwSetWindowFocusCallback(m_pWindow, [](GLFWwindow* window, int focus)
		{
			// focus > 0 - gained focus
			if (focus > 0)
			{
				WindowFocusEvent event;
				EventSystem::Get().Broadcast(&event);
			}
			// focus <= 0 - lost focus
			else
			{
				WindowLostFocusEvent event;
				EventSystem::Get().Broadcast(&event);
			}
		});
	}

	void Window::Shutdown()
	{
		GB_PROFILE_FUNCTION();

		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			Renderer::Deinitialize();
		}
	}

	void Window::OnUpdate()
	{
		GB_PROFILE_FUNCTION();
		glfwPollEvents();
	}

	uint32_t Window::GetWidth() const
	{
		int width, height;
		glfwGetWindowSize(m_pWindow, &width, &height);
		return width;
	}

	uint32_t Window::GetHeight() const
	{
		int width, height;
		glfwGetWindowSize(m_pWindow, &width, &height);
		return height;
	}

	void* Window::GetNativeWindow() const
	{
		return m_pWindow;
	}
}