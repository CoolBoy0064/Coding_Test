#ifndef _CORE_LRU_CACHE_H_
#define _CORE_LRU_CACHE_H_

// Include any headers needed here
#include <cstdint>
#include <concepts>
#include <unordered_map>

// Do Not use std::list but you can make your own if needed


template <typename T>
concept Hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

template <Hashable Key, typename Value>
class LRUCache {
public:
    struct Node {
        Key key;
        Value value;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node(const Key& k, const Value& v)
            : key(k), value(v), prev(nullptr), next(nullptr) {}

        Node(Key&& k, Value&& v)
            : key(std::move(k)), value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    LRUCache() = delete;

    explicit LRUCache(std::size_t capacity)
        : capacity_(capacity), size_(0), head_(nullptr), tail_(nullptr) {
    }

    LRUCache(const LRUCache& other)
        : capacity_(other.capacity_), size_(0), head_(nullptr), tail_(nullptr) {
        for (Node* current = other.tail_; current != nullptr; current = current->prev) {
            put(current->key, current->value);
        }
    }

    LRUCache(LRUCache&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), head_(other.head_), tail_(other.tail_), cache_(std::move(other.cache_)) {
        other.capacity_ = 0;
        other.size_ = 0;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }

    ~LRUCache() {
        clear();
    }

    LRUCache& operator=(const LRUCache& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        capacity_ = other.capacity_;
        for (Node* current = other.tail_; current != nullptr; current = current->prev) {
            put(current->key, current->value);
        }
        return *this;
    }

    LRUCache& operator=(LRUCache&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        clear();
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
        cache_ = std::move(other.cache_);

        other.capacity_ = 0;
        other.size_ = 0;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        return *this;
    }

    std::size_t size() const { 
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    bool contains(const Key& key) const {
        return cache_.find(key) != cache_.end();
    }

    Value* get(const Key& key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            return nullptr;
        }
        Node* node = it->second;
        moveToHead(node);
        return &node->value;
    }

    void put(const Key& key, const Value& value) {
        if (capacity_ == 0) {
            return;
        }

        auto it = cache_.find(key);
        if (it != cache_.end()) {
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
            return;
        }

        if (size_ >= capacity_) {
            evictLRU();
        }

        Node* newNode = new Node(key, value);
        addToHead(newNode);
        cache_[key] = newNode;
        ++size_;
    }

private:
    std::size_t capacity_;
    std::size_t size_;
    Node* head_;
    Node* tail_;
    std::unordered_map<Key, Node*> cache_;

    void clear() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        cache_.clear();
    }

    void addToHead(Node* node) {
        node->prev = nullptr;
        node->next = head_;

        if (head_ != nullptr) {
            head_->prev = node;
        }
        head_ = node;

        if (tail_ == nullptr) {
            tail_ = node;
        }
    }

    void removeNode(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }

        node->prev = nullptr;
        node->next = nullptr;
    }

    void moveToHead(Node* node) {
        if (node == head_) {
            return;
        }
        removeNode(node);
        addToHead(node);
    }

    void evictLRU() {
        if (tail_ == nullptr) {
            return;
        }
        Node* toRemove = tail_;
        cache_.erase(toRemove->key);
        removeNode(toRemove);
        delete toRemove;
        --size_;
    }
};


#endif // _CORE_LRU_CACHE_H_
