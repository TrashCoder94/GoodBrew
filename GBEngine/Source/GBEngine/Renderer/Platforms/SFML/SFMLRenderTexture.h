#pragma once

#include "GBEngine/Renderer/RenderTexture.h"
#include <SFML/Graphics/RenderTexture.hpp>

namespace GB
{
	class SFMLRenderTexture : public RenderTexture
	{
	public:
		SFMLRenderTexture(uint32_t width, uint32_t height);
		~SFMLRenderTexture();

		virtual void Begin() override;
		virtual void AddTextureToDraw(Texture2D* pTexture) override;
		virtual void End() override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

		const sf::RenderTexture& GetSFRenderTexture();

	private:
		sf::RenderTexture m_RenderTexture;

		uint32_t m_Width;
		uint32_t m_Height;
	};
}