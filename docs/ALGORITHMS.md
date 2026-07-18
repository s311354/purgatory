# Algorithm Index

Comprehensive catalog of all algorithms implemented in purgatory, organized by problem-solving pattern.

## Quick Stats

- **Total Algorithms**: 300+
- **Total Test Cases**: 248
- **Lines of Code**: ~9,114
- **C++ Standard**: C++17

## Pattern Overview

| Pattern | File | LOC | Algorithms | Test Coverage |
|---------|------|-----|------------|---------------|
| Array/String | array.cc | 1162 | 40+ | ✓ |
| Hash Map | hashmap.cc | 762 | 24+ | ✓ |
| Two Pointers | twopointers.cc | 916 | 26+ | ✓ |
| Sliding Window | slidingwindow.cc | 596 | 19+ | ✓ |
| Stack | stack.cc | 1178 | 44+ | ✓ |
| Binary Tree | binarytree.cc | 446 | 11+ | ✓ |
| Graph | graph.cc, graphbfs.cc | 512 | 12+ | ✓ |
| Heap | heap.cc | 606 | 18+ | ✓ |
| Linked List | linkedlist.cc | 641 | 22+ | ✓ |
| Binary Search | binarysearch.cc | 257 | 8+ | ✓ |
| DP | dp.cc | 144 | 4+ | ✓ |
| Backtracking | backtracking.cc | 299 | 8+ | ✓ |
| Intervals | intervals.cc | 193 | 4+ | ✓ |
| Matrix | matrix.cc | 170 | 4+ | ✓ |

## Detailed Catalogs

- [Array & String Problems](algorithms/array.md)
- [Hash Map Problems](algorithms/hashmap.md)
- [Two Pointers Problems](algorithms/twopointers.md)
- [Sliding Window Problems](algorithms/slidingwindow.md)
- [Stack Problems](algorithms/stack.md)
- [Tree & Graph Problems](algorithms/tree-graph.md)
- [Advanced Topics](algorithms/advanced.md)

## How to Use

### Find by Pattern
Browse sections below or use pattern-specific documentation files.

### Search by Name
Use Ctrl+F to find specific algorithm implementations.

### Filter by Complexity
Each entry includes time/space complexity for quick reference.

## Testing

Run all algorithm tests:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -DBUILD_TESTING=ON -B build
cmake --build build -j$(nproc)
ctest --test-dir build  --output-on-failure
```

## Contributing

When adding algorithms:
1. Implement in appropriate pattern file
2. Add declaration to `purgatory.h`
3. Write tests in `test/test.cc`
4. Update this catalog
5. Include complexity analysis in comments
