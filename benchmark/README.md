# Performance Benchmarks

This directory contains microbenchmarks for purgatory algorithms using [Google Benchmark](https://github.com/google/benchmark).

## Benchmark Organization

**Current Implementation**: 46 benchmarks across 2 benchmark files

### Benchmark Files

1. **twopointers_bench.cc** (33 benchmarks)
   - Two pointers and string manipulation algorithms
   - Includes: isPalindrome, twoSum, maxArea, trap, reverseString, sortColors, compareVersion, checkInclusion, judgeSquareSum, countBinarySubstrings, countSubstrings, longestMountain, reverseStr, shortestToChar, getCommon, reverseOnlyLetters, numRescueBoats, applyOperations, minimumSteps, addSpaces, isLongPressedName, findTheArrayConcVal, maxNumOfMarkedIndices, findContentChildren

2. **hashmap_bench.cc** (13 benchmarks)
   - Hash map and hash set algorithms
   - Includes: canConstruct, groupAnagrams, longestConsecutive, findSubstring, containsDuplicate

All benchmark files are compiled into a single `purgatory_bench` executable.

### Benchmark Categories

**Two Pointers & String Algorithms** (33 benchmarks):
- String validation: isPalindrome, checkInclusion, isLongPressedName
- Array operations: twoSum, maxArea, trap, reverseString, sortColors
- String transformations: compareVersion, reverseStr, reverseOnlyLetters, addSpaces
- Greedy algorithms: findContentChildren, numRescueBoats
- Array manipulation: applyOperations, minimumSteps, findTheArrayConcVal, maxNumOfMarkedIndices
- Pattern detection: countBinarySubstrings, countSubstrings, longestMountain
- Distance calculations: shortestToChar, getCommon
- Mathematical: judgeSquareSum

**Hash Map & Set Algorithms** (13 benchmarks):
- Frequency counting: canConstruct
- Grouping & anagrams: groupAnagrams
- Sequence detection: longestConsecutive
- Substring matching: findSubstring (with multiple variants)
- Duplicate detection: containsDuplicate (with no-dup, with-dup, and random variants)

Each algorithm typically includes multiple variants:
- **_Small**: Fixed small input for basic performance
- **_Large/Long**: Scalable input with complexity analysis
- **_Random**: Randomized input for average-case behavior
- **Parameterized**: Uses `->Range()` for scaling analysis with `->Complexity()`

## Quick Start

```bash
# Build with benchmarks
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_BENCHMARKS=ON
cmake --build build --parallel

# Run all benchmarks (from both twopointers_bench.cc and hashmap_bench.cc)
./build/benchmark/purgatory_bench

# Run specific category
./build/benchmark/purgatory_bench --benchmark_filter=".*TwoSum.*"
./build/benchmark/purgatory_bench --benchmark_filter=".*HashMap.*|.*GroupAnagrams.*"

# Generate baseline and verify performance
../scripts/benchmark_verify.sh --output baseline.json
../scripts/benchmark_verify.sh --baseline baseline.json  # Detects >10% regressions
```

## Configuration

### Regression Thresholds

| Context | Threshold | Purpose |
|---------|-----------|---------|
| **Local Verification** | **10%** (default) | Used by `benchmark_verify.sh` for local testing |
| **CI (main branch)** | **10%** | Regression detection on main branch pushes |
| **Custom** | Variable | Override via `--threshold N` flag |

**Rationale**: 10% catches most real regressions while allowing some variance from system and compiler differences.

## Building Benchmarks

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_BENCHMARKS=ON \
  -DBUILD_TESTING=ON

cmake --build build --parallel
```

## Running Benchmarks

### Run all benchmarks
```bash
./build/benchmark/purgatory_bench
```

### Filter specific benchmarks
```bash
./build/benchmark/purgatory_bench --benchmark_filter=IsPalindrome
```

### Verify performance (detect >10% regressions)
```bash
# Generate baseline
../scripts/benchmark_verify.sh --output baseline.json

# Later, verify against baseline
../scripts/benchmark_verify.sh --baseline baseline.json

# Custom threshold (e.g., 15%)
../scripts/benchmark_verify.sh --baseline baseline.json --threshold 15

# Filter specific benchmarks
../scripts/benchmark_verify.sh --baseline baseline.json --filter "BM_TwoSum.*"
```

The verification script automatically:
- Runs benchmarks and saves JSON results
- Compares current performance against baseline
- Highlights regressions >threshold%
- Reports improvements and unchanged benchmarks
- Returns exit code 1 if regressions detected (CI-friendly)

**Standalone Python comparison** (for custom workflows):
```bash
# Compare two JSON files directly
./benchmark/benchmark_compare.py baseline.json current.json --threshold 10
```

### Output as JSON (for CI/analysis)
```bash
./build/benchmark/purgatory_bench --benchmark_format=json > results.json
```

### Run with CPU profiling

**Note**: Requires `perf` to be installed. Run `./install-build-deps.sh` to install all dependencies including `perf`.

```bash
./build/benchmark/purgatory_bench --benchmark_filter=.*_Large --benchmark_perf_counters=CYCLES,INSTRUCTIONS
```

### Compare two runs
```bash
# Baseline
./build/benchmark/purgatory_bench --benchmark_out=baseline.json --benchmark_out_format=json

# After optimization
./build/benchmark/purgatory_bench --benchmark_out=optimized.json --benchmark_out_format=json

# Compare using benchmark_compare.py
./benchmark/benchmark_compare.py baseline.json optimized.json --threshold 10
```

## Benchmark Options

| Flag | Description |
|------|-------------|
| `--benchmark_filter=<regex>` | Run only matching benchmarks |
| `--benchmark_min_time=<N>` | Minimum time per benchmark (default: 0.5s) |
| `--benchmark_repetitions=<N>` | Repeat each benchmark N times |
| `--benchmark_report_aggregates_only={true\|false}` | Show only aggregate stats |
| `--benchmark_display_aggregates_only={true\|false}` | Display only aggregates |
| `--benchmark_format=<console\|json\|csv>` | Output format |
| `--benchmark_counters_tabular={true\|false}` | Tabular counter display |

## Interpreting Results

```
Benchmark                        Time             CPU   Iterations
--------------------------------------------------------------------
BM_IsPalindrome_Short          156 ns          156 ns      4480000
BM_IsPalindrome_Long         15234 ns        15229 ns        45926
BM_CanConstruct/8               18.7 ns        18.7 ns     7516089
BM_GroupAnagrams/64           14089 ns        14105 ns        9970
```

- **Time**: Wall-clock time per iteration
- **CPU**: CPU time per iteration
- **Iterations**: Number of times the benchmark was executed

### Example Output with Complexity Analysis

```
BM_ContainsDuplicate_Random/8              471 ns          476 ns       296062
BM_ContainsDuplicate_Random/64             646 ns          652 ns       215190
BM_ContainsDuplicate_Random/512           1337 ns         1343 ns       102410
BM_ContainsDuplicate_Random/4096          4002 ns         4001 ns        34604
BM_ContainsDuplicate_Random_BigO          0.29 N          0.29 N
BM_ContainsDuplicate_Random_RMS             24 %            24 %
```

The `_BigO` line shows the measured time complexity (0.29 N indicates O(N) behavior), and `_RMS` shows the variance.

### Performance Metrics

The benchmarks track:
- **Time Complexity**: `->Complexity()` validates O(n) behavior
- **Items Processed**: Throughput in items/second
- **Bytes Processed**: Memory bandwidth

## Adding New Benchmarks

### 1. Choose or Create Benchmark File

Add benchmarks to existing files by category:
- **twopointers_bench.cc**: Two pointers, string manipulation, greedy algorithms
- **hashmap_bench.cc**: Hash map/set operations, frequency counting

Or create a new file for a different category (e.g., `array_bench.cc`, `tree_bench.cc`).

### 2. Implement Benchmark Function

```cpp
static void BM_YourAlgorithm(benchmark::State& state) {
  Purgatory p;
  // Setup
  vector<int> data = prepareTestData();
  
  for (auto _ : state) {
    // Code to benchmark
    auto result = p.yourAlgorithm(data);
    benchmark::DoNotOptimize(result);
  }
  
  // Optional: track complexity
  state.SetComplexityN(data.size());
}
BENCHMARK(BM_YourAlgorithm)->Range(8, 8<<10)->Complexity();
```

### 3. Update Build Configuration (if creating new file)

If creating a new benchmark file, add it to `benchmark/CMakeLists.txt`:

```cmake
add_executable(purgatory_bench
    twopointers_bench.cc
    hashmap_bench.cc
    your_new_bench.cc  # Add your file here
)
```

**Important**: Only `twopointers_bench.cc` should have `BENCHMARK_MAIN()` at the end. All other benchmark files should omit this macro to avoid multiple `main()` definitions during linking.

## Best Practices

1. **Avoid optimization removal**: Use `DoNotOptimize()` on results
2. **Measure stable state**: Exclude setup with `PauseTiming()`/`ResumeTiming()`
3. **Use deterministic data**: Seed RNGs for reproducibility
4. **Test multiple sizes**: Use `->Range()` or `->RangeMultiplier()`
5. **Validate complexity**: Add `->Complexity()` to verify Big-O
6. **Run in Release mode**: Always benchmark with optimizations enabled

## CI Integration

Benchmarks run automatically on:
- Pushes to `main` branch
- Pull requests targeting `main` (when `src/`, `CMakeLists.txt`, or `benchmark/` changes)
- Version tags (`v*`)
- Manual workflow dispatch

### Regression Detection Strategy

The CI workflow performs regression detection on **main branch pushes only**:

- **Automatic baseline updates**: Each main branch push becomes the new baseline
- **10% threshold**: Regressions >10% trigger workflow failure
- **Artifact storage**: Results stored for 90 days via GitHub Actions artifacts
- **Historical tracking**: Compare against the most recent main branch baseline

**Note**: Regression detection does not run on pull requests. To verify performance before merging:
```bash
# On your PR branch
git checkout main
./benchmark_verify.sh --output main_baseline.json
git checkout your-branch
./benchmark_verify.sh --baseline main_baseline.json
```

**Local verification** with custom threshold:
```bash
../scripts/benchmark_verify.sh --baseline baseline.json --threshold 15
```

## Hardware Info

Check CPU features and caching:
```bash
lscpu | grep -E "Model name|Thread|Core|Cache"
```

Benchmarks are sensitive to:
- CPU frequency scaling (disable with `cpupower`)
- Thermal throttling
- Background processes
- Cache state

For consistent results, run on idle system with fixed CPU frequency.

## Troubleshooting Performance Regressions

### Regression Detected in PR

If you see "Performance regression detected" in your PR:

1. **Verify it's real** - Run locally to confirm:
   ```bash
   # Checkout main branch and generate baseline
   git checkout main
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_BENCHMARKS=ON
   cmake --build build --parallel
   ./scripts/benchmark_verify.sh --output baseline.json
   
   # Checkout your PR branch and compare
   git checkout your-branch
   cmake --build build --parallel
   ./scripts/benchmark_verify.sh --baseline baseline.json
   ```

2. **Identify the cause** - Check what changed:
   ```bash
   # Profile the specific benchmark
   ./build/benchmark/purgatory_bench --benchmark_filter=<RegrassedBenchmark>
   
   # Run with perf for detailed analysis (requires perf installation)
   # Install via: sudo ./install-build-deps.sh
   perf record ./build/benchmark/purgatory_bench --benchmark_filter=<name>
   perf report
   ```

3. **Common causes**:
   - **Algorithm complexity increase**: O(n) → O(n²)
   - **Memory allocations**: Heap allocations in hot path
   - **Cache misses**: Changed data structure layout
   - **Compiler optimizations**: Inlining disabled, loop unrolling affected
   - **False positive**: CI variance (re-run the workflow)

4. **Fix strategies**:
   ```cpp
   // Bad: Repeated allocations
   for (int i = 0; i < n; i++) {
       vector<int> temp;  // ❌ Allocates every iteration
   }
   
   // Good: Reuse allocation
   vector<int> temp;
   temp.reserve(expected_size);
   for (int i = 0; i < n; i++) {
       temp.clear();  // ✅ Reuses memory
   }
   ```

5. **If regression is acceptable**:
   - Document the tradeoff in PR description
   - Verify it's necessary for correctness/features
   - Consider adjusting threshold if CI environment changed

### CI-Specific Regressions

If regressions only appear in CI:

```bash
# Compare with CI flags
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=g++-12 \
  -DPURGATORY_USE_MOLD=ON \
  -DBUILD_BENCHMARKS=ON
```

### Adjusting Thresholds

**For local testing**, use the `--threshold` flag:
```bash
../scripts/benchmark_verify.sh --baseline baseline.json --threshold 15
```

**To change CI threshold** (requires editing workflow):
- Edit `.github/workflows/benchmark.yml`
- Locate the `benchmark_compare.py` call in the "Compare against baseline" step
- Change `--threshold 10` to your desired percentage
- Document the reason in your commit message
