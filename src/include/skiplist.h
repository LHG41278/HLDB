#include <atomic>
#include <vector>

#define MAX_HEIGHT

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
    SkipList() {

    }

private:
    std::atomic<int32_t> max_height{};
    KeyComparator comparator;
    std::atomic<Node<KeyType> *> headArray[MAX_HEIGHT];

    struct SkipListNode {
        bool active;
        const ValueType value;
        SkipListNode *next;
        Node<KeyType> node[1];
    };

    
};


// template <typename KeyType, typename ValueType, typename KeyComparator>
