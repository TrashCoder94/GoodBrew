#include "gbpch.h"
#include "SpriteComponent.h"

#include "GBEngine/Objects/Object.h"
#include "GBEngine/Renderer/Platforms/SFML/SFMLTexture.h"
#include "TransformComponent.h"

#include <SFML/Graphics/Sprite.hpp>

namespace GB
{
	SpriteComponent::SpriteComponent() : Component(),
		m_pTexture(Texture2D::Create("Assets/Textures/T_WhiteSquare.png")),
		m_pTransformComponent(nullptr)
	{}

	SpriteComponent::~SpriteComponent()
	{}

	void SpriteComponent::Initialize()
	{
		m_pTransformComponent = GetOwner()->GetTransformComponent();
	}

	void SpriteComponent::Update(const float deltaTime)
	{
		GB_CORE_ASSERT(m_pTexture.get(), "Invalid Texture2D, make sure Texture2D::Create has been called first!");
		GB_CORE_ASSERT(m_pTransformComponent, "TransformComponent from Owner is nullptr!");	
		
		// Temporary, not sure where to put this but need to update the position etc.
		GB_PTR(pSFMLTexture, static_cast<SFMLTexture*>(m_pTexture.get()), "Texture2D isn't an SFMLTexture!");
		sf::Sprite& sfmlSprite = pSFMLTexture->GetSFMLSprite();
		sfmlSprite.setPosition(m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y);
		sfmlSprite.setRotation(m_pTransformComponent->GetRotation().z);
		sfmlSprite.setScale(m_pTransformComponent->GetScale().x, m_pTransformComponent->GetScale().y);
	}

	Texture2D* SpriteComponent::GetTexture()
	{
		return m_pTexture.get();
	}
}