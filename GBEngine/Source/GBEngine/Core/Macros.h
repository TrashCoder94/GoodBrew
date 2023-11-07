#pragma once

#include "Assert.h"

#define GB_CHECK_PTR(x, msg) if(x == nullptr) GB_ASSERT(x, msg)
#define GB_CHECK_PTR_SAFE(x) if(x == nullptr) return

#define GB_PTR(x, y, msg) auto x = y; GB_CHECK_PTR(x, msg)
#define GB_PTR_SAFE(x, y) auto x = y; GB_CHECK_PTR_SAFE(x)
