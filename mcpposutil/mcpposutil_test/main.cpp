#include <iostream>
#include <mcpposutil/mcpposutil/memory_sections.hpp>

int main()
{
  using namespace mcpposutil;
  ::std::cout << "data section: " << get_data_start() << " " << get_data_end() << ::std::endl;
  ::std::cout << "memory maps:\n" << read_memory_maps() << ::std::endl;
  return 0;
}
