#include "gbpch.h"
#include "GraphicsContext.h"
#include "RendererAPI.h"

namespace GB
{
	UniquePtr<GraphicsContext> GB::GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::EAPI::None:
			{
				GB_CORE_ASSERT(false, "RendererAPI::EAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::EAPI::SFML:
			{
				return nullptr;
			}
			/*case RendererAPI::EAPI::BGFX:
			{
				return CreateUniquePtr<BGFXGraphicsContext>(static_cast<GLFWwindow*>(window));
			}*/
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}