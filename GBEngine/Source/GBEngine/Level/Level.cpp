#include "gbpch.h"
#include "Level.h"
#include "GBEngine/Objects/Object.h"

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

		ForEachValidObject([&](Object& object)
		{
			object.Deinitialize();
		});

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