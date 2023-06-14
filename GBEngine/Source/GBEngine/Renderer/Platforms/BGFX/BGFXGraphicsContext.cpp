#include "gbpch.h"
#include "BGFXGraphicsContext.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <nanovg.h>

namespace GB
{
	BGFXGraphicsContext::BGFXGraphicsContext(GLFWwindow* pWindowHandle) : GraphicsContext(),
		m_pWindow(pWindowHandle),
		m_pNVGContext(nullptr)
	{}

	BGFXGraphicsContext::~BGFXGraphicsContext()
	{}

	void BGFXGraphicsContext::Initialize()
	{
		// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
		// Most graphics APIs must be used on the same thread that created the window.
		bgfx::renderFrame();

		{
			GB_PROFILE_SCOPE("bgfxInit");

			// Initialize bgfx using the native window handle and window resolution.
			bgfx::Init init;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
			init.platformData.ndt = glfwGetX11Display();
			init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(m_pWindow);
#elif BX_PLATFORM_OSX
			init.platformData.nwh = glfwGetCocoaWindow(m_pWindow);
#elif BX_PLATFORM_WINDOWS
			init.platformData.nwh = glfwGetWin32Window(m_pWindow);
#endif

			int width, height;
			glfwGetWindowSize(m_pWindow, &width, &height);
			init.resolution.width = (uint32_t)width;
			init.resolution.height = (uint32_t)height;
			init.resolution.reset = BGFX_RESET_VSYNC;

			const bool bgfxInitSuccess = bgfx::init(init);
			GB_CORE_ASSERT(bgfxInitSuccess, "bgfx failed to init!");

			// Set view 0 to the same dimensions as the window and to clear the color buffer.
			const bgfx::ViewId kClearView = 0;
			bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
			bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

			//m_pNVGContext = nvgCreate(1, kClearView);
		}
	}

	void BGFXGraphicsContext::Deinitialize()
	{
		GB_PROFILE_FUNCTION();

		GB_CORE_LOG_INFO("Terminating bgfx and GLFW!");
		bgfx::shutdown();
		glfwTerminate();
	}

	NVGcontext* BGFXGraphicsContext::GetNVGContext()
	{
		return m_pNVGContext;
	}

	NVGcontext* BGFXGraphicsContext::GetNVGContext() const
	{
		return m_pNVGContext;
	}
}