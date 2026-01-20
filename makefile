# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -I./src -I./src/helpers -I./src/engine -I./src/ui -I./src/validators -I./src/config

# Linker flags
LDFLAGS = -lncurses

# Source files (recursive)
SRCS := $(shell find src -name '*.c')

# Object files
OBJS := $(SRCS:.c=.o)

# Target executable
TARGET = linuxplus-learn

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile C files into objects
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
