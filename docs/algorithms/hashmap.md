# Hash Map Algorithms

**File**: `src/hashmap.cc` (762 LOC)  
**Total Problems**: 24+

## Problems

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `canConstruct()` | Ransom note | O(n) | O(1) |
| `containsDuplicate()` | Contains duplicate | O(n) | O(n) |
| `intersection()` | Array intersection | O(n+m) | O(min(n,m)) |
| `majorityElement()` | Find majority elements | O(n) | O(n) |
| `findTheDifference()` | Find the difference | O(n) | O(1) |
| `longestWord()` | Longest word in dictionary | O(n×L) | O(n×L) |
| `longestPalindrome()` | Longest palindrome length | O(n) | O(1) |
| `fairCandySwap()` | Fair candy swap | O(n+m) | O(n) |
| `findDisappearedNumbers()` | Find disappeared numbers | O(n) | O(1) |
| `findRestaurant()` | Minimum index sum | O(n+m) | O(n) |
| `findErrorNums()` | Find error numbers | O(n) | O(n) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `groupAnagrams()` | Group anagrams | O(n×k log k) | O(n×k) |
| `longestConsecutive()` | Longest consecutive sequence | O(n) | O(n) |
| `findSubstring()` | Substring with concatenation | O(n×m×k) | O(m×k) |
| `fractionToDecimal()` | Fraction to decimal | O(k) | O(k) |
| `firstMissingPositive()` | First missing positive | O(n) | O(1) |
| `getHint()` | Bulls and cows | O(n) | O(1) |
| `numberOfBoomerangs()` | Number of boomerangs | O(n²) | O(n) |
| `findAnagrams()` | Find anagrams in string | O(n) | O(1) |
| `subarraySum()` | Subarray sum equals K | O(n) | O(n) |
| `deleteAndEarn()` | Delete and earn | O(n) | O(n) |
| `minimumLengthEncoding()` | Minimum length encoding | O(n×L²) | O(n×L) |
| `wordSubsets()` | Word subsets | O(n×L) | O(1) |
| `findMaxLength()` | Maximum length (equal 0s and 1s) | O(n) | O(n) |
| `checkSubarraySum()` | Check subarray sum | O(n) | O(n) |
| `findDuplicate()` | Find duplicate files | O(n×L) | O(n×L) |

## Key Patterns

### Frequency Counting
- `canConstruct()`: Character frequency array
- `groupAnagrams()`: Sorted string as key
- `findAnagrams()`: Sliding window with frequency map

### Hash Set for Lookup
- `longestConsecutive()`: O(1) lookup for sequences
- `containsDuplicate()`: Detect duplicates

### Hash Map for State Tracking
- `subarraySum()`: Prefix sum mapping
- `fractionToDecimal()`: Detect cycles in division
- `findMaxLength()`: Prefix sum to index mapping

### Trie-Based Solutions
- `minimumLengthEncoding()`: Reverse trie
- `longestWord()`: Dictionary trie

### In-Place Hashing
- `firstMissingPositive()`: Use array indices as hash
- `findDisappearedNumbers()`: Mark visited with negation

## Implementation Notes

- Cache-friendly frequency arrays for small character sets
- `reserve()` calls to minimize rehashing
- Custom hash functions where applicable
- Efficient string key generation
