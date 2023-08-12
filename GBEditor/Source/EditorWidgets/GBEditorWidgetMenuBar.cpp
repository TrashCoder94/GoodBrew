#include "GBEditorWidgetMenuBar.h"
#include <imgui.h>
#include <GBEngine/Core/Application.h>

namespace GB
{
	EditorWidgetMenuBar::EditorWidgetMenuBar(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetMenuBar::~EditorWidgetMenuBar()
	{}

	void EditorWidgetMenuBar::Draw()
	{
#if GB_IMGUI_ENABLED
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					//NewScene();
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					//OpenScene();
				}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
				{
					//SaveSceneAs();
				}

				if (ImGui::MenuItem("Exit"))
				{
					GB::Application::Get().Close();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
#endif
	}
}