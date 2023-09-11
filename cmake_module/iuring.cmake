FetchContent_Declare(
    iuring
    GIT_REPOSITORY https://github.com/axboe/liburing.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/iuring
)

FetchContent_MakeAvailable(iuring)