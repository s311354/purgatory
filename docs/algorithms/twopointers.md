# Two Pointers Algorithms

**File**: `src/twopointers.cc` (1059 LOC)  
**Total Problems**: 33

## Problems

### Easy (14 problems)

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `isPalindrome()` | Valid palindrome | O(n) | O(1) |
| `twoSum()` | Two sum (sorted array) | O(n) | O(n) |
| `reverseString()` | Reverse string in-place | O(n) | O(1) |
| `findContentChildren()` | Assign cookies | O(n log n) | O(1) |
| `judgeSquareSum()` | Sum of two squares | O(√c) | O(1) |
| `removePalindromeSub()` | Remove palindrome substring | O(n) | O(1) |
| `reverseStr()` | Reverse string II | O(n) | O(n) |
| `shortestToChar()` | Shortest distance to character | O(n) | O(n) |
| `addSpaces()` | Add spaces to string | O(n) | O(n) |
| `minimumSteps()` | Minimum steps | O(n) | O(1) |
| `getCommon()` | Get common elements | O(n+m) | O(1) |
| `reverseOnlyLetters()` | Reverse only letters | O(n) | O(1) |
| `applyOperations()` | Apply operations | O(n) | O(1) |
| `arithmeticTriplets()` | Count arithmetic triplets | O(n²) | O(1) |

### Medium (18 problems)

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `maxArea()` | Container with most water | O(n) | O(1) |
| `trap()` | Trapping rain water | O(n) | O(1) |
| `sortColors()` | Dutch national flag | O(n) | O(1) |
| `compareVersion()` | Version number comparison | O(n+m) | O(1) |
| `maxNumber()` | Create maximum number | O(k×(n+m)²) | O(n+m) |
| `magicalString()` | Magical string | O(n) | O(n) |
| `checkInclusion()` | Permutation in string | O(n) | O(1) |
| `findRadius()` | Heaters radius | O(n log n) | O(1) |
| `circularArrayLoop()` | Circular array loop | O(n) | O(1) |
| `maxProfitAssignment()` | Maximum profit assignment | O(n log n) | O(n) |
| `countBinarySubstrings()` | Count binary substrings | O(n) | O(1) |
| `countSubstrings()` | Count palindromic substrings | O(n²) | O(1) |
| `longestMountain()` | Longest mountain in array | O(n) | O(1) |
| `rangeSum()` | Range sum of sorted subarray | O(n² log n) | O(n²) |
| `numFriendRequests()` | Number of friend requests | O(n) | O(1) |
| `numRescueBoats()` | Number of rescue boats | O(n log n) | O(1) |
| `waysToSplit()` | Ways to split array | O(n log n) | O(n) |
| `partitionLabels()` | Partition labels | O(n) | O(1) |

### Hard (1 problem)

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `findLUSlegnth()` | Longest uncommon subsequence II | O(n² × m) | O(1) |

## Key Patterns

### Opposite Direction
- `isPalindrome()`: Start from both ends
- `maxArea()`: Greedy shrink from widest
- `trap()`: Track left/right max heights

### Same Direction (Fast/Slow)
- `removeDuplicates()`: Write pointer lags behind read
- `sortColors()`: Dutch flag with three pointers

### Expand Around Center
- `countSubstrings()`: Check palindromes from center
- `longestMountain()`: Find peak then expand

### Sorted Array Two Pointers
- `twoSum()`: Classic two pointer on sorted
- `judgeSquareSum()`: Meet in middle
- `numRescueBoats()`: Greedy pairing

### Sliding/Fixed Window Hybrid
- `checkInclusion()`: Frequency matching
- `countBinarySubstrings()`: Group counting

## Implementation Notes

- Minimize memory access with register variables
- Branch prediction optimization noted
- In-place modifications where possible
- Character type checking optimized
