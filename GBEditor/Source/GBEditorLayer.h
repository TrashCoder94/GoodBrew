#pragma once

#include <GBEngine/Core/Layer.h>
#include "GBEditorLevelState.h"

namespace GB
{
	class GBEditorLayer : public GB::Layer
	{
	public:
		GBEditorLayer();
		~GBEditorLayer();

#if GB_IMGUI_ENABLED
		virtual void OnImGuiRender() override;
#endif

	private:
#if GB_IMGUI_ENABLED
		void DrawMenuBar();
		void DrawToolBar();
		void DrawViewportWindow();
		void DrawLevelHierarchyWindow();
		void DrawAssetWindow();
		void DrawLogWindow();
		void DrawDetailsWindow();
#endif

		EGBEditorLevelState m_EditorLevelState;
	};
}