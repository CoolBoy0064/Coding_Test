#include "tests.h"
#include "timer.hpp"


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

    // =============================================================================
    // Tests
    // =============================================================================

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