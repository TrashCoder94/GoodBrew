#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

class BuildMachineApplication : public GB::Application
{
public:
	BuildMachineApplication() : GB::Application("GB BuildMachine")
	{
		GB_SET_TIMER(this, GB::Application::Close, 10.0f);
	}

	~BuildMachineApplication()
	{

	}
};

GB::Application* GB::CreateApplication()
{
	return new BuildMachineApplication();
}