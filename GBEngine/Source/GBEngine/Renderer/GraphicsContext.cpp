#include "gbpch.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"

#include "Platforms/SFML/SFMLGraphicsContext.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace GB
{
	UniquePtr<GraphicsContext> GB::GraphicsContext::Create(void* window)
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
				return CreateUniquePtr<SFMLGraphicsContext>(static_cast<sf::RenderWindow*>(window));
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}