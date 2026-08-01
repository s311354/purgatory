#!/usr/bin/env python3
"""
benchmark_compare.py - Compare benchmark results and detect performance regressions

Usage:
    benchmark_compare.py <baseline.json> <current.json> [--threshold <percent>]
"""

import json
import sys
from typing import Dict, List, Tuple, Optional


# Color codes
RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[1;33m'
BLUE = '\033[0;34m'
NC = '\033[0m'


def get_time_value(bench: Dict) -> float:
    """Extract time value from benchmark entry, handling different types.
    
    Args:
        bench: Benchmark entry dictionary
        
    Returns:
        Time value in nanoseconds, or 0 if not applicable
    """
    # BigO/RMS aggregates use coefficients instead of cpu_time
    if bench.get('run_type') == 'aggregate':
        agg_name = bench.get('aggregate_name')
        if agg_name == 'BigO':
            # Use cpu_coefficient for BigO entries
            return bench.get('cpu_coefficient', 0)
        elif agg_name == 'RMS':
            # RMS is a percentage, not a time - skip it
            return 0
    # Regular benchmarks use cpu_time
    return bench.get('cpu_time', 0)


def load_benchmarks(filepath: str) -> Dict[str, float]:
    """Load benchmark results from JSON file.
    
    Args:
        filepath: Path to JSON file
        
    Returns:
        Dictionary mapping benchmark name to time value
    """
    try:
        with open(filepath, 'r') as f:
            data = json.load(f)
    except FileNotFoundError:
        print(f"{RED}Error: File not found: {filepath}{NC}", file=sys.stderr)
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"{RED}Error: Invalid JSON in {filepath}: {e}{NC}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"{RED}Error loading {filepath}: {e}{NC}", file=sys.stderr)
        sys.exit(1)
    
    # Build lookup table
    benchmarks = {}
    for bench in data.get('benchmarks', []):
        name = bench['name']
        time_val = get_time_value(bench)
        if time_val > 0:  # Only store if we have a valid time
            benchmarks[name] = time_val
    
    return benchmarks


def compare_benchmarks(
    baseline: Dict[str, float],
    current: Dict[str, float],
    threshold: float
) -> Tuple[List[Tuple], List[Tuple], List[Tuple]]:
    """Compare current benchmarks against baseline.
    
    Args:
        baseline: Baseline benchmark times
        current: Current benchmark times
        threshold: Regression threshold percentage
        
    Returns:
        Tuple of (regressions, improvements, unchanged) lists
    """
    regressions = []
    improvements = []
    unchanged = []
    
    for name, current_time in current.items():
        if name not in baseline:
            print(f"{YELLOW}NEW{NC}     {name:50s} {current_time:12.2f} ns")
            continue
        
        baseline_time = baseline[name]
        
        if baseline_time == 0:
            continue
        
        percent_change = ((current_time - baseline_time) / baseline_time) * 100
        
        # Categorize the change
        if percent_change > threshold:
            status = f"{RED}SLOWER{NC}"
            regressions.append((name, baseline_time, current_time, percent_change))
        elif percent_change < -threshold:
            status = f"{GREEN}FASTER{NC}"
            improvements.append((name, baseline_time, current_time, percent_change))
        else:
            status = f"{GREEN}OK{NC}    "
            unchanged.append((name, baseline_time, current_time, percent_change))
        
        # Format output
        change_str = f"{percent_change:+6.1f}%"
        if percent_change > threshold:
            change_str = f"{RED}{change_str}{NC}"
        elif percent_change < -threshold:
            change_str = f"{GREEN}{change_str}{NC}"
        
        print(f"{status} {name:50s} {baseline_time:12.2f} -> {current_time:12.2f} ns ({change_str})")
    
    return regressions, improvements, unchanged


def print_summary(
    baseline_count: int,
    improvements: List[Tuple],
    unchanged: List[Tuple],
    regressions: List[Tuple],
    threshold: float
) -> int:
    """Print comparison summary and return exit code.
    
    Args:
        baseline_count: Number of benchmarks in baseline
        improvements: List of improved benchmarks
        unchanged: List of unchanged benchmarks
        regressions: List of regressed benchmarks
        threshold: Threshold percentage used
        
    Returns:
        Exit code (0 for success, 1 for regressions detected)
    """
    print("")
    print("=" * 80)
    print(f"{BLUE}SUMMARY{NC}")
    print("=" * 80)
    print(f"Total benchmarks:  {baseline_count}")
    print(f"{GREEN}Improvements:{NC}      {len(improvements):3d} (>{threshold}% faster)")
    print(f"{GREEN}Unchanged:{NC}         {len(unchanged):3d} (within ±{threshold}%)")
    print(f"{RED}Regressions:{NC}       {len(regressions):3d} (>{threshold}% slower)")
    print("")
    
    # Detail regressions
    if regressions:
        print(f"{RED}PERFORMANCE REGRESSIONS DETECTED!{NC}")
        print("")
        print(f"{'Benchmark':<50s} {'Baseline':>12s} {'Current':>12s} {'Change':>10s}")
        print("-" * 90)
        for name, baseline_t, current_t, pct in sorted(regressions, key=lambda x: x[3], reverse=True):
            print(f"{name:<50s} {baseline_t:12.2f} {current_t:12.2f} {pct:+9.1f}%")
        print("")
        return 1
    else:
        print(f"{GREEN}✓ No performance regressions detected!{NC}")
        if improvements:
            print("")
            print(f"{GREEN}Notable improvements:{NC}")
            print(f"{'Benchmark':<50s} {'Baseline':>12s} {'Current':>12s} {'Change':>10s}")
            print("-" * 90)
            for name, baseline_t, current_t, pct in sorted(improvements, key=lambda x: x[3])[:5]:
                print(f"{name:<50s} {baseline_t:12.2f} {current_t:12.2f} {pct:+9.1f}%")
        return 0


def main():
    """Main entry point."""
    if len(sys.argv) < 3:
        print("Usage: benchmark_compare.py <baseline.json> <current.json> [--threshold <percent>]")
        sys.exit(1)
    
    baseline_file = sys.argv[1]
    current_file = sys.argv[2]
    threshold = 10.0  # Default threshold
    
    # Parse optional threshold argument
    if len(sys.argv) >= 5 and sys.argv[3] == '--threshold':
        try:
            threshold = float(sys.argv[4])
        except ValueError:
            print(f"{RED}Error: Invalid threshold value: {sys.argv[4]}{NC}", file=sys.stderr)
            sys.exit(1)
    
    # Load benchmark data
    baseline = load_benchmarks(baseline_file)
    current = load_benchmarks(current_file)
    
    if not baseline:
        print(f"{RED}Error: No valid benchmarks found in baseline file{NC}", file=sys.stderr)
        sys.exit(1)
    
    if not current:
        print(f"{RED}Error: No valid benchmarks found in current file{NC}", file=sys.stderr)
        sys.exit(1)
    
    # Compare benchmarks
    regressions, improvements, unchanged = compare_benchmarks(baseline, current, threshold)
    
    # Print summary and exit
    exit_code = print_summary(len(baseline), improvements, unchanged, regressions, threshold)
    sys.exit(exit_code)


if __name__ == '__main__':
    main()
