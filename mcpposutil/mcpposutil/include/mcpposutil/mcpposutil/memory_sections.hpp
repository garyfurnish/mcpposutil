#pragma once
#include "declarations.hpp"
#ifdef __linux__
#include "memory_sections_linux.hpp"
#elif defined(__APPLE__)
#include "memory_sections_osx.hpp"
#elif defined(_WIN32)
inline auto get_data_start() -> void * { return nullptr; }
inline auto get_data_end() -> void * { return nullptr; }
inline void print_pmap() {}
#else
#error "UNKNOWN PLATFORM"
#endif
