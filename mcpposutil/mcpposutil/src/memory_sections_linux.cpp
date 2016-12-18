#include <exception>
#include <fstream>
#include <iostream>
#include <mcpposutil/mcpposutil/memory_map_region.hpp>
#include <mcpposutil/mcpposutil/memory_sections_linux.hpp>
#include <mcpputil/mcpputil/boost/algorithm/string/classification.hpp>
#include <mcpputil/mcpputil/boost/algorithm/string/predicate.hpp>
#include <mcpputil/mcpputil/boost/algorithm/string/split.hpp>
#include <sstream>
#include <vector>
using namespace ::std::string_literals;

extern int __data_start[];
extern int _end[];
namespace mcpposutil
{
  [[nodiscard]] auto get_data_start() -> void *
  {
    return __data_start;
  }
  [[nodiscard]] auto get_data_end() -> void *
  {
    return _end;
  }

  [[nodiscard]] ::std::string read_text_file_racy(::gsl::cstring_span<> filename, size_t max_iterations)
  {
    const auto sfilename = ::gsl::to_string(filename);
    ::std::string buf, buf2;
    size_t i = 0;
    do {
      const size_t buf_size = 64000;
      buf.clear();
      buf2.clear();
      buf.resize(buf_size);
      buf2.resize(buf_size);
      ::std::ifstream is(sfilename, ::std::ifstream::binary);
      is.read(const_cast<char *>(buf.data()), buf_size);
      is.close();
      ::std::ifstream is2(sfilename, ::std::ifstream::binary);
      is2.read(const_cast<char *>(buf2.data()), buf_size);
      is2.close();
    } while (buf != buf2 && i != max_iterations++);
    if (i == max_iterations)
      throw ::std::runtime_error("read_text_file_racy"s + sfilename + "failed");
    return buf;
  }
  [[nodiscard]] static auto process_map_strings(const ::std::string map_string)
  {
    ::std::vector<::std::string> lines;
    ::boost::split(lines, map_string, ::boost::is_any_of("\n"), ::boost::token_compress_on);
    ::std::vector<::std::vector<::std::string>> pmap;
    for (auto &&line : lines) {
      if (line[0] == 0)
        continue;
      ::std::vector<::std::string> split_line;
      ::boost::split(split_line, line, ::boost::is_any_of(" "), ::boost::token_compress_on);
      pmap.emplace_back(::std::move(split_line));
    }
    return pmap;
  }
  [[nodiscard]] static ::std::string read_memory_maps_string()
  {
    return read_text_file_racy("/proc/self/maps", 10);
  }
  [[nodiscard]] static auto create_process_map()
  {
    auto pmap_str = read_memory_maps_string();
    auto pmap_vector = process_map_strings(pmap_str);
    return pmap_vector;
  }
  [[nodiscard]] static auto memory_map_region_type_from_string(const ::std::string &path)
  {
    if (path == "[stack]")
      return memory_map_region_type_enum::stack;
    else if (::boost::starts_with(path, "[stack:"))
      return memory_map_region_type_enum::thread_stack;
    else if (path == "[vdso]")
      return memory_map_region_type_enum::vdso;
    else if (path == "[vvar]")
      return memory_map_region_type_enum::vvar;
    else if (path == "[vsyscall]")
      return memory_map_region_type_enum::vsyscall;
    else if (path == "[heap]")
      return memory_map_region_type_enum::heap;
    else if (::boost::starts_with(path, "["))
      throw ::std::runtime_error("unknown memory map region type: " + path);
    else
      return memory_map_region_type_enum::normal;
  }
  [[nodiscard]] static auto memory_range_from_string(const ::std::string &str)
  {
    ::std::vector<::std::string> parts;
    ::boost::split(parts, str, ::boost::is_any_of("-"));
    assert(parts.size() == 2);
    void *vbegin = nullptr, *vend = nullptr;
    memory_map_region_t::range_type::pointer_type begin = nullptr, end = nullptr;
    ::std::stringstream ss, ss2;
    ss << ::std::hex << parts.at(0);
    ss >> vbegin;
    ss2 << ::std::hex << parts.at(1);
    ss2 >> vend;
    begin = mcpputil::unsafe_cast<::std::remove_pointer_t<decltype(begin)>>(vbegin);
    end = mcpputil::unsafe_cast<::std::remove_pointer_t<decltype(end)>>(vend);
    return memory_map_region_t::range_type{begin, end};
  }
  [[nodiscard]] static auto memory_map_region_from_string(const ::std::vector<::std::string> &vec)
  {
    auto &path = vec.at(5);
    auto type = memory_map_region_type_from_string(path);
    auto range = memory_range_from_string(vec.at(0));
    auto mmr = memory_map_region_t{range, type};
    mmr.set_path(path);
    mmr.permissions() = memory_map_region_permissions_from_string(vec.at(1));
    mmr.set_offset(::std::stoull(vec.at(2), 0, 16));
    return mmr;
  }
  auto pmap_as_string() -> ::std::string
  {
    ::std::stringstream ss;
    auto pmap = create_process_map();
    for (auto &&section : pmap) {
      auto region = memory_map_region_from_string(section);
      ss << to_string(region) << "\n";
    }
    return ss.str();
  }
}
