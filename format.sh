#!/usr/bin/env bash
#
# format.sh - Check or apply clang-format to C/C++ source files
#
# Usage:
#   ./format.sh check [dir]   # Check formatting (exit 1 if issues found)
#   ./format.sh apply [dir]   # Apply formatting in-place
#
# Examples:
#   ./format.sh check         # Check all (src, test)
#   ./format.sh check src     # Check only src/
#   ./format.sh apply test    # Apply formatting to test/

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Detect clang-format binary
CLANG_FORMAT=""
for candidate in clang-format-14 clang-format; do
    if command -v "$candidate" &>/dev/null; then
        CLANG_FORMAT="$candidate"
        break
    fi
done

if [[ -z "$CLANG_FORMAT" ]]; then
    echo "Error: clang-format or clang-format-14 not found in PATH" >&2
    exit 1
fi

# Parse arguments
MODE="${1:-check}"
TARGET_DIR="${2:-}"

if [[ "$MODE" != "check" && "$MODE" != "apply" ]]; then
    echo "Usage: $0 {check|apply} [directory]" >&2
    echo "  directory: src, test, or omit for all" >&2
    exit 1
fi

# Determine target directories
TARGETS=()
if [[ -z "$TARGET_DIR" ]]; then
    # Default: format both src and test
    [[ -d "$SCRIPT_DIR/src" ]] && TARGETS+=("$SCRIPT_DIR/src")
    [[ -d "$SCRIPT_DIR/test" ]] && TARGETS+=("$SCRIPT_DIR/test")
else
    # Specific directory provided
    if [[ -d "$SCRIPT_DIR/$TARGET_DIR" ]]; then
        TARGETS+=("$SCRIPT_DIR/$TARGET_DIR")
    elif [[ -d "$TARGET_DIR" ]]; then
        TARGETS+=("$TARGET_DIR")
    else
        echo "Error: Directory '$TARGET_DIR' not found" >&2
        exit 1
    fi
fi

if [[ ${#TARGETS[@]} -eq 0 ]]; then
    echo "Error: No target directories found" >&2
    exit 1
fi

echo "Using: $CLANG_FORMAT"
echo "Target(s): ${TARGETS[*]}"

# Find all C/C++ source and header files in target directories
FILES=""
for target in "${TARGETS[@]}"; do
    FOUND=$(find "$target" -type f \( \
        -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' -o \
        -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o -name '*.hxx' \
    \) 2>/dev/null || true)
    if [[ -n "$FOUND" ]]; then
        FILES="$FILES"$'\n'"$FOUND"
    fi
done

# Remove leading newline
FILES="${FILES#$'\n'}"

if [[ -z "$FILES" ]]; then
    echo "No C/C++ files found in target directories"
    exit 0
fi

FILE_COUNT=$(echo "$FILES" | wc -l)
echo "Found $FILE_COUNT file(s)"

case "$MODE" in
    check)
        echo "Checking formatting..."
        echo "$FILES" | xargs "$CLANG_FORMAT" --style=file --dry-run --Werror
        echo "✓ All files are properly formatted"
        ;;
    apply)
        echo "Applying formatting..."
        echo "$FILES" | xargs "$CLANG_FORMAT" --style=file -i
        echo "✓ Formatting applied to $FILE_COUNT file(s)"
        ;;
esac
