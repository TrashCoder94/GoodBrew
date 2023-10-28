#include "GBEditorStyle.h"
#include <imgui.h>

namespace GB
{
	void BeginButtonStyle()
	{
		const ImVec4& kAddComponentButtonColourIdle = ImVec4{ 0.0f, 0.0f, 0.5f, 1.0f };
		const ImVec4& kAddComponentButtonColourHover = ImVec4{ 0.0f, 0.0f, 0.75f, 1.0f };

		ImGui::PushStyleColor(ImGuiCol_Button, kAddComponentButtonColourIdle);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kAddComponentButtonColourHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kAddComponentButtonColourHover);
	}

	void EndButtonStyle()
	{
		ImGui::PopStyleColor(3);
	}
}