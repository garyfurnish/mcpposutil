#pragma once
#include <mcpputil/mcpputil/memory_range.hpp>
#include <vector>
namespace mcpposutil
{
  enum class memory_map_region_permissions_enum : uint8_t {
    none,
    read,
    write,
    execute,
    shared,
    private_,

  };
  enum class memory_map_region_type_enum : uint8_t {
    none,
    normal,
    stack,
    thread_stack,
    vdso,
    vvar,
    vsyscall,
    heap,

  };
  [[nodiscard]] extern ::std::string to_string(memory_map_region_type_enum);
  [[nodiscard]] extern ::std::string to_string(memory_map_region_permissions_enum);
  [[nodiscard]] extern ::std::string to_string(::std::vector<memory_map_region_permissions_enum>);
  [[nodiscard]] extern memory_map_region_permissions_enum memory_map_region_permission_from_string(char);
  [[nodiscard]] extern ::std::vector<memory_map_region_permissions_enum>
  memory_map_region_permissions_from_string(const ::std::string &);
  /**
   * \brief Memory map region.
   **/
  class memory_map_region_t
  {
  public:
    /**
     * \brief Type of memory pointer.
     **/
    using memory_pointer_type = uint8_t *;
    /**
     * \brief Type of memory range.
     **/
    using range_type = mcpputil::memory_range_t<memory_pointer_type>;
    /**
     * \brief Constructor.
     *
     * @param range Memory range.
     * @param type Type of memory region.
     **/
    memory_map_region_t(range_type range, memory_map_region_type_enum type);
    memory_map_region_t(const memory_map_region_t &) = default;
    memory_map_region_t(memory_map_region_t &&) noexcept = default;
    memory_map_region_t &operator=(const memory_map_region_t &) = default;
    memory_map_region_t &operator=(memory_map_region_t &&) noexcept = default;
    /**
     * \brief Beginning of memory range.
     **/
    auto begin() noexcept;
    /**
     * \brief Beginning of memory range.
     **/
    auto begin() const noexcept;
    /**
     * \brief End of memory range.
     **/
    auto end() noexcept;
    /**
     * \brief End of memory range.
     **/
    auto end() const noexcept;
    auto range() noexcept;
    auto range() const noexcept;
    auto &permissions() noexcept;
    auto &permissions() const noexcept;
    auto type() const noexcept -> memory_map_region_type_enum;
    auto path() const -> ::std::string;
    auto offset() const noexcept -> size_t;
    void set_offset(size_t offset) noexcept;
    void set_path(::std::string path);

  private:
    range_type m_range;
    size_t m_offset;
    ::std::vector<memory_map_region_permissions_enum> m_permissions;
    memory_map_region_type_enum m_type;
    ::std::string m_path;
  };
  [[nodiscard]] extern ::std::string to_string(const memory_map_region_t &);
}
#include "memory_map_region_impl.hpp"
