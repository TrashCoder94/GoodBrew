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
	GB_CORE_LOG_INFO("main function - about to clean up application pointer");
	delete application;
	application = nullptr;
	GB_CORE_LOG_INFO("main function - about to shutdown global systems");
	GB::GBSystems::Shutdown();
	GB_PROFILE_END_SESSION();

	GB_CORE_LOG_INFO("main function - about to exit out");
	return 0;
}