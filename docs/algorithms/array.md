# Array & String Algorithms

**File**: `src/array.cc` (1162 LOC)  
**Total Problems**: 40+

## Problems

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `merge()` | Merge sorted arrays | O(m+n) | O(1) |
| `removeDuplicates()` | Remove duplicates from sorted array | O(n) | O(1) |
| `removeElement()` | Remove element by value | O(n) | O(1) |
| `arrayPairSum()` | Array pair sum maximization | O(n log n) | O(1) |
| `distributeCandies()` | Candy distribution problem | O(n) | O(n) |
| `matrixReshape()` | Reshape matrix | O(m×n) | O(m×n) |
| `maximumProduct()` | Maximum product of three numbers | O(n log n) | O(1) |
| `minimumPairRemoval()` | Minimum pair removal | O(n log n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `increasingTriplet()` | Find increasing triplet subsequence | O(n) | O(1) |
| `rotate()` | Rotate array k steps | O(n) | O(1) |
| `candy()` | Candy distribution with ratings | O(n) | O(n) |
| `canJump()` | Jump game | O(n) | O(1) |
| `productExceptSelf()` | Product except self | O(n) | O(1) |
| `generate()` | Pascal's triangle | O(n²) | O(n²) |
| `nextPermutation()` | Next permutation | O(n) | O(1) |
| `combinationSum2()` | Combination sum II | O(2^n) | O(n) |
| `getEncryptedString()` | String encryption | O(n) | O(n) |
| `maxProduct()` | Max product (word lengths) | O(n² × L) | O(n) |
| `largestDivisibleSubset()` | Largest divisible subset | O(n²) | O(n) |
| `maxRotateFunction()` | Maximum rotate function | O(n) | O(1) |
| `findRightInterval()` | Find right interval | O(n log n) | O(n) |
| `largestNumber()` | Largest number from array | O(n log n) | O(n) |
| `arrayNesting()` | Array nesting | O(n) | O(1) |
| `isPossible()` | Check if possible to form sequences | O(n) | O(n) |
| `canPartitionKSubsets()` | Partition to K equal sum subsets | O(k×2^n) | O(n) |
| `minMoves()` | Minimum moves to equal array | O(n) | O(1) |
| `makesquare()` | Make square with matchsticks | O(4^n) | O(n) |
| `findTargetSumWays()` | Target sum ways | O(n×S) | O(S) |
| `countPrimes()` | Count prime numbers | O(n log log n) | O(n) |
| `wiggleMaxLength()` | Wiggle subsequence | O(n) | O(1) |
| `findDuplicates()` | Find duplicates | O(n) | O(1) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `fullJustify()` | Text justification | O(n) | O(n) |
| `solveSudoku()` | Sudoku solver | O(9^m) | O(1) |

## Key Patterns

### Two-Pass Techniques
- `candy()`: Forward + backward pass
- `productExceptSelf()`: Prefix + suffix products

### In-Place Operations
- `rotate()`: Reverse algorithm
- `removeDuplicates()`: Two pointers
- `nextPermutation()`: Find pivot and swap

### Greedy Algorithms
- `canJump()`: Track max reachable
- `candy()`: Local minima approach

### Backtracking
- `solveSudoku()`: Constraint satisfaction
- `combinationSum2()`: Pruning duplicates
- `canPartitionKSubsets()`: Bucket filling

## Implementation Notes

All implementations include:
- Detailed complexity analysis
- Cache-aware optimizations
- Register vs memory trade-offs noted
- Branch prediction hints
