#pragma once

#include <stdint.h>

namespace GB
{
	class GraphicsContext;

	class Renderer
	{
	public:
		static void Initialize(void* window);
		static void Deinitialize();

		static uint32_t GenerateID();

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

	private:
		static UniquePtr<GraphicsContext> s_pGraphicsContext;
		static uint32_t s_RendererID;
	};
}