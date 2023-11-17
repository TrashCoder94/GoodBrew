#pragma once

#include "GBEngine/Core/Base.h"

namespace GB
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual const std::string& GetFilepath() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D();
		static SharedPtr<Texture2D> Create(const uint32_t width, const uint32_t height);
		static SharedPtr<Texture2D> Create(const std::string& filepath);

	protected:
		Texture2D(const uint32_t width, const uint32_t height);
		Texture2D(const std::string& filepath);

	public:
		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual uint32_t GetRendererID() const override;

		virtual const std::string& GetFilepath() const override;

		virtual bool operator==(const Texture& other) const override
		{
			return GetFilepath() == other.GetFilepath();
		}

	protected:
		std::string m_Filepath;
		int2 m_Dimensions;
	};
}