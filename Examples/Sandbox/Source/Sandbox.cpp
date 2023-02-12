#include <GBEngine.h>

#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>

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