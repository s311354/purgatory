# Performance Optimization Quick Reference

## Quick Start

### Apply All Quick Wins
```bash
./apply-perf-improvements.sh quick
```

### Build with Optimizations
```bash
cmake -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DPURGATORY_USE_MOLD=ON \
  -DBUILD_BENCHMARKS=ON

cmake --build build --parallel
```

### Run Benchmarks
```bash
./build/benchmark/purgatory_bench
```

## Build Options

| Option | Effect | Build Time | Runtime | When to Use |
|--------|--------|-----------|---------|-------------|
| `-DCMAKE_BUILD_TYPE=Release` | -O3 optimization | +0% | -20% | Always for production |
| `-DPURGATORY_USE_MOLD=ON` | Fast linker | -60% link | 0% | Development & CI |
| `-DPURGATORY_UNITY_BUILD=ON` | Single compilation unit | -40% | 0% | CI only |
| `-DPURGATORY_ENABLE_PROFILING=ON` | gprof support | +0% | +10% | Profiling only |
| `-DBUILD_BENCHMARKS=ON` | Performance tests | +20% | N/A | Development |

## Performance Checklist

### Before Committing
- [ ] Run benchmarks: `./build/benchmark/purgatory_bench`
- [ ] Check for regressions: Compare with baseline
- [ ] Profile if >10% slower: `./build-prof/purgatory src/test.txt && gprof ...`

### For New Algorithms
- [ ] Add benchmark in `benchmark/` directory
- [ ] Verify time complexity: Use `->Complexity()`
- [ ] Test multiple input sizes: Use `->Range(8, 8<<12)`
- [ ] Document in `docs/algorithms/`

### Hot Path Optimization
- [ ] Mark with `inline` if <10 lines
- [ ] Use `const int* data = v.data()` for repeated access
- [ ] Add `__builtin_expect()` for predictable branches
- [ ] Consider `alignas(64)` for cache-line alignment

## Profiling Commands

```bash
# CPU profiling with gprof
cmake -B build-prof -DPURGATORY_ENABLE_PROFILING=ON
cmake --build build-prof
./build-prof/purgatory src/test.txt
gprof ./build-prof/purgatory gmon.out | less

# Memory profiling with valgrind
valgrind --tool=massif ./build/purgatory src/test.txt
ms_print massif.out.* | less

# Cache profiling with cachegrind
valgrind --tool=cachegrind ./build/purgatory src/test.txt
cg_annotate cachegrind.out.* | less

# CPU counters with perf (Linux)
perf stat -e cycles,instructions,cache-misses ./build/purgatory src/test.txt
perf record ./build/purgatory src/test.txt
perf report
```

## Benchmark Interpretation

```
Benchmark                    Time       CPU    Iterations
--------------------------------------------------------
BM_Algorithm/8            45.2 ns   45.1 ns   15534156    (baseline)
BM_Algorithm/64            362 ns    361 ns    1937891    (8x size = 8x time ✓)
BM_Algorithm/512          2890 ns   2887 ns     242373    (64x size = 64x time ✓)
BM_Algorithm_BigO            N/A       N/A        N/A    O(N)
```

- **Good**: Linear growth confirms O(n) complexity
- **Bad**: Quadratic growth indicates O(n²) when expecting O(n)

## Common Optimizations

### 1. Loop Optimization
```cpp
// BEFORE: Repeated vector access
for (int i = 0; i < v.size(); i++) {
    sum += v[i] * 2;
}

// AFTER: Cache pointer and size
const int* data = v.data();
const int n = v.size();
for (int i = 0; i < n; i++) {
    sum += data[i] * 2;
}
```

### 2. Branch Prediction
```cpp
// BEFORE: Unpredictable branch
if (unlikely_condition) { /* ... */ }

// AFTER: With hint
if (__builtin_expect(unlikely_condition, 0)) { /* ... */ }
```

### 3. Reserve Capacity
```cpp
// BEFORE: Multiple reallocations
vector<int> result;
for (int i = 0; i < n; i++) result.push_back(i);

// AFTER: Pre-allocate
vector<int> result;
result.reserve(n);
for (int i = 0; i < n; i++) result.push_back(i);
```

### 4. String Operations
```cpp
// AVOID: Character-by-character
string result;
for (char c : input) result += c;

// PREFER: Reserve or use string_view
string result;
result.reserve(input.size());
for (char c : input) result += c;
```

## Target Performance

| Algorithm Pattern | Expected Complexity | Target µs/1000 items |
|------------------|---------------------|---------------------|
| Two Pointers | O(n) | <10 µs |
| Sliding Window | O(n) | <15 µs |
| Binary Search | O(log n) | <1 µs |
| Hash Map | O(n) | <50 µs |
| Sorting | O(n log n) | <100 µs |
| DFS/BFS | O(V+E) | <200 µs |

## Resources

- Full documentation: [PERFORMANCE_IMPROVEMENTS.md](.github/PERFORMANCE_IMPROVEMENTS.md)
- Benchmark guide: [benchmark/README.md](benchmark/README.md)
- Algorithm catalog: [docs/ALGORITHMS.md](docs/ALGORITHMS.md)
- CI/CD details: [.github/CI_CD.md](.github/CI_CD.md)
