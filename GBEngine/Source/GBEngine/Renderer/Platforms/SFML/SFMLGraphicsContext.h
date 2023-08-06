#pragma once

#include "GBEngine/Renderer/GraphicsContext.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace GB
{
	class SFMLGraphicsContext : public GraphicsContext
	{
	public:
		SFMLGraphicsContext(sf::RenderWindow* pWindow);
		~SFMLGraphicsContext();

		virtual void Initialize() override;
		virtual void Deinitialize() override;

	private:
		sf::RenderWindow* m_pWindow;
	};
}