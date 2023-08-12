#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetDetailsWindow : public EditorWidget
	{
	public:
		EditorWidgetDetailsWindow(EditorLayer* pEditorLayer);
		~EditorWidgetDetailsWindow();
		virtual void Draw() override;
	};
}