#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetLogWindow : public EditorWidget
	{
	public:
		EditorWidgetLogWindow(EditorLayer* pEditorLayer);
		~EditorWidgetLogWindow();
		virtual void Draw() override;
	};
}
