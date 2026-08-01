# Google Benchmark configuration for purgatory

# Option to build benchmarks
option(BUILD_BENCHMARKS "Build performance benchmarks" OFF)

if(BUILD_BENCHMARKS)
    message(STATUS "Building performance benchmarks")
    
    # Fetch Google Benchmark
    include(FetchContent)
    
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    
    FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
    )
    
    FetchContent_MakeAvailable(googlebenchmark)
    
    # Create benchmark executable
    add_executable(purgatory_bench
        twopointers_bench.cc
    )
    
    target_link_libraries(purgatory_bench
        PRIVATE
        solutions
        benchmark::benchmark
        benchmark::benchmark_main
    )
    
    target_compile_features(purgatory_bench PRIVATE cxx_std_17)
    
    # Apply same optimization flags as main target
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        # Architecture-specific optimizations
        if(NOT DEFINED CMAKE_CXX_COMPILER_TARGET)
            # Detect system architecture
            if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
                # Use x86-64-v3 for CI compatibility on x86, native for local builds
                if(DEFINED ENV{CI})
                    target_compile_options(purgatory_bench PRIVATE
                        -O3
                        -march=x86-64-v3
                    )
                else()
                    target_compile_options(purgatory_bench PRIVATE
                        -O3
                        -march=native
                        -mtune=native
                    )
                endif()
            elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
                # Use armv8-a for CI compatibility on ARM, native for local builds
                if(DEFINED ENV{CI})
                    target_compile_options(purgatory_bench PRIVATE
                        -O3
                        -march=armv8-a
                    )
                else()
                    target_compile_options(purgatory_bench PRIVATE
                        -O3
                        -march=native
                        -mtune=native
                    )
                endif()
            else()
                # Fallback for other architectures
                target_compile_options(purgatory_bench PRIVATE
                    -O3
                    -march=native
                    -mtune=native
                )
            endif()
        endif()
    endif()
    
    # Install benchmark binary
    install(TARGETS purgatory_bench DESTINATION bin)
    
    message(STATUS "Benchmark target: purgatory_bench")
endif()
