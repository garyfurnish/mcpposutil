#pragma once
#pragma weak __data_start
extern int __data_start[];
extern int _end[];
namespace mcpposutil
{
  inline auto get_data_start() -> void *
  {
    return __data_start;
  }
  inline auto get_data_end() -> void *
  {
    return _end;
  }
}
