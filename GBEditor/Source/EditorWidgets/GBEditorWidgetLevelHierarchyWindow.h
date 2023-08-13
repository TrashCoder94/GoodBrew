#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class Object;

	class EditorWidgetLevelHierarchyWindow : public EditorWidget
	{
	public:
		EditorWidgetLevelHierarchyWindow(EditorLayer* pEditorLayer);
		~EditorWidgetLevelHierarchyWindow();
		virtual void Draw() override;

	private:
		void DrawObject(Object* pObject);

		void RemoveSelectedObject();
	};
}