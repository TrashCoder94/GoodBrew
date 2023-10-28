#pragma once

#include "GBEngine/Core/Base.h"

namespace GB
{
	class Texture2D;

	class RenderTexture
	{
	public:
		static SharedPtr<RenderTexture> Create(uint32_t width, uint32_t height);

		virtual void Begin() = 0;
		virtual void AddTextureToDraw(Texture2D* pTexture) = 0;
		virtual void End() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
	};
}