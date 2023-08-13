#include "gbpch.h"
#include "Object.h"

namespace GB
{
	int Object::s_ObjectID = 0;

	Object::Object() : BaseObject(),
		m_pComponents(),
		m_Name("Object" + std::to_string(++s_ObjectID))
	{}

	Object::~Object()
	{}

	void Object::Initialize()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Initialize();

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

		ForEachValidComponent([&](Component& component)
		{
			component.Deinitialize();
		});

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

	bool Object::HasComponent(Component* pComponentToFind) const
	{
		GB_PROFILE_FUNCTION();

		GB_CHECK_PTR(pComponentToFind, "Trying to find a component that's a nullptr!");

		bool bHasComponent = false;

		ForEachValidComponent([&](Component& component)
		{
			if (&component == pComponentToFind)
			{
				bHasComponent = true;
				return;
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

		pComponent->SetOwner(this);
		pComponent->Initialize();
		pComponent->Begin();
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