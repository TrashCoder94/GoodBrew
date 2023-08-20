#pragma once

#include <stdint.h>

namespace GB
{
	class GraphicsContext;
	class RendererAPI;
	class Texture2D;

	class Renderer
	{
	public:
		static void Initialize(void* window);
		static void Begin();
		static void DrawTexture(Texture2D* pTexture);
		static void End();
		static void Deinitialize();

		static uint32_t GenerateID();

		static RendererAPI* GetRendererAPI();

		template<class T>
		static T* GetRendererAPI()
		{
			const bool inherits = GB_DOES_CLASS_INHERIT_FROM(RendererAPI, T);
			GB_CORE_ASSERT(inherits, "Class T doesn't inherit from RendererAPI base class");

			if (RendererAPI* pRendererAPI = s_pRendererAPI.get())
			{
				T* pRendererAPICasted = static_cast<T*>(pRendererAPI);
				return pRendererAPICasted;
			}

			return nullptr;
		}

		static GraphicsContext* GetGraphicsContext();
		
		template<class T>
		static T* GetGraphicsContext()
		{
			const bool inherits = GB_DOES_CLASS_INHERIT_FROM(GraphicsContext, T);
			GB_CORE_ASSERT(inherits, "Class T doesn't inherit from GraphicsContext base class");

			if (GraphicsContext* pGraphicsContext = s_pGraphicsContext.get())
			{
				T* pGraphicsContextCasted = static_cast<T*>(pGraphicsContext);
				return pGraphicsContextCasted;
			}

			return nullptr;
		}

		struct Statistics
		{
			uint32_t m_TextureCount = 0;
		};

		static const Statistics& GetStats();
		static void ResetStats();

	private:
		static UniquePtr<GraphicsContext> s_pGraphicsContext;
		static UniquePtr<RendererAPI> s_pRendererAPI;
		static Statistics s_RendererStatistics;
		static uint32_t s_RendererID;
	};
}