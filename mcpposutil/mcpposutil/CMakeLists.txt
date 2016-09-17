include_directories(../mcpputil/mcpputil/include)
include_directories(include)
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_compile_options(-fPIC)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")



IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  list (APPEND SRC_FILES src/memory_sections_linux.cpp)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_library(mcpposutil ${SRC_FILES})
