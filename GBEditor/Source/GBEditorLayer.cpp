#include "GBEditorLayer.h"

#include <GBEngine/Core/Application.h>
#include <GBEngine/Level/Level.h>
#include <imgui.h>
#include <vector>

#include "EditorWidgets/GBEditorWidgetAssetWindow.h"
#include "EditorWidgets/GBEditorWidgetDetailsWindow.h"
#include "EditorWidgets/GBEditorWidgetLevelHierarchyWindow.h"
#include "EditorWidgets/GBEditorWidgetLogWindow.h"
#include "EditorWidgets/GBEditorWidgetMenuBar.h"
#include "EditorWidgets/GBEditorWidgetToolBar.h"
#include "EditorWidgets/GBEditorWidgetViewportWindow.h"

namespace GB
{
	EditorLayer::EditorLayer() : GB::Layer("GBEditorLayer"),
		m_pEditorWidgets(),
		m_pEditorLevel(nullptr),
		m_pSelectedObject(nullptr),
		m_EditorLevelState(EEditorLevelState::Edit)
	{}

	EditorLayer::~EditorLayer()
	{}

	void EditorLayer::OnAttach()
	{
		m_pEditorLevel = CreateSharedPtr<Level>();

		constexpr size_t kNumberOfEditorWidgets = 7;
		m_pEditorWidgets.reserve(kNumberOfEditorWidgets);
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetMenuBar>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetToolBar>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetLevelHierarchyWindow>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetDetailsWindow>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetAssetWindow>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetLogWindow>(this));
		m_pEditorWidgets.push_back(CreateUniquePtr<EditorWidgetViewportWindow>(this));
	}

	void EditorLayer::OnDetach()
	{
		if (m_pEditorLevel)
		{
			m_pEditorLevel->End();
			m_pEditorLevel->Deinitialize();
			m_pEditorLevel.reset();
		}

		// TODO: Call any editor widget clean up functions here...
		m_pEditorWidgets.clear();
	}

	void EditorLayer::OnUpdate(const float deltaTime)
	{
		switch (m_EditorLevelState)
		{
			case EEditorLevelState::Edit:
			{
				if (m_pEditorLevel)
				{
					m_pEditorLevel->Update(deltaTime);
				}
				break;
			}
			case EEditorLevelState::Play:
			{
				//m_pRuntimeLevel->Update(deltaTime);
				break;
			}
			case EEditorLevelState::Pause:
			{
				break;
			}
		}
	}

	void EditorLayer::OnRender()
	{
		//switch (m_EditorLevelState)
		//{
		//	case EEditorLevelState::Edit:
		//	{
		//		if (m_pEditorLevel)
		//		{
		//			m_pEditorLevel->Render();
		//		}
		//		break;
		//	}
		//	case EEditorLevelState::Play:
		//	{
		//		//m_pRuntimeLevel->Render(deltaTime);
		//		break;
		//	}
		//	case EEditorLevelState::Pause:
		//	{
		//		break;
		//	}
		//}
	}

#if GB_IMGUI_ENABLED
	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static constexpr bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		
		ImGui::Begin("GB Dockspace", &dockspaceOpen, window_flags);
		{
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& style = ImGui::GetStyle();
			float minWindowSizeX = style.WindowMinSize.x;
			style.WindowMinSize.x = 370.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("GBDockspace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			style.WindowMinSize.x = minWindowSizeX;

			ForEachValidEditorWidget([&](EditorWidget& widget)
			{
				widget.Draw();
			});
		}
		ImGui::End();
	}
#endif

	void EditorLayer::SetSelectedObject(Object* pObject)
	{
		if (m_pSelectedObject)
		{
			m_pSelectedObject = nullptr;
		}

		m_pSelectedObject = pObject;
	}

	const SharedPtr<Level>& EditorLayer::GetEditorLevel()
	{
		return m_pEditorLevel;
	}

	const SharedPtr<Level>& EditorLayer::GetEditorLevel() const
	{
		return m_pEditorLevel;
	}

	const EEditorLevelState EditorLayer::GetEditorLevelState()
	{
		return m_EditorLevelState;
	}

	const EEditorLevelState EditorLayer::GetEditorLevelState() const
	{
		return m_EditorLevelState;
	}

	Object* EditorLayer::GetSelectedObject()
	{
		return m_pSelectedObject;
	}

	Object* EditorLayer::GetSelectedObject() const
	{
		return m_pSelectedObject;
	}

	void EditorLayer::ForEachValidEditorWidget(const std::function<void(EditorWidget&)>& function)
	{
		for (const UniquePtr<EditorWidget>& editorWidget : m_pEditorWidgets)
		{
			if (editorWidget.get())
			{
				function(*editorWidget.get());
			}
		}
	}
}