#include <iostream>
#include <mutex>
namespace hldb
{
    // to be replaced cuz it is ugly
    // suggested libspd or format

    // that could NOT BE STATIC!!!
    // [[maybe_unused]] volatile std::mutex log_mutex; removed
    // Concurrent access to a synchronized (§27.5.3.4) standard iostream 
    // object’s formatted and unformatted input (§27.7.2.1) and 
    // output (§27.7.3.1) functions or a standard C stream by multiple threads 
    // shall not result in a data race (§1.10). [ Note: Users must still 
    // synchronize concurrent use of these objects and streams by multiple threads
    //  if they wish to avoid interleaved characters. — end note ]
    
    // Multiple Thread Log
    template <typename... Types>
    static inline void          // get it to a rv-ref  to incrase performance
    LogDebugMT(Types&&... args) // add static inline to incrase performance
    {
        // std::lock_guard<std::mutex> raii_lock{ log_mutex };
        //forward...
        std::clog.operator<<(std::forward(args)...) << std::endl;
        // std::clog << '\n'; stay in here for attetion to MUST NOT USE c-stly \n
        // because it is NOT PORTABLE due to locale
    }

    // Single Thread Log
    template <typename... Types>
    static inline void LogDebug(Types&&... args)
    {
        std::clog.operator<<(std::forward(args)...) << std::endl;
    }
} // namespace hldb
