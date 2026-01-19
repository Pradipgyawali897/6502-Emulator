#include "../include/cpu.h"

void CPU::PushByte(u32 &Cycles, Byte Value, Mem &memory) {
    memory.WriteByte(0x0100 | SP, Value);
    SP--;
    Cycles--;
}

void CPU::PushWord(u32 &Cycles, Word Value, Mem &memory) {
    PushByte(Cycles, (Value >> 8) & 0xFF, memory);
    PushByte(Cycles, Value & 0xFF, memory);
}

Byte CPU::PopByte(u32 &Cycles, Mem &memory) {
    SP++;
    const Byte Value = memory.ReadByte(0x0100 | SP);
    Cycles--;
    return Value;
}

Word CPU::PopWord(u32 &Cycles, Mem &memory) {
    Word Value = PopByte(Cycles, memory);
    Value |= (static_cast<Word>(PopByte(Cycles, memory)) << 8);
    return Value;
}
