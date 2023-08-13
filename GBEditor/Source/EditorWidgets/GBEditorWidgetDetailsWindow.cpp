#include "GBEditorWidgetDetailsWindow.h"
#include "GBEditorLayer.h"
#include <GBEngine/Level/Level.h>
#include <GBEngine/Objects/Object.h>
#include <imgui.h>

namespace GB
{
	EditorWidgetDetailsWindow::EditorWidgetDetailsWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetDetailsWindow::~EditorWidgetDetailsWindow()
	{}

	void EditorWidgetDetailsWindow::Draw()
	{
		GB_CHECK_PTR(m_pEditorLayer, "Editor layer is nullptr, make sure a valid editor layer was passed in the constructor!");

#if GB_IMGUI_ENABLED
		ImGui::Begin("Details");
		{
			if (const Object* pObject = m_pEditorLayer->GetSelectedObject())
			{
				ImGui::TextUnformatted(pObject->GetName().c_str());
			}
		}
		ImGui::End();
#endif
	}
}