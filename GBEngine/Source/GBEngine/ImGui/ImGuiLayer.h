#pragma once

#if GB_IMGUI_ENABLED

#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "GBEngine/Core/Layer.h"
#include "GBEngine/Events/KeyEvents.h"
#include "GBEngine/Events/MouseEvents.h"

namespace GB
{
	class ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer();

			virtual void OnAttach() override;
			void Update(const sf::Time& sfDeltaTime);
			virtual void OnDetach() override;

			void Begin();
			void End();

		private:
			void SetDefaultThemeColours();
			void SetDarkThemeColours();
			void SetDarkBlueThemeColours();
			void SetDarkPurpleThemeColours();
			void SetTheme(const ImVec4& mainColour);

			sf::RenderWindow* m_pWindow;
	};
}

#endif