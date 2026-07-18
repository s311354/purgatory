# Sliding Window Algorithms

**File**: `src/slidingwindow.cc` (596 LOC)  
**Total Problems**: 19+

## Problems

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `containsNearbyDuplicate()` | Contains duplicate within K | O(n) | O(k) |
| `numberOfAlternatingGroups()` | Alternating groups count | O(n) | O(1) |
| `countKConstraintSubstrings()` | Count K-constraint substrings | O(n) | O(1) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `minSubArrayLen()` | Minimum size subarray sum | O(n) | O(1) |
| `lengthOfLongestSubstring()` | Longest substring without repeat | O(n) | O(min(n,m)) |
| `longestNiceSubstring()` | Longest nice substring | O(n²) | O(1) |
| `longestSubstring()` | Longest substring (K repeats) | O(n) | O(1) |
| `numberOfArithmeticSlices()` | Arithmetic slices | O(n) | O(1) |
| `medianSlidingWindow()` | Median sliding window | O(n log k) | O(k) |
| `minimumSumSubarray()` | Minimum sum subarray | O(n×r) | O(1) |
| `numSubarraysWithSum()` | Subarrays with sum goal | O(n) | O(1) |
| `maxLength()` | Max consecutive ones III | O(n) | O(1) |
| `characterReplacement()` | Longest repeating char replacement | O(n) | O(1) |
| `numSubarrayProductLessThanK()` | Subarray product less than K | O(n) | O(1) |
| `totalFruit()` | Fruit into baskets | O(n) | O(1) |
| `findLength()` | Maximum length of repeated subarray | O(n×m) | O(n×m) |
| `maxSatisfied()` | Grumpy bookstore owner | O(n) | O(1) |
| `maxTurbulenceSize()` | Longest turbulent subarray | O(n) | O(1) |
| `numberOfSubarrays()` | Count nice subarrays | O(n) | O(n) |
| `maximumUniqueSubarray()` | Maximum unique subarray sum | O(n) | O(n) |

## Key Patterns

### Fixed-Size Window
- `medianSlidingWindow()`: Maintain window of size K
- `numberOfAlternatingGroups()`: Fixed circular window
- `maxSatisfied()`: Fixed grumpy minutes window

### Variable-Size Window (Expand/Contract)
- `minSubArrayLen()`: Shrink when valid
- `lengthOfLongestSubstring()`: Expand until duplicate
- `characterReplacement()`: Expand with K replacements

### At-Most K Pattern
- `maxLength()`: At most K flips
- `totalFruit()`: At most 2 types
- `characterReplacement()`: At most K replacements

### Frequency Tracking Window
- `lengthOfLongestSubstring()`: Character frequency
- `characterReplacement()`: Track max frequency
- `maximumUniqueSubarray()`: Hash set for uniqueness

### Multiple Pass / Divide-and-Conquer
- `longestNiceSubstring()`: Recursive split on invalid
- `longestSubstring()`: Divide at < K frequency chars

## Implementation Notes

- Hash map/set for O(1) frequency queries
- Two-pointer technique within window
- Amortized O(n) for shrinking operations
- Prefix sum optimizations where applicable
