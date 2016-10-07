#pragma once
#include "declarations.hpp"
#include <gsl/gsl>
namespace mcpposutil
{
  /**
   * \brief Return start of data section.
   **/
  inline auto get_data_start() -> void *
  {
    return nullptr;
  }
  /**
   * \brief Return end of data section.
   **/
  inline auto get_data_end() -> void *
  {
    return nullptr;
  }
  /**
   * \brief Print current process map.
   **/
  inline void print_pmap(){};
}
