#include "GBEditorLayer.h"
#include <imgui.h>
#include <GBEngine/Core/Application.h>

namespace GB
{
	GBEditorLayer::GBEditorLayer() : GB::Layer("GBLauncherLayer"),
		m_EditorLevelState(EGBEditorLevelState::Edit)
	{
	}

	GBEditorLayer::~GBEditorLayer()
	{
	}

#if GB_IMGUI_ENABLED
	void GBEditorLayer::OnImGuiRender()
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

			DrawMenuBar();
			DrawToolBar();
			DrawViewportWindow();
			DrawLevelHierarchyWindow();
			DrawAssetWindow();
			DrawLogWindow();
			DrawDetailsWindow();
		}
		ImGui::End();
	}

	void GBEditorLayer::DrawMenuBar()
	{
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
	}
	
	void GBEditorLayer::DrawToolBar()
	{
		ImGui::Begin("Toolbar");
		{

		}
		ImGui::End();
	}

	void GBEditorLayer::DrawViewportWindow()
	{
		ImGui::Begin("Viewport");
		{

		}
		ImGui::End();
	}
	
	void GBEditorLayer::DrawLevelHierarchyWindow()
	{
		ImGui::Begin("LeveHierarchy");
		{

		}
		ImGui::End();
	}

	void GBEditorLayer::DrawAssetWindow()
	{
		ImGui::Begin("Assets");
		{

		}
		ImGui::End();
	}
	
	void GBEditorLayer::DrawLogWindow()
	{
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

			ImGui::Text(Log::GetString().c_str());
		}
		ImGui::End();
	}
	
	void GBEditorLayer::DrawDetailsWindow()
	{
		ImGui::Begin("Details");
		{

		}
		ImGui::End();
	}
#endif
}