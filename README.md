# purgatory: Structured Coding Sandbox for Interview Prep and Testing

![CI](https://github.com/s311354/purgatory/workflows/CI/badge.svg)
![Release](https://github.com/s311354/purgatory/workflows/Release/badge.svg)
![Code Coverage](https://github.com/s311354/purgatory/workflows/Code%20Coverage/badge.svg)

purgatory is a lightweight, modular C++17-based environment for prototyping, embedded experimentation, and test-driven workflows.

## Requirements

- CMake 3.14 or later
- A C++17 compiler
- Git with submodule support
- clang-format 14 for the repository formatting check

## Project Layout

```shell
.
├── .clang-format          # LLVM-based C++ formatting rules
├── .github/               # CI, coverage, and release workflows
├── CMakeLists.txt         # Root CMake configuration
├── format.sh              # Check or apply clang-format
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
    └── googletest/        # Pinned GoogleTest submodule
```

## Build and Test

Clone the repository with its pinned GoogleTest submodule:

```shell
git clone --recurse-submodules https://github.com/s311354/purgatory.git
cd purgatory
```

For an existing clone, restore the dependency with:

```shell
git submodule update --init --recursive
```

Configure, build, and run the same test path used by CI:

```shell
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=c++ \
  -DBUILD_TESTING=ON

cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/purgatory src/test.txt
```

## Development Workflow

Add unit tests in `test/test.cc`, then run the build, CTest, sample executable, and formatting check before opening a pull request.

### Code Formatting

Use `format.sh` to check or apply clang-format:

```shell
./format.sh check              # Check formatting in src/ and test/
./format.sh apply              # Apply formatting to src/ and test/
./format.sh check src          # Check only src/ directory
./format.sh apply test         # Apply formatting to test/ directory
```

### Development Environment

For an optional tmux workspace:

```shell
./tmux-session.sh dev
# or
./tmux-session.sh quick
```

See [.github/CI_CD.md](.github/CI_CD.md) for workflow triggers, release behavior, coverage details, and troubleshooting.

## Algorithm Catalog

purgatory includes **300+ algorithm implementations** organized by pattern:

📚 **[Complete Algorithm Index](docs/ALGORITHMS.md)** - Full catalog with complexity analysis

### Quick Links

- [Array & String (40+)](docs/algorithms/array.md)
- [Hash Map (24+)](docs/algorithms/hashmap.md)
- [Two Pointers (33)](docs/algorithms/twopointers.md)
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

Before submitting a change:

1. Initialize the GoogleTest submodule.
2. Add or update tests for behavior changes.
3. Run the test-enabled Release build and sample executable.
4. Apply clang-format 14 and confirm the dry-run check passes.
5. Update the algorithm documentation when adding or changing an algorithm.
