# Advanced Topics

Algorithms for heap/priority queue, dynamic programming, backtracking, binary search, intervals, linked list, and matrix problems.

## Heap / Priority Queue

**File**: `src/heap.cc` (606 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `lastStoneWeight()` | Last stone weight | O(n log n) | O(n) |
| `numberGame()` | Number game | O(n log n) | O(n) |
| `minSetSize()` | Reduce array size to half | O(n log n) | O(n) |
| `deleteGreatestValue()` | Delete greatest value | O(m×n log n) | O(n) |
| `pickGifts()` | Pick gifts | O(k log n) | O(n) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `nthUglyNumber()` | Nth ugly number | O(n) | O(n) |
| `topKFrequent()` | Top K frequent elements | O(n log k) | O(n) |
| `maxSlidingWindow()` | Max sliding window | O(n) | O(k) |
| `maxProduct()` | Maximum product | O(n log n) | O(n) |
| `frequencySort()` | Sort by frequency | O(n log n) | O(n) |
| `rearrangeBarcodes()` | Rearrange barcodes | O(n log k) | O(k) |
| `furthestBuilding()` | Furthest building | O(n log m) | O(m) |
| `assignTasks()` | Assign tasks to servers | O(n log m) | O(m) |
| `networkDelayTime()` | Network delay (Dijkstra) | O(E log V) | O(V+E) |
| `longestDiverseString()` | Longest diverse string | O(n log 3) | O(1) |
| `minimumEffortPath()` | Minimum effort path | O(m×n log(m×n)) | O(m×n) |
| `getOrder()` | Task scheduler | O(n log n) | O(n) |

## Dynamic Programming

**File**: `src/dp.cc` (144 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `climbStairs()` | Climbing stairs | O(n) | O(1) |
| `rob()` | House robber | O(n) | O(1) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `wordBreak()` | Word break | O(n²) | O(n) |
| `isMatch()` | Regular expression matching | O(m×n) | O(m×n) |

## Backtracking

**File**: `src/backtracking.cc` (299 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `binaryTreePaths()` | All root-to-leaf paths | O(n) | O(h) |
| `readBinaryWatch()` | Binary watch combinations | O(1) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `letterCombinations()` | Letter combinations | O(4^n) | O(n) |
| `combine()` | Combinations | O(C(n,k)) | O(k) |
| `totalNQueens()` | N-Queens count | O(n!) | O(n) |
| `subsets()` | Generate subsets | O(2^n) | O(n) |
| `grayCode()` | Gray code sequence | O(2^n) | O(1) |
| `findSubsequences()` | Find increasing subsequences | O(2^n) | O(n) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `judgePoint24()` | 24 game solver | O(1) | O(1) |

## Binary Search

**File**: `src/binarysearch.cc` (257 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `searchInsert()` | Search insert position | O(log n) | O(1) |
| `missingNumber()` | Missing number | O(log n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `searchMatrix()` | Search 2D matrix | O(log(m×n)) | O(1) |
| `findPeakElement()` | Find peak element | O(log n) | O(1) |
| `search()` | Search rotated sorted array | O(log n) | O(1) |
| `findMin()` | Find minimum in rotated array | O(log n) | O(1) |
| `findDuplicate()` | Find duplicate (cycle detection) | O(n) | O(1) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `findMedianSortedArrays()` | Median of two sorted arrays | O(log(m+n)) | O(1) |

## Intervals

**File**: `src/intervals.cc` (193 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `summaryRanges()` | Summary ranges | O(n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `merge()` | Merge intervals | O(n log n) | O(n) |
| `insert()` | Insert interval | O(n) | O(n) |
| `findMinArrowShots()` | Minimum arrows (greedy) | O(n log n) | O(1) |

## Linked List

**File**: `src/linkedlist.cc` (641 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `hasCycle()` | Detect cycle (Floyd) | O(n) | O(1) |
| `isPalindromeLinkedList()` | Is palindrome | O(n) | O(1) |
| `middleNode()` | Find middle | O(n) | O(1) |
| `deleteDuplicates()` | Remove duplicates | O(n) | O(1) |
| `getDecimalValue()` | Binary to decimal | O(n) | O(1) |
| `removeElements()` | Remove elements | O(n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `addTwoNumbers()` | Add two numbers | O(max(m,n)) | O(max(m,n)) |
| `removeNthFromEnd()` | Remove Nth from end | O(n) | O(1) |
| `swapPairs()` | Swap nodes in pairs | O(n) | O(1) |
| `reorderList()` | Reorder list | O(n) | O(1) |
| `numComponents()` | Number of components | O(n+m) | O(m) |
| `nodesBetweenCriticalPoints()` | Nodes between critical points | O(n) | O(1) |
| `removeNodes()` | Remove nodes | O(n) | O(n) |
| `doubleIt()` | Double linked list number | O(n) | O(1) |
| `mergeNodes()` | Merge between zeros | O(n) | O(1) |
| `insertGreatestCommonDivisors()` | Insert GCD nodes | O(n log m) | O(1) |
| `mergeInBetween()` | Merge in between | O(n) | O(1) |
| `modifiedList()` | Modified list | O(n+m) | O(m) |
| `nextLargerNodes()` | Next larger nodes | O(n) | O(n) |
| `insertionSortList()` | Insertion sort | O(n²) | O(1) |
| `reverseEvenLengthGroups()` | Reverse even groups | O(n) | O(1) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `reverseKGroup()` | Reverse nodes in K-group | O(n) | O(1) |

## Matrix

**File**: `src/matrix.cc` (170 LOC)

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `islandPerimeter()` | Island perimeter | O(m×n) | O(1) |
| `countBattleships()` | Count battleships | O(m×n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `kthSmallest()` | Kth smallest in sorted matrix | O(k log k) | O(k) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `maximalRectangle()` | Maximal rectangle | O(m×n) | O(n) |

## Prefix Sum

**File**: `src/prefixsum.cc` (87 LOC)

| Class/Function | Description | Time | Space |
|----------------|-------------|------|-------|
| `NumArray` | Range sum query (immutable) | O(1) query | O(n) |
| `NumMatrix` | 2D range sum query | O(1) query | O(m×n) |
| `maxSumSubmatrix()` | Max sum with constraint | O(m²×n log n) | O(n) |
