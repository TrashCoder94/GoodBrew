#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class EditorWidgetAssetWindow : public EditorWidget
	{
	public:
		EditorWidgetAssetWindow(EditorLayer* pEditorLayer);
		~EditorWidgetAssetWindow();
		virtual void Draw() override;
	};
}