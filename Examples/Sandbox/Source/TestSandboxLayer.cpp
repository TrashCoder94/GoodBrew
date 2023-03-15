#include "TestSandboxLayer.h"
#include <imgui.h>

TestSandboxLayer::TestSandboxLayer() : GB::Layer("TestSandboxLayer")
{
}

TestSandboxLayer::~TestSandboxLayer()
{
}

#if GB_IMGUI_ENABLED
void TestSandboxLayer::OnImGuiRender()
{
	ImGui::ShowDemoWindow();
}
#endif