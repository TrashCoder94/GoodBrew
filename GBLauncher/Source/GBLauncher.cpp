#include <GBEngine.h>
#include <GBEngine/Core/EntryPoint.h>

#include "GBLauncherLayer.h"

class GBLauncher : public GB::Application
{
public:
	GBLauncher() : GB::Application("GB Launcher")
	{
		PushLayer(new GBLauncherLayer());
	}

	~GBLauncher()
	{

	}
};

GB::Application* GB::CreateApplication()
{
	return new GBLauncher();
}