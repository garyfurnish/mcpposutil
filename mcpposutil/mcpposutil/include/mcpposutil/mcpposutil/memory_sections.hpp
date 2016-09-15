#pragma once
#include "declarations.hpp"
#ifdef __linux__
#include "memory_sections_linux.hpp"
#elif defined(__APPLE__)
#include "memory_sections_osx.hpp"
#else
#error "UNKNOWN PLATFORM"
#endif
