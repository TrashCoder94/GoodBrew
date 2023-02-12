#pragma once

#include <memory>
#include "GBEngine/Core/PlatformDetection.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Timer/TimerSystem.h"

// DLL support.
#ifdef GB_PLATFORM_WINDOWS
	#if GB_DYNAMIC_LINK
		#ifdef GB_BUILD_DLL
			#define GB_API __declspec(dllexport)
		#else
			#define GB_API __declspec(dllimport)
		#endif
	#else
		#define GB_API
	#endif
#endif	// End of DLL support.

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

#define GB_EXPAND_MACRO(x) x
#define GB_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define GB_BIND_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define GB_BIND_EVENT(type, obj, func) GB::EventSystem::Get().Bind(type, obj, GB_BIND_FUNCTION(func));
#define GB_UNBIND_EVENT(type, obj) GB::EventSystem::Get().Unbind(type, obj);

#define GB_SET_TIMER(obj, func, time) GB::TimerSystem::Get().AddTimer(obj, GB_BIND_FUNCTION(func), time);
#define GB_CLEAR_TIMER(timerHandle) GB::TimerSystem::Get().ClearTimer(timerHandle);

namespace GB
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr UniquePtr<T> CreateUniquePtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr SharedPtr<T> CreateSharedPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using WeakPtr = std::weak_ptr<T>;
	template<typename T, typename ... Args>
	constexpr WeakPtr<T> CreateWeakPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}