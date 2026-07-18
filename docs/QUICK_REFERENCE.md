# Quick Reference Guide

Fast lookup for common algorithm patterns and techniques used in purgatory.

## Pattern Recognition

### When to Use Each Pattern

| Problem Type | Pattern | Example Functions |
|--------------|---------|-------------------|
| Two sorted arrays | Two Pointers | `merge()`, `getCommon()` |
| Container/water problem | Two Pointers | `maxArea()`, `trap()` |
| Remove/modify in-place | Two Pointers | `removeDuplicates()`, `removeElement()` |
| Subarray with constraint | Sliding Window | `minSubArrayLen()`, `maxLength()` |
| Longest substring | Sliding Window | `lengthOfLongestSubstring()` |
| Fixed window size | Sliding Window | `medianSlidingWindow()`, `maxSatisfied()` |
| Parentheses matching | Stack | `isValid()`, `checkValidString()` |
| Next greater/smaller | Monotonic Stack | `nextGreaterElement()`, `sumSubarrayMins()` |
| Expression evaluation | Stack | `calculate()`, `evalRPN()` |
| Frequency counting | Hash Map | `canConstruct()`, `groupAnagrams()` |
| Detect duplicates | Hash Map/Set | `containsDuplicate()`, `longestConsecutive()` |
| Prefix sum tracking | Hash Map | `subarraySum()`, `checkSubarraySum()` |
| Level-by-level traversal | BFS | `levelOrder()`, `rightSideView()` |
| Shortest path unweighted | BFS | `numSquares()`, `findLadders()` |
| Connected components | DFS/BFS | `numIslands()`, `solve()` |
| All paths/combinations | Backtracking | `letterCombinations()`, `subsets()` |
| Top K elements | Heap | `topKFrequent()`, `nthUglyNumber()` |
| Merge K sorted | Heap | `assignTasks()` |
| Shortest path weighted | Dijkstra (Heap) | `networkDelayTime()`, `minimumEffortPath()` |
| Overlapping subproblems | DP | `climbStairs()`, `rob()`, `wordBreak()` |
| Sorted array search | Binary Search | `searchInsert()`, `findPeakElement()` |
| Rotated sorted array | Binary Search | `search()`, `findMin()` |
| Interval merging | Sorting + Greedy | `merge()`, `insert()` |
| Cycle detection | Floyd's Algorithm | `hasCycle()`, `findDuplicate()` |

## Complexity Cheatsheet

### Time Complexities by Pattern

| Pattern | Typical Complexity | Notes |
|---------|-------------------|-------|
| Two Pointers | O(n) | Single pass, opposite or same direction |
| Sliding Window | O(n) | Amortized, each element visited at most twice |
| Stack | O(n) | Single pass with push/pop |
| Monotonic Stack | O(n) | Each element pushed/popped once |
| Hash Map | O(n) | With O(1) operations |
| BFS/DFS | O(V+E) | Graph with V vertices, E edges |
| Binary Search | O(log n) | Halving search space |
| Heap Operations | O(log n) | Insert/delete in heap |
| Build Heap | O(n) | Floyd's method |
| Backtracking | O(2^n) to O(n!) | Depends on branching factor |
| DP | O(n) to O(n²) | Depends on state transitions |

### Space Complexities

| Technique | Space | Notes |
|-----------|-------|-------|
| In-place modification | O(1) | No extra data structures |
| Hash Map/Set | O(n) | Store unique elements |
| Recursion depth | O(h) | Tree height or recursion depth |
| BFS queue | O(w) | Maximum width of tree/graph level |
| DP table | O(n) to O(n²) | Can often optimize to O(1) or O(n) |
| Backtracking | O(depth) | Recursion stack |

## Common Techniques

### In-Place Array Manipulation

```cpp
// Two pointers: write pointer lags read pointer
int write = 0;
for (int read = 0; read < n; ++read) {
    if (condition) {
        nums[write++] = nums[read];
    }
}
```

### Sliding Window Template

```cpp
// Variable size window
int left = 0, result = 0;
for (int right = 0; right < n; ++right) {
    // Expand window
    add(nums[right]);
    
    // Shrink while invalid
    while (!isValid()) {
        remove(nums[left++]);
    }
    
    result = max(result, right - left + 1);
}
```

### Monotonic Stack

```cpp
// Next greater element (decreasing stack)
stack<int> st;
for (int i = 0; i < n; ++i) {
    while (!st.empty() && nums[i] > nums[st.top()]) {
        int idx = st.top(); st.pop();
        result[idx] = nums[i];
    }
    st.push(i);
}
```

### Hash Map for Frequency

```cpp
// Character frequency array (fixed size)
int freq[26] = {0};
for (char c : s) {
    freq[c - 'a']++;
}

// Hash map (variable keys)
unordered_map<int, int> freq;
for (int x : nums) {
    freq[x]++;
}
```

### BFS Level-by-level

```cpp
queue<Node*> q;
q.push(root);

while (!q.empty()) {
    int levelSize = q.size();
    for (int i = 0; i < levelSize; ++i) {
        Node* node = q.front(); q.pop();
        // Process node
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

### DFS for Graphs

```cpp
void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}
```

### Floyd's Cycle Detection

```cpp
// Fast/slow pointers
ListNode *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true; // Cycle detected
}
return false;
```

### Backtracking Template

```cpp
void backtrack(vector<int>& path, int start) {
    // Base case
    if (isComplete(path)) {
        result.push_back(path);
        return;
    }
    
    // Recursive case
    for (int i = start; i < candidates.size(); ++i) {
        // Choose
        path.push_back(candidates[i]);
        // Explore
        backtrack(path, i + 1);
        // Unchoose
        path.pop_back();
    }
}
```

## Performance Tips

### From purgatory Implementation

1. **Cache Behavior**: Use `reserve()` on vectors/maps to avoid rehashing
2. **Register vs Memory**: Store frequently accessed values in local variables
3. **Branch Prediction**: Put likely conditions first
4. **Loop Optimization**: Minimize work inside inner loops
5. **Compiler Hints**: Use const references for large objects

### Memory Access Patterns

- Prefer sequential access over random access
- Use arrays over maps for small, fixed ranges (e.g., character frequencies)
- Consider cache line sizes (64 bytes typically)

## Testing Strategy

### Edge Cases to Always Test

- Empty input: `[]`, `""`
- Single element: `[x]`, `"a"`
- Two elements: `[x, y]`
- All same: `[1, 1, 1, 1]`
- Sorted ascending: `[1, 2, 3, 4]`
- Sorted descending: `[4, 3, 2, 1]`
- Maximum constraints (array size, value ranges)
- Negative numbers, zero
- Overflow scenarios (use `long long`)

### Test Organization

All tests in `test/test.cc`:
```bash
# Run all tests
ctest --test-dir build --output-on-failure

# Run specific test
./build/test/purgatory_test --gtest_filter="ArrayTest.IncreaseTriplet"
```

## Interview Tips

1. **Ask clarifying questions**: Input size? Duplicates? Sorted?
2. **Start with brute force**: State O(n²) solution before optimizing
3. **Explain trade-offs**: Time vs space complexity
4. **Trace example**: Walk through small input
5. **Consider edge cases**: Empty, single element, all same
6. **Optimize iteratively**: Don't jump to optimal solution
7. **Write clean code**: Meaningful variable names, comments for clarity
