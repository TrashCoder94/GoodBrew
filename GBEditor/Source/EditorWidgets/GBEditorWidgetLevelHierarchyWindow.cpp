#include "GBEditorWidgetLevelHierarchyWindow.h"

#include "GBEditorLayer.h"
#include "GBEditorLevelState.h"
#include <GBEngine/Level/Level.h>
#include <GBEngine/Objects/Object.h>
#include <imgui.h>

namespace GB
{
	EditorWidgetLevelHierarchyWindow::EditorWidgetLevelHierarchyWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetLevelHierarchyWindow::~EditorWidgetLevelHierarchyWindow()
	{}

	void EditorWidgetLevelHierarchyWindow::Draw()
	{
		GB_CHECK_PTR(m_pEditorLayer, "Editor layer is nullptr, make sure a valid editor layer was passed in the constructor!");

#if GB_IMGUI_ENABLED
		ImGui::Begin("Level Hierarchy");
		{
			switch (m_pEditorLayer->GetEditorLevelState())
			{
				case EEditorLevelState::Edit:
				{
					GB::BeginButtonStyle();
					{
						if (ImGui::Button("Add Object"))
						{
							if (Object* pObject = m_pEditorLayer->GetEditorLevel()->SpawnObject())
							{
								m_pEditorLayer->SetSelectedObject(pObject);
							}
						}
					}
					GB::EndButtonStyle();

					if (ImGui::BeginPopupContextWindow(0, 1))
					{
						if (ImGui::MenuItem("Delete Object"))
						{
							RemoveSelectedObject();
						}

						ImGui::EndPopup();
					}

					if (ImGui::IsKeyPressed(ImGuiKey_Delete))
					{
						RemoveSelectedObject();
					}

					for (Object* pObject : m_pEditorLayer->GetEditorLevel()->GetObjects())
					{
						if (pObject)
						{
							DrawObject(pObject);
						}
					}
					break;
				}
				case EEditorLevelState::Play:
				{
					break;
				}
				case EEditorLevelState::Pause:
				{
					break;
				}
			}
		}
		ImGui::End();
#endif
	}

	void EditorWidgetLevelHierarchyWindow::DrawObject(Object* pObject)
	{
		GB_CHECK_PTR(m_pEditorLayer, "Editor layer is nullptr, make sure a valid editor layer was passed in the constructor!");

#if GB_IMGUI_ENABLED
		const std::string& name = pObject->GetName();

		ImGuiTreeNodeFlags flags = ((m_pEditorLayer->GetSelectedObject() == pObject) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		const bool opened = ImGui::TreeNodeEx(static_cast<void*>(pObject), flags, "%s", name.c_str());

		if (ImGui::IsItemClicked())
		{
			m_pEditorLayer->SetSelectedObject(pObject);
		}

		if (opened)
		{
			ImGui::TreePop();
		}
#endif
	}

	void EditorWidgetLevelHierarchyWindow::RemoveSelectedObject()
	{
		if (m_pEditorLayer->GetSelectedObject())
		{
			m_pEditorLayer->GetEditorLevel()->RemoveObject(m_pEditorLayer->GetSelectedObject());
			m_pEditorLayer->SetSelectedObject(nullptr);
		}
	}
}