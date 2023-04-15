#include "gbpch.h"
#include "Object.h"
#include "GBEngine/Components/Component.h"

namespace GB
{
	Object::Object() : BaseObject(),
		m_pComponents()
	{}

	Object::~Object()
	{}

	bool Object::HasComponent(Component* pComponentToFind) const
	{
		GB_CHECK_PTR(pComponentToFind, "Trying to find a component that's a nullptr!");

		bool bHasComponent = false;

		auto func = [&](Component* pComponent)
		{
			// TODO: Test this comparison works...
			if (pComponent == pComponentToFind)
			{
				bHasComponent = true;
				return;
			}
		};
		IterateComponents(func);

		return bHasComponent;
	}

	void Object::AddComponent(Component* pComponent)
	{
		GB_CHECK_PTR(pComponent, "Trying to add a component that's a nullptr!");

		if (HasComponent(pComponent))
		{
			return;
		}

		pComponent->SetOwner(this);
		pComponent->Begin();
		m_pComponents.push_back(pComponent);
	}

	void Object::IterateComponents(const std::function<void(Component*)>& function) const
	{
		for (Component* pComponent : m_pComponents)
		{
			if (!pComponent)
				continue;

			function(pComponent);
		}
	}
}