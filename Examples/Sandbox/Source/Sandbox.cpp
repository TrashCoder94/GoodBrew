#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

#include "TestSandboxLayer.h"

class Sandbox : public GB::Application
{
public:
	Sandbox() : GB::Application("GB Sandbox")
	{
		m_pSandboxLayer = new TestSandboxLayer();
		PushLayer(m_pSandboxLayer);
	}

	~Sandbox()
	{
		PopLayer(m_pSandboxLayer);

		if (m_pSandboxLayer)
		{
			delete m_pSandboxLayer;
			m_pSandboxLayer = nullptr;
		}
	}

private:
	TestSandboxLayer* m_pSandboxLayer = nullptr;
};

GB::Application* GB::CreateApplication()
{
	return new Sandbox();
}