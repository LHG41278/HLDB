set(INSTALL_GTEST ON CACHE BOOL "Google Test Install")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

set(HWY_ENABLE_TESTS OFF CACHE BOOL "Highway Tests")
set(HWY_ENABLE_CONTRIB OFF CACHE BOOL "Highway Contrib")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/highway)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/highway)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/asio/asio/include)
