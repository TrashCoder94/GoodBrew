#pragma once

#if GB_IMGUI_ENABLED

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

			void SetDarkThemeColours();

		private:
			sf::RenderWindow* m_pWindow;
	};
}

#endif