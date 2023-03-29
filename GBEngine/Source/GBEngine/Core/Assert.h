#pragma once

#include "GBEngine/Core/Base.h"
#include "GBEngine/Core/Log.h"

#ifdef GB_ENABLE_ASSERTS
namespace GB::Assert
{
	constexpr const char* CurrentFileName(const char* path)
	{
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}

#define GB_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { GB##type##LOG_ERROR(msg, __VA_ARGS__); GB_DEBUGBREAK(); } }
#define GB_INTERNAL_ASSERT_WITH_MSG(type, check, ...) GB_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: '{0}'", __VA_ARGS__)
#define GB_INTERNAL_ASSERT_NO_MSG(type, check) GB_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at '{1}':'{2}'", GB_STRINGIFY_MACRO(check), ::GB::Assert::CurrentFileName(__FILE__), __LINE__)

#define GB_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define GB_INTERNAL_ASSERT_GET_MACRO(...) GB_EXPAND_MACRO( GB_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, GB_INTERNAL_ASSERT_WITH_MSG, GB_INTERNAL_ASSERT_NO_MSG) )

#define GB_ASSERT(...) GB_EXPAND_MACRO( GB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define GB_CORE_ASSERT(...) GB_EXPAND_MACRO( GB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define GB_ASSERT(...)
#define GB_CORE_ASSERT(...)
#endif

#define GB_CHECK_PTR(x, msg) if(x == nullptr) GB_ASSERT(x, msg);
#define GB_CHECK_PTR_SAFE(x) if(x == nullptr) return
