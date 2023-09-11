file(GLOB SOURCES LIST_DIRECTORIES ON ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(hldb SHARED ${SOURCES})
add_executable(hldbapp hldb ${SOURCES})
add_subdirectory(test)
