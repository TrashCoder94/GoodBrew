#pragma once

#include "GBEngine/Objects/BaseObject.h"
#include <vector>

namespace GB
{
	class Object;

	class Level : public BaseObject
	{
		GB_REFLECT()

	public:
		Level();
		~Level();

		// BaseObject
		virtual void Initialize() final override;
		virtual void Begin() final override;
		virtual void Update(const float deltaTime) final override;
		void Render();
		virtual void End() final override;
		virtual void Deinitialize() final override;
#if GB_IMGUI_ENABLED
		// For custom editor properties
		virtual void ImGuiRender() final override;
#endif
		// ~BaseObject

		Object* SpawnObject();
		void AddObject(Object* pObject);
		void RemoveObject(Object* pObject);

		const std::vector<Object*>& GetObjects();
		const std::vector<Object*>& GetObjects() const;

	private:
		std::vector<Object*> m_pObjects;

		void ForEachValidObject(const std::function<void(Object&)>& function);
	};
}