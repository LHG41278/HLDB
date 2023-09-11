#include <iostream>
#include <mutex>

static std::mutex log_mutex;

// Multiple Thread Log
template <typename... Types>
void LogDebugMT(Types... args)
{
    std::lock_guard<std::mutex> raii_lock{ log_mutex };
    (std::cout << ... << args);
    std::cout << '\n';
}

// Single Thread Log
template <typename... Types>
void LogDebug(Types... args)
{
    (std::cout << ... << args);
    std::cout << '\n';
}
