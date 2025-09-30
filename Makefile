# Makefile for Atari 8-bit Project

# --- Configuration ---
CC = cl65
TARGET = main.xex
CFLAGS = -t atari

# --- File Discovery ---
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# --- Build Rules ---
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete! Output file is $(TARGET)"

%.o: %.c animation.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
	@echo "Cleaned up the project."