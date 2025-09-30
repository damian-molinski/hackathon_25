#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Cleaning project..."
make clean

echo "Building project..."
make

echo "Running project..."
atari800 main.xex

echo "Emulator exited."