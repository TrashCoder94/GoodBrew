#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

#include "TestSandboxLayer.h"

class Sandbox : public GB::Application
{
public:
	Sandbox() : GB::Application("GB Sandbox")
	{
		PushLayer(new TestSandboxLayer());
	}

	~Sandbox()
	{

	}
};

GB::Application* GB::CreateApplication()
{
	return new Sandbox();
}