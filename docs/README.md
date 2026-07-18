# Documentation Guide

Welcome to the purgatory algorithm documentation! This guide helps you find what you need quickly.

## 📁 Documentation Structure

```
docs/
├── ALGORITHMS.md           # Main index with overview
├── QUICK_REFERENCE.md      # Pattern templates and tips
└── algorithms/
    ├── array.md            # Array & String (40+ problems)
    ├── hashmap.md          # Hash Map (24+ problems)
    ├── twopointers.md      # Two Pointers (26+ problems)
    ├── slidingwindow.md    # Sliding Window (19+ problems)
    ├── stack.md            # Stack (44+ problems)
    ├── tree-graph.md       # Tree & Graph (23+ problems)
    └── advanced.md         # Heap, DP, Backtracking, etc.
```

## 🎯 Quick Navigation

### I want to...

**Find a specific algorithm by name**
→ Use Ctrl+F in [ALGORITHMS.md](ALGORITHMS.md) or search in pattern-specific files

**Learn when to use each pattern**
→ Check [QUICK_REFERENCE.md](QUICK_REFERENCE.md#pattern-recognition)

**See code templates for common patterns**
→ See [QUICK_REFERENCE.md](QUICK_REFERENCE.md#common-techniques)

**Browse by difficulty**
→ Each pattern file (e.g., [array.md](algorithms/array.md)) groups by Easy/Medium/Hard

**Find time/space complexity**
→ Every algorithm entry includes complexity analysis

**Understand testing strategy**
→ See [QUICK_REFERENCE.md](QUICK_REFERENCE.md#testing-strategy)

## 📊 By Pattern

| Pattern | When to Use | File |
|---------|-------------|------|
| **Array & String** | In-place manipulation, sorting | [array.md](algorithms/array.md) |
| **Hash Map** | Frequency counting, fast lookup | [hashmap.md](algorithms/hashmap.md) |
| **Two Pointers** | Sorted arrays, palindromes | [twopointers.md](algorithms/twopointers.md) |
| **Sliding Window** | Contiguous subarrays/substrings | [slidingwindow.md](algorithms/slidingwindow.md) |
| **Stack** | Matching, monotonic, calculators | [stack.md](algorithms/stack.md) |
| **Tree & Graph** | Traversal, paths, connectivity | [tree-graph.md](algorithms/tree-graph.md) |
| **Heap** | Top K, priority, scheduling | [advanced.md](algorithms/advanced.md#heap--priority-queue) |
| **DP** | Overlapping subproblems | [advanced.md](algorithms/advanced.md#dynamic-programming) |
| **Backtracking** | All combinations, permutations | [advanced.md](algorithms/advanced.md#backtracking) |
| **Binary Search** | Sorted search, binary answer | [advanced.md](algorithms/advanced.md#binary-search) |
| **Linked List** | List operations, cycle detection | [advanced.md](algorithms/advanced.md#linked-list) |
| **Intervals** | Merging, scheduling | [advanced.md](algorithms/advanced.md#intervals) |

## 🎓 Study Paths

### Beginner Path (Easy Problems First)
1. Start with [Array & String Easy](algorithms/array.md#easy)
2. Move to [Hash Map Easy](algorithms/hashmap.md#easy)
3. Practice [Two Pointers Easy](algorithms/twopointers.md#easy)
4. Try [Stack Easy](algorithms/stack.md#easy)

### Pattern Mastery
1. Pick a pattern from [ALGORITHMS.md](ALGORITHMS.md)
2. Read the pattern overview in the specific file
3. Solve Easy → Medium → Hard problems
4. Review [QUICK_REFERENCE.md](QUICK_REFERENCE.md) for templates

### Interview Prep Sprint
1. Review [Pattern Recognition](QUICK_REFERENCE.md#pattern-recognition)
2. Practice most common patterns: Arrays, Hash Maps, Two Pointers
3. Memorize [Common Techniques](QUICK_REFERENCE.md#common-techniques)
4. Review [Interview Tips](QUICK_REFERENCE.md#interview-tips)

## 🔍 Search Tips

### By Algorithm Name
Use GitHub's search or Ctrl+F in browser:
- Pattern files have alphabetically organized problem tables
- Each function name is linked to its complexity

### By Complexity
Look for complexity tags in tables:
- `O(n)` - Linear time
- `O(log n)` - Logarithmic (usually binary search)
- `O(n log n)` - Linearithmic (often sorting)
- `O(n²)` - Quadratic (nested loops)

### By Keyword
Common keywords in documentation:
- "Greedy" → Array, Intervals
- "Monotonic" → Stack
- "BFS/DFS" → Tree, Graph
- "Sliding" → Sliding Window
- "Frequency" → Hash Map
- "Prefix sum" → Array, Hash Map

## 📝 Contributing to Docs

When adding algorithms:

1. **Update the pattern file** (e.g., `algorithms/array.md`)
   - Add entry to appropriate difficulty section
   - Include function name, description, time, space

2. **Add complexity comments** in source code
   ```cpp
   /*
    * Description of approach
    * T: O(n), S: O(1)
    */
   ```

3. **Update test coverage** in `test/test.cc`

4. **Verify links** work in all documentation

## 🚀 Getting Started

New to the codebase? Follow this path:

1. Read [README.md](../README.md) for project overview
2. Browse [ALGORITHMS.md](ALGORITHMS.md) to see what's available
3. Check [QUICK_REFERENCE.md](QUICK_REFERENCE.md) for common patterns
4. Dive into specific patterns in `algorithms/` directory
5. Run the tests to see implementations in action

## 📚 Related Files

- **Source Code**: `src/*.cc` - Algorithm implementations
- **Header**: `src/purgatory.h` - All function declarations
- **Tests**: `test/test.cc` - Unit tests for all algorithms
- **Build**: `CMakeLists.txt` - Build configuration

## 💡 Tips

- **Bookmark QUICK_REFERENCE.md** for fast pattern lookup during coding
- **Use pattern-specific files** for deep dives into specific techniques
- **Check implementation comments** in source files for optimization notes
- **Run tests** to understand expected input/output formats
