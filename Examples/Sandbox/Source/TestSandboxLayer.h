#pragma once

#include <GBEngine/Core/Layer.h>

class TestSandboxLayer : public GB::Layer
{
public:
	TestSandboxLayer();
	~TestSandboxLayer();

	virtual void OnImGuiRender() override;
};