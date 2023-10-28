#include "gbpch.h"
#include "SFMLRenderTexture.h"
#include "SFMLTexture.h"

namespace GB
{
	SFMLRenderTexture::SFMLRenderTexture(uint32_t width, uint32_t height) :
		m_Width(width),
		m_Height(height)
	{
		GB_CORE_ASSERT((m_Width != 0 && m_Height != 0), "Make width and height a non 0 value");
		m_RenderTexture.create(m_Width, m_Height);
	}

	SFMLRenderTexture::~SFMLRenderTexture()
	{}

	void SFMLRenderTexture::Begin()
	{
		m_RenderTexture.clear();
	}

	void SFMLRenderTexture::AddTextureToDraw(Texture2D* pTexture)
	{
		GB_PTR(pSFMLTexture, static_cast<SFMLTexture*>(pTexture), "pTexture isn't an SFMLTexture");
		m_RenderTexture.draw(pSFMLTexture->GetSFMLSprite());
	}

	void SFMLRenderTexture::End()
	{
		m_RenderTexture.display();
	}

	uint32_t SFMLRenderTexture::GetWidth() const
	{
		return m_Width;
	}

	uint32_t SFMLRenderTexture::GetHeight() const
	{
		return m_Height;
	}

	const sf::RenderTexture& SFMLRenderTexture::GetSFRenderTexture()
	{
		return m_RenderTexture;
	}
}