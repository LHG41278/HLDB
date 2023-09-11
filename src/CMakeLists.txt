set(CMAKE_PROJECT_NAME HLDB)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true include/*.h *.cpp test/*.cpp)

enable_testing()

add_executable(DBRUN ${SOURCES})

add_library(DBLIB ${SOURCES})

target_include_directories(DBRUN PRIVATE ./include/)
