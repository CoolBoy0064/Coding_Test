/*
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
DO NOT CHANGE THIS FILE
*/

#include "tests.h"
#include "timer.hpp"
#include "iomanip"


static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

static const char* GREEN = "\033[32m";
static const char* RED = "\033[31m";
static const char* CYAN = "\033[36m";
static const char* RESET = "\033[0m";

void Run(bool (*test)(), std::string_view name) {
    total_tests++;
    Timer timer;

    std::cout << CYAN << "[TEST] " << RESET << std::left << std::setw(40) << name;

    timer.Start();
    bool result = test();
    timer.Stop();

    if (result) {
        passed_tests++;
        std::cout << GREEN << "[PASS]" << RESET;
    } else {
        failed_tests++;
        std::cout << RED   << "[FAIL]" << RESET;
    }

    std::cout << "  " << timer.ElapsedStr() << "\n";
}

int main(int argc, char* argv[]) {

    (void)argc;
    (void)argv;

    std::cout << "========================================\n";
    std::cout << "Running Tests\n";
    std::cout << "========================================\n";

    Run(test_default_ctor_deleted,       "Default ctor deleted");
    Run(test_explicit_constructor,       "Explicit constructor");
    Run(test_copy_constructor,           "Copy constructor");
    Run(test_move_constructor,           "Move constructor");
    Run(test_destructor,                 "Destructor");
    Run(test_copy_assignment,            "Copy assignment operator");
    Run(test_move_assignment,            "Move assignment operator");

    Run(test_size_returns_value,         "size() returns value");
    Run(test_capacity_returns_value,     "capacity() returns value");

    Run(test_put_and_get_single,         "Put and get single item");
    Run(test_get_nonexistent_returns_nullptr, "Get nonexistent returns nullptr");
    Run(test_put_overwrites_existing,    "Put overwrites existing key");
    Run(test_eviction_at_capacity,       "Eviction at capacity");
    Run(test_get_promotes_node,          "Get promotes node (no evict)");
    Run(test_contains_true,              "contains() true for existing");
    Run(test_contains_false_after_eviction, "contains() false after eviction");
    Run(test_put_multiple_evictions,     "Multiple sequential evictions");
    Run(test_capacity_one,               "Capacity of 1");
    Run(test_copy_is_independent,        "Copy is independent");
    Run(test_move_leaves_source_empty,   "Move leaves source empty");


    // =============================================================================
    // Test Summary
    // =============================================================================
    std::cout << "\n========================================\n";
    std::cout << "Test Summary\n";
    std::cout << "========================================\n";
    std::cout << "Total:  " << total_tests  << "\n";
    std::cout << GREEN << "Passed: " << passed_tests << RESET << "\n";
    std::cout << RED   << "Failed: " << failed_tests << RESET << "\n\n";
}

// =============================================================================
// Helper Functions
// =============================================================================
bool test_helper(std::string_view expected, std::string_view result) {
    if (result == expected) {
        return true;
    } else {
        std::cout << "\n" << RED << "  Expected: " << RESET << expected << "\n";
        std::cout         << RED << "  Got:      " << RESET << result   << "\n";
        return false;
    }
}