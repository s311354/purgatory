option(PURGATORY_ENABLE_QEMU_TESTS "Enable tests on non-native targets" ON)
set(MACHINE ${CMAKE_HOST_SYSTEM_PROCESSOR})

if(EXISTS "/proc/cpuinfo")
	file(READ "/proc/cpuinfo" CPUINFO)
endif()

# CMAKE_HOST_SYSTEM_PROCESSOR returns "aarch64" on ARM32 userland
# with ARM64 kernel. Here, we run `cc -dumpmachine` to determine the
# compiler's default target.
execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpmachine
    RESULT_VARIABLE EXIT_CODE
    OUTPUT_VARIABLE ARCH
    ERROR_QUIET)

if(NOT EXIT_CODE AND ARCH MATCHES "([^-]+).*")
	set(MACHINE ${CMAKE_MATCH_1})
endif()

if(${MACHINE} MATCHES "arm64")
	set(MACHINE x86_64)
elseif(${MACHINE} MATCHES "i.86")
	set(MACHINE i686)
elseif(${AMCHINE} MATCHES "arm.*")
	set(MACHINE arm)
endif()

list(APPEND TEST_TEMPLATE_FILES
	test.cc)

list(APPEND TARGETS
	X86_64 I386 ARM64LE)

set(TEST_SOURCES "")


function(test_instantiate_templates SOURCE TARGET)
	string(TOLOWER ${TARGET} LOWER_TARGET)
	set(PATH ${CMAKE_CURRENT_BINARY_DIR}/test_${LOWER_TARGET}.cc)

	message(STATUS "Found PATH is ${PATH}")
	if(NOT EXISTS ${PATH})
		file(WRITE ${PATH} "#define PURGATORY_${TARGET} 1
#define PURGATORY_TARGET ${TARGETS}
#include \"${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}\"
")
	endif()

	set(TEST_SOURCES ${TEST_SOURCES} ${PATH} PARENT_SCOPE)
endfunction()


foreach(SOURCE IN LISTS TEST_TEMPLATE_FILES)
	foreach(TARGET IN LISTS TARGETS)
		test_instantiate_templates(${SOURCE} ${TARGET})
	endforeach()
endforeach()
message(STATUS "Found TEST_SOURCES is ${TEST_SOURCES}")


include(GoogleTest)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests PRIVATE GTest::gtest_main solutions)
target_include_directories(unit_tests PRIVATE
	${CMAKE_SOURCE_DIR}/src
	${gtest_SOURCE_DIR}/include
	${gmock_SOURCE_DIR}/include)

gtest_discover_tests(unit_tests
	DISCOVERY_TIMEOUT 30
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

if(PURGATORY_ENABLE_QEMU_TESTS AND MACHINE STREQUAL "X86_64")
	message(STATUS "QEMU tests enabled for cross-platform simulation.")
endif()
