#pragma once

#include <memory>
#include "GBEngine/Core/Macros.h"
#include "GBEngine/Events/EventSystem.h"
#include "GBEngine/Profiling/Instrumentor.h"
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

#define GB_EXPAND_MACRO(x) x
#define GB_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define GB_BIND_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define GB_BIND_EVENT(type, obj, func) GB::EventSystem::Get().Bind(type, obj, GB_BIND_FUNCTION(func));
#define GB_UNBIND_EVENT(type, obj) GB::EventSystem::Get().Unbind(type, obj);

#define GB_SET_TIMER(obj, func, time) GB::TimerSystem::Get().AddTimer(obj, GB_BIND_FUNCTION(func), time);
#define GB_CLEAR_TIMER(timerHandle) GB::TimerSystem::Get().ClearTimer(timerHandle);

#define GB_DOES_CLASS_INHERIT_FROM(base, derived) std::is_base_of<base, derived>::value

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