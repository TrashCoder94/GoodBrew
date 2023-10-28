#include "gbpch.h"
#include "RenderTexture.h"
#include "RendererAPI.h"
#include "Platforms/SFML/SFMLRenderTexture.h"

namespace GB
{
	SharedPtr<RenderTexture> RenderTexture::Create(uint32_t width, uint32_t height)
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
				return CreateSharedPtr<SFMLRenderTexture>(width, height);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}