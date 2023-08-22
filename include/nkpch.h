#pragma once

#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <concepts>
#include <sstream>
#include <filesystem>
#include <format>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <span>

#if defined(NK_PLATFORM_WINDOWS)
	#include <windows.h>
#endif

#include "core/defines.h"
#include "system/logging_system.h"
