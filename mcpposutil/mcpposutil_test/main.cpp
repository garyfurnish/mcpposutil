#include <iostream>
#include <mcpposutil/mcpposutil/memory_sections.hpp>

int main()
{
  using namespace mcpposutil;
  (void)get_data_start();
  (void)get_data_end();
  (void)pmap_as_string();
  return 0;
}
