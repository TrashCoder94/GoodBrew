#include "gbpch.h"
#include "Level.h"
#include "GBEngine/Objects/Object.h"
#include "GBEngine/Components/SpriteComponent.h"
#include "GBEngine/Renderer/Renderer.h"

namespace GB
{
	Level::Level() : BaseObject(),
		m_pObjects()
	{}

	Level::~Level()
	{}

	void Level::Initialize()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Initialize();

		ForEachValidObject([&](Object& object) 
		{
			object.Initialize();
		});
	}

	void Level::Begin()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Begin();

		ForEachValidObject([&](Object& object)
		{
			object.Begin();
		});
	}

	void Level::Update(const float deltaTime)
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Update(deltaTime);

		ForEachValidObject([&](Object& object)
		{
			object.Update(deltaTime);
		});
	}

	void Level::Render()
	{
		GB_PROFILE_FUNCTION();

		Renderer::Begin();
		{
			ForEachValidObject([&](Object& object)
			{
				GB_PTR_SAFE(pSpriteComponent, object.GetComponent<SpriteComponent>());
				Renderer::DrawTexture(pSpriteComponent->GetTexture());
			});
		}
		Renderer::End();
	}

	void Level::End()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::End();

		ForEachValidObject([&](Object& object)
		{
			object.End();
		});
	}

	void Level::Deinitialize()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::Deinitialize();

		for (Object* pObject : m_pObjects)
		{
			if (pObject)
			{
				pObject->Deinitialize();

				delete pObject;
				pObject = nullptr;
			}
		}

		m_pObjects.clear();
	}

#if GB_IMGUI_ENABLED
	void Level::ImGuiRender()
	{
		GB_PROFILE_FUNCTION();

		BaseObject::ImGuiRender();

		ForEachValidObject([&](Object& object)
		{
			object.ImGuiRender();
		});
	}
#endif

	Object* Level::SpawnObject()
	{
		Object* pObject = new Object();

		// Initialize this object now
		// TODO: Check if this should call Begin as well
		// Not really clear when setting up editor functionality.
		pObject->Initialize();

		// Add this new object to the list of level objects
		m_pObjects.push_back(pObject);
		return pObject;
	}

	void Level::AddObject(Object* pObject)
	{
		GB_CHECK_PTR(pObject, "Cannot add a nullptr object to the level!");
		m_pObjects.push_back(pObject);
	}

	void Level::RemoveObject(Object* pObject)
	{
		if (pObject)
		{
			pObject->End();
			pObject->Deinitialize();
		}

		m_pObjects.erase(std::remove_if(begin(m_pObjects), end(m_pObjects), [&](Object* pLevelObject) 
		{
			return pLevelObject == pObject; 
		}), end(m_pObjects));

		// Free up the memory since objects are newly allocated
		delete pObject;
		pObject = nullptr;
	}

	const std::vector<Object*>& Level::GetObjects()
	{
		return m_pObjects;
	}

	const std::vector<Object*>& Level::GetObjects() const
	{
		return m_pObjects;
	}

	void Level::ForEachValidObject(const std::function<void(Object&)>& function)
	{
		for (Object* pObject : m_pObjects)
		{
			if (!pObject)
				continue;

			function(*pObject);
		}
	}
}