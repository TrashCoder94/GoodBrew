#include "GBEditorWidgetDetailsWindow.h"
#include "GBEditorLayer.h"
#include <GBEngine/Level/Level.h>
#include <GBEngine/Objects/Object.h>
#include <imgui.h>

namespace GB
{
	EditorWidgetDetailsWindow::EditorWidgetDetailsWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{
		m_ComponentClassesToHide.push_back("Component");
		m_ComponentClassesToHide.push_back("TransformComponent");
	}

	EditorWidgetDetailsWindow::~EditorWidgetDetailsWindow()
	{}

	void EditorWidgetDetailsWindow::Draw()
	{
		GB_CHECK_PTR(m_pEditorLayer, "Editor layer is nullptr, make sure a valid editor layer was passed in the constructor!");

#if GB_IMGUI_ENABLED
		ImGui::Begin("Details");
		{
			if (Object* pObject = m_pEditorLayer->GetSelectedObject())
			{
				ImGui::TextUnformatted(pObject->GetName().c_str());
				DrawComponents(pObject);
			}
		}
		ImGui::End();
#endif
	}

	void EditorWidgetDetailsWindow::DrawComponents(Object* pObject)
	{
#if GB_IMGUI_ENABLED
		// Add Component Button
		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 150.0f);

		GB::BeginButtonStyle();
		{
			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("AddComponent");
			}
		}
		GB::EndButtonStyle();

		// Components...
		if (ImGui::BeginPopup("AddComponent"))
		{
			// This will find anything named component in the class registry
			// You can add new components to the class registry by using the reflection macro: GB_REFLECT
			const GB::RegisteredClassMap& classMap = GB::ClassRegistry::Get().GetClassMap();
			for (const std::pair<std::string, GB::Constructor_T>& classData : classMap)
			{
				const std::string& className = classData.first;

				if (className.find("Component") != std::string::npos)
				{
					if (ShouldHideComponent(className))
					{
						continue;
					}
					
					if (ImGui::MenuItem(className.c_str()))
					{
						// Be mindful, this causes a "new" allocation, make sure an appropriate "delete" is called later
						// If the component is added to the object, then the object will automatically clean this up during Deinitialize().
						if (void* pConstructedComponent = GB::ClassRegistry::Get().Construct(className))
						{
							GB_PTR(pNewComponent, static_cast<Component*>(pConstructedComponent), "pConstructedComponent is somehow not a component");

							if (pObject->HasComponent(pNewComponent))
							{
								GB_CORE_LOG_WARN("Object '{0}' already has a {1} so this component won't be added", pObject->GetName().c_str(), className);
								
								// Since this object already has this component and there was a new allocation
								// Clean this up here since it won't be used any more
								delete pNewComponent;
								pNewComponent = nullptr;
							}
							else
							{
								pObject->AddComponent(pNewComponent);
							}
							ImGui::CloseCurrentPopup();
						}
					}
				}
			}

			ImGui::EndPopup();
		}

		ImGui::Separator();
#endif
	}

	bool EditorWidgetDetailsWindow::ShouldHideComponent(const std::string& componentClassName)
	{
		bool shouldHide = false;

		for (const std::string& componentClassNameToHide : m_ComponentClassesToHide)
		{
			if (componentClassNameToHide.find(componentClassName) != std::string::npos)
			{
				shouldHide = true;
				break;
			}
		}

		return shouldHide;
	}
}