#include <exception>
#include <fstream>
#include <mcpposutil/mcpposutil/memory_sections_linux.hpp>
using namespace ::std::string_literals;

#pragma weak __data_start
extern int __data_start[];
extern int _end[];
namespace mcpposutil
{
  auto get_data_start() -> void *
  {
    return __data_start;
  }
  auto get_data_end() -> void *
  {
    return _end;
  }

  ::std::string read_text_file_racy(::gsl::cstring_span<> filename, size_t max_iterations)
  {
    ::std::string sfilename = ::gsl::to_string(filename);
    ::std::string buf, buf2;
    size_t i = 0;
    do {
      const size_t buf_size = 64000;
      buf.clear();
      buf2.clear();
      buf.resize(buf_size);
      buf2.resize(buf_size);
      ::std::ifstream is(sfilename, std::ifstream::binary);
      is.read(const_cast<char *>(buf.data()), buf_size);
      const auto buf_read_len = is.gcount();
      is.close();
      ::std::ifstream is2(sfilename, std::ifstream::binary);
      is2.read(const_cast<char *>(buf2.data()), buf_size);
      const auto buf2_read_len = is.gcount();
      is2.close();
      (void)buf_read_len;
      (void)buf2_read_len;
    } while (buf != buf2 && i != max_iterations++);
    if (i == max_iterations)
      throw ::std::runtime_error("read_text_file_racy"s + sfilename + "failed");
    return buf;
  }
  ::std::string read_memory_maps()
  {
    return read_text_file_racy("/proc/self/maps", 10);
  }
}
