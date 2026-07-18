# Tree & Graph Algorithms

**Files**: `src/binarytree.cc`, `src/graph.cc`, `src/graphbfs.cc`  
**Total Problems**: 23+

## Binary Tree Problems

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `sumOfLeftLeaves()` | Sum of left leaves | O(n) | O(h) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `averageOfLevels()` | Average of levels (BFS) | O(n) | O(n) |
| `rightSideView()` | Right side view | O(n) | O(n) |
| `levelOrder()` | Level order traversal | O(n) | O(n) |
| `levelOrderBottom()` | Level order bottom-up | O(n) | O(n) |
| `inorderTraversal()` | Inorder traversal (iterative) | O(n) | O(h) |
| `numTrees()` | Unique BSTs (Catalan) | O(n) | O(n) |
| `findFrequentTreeSum()` | Most frequent subtree sum | O(n) | O(n) |
| `maxAncestorDiff()` | Max ancestor difference | O(n) | O(h) |
| `minDepth()` | Minimum depth | O(n) | O(n) |
| `connect()` | Populating next right pointers | O(n) | O(1) |

### Tree Serialization

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `Codec::serialize()` | Serialize tree | O(n) | O(n) |
| `Codec::deserialize()` | Deserialize tree | O(n) | O(n) |

## Graph Problems (DFS/BFS)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `findJudge()` | Find the town judge | O(n) | O(n) |
| `findCenter()` | Find center of star graph | O(1) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `numIslands()` | Number of islands | O(m×n) | O(m×n) |
| `solve()` | Surrounded regions | O(m×n) | O(m×n) |
| `longestIncreasingPath()` | Longest increasing path | O(m×n) | O(m×n) |
| `isBipartite()` | Is graph bipartite | O(V+E) | O(V) |
| `numberOfComponents()` | Number of connected components | O(n) | O(n) |
| `numSquares()` | Perfect squares (BFS) | O(n×√n) | O(n) |
| `canMeasureWater()` | Water and jug problem | O(x×y) | O(x×y) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `removeInvalidParentheses()` | Remove invalid parentheses | O(2^n) | O(n) |
| `findLadders()` | Word ladder II | O(n×m²) | O(n×m) |

## Key Patterns

### Tree Traversal
- **BFS**: Level order, right side view, minimum depth
- **DFS**: Inorder, ancestor difference, subtree sums
- **Morris**: O(1) space traversal (not implemented yet)

### Tree Construction/Serialization
- `Codec`: Preorder with null markers
- Recursive build from serialized string

### Graph Traversal
- **DFS**: Island problems, surrounded regions, cycles
- **BFS**: Shortest path, level-by-level exploration

### Graph Coloring
- `isBipartite()`: Two-color alternating DFS

### Matrix as Graph
- `numIslands()`: Treat cells as nodes
- `longestIncreasingPath()`: DFS with memoization
- `solve()`: Boundary-connected regions

### Topological/BFS Shortest Path
- `numSquares()`: BFS on implicit graph
- `findLadders()`: BFS + backtracking
- `canMeasureWater()`: GCD-based BFS

## Implementation Notes

### Binary Tree
- Helper structures: TreeNode, Node (with next pointer)
- `buildTree()`: Construct from level-order with INT_MIN as null
- Queue-based BFS using deque for cache locality

### Graph
- Adjacency list representation
- Visited tracking with vector<bool> or unordered_set
- DFS/BFS helper functions for reusability
- Matrix problems use in-place marking when possible
