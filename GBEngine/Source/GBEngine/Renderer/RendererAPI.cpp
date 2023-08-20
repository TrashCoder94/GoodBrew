#include "gbpch.h"
#include "RendererAPI.h"
#include "Platforms/SFML/SFMLRendererAPI.h"
#include "GBEngine/Core/Platforms/SFML/SFMLWindow.h"
#include "Texture.h"

namespace GB
{
	RendererAPI::EAPI RendererAPI::s_API = RendererAPI::EAPI::None;

	UniquePtr<RendererAPI> RendererAPI::Create(void* pWindow)
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
				GB_PTR(pSFMLRenderWindow, static_cast<sf::RenderWindow*>(pWindow), "pSFMLWindow->GetNativeWindow() isn't an sf::RenderWindow!");
				return CreateUniquePtr<SFMLRendererAPI>(pSFMLRenderWindow);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}