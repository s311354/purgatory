# purgatory: Structured Coding Sandbox for Interview Prep and Testing

purgatory is a lightweight, modular C++11-based environment for prototyping, embedded experimentation, and test-driven workflows.

## Project Layout

```shell
.
├── CMakeLists.txt         # Root CMake configuration
├── install-build-deps.sh  # Script to install compiler/tools
├── tmux-session.sh        # Launch development tmux sessions
├── src/
│   ├── main.cc            # Sandbox for quick experiments
│   ├── entry.cc           # Entry point or application driver
│   ├── purgatory.h        # Shared header/interfaces
│   ├── array.cc           # Array & string algorithms
│   ├── hashmap.cc         # Hash map algorithms
│   ├── twopointers.cc     # Two pointers algorithms
│   ├── slidingwindow.cc   # Sliding window algorithms
│   ├── stack.cc           # Stack algorithms
│   ├── linkedlist.cc      # Linked list algorithms
│   ├── binarytree.cc      # Binary tree algorithms
│   ├── graph.cc           # Graph algorithms
│   ├── graphbfs.cc        # Graph BFS algorithms
│   ├── heap.cc            # Heap algorithms
│   ├── dp.cc              # Dynamic programming algorithms
│   ├── backtracking.cc    # Backtracking algorithms
│   ├── binarysearch.cc    # Binary search algorithms
│   ├── intervals.cc       # Intervals algorithms
│   ├── matrix.cc          # Matrix algorithms
│   ├── prefixsum.cc       # Prefix sum algorithms
│   └── query.cc / query.h # Text query functionality
├── test/
│   ├── CMakeLists.txt     # CMake config for test targets
│   └── test.cc            # GoogleTest unit tests
├── docs/
│   ├── ALGORITHMS.md      # Complete algorithm index
│   ├── QUICK_REFERENCE.md # Pattern recognition & templates
│   └── algorithms/        # Detailed algorithm documentation by category
└── third-party/
    └── googletest/        # Embedded gtest framework
```

## How to Build

purgatory is written in C++11, so if you build purgatory yourself, you will need a recent version of a C++ compiler and a C++ standard library. We recommend GCC 10.2 or Clang 12.0.0 (or later).

### Compile purgatory

```shell
git clone https://github.com/s311354/purgatory.git
cd purgatory
./install-build-deps.sh
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -B build
cmake --build build -j$(nproc)
```

## How to use

<details><summary>🚀 Efficient tmux development environment (Recommended)</summary>

Launch an optimized development session (max 4 windows):

```shell
# Dev mode (3-window: editor, build/test, git)
./tmux-session.sh dev

# Quick mode (2-pane: editor, terminal)
./tmux-session.sh quick
```
</details>

<details><summary>A classic way to use purgatory</summary>

If you can specify new algorithms for testing by editing src/main.cc, use print statements or assertions to validate logic quickly before formalizing tests.

</details>

<details><summary>If you are running unit testing with GoogleTest</summary>

purgatory uses GoogleTest for reliable, isolated testing.

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -DBUILD_TESTING=ON -B build
cmake --build build -j$(nproc)
cd build
ctest --output-on-failure -j$(nproc)
```
To add new test cases, edit test/test.cc. All tests should assert correctness, edge cases, and maintainability. 

</details>

## Algorithm Catalog

purgatory includes **300+ algorithm implementations** organized by pattern:

📚 **[Complete Algorithm Index](docs/ALGORITHMS.md)** - Full catalog with complexity analysis

### Quick Links

- [Array & String (40+)](docs/algorithms/array.md)
- [Hash Map (24+)](docs/algorithms/hashmap.md)
- [Two Pointers (26+)](docs/algorithms/twopointers.md)
- [Sliding Window (19+)](docs/algorithms/slidingwindow.md)
- [Stack (44+)](docs/algorithms/stack.md)
- [Tree & Graph (23+)](docs/algorithms/tree-graph.md)
- [Advanced Topics](docs/algorithms/advanced.md) - Heap, DP, Backtracking, Binary Search, etc.
- [Quick Reference](docs/QUICK_REFERENCE.md) - Pattern recognition & templates

## Design principles

- Enable rapid development and prototyping of algorithm solutions
- Encourage test-driven development (TDD) with clean separation
- Support embedded and system-level portability

## Contributing

If you're inspired to contribute, whether through new test cases, algorithm enhancements, or tooling improvements, your efforts are truly appreciated.
