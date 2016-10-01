#include <exception>
#include <mcpposutil/mcpposutil/memory_map_region.hpp>
#include <numeric>
#include <sstream>
using namespace ::std::string_literals;
namespace mcpposutil
{
  [[nodiscard]] ::std::string to_string(memory_map_region_type_enum type)
  {
    switch (type) {
    case memory_map_region_type_enum::none:
      return "none";
    case memory_map_region_type_enum::normal:
      return "normal";
    case memory_map_region_type_enum::stack:
      return "stack";
    case memory_map_region_type_enum::thread_stack:
      return "thread_stack";
    case memory_map_region_type_enum::vdso:
      return "vdso";
    case memory_map_region_type_enum::vvar:
      return "vvar";
    case memory_map_region_type_enum::vsyscall:
      return "vsyscall";
    case memory_map_region_type_enum::heap:
      return "heap";
    }
  }
  [[nodiscard]] ::std::string to_string(memory_map_region_permissions_enum perm)
  {
    switch (perm) {
    case memory_map_region_permissions_enum::read:
      return "r";
    case memory_map_region_permissions_enum::write:
      return "w";
    case memory_map_region_permissions_enum::execute:
      return "x";
    case memory_map_region_permissions_enum::shared:
      return "s";
    case memory_map_region_permissions_enum::private_:
      return "p";
    case memory_map_region_permissions_enum::none:
      return "-";
    }
  }
  [[nodiscard]] extern memory_map_region_permissions_enum memory_map_region_permission_from_string(char c)
  {
    switch (c) {
    case 'r':
      return memory_map_region_permissions_enum::read;
    case 'w':
      return memory_map_region_permissions_enum::write;
    case 'x':
      return memory_map_region_permissions_enum::execute;
    case 's':
      return memory_map_region_permissions_enum::shared;
    case 'p':
      return memory_map_region_permissions_enum::private_;
    case '-':
      return memory_map_region_permissions_enum::none;
    default:
      throw ::std::runtime_error("Unknown memory permission: "s + c);
    }
  }
  [[nodiscard]] extern ::std::vector<memory_map_region_permissions_enum>
  memory_map_region_permissions_from_string(const ::std::string &s)
  {
    ::std::vector<memory_map_region_permissions_enum> ret;
    for (auto &c : s) {
      auto perm = memory_map_region_permission_from_string(c);
      if (perm != memory_map_region_permissions_enum::none)
        ret.push_back(perm);
    }
    return ret;
  }
  [[nodiscard]] ::std::string to_string(::std::vector<memory_map_region_permissions_enum> perms)
  {
    auto ret = ::std::accumulate(perms.begin(), perms.end(), ::std::string{},
                                 [](auto &a, memory_map_region_permissions_enum b) { return a + to_string(b); });
    return ret;
  }

  memory_map_region_t::memory_map_region_t(range_type range, memory_map_region_type_enum type)
      : m_range(::std::move(range)), m_type(type)
  {
  }
  auto memory_map_region_t::path() const -> ::std::string
  {
    return m_path;
  }
  void memory_map_region_t::set_path(::std::string path)
  {
    m_path = ::std::move(path);
  }
  ::std::string to_string(const memory_map_region_t &region)
  {
    ::std::stringstream ss;
    ss << region.range();
    auto ret = ss.str() + " " + to_string(region.permissions()) + " " + ::std::to_string(region.offset()) + " " +
               to_string(region.type()) + " " + region.path();
    return ret;
  }
}
