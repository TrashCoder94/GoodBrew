#include "GBEditorWidgetViewportWindow.h"
#include <imgui.h>

namespace GB
{
	EditorWidgetViewportWindow::EditorWidgetViewportWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetViewportWindow::~EditorWidgetViewportWindow()
	{}

	void EditorWidgetViewportWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Viewport");
		{

		}
		ImGui::End();
#endif
	}
}