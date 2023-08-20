#include "gbpch.h"
#include "TransformComponent.h"

namespace GB
{
	TransformComponent::TransformComponent() : Component(),
		m_Position(0.0f, 0.0f, 0.0f),
		m_Rotation(0.0f, 0.0f, 0.0f),
		m_Scale(1.0f, 1.0f, 1.0f)
	{}

	TransformComponent::~TransformComponent()
	{}

	void TransformComponent::SetPosition(const float3& newPosition)
	{
		m_Position = newPosition;
	}

	void TransformComponent::SetRotation(const float3& newRotation)
	{
		m_Rotation = newRotation;
	}

	void TransformComponent::SetScale(const float3& newScale)
	{
		m_Scale = newScale;
	}

	const float3& TransformComponent::GetPosition()
	{
		return m_Position;
	}

	const float3& TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	const float3& TransformComponent::GetRotation()
	{
		return m_Rotation;
	}

	const float3& TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	const float3& TransformComponent::GetScale()
	{
		return m_Scale;
	}

	const float3& TransformComponent::GetScale() const
	{
		return m_Scale;
	}
}