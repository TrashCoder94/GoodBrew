#pragma once

extern GB::Application* GB::CreateApplication();

int main(int argc, char** argv)
{
	GB_PROFILE_BEGIN_SESSION("Startup", "GBProfile-Startup.json");
	GB::GBSystems::Init();
	GB::Application* application = GB::CreateApplication();
	GB_PROFILE_END_SESSION();

	GB_PROFILE_BEGIN_SESSION("Runtime", "GBProfile-Runtime.json");
	application->Run();
	GB_PROFILE_END_SESSION();

	GB_PROFILE_BEGIN_SESSION("Shutdown", "GBProfile-Shutdown.json");
	delete application;
	GB::GBSystems::Shutdown();
	GB_PROFILE_END_SESSION();

	return 0;
}