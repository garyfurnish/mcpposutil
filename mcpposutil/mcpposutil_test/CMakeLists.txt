include_directories(../../mcpputil/include/)
include_directories(../mcpposutil/include/)
find_path(BANDIT_INCLUDE_PATH bandit/bandit.h PATHS ../../bandit)
include_directories(${BANDIT_INCLUDE_PATH})
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_compile_options(-fPIE)
ENDIF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_executable(mcpputil_test
  main.cpp
  )
target_link_libraries(mcpputil_test)
