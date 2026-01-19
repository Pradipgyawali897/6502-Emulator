#include "../include/cpu.h"

Byte CPU::FetchByteByZero(u32 &Cycles, Mem &memory) {
    const Byte Address = FetchByte(Cycles, memory);
    return ReadByte(Cycles, Address, memory);
}

Byte CPU::FetchByteByZeroX(u32 &Cycles, Mem &memory) {
    Byte Address = FetchByte(Cycles, memory);
    Address += X;
    Cycles--; // 1 cycle for addition
    return ReadByte(Cycles, Address, memory);
}

Byte CPU::FetchByteByZeroY(u32 &Cycles, Mem &memory) {
    Byte Address = FetchByte(Cycles, memory);
    Address += Y;
    Cycles--; // 1 cycle for addition
    return ReadByte(Cycles, Address, memory);
}
