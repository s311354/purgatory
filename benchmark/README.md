# Performance Benchmarks

This directory contains microbenchmarks for purgatory algorithms using [Google Benchmark](https://github.com/google/benchmark).

## Quick Start

```bash
# Build with benchmarks
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_BENCHMARKS=ON
cmake --build build --parallel

# Run all benchmarks
./build/benchmark/purgatory_bench

# Generate baseline and verify performance
./benchmark_verify.sh --output baseline.json
./benchmark_verify.sh --baseline baseline.json  # Detects >10% regressions
```

## Configuration

### Regression Thresholds

| Context | Threshold | Purpose |
|---------|-----------|---------|
| **PR Checks** | **10%** | Early detection during code review |
| **CI Alerts** | **20%** | Filter CI noise, catch critical regressions |
| **Custom** | Variable | Override via `--threshold N` or `BENCHMARK_THRESHOLD` |

**Rationale**: 10% catches most real regressions while 20% reduces false positives from CI environment variance.

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
./benchmark_verify.sh --output baseline.json

# Later, verify against baseline
./benchmark_verify.sh --baseline baseline.json

# Custom threshold (e.g., 15%)
./benchmark_verify.sh --baseline baseline.json --threshold 15

# Filter specific benchmarks
./benchmark_verify.sh --baseline baseline.json --filter "BM_TwoSum.*"
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
```bash
./build/benchmark/purgatory_bench --benchmark_filter=.*_Large --benchmark_perf_counters=CYCLES,INSTRUCTIONS
```

### Compare two runs
```bash
# Baseline
./build/benchmark/purgatory_bench --benchmark_out=baseline.json --benchmark_out_format=json

# After optimization
./build/benchmark/purgatory_bench --benchmark_out=optimized.json --benchmark_out_format=json

# Compare
../third-party/benchmark/tools/compare.py benchmarks baseline.json optimized.json
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
```

- **Time**: Wall-clock time per iteration
- **CPU**: CPU time per iteration
- **Iterations**: Number of times the benchmark was executed

### Performance Metrics

The benchmarks track:
- **Time Complexity**: `->Complexity()` validates O(n) behavior
- **Items Processed**: Throughput in items/second
- **Bytes Processed**: Memory bandwidth

## Adding New Benchmarks

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

The project uses a **two-tier threshold approach**:

1. **10% threshold** (PR checks): Stricter detection for code review
   - Catches performance regressions early
   - Used in `benchmark_verify.sh` by default
   - Triggers detailed comparison reports in PRs

2. **20% threshold** (Critical alerts): CI noise tolerance
   - Used by `github-action-benchmark` for persistent tracking
   - Only triggers alerts for significant regressions
   - Accounts for CI environment variability

**Override threshold** using repository variable:
```yaml
# Set in GitHub: Settings → Secrets and variables → Actions → Variables
BENCHMARK_THRESHOLD=15  # Custom threshold percentage
```

**Local verification** with custom threshold:
```bash
./benchmark_verify.sh --baseline baseline.json --threshold 15
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
   ./benchmark_verify.sh --output baseline.json
   
   # Checkout your PR branch and compare
   git checkout your-branch
   cmake --build build --parallel
   ./benchmark_verify.sh --baseline baseline.json
   ```

2. **Identify the cause** - Check what changed:
   ```bash
   # Profile the specific benchmark
   ./build/benchmark/purgatory_bench --benchmark_filter=<RegrassedBenchmark>
   
   # Run with perf for detailed analysis
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

**Temporary adjustment** for noisy CI environment:
```yaml
# Set GitHub Actions variable: BENCHMARK_THRESHOLD=15
# Settings → Secrets and variables → Actions → Variables → New variable
```

**Permanent adjustment** (requires team consensus):
- Edit `.github/workflows/benchmark.yml`
- Update default in line: `REGRESSION_THRESHOLD: ${{ vars.BENCHMARK_THRESHOLD || '10' }}`
- Document reason in commit message
