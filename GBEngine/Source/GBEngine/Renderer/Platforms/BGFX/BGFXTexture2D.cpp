#include "gbpch.h"
#include "BGFXTexture2D.h"

#include <bimg/bimg.h>
#include <bx/bx.h>
#include <bimg/decode.h>
#include <stb_image.h>
#include <nanovg.h>

#include "BGFXGraphicsContext.h"
#include "GBEngine/Renderer/Renderer.h"

extern bx::AllocatorI* g_allocator;

namespace GB
{
	BGFXTexture2D::BGFXTexture2D(uint32_t width, uint32_t height) :
		m_Filepath(""),
		m_Width(width),
		m_Height(height),
		m_RendererID(0)
	{

	}

	BGFXTexture2D::BGFXTexture2D(const std::string& filepath) :
		m_Filepath(filepath),
		m_Width(0),
		m_Height(0),
		m_RendererID(0)
	{
		uint32_t size = 0;

		//void* data = Load(m_Filepath, size);
		int width = 0;
		int height = 0;
		int channels = 0;

		// OpenGL (Windows+Linux will use this) expects textures to be given bottom to top, stbi works in the opposite direction.
		// Use this function to flip it and sync up with OpenGL.
#if defined (GB_PLATFORM_WINDOWS)
		stbi_set_flip_vertically_on_load(1);
#elif defined(GB_PLATFORM_LINUX)
		stbi_set_flip_vertically_on_load(1);
#endif

		stbi_uc* data = nullptr;
		{
			GB_PROFILE_SCOPE("stbi_load - BGFXTexture2D::BGFXTexture2D(const std::string&)");
			data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		}
		GB_CHECK_PTR(data, "BGFXTexture2D wasn't able to load!");

		m_Width = width;
		m_Height = height;

		bimg::ImageContainer* imageContainer = bimg::imageParse(
			g_allocator
			, data
			, size
			, bimg::TextureFormat::RGBA8
		);
		
		GB_CHECK_PTR(imageContainer, "bimg::ImageContainer isn't valid for image data");

		static constexpr int kImageFlags = 0;
		NVGcontext* pNVGContext = Renderer::GetGraphicsContext<BGFXGraphicsContext>()->GetNVGContext();

		int32_t texId = nvgCreateImageRGBA(
			pNVGContext
			, imageContainer->m_width
			, imageContainer->m_height
			, kImageFlags
			, (const uint8_t*)imageContainer->m_data
		);

		m_RendererID = texId;

		bimg::imageFree(imageContainer);
		stbi_image_free(data);
	}

	BGFXTexture2D::~BGFXTexture2D()
	{
	}

	uint32_t BGFXTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t BGFXTexture2D::GetHeight() const
	{
		return m_Height;
	}

	uint32_t BGFXTexture2D::GetRendererID() const
	{
		return m_RendererID;
	}

	void BGFXTexture2D::SetData(void* data, uint32_t size)
	{
	}

	void BGFXTexture2D::Bind(uint32_t slot) const
	{
	}

	void BGFXTexture2D::Unbind(uint32_t slot) const
	{
	}

	const std::string& BGFXTexture2D::GetFilepath() const
	{
		return m_Filepath;
	}

	bool BGFXTexture2D::operator==(const Texture& other) const
	{
		return m_RendererID == ((BGFXTexture2D&)other).m_RendererID;
	}
}