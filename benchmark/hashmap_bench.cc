#include "../src/purgatory.h"
#include <benchmark/benchmark.h>
#include <random>
#include <string>
#include <vector>

using namespace std;
using namespace purgatory;

// ============================================================================
// Benchmark: canConstruct (Ransom Note)
// ============================================================================

static void BM_CanConstruct_Small(benchmark::State &state) {
  Purgatory p;
  string ransomNote = "aa";
  string magazine = "aab";

  for (auto _ : state) {
    auto result = p.canConstruct(ransomNote, magazine);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_CanConstruct_Small);

static void BM_CanConstruct(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  string ransomNote;
  string magazine;
  ransomNote.reserve(n);
  magazine.reserve(n * 2);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(0, 25);

  for (int i = 0; i < n; ++i) {
    char c = 'a' + dist(rng);
    ransomNote += c;
    magazine += c;
    magazine += static_cast<char>('a' + dist(rng)); // Extra chars
  }

  for (auto _ : state) {
    auto result = p.canConstruct(ransomNote, magazine);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_CanConstruct)->Range(8, 8 << 14)->Complexity();

// ============================================================================
// Benchmark: groupAnagrams
// ============================================================================

static void BM_GroupAnagrams_Small(benchmark::State &state) {
  Purgatory p;
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

  for (auto _ : state) {
    auto result = p.groupAnagrams(strs);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_GroupAnagrams_Small);

static void BM_GroupAnagrams(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  mt19937 rng(42);
  uniform_int_distribution<int> length_dist(3, 10);
  uniform_int_distribution<int> char_dist(0, 25);

  for (auto _ : state) {
    state.PauseTiming();
    vector<string> strs(n);
    for (int i = 0; i < n; ++i) {
      int len = length_dist(rng);
      strs[i].reserve(len);
      for (int j = 0; j < len; ++j) {
        strs[i] += static_cast<char>('a' + char_dist(rng));
      }
    }
    state.ResumeTiming();

    auto result = p.groupAnagrams(strs);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_GroupAnagrams)->Range(8, 8 << 10)->Complexity();

// ============================================================================
// Benchmark: longestConsecutive
// ============================================================================

static void BM_LongestConsecutive_Small(benchmark::State &state) {
  Purgatory p;
  vector<int> nums = {100, 4, 200, 1, 3, 2};

  for (auto _ : state) {
    auto result = p.longestConsecutive(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_LongestConsecutive_Small);

static void BM_LongestConsecutive(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(-100000, 100000);

  for (auto _ : state) {
    state.PauseTiming();
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      nums[i] = dist(rng);
    }
    state.ResumeTiming();

    auto result = p.longestConsecutive(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
}
BENCHMARK(BM_LongestConsecutive)->Range(8, 8 << 12)->Complexity();

// ============================================================================
// Benchmark: findSubstring (Substring with Concatenation)
// ============================================================================

static void BM_FindSubstring_Small(benchmark::State &state) {
  Purgatory p;
  string s = "barfoothefoobarman";
  vector<string> words = {"foo", "bar"};

  for (auto _ : state) {
    auto result = p.findSubstring(s, words);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_FindSubstring_Small);

static void BM_FindSubstring_Medium(benchmark::State &state) {
  Purgatory p;
  string s = "wordgoodgoodgoodbestword";
  vector<string> words = {"word", "good", "best", "word"};

  for (auto _ : state) {
    auto result = p.findSubstring(s, words);
    benchmark::DoNotOptimize(result);
  }
  state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_FindSubstring_Medium);

static void BM_FindSubstring_Long(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  string s;
  s.reserve(n);
  for (int i = 0; i < n; ++i) {
    s += static_cast<char>('a' + (i % 26));
  }

  vector<string> words = {"abc", "def", "ghi"};

  for (auto _ : state) {
    auto result = p.findSubstring(s, words);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_FindSubstring_Long)->Range(100, 10000)->Complexity();

static void BM_FindSubstring_ManyWords(benchmark::State &state) {
  Purgatory p;

  // Create string with repeating pattern
  string s;
  s.reserve(5000);
  for (int i = 0; i < 1000; ++i) {
    s += "abcde";
  }

  // Create many short words
  vector<string> words;
  int word_count = state.range(0);
  words.reserve(word_count);
  for (int i = 0; i < word_count; ++i) {
    words.push_back("ab");
  }

  for (auto _ : state) {
    auto result = p.findSubstring(s, words);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(word_count);
}
BENCHMARK(BM_FindSubstring_ManyWords)->Range(2, 100)->Complexity();

// ============================================================================
// Benchmark: containsDuplicate
// ============================================================================

static void BM_ContainsDuplicate_NoDup(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);
  vector<int> nums(n);

  for (int i = 0; i < n; ++i) {
    nums[i] = i;
  }

  for (auto _ : state) {
    auto result = p.containsDuplicate(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ContainsDuplicate_NoDup)->Range(8, 8 << 14)->Complexity();

static void BM_ContainsDuplicate_WithDup(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  for (auto _ : state) {
    state.PauseTiming();
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      nums[i] = i;
    }
    nums[n - 1] = 0; // Duplicate at end (worst case)
    state.ResumeTiming();

    auto result = p.containsDuplicate(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ContainsDuplicate_WithDup)->Range(8, 8 << 14)->Complexity();

static void BM_ContainsDuplicate_Random(benchmark::State &state) {
  Purgatory p;
  int n = state.range(0);

  mt19937 rng(42);
  uniform_int_distribution<int> dist(0,
                                     n / 2); // High probability of duplicates

  for (auto _ : state) {
    state.PauseTiming();
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      nums[i] = dist(rng);
    }
    state.ResumeTiming();

    auto result = p.containsDuplicate(nums);
    benchmark::DoNotOptimize(result);
  }
  state.SetComplexityN(n);
  state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_ContainsDuplicate_Random)->Range(8, 8 << 14)->Complexity();

// ============================================================================
// Benchmarks for hashmap algorithms
// ============================================================================
// Note: BENCHMARK_MAIN() is defined in twopointers_bench.cc
