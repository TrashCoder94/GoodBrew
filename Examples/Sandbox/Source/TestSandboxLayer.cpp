#include "TestSandboxLayer.h"

#include <GBEngine/Components/SpriteComponent.h>
#include <GBEngine/Components/TransformComponent.h>
#include <GBEngine/Level/Level.h>
#include <GBEngine/Objects/Object.h>
#include <GBEngine/Renderer/Renderer.h>
#include <GBEngine/Renderer/Platforms/SFML/SFMLTexture.h>
#include <imgui.h>

TestSandboxLayer::TestSandboxLayer() : GB::Layer("TestSandboxLayer"),
	m_pTestLevel(new GB::Level()),
	m_pTestObject(new GB::Object())
{}

TestSandboxLayer::~TestSandboxLayer()
{}

void TestSandboxLayer::OnAttach()
{	
	GB_CHECK_PTR(m_pTestLevel, "Test level isn't initialized");

	// Sorting out what the object should look like!
	{
		GB::TransformComponent* pTransformComponent = m_pTestObject->AddComponent<GB::TransformComponent>();
		GB::SpriteComponent* pSpriteComponent = m_pTestObject->AddComponent<GB::SpriteComponent>();
	}

	// Add the object to the level
	m_pTestLevel->AddObject(m_pTestObject);
	
	// Initialize/begin the level and any objects...
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

	if (m_pTestObject)
	{
		// Don't need to call End/Deinitialize for m_pTestObject since the owning level will handle that already
		delete m_pTestObject;
		m_pTestObject = nullptr;
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
	m_pTestLevel->Render();
}

#if GB_IMGUI_ENABLED
void TestSandboxLayer::OnImGuiRender()
{
	ImGui::ShowDemoWindow();

	GB_CHECK_PTR(m_pTestLevel, "Level isn't initialized!");
	m_pTestLevel->ImGuiRender();

	ImGui::Begin("Renderer Stats");
	{
		ImGui::Text("Texture Count: %d", GB::Renderer::GetStats().m_TextureCount);
	}
	ImGui::End();
}
#endif