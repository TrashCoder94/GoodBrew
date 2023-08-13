#pragma once

#include <functional>

#include <GBEngine/Core/Base.h>
#include <GBEngine/Core/Layer.h>
#include "GBEditorLevelState.h"

namespace GB
{
	class EditorWidget;
	class Level;
	class Object;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const float deltaTime) override;
		virtual void OnRender() override;
#if GB_IMGUI_ENABLED
		virtual void OnImGuiRender() override;
#endif
		void SetSelectedObject(Object* pObject);

		const SharedPtr<Level>& GetEditorLevel();
		const SharedPtr<Level>& GetEditorLevel() const;

		const EEditorLevelState GetEditorLevelState();
		const EEditorLevelState GetEditorLevelState() const;
	
		Object* GetSelectedObject();
		Object* GetSelectedObject() const;

	private:
		void ForEachValidEditorWidget(const std::function<void(EditorWidget&)>& function);

		std::vector<UniquePtr<EditorWidget>> m_pEditorWidgets;
		SharedPtr<Level> m_pEditorLevel;
		Object* m_pSelectedObject;
		EEditorLevelState m_EditorLevelState;
	};
}