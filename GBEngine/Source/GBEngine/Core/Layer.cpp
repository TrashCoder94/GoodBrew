#include "gbpch.h"
#include "Layer.h"

namespace GB
{
	Layer::Layer(const std::string& LayerName) :
		m_DebugName(LayerName)
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::OnAttach()
	{
	}

	void Layer::OnDetach()
	{
	}

	void Layer::OnUpdate(const float deltaTime)
	{
	}

	void Layer::OnRender()
	{
	}

#if GB_IMGUI_ENABLED
	void Layer::OnImGuiRender()
	{
	}
#endif
}