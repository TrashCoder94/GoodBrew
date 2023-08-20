#pragma once

#include "GBEngine/Objects/BaseObject.h"

namespace GB
{
	class Object;

	class Component : public BaseObject
	{
	public:
		Component();
		~Component();

		Object* GetOwner();
		const Object* GetOwner() const;
	};
}