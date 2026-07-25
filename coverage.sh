#!/bin/bash
# coverage.sh - Generate code coverage report for purgatory
#
# Usage:
#   ./coverage.sh                # Generate text report with default settings
#   ./coverage.sh --text         # Generate text report (default)
#   ./coverage.sh --detailed     # Generate detailed text report
#   ./coverage.sh --xml          # Generate XML report (Cobertura format)
#   ./coverage.sh --html         # Generate HTML report
#   ./coverage.sh --clean        # Clean coverage artifacts
#
# Requirements:
#   - gcovr (pip install gcovr or apt install gcovr)
#   - g++ with gcov support

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default settings
BUILD_DIR="build-coverage"
OUTPUT_FORMAT="text"
CLEAN_ONLY=false
MIN_COVERAGE=0
AUTO_OPEN=false

print_usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --text              Generate text summary (default)"
    echo "  --detailed          Generate detailed text report with file breakdown"
    echo "  --xml               Generate XML report (Cobertura format)"
    echo "  --html              Generate HTML coverage report"
    echo "  --clean             Clean coverage artifacts and exit"
    echo "  --min-coverage N    Set minimum coverage threshold (default: 0)"
    echo "  --help              Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                  # Generate text summary"
    echo "  $0 --detailed       # Show detailed per-file coverage"
    echo "  $0 --xml            # Generate XML for CI/CD"
    echo "  $0 --min-coverage 80  # Fail if coverage < 80%"
    exit 0
}

print_step() {
    echo -e "${BLUE}==>${NC} $1"
}

print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

check_dependencies() {
    print_step "Checking dependencies..."
    
    local missing_deps=false
    
    if ! command -v gcovr &> /dev/null; then
        print_error "gcovr not found. Install with: pip install gcovr or apt install gcovr"
        missing_deps=true
    fi
    
    if ! command -v g++ &> /dev/null; then
        print_error "g++ not found. Install with: apt install g++"
        missing_deps=true
    fi
    
    if ! command -v cmake &> /dev/null; then
        print_error "cmake not found. Install with: apt install cmake"
        missing_deps=true
    fi
    
    if [ "$missing_deps" = true ]; then
        exit 1
    fi
    
    print_success "All dependencies found"
}

clean_coverage() {
    print_step "Cleaning coverage artifacts..."
    
    # Remove build directory
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "Removed $BUILD_DIR"
    fi
    
    # Remove coverage files
    find . -name "*.gcda" -delete 2>/dev/null || true
    find . -name "*.gcno" -delete 2>/dev/null || true
    find . -name "*.gcov" -delete 2>/dev/null || true
    
    # Remove coverage reports
    rm -f coverage.html coverage*.html coverage.xml coverage-summary.txt
    
    print_success "Coverage artifacts cleaned"
}

build_with_coverage() {
    print_step "Building project with coverage instrumentation..."
    
    # Clean previous build
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    fi
    
    # Configure with coverage flags
    cmake -S . -B "$BUILD_DIR" \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_COMPILER=g++ \
        -DCMAKE_CXX_FLAGS="--coverage -fprofile-arcs -ftest-coverage" \
        -DCMAKE_EXE_LINKER_FLAGS="--coverage" \
        -DBUILD_TESTING=ON
    
    # Build
    cmake --build "$BUILD_DIR" --parallel
    
    print_success "Build completed"
}

run_tests() {
    print_step "Running tests to generate coverage data..."
    
    # Run the main executable
    if [ -f "$BUILD_DIR/purgatory" ] && [ -f "src/test.txt" ]; then
        "$BUILD_DIR/purgatory" src/test.txt > /dev/null 2>&1 || true
        print_success "Main executable ran"
    fi
    
    # Run unit tests if available
    if [ -f "$BUILD_DIR/test/purgatory_test" ]; then
        "$BUILD_DIR/test/purgatory_test" > /dev/null 2>&1 || true
        print_success "Unit tests ran"
    fi
    
    # Run ctest
    if ctest --test-dir "$BUILD_DIR" --output-on-failure > /dev/null 2>&1; then
        print_success "All tests passed"
    else
        print_warning "Some tests failed (continuing with coverage)"
    fi
}

generate_report() {
    print_step "Generating coverage report..."
    
    local gcovr_base_cmd="gcovr --root . \
        --filter src/ \
        --exclude 'src/main.cc' \
        --exclude 'src/entry.cc' \
        --exclude-unreachable-branches \
        --exclude-throw-branches"
    
    case "$OUTPUT_FORMAT" in
        text)
            echo ""
            echo "========================================"
            echo "        Coverage Summary"
            echo "========================================"
            $gcovr_base_cmd --print-summary
            echo "========================================"
            print_success "Coverage report generated"
            ;;
        detailed)
            echo ""
            echo "========================================"
            echo "    Detailed Coverage Report"
            echo "========================================"
            $gcovr_base_cmd
            echo "========================================"
            print_success "Detailed coverage report generated"
            ;;
        xml)
            $gcovr_base_cmd \
                --xml coverage.xml \
                --print-summary
            print_success "XML report generated: coverage.xml"
            ;;
        html)
            $gcovr_base_cmd \
                --html-details coverage.html \
                --print-summary
            print_success "HTML report generated: coverage.html"
            echo "Note: HTML viewing may not be supported in this environment"
            echo "Consider using --text or --detailed for terminal output"
            ;;
    esac
}

check_coverage_threshold() {
    if [ "$MIN_COVERAGE" -gt 0 ]; then
        print_step "Checking coverage threshold (minimum: ${MIN_COVERAGE}%)..."
        
        if ! gcovr --root . \
            --filter src/ \
            --exclude 'src/main.cc' \
            --exclude 'src/entry.cc' \
            --fail-under-line "$MIN_COVERAGE" &> /dev/null; then
            print_error "Coverage below threshold of ${MIN_COVERAGE}%"
            exit 1
        fi
        
        print_success "Coverage meets threshold"
    fi
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --text)
            OUTPUT_FORMAT="text"
            shift
            ;;
        --detailed)
            OUTPUT_FORMAT="detailed"
            shift
            ;;
        --xml)
            OUTPUT_FORMAT="xml"
            shift
            ;;
        --html)
            OUTPUT_FORMAT="html"
            shift
            ;;
        --clean)
            CLEAN_ONLY=true
            shift
            ;;
        --min-coverage)
            MIN_COVERAGE="$2"
            shift 2
            ;;
        --help)
            print_usage
            ;;
        *)
            print_error "Unknown option: $1"
            print_usage
            ;;
    esac
done

# Main execution
echo -e "${GREEN}Code Coverage Report Generator${NC}"
echo ""

if [ "$CLEAN_ONLY" = true ]; then
    clean_coverage
    exit 0
fi

check_dependencies
build_with_coverage
run_tests
generate_report
check_coverage_threshold

echo ""
print_success "Coverage analysis completed"
