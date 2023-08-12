#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetMenuBar : public EditorWidget
	{
	public:
		EditorWidgetMenuBar(EditorLayer* pEditorLayer);
		~EditorWidgetMenuBar();
		virtual void Draw() override;
	};
}