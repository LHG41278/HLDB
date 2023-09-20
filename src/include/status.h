#include <iostream>
namespace hldb
{
    //suggest to use exception.
    enum class status_t // renamed due to be in a same naming way as "page_t"
    {
        Normal,
        FileReadError,
        MemoryAllocationError,
        DeleteKeyNotFound,
        InsertError        
    };
} // namespace hldb
