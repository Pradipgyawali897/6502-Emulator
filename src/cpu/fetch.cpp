#include "cpu.h"

Byte CPU::FetchByte(u32 &Cycles, Mem &memory) {
  const Byte Data = memory.ReadByte(PC);
  PC++;
  Cycles--;
  return Data;
}

Word CPU::FetchWord(u32 &Cycles, Mem &memory) {
  Word Data = memory.ReadByte(PC);
  PC++;
  Cycles--;

  Data |= (static_cast<Word>(memory.ReadByte(PC)) << 8);
  PC++;
  Cycles--;

  return Data;
}

Byte CPU::ReadByte(u32 &Cycles, const Word Address, Mem &memory) {
  const Byte Data = memory.ReadByte(Address);
  Cycles--;
  return Data;
}
