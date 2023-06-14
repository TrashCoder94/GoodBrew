#include "TestSandboxLayer.h"
#include <GBEngine/Level/Level.h>
#include <GBEngine/Objects/Object.h>
#include <imgui.h>

TestSandboxLayer::TestSandboxLayer() : GB::Layer("TestSandboxLayer"),
	m_pTestLevel(new GB::Level()),
	m_pTestObject(new GB::Object())
{
}

TestSandboxLayer::~TestSandboxLayer()
{
}

void TestSandboxLayer::OnAttach()
{	
	GB_CHECK_PTR(m_pTestLevel, "Test level isn't initialized");

	//m_pTestObject->AddComponent<TransformComponent>();
	//m_pTestObject->AddComponent<SpriteComponent>();

	m_pTestLevel->Initialize();
	m_pTestLevel->Begin();
}

void TestSandboxLayer::OnDetach()
{
	if (m_pTestLevel)
	{
		m_pTestLevel->End();
		m_pTestLevel->Deinitialize();

		delete m_pTestLevel;
		m_pTestLevel = nullptr;
	}
}

void TestSandboxLayer::OnUpdate(const float deltaTime)
{
	GB_CHECK_PTR(m_pTestLevel, "Level isn't initialized!");

	m_pTestLevel->Update(deltaTime);
}

void TestSandboxLayer::OnRender()
{
	GB_CHECK_PTR(m_pTestLevel, "Level isn't initialized!");
}

#if GB_IMGUI_ENABLED
void TestSandboxLayer::OnImGuiRender()
{
	ImGui::ShowDemoWindow();
}
#endif