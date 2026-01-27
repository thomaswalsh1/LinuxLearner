# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -g -I./src -I./src/helpers -I./src/engine -I./src/ui -I./src/validators -I./src/config
# Linker flags
LDFLAGS = -lncurses
# Source files (recursive)
SRCS := $(shell find src -name '*.c')
# Object files
OBJS := $(SRCS:.c=.o)
# Target executable
TARGET = linuxplus-learn
# Version
VERSION = 0.2.0
# Project name (use current directory name)
PROJECT_NAME = $(shell basename $(CURDIR))
# Release name
RELEASE_NAME = linuxlearner-v$(VERSION)

# Default target - just compile
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

# Create source distribution tarball
release-src: clean
	@echo "Creating source distribution..."
	cd .. && tar --exclude='.git' \
		--exclude='*.o' \
		--exclude='.vscode' \
		--exclude='*.swp' \
		--exclude='.DS_Store' \
		--exclude='*.tar.gz' \
		--exclude='labs_backup' \
		--exclude='resize.log' \
		--exclude='*.log' \
		--exclude='src/log' \
		--exclude='src/config/comparatorlogs.txt' \
		--exclude='labs/output.txt' \
		--transform='s,^$(PROJECT_NAME),$(RELEASE_NAME),' \
		-czf $(RELEASE_NAME)-source.tar.gz $(PROJECT_NAME)/
	@echo "Source tarball created: ../$(RELEASE_NAME)-source.tar.gz"

release-bin: clean all
	@echo "Creating binary release..."
	mkdir -p dist/$(BIN_RELEASE_NAME)

	# Copy binary
	cp $(TARGET) dist/$(BIN_RELEASE_NAME)/

	# Copy runtime files (adjust as needed)
	cp -r labs dist/$(BIN_RELEASE_NAME)/
	cp README.md dist/$(BIN_RELEASE_NAME)/
	cp LICENSE dist/$(BIN_RELEASE_NAME)/ 2>/dev/null || true

	# Create tarball
	cd dist && tar -czf ../$(BIN_RELEASE_NAME).tar.gz $(BIN_RELEASE_NAME)

	@echo "Binary release created: $(BIN_RELEASE_NAME).tar.gz"
	
# Phony targets
.PHONY: all clean release