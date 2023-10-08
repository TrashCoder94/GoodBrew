#pragma once

#include "GBEngine/Objects/BaseObject.h"

namespace GB
{
	class Object;

	class Component : public BaseObject
	{
		GB_REFLECT()

	public:
		Component();
		~Component();

		Object* GetOwner();
		const Object* GetOwner() const;
	};
}