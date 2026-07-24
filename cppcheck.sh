#!/bin/bash
# cppcheck.sh - Static analysis script for purgatory project
# Usage: ./cppcheck.sh [check|strict|report]

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if cppcheck is installed
if ! command -v cppcheck &> /dev/null; then
    echo -e "${RED}Error: cppcheck is not installed${NC}"
    echo "Install with: sudo apt-get install cppcheck (Ubuntu/Debian)"
    exit 1
fi

# Display cppcheck version
echo -e "${GREEN}cppcheck version:${NC}"
cppcheck --version
echo ""

# Default to check mode
MODE="${1:-check}"

case "$MODE" in
    strict)
        echo -e "${YELLOW}Running comprehensive analysis (all checks)...${NC}"
        echo ""
        cppcheck \
            --enable=warning,style,performance,portability \
            --std=c++17 \
            --suppress=missingIncludeSystem \
            --suppress=functionStatic \
            --suppress=useStlAlgorithm \
            --suppress=noExplicitConstructor:src/query.h:79 \
            --inconclusive \
            --inline-suppr \
            --template='{file}:{line}: [{severity}] {message} [{id}]' \
            src/ 2>&1
        
        EXIT_CODE=$?
        echo ""
        if [ $EXIT_CODE -eq 0 ]; then
            echo -e "${GREEN}✓ Comprehensive analysis complete${NC}"
        fi
        exit $EXIT_CODE
        ;;
    
    report)
        echo -e "${YELLOW}Generating detailed cppcheck report...${NC}"
        echo ""
        cppcheck \
            --enable=warning,style,performance,portability \
            --std=c++17 \
            --suppress=missingIncludeSystem \
            --suppress=functionStatic \
            --suppress=useStlAlgorithm \
            --suppress=noExplicitConstructor:src/query.h:79 \
            --inconclusive \
            --inline-suppr \
            --template='{file}:{line}: [{severity}] {message} [{id}]' \
            src/ 2>&1 | tee cppcheck-report.txt
        echo ""
        echo -e "${GREEN}Report saved to cppcheck-report.txt${NC}"
        ;;
    
    check)
        echo -e "${YELLOW}Running standard checks (warnings + style + performance)...${NC}"
        echo ""
        cppcheck \
            --enable=warning,style,performance \
            --std=c++17 \
            --suppress=missingIncludeSystem \
            --suppress=functionStatic \
            --suppress=useStlAlgorithm \
            --suppress=noExplicitConstructor:src/query.h:79 \
            --quiet \
            src/ 2>&1
        
        EXIT_CODE=$?
        if [ $EXIT_CODE -eq 0 ]; then
            echo ""
            echo -e "${GREEN}✓ No issues found${NC}"
        fi
        exit $EXIT_CODE
        ;;
    
    *)
        echo "Usage: $0 [check|strict|report]"
        echo ""
        echo "  check  - Standard checks (warnings + style + performance) [default]"
        echo "  strict - Comprehensive analysis (includes portability)"
        echo "  report - Generate detailed report to file"
        exit 1
        ;;
esac
