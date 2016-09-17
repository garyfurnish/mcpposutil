#pragma once
#include "declarations.hpp"
#include <gsl/gsl>
namespace mcpposutil
{
  /**
   * \brief Return start of data section.
   **/
  extern auto get_data_start() -> void *;
  /**
   * \brief Return end of data section.
   **/
  extern auto get_data_end() -> void *;
  /**
   * \brief Read in a file that can change while being read in a quasi-determinalistic way.
   *
   * \brief filename File to read.
   * \brief max_iterations Number of times to try to read file before throwing exception.
   **/
  extern ::std::string read_file(::gsl::cstring_span<> filename, size_t max_iterations);
  /**
   * \brief Read memory maps for this process in as string from proc.
   **/
  extern ::std::string read_memory_maps();
}
