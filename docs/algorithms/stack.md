# Stack Algorithms

**File**: `src/stack.cc` (1178 LOC)  
**Total Problems**: 44+

## Problems

### Easy

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `isValid()` | Valid parentheses | O(n) | O(n) |
| `nextGreaterElement()` | Next greater element I | O(n+m) | O(m) |
| `backspaceCompare()` | Backspace string compare | O(n+m) | O(n+m) |
| `makeGood()` | Make string good | O(n) | O(n) |
| `reversePrefix()` | Reverse string prefix | O(n) | O(n) |
| `removeDuplicates()` | Remove adjacent duplicates | O(n) | O(n) |
| `clearDigits()` | Clear digits | O(n) | O(n) |
| `validateStackSequences()` | Validate stack sequences | O(n) | O(n) |
| `minOperations()` | Minimum operations (logs) | O(n) | O(n) |
| `buildArray()` | Build array with stack | O(n) | O(n) |
| `preorderTraversal()` | Binary tree preorder | O(n) | O(h) |
| `postorderTraversal()` | Binary tree postorder | O(n) | O(h) |

### Medium

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `simplifyPath()` | Simplify Unix path | O(n) | O(n) |
| `evalRPN()` | Evaluate RPN | O(n) | O(n) |
| `calculate()` | Basic calculator | O(n) | O(n) |
| `removeDuplicateLetters()` | Remove duplicate letters | O(n) | O(1) |
| `calculateII()` | Basic calculator II | O(n) | O(n) |
| `findUnsortedSubarray()` | Shortest unsorted subarray | O(n log n) | O(n) |
| `carFleet()` | Car fleet | O(n log n) | O(n) |
| `sumSubarrayMins()` | Sum of subarray minimums | O(n) | O(n) |
| `removeOccurrences()` | Remove occurrences | O(n×m) | O(n) |
| `maximumGain()` | Maximum gain | O(n) | O(n) |
| `addMinimum()` | Add minimum (make valid) | O(n) | O(1) |
| `calculateScore()` | Calculate score | O(n) | O(n) |
| `minLengthAfterRemovals()` | Min length after removals | O(n) | O(n) |
| `minLength()` | Minimum length | O(n) | O(n) |
| `exclusiveTime()` | Exclusive time of functions | O(n) | O(n) |
| `subArrayRanges()` | Sum of subarray ranges | O(n) | O(n) |
| `checkValidString()` | Valid parenthesis string | O(n) | O(n) |
| `find132pattern()` | 132 pattern | O(n) | O(n) |
| `maxWidthRamp()` | Maximum width ramp | O(n) | O(n) |
| `minRemoveToMakeValid()` | Remove to make valid | O(n) | O(n) |
| `totalSteps()` | Total steps to remove | O(n) | O(n) |
| `scoreOfParentheses()` | Score of parentheses | O(n) | O(n) |
| `maximumPossibleSize()` | Maximum possible size | O(n) | O(n) |
| `maxBalanceShipments()` | Max balance shipments | O(n) | O(n) |
| `bowlSubarrays()` | Bowl subarrays | O(n) | O(n) |
| `mergeAdjacent()` | Merge adjacent | O(n) | O(n) |
| `decodeAtIndex()` | Decode string at index | O(n) | O(1) |
| `isValidString()` | Is valid string | O(n) | O(n) |

### Hard

| Function | Description | Time | Space |
|----------|-------------|------|-------|
| `longestValidParentheses()` | Longest valid parentheses | O(n) | O(n) |

## Key Patterns

### Matching/Validation
- `isValid()`: Parentheses matching
- `checkValidString()`: Wildcard matching
- `validateStackSequences()`: Sequence validation

### Monotonic Stack
- `nextGreaterElement()`: Decreasing stack
- `sumSubarrayMins()`: Track minimums
- `maxWidthRamp()`: Decreasing indices
- `find132pattern()`: Track max for 3-2 pattern

### Calculator/Expression Evaluation
- `calculate()`: Basic arithmetic
- `calculateII()`: With operator precedence
- `evalRPN()`: Postfix notation
- `scoreOfParentheses()`: Nested scoring

### String Manipulation
- `simplifyPath()`: Path canonicalization
- `removeDuplicateLetters()`: Greedy + monotonic
- `removeOccurrences()`: Pattern removal
- `backspaceCompare()`: Backspace simulation

### Tree Traversal
- `preorderTraversal()`: Iterative preorder
- `postorderTraversal()`: Iterative postorder

## Implementation Notes

- Use deque for better cache locality
- Minimize push/pop overhead
- Store indices instead of values when possible
- Combine stack with other data structures (counters, maps)
