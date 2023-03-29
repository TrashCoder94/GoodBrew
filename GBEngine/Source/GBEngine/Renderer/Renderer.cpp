#include "gbpch.h"
#include "Renderer.h"
#include "GraphicsContext.h"

namespace GB
{
	UniquePtr<GraphicsContext> Renderer::s_pGraphicsContext = nullptr;

	void Renderer::Initialize(void* window)
	{
		s_pGraphicsContext = GraphicsContext::Create(window);
		GB_CORE_ASSERT(s_pGraphicsContext.get(), "Failed to create graphics context! Make sure RendererAPI::s_API is set correctly before this is called.");

		s_pGraphicsContext->Initialize();
	}

	void Renderer::Deinitialize()
	{
		s_pGraphicsContext->Deinitialize();
	}
}