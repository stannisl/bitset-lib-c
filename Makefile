# Compiler & options
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
ASAN_FLAGS = -fsanitize=address -g

# Libs
LIBS = 

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects
EXEC_DIR = $(BUILD_DIR)/executables
TESTS_DIR = tests
SRC_DIR = src
SRC_DIRS = $(SRC_DIR)/bitset $(SRC_DIR)/output
EXAMPLE_DIR = examples

# Files
SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_SOURCE = $(wildcard $(TESTS_DIR)/*.c)
TEST_EXEC = $(EXEC_DIR)/test

# Target build
TARGET = $(BUILD_DIR)/bitset.a

# Main targets
all: clean $(TARGET) main

rebuild: clean all

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR) main

main: clean $(TARGET)
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(TARGET) -o main
	./main

test: build_test_asan
	./$(TEST_EXEC)
	@rm -f $(TEST_EXEC)

# Precompile targets
build_test_noasan: $(TARGET) $(TEST_SOURCE)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $(TEST_SOURCE) $(TARGET) -o $(TEST_EXEC)

build_test_asan: $(TARGET) $(TEST_SOURCE)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(TEST_SOURCE) $(TARGET) -o $(TEST_EXEC)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Valgrind targets
valgrind: build_test_noasan
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)
	@rm -f $(TEST_EXEC)

# Making folders
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clang-formatter targets
clang-check:
	@clang-format --style=google -n $$(find . -name "*.c")
	@clang-format --style=google -n $$(find . -name "*.h")

clang-format:
	@clang-format --style=google -i $$(find . -name "*.c")
	@clang-format --style=google -i $$(find . -name "*.h")
