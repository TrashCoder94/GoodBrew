#pragma once

#include "GBEditorWidget.h"

namespace GB
{
	class Object;

	class EditorWidgetDetailsWindow : public EditorWidget
	{
	public:
		EditorWidgetDetailsWindow(EditorLayer* pEditorLayer);
		~EditorWidgetDetailsWindow();
		virtual void Draw() override;

	private:
		void DrawComponents(Object* pObject);

		bool ShouldHideComponent(const std::string& componentClassName);

		std::vector<std::string> m_ComponentClassesToHide;
	};
}