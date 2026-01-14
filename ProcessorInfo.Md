# Processor Information & Technical Guide

## The Big Picture: An Analogy

Understanding a CPU can be daunting, so let's use an analogy: **The Office Clerk**.

- **The CPU (The Clerk)**: Imagine a diligent clerk sitting at a desk. Their job is to process instructions one by one.
- **Memory/RAM (The Mailboxes)**: Across the room is a massive wall of **65,536 mailboxes**. Each mailbox holds a single piece of paper (a byte of data).
- **The Program Counter (The Notepad)**: The clerk has a notepad where they write down the number of the *next* mailbox they need to check. They go to that mailbox, read the instruction, and do what it says.
- **Registers (The Desk Trays)**: On the clerk's desk are small trays (A, X, Y) where they hold the specific papers they are currently working on. They don't have to walk to the wall to check these; they are right there for fast access.

## Technical Specifications

The 6502 is an 8-bit microprocessor. Here is the technical breakdown:

### Architecture
- **8-bit Data**: It works with 8 bits (1 byte) at a time.
- **16-bit Address Bus**: It can access $2^{16}$ (65,536) unique memory locations.
- **Little-Endian**: Multibyte values are stored with the least significant byte first (e.g., `0x1234` is stored as `34 12`).

### Registers (The Clerk's Tools)
- **Program Counter (PC)**: 16-bit. Holds the address of the next instruction.
- **Stack Pointer (SP)**: 16-bit. Points to the current top of the stack (a temporary storage area).
- **Accumulator (A)**: 8-bit. The primary register for math and logic.
- **Index Registers (X, Y)**: 8-bit. Used for loops and modifying addresses.

### Status Flags (The Clerk's Checklist)
The processor keeps track of the result of the last operation using a set of 1-bit flags:
- **C (Carry)**: Did the last math operation overflow?
- **Z (Zero)**: Was the result zero?
- **I (Interrupt Disable)**: Is the clerk ignoring phone calls (interrupts)?
- **D (Decimal)**: Are we doing math in human mode (BCD)?
- **B (Break)**: Was a software interrupt triggered?
- **V (Overflow)**: Did the sign bit get messed up?
- **N (Negative)**: Is the result negative?

## Current Implementation Status

We have built the foundational skeleton of the emulator in `main_6502.cpp`. Here is how our code maps to the hardware concepts:

| Concept | Code Implementation | Description |
| :--- | :--- | :--- |
| **The Mailboxes** | `struct Mem` | Contains `Byte Data[1024 * 64]` representing the 64KB memory space. |
| **The Clerk** | `struct CPU` | Holds all registers and flags as member variables. |
| **Startup** | `CPU::Reset()` | Wakes up the clerk, sets the PC to `0xFFFC` (standard 6502 start location), and clears flags. |
| **Getting Instructions** | `CPU::FetchByte()` | The clerk walks to the mailbox at `PC`, increments `PC`, and returns the data. |
| **Working** | `CPU::Execute()` | A loop where the clerk keeps fetching and executing instructions for a set number of cycles. |

## Future Roadmap
- [ ] **Teach the Clerk Math**: Implement official 6502 opcodes (ADC, SBC, etc.).
- [ ] **Better Navigation**: Add support for all addressing modes.
- [ ] **Stack Management**: Implement Push/Pop operations.
- [ ] **Strict Schedule**: Add cycle-accurate timing.
