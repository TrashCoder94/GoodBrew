#pragma once

#include <string>
#include "GBEngine/Events/Event.h"

namespace GB
{
	class Layer
	{
		public:
			Layer(const std::string& LayerName = "Layer");
			virtual ~Layer();

			virtual void OnAttach();
			virtual void OnDetach();
			virtual void OnUpdate(const float deltaTime);
			virtual void OnRender();
#if GB_IMGUI_ENABLED
			virtual void OnImGuiRender();
#endif
			inline const std::string& GetName() const { return m_DebugName; }
		
		protected:
			std::string m_DebugName;
	};
}
