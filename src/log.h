#include <iostream>
#include <mutex>

static std::mutex log_mutex; 

template <typename ... Types>
void LogDebug(Types ... args) {
    std::lock_guard<std::mutex> raii_lock{log_mutex};
    (std::cout << ... << args);
    std::cout << '\n';
}