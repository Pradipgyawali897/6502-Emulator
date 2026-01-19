cmake_minimum_required(VERSION 3.10)
project(6502_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main_6502.cpp
    src/memory/memory.cpp
    src/cpu/core.cpp
    src/cpu/fetch.cpp
    src/cpu/addressing.cpp
    src/cpu/instructions.cpp
    src/cpu/stack.cpp
)

# Executable
add_executable(6502_emulator ${SOURCES})

# Testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0 # Or any stable version
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  cpu_tests
  tests/cpu_tests.cpp
  tests/ADC_tests.cpp
  src/memory/memory.cpp
  src/cpu/core.cpp
  src/cpu/fetch.cpp
  src/cpu/addressing.cpp
  src/cpu/instructions.cpp
  src/cpu/stack.cpp
)
target_link_libraries(
  cpu_tests
  GTest::gtest_main
)
target_include_directories(cpu_tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(cpu_tests)
