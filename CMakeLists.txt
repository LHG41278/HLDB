cmake_minimum_required(VERSION 3.20.0)
project(HLDB VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)

include(CPack)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_module;${CMAKE_MODULE_PATH}")

include(FetchContent)
include(googletest)
include(iuring)

add_subdirectory(src)