cmake_minimum_required(VERSION 3.10)
project(6502_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main_6502.cpp
    src/memory.cpp
    src/cpu.cpp
)

# Executable
add_executable(6502_emulator ${SOURCES})
