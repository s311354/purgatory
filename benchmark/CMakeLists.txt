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
        target_compile_options(purgatory_bench PRIVATE
            -O3
            -march=native
            -mtune=native
        )
    endif()
    
    # Install benchmark binary
    install(TARGETS purgatory_bench DESTINATION bin)
    
    message(STATUS "Benchmark target: purgatory_bench")
endif()
