#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

#include "GBEditorLayer.h"

namespace GB
{
	class GBEditor : public GB::Application
	{
	public:
		GBEditor() : GB::Application("GB Editor"),
			m_pEditorLayer(CreateSharedPtr<GBEditorLayer>())
		{
			PushLayer(m_pEditorLayer.get());
		}

		~GBEditor()
		{
			PopLayer(m_pEditorLayer.get());
		}

	private:
		SharedPtr<GBEditorLayer> m_pEditorLayer;
	};

	GB::Application* GB::CreateApplication()
	{
		return new GBEditor();
	}
}