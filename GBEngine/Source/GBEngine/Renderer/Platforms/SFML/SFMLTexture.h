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
		~SFMLTexture();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual uint32_t GetRendererID() const override;

		virtual const std::string& GetFilepath() const override;

		sf::Sprite& GetSFMLSprite();
		const sf::Sprite& GetSFMLSprite() const;

		virtual bool operator==(const Texture& other) const override
		{
			// TODO: More comparisons
			return GetFilepath() == other.GetFilepath();
		};

	private:
		bool LoadSprite();

		sf::Sprite m_Sprite;
		sf::Texture m_Texture;
		std::string m_Filepath;
		int2 m_Dimensions;
	};
}