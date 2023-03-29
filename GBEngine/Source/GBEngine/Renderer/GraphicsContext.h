#pragma once

#include "GBEngine/Core/Base.h"

namespace GB
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Initialize() = 0;
		virtual void Deinitialize() = 0;

		static UniquePtr<GraphicsContext> Create(void* window);
	};
}