#include "TestSandboxLayer.h"
#include <imgui.h>

TestSandboxLayer::TestSandboxLayer() : GB::Layer("TestSandboxLayer")
{
}

TestSandboxLayer::~TestSandboxLayer()
{
}

void TestSandboxLayer::OnImGuiRender()
{
	ImGui::ShowDemoWindow();
}