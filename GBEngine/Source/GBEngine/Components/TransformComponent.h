#pragma once

#include "Component.h"
#include <linalg.h>

using namespace linalg::aliases;

namespace GB
{
	class TransformComponent : public Component
	{
		GB_REFLECT()

	public:
		TransformComponent();
		~TransformComponent();

		void SetPosition(const float3& newPosition);
		void SetRotation(const float3& newRotation);
		void SetScale(const float3& newScale);

		const float3& GetPosition();
		const float3& GetPosition() const;
		const float3& GetRotation();
		const float3& GetRotation() const;
		const float3& GetScale();
		const float3& GetScale() const;

	private:
		GBVARIABLE(Edit)
		float3 m_Position;
		GBVARIABLE(Edit)
		float3 m_Rotation;
		GBVARIABLE(Edit)
		float3 m_Scale;
	};
}