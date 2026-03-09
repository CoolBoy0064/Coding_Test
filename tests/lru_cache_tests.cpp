/*
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
*/

#include "tests.h"
#include "LRUCache.tpp"

#include <type_traits>
#include <string>
#include <utility>

// =============================================================================
// 1. Default constructor is deleted
// =============================================================================
bool test_default_ctor_deleted() {
    return !std::is_default_constructible_v<LRUCache<int, int>>;
}

// =============================================================================
// 2. Explicit constructor
// =============================================================================
bool test_explicit_constructor() {
    // Not implicitly convertible from size_t (explicit keyword works)
    bool is_explicit = !std::is_convertible_v<std::size_t, LRUCache<int, int>>;
    // But IS directly constructible from size_t
    bool is_constructible = std::is_constructible_v<LRUCache<int, int>, std::size_t>;
    return is_explicit && is_constructible;
}

// =============================================================================
// 3. Copy constructor
// =============================================================================
bool test_copy_constructor() {
    return std::is_copy_constructible_v<LRUCache<int, int>>;
}

// =============================================================================
// 4. Move constructor
// =============================================================================
bool test_move_constructor() {
    return std::is_move_constructible_v<LRUCache<int, int>>;
}

// =============================================================================
// 5. Destructor
// =============================================================================
bool test_destructor() {
    return std::is_destructible_v<LRUCache<int, int>>;
}

// =============================================================================
// 6. Copy assignment operator
// =============================================================================
bool test_copy_assignment() {
    return std::is_copy_assignable_v<LRUCache<int, int>>;
}

// =============================================================================
// 7. Move assignment operator
// =============================================================================
bool test_move_assignment() {
    return std::is_move_assignable_v<LRUCache<int, int>>;
}

// =============================================================================
// 8. size() returns a value
// =============================================================================
bool test_size_returns_value() {
    LRUCache<int, int> cache(3);
    if (cache.size() != 0) return false;
    cache.put(1, 100);
    if (cache.size() != 1) return false;
    cache.put(2, 200);
    if (cache.size() != 2) return false;
    return true;
}

// =============================================================================
// 9. capacity() returns a value
// =============================================================================
bool test_capacity_returns_value() {
    LRUCache<int, int> cache(5);
    return cache.capacity() == 5;
}

// =============================================================================
// 10. Put a single item and get it back
// =============================================================================
bool test_put_and_get_single() {
    LRUCache<int, std::string> cache(3);
    cache.put(1, "hello");
    auto* val = cache.get(1);
    return val != nullptr && *val == "hello";
}

// =============================================================================
// 11. Get on a nonexistent key returns nullptr
// =============================================================================
bool test_get_nonexistent_returns_nullptr() {
    LRUCache<int, int> cache(3);
    cache.put(1, 100);
    return cache.get(42) == nullptr;
}

// =============================================================================
// 12. Put overwrites an existing key's value
// =============================================================================
bool test_put_overwrites_existing() {
    LRUCache<int, int> cache(3);
    cache.put(1, 100);
    cache.put(1, 999);
    auto* val = cache.get(1);
    return val != nullptr && *val == 999 && cache.size() == 1;
}

// =============================================================================
// 13. Eviction when capacity is exceeded
// =============================================================================
bool test_eviction_at_capacity() {
    LRUCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);  // Should evict key 1 (LRU)

    return cache.get(1) == nullptr
        && cache.get(2) != nullptr && *cache.get(2) == 200
        && cache.get(3) != nullptr && *cache.get(3) == 300
        && cache.size() == 2;
}

// =============================================================================
// 14. Get promotes a node so it doesn't get evicted
// =============================================================================
bool test_get_promotes_node() {
    LRUCache<int, int> cache(2);
    cache.put(1, 100);
    cache.put(2, 200);
    cache.get(1);       // Promote key 1 — now key 2 is LRU
    cache.put(3, 300);  // Should evict key 2

    return cache.get(2) == nullptr
        && cache.get(1) != nullptr && *cache.get(1) == 100
        && cache.get(3) != nullptr && *cache.get(3) == 300;
}

// =============================================================================
// 15. contains() returns true for existing key
// =============================================================================
bool test_contains_true() {
    LRUCache<std::string, int> cache(3);
    cache.put("alpha", 1);
    cache.put("beta", 2);
    return cache.contains("alpha") && cache.contains("beta");
}

// =============================================================================
// 16. contains() returns false after eviction
// =============================================================================
bool test_contains_false_after_eviction() {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);  // Evicts key 1
    return !cache.contains(1) && cache.contains(2) && cache.contains(3);
}

// =============================================================================
// 17. Multiple evictions in sequence
// =============================================================================
bool test_put_multiple_evictions() {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);  // Evicts 1
    cache.put(4, 40);  // Evicts 2

    return cache.get(1) == nullptr
        && cache.get(2) == nullptr
        && cache.get(3) != nullptr && *cache.get(3) == 30
        && cache.get(4) != nullptr && *cache.get(4) == 40
        && cache.size() == 2;
}

// =============================================================================
// 18. Capacity of 1 — every new put evicts
// =============================================================================
bool test_capacity_one() {
    LRUCache<int, int> cache(1);
    cache.put(1, 100);
    if (cache.size() != 1 || cache.get(1) == nullptr) return false;

    cache.put(2, 200);  // Evicts 1
    if (cache.get(1) != nullptr) return false;
    if (cache.get(2) == nullptr || *cache.get(2) != 200) return false;

    cache.put(3, 300);  // Evicts 2
    if (cache.get(2) != nullptr) return false;
    if (cache.get(3) == nullptr || *cache.get(3) != 300) return false;

    return cache.size() == 1;
}

// =============================================================================
// 19. Copy constructor produces an independent cache
// =============================================================================
bool test_copy_is_independent() {
    LRUCache<int, int> original(3);
    original.put(1, 100);
    original.put(2, 200);

    LRUCache<int, int> copy(original);

    // Verify copy has same data
    if (copy.size() != 2 || copy.capacity() != 3) return false;
    if (copy.get(1) == nullptr || *copy.get(1) != 100) return false;
    if (copy.get(2) == nullptr || *copy.get(2) != 200) return false;

    // Mutate the copy — original should be unaffected
    copy.put(3, 300);
    copy.put(1, 999);

    if (original.get(1) == nullptr || *original.get(1) != 100) return false;
    if (original.contains(3)) return false;

    return true;
}

// =============================================================================
// 20. Move constructor leaves source empty
// =============================================================================
bool test_move_leaves_source_empty() {
    LRUCache<int, int> original(3);
    original.put(1, 100);
    original.put(2, 200);

    LRUCache<int, int> moved(std::move(original));

    // Moved-to cache should have the data
    if (moved.size() != 2 || moved.capacity() != 3) return false;
    if (moved.get(1) == nullptr || *moved.get(1) != 100) return false;
    if (moved.get(2) == nullptr || *moved.get(2) != 200) return false;

    // Source should be empty
    if (original.size() != 0 || original.capacity() != 0) return false;

    return true;
}