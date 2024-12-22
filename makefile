# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Executable and source files
TARGET = sha1
SRCS = src/sha1.c

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up compiled files
clean:
	rm -f $(TARGET)
