#include "gbpch.h"
#include "Renderer.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"

namespace GB
{
	UniquePtr<GraphicsContext> Renderer::s_pGraphicsContext = nullptr;
	UniquePtr<RendererAPI> Renderer::s_pRendererAPI = nullptr;
	Renderer::Statistics Renderer::s_RendererStatistics = Renderer::Statistics();
	uint32_t Renderer::s_RendererID = 0;

	void Renderer::Initialize(void* window)
	{
		s_pGraphicsContext = GraphicsContext::Create(window);
		GB_CORE_ASSERT(s_pGraphicsContext.get(), "Failed to create graphics context! Make sure RendererAPI::s_API is set correctly before this is called.");

		s_pRendererAPI = RendererAPI::Create(window);
		GB_CORE_ASSERT(s_pRendererAPI.get(), "Failed to create renderer API! Make sure RendererAPI::s_API is set correctly before this is called.");

		s_pGraphicsContext->Initialize();
		s_pRendererAPI->Initialize();
	}

	void Renderer::Begin()
	{
		ResetStats();
	}

	void Renderer::DrawTexture(Texture2D* pTexture)
	{
		GB_CHECK_PTR(s_pRendererAPI.get(), "RendererAPI is nullptr!");
		s_pRendererAPI->DrawTexture(pTexture);
		++s_RendererStatistics.m_TextureCount;
	}

	void Renderer::End()
	{
	}

	void Renderer::Deinitialize()
	{
		s_pGraphicsContext->Deinitialize();
		s_pRendererAPI->Deinitialize();

		s_pGraphicsContext.reset();
		s_pRendererAPI.reset();
	}

	uint32_t Renderer::GenerateID()
	{
		return ++s_RendererID;
	}

	const Renderer::Statistics& Renderer::GetStats()
	{
		return s_RendererStatistics;
	}

	void Renderer::ResetStats()
	{
		s_RendererStatistics.m_TextureCount = 0;
	}

	GraphicsContext* Renderer::GetGraphicsContext()
	{
		return s_pGraphicsContext.get();
	}

	RendererAPI* Renderer::GetRendererAPI()
	{
		return s_pRendererAPI.get();
	}
}