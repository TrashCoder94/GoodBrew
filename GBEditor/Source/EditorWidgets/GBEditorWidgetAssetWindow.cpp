#include "GBEditorWidgetAssetWindow.h"
#include <imgui.h>

namespace GB
{
	EditorWidgetAssetWindow::EditorWidgetAssetWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetAssetWindow::~EditorWidgetAssetWindow()
	{}

	void EditorWidgetAssetWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Assets");
		{

		}
		ImGui::End();
#endif
	}
}