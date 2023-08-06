#include "gbpch.h"

#if GB_IMGUI_ENABLED

#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GBEngine/Core/Application.h"
#include "GBEngine/Core/Window.h"

namespace GB
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"),
		m_pWindow(nullptr)
	{}

	ImGuiLayer::~ImGuiLayer()
	{}

	void ImGuiLayer::OnAttach()
	{
		GB_PROFILE_FUNCTION();

		GB_CORE_LOG_INFO("ImGui Layer is initializing now...");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColours();

		Application& app = Application::Get();
		m_pWindow = static_cast<sf::RenderWindow*>(app.GetWindow().GetNativeWindow());
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");

		const bool kImguiSFMLInitialized = ImGui::SFML::Init(*m_pWindow);
		GB_ASSERT(kImguiSFMLInitialized, "ImGui SFML failed to initialize!");
	}

	void ImGuiLayer::Update(const sf::Time& sfDeltaTime)
	{
		GB_PROFILE_FUNCTION();

		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");
		ImGui::SFML::Update(*m_pWindow, sfDeltaTime);
	}

	void ImGuiLayer::OnDetach()
	{
		GB_PROFILE_FUNCTION();

		ImGui::SFML::Shutdown();

		GB_CORE_LOG_INFO("ImGui Layer is shutting down now...");
	}

	void ImGuiLayer::Begin()
	{
		GB_PROFILE_FUNCTION();

		// No need to do this any longer since ImGuiLayer::Update calls ImGui::SFML::Update which calls ImGui::NewFrame at the end of the update function...
		//ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		GB_PROFILE_FUNCTION();

		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		
		ImGui::SFML::Render(*m_pWindow);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void ImGuiLayer::SetDarkThemeColours()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		style.Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		style.Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		style.Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		style.Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}

#endif