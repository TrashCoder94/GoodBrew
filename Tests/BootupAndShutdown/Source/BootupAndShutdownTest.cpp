#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

class BootupAndShutdownTestApplication : public GB::Application
{
public:
	BootupAndShutdownTestApplication() : GB::Application("GB Bootup and Shutdown Test App")
	{
		GB_SET_TIMER(this, GB::Application::Close, 10.0f);
	}

	~BootupAndShutdownTestApplication()
	{

	}
};

GB::Application* GB::CreateApplication()
{
	return new BootupAndShutdownTestApplication();
}