#pragma once

#include "GBEngine/Core/Base.h"
#include "GBEngine/Core/Log.h"

#ifdef GB_ENABLE_ASSERTS
	#define GB_INTERNAL_ASSERT_IMPL(type, check, message) { if(!(check)) { GB##type##LOG_ERROR("ASSERT: {0}", message); GB_DEBUGBREAK(); } }

	#define GB_ASSERT(check, message) { GB_INTERNAL_ASSERT_IMPL(_, check, message); }
	#define GB_CORE_ASSERT(check, message) { GB_INTERNAL_ASSERT_IMPL(_CORE_, check, message); }
#else
	#define GB_ASSERT(...)
	#define GB_CORE_ASSERT(...)
#endif

#define GB_CHECK_PTR(x, msg) if(x == nullptr) GB_ASSERT(x, msg);
#define GB_CHECK_PTR_SAFE(x) if(x == nullptr) return
