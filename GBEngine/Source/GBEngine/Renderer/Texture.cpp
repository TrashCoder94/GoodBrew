#include "gbpch.h"
#include "RendererAPI.h"
#include "Texture.h"
#include "Platforms/SFML/SFMLTexture.h"

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
			case RendererAPI::EAPI::SFML:
			{
				return CreateSharedPtr<SFMLTexture>(width, height);
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
			case RendererAPI::EAPI::SFML:
			{
				return CreateSharedPtr<SFMLTexture>(filepath);
			}
		}

		GB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D::Texture2D() : Texture2D(0, 0)
	{}

	Texture2D::Texture2D(const uint32_t width, const uint32_t height) : m_Filepath(""),
		m_Dimensions(width, height)
	{}

	Texture2D::Texture2D(const std::string& filepath) : m_Filepath(filepath),
		m_Dimensions(0, 0)
	{}

	uint32_t Texture2D::GetWidth() const
	{
		return m_Dimensions.x;
	}

	uint32_t Texture2D::GetHeight() const
	{
		return m_Dimensions.y;
	}

	uint32_t Texture2D::GetRendererID() const
	{
		return 0;
	}

	const std::string& Texture2D::GetFilepath() const
	{
		return m_Filepath;
	}
}