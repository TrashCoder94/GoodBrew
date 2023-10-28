#pragma once

#include <GBEngine/Core/Base.h>
#include "GBEditorStyle.h"

namespace GB
{
	class EditorLayer;

	class EditorWidget
	{
	public:
		EditorWidget(EditorLayer* pEditorLayer);
		virtual ~EditorWidget() = default;
		virtual void Draw() = 0;

	protected:
		EditorLayer* m_pEditorLayer;
	};
}