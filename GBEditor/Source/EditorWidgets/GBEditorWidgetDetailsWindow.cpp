#include "GBEditorWidgetDetailsWindow.h"
#include <imgui.h>

namespace GB
{
	EditorWidgetDetailsWindow::EditorWidgetDetailsWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetDetailsWindow::~EditorWidgetDetailsWindow()
	{}

	void EditorWidgetDetailsWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Details");
		{

		}
		ImGui::End();
#endif
	}
}