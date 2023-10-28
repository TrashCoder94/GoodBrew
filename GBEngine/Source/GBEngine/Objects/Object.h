#pragma once

#include "BaseObject.h"
#include "GBEngine/Components/TransformComponent.h"

#include <string>
#include <vector>

namespace GB
{
	class Object : public BaseObject
	{
		GB_REFLECT()

	public:
		Object();
		~Object();

		// BaseObject
		virtual void Initialize() override;
		virtual void Begin() override;
		virtual void Update(const float deltaTime) override;
		virtual void End() override;
		virtual void Deinitialize() override;
#if GB_IMGUI_ENABLED
		// For custom editor properties
		virtual void ImGuiRender() override;
#endif
		// ~BaseObject

		const std::string& GetName();
		const std::string& GetName() const;

		TransformComponent* GetTransformComponent();
		const TransformComponent* GetTransformComponent() const;

		bool HasComponent(Component* pComponent) const;

		template<class ComponentClass>
		bool HasComponent()
		{
			GB_PROFILE_FUNCTION();

			bool bHasComponent = false;

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			ForEachValidComponent([&](Component& component)
			{
				if (component.IsA<ComponentClass>())
				{
					bHasComponent = true;
					return;
				}
			});

			return bHasComponent;
		}

		void AddComponent(Component* pComponent);

		template<class ComponentClass, typename... Args>
		ComponentClass* AddComponent(Args&&... args)
		{
			GB_PROFILE_FUNCTION();

			ComponentClass* pResult{ nullptr };

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			if (HasComponent<ComponentClass>())
			{
				return pResult;
			}

			ComponentClass* pNewComponent{ new ComponentClass(std::forward<Args>(args)...) };
			if (!pNewComponent)
				return pResult;

			pNewComponent->SetBaseObjectOwner(this);
			pNewComponent->Initialize();
			// TODO: See if you need to call Begin() here as well?
			pResult = pNewComponent;
			m_pComponents.push_back(pResult);

			return pResult;
		}

		template<class ComponentClass>
		ComponentClass* GetComponent() const
		{
			GB_PROFILE_FUNCTION();

			ComponentClass* pComponentResult = nullptr;

			const bool bIsValidComponentClass = GB_DOES_CLASS_INHERIT_FROM(Component, ComponentClass);
			GB_CORE_ASSERT(bIsValidComponentClass, "Class passed in template parameter doesn't inherit from Component!");

			ForEachValidComponent([&](Component& component)
			{
				if (component.IsA<ComponentClass>())
				{
					pComponentResult = static_cast<ComponentClass*>(&component);
					return;
				}
			});

			return pComponentResult;
		}

	private:
		static int s_ObjectID;

		std::vector<Component*> m_pComponents;
		TransformComponent* m_pTransformComponent;
		std::string m_Name; 

		void ForEachValidComponent(const std::function<void(Component&)>& function) const;
	};
}