# 6502 Emulator Project

## Overview
This project is a C++ implementation of the MOS Technology 6502 microprocessor. It is designed to be a clear, educational emulator that demonstrates how a CPU works at a low level.

## Project Vision
The goal is to build a cycle-accurate emulator that effectively communicates the internal mechanics of the 6502. We aim to bridge the gap between abstract code and the physical reality of fetch-decode-execute cycles, registers, and memory management.

## Getting Started

### Prerequisites
- A C++ compiler (e.g., `g++`).

### Quick Start
1.  **Compile**:
    ```bash
    g++ main_6502.cpp -o 6502_emu
    ```
2.  **Run**:
    ```bash
    ./6502_emu
    ```

## Learn More
For a deep dive into the processor architecture, our "Office Clerk" analogy, and exactly how the code implements the hardware, please see **[Processor Information](ProcessorInfo.Md)**.
