#include <atomic>
#include <exception>
#include <optional>
#include <vector>
#include <random>
#include "memory_pool.h"
#include "status.h"

namespace hldb {
    #define MAX_HEIGHT 12

template <typename KeyType, typename ValueType, typename KeyComparator>
class SkipList {
public:
    SkipList() = delete;

    explicit SkipList(const KeyComparator &comp) : re{rd()}, uni_dist(1,MAX_HEIGHT) {                
        comparator = comp;
    }

    status_t Insert(const KeyType &key, const ValueType &value);

    status_t Update(const KeyType &key, const ValueType &value);

    status_t Delete(const KeyType &key);

private:
    struct Node {
        bool active;
        const KeyType key;
        const ValueType value;
        const uint16_t height;
        std::atomic<Node *> next[1];

        bool setNext(int ext_height, Node *next) {
            if (ext_height > height) {
                return false;
            }

            next[ext_height - 1].store(next, std::memory_order_release);
            return true;
        }

        std::optional<Node *> Next(int ext_height) {
            if (ext_height > height) {
                return std::nullopt;
            }

            return next[ext_height - 1].load(std::memory_order_acquire);
        }
    };

    Node *head[MAX_HEIGHT];
    std::atomic<uint32_t> max_height{};
    KeyComparator comparator;
    std::random_device rd;
    std::default_random_engine re;
    std::uniform_int_distribution<int> uni_dist;
    MemoryPool memory_pool;

    uint32_t randomHeight();    

    Node *buildNode(uint64_t ran_hei) {
        auto node =  static_cast<Node *>(memory_pool.AlignMemory(sizeof(bool) + 
                sizeof(KeyType) + sizeof(ValueType) + 
                sizeof(uint64_t) + sizeof(std::atomic<Node *>) * ran_hei));
        node->height = ran_hei;
        return node;
    }
 
    void releaseNode(Node *ptr) {
        memory_pool.FreeMemory(ptr);
    }

    Node *findLastLessOrEqualThan(Node *start ,const KeyType &key, uint32_t height) {
        if (start == nullptr) {
            return nullptr;
        }
        Node *result = start;

        while (result->Next(height) != nullptr && comparator(key, result->key) < 0) {
            result = result->Next(height);
        }

        return result;
    }    
};


template <typename KeyType, typename ValueType, typename KeyComparator>
uint32_t SkipList<KeyType, ValueType, KeyComparator>::randomHeight() {
    return uni_dist(re);
}

template <typename KeyType, typename ValueType, typename KeyComparator>
status_t SkipList<KeyType, ValueType, KeyComparator>::Insert(const KeyType &key, const ValueType &value) {
    Node *prev[MAX_HEIGHT];
    uint32_t random_height = randomHeight();

    max_height.load(std::memory_order_relaxed);
    if (random_height > max_height) {
        max_height.store(random_height, std::memory_order_relaxed);
    }

    for (int i = random_height - 1; i >= 0; i--) {
        if (i != random_height - 1) [[likely]] {
            prev[i] = prev[i + 1];
        } else {
            prev[i] = head;
        }

        prev[i] = findLastLessOrEqualThan(prev[i], key, i);
    }

    Node *newNode = buildNode(random_height);
    for (int i = 0; i < random_height; i++) {
        bool success = newNode->setNext(i, prev[i]->Next(i));
        if (success) {
            return status_t::MemoryAllocationError;
        }
        success = prev[i]->setNext(i, newNode);
        if (success) {
            return status_t::MemoryAllocationError;
        }
    }

    return status_t::Normal;
}
}

// template <typename KeyType, typename ValueType, typename KeyComparator>
