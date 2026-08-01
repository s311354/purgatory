# Benchmark Verification System

A decoupled system for detecting performance regressions in purgatory benchmarks.

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                      benchmark_verify.sh                        │
│                     (Shell Orchestrator)                        │
│                                                                 │
│  • Parse command-line arguments                                │
│  • Validate benchmark binary exists                            │
│  • Run Google Benchmark with JSON output                       │
│  • Manage temporary files                                      │
│  • Delegate comparison to Python script                        │
└────────────────────┬────────────────────────────────────────────┘
                     │
                     │ Calls
                     ▼
┌─────────────────────────────────────────────────────────────────┐
│               benchmark/benchmark_compare.py                    │
│                    (Python Analyzer)                            │
│                                                                 │
│  • Load and parse JSON benchmark results                       │
│  • Handle different benchmark types (iteration, BigO, RMS)     │
│  • Calculate percentage changes                                │
│  • Categorize: regressions, improvements, unchanged            │
│  • Generate colored comparison report                          │
│  • Return exit code (0=pass, 1=regression detected)            │
└─────────────────────────────────────────────────────────────────┘
```

## Components

### 1. benchmark_verify.sh (Shell Script)
**Responsibility**: Orchestration and file management

**Features**:
- Command-line argument parsing
- Benchmark binary validation
- Executes Google Benchmark with specified filters
- Manages baseline and comparison JSON files
- Provides user-friendly output formatting

**Usage**:
```bash
# Generate baseline
./benchmark_verify.sh --output baseline.json

# Compare against baseline
./benchmark_verify.sh --baseline baseline.json

# Custom threshold
./benchmark_verify.sh --baseline baseline.json --threshold 15

# Filter specific benchmarks
./benchmark_verify.sh --baseline baseline.json --filter "BM_TwoSum.*"
```

### 2. benchmark/benchmark_compare.py (Python Script)
**Responsibility**: JSON analysis and comparison logic

**Features**:
- Loads benchmark JSON files
- Extracts time values from different benchmark types:
  - Regular benchmarks: `cpu_time`
  - BigO aggregates: `cpu_coefficient`
  - RMS aggregates: skipped (percentage, not time)
- Calculates percentage changes
- Categorizes changes by threshold
- Generates detailed comparison reports
- Returns appropriate exit codes

**Usage (Standalone)**:
```bash
./benchmark/benchmark_compare.py baseline.json current.json --threshold 10
```

**API** (for integration):
```python
from benchmark_compare import load_benchmarks, compare_benchmarks, print_summary

baseline = load_benchmarks('baseline.json')
current = load_benchmarks('current.json')
regressions, improvements, unchanged = compare_benchmarks(baseline, current, threshold=10.0)
exit_code = print_summary(len(baseline), improvements, unchanged, regressions, 10.0)
```

## Decoupling Benefits

### 1. **Modularity**
- Shell script can be replaced with different orchestrators (Python, Make, etc.)
- Python comparison logic can be reused in other contexts

### 2. **Testability**
- Python script can be unit tested independently
- Shell script logic is simplified and easier to maintain

### 3. **Flexibility**
- Python script can be imported as a library
- Direct JSON comparison without running benchmarks
- Easy to integrate into CI/CD pipelines

### 4. **Maintainability**
- Python code is easier to debug than embedded heredocs
- Proper error handling and type hints
- Clear separation of concerns

## Data Flow

```
User Command
    ↓
benchmark_verify.sh
    ↓
    ├─→ Run Google Benchmark → JSON output
    ↓
    └─→ Call benchmark_compare.py
            ↓
            ├─→ Load baseline JSON
            ├─→ Load current JSON
            ├─→ Extract time values (handle BigO/RMS)
            ├─→ Calculate % changes
            ├─→ Categorize results
            └─→ Print report + exit code
                    ↓
            Return to shell script
                    ↓
            Exit with appropriate code
```

## Special Cases Handled

### Google Benchmark Output Types

1. **Regular Benchmarks** (run_type: "iteration")
   ```json
   {"name": "BM_Function", "cpu_time": 123.45, ...}
   ```
   ✓ Uses `cpu_time` field

2. **BigO Aggregates** (run_type: "aggregate", aggregate_name: "BigO")
   ```json
   {"name": "BM_Function_BigO", "cpu_coefficient": 1.23, "big_o": "N", ...}
   ```
   ✓ Uses `cpu_coefficient` field

3. **RMS Aggregates** (run_type: "aggregate", aggregate_name: "RMS")
   ```json
   {"name": "BM_Function_RMS", "rms": 0.15, ...}
   ```
   ✓ Skipped (percentage, not time measurement)

## Exit Codes

- `0`: Success (no regressions detected)
- `1`: Failure (regressions detected OR error occurred)

