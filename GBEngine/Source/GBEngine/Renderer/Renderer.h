#pragma once

namespace GB
{
	class GraphicsContext;

	class Renderer
	{
	public:
		static void Initialize(void* window);
		static void Deinitialize();

	private:
		static UniquePtr<GraphicsContext> s_pGraphicsContext;
	};
}