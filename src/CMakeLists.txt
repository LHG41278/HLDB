file(GLOB SOURCES LIST_DIRECTORIES ON ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(hldb SHARED ${SOURCES})

add_executable(hldbapp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(hldbapp hldb)

add_subdirectory(test)
