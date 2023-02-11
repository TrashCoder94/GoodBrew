#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

class Sandbox : public GB::Application
{
public:
	Sandbox() : GB::Application("GB Sandbox")
	{
		//PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GB::Application* GB::CreateApplication()
{
	return new Sandbox();
}