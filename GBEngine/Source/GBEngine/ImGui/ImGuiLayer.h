#pragma once

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

			void OnAttach() override;
			void OnDetach() override;

			void Begin();
			void End();

			void SetDarkThemeColours();
	};
}
