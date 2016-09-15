#include <iostream>
#include <mcpposutil/mcpposutil/memory_sections.hpp>

int main()
{
  using namespace mcpposutil;
  ::std::cout << "data section: " << get_data_start() << " " << get_data_end() << ::std::endl;
  return 0;
}
