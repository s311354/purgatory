cmake_minimum_required(VERSION 3.14)
project(purgatory VERSION 0.0.0)

# Profiling support
option(PURGATORY_ENABLE_PROFILING "Enable gprof profiling" OFF)
if(PURGATORY_ENABLE_PROFILING)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

add_executable(purgatory)
target_compile_features(purgatory PRIVATE cxx_std_17)


# Build purgatory using mold if -DPURGATORY_USE_MOLD=ON
option(PURGATORY_USE_MOLD "Use purgatory to build mold" OFF)
if(PURGATORY_USE_MOLD)
	message(STATUS "PURGATORY_USE_MOLD is ${PURGATORY_USE_MOLD}")

	target_link_options(purgatory PRIVATE -fuse-ld=mold)

	if(CMAKE_BUILD_TYPE MATCHES "Deb")
		target_link_options(purgatory PRIVATE -Wl,--gdb-index)
	endif()

	if(CMAKE_BUILD_TYPE MATCHES "^Rel")
		# Enable section garbage collection (--icf requires mold >= 1.3.0)
		target_link_options(purgatory PRIVATE -Wl,--gc-sections)
	endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(purgatory PRIVATE -D_GLIBCXX_ASSERTIONS)
endif()

# Enable AddressSanitizer if -DPURGATORY_USE_ASAN=ON
option(PURGATORY_USE_ASAN "Build purgatory with AddressSanitizer" OFF)
if(PURGATORY_USE_ASAN)
	message(STATUS "PURGATORY_USE_ASAN is ${PURGATORY_USE_ASAN}")
	target_compile_options(purgatory PRIVATE -fsanitize=address -fsanitize=undefined)
	target_link_options(purgatory PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

# Enable ThreadSanitize if -DPURGATORY_USE_TSAN=ON
option(PURGATORY_USE_TSAN "Build purgatory with ThreadSanitize" OFF)
if(PURGATORY_USE_TSAN)
	message(STATUS "PURGATORY_USE_TSAN is ${PURGATORY_USE_TSAN}")
	target_compile_options(purgatory PRIVATE -fsanitize=thread)
	target_link_options(purgatory PRIVATE -fsanitize=thread)
endif()

# Add -pthread
if(NOT APPLE AND NOT MSVC)
	target_compile_options(purgatory PRIVATE -pthread)
	target_link_options(purgatory PRIVATE -pthread)
endif()

list(APPEND PURGATORY_TARGETS
	X86_64
	ARM64LE
	I386
)

file(COPY ${CMAKE_SOURCE_DIR}/src/test.txt DESTINATION ${CMAKE_BINARY_DIR})

list(APPEND PURGATORY_FILES
	src/main.cc
)

function(purgatory_instantiate_templates SOURCE TARGET)
	set(PATH ${CMAKE_BINARY_DIR}/${SOURCE}.${TARGET}.cc)
	if(NOT EXISTS ${PATH})
		file(WRITE ${PATH} "#define PURGATORY_${TARGET} 1
#define PURGATORY_TARGET ${TARGET}
#include \"${CMAKE_SOURCE_DIR}/${SOURCE}\"
")
	endif()
	target_sources(purgatory PRIVATE ${PATH})
endfunction()

foreach (SOURCE IN LISTS PURGATORY_FILES)
	foreach (TARGET IN LISTS PURGATORY_TARGETS)
		purgatory_instantiate_templates(${SOURCE} ${TARGET})
	endforeach()
endforeach()

set(SOLUTIONS_FILES 
	src/query.cc
	src/array.cc
	src/hashmap.cc
	src/twopointers.cc
	src/slidingwindow.cc
	src/prefixsum.cc
	src/binarytree.cc
	src/stack.cc
	src/graphbfs.cc
	src/graph.cc
	src/heap.cc
	src/intervals.cc
	src/dp.cc
	src/backtracking.cc
	src/binarysearch.cc
	src/linkedlist.cc
	src/matrix.cc)

target_sources(purgatory PRIVATE
    ${SOLUTIONS_FILES}
    src/entry.cc
)

if(CMAKE_SYSTEM_NAME STREQUAL "OpenBSD")
	set(OPENBSD ON)
endif()

if(BUILD_TESTING)
	if(${UNIX})
		add_library(solutions SHARED ${SOLUTIONS_FILES})
		target_compile_features(solutions PUBLIC cxx_std_17)

		enable_testing()
		add_subdirectory(third-party/googletest)
		add_subdirectory(test)
	endif()
endif()

# Benchmark suite
if(BUILD_BENCHMARKS)
	if(${UNIX})
		if(NOT TARGET solutions)
			add_library(solutions SHARED ${SOLUTIONS_FILES})
			target_compile_features(solutions PUBLIC cxx_std_17)
		endif()
		add_subdirectory(benchmark)
	endif()
endif()

# Generate System.map after linking
add_custom_command(TARGET purgatory POST_BUILD
	COMMAND ${CMAKE_NM} -n $<TARGET_FILE:purgatory> > ${CMAKE_BINARY_DIR}/System.map
        COMMENT "Generating System.map for purgatory"
)

# Performance optimizations for Release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	# Architecture-specific optimizations
	if(NOT DEFINED CMAKE_CXX_COMPILER_TARGET)
		# Detect system architecture
		if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
			# Use x86-64-v3 for CI compatibility on x86, native for local builds
			if(DEFINED ENV{CI})
				target_compile_options(purgatory PRIVATE -march=x86-64-v3)
			else()
				target_compile_options(purgatory PRIVATE -march=native -mtune=native)
			endif()
		elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
			# Use armv8-a for CI compatibility on ARM, native for local builds
			if(DEFINED ENV{CI})
				target_compile_options(purgatory PRIVATE -march=armv8-a)
			else()
				target_compile_options(purgatory PRIVATE -march=native -mtune=native)
			endif()
		else()
			# Fallback for other architectures
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
