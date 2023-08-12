#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

#include "GBEditorLayer.h"

namespace GB
{
	class Editor : public Application
	{
	public:
		Editor() : Application("GB Editor"),
			m_pEditorLayer(CreateSharedPtr<EditorLayer>())
		{
			PushLayer(m_pEditorLayer.get());
		}

		~Editor()
		{
			PopLayer(m_pEditorLayer.get());
		}

	private:
		SharedPtr<EditorLayer> m_pEditorLayer;
	};

	Application* CreateApplication()
	{
		return new Editor();
	}
}