#include "GBEditorWidgetViewportWindow.h"
#include <imgui.h>
#include <imgui-SFML.h>
#include <GBEngine/Renderer/Platforms/SFML/SFMLRenderTexture.h>
#include "GBEditorLayer.h"

namespace GB
{
	EditorWidgetViewportWindow::EditorWidgetViewportWindow(EditorLayer* pEditorLayer) : EditorWidget(pEditorLayer)
	{}

	EditorWidgetViewportWindow::~EditorWidgetViewportWindow()
	{}

	void EditorWidgetViewportWindow::Draw()
	{
#if GB_IMGUI_ENABLED
		ImGui::Begin("Viewport");
		{
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			// TODO: Abstract this somehow?
			GB_PTR(pRenderTexture, m_pEditorLayer->GetRenderTexture(), "");
			GB_PTR(pSFMLRenderTexture, static_cast<SFMLRenderTexture*>(pRenderTexture), "");
			ImGui::Image(pSFMLRenderTexture->GetSFRenderTexture(), { m_ViewportSize.x, m_ViewportSize.y });
		}
		ImGui::End();
#endif
	}
}