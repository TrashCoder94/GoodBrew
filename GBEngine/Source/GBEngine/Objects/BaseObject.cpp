#include "gbpch.h"
#include "BaseObject.h"

namespace GB
{
	BaseObject::BaseObject() :
		m_pOwner(nullptr)
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

#if GB_IMGUI_ENABLED
	void BaseObject::ImGuiRender()
	{}
#endif

	void BaseObject::SetBaseObjectOwner(BaseObject* pOwner)
	{
		GB_CHECK_PTR(pOwner, "Cannot set owner to nullptr.");
		m_pOwner = pOwner;
	}

	BaseObject* BaseObject::GetBaseObjectOwner()
	{
		return m_pOwner;
	}

	const BaseObject* BaseObject::GetBaseObjectOwner() const
	{
		return m_pOwner;
	}
}