# You can customize a build by specifying CMake options. An option may be
# given in the -Dvariable=value form. For a boolean variable, `ON` or `1`
# means true, while `OFF` or `0` means false.
#
# Here are a couple of common cmake options:
#
# -DCMAKE_C_COMPILER=<command-name>
#
#  Specifies the C compiler name to use. The default value is `cc`.
#
# -DCMAKE_CXX_COMPILER=<command-name>
#
#  Specifies the C++ compiler name to use. The default value is `c++`.
#
# -DCMAKE_BUILD_TYPE=[Debug | Release | RelWithDebInfo | MinSinzeRel]
#  Specifies the build type. The default is `Release`, which is the right
#  option unless you are debugging purgatory.
#
# An example of a cmake command line is shown below:
#
#  $ cmake -DCMAKE_CXX_COMPILER=g++-12 ..
#
# where `..` refers to this directory.

cmake_minimum_required(VERSION 3.14)
project(purgatory VERSION 0.0.0)

add_executable(purgatory)
target_compile_features(purgatory PRIVATE cxx_std_11)

# Build purgatory using mold if -DPURGATORY_USE_MOLD=ON
option(PURGATORY_USE_MOLD "Use purgatory to build mold" OFF)
if(PURGATORY_USE_MOLD)
	message(STATUS "PURGATORY_USE_MOLD is ${PURGATORY_USE_MOLD}")

	target_link_options(purgatory PRIVATE -fuse-ld=mold)

	if(CMAKE_BUILD_TYPE MATCHES "Deb")
		target_link_options(purgatory PRIVATE -Wl,--gdb-index)
	endif()

	if(CMAKE_BUILD_TYPE MATCHES "^Rel")
		target_link_options(purgatory PRIVATE -Wl,--gc-sections,--icf=safe)
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
	src/binarysearch.cc)

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

		enable_testing()
		add_subdirectory(third-party/googletest)
		add_subdirectory(test)
	endif()
endif()

# Generate System.map after linking
add_custom_command(TARGET purgatory POST_BUILD
	COMMAND ${CMAKE_NM} -n $<TARGET_FILE:purgatory> > ${CMAKE_BINARY_DIR}/System.map
        COMMENT "Generating System.map for purgatory"
)
