# Variables
CC = gcc
CFLAGS = -o
BINARY = /home/neon/Ragnarok/src/Ragnarok
SRC = /home/neon/Ragnarok/src/main.c
USER = neon
PROCESS_NAME = Ragnarok

# Default target
all: build run

# Build target
build:
	$(CC) $(CFLAGS) $(BINARY) $(SRC)

# Run target
run: build
	$(BINARY)

# Clean target
clean:
	rm -f $(BINARY)

# Kill target
kill:
	pkill -u $(USER) $(PROCESS_NAME)

.PHONY: all build run clean kill

