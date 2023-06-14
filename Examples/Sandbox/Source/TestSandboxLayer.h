#pragma once

#include <GBEngine/Core/Layer.h>

namespace GB
{
	class Object;
	class Level;
}

class TestSandboxLayer : public GB::Layer
{
public:
	TestSandboxLayer();
	~TestSandboxLayer();
	
	// Layer
	virtual void OnAttach() final override;
	virtual void OnDetach() final override;
	virtual void OnUpdate(const float deltaTime) final override;
	virtual void OnRender() final override;
#if GB_IMGUI_ENABLED
	virtual void OnImGuiRender() final override;
#endif
	// ~Layer

public:
	GB::Level* m_pTestLevel;
	GB::Object* m_pTestObject;
};