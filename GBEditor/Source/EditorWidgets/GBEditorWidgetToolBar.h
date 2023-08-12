#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetToolBar : public EditorWidget
	{
	public:
		EditorWidgetToolBar(EditorLayer* pEditorLayer);
		~EditorWidgetToolBar();
		virtual void Draw() override;
	};
}