#pragma once

#include "GBEngine/Renderer/Texture.h"

namespace GB
{
	class BGFXTexture2D : public Texture2D
	{
	public:
		BGFXTexture2D(uint32_t width, uint32_t height);
		BGFXTexture2D(const std::string& filepath);
		~BGFXTexture2D();

		virtual uint32_t GetWidth() const final override;
		virtual uint32_t GetHeight() const final override;
		virtual uint32_t GetRendererID() const final override;

		virtual void SetData(void* data, uint32_t size) final override;

		virtual void Bind(uint32_t slot = 0) const final override;
		virtual void Unbind(uint32_t slot = 0) const final override;

		virtual const std::string& GetFilepath() const final override;

		virtual bool operator==(const Texture& other) const final override;

	private:
		std::string m_Filepath;
		uint32_t m_Width;
		uint32_t m_Height;
		int32_t m_RendererID;
	};
}