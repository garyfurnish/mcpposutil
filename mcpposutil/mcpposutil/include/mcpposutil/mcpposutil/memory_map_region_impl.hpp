#pragma once
#include "memory_map_region.hpp"
namespace mcpposutil
{
  inline auto memory_map_region_t::range() noexcept
  {
    return m_range;
  }
  inline auto memory_map_region_t::range() const noexcept
  {
    return m_range;
  }
  inline auto memory_map_region_t::begin() noexcept
  {
    return range().begin();
  }
  inline auto memory_map_region_t::begin() const noexcept
  {
    return range().begin();
  }
  inline auto memory_map_region_t::end() noexcept
  {
    return range().end();
  }
  inline auto memory_map_region_t::end() const noexcept
  {
    return range().end();
  }
  inline auto &memory_map_region_t::permissions() noexcept
  {
    return m_permissions;
  }
  inline auto &memory_map_region_t::permissions() const noexcept
  {
    return m_permissions;
  }
  inline auto memory_map_region_t::type() const noexcept -> memory_map_region_type_enum
  {
    return m_type;
  }
  inline auto memory_map_region_t::offset() const noexcept -> size_t
  {
    return m_offset;
  }
  inline void memory_map_region_t::set_offset(size_t offset) noexcept
  {
    m_offset = offset;
  }
}
