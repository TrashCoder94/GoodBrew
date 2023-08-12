#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetLevelHierarchyWindow : public EditorWidget
	{
	public:
		EditorWidgetLevelHierarchyWindow(EditorLayer* pEditorLayer);
		~EditorWidgetLevelHierarchyWindow();
		virtual void Draw() override;
	};
}