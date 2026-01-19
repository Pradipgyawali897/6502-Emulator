#include "../include/memory.h"

void Mem::initialize() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0;
    }
}

Byte Mem::ReadByte(u32 Address) const {
    if (Address >= MAX_MEM) return 0;
    return Data[Address];
}

void Mem::WriteByte(u32 Address, Byte Value) {
    if (Address < MAX_MEM) {
        Data[Address] = Value;
    }
}

Byte Mem::operator[](u32 Address) const {
    return ReadByte(Address);
}

void Mem::WriteWord(u32 &Cycles, const Word Value, const u32 Address) {
    WriteByte(Address, Value & 0xFF);
    WriteByte(Address + 1, (Value >> 8));
    Cycles -= 2;
}
