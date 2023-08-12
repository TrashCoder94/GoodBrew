#include "GBEditorWidgetLogWindow.h"
#include <GBEngine/Core/Log.h>
#include <imgui.h>

namespace GB
{
	EditorWidgetLogWindow::EditorWidgetLogWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetLogWindow::~EditorWidgetLogWindow()
	{}

	void EditorWidgetLogWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Log");
		{
			if (ImGui::BeginPopupContextWindow(0, 1))
			{
				if (ImGui::MenuItem("Clear Log"))
				{
					Log::Clear();
				}

				ImGui::EndPopup();
			}

			const std::string& logAsString = Log::GetString();
			ImGui::TextUnformatted(logAsString.c_str());
		}
		ImGui::End();
#endif
	}
}