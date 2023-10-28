#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetViewportWindow : public EditorWidget
	{
	public:
		EditorWidgetViewportWindow(EditorLayer* pEditorLayer);
		~EditorWidgetViewportWindow();
		virtual void Draw() override;

	private:
		float2 m_ViewportSize;
	};
}