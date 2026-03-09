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
    // *****************************
    // YOUR IMPLEMENTATION GOES HERE
    // *****************************

    // You should change parts of this or add to it *hint hint*
    struct Node {
        Key key;
        Value value;
    };

    // THE TEST CODE WILL NOT COMPILE UNTIL YOU COMPLETE OR STUB OUT EVERYTHING

    // Remove the instruction comments as you complete them  

    /*** Constructors and Destructors ***/
    // Delete the default constructor
    // Create an explict constructor that takes a std::size_t for the capacity

    // Implement a copy constructor

    // Implement a move constructor

    // Implement a destructor

    /*** Operator Overloads ***/
    // Implement a copy assignment operator
    // Implement a move assignmnet operator

    /*** Public Functions ***/
    std::size_t size() const { 
        // Implement
    }

    std::size_t capacity() const {
        // Implement
    }

    bool contains(const Key& key) const {
        // Implement     
    }

    Value* get(const Key& key) {
        // Implement
    }

    void put(const Key& key, const Value& value) {
        // Implement
    }

private:
    // Put member variables and helper functions here
};


#endif // _CORE_LRU_CACHE_H_
