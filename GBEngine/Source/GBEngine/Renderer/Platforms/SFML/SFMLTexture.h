#pragma once

#include "GBEngine/Renderer/Texture.h"
#include <linalg.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace linalg::aliases;

namespace GB
{
	class SFMLTexture : public Texture2D
	{
	public:
		SFMLTexture(uint32_t width, uint32_t height);
		SFMLTexture(const std::string& filepath);

		sf::Sprite& GetSFMLSprite();
		const sf::Sprite& GetSFMLSprite() const;

	private:
		bool LoadSprite();

		sf::Sprite m_Sprite;
		sf::Texture m_Texture;
	};
}