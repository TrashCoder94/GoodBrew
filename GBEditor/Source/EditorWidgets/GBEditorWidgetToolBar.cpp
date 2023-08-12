#include "GBEditorWidgetToolBar.h"
#include <imgui.h>

namespace GB
{
	EditorWidgetToolBar::EditorWidgetToolBar(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetToolBar::~EditorWidgetToolBar()
	{}

	void EditorWidgetToolBar::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Toolbar");
		{

		}
		ImGui::End();
#endif
	}
}