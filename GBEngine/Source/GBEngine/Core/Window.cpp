#include "gbpch.h"
#include "Window.h"

#include "GBEngine/Renderer/RendererAPI.h"
#include "Platforms/SFML/SFMLWindow.h"

namespace GB
{
	UniquePtr<Window> Window::Create(const WindowProperties& properties)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::EAPI::None:
			{
				GB_CORE_ASSERT(false, "RendererAPI::EAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::EAPI::SFML:
			{
				return CreateUniquePtr<SFMLWindow>(properties);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Window::Window(const WindowProperties& properties)
	{}

	Window::~Window()
	{}

	void Window::Begin()
	{
		GB_PROFILE_FUNCTION();
		OnBegin();
	}

	void Window::Update()
	{
		GB_PROFILE_FUNCTION();
		OnUpdate();
	}

	void Window::End()
	{
		GB_PROFILE_FUNCTION();
		OnEnd();
	}
}
