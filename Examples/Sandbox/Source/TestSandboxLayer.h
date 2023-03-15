#pragma once

#include <GBEngine/Core/Layer.h>

class TestSandboxLayer : public GB::Layer
{
public:
	TestSandboxLayer();
	~TestSandboxLayer();

#if GB_IMGUI_ENABLED
	virtual void OnImGuiRender() override;
#endif
};