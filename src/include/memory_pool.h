#include <memory>
#include <cstdlib>

class MemoryPool {
// TODO
// make it allocate the memory as we wish
public:
    void *AlignMemory(uint64_t bytes) {
        return std::malloc(bytes);
    }

    void FreeMemory(void *ptr) {
        std::free(ptr);
    }

private:
// TODO
// embed a memory pool in this object to align the memory
// make it extendible but with a finite memory(the size of pool can't grow infinitly)
};