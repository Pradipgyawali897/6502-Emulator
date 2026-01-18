#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM]; // Memory size is 64kb

    void initilize();

    // Read the 1 byte
    Byte operator[](u32 Address) const;

    void WriteWord(u32 &Cycles, Word Value, u32 Address);
};

#endif // MEMORY_H
