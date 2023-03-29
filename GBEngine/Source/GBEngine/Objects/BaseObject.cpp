#include "gbpch.h"
#include "BaseObject.h"

namespace GB
{
	BaseObject::BaseObject() :
		m_pOwner(nullptr)
	{}

	BaseObject::~BaseObject()
	{}

	void BaseObject::Initialize()
	{}

	void BaseObject::Begin()
	{}

	void BaseObject::Update(const float deltaTime)
	{}

	void BaseObject::End()
	{}

	void BaseObject::Deinitialize()
	{}

	void BaseObject::ImGuiRender()
	{}

	void BaseObject::SetOwner(BaseObject* pOwner)
	{
		GB_CHECK_PTR(pOwner, "Cannot set owner to nullptr.");
		m_pOwner = pOwner;
	}

	BaseObject* BaseObject::GetOwner()
	{
		return m_pOwner;
	}

	const BaseObject* BaseObject::GetOwner() const
	{
		return m_pOwner;
	}
}