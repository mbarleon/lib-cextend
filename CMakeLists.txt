cmake_minimum_required(VERSION 3.16)
project(cextend VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

########################################
# INFO: enable multithreading for build
########################################
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

########################################
# INFO: CMake cache management for faster builds
########################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########################################

file(GLOB LOGGER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/logger/*.c")

file(GLOB_RECURSE EXCEPTION_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/exception/*.c")

file(GLOB_RECURSE MEMORY_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/memory/*.c")

file(GLOB SNPRINTF_ALLOC_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/snprintf_alloc/*.c")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    list(FILTER EXCEPTION_SOURCE EXCLUDE REGEX ".*/backtrace/linux/.*")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(FILTER EXCEPTION_SOURCE EXCLUDE REGEX ".*/backtrace/macos/.*")
endif()

add_library(cextend SHARED
    ${LOGGER_SOURCE}
    ${MEMORY_SOURCE}
    ${EXCEPTION_SOURCE}
    ${SNPRINTF_ALLOC_SOURCE}
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(cextend PRIVATE dl)
endif()

target_compile_options(cextend PRIVATE
    # INFO: classic warnings
    -Wall
    -Wextra
    -Werror
    -pedantic

    # INFO: type safety & conversions
    -Wconversion
    -Wsign-conversion
    -Wfloat-equal

    # INFO: code correctness
    -Wshadow
    -Wnull-dereference
    -Wundef
    -Wuninitialized
    -Winit-self
    -Wredundant-decls

    # INFO: code hygiene
    -Wcast-align
    -Wcast-qual
    -Wmissing-declarations

    # INFO: logic bugs & bad practices
    -Wswitch-default
    -Wswitch-enum

    # INFO: prevent common portability issues
    -Wdouble-promotion
    -Wwrite-strings

    # INFO: disabling this because this causes a compilation error
    -Wno-gnu-zero-variadic-macro-arguments
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(cextend PRIVATE -Wno-format-truncation)
endif()

add_custom_command(TARGET cextend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/libs
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:cextend> ${CMAKE_SOURCE_DIR}/libs
    COMMENT "Copying shared library to ./libs"
)

########################################

option(CEXTEND_ENABLE_DEBUG "Enable debug definition" OFF)

if(CEXTEND_ENABLE_DEBUG)
    target_compile_definitions(cextend PRIVATE CEXTEND_DEBUG=1)
endif()

########################################

file(GLOB TEST_SOURCE
    "tests/*.c")

add_executable(cextend_unit_tests
    ${TEST_SOURCE}
    ${LOGGER_SOURCE}
    ${MEMORY_SOURCE}
    ${EXCEPTION_SOURCE}
    ${SNPRINTF_ALLOC_SOURCE}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
    target_compile_options(cextend_unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(cextend_unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(cextend_unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(cextend_unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
endif()

target_compile_definitions(cextend_unit_tests PRIVATE UNIT_TESTS=1)

target_link_libraries(cextend_unit_tests PRIVATE criterion sfml-graphics sfml-system sfml-window)

target_include_directories(cextend_unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

enable_testing()
add_test(NAME cextend_unit_tests COMMAND cextend_unit_tests)

add_custom_target(tests_run
    COMMAND cextend_unit_tests
    DEPENDS cextend_unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
