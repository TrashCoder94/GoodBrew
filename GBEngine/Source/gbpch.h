#pragma once

#include "GBEngine/Core/PlatformDetection.h"

// ===============================================
// Common
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

// Data Structures
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
// ===============================================

// ===============================================
// GB Engine
#include "GBEngine/Core/Base.h"
#include "GBEngine/Core/Log.h"
#include "GBEngine/Core/Assert.h"
#include "GBEngine/Profiling/Instrumentor.h"

// Platform Specific
#ifdef GB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
// ===============================================