# 6502 Emulator Project

## Overview
This project is a C++ implementation of the MOS Technology 6502 microprocessor. It is designed to be a clear, educational emulator that demonstrates how a CPU works at a low level.

## Project Vision
The goal is to build a cycle-accurate emulator that effectively communicates the internal mechanics of the 6502. We aim to bridge the gap between abstract code and the physical reality of fetch-decode-execute cycles, registers, and memory management.

## Getting Started

### Prerequisites
- A C++ compiler supporting C++17.
- [CMake](https://cmake.org/) (version 3.10 or higher).

### Quick Start (using CMake)
1.  **Generate Build Files**:
    ```bash
    mkdir build && cd build
    cmake ..
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./6502_emulator
    ```

## Learn More
For a deep dive into the processor architecture, our "Office Clerk" analogy, and exactly how the code implements the hardware, please see **[Processor Information](ProcessorInfo.Md)**.
