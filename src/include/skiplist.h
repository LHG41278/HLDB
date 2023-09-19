#include <atomic>
#include <optional>
#include <vector>
#include "status.h"

namespace hldb {
    #define MAX_HEIGHT 12

template <typename KeyType>
struct Node {
    const KeyType key;
    std::atomic<Node *> next{};

    explicit Node (const KeyType &OtherKey) : key{OtherKey} {}
    Node (KeyType &&OtherKey) : key{std::move(OtherKey)} {}

    void setNext(Node *next);

    Node *Next();

};


template <typename KeyType>
void Node<KeyType>::setNext(Node *next_ptr) {
    next.store(next_ptr, std::memory_order_release);
}

template <typename KeyType>
Node<KeyType>* Node<KeyType>::Next() {
    next.load(std::memory_order_acquire);
}

template <typename KeyType, typename ValueType, typename KeyComparator>
class SkipList {
public:
    SkipList() = delete;

    explicit SkipList(const KeyComparator &comp) {
        comparator = comp;
        skipHead = buildNode();
    }

    status_t Insert(const KeyType &key, const ValueType &value);

    status_t Update(const KeyType &key, const ValueType &value);

    status_t Delete(const KeyType &key);

private:
    struct SkipListNode {
        bool active;
        const ValueType value;
        SkipListNode *next;
        Node<KeyType> node[1];
    };
    std::atomic<int32_t> max_height{};
    KeyComparator comparator;
    SkipListNode* skipHead;

    SkipListNode* buildNode();

    void releaseNode(SkipListNode *ptr);

    // return the target skip list node and the height of the result
    std::pair<SkipListNode *, uint64_t> findLastLessOrEqualThan(const KeyType & key);
};

template <typename KeyType, typename ValueType, typename KeyComparator>
status_t SkipList<KeyType, ValueType, KeyComparator>::Insert(const KeyType &key, const ValueType &value) {
    struct SkipPrev {
        SkipListNode * levelNode{};
        uint64_t height{};
    };

    SkipPrev prev[MAX_HEIGHT];
    
}
}




// template <typename KeyType, typename ValueType, typename KeyComparator>
