#pragma once

#include "Component.h"
#include "GBEngine/Renderer/Texture.h"

namespace GB
{
	class TransformComponent;

	class SpriteComponent : public Component
	{
		GB_REFLECT()

	public:
		SpriteComponent();
		~SpriteComponent();

		virtual void Initialize() override;
		virtual void Update(const float deltaTime) override;

		Texture2D* GetTexture();

	private:
		GBVARIABLE(Edit)
		SharedPtr<Texture2D> m_pTexture;

		TransformComponent* m_pTransformComponent;
	};
}