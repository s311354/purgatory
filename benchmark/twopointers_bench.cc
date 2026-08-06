#include "../src/purgatory.h"
#include <benchmark/benchmark.h>
#include <random>
#include <string>
#include <vector>

using namespace std;
using namespace purgatory;

// ============================================================================
// Benchmark: isPalindrome
// ============================================================================

static void BM_IsPalindrome_Short(benchmark::State &state) {
  Purgatory p;
  string input = "A man, a plan, a canal: Panama";

  for (auto _ : state) {
    benchmark::DoNotOptimize(p.isPalindrome(input));
  }
  state.SetItemsProcessed(state.iterations());
  state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_IsPalindrome_Short);

static void BM_IsPalindrome_Long(benchmark::State &state) {
  Purgatory p;
  string input(10000, 'a');
  input += string(10000, 'a'); // Perfect palindrome

  for (auto _ : state) {
    benchmark::DoNotOptimize(p.isPalindrome(input));
  }
  state.SetItemsProcessed(state.iterations());
  state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_IsPalindrome_Long);

// ============================================================================
// Benchmark: twoSum
// ============================================================================

static void BM_TwoSum_Small(benchmark::State &state) {
  Purgatory p;
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;

  for (auto _ : state) {
    auto result = p.twoSum(nums, target);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_TwoSum_Small);

static void BM_TwoSum_Large(benchmark::State &state) {
  Purgatory p;
  vector<int> nums(10000);
  mt19937 rng(42);
  uniform_int_distribution<int> dist(-1000000, 1000000);

  for (auto &n : nums) {
    n = dist(rng);
  }
  nums[5000] = 12345;
  nums[7500] = 67890;
  int target = 12345 + 67890;

  for (auto _ : state) {
    auto result = p.twoSum(nums, target);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_TwoSum_Large);

// ============================================================================
// Benchmark: maxArea (Container With Most Water)
// ============================================================================

static void BM_MaxArea_Linear(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> height(n);

  for (int i = 0; i < n; ++i) {
    height[i] = (i * 17 + 13) % 100; // Deterministic pseudo-random
  }

  for (auto _ : state) {
    auto result = p.maxArea(height);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_MaxArea_Linear)->Range(8, 8 << 10)->Complexity();

// ============================================================================
// Benchmark: trap (Trapping Rain Water)
// ============================================================================

static void BM_Trap(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> height(n);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(0, 100);
  for (auto &h : height) {
    h = dist(rng);
  }

  for (auto _ : state) {
    auto result = p.trap(height);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_Trap)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: reverseString
// ============================================================================

static void BM_ReverseString(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  for (auto _ : state) {
    state.PauseTiming();
    vector<char> s(n);
    for (int i = 0; i < n; ++i) {
      s[i] = 'a' + (i % 26);
    }
    state.ResumeTiming();

    p.reverseString(s);
    benchmark::DoNotOptimize(s.data());
    benchmark::ClobberMemory();
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ReverseString)->Range(8, 8 << 14)->Complexity();

// ============================================================================
// Benchmark: sortColors (Dutch National Flag)
// ============================================================================

static void BM_SortColors(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  for (auto _ : state) {
    state.PauseTiming();
    vector<int> nums(n);
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, 2);
    for (auto &num : nums) {
      num = dist(rng);
    }
    state.ResumeTiming();

    p.sortColors(nums);
    benchmark::DoNotOptimize(nums.data());
    benchmark::ClobberMemory();
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_SortColors)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: compareVersion
// ============================================================================

static void BM_CompareVersion(benchmark::State &state) {
  Purgatory p;
  string v1 = "1.0.1";
  string v2 = "1.0.0";

  for (auto _ : state) {
    auto result = p.compareVersion(v1, v2);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CompareVersion);

static void BM_CompareVersion_Long(benchmark::State &state) {
  Purgatory p;
  string v1 = "1.2.3.4.5.6.7.8.9.10.11.12.13.14.15";
  string v2 = "1.2.3.4.5.6.7.8.9.10.11.12.13.14.16";

  for (auto _ : state) {
    auto result = p.compareVersion(v1, v2);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CompareVersion_Long);

// ============================================================================
// Benchmark: findContentChildren (Greedy)
// ============================================================================

static void BM_FindContentChildren(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> g(n), s(n);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(1, 100);
  for (int i = 0; i < n; ++i) {
    g[i] = dist(rng);
    s[i] = dist(rng);
  }

  for (auto _ : state) {
    auto result = p.findContentChildren(g, s);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_FindContentChildren)->Range(8, 8 << 10)->Complexity();

// ============================================================================
// Benchmark: checkInclusion (Permutation in String)
// ============================================================================

static void BM_CheckInclusion(benchmark::State &state) {
  Purgatory p;
  string s1 = "ab";
  string s2 = "eidbaooo";

  for (auto _ : state) {
    auto result = p.checkInclusion(s1, s2);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CheckInclusion);

static void BM_CheckInclusion_Long(benchmark::State &state) {
  Purgatory p;
  string s1 = "abc";
  string s2(10000, 'x');
  s2 += "bca"; // Match at end
  s2 += string(10000, 'y');

  for (auto _ : state) {
    auto result = p.checkInclusion(s1, s2);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CheckInclusion_Long);

// ============================================================================
// Benchmark: judgeSquareSum
// ============================================================================

static void BM_JudgeSquareSum(benchmark::State &state) {
  Purgatory p;
  int c = 5;

  for (auto _ : state) {
    auto result = p.judgeSquareSum(c);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_JudgeSquareSum);

static void BM_JudgeSquareSum_Large(benchmark::State &state) {
  Purgatory p;
  int c = 2147483647; // Large number

  for (auto _ : state) {
    auto result = p.judgeSquareSum(c);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_JudgeSquareSum_Large);

// ============================================================================
// Benchmark: countBinarySubstrings
// ============================================================================

static void BM_CountBinarySubstrings(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string s;
  s.reserve(n);

  // Generate alternating groups
  for (int i = 0; i < n; ++i) {
    s += ((i / 5) % 2) ? '1' : '0';
  }

  for (auto _ : state) {
    auto result = p.countBinarySubstrings(s);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_CountBinarySubstrings)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: countSubstrings (Palindromic Substrings)
// ============================================================================

static void BM_CountSubstrings(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string s(n, 'a');

  for (auto _ : state) {
    auto result = p.countSubstrings(s);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_CountSubstrings)->Range(8, 1024)->Complexity();

// ============================================================================
// Benchmark: longestMountain
// ============================================================================

static void BM_LongestMountain(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> arr(n);

  // Create mountain-like pattern
  for (int i = 0; i < n; ++i) {
    arr[i] = (i < n / 2) ? i : (n - i);
  }

  for (auto _ : state) {
    auto result = p.longestMountain(arr);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_LongestMountain)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: reverseStr
// ============================================================================

static void BM_ReverseStr(benchmark::State &state) {
  Purgatory p;
  string s = "abcdefghijklmnopqrstuvwxyz";
  int k = 2;

  for (auto _ : state) {
    auto result = p.reverseStr(s, k);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_ReverseStr);

// ============================================================================
// Benchmark: shortestToChar
// ============================================================================

static void BM_ShortestToChar(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string s(n, 'x');
  s[n / 2] = 'e'; // Target char in middle
  char c = 'e';

  for (auto _ : state) {
    auto result = p.shortestToChar(s, c);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ShortestToChar)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: getCommon
// ============================================================================

static void BM_GetCommon(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> nums1(n), nums2(n);

  for (int i = 0; i < n; ++i) {
    nums1[i] = i * 2;
    nums2[i] = i * 2 + 1;
  }
  nums1[n / 2] = 100;
  nums2[n / 2] = 100; // Common element

  for (auto _ : state) {
    auto result = p.getCommon(nums1, nums2);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_GetCommon)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: reverseOnlyLetters
// ============================================================================

static void BM_ReverseOnlyLetters(benchmark::State &state) {
  Purgatory p;
  string s = "a-bC-dEf-ghIj";

  for (auto _ : state) {
    auto result = p.reverseOnlyLetters(s);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_ReverseOnlyLetters);

static void BM_ReverseOnlyLetters_Long(benchmark::State &state) {
  Purgatory p;
  string s;
  s.reserve(10000);
  for (int i = 0; i < 10000; ++i) {
    if (i % 3 == 0) {
      s += '-';
    } else {
      s += 'a' + (i % 26);
    }
  }

  for (auto _ : state) {
    auto result = p.reverseOnlyLetters(s);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_ReverseOnlyLetters_Long);

// ============================================================================
// Benchmark: numRescueBoats
// ============================================================================

static void BM_NumRescueBoats(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> people(n);
  int limit = 100;

  mt19937 rng(42);
  uniform_int_distribution<int> dist(1, 100);
  for (auto &person : people) {
    person = dist(rng);
  }

  for (auto _ : state) {
    auto result = p.numRescueBoats(people, limit);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_NumRescueBoats)->Range(8, 8 << 10)->Complexity();

// ============================================================================
// Benchmark: applyOperations
// ============================================================================

static void BM_ApplyOperations(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  for (auto _ : state) {
    state.PauseTiming();
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      nums[i] = i % 10;
    }
    state.ResumeTiming();

    auto result = p.applyOperations(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ApplyOperations)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: minimumSteps
// ============================================================================

static void BM_MinimumSteps(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string s(n / 2, '1');
  s += string(n / 2, '0');

  for (auto _ : state) {
    auto result = p.minimumSteps(s);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_MinimumSteps)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: addSpaces
// ============================================================================

static void BM_AddSpaces(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string s(n, 'a');
  vector<int> spaces;
  for (int i = 5; i < n; i += 10) {
    spaces.push_back(i);
  }

  for (auto _ : state) {
    auto result = p.addSpaces(s, spaces);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_AddSpaces)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: isLongPressedName
// ============================================================================

static void BM_IsLongPressedName(benchmark::State &state) {
  Purgatory p;
  string name = "alex";
  string typed = "aaleex";

  for (auto _ : state) {
    auto result = p.isLongPressedName(name, typed);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_IsLongPressedName);

static void BM_IsLongPressedName_Long(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  string name;
  string typed;
  name.reserve(n);
  typed.reserve(n * 2);

  // Generate alternating pattern with long presses
  for (int i = 0; i < n; ++i) {
    char c = 'a' + (i % 26);
    name += c;
    typed += c;
    typed += c; // Double each character
  }

  for (auto _ : state) {
    auto result = p.isLongPressedName(name, typed);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_IsLongPressedName_Long)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: findTheArrayConcVal
// ============================================================================

static void BM_FindTheArrayConcVal_Small(benchmark::State &state) {
  Purgatory p;
  vector<int> nums = {7, 52, 2, 4};

  for (auto _ : state) {
    auto result = p.findTheArrayConcVal(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_FindTheArrayConcVal_Small);

static void BM_FindTheArrayConcVal(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> nums(n);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(1, 99999);
  for (auto &num : nums) {
    num = dist(rng);
  }

  for (auto _ : state) {
    auto result = p.findTheArrayConcVal(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_FindTheArrayConcVal)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: maxNumOfMarkedIndices
// ============================================================================

static void BM_MaxNumOfMarkedIndices_Small(benchmark::State &state) {
  Purgatory p;
  vector<int> nums = {3, 5, 2, 4};

  for (auto _ : state) {
    auto result = p.maxNumOfMarkedIndices(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_MaxNumOfMarkedIndices_Small);

static void BM_MaxNumOfMarkedIndices(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> nums(n);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(1, 1000000);
  for (auto &num : nums) {
    num = dist(rng);
  }

  for (auto _ : state) {
    auto result = p.maxNumOfMarkedIndices(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_MaxNumOfMarkedIndices)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Main
// ============================================================================

BENCHMARK_MAIN();
