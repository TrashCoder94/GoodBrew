#pragma once

#include "GBEngine/Core/Log.h"
#include "GBEngine/Core/PlatformDetection.h"

#ifdef GB_DEBUG
	#if defined(GB_PLATFORM_WINDOWS)
		#define GB_DEBUGBREAK() __debugbreak();
	#elif defined(GB_PLATFORM_LINUX)
		#include <signal.h>
		#define GB_DEBUGBREAK() raise(SIGTRAP)
	#elif defined(GB_PLATFORM_MACOS)
		#include <signal.h>
		#define GB_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define GB_ENABLE_ASSERTS
#else
	#define GB_DEBUGBREAK()
#endif

#ifdef GB_ENABLE_ASSERTS
	#define GB_INTERNAL_ASSERT_IMPLEMENTATION(type, check, message) { if(!(check)) { GB##type##LOG_ERROR("ASSERT: {0}", message); GB_DEBUGBREAK(); } }

	#define GB_ASSERT(check, message) { GB_INTERNAL_ASSERT_IMPLEMENTATION(_, check, message); }
	#define GB_CORE_ASSERT(check, message) { GB_INTERNAL_ASSERT_IMPLEMENTATION(_CORE_, check, message); }
#else
	#define GB_ASSERT(...)
	#define GB_CORE_ASSERT(...)
#endif

#define GB_CHECK_PTR(x, msg) if(x == nullptr) GB_ASSERT(x, msg)
#define GB_CHECK_PTR_SAFE(x) if(x == nullptr) return
