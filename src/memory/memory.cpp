#include <iostream>
#include "../include/memory.h"

void Mem::initialize() {
    for (u32 i = 0; i < MAX_MEM; i++) {
        Data[i] = 0;
    }
}

Byte Mem::ReadByte(u32 Address) const {
    if (Address >= MAX_MEM) {
        std::cerr << "Memory Read Error: Address " << std::hex << Address << " is out of bounds!" << std::endl;
        return 0;
    }
    return Data[Address];
}

void Mem::WriteByte(u32 Address, Byte Value) {
    if (Address >= MAX_MEM) {
        std::cerr << "Memory Write Error: Address " << std::hex << Address << " is out of bounds!" << std::endl;
        return;
    }
    Data[Address] = Value;
}

Byte Mem::operator[](u32 Address) const {
    return ReadByte(Address);
}

Word Mem::ReadWord(u32 &Cycles, u32 Address) const {
    Word Data = ReadByte(Address);
    Data |= (static_cast<Word>(ReadByte(Address + 1)) << 8);
    Cycles -= 2;
    return Data;
}

void Mem::WriteWord(u32 &Cycles, const Word Value, const u32 Address) {
    WriteByte(Address, Value & 0xFF);
    WriteByte(Address + 1, (Value >> 8));
    Cycles -= 2;
}
