#include "gbpch.h"
#include "Renderer.h"
#include "GraphicsContext.h"

namespace GB
{
	UniquePtr<GraphicsContext> Renderer::s_pGraphicsContext = nullptr;
	uint32_t Renderer::s_RendererID = 0;

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

	uint32_t Renderer::GenerateID()
	{
		return ++s_RendererID;
	}

	GraphicsContext* Renderer::GetGraphicsContext()
	{
		return s_pGraphicsContext.get();
	}
}