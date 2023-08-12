#include "GBEditorWidgetLevelHierarchyWindow.h"
#include <imgui.h>

namespace GB
{
	EditorWidgetLevelHierarchyWindow::EditorWidgetLevelHierarchyWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetLevelHierarchyWindow::~EditorWidgetLevelHierarchyWindow()
	{}

	void EditorWidgetLevelHierarchyWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Level Hierarchy");
		{

		}
		ImGui::End();
#endif
	}
}