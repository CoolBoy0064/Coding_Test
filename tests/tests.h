/*
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
*/

#ifndef _TESTS_H_
#define _TESTS_H_

#include <string_view>
#include <iostream>

// =============================================================================
// Tests
// =============================================================================


// 1-7: Type trait / constructor tests
bool test_default_ctor_deleted();
bool test_explicit_constructor();
bool test_copy_constructor();
bool test_move_constructor();
bool test_destructor();
bool test_copy_assignment();
bool test_move_assignment();

// 8-9: size() and capacity()
bool test_size_returns_value();
bool test_capacity_returns_value();

// 10-20: LRUCache behavior tests
bool test_put_and_get_single();
bool test_get_nonexistent_returns_nullptr();
bool test_put_overwrites_existing();
bool test_eviction_at_capacity();
bool test_get_promotes_node();
bool test_contains_true();
bool test_contains_false_after_eviction();
bool test_put_multiple_evictions();
bool test_capacity_one();
bool test_copy_is_independent();
bool test_move_leaves_source_empty();

// =============================================================================
// Helper Functions
// =============================================================================
bool test_helper(std::string_view expected, std::string_view result);

#endif  // _TESTS_H_