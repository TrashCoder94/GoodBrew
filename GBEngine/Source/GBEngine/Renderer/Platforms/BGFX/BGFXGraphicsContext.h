#pragma once

#include "GBEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;
struct NVGcontext;

namespace GB
{
	class BGFXGraphicsContext : public GraphicsContext
	{
	public:
		BGFXGraphicsContext(GLFWwindow* pWindowHandle);
		~BGFXGraphicsContext();

		virtual void Initialize() final override;
		virtual void Deinitialize() final override;

		NVGcontext* GetNVGContext();
		NVGcontext* GetNVGContext() const;

	private:
		GLFWwindow* m_pWindow;
		NVGcontext* m_pNVGContext;
	};
}