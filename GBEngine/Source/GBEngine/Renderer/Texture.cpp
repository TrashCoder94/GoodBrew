#include "gbpch.h"
#include "RendererAPI.h"
#include "Texture.h"
#include "Platforms/BGFX/BGFXTexture2D.h"

namespace GB
{
	SharedPtr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::EAPI::None:
			{
				GB_CORE_ASSERT(false, "RendererAPI::EAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::EAPI::BGFX:
			{
				return CreateUniquePtr<BGFXTexture2D>(width, height);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	SharedPtr<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::EAPI::None:
			{
				GB_CORE_ASSERT(false, "RendererAPI::EAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::EAPI::BGFX:
			{
				return CreateUniquePtr<BGFXTexture2D>(filepath);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}