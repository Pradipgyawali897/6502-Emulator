#include "../include/cpu.h"
#include "../include/memory.h"

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

Byte CPU::FetchByteByAbsolute(u32 &Cycles, Mem &memory) {
    const Word Address = FetchWord(Cycles, memory);
    return ReadByte(Cycles, Address, memory);
}


Byte CPU::FetchByteByAbsoluteX(u32 &cycles,Mem &memory){
    Word BaseAddress=FetchWord(cycles,memory);
    Word Address=BaseAddress+static_cast<Word>(X);
    bool is_page_crossed=(BaseAddress& 0xFF00) != (Address & 0xFF00);
    if(is_page_crossed)
        cycles --;
    return ReadByte(cycles,Address,memory);
}

Byte CPU::FetchByteByAbsoluteY(u32 &cycles,Mem &memory){
    Word BaseAddress=FetchWord(cycles,memory);
    Word Address=BaseAddress+static_cast<Word>(Y);
    bool is_page_crossed=(BaseAddress& 0xFF00) != (Address & 0xFF00);
    if(is_page_crossed)
        cycles --;
    return ReadByte(cycles,Address,memory);
}