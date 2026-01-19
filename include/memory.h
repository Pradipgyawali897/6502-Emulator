#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;

    void initialize();

    [[nodiscard]] Byte ReadByte(u32 Address) const;
    void WriteByte(u32 Address, Byte Value);
    Byte operator[](u32 Address) const;

    void WriteWord(u32 &Cycles, const Word Value, const u32 Address);

private:
    Byte Data[MAX_MEM]; // Memory size is 64kb
};

#endif // MEMORY_H
