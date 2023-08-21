#include "gbpch.h"

#if GB_IMGUI_ENABLED

#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GBEngine/Core/Application.h"
#include "GBEngine/Core/Window.h"

// TEMP
#if defined(GB_PLATFORM_WINDOWS)
#include <direct.h>
#elif defined(GB_PLATFORM_LINUX)
#include <unistd.h>
#endif
#include <stdio.h>
#include <limits.h>

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

		Application& app = Application::Get();
		m_pWindow = static_cast<sf::RenderWindow*>(app.GetWindow().GetNativeWindow());
		GB_ASSERT(m_pWindow, "SFML Window hasn't been initialized yet! Make sure SFMLWindow::Init has been called first");

		const bool kImguiSFMLInitialized = ImGui::SFML::Init(*m_pWindow);
		GB_ASSERT(kImguiSFMLInitialized, "ImGui SFML failed to initialize!");

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		// TEMP
		constexpr size_t kPathMax = 1024;
		char cwd[kPathMax];
#ifdef GB_PLATFORM_WINDOWS
		if (_getcwd(cwd, sizeof(cwd)) != NULL) 
#elif defined(GB_PLATFORM_LINUX)
		if (getcwd(cwd, sizeof(cwd)) != NULL)
#endif
		{
			printf("Current working dir: %s\n", cwd);
		}
		else
		{
			perror("getcwd() error");
		}

		constexpr float kFontSize = 15.0f;
		io.Fonts->Clear();
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets\\Fonts\\LowballNeue\\LowballNeueRegular-rglJB.ttf", kFontSize);
		io.Fonts->AddFontFromFileTTF("Assets\\Fonts\\LowballNeue\\LowballNeueBold-w18A6.ttf", kFontSize);

		const bool fontsUpdated = ImGui::SFML::UpdateFontTexture();
		GB_CORE_ASSERT(fontsUpdated, "ImGui::SFML::UpdateFontTexture failed!");

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDefaultThemeColours();
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

	void ImGuiLayer::SetDefaultThemeColours()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_WindowBg]				= ImVec4{ 0.12f, 0.03f, 0.14f, 1.0f };

		// Headers
		style.Colors[ImGuiCol_Header]				= ImVec4{ 0.24f, 0.13f, 0.24f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered]		= ImVec4{ 0.34f, 0.23f, 0.34f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive]			= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };

		// Buttons
		style.Colors[ImGuiCol_Button]				= ImVec4{ 0.24f, 0.13f, 0.24f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered]		= ImVec4{ 0.34f, 0.23f, 0.34f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive]			= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };

		// Frame BG
		style.Colors[ImGuiCol_FrameBg]				= ImVec4{ 0.24f, 0.13f, 0.24f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered]		= ImVec4{ 0.34f, 0.23f, 0.34f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive]		= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };

		// Menubar BG
		style.Colors[ImGuiCol_MenuBarBg]			= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };

		// Tabs
		style.Colors[ImGuiCol_Tab]					= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };
		style.Colors[ImGuiCol_TabHovered]			= ImVec4{ 0.4f, 0.315f, 0.4f, 1.0f };
		style.Colors[ImGuiCol_TabActive]			= ImVec4{ 0.3f, 0.315f, 0.3f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused]			= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive]	= ImVec4{ 0.22f, 0.171f, 0.23f, 1.0f };

		// Title
		style.Colors[ImGuiCol_TitleBg]				= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive]		= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed]		= ImVec4{ 0.17f, 0.115f, 0.17f, 1.0f };
	}

	void ImGuiLayer::SetDarkThemeColours()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_WindowBg]				= ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		style.Colors[ImGuiCol_Header]				= ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered]		= ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive]			= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		style.Colors[ImGuiCol_Button]				= ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered]		= ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive]			= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		style.Colors[ImGuiCol_FrameBg]				= ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered]		= ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive]		= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		style.Colors[ImGuiCol_Tab]					= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabHovered]			= ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		style.Colors[ImGuiCol_TabActive]			= ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused]			= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive]	= ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		style.Colors[ImGuiCol_TitleBg]				= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive]		= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed]		= ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}

#endif