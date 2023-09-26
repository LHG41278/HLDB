#include <algorithm>
#include <atomic>
#include <exception>
#include <optional>
#include <vector>
#include <random>
#include "log.h"
#include "memory_pool.h"
#include "status.h"

namespace hldb {
    #define MAX_HEIGHT 12

template <typename KeyType, typename ValueType, typename KeyComparator>
class SkipList {
public:
    SkipList() = delete;

    explicit SkipList(const KeyComparator &comp) : re{rd()}, uni_dist(1,MAX_HEIGHT) {                
        head = buildNode(MAX_HEIGHT);
        comparator = comp;
    }

    status_t Insert(const KeyType &key, const ValueType &value);

    status_t Update(const KeyType &key, const ValueType &value);

    status_t Delete(const KeyType &key);

    void Print() {
        Node *iter = head->Next(1).value_or(nullptr);
        
        while (iter != nullptr) {
          std::cout << " key : " << iter->key
                    << " height : " << iter->height << std::endl;
          
          iter = iter->Next(1).value_or(nullptr);
        }
        std::cout << std::endl;
    }


private:
    struct Node {
        bool active;
        KeyType key;
        ValueType value;
        uint16_t height;
        std::atomic<Node *> next[1];

        bool setNext(int ext_height, Node *nextPtr) {
            if (ext_height > height) {
                return false;
            }

            next[ext_height - 1].store(nextPtr, std::memory_order_release);
            return true;
        }

        std::optional<Node *> Next(int ext_height) {
            if (ext_height > height) {
                return std::nullopt;
            }

            return next[ext_height - 1].load(std::memory_order_acquire);
        }
    };

    Node *head;
    std::atomic<uint32_t> max_height{};
    KeyComparator comparator;
    std::random_device rd;
    std::default_random_engine re;
    std::uniform_int_distribution<int> uni_dist;
    MemoryPool memory_pool;

    uint32_t randomHeight();    

    Node *buildNode(uint64_t ran_hei) {
        auto node =  static_cast<Node *>(memory_pool.AlignMemory( sizeof(Node) + 
              sizeof(std::atomic<Node *>) * (ran_hei - 1)));
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
        auto afterHead = head->Next(height).value_or(nullptr);
        if (result == head && afterHead != nullptr && comparator(key, afterHead->key) > 0) {
            result = head->Next(height).value();
        }

        while (result->Next(height).value_or(nullptr) != nullptr && comparator(key, result->key) <= 0) {
            result = result->Next(height).value_or(nullptr);
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

    for (int i = random_height; i >= 1; i--) {
        if (i != random_height) [[likely]] {
            prev[i - 1] = prev[i];
        } else {
            prev[i - 1] = head;
        }

        prev[i - 1] = findLastLessOrEqualThan(prev[i - 1], key, i);
    }

    Node *newNode = buildNode(random_height);
    newNode->key = key;
    newNode->value = value;

    for (int i = 1; i <= random_height; i++) {
        std::optional<Node *> nextPtr = prev[i - 1]->Next(i);

        bool success = newNode->setNext(i, nextPtr.value_or(nullptr));
        if (!success) {
            return status_t::InsertError;
        }

        success = prev[i - 1]->setNext(i, newNode);
        if (!success) {
            return status_t::InsertError;
        }
    }

    return status_t::Normal;
}

template <typename KeyType, typename ValueType, typename KeyComparator>
status_t SkipList<KeyType, ValueType, KeyComparator>::Delete(const KeyType &key) {
    int32_t search_height = MAX_HEIGHT - 1;
    Node *result = head->next[search_height];
    while (comparator(result->key, key) != 0 && search_height >= 0) {
        result = findLastLessOrEqualThan(result, key, search_height);        
        search_height--;
    }
    
    if (comparator(result->key, key) != 0) {
        return status_t::DeleteKeyNotFound;
    }

    result->active = false;

    return status_t::Normal;
}

template <typename KeyType, typename ValueType, typename KeyComparator>
status_t SkipList<KeyType, ValueType, KeyComparator>::Update(const KeyType& key, const ValueType &value) {
    status_t stat;
    stat = Delete(key);
    if (stat != status_t::Normal) {
        return stat;
    }

    stat = Insert(key, value);
    if (stat != status_t::Normal) {
        return stat;
    }

    return status_t::Normal;
}
}

// template <typename KeyType, typename ValueType, typename KeyComparator>
