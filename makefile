# ----- Project -----
TEST_TARGET := test_runner
CXX := g++
WARN := -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror
STD := -std=c++20
OPT := -O2
DEP := -MMD -MP
INCLUDES := -Icore -Itests

# ----- File Extensions -----
CXX_EXT := cpp

# ----- makefile Config -----
MAKEFLAGS += --no-print-directory


# ----- Directories -----
OBJDIR := obj
TESTDIR := tests
TEST_OBJDIR := $(TESTDIR)/obj
TEST_BINDIR := $(TESTDIR)/bin

# ----- Source & Dependencies -----
CORE_SRCS := $(wildcard core/*.$(CXX_EXT))  
TEST_SRCS := $(wildcard $(TESTDIR)/*.$(CXX_EXT))

CORE_OBJS := $(patsubst %.$(CXX_EXT),$(OBJDIR)/%.o,$(CORE_SRCS))
TEST_OBJS := $(patsubst $(TESTDIR)/%.$(CXX_EXT),$(TEST_OBJDIR)/%.o,$(TEST_SRCS))

CORE_DEPS := $(CORE_OBJS:.o=.d) 
TEST_DEPS := $(TEST_OBJS:.o=.d)

# ----- Flags -----
CXXFLAGS := $(STD) $(WARN) $(OPT) $(DEP) $(INCLUDES)
LDFLAGS := 

# ----- Object Directory -----
$(OBJDIR)/%.o: %.$(CXX_EXT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# ----- Test Object Directory -----
$(TEST_OBJDIR)/%.o: $(TESTDIR)/%.$(CXX_EXT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# ----- Test Executable -----
$(TEST_BINDIR)/$(TEST_TARGET): $(TEST_OBJS) $(CORE_OBJS)
	@mkdir -p $(TEST_BINDIR)
	@$(CXX) $(TEST_OBJS) $(CORE_OBJS) -o $@ $(LDFLAGS)

# ----- Commands -----
.PHONY: run clean help

run: $(TEST_BINDIR)/$(TEST_TARGET)
	@echo "[makefile] Running tests..."
	@./$(TEST_BINDIR)/$(TEST_TARGET)

clean:
	@echo "[makefile] Cleaning build artifacts..."
	@rm -rf obj $(TEST_OBJDIR) $(TEST_BINDIR)

help:
	@echo "Usage: make <target>"
	@echo
	@echo "Targets:"
	@echo "  run    Build everything and run all tests"
	@echo "  clean  Remove all build artifacts"
	@echo "  help   Show this dialog"

# ----- Include dependencies if present -----
-include $(CORE_DEPS) $(TEST_DEPS)