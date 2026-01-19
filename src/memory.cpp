#include "../include/memory.h"

void Mem::initialize() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0;
    }
}

Byte Mem::operator[](u32 Address) const {
    return Data[Address];
}

void Mem::WriteWord(u32 &Cycles, const Word Value, const u32 Address) {
    Data[Address] = Value & 0xFF;
    Data[Address + 1] = (Value >> 8);
    Cycles -= 2;
}
