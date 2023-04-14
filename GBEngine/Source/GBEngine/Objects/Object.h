#pragma once

#include "BaseObject.h"
#include "GBEngine/Components/Component.h"

#include <vector>

namespace GB
{
	class Object : public BaseObject
	{
	public:
		Object();
		~Object();

		bool HasComponent(Component* pComponent) const;

		template<class ComponentClass>
		bool HasComponent()
		{
			bool bHasComponent = false;

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			for (Component* pComponent : m_pComponents)
			{
				if (!pComponent)
					continue;

				if (pComponent->IsA<ComponentClass>())
				{
					bHasComponent = true;
					break;
				}
			}

			return bHasComponent;
		}

		void AddComponent(Component* pComponent);

		template<class ComponentClass, typename... Args>
		ComponentClass* AddComponent(Args&&... args)
		{
			ComponentClass* pResult{ nullptr };

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			if (HasComponent<ComponentClass>())
			{
				return pResult;
			}

			ComponentClass* pNewComponent{ new ComponentClass(std::forward<Args>(args)...) };
			pNewComponent->SetOwner(this);
			pNewComponent->Start();
			if (!pNewComponent)
				return pResult;

			pResult = pNewComponent;
			m_pComponents.push_back(pResult);

			return pResult;
		}

		template<class ComponentClass>
		ComponentClass* GetComponent() const
		{
			ComponentClass* pComponentResult = nullptr;

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			for (Component* pComponent : m_pComponents)
			{
				if (!pComponent)
					continue;

				if (pComponent->IsA<ComponentClass>())
				{
					pComponentResult = static_cast<ComponentClass*>(pComponent);
					break;
				}
			}

			return pComponentResult;
		}

		void IterateComponents(const std::function<void(Component*)>& function) const;

	private:
		std::vector<Component*> m_pComponents;
	};
}