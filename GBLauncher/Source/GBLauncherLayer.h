#pragma once

#include <GBEngine/Core/Layer.h>

class GBLauncherLayer : public GB::Layer
{
public:
	GBLauncherLayer();
	~GBLauncherLayer();

#if GB_IMGUI_ENABLED
	virtual void OnImGuiRender() override;
#endif
};