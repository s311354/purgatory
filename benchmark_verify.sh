#!/usr/bin/env bash
#
# benchmark_verify.sh - Verify benchmark performance and detect regressions
#
# Architecture:
#   - Shell script: Orchestrates benchmark execution and file management
#   - Python script (benchmark_compare.py): Performs JSON comparison and analysis
#   - Decoupled design allows standalone usage of either component
#
# Usage:
#   ./benchmark_verify.sh [baseline_file] [options]
#
# Options:
#   --threshold <percent>    Regression threshold (default: 10)
#   --filter <pattern>       Benchmark filter pattern
#   --min-time <seconds>     Minimum time per benchmark (default: 0.5s)
#   --output <file>          Save current results to file
#   --baseline <file>        Compare against baseline file
#   --help                   Show this help message
#
# Examples:
#   ./benchmark_verify.sh --output baseline.json
#   ./benchmark_verify.sh --baseline baseline.json --threshold 15
#   ./benchmark_verify.sh --baseline baseline.json --filter "BM_TwoSum.*"
#
# For standalone Python comparison:
#   ./benchmark/benchmark_compare.py baseline.json current.json [--threshold <percent>]

set -euo pipefail

# Default configuration
THRESHOLD=10
FILTER=""
MIN_TIME="0.5s"
BASELINE_FILE=""
OUTPUT_FILE=""
BENCHMARK_BINARY="./build/benchmark/purgatory_bench"
COMPARE_SCRIPT="$(dirname "$0")/benchmark/benchmark_compare.py"
TEMP_RESULTS="/tmp/benchmark_results_$$.json"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Parse command line arguments
parse_args() {
  while [[ $# -gt 0 ]]; do
    case $1 in
      --threshold)
        THRESHOLD="$2"
        shift 2
        ;;
      --filter)
        FILTER="$2"
        shift 2
        ;;
      --min-time)
        MIN_TIME="$2"
        shift 2
        ;;
      --output)
        OUTPUT_FILE="$2"
        shift 2
        ;;
      --baseline)
        BASELINE_FILE="$2"
        shift 2
        ;;
      --help)
        grep '^#' "$0" | sed 's/^# //' | sed 's/^#//'
        exit 0
        ;;
      *)
        # First positional argument is baseline file
        if [[ -z "$BASELINE_FILE" ]] && [[ -f "$1" ]]; then
          BASELINE_FILE="$1"
        else
          echo -e "${RED}Error: Unknown option or file not found: $1${NC}"
          exit 1
        fi
        shift
        ;;
    esac
  done
}

# Check if benchmark binary exists
check_binary() {
  if [[ ! -f "$BENCHMARK_BINARY" ]]; then
    echo -e "${RED}Error: Benchmark binary not found: $BENCHMARK_BINARY${NC}"
    echo "Please build the project first:"
    echo "  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release"
    echo "  cmake --build build --parallel"
    exit 1
  fi
}

# Check if comparison script exists
check_compare_script() {
  if [[ ! -f "$COMPARE_SCRIPT" ]]; then
    echo -e "${RED}Error: Comparison script not found: $COMPARE_SCRIPT${NC}"
    exit 1
  fi
  
  if [[ ! -x "$COMPARE_SCRIPT" ]]; then
    chmod +x "$COMPARE_SCRIPT"
  fi
}

# Run benchmarks and save results
run_benchmarks() {
  local output_file="$1"
  
  echo -e "${BLUE}Running benchmarks...${NC}"
  echo "  Binary: $BENCHMARK_BINARY"
  echo "  Min time: $MIN_TIME"
  [[ -n "$FILTER" ]] && echo "  Filter: $FILTER"
  echo ""
  
  local filter_arg=""
  [[ -n "$FILTER" ]] && filter_arg="--benchmark_filter=$FILTER"
  
  # Run benchmarks with JSON output
  $BENCHMARK_BINARY \
    --benchmark_format=json \
    --benchmark_min_time="$MIN_TIME" \
    --benchmark_out="$output_file" \
    $filter_arg \
    2>/dev/null || {
      echo -e "${RED}Error: Benchmark execution failed${NC}"
      exit 1
    }
  
  echo -e "${GREEN}✓ Benchmarks completed${NC}"
  echo ""
}

# Compare baseline and current results
compare_results() {
  local baseline="$1"
  local current="$2"
  
  echo -e "${BLUE}Comparing results against baseline...${NC}"
  echo "  Baseline: $baseline"
  echo "  Threshold: ${THRESHOLD}%"
  echo ""
  
  # Call Python comparison script
  "$COMPARE_SCRIPT" "$baseline" "$current" --threshold "$THRESHOLD"
}

# Main execution
main() {
  parse_args "$@"
  check_binary
  
  # Mode 1: Generate baseline
  if [[ -n "$OUTPUT_FILE" ]] && [[ -z "$BASELINE_FILE" ]]; then
    echo -e "${BLUE}Generating baseline results...${NC}"
    echo ""
    run_benchmarks "$OUTPUT_FILE"
    echo -e "${GREEN}✓ Baseline saved to: $OUTPUT_FILE${NC}"
    echo ""
    echo "To verify performance later, run:"
    echo "  $0 --baseline $OUTPUT_FILE"
    exit 0
  fi
  
  # Mode 2: Compare against baseline
  if [[ -n "$BASELINE_FILE" ]]; then
    if [[ ! -f "$BASELINE_FILE" ]]; then
      echo -e "${RED}Error: Baseline file not found: $BASELINE_FILE${NC}"
      exit 1
    fi
    
    check_compare_script
    run_benchmarks "$TEMP_RESULTS"
    
    # Save current results if requested
    if [[ -n "$OUTPUT_FILE" ]]; then
      cp "$TEMP_RESULTS" "$OUTPUT_FILE"
      echo -e "${GREEN}✓ Current results saved to: $OUTPUT_FILE${NC}"
      echo ""
    fi
    
    compare_results "$BASELINE_FILE" "$TEMP_RESULTS"
    exit_code=$?
    
    # Cleanup
    rm -f "$TEMP_RESULTS"
    exit $exit_code
  fi
  
  # Mode 3: Just run benchmarks
  echo -e "${YELLOW}No baseline or output file specified${NC}"
  echo "Running benchmarks without comparison..."
  echo ""
  
  local filter_arg=""
  [[ -n "$FILTER" ]] && filter_arg="--benchmark_filter=$FILTER"
  
  $BENCHMARK_BINARY \
    --benchmark_min_time="$MIN_TIME" \
    $filter_arg
}

main "$@"
