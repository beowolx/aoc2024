# AoC2024

My solutions for [Advent of Code 2024](https://adventofcode.com/2024) in C++.

## Requirements
- CMake 3.18.4 or higher
- C++ compiler with C++17 support

## Building the Project

```bash
cmake -B build -S .
cmake --build build
```

## Running Solutions

```bash
# Run a specific day's solution (replace N with day number)
./build/aoc N

# Example: Run Day 1
./build/aoc 1
```

## Project Structure
```
.
├── input/          # Puzzle inputs
│   └── dayNN.txt   # Input for day NN
├── src/
│   ├── solutions/  # One file per day
│   ├── utils/      # Helper functions
│   └── main.cpp    # Program entry point
└── CMakeLists.txt  # Build configuration
```

## Adding New Solutions
1. Create new files `dayNN.h` and `dayNN.cpp` in `src/solutions/`
2. Add puzzle input to `input/dayNN.txt`
3. Add day to the switch statement in `main.cpp`
4. Rebuild and run