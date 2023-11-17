#include "gbpch.h"
#include "SFMLTexture.h"
#include "GBEngine/Core/Application.h"
#include "GBEngine/Core/Platforms/SFML/SFMLWindow.h"

namespace GB
{
	SFMLTexture::SFMLTexture(uint32_t width, uint32_t height) : Texture2D(width, height),
		m_Sprite(),
		m_Texture()
	{
		if (!LoadSprite())
		{
			GB_CORE_LOG_ERROR("Couldn't load sprite with dimensions %d x %d", width, height);
		}
	}

	SFMLTexture::SFMLTexture(const std::string& filepath) : Texture2D(filepath),
		m_Sprite(),
		m_Texture()
	{
		if (!LoadSprite())
		{
			GB_CORE_LOG_ERROR("Couldn't load sprite from filepath %s", m_Filepath.c_str());
		}
	}

	sf::Sprite& SFMLTexture::GetSFMLSprite()
	{
		return m_Sprite;
	}

	const sf::Sprite& SFMLTexture::GetSFMLSprite() const
	{
		return m_Sprite;
	}

	bool SFMLTexture::LoadSprite()
	{
		bool bSuccessfullyLoaded = true;

		if (m_Filepath.empty())
		{
			if (!m_Texture.create(m_Dimensions.x, m_Dimensions.y))
			{
				bSuccessfullyLoaded = false;
				GB_CORE_ASSERT(bSuccessfullyLoaded, "SFML failed to create the texture with the given dimensions, check these are valid values!");
				return false;
			}
		}
		else
		{
			if (!m_Texture.loadFromFile(m_Filepath))
			{
				bSuccessfullyLoaded = false;
				GB_CORE_ASSERT(bSuccessfullyLoaded, "SFML failed to load the texture, check filepath and where the texture lives!");
				return false;
			}
		}

		m_Sprite.setTexture(m_Texture);
		
		return bSuccessfullyLoaded;
	}
}