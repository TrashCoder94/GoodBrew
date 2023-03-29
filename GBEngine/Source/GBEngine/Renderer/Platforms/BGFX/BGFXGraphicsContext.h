#pragma once

#include "GBEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace GB
{
	class BGFXGraphicsContext : public GraphicsContext
	{
	public:
		BGFXGraphicsContext(GLFWwindow* pWindowHandle);
		~BGFXGraphicsContext();

		virtual void Initialize() final override;
		virtual void Deinitialize() final override;

	private:
		GLFWwindow* m_pWindow;
	};
}