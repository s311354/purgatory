#!/bin/bash
# Apply quick-win performance improvements to purgatory
# Run with: ./apply-perf-improvements.sh [quick|medium|all]

set -e

MODE="${1:-quick}"
BACKUP_DIR=".backup_$(date +%Y%m%d_%H%M%S)"

echo "🚀 Applying performance improvements: $MODE"
echo "📦 Backup directory: $BACKUP_DIR"

# Backup original files
mkdir -p "$BACKUP_DIR"
cp CMakeLists.txt "$BACKUP_DIR/"
cp .github/workflows/ci.yml "$BACKUP_DIR/"

# ============================================================================
# QUICK WINS
# ============================================================================

if [[ "$MODE" == "quick" || "$MODE" == "all" ]]; then
    echo ""
    echo "✅ Quick Wins (1-2 days effort)"
    echo "================================"
    
    # 1. Remove unconditional -pg flag
    echo "1. Removing unconditional profiling overhead (-pg flag)..."
    sed -i '/^set(CMAKE_C_FLAGS "\${CMAKE_C_FLAGS} -pg")/d' CMakeLists.txt
    sed -i '/^set(CMAKE_EXE_LINKER_FLAGS "\${CMAKE_EXE_LINKER_FLAGS} -pg")/d' CMakeLists.txt
    
    # Add conditional profiling support
    if ! grep -q "PURGATORY_ENABLE_PROFILING" CMakeLists.txt; then
        sed -i '/^project(purgatory VERSION/a\\n# Profiling support\noption(PURGATORY_ENABLE_PROFILING "Enable gprof profiling" OFF)\nif(PURGATORY_ENABLE_PROFILING)\n\tset(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")\n\tset(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")\nendif()' CMakeLists.txt
    fi
    
    # 2. Add aggressive Release optimization flags
    echo "2. Adding aggressive optimization flags..."
    if ! grep -q "march=native" CMakeLists.txt; then
        cat >> CMakeLists.txt << 'EOF'

# Performance optimizations for Release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	# Architecture-specific optimizations
	if(NOT DEFINED CMAKE_CXX_COMPILER_TARGET)
		# Use x86-64-v3 for CI compatibility, native for local builds
		if(DEFINED ENV{CI})
			target_compile_options(purgatory PRIVATE -march=x86-64-v3)
		else()
			target_compile_options(purgatory PRIVATE -march=native -mtune=native)
		endif()
	endif()
	
	# Additional performance flags
	target_compile_options(purgatory PRIVATE
		-fomit-frame-pointer
		-funroll-loops
		-fmerge-all-constants
	)
	
	# Link-time optimizations (if supported)
	include(CheckIPOSupported)
	check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
	if(ipo_supported)
		message(STATUS "IPO/LTO enabled")
		set_property(TARGET purgatory PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
	else()
		message(STATUS "IPO/LTO not supported: ${ipo_error}")
	endif()
endif()
EOF
    fi
    
    # 3. Update CI to use mold and ccache
    echo "3. Updating CI configuration..."
    
    # Check if ci.yml exists
    if [[ -f .github/workflows/ci.yml ]]; then
        # Add mold installation
        if ! grep -q "mold" .github/workflows/ci.yml; then
            sed -i 's/sudo apt-get install -y cmake ninja-build g++-11/sudo apt-get install -y cmake ninja-build g++-11 mold/' .github/workflows/ci.yml
        fi
        
        # Enable mold in CMake configure
        if ! grep -q "PURGATORY_USE_MOLD" .github/workflows/ci.yml; then
            sed -i 's/-DBUILD_TESTING=ON/-DBUILD_TESTING=ON \\\n          -DPURGATORY_USE_MOLD=ON/' .github/workflows/ci.yml
        fi
        
        # Add ccache step (insert after checkout)
        if ! grep -q "ccache" .github/workflows/ci.yml; then
            # This is complex, create a note instead
            echo "   ⚠️  Manual step required: Add ccache to CI (see PERFORMANCE_IMPROVEMENTS.md §2.1)"
        fi
    fi
    
    echo ""
    echo "✅ Quick wins applied!"
    echo "   • Profiling overhead removed (enable with -DPURGATORY_ENABLE_PROFILING=ON)"
    echo "   • Architecture-specific optimizations added"
    echo "   • LTO enabled for Release builds"
    echo "   • Mold linker enabled in CI"
fi

# ============================================================================
# MEDIUM EFFORT
# ============================================================================

if [[ "$MODE" == "medium" || "$MODE" == "all" ]]; then
    echo ""
    echo "⚙️  Medium Effort (1 week)"
    echo "=========================="
    
    # 4. Add precompiled headers
    echo "4. Adding precompiled headers..."
    if ! grep -q "target_precompile_headers" CMakeLists.txt; then
        cat >> CMakeLists.txt << 'EOF'

# Precompiled headers for faster compilation
target_precompile_headers(purgatory PRIVATE
	<vector>
	<string>
	<unordered_map>
	<unordered_set>
	<algorithm>
	<cmath>
	<numeric>
	<queue>
	<stack>
	<memory>
	<utility>
)
EOF
    fi
    
    # 5. Add unity build option
    echo "5. Adding unity build option..."
    if ! grep -q "PURGATORY_UNITY_BUILD" CMakeLists.txt; then
        sed -i '/^option(PURGATORY_USE_MOLD/a\\noption(PURGATORY_UNITY_BUILD "Use unity build for faster compilation" OFF)\nif(PURGATORY_UNITY_BUILD)\n\tset_target_properties(purgatory PROPERTIES UNITY_BUILD ON)\n\tset_target_properties(purgatory PROPERTIES UNITY_BUILD_BATCH_SIZE 8)\nendif()' CMakeLists.txt
    fi
    
    echo ""
    echo "⚙️  Medium improvements applied!"
    echo "   • Precompiled headers configured"
    echo "   • Unity build option added (enable with -DPURGATORY_UNITY_BUILD=ON)"
fi

# ============================================================================
# SUMMARY
# ============================================================================

echo ""
echo "🎉 Performance improvements applied!"
echo ""
echo "📊 Expected improvements:"
echo "   • Build time: -30% to -50% (with ccache)"
echo "   • Link time: -50% to -70% (mold)"
echo "   • Runtime: -15% to -25% (optimizations + LTO)"
echo "   • Binary size: -5% to -10%"
echo ""
echo "🔧 Next steps:"
echo "   1. Review changes: git diff CMakeLists.txt"
echo "   2. Test build: cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build"
echo "   3. Run benchmarks to validate improvements"
echo "   4. Manually add ccache to .github/workflows/ci.yml (see doc)"
echo ""
echo "📚 Full documentation: .github/PERFORMANCE_IMPROVEMENTS.md"
echo "♻️  Restore backup: cp $BACKUP_DIR/* ."
