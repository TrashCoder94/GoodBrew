#include "gbpch.h"

#if GB_IMGUI_ENABLED

#include "ImGuiLayer.h"

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

		constexpr const char* kDefaultFontFilepath = "Assets/Fonts/Metropolis/Metropolis-Medium.ttf";
		constexpr const char* kBoldFontFilepath = "Assets/Fonts/Metropolis/Metropolis-Bold.ttf";
		constexpr float kFontSize = 18.0f;
		io.Fonts->Clear();
		io.FontDefault = io.Fonts->AddFontFromFileTTF(kDefaultFontFilepath, kFontSize);
		io.Fonts->AddFontFromFileTTF(kBoldFontFilepath, kFontSize);

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
		SetDarkBlueThemeColours();
	}

	void ImGuiLayer::SetDarkThemeColours()
	{
		SetTheme(ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f });
	}

	void ImGuiLayer::SetDarkBlueThemeColours()
	{
		SetTheme(ImVec4{ 0.2f, 0.2f, 0.4f, 1.0f });
	}

	void ImGuiLayer::SetDarkPurpleThemeColours()
	{
		SetTheme(ImVec4{ 0.4f, 0.315f, 0.4f, 1.0f });
	}

	void ImGuiLayer::SetTheme(const ImVec4& mainColour)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// General BG
		style.Colors[ImGuiCol_WindowBg] = ImVec4{ mainColour.x - 0.28f, mainColour.y - 0.2755f, mainColour.z - 0.271f, 1.0f };
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
		style.Colors[ImGuiCol_PopupBg] = ImVec4{ mainColour.x - 0.28f, mainColour.y - 0.2755f, mainColour.z - 0.271f, 1.0f };
		
		// Headers
		style.Colors[ImGuiCol_Header] = ImVec4{ mainColour.x - 0.18f, mainColour.y - 0.1755f, mainColour.z - 0.171f, 1.0f };
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ mainColour.x - 0.08f, mainColour.y - 0.0755f, mainColour.z - 0.071f, 1.0f };
		style.Colors[ImGuiCol_HeaderActive] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };

		// Buttons
		style.Colors[ImGuiCol_Button] = ImVec4{ mainColour.x - 0.18f, mainColour.y - 0.1755f, mainColour.z - 0.171f, 1.0f };
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ mainColour.x - 0.08f, mainColour.y - 0.0755f, mainColour.z - 0.071f, 1.0f };
		style.Colors[ImGuiCol_ButtonActive] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };

		// Frame BG
		style.Colors[ImGuiCol_FrameBg] = ImVec4{ mainColour.x - 0.18f, mainColour.y - 0.1755f, mainColour.z - 0.171f, 1.0f };
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ mainColour.x - 0.08f, mainColour.y - 0.0755f, mainColour.z - 0.071f, 1.0f };
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };

		// Tabs
		style.Colors[ImGuiCol_Tab] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
		style.Colors[ImGuiCol_TabHovered] = ImVec4{ mainColour.x, mainColour.y, mainColour.z, 1.0f };
		style.Colors[ImGuiCol_TabActive] = ImVec4{ mainColour.x - 0.1f, mainColour.y - 0.1f, mainColour.z - 0.1f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ mainColour.x - 0.18f, mainColour.y - 0.1755f, mainColour.z - 0.171f, 1.0f };

		// Title
		style.Colors[ImGuiCol_TitleBg] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ mainColour.x - 0.23f, mainColour.y - 0.23f, mainColour.z - 0.23f, 1.0f };
	}
}

#endif