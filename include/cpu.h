#ifndef CPU_H
#define CPU_H

#include "common.h"
#include "memory.h"

struct CPU {
    Word PC; // Program counter = 16 bit
    Word SP;

    Byte A, X, Y; // 8 bit Register

    // flags
    Byte C : 1; // Carry
    Byte Z : 1; // Zero
    Byte I : 1; // Interrupt Disable
    Byte D : 1; // Decimal
    Byte B : 1; // Break
    Byte V : 1; // Overflow
    Byte N : 1; // Negative

    void Reset(Mem &memory);
    void LDASetStatus();
    Byte FetchByte(u32 &Cycles, Mem &memory);
    Word FetchWord(u32 &Cycles, Mem &memory);
    Byte ReadByte(u32 &Cycles, Byte &Address, Mem &memory);
    void Excute(u32 Cycles, Mem &memory);
};

#endif // CPU_H
