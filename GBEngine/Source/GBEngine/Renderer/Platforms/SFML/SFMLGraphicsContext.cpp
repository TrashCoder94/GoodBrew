#include "gbpch.h"
#include "SFMLGraphicsContext.h"

namespace GB
{
	SFMLGraphicsContext::SFMLGraphicsContext(sf::RenderWindow* pWindow) : 
		m_pWindow(pWindow)
	{}

	SFMLGraphicsContext::~SFMLGraphicsContext()
	{}

	void SFMLGraphicsContext::Initialize()
	{

	}

	void SFMLGraphicsContext::Deinitialize()
	{
		if (m_pWindow)
		{
			m_pWindow = nullptr;
		}
	}
}