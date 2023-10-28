#include "gbpch.h"
#include "Object.h"

namespace GB
{
	int Object::s_ObjectID = 0;

	Object::Object() : BaseObject(),
		m_pComponents(),
		m_pTransformComponent(nullptr),
		m_Name("Object" + std::to_string(++s_ObjectID))
	{}

	Object::~Object()
	{}

	void Object::Initialize()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Initialize();

		// Objects should _always_ have a transform component
		// These can be moved around in editor/runtime
		m_pTransformComponent = AddComponent<TransformComponent>();

		ForEachValidComponent([&](Component& component)
		{
			component.Initialize();
		});
	}

	void Object::Begin()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Begin();

		ForEachValidComponent([&](Component& component)
		{
			component.Begin();
		});
	}

	void Object::Update(const float deltaTime)
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Update(deltaTime);

		ForEachValidComponent([&](Component& component)
		{
			component.Update(deltaTime);
		});
	}

	void Object::End()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::End();

		ForEachValidComponent([&](Component& component)
		{
			component.End();
		});
	}

	void Object::Deinitialize()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Deinitialize();
		
		// No need to clean up this pointer since it will be cleaned up just below here
		m_pTransformComponent = nullptr;

		for (Component* pComponent : m_pComponents)
		{
			if (pComponent)
			{
				pComponent->Deinitialize();
				delete pComponent;
				pComponent = nullptr;
			}
		}

		m_pComponents.clear();
	}

#if GB_IMGUI_ENABLED
	void Object::ImGuiRender()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::ImGuiRender();

		ForEachValidComponent([&](Component& component)
		{
			component.ImGuiRender();
		});
	}
#endif

	const std::string& Object::GetName()
	{
		return m_Name;
	}

	const std::string& Object::GetName() const
	{
		return m_Name;
	}

	TransformComponent* Object::GetTransformComponent()
	{
		return m_pTransformComponent;
	}

	const TransformComponent* Object::GetTransformComponent() const
	{
		return m_pTransformComponent;
	}

	bool Object::HasComponent(Component* pComponentToFind) const
	{
		GB_PROFILE_FUNCTION();

		GB_CHECK_PTR(pComponentToFind, "Trying to find a component that's a nullptr!");

		bool bHasComponent = false;

		ForEachValidComponent([&](Component& component)
		{
			// Only have to do these checks if we haven't found the component yet
			if (!bHasComponent)
			{
				const reflect::TypeDescriptor_Struct& componentReflectedData = component.GetTypeDescription();
				const reflect::TypeDescriptor_Struct& componentToFindReflectedData = pComponentToFind->GetTypeDescription();

				if (componentReflectedData.getFullName() == componentToFindReflectedData.getFullName())
				{
					bHasComponent = true;
				}
			}
		});

		return bHasComponent;
	}

	void Object::AddComponent(Component* pComponent)
	{
		GB_PROFILE_FUNCTION();

		GB_CHECK_PTR(pComponent, "Trying to add a component that's a nullptr!");

		if (HasComponent(pComponent))
		{
			return;
		}

		pComponent->SetBaseObjectOwner(this);
		pComponent->Initialize();
		// TODO: See if you need to call Begin() here?
		m_pComponents.push_back(pComponent);
	}

	void Object::ForEachValidComponent(const std::function<void(Component&)>& function) const
	{
		for (Component* pComponent : m_pComponents)
		{
			if (!pComponent)
				continue;

			function(*pComponent);
		}
	}
}