#include "gbpch.h"
#include "SFMLRendererAPI.h"
#include "SFMLTexture.h"

namespace GB
{
	SFMLRendererAPI::SFMLRendererAPI(sf::RenderWindow* pWindow) :
		m_pRenderWindow(pWindow)
	{}

	SFMLRendererAPI::~SFMLRendererAPI()
	{
	}

	void SFMLRendererAPI::Initialize()
	{

	}

	void SFMLRendererAPI::DrawTexture(Texture2D* pTexture)
	{
		GB_CHECK_PTR(pTexture, "pTexture is nullptr!");
		GB_CHECK_PTR(m_pRenderWindow, "m_pRenderWindow is nullptr!");
		GB_PTR(pSFMLTexture, static_cast<SFMLTexture*>(pTexture), "pTexture isn't an SFMLTexture!");
		
		m_pRenderWindow->draw(pSFMLTexture->GetSFMLSprite());
	}

	void SFMLRendererAPI::Deinitialize()
	{
		if (m_pRenderWindow)
		{
			m_pRenderWindow = nullptr;
		}
	}
}