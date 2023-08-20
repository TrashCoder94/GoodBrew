#include "gbpch.h"
#include "Component.h"
#include "GBEngine/Objects/Object.h"

namespace GB
{
	Component::Component() : BaseObject()
	{}

	Component::~Component()
	{}
	
	Object* Component::GetOwner()
	{
		return static_cast<Object*>(GetBaseObjectOwner());
	}
	
	const Object* Component::GetOwner() const
	{
		return static_cast<const Object*>(GetBaseObjectOwner());
	}
}