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
EXAMPLE_DIR = examples

# Files
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SOURCES))
SOURCES = $(wildcard $(SRC_DIR)/*.c)
TEST_SOURCE = $(wildcard  $(TESTS_DIR)/*.c)
TEST_EXEC = $(EXEC_DIR)/test

# Target build

TARGET = $(BUILD_DIR)/bitset.a

# main targets

all: clean $(TARGET)

rebuild: clean all

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR)

test: build_test_asan
	./$(TEST_EXEC)
	@rm -f $(TEST_EXEC)

# precompile targets

build_test_noasan: $(TARGET) $(TEST_SOURCE)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $(TEST_SOURCE) $(TARGET) -o $(TEST_EXEC)

build_test_asan: $(TARGET) $(TEST_SOURCE)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(TEST_SOURCE) $(TARGET) -o $(TEST_EXEC)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# valgrind targets

valgrind: build_test_noasan
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)
	@rm -f $(TEST_EXEC)

# making folders

$(BUILD_DIR):
	@mkdir build

# clang-formatter targets

clang-check:
	@clang-format --style=google -n src/*.c examples/*.c src/*.h tests/*.c

clang-format:
	@clang-format --style=google -i src/*.c examples/*.c src/*.h tests/*.c
