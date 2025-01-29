# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(SRC_DIR)

# Source files
SRC_DIR = src
TEST_DIR = tests
CORE_SRC = $(SRC_DIR)/sha1.c # Core SHA-1 logic
MAIN = $(SRC_DIR)/main.c          # Main application
TEST_SRC = $(TEST_DIR)/sha1_pad_test.c

# Output executables
MAIN_EXEC = sha1
TEST_EXEC = sha1_pad_test

# Default target: Build the main application
all: $(MAIN_EXEC)

# Build the main application
$(MAIN_EXEC): $(MAIN) $(CORE_SRC)
	$(CC) $(CFLAGS) -o $(MAIN_EXEC) $(MAIN) $(CORE_SRC)

# Build and run the test executable
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC) $(CORE_SRC)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_SRC) $(CORE_SRC)

# Clean up compiled files
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)
