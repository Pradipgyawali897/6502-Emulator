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

### Memory Map
The 6502 can address 64KB of memory. Here is how it is typically laid out:

| Address Range | Description | Notes |
| :--- | :--- | :--- |
| `$0000 - $00FF` | **Zero Page** | Faster to access (requires only 1 byte address). Often used for "heavy traffic" variables. |
| `$0100 - $01FF` | **Stack** | Hardcoded stack capability. `SP` register indexes this page ($0100 + SP). |
| `$0200 - $FFFF` | **General Purpose RAM** | Where your main program and data live. |
| `$FFFA - $FFFF` | **Interrupt Vectors** | Addresses where the CPU jumps when things happen (NMI, Reset, IRQ). |

### Addressing Modes
"Addressing Modes" is just a fancy way of saying: "Where is the data I need to work on?"

- **Implicit**: The data is implied by the instruction (e.g., `TAX` transfers A to X).
- **Immediate** (`#$nn`): The data is right here in the code.
  - *Example*: `LDA #$10` (Load the number 16 into A).
  - *Status*: **Implemented**.
- **Zero Page** (`$nn`): The data is in the first page of memory.
- **Zero Page, X/Y** (`$nn,X`): Address is `Address + X`.
- **Absolute** (`$nnnn`): Data is at a specific 16-bit address.
- **Absolute, X/Y** (`$nnnn,X`): Address is `Address + X`.
- **Indirect** (`($nnnn)`): The address contains *another* address (pointers!).

### Instruction Set
A small sampling of the instructions we are implementing:

- **LDA** (Load Accumulator): Puts a value into the A register. Affected Flags: **Z, N**.
- **LDX / LDY**: Load Index X / Y.
- **STA / STX / STY**: Store register contents into memory.
- **ADC** (Add with Carry): `A = A + M + C`.
- **JMP**: Jump to a new location (sets PC).

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
