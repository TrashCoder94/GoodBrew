#pragma once

#include "GBEngine/Renderer/RendererAPI.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace GB
{
	class SFMLRendererAPI : public RendererAPI
	{
	public:
		SFMLRendererAPI(sf::RenderWindow* pWindow);
		~SFMLRendererAPI();

		virtual void Initialize() final override;
		virtual void DrawTexture(Texture2D* pTexture) final override;
		virtual void Deinitialize() final override;

	private:
		sf::RenderWindow* m_pRenderWindow;
	};
}