# Makefile for Atari 8-bit Project

# --- Configuration ---
CC = cl65
TARGET = main.xex
CFLAGS = -t atari

# --- File Discovery ---
SRCS = $(wildcard *.c)

# --- Build Rules ---
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	@echo "Build complete! Output file is $(TARGET)"

clean:
	rm -f $(TARGET)
	@echo "Cleaned up the project."