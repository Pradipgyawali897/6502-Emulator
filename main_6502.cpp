#include "include/common.h"
#include "include/cpu.h"
#include "include/instructions.h"
#include "include/memory.h"
#include <iostream>
#include <stdlib.h>

int main() {
  using namespace CPUOpCodes;

  CPU cpu;
  Mem mem;

  cpu.Reset(mem);

  Word i = 0x8000;
  cpu.PC = i;

  mem.WriteByte(i++, INS_LDA_IM);
  mem.WriteByte(i++, 0x05);

  mem.WriteByte(i++, INS_LDA_IM);
  mem.WriteByte(i++, 0x0A);

  mem.WriteByte(i++, INS_ADC_IM);
  mem.WriteByte(i++, 0x03);

  Word dataAddr = 0x1000;
  mem.WriteByte(dataAddr, 0x04);

  cpu.X = 0x00;

  mem.WriteByte(i++, INS_ADC_ABSX);
  mem.WriteByte(i++, 0x00);
  mem.WriteByte(i++, 0x10);
  
  
  mem.WriteByte(i++,INS_LDA_IM);
  mem.WriteByte(i++,0xFF);
  
  mem.WriteByte(i++,INS_AND_ABS);
  mem.WriteByte(i++,0x00);
  mem.WriteByte(i++,0x10);
  mem.WriteByte(0x0010,0x0F);
  
  mem.WriteByte(i++,INS_JSR);
  mem.WriteByte(i++,0x90);
  mem.WriteByte(i++,0x80);
  mem.WriteByte(i++,INS_BRK);
  u32 cycles = 100;
  cpu.Execute(cycles, mem);

  std::cout << "--- Execution Results ---" << std::endl;
  std::cout << "A  " << (int)cpu.A << std::endl;
  std::cout << "PC: 0x" << std::hex << cpu.PC << std::endl;
  std::cout << "Cycles Remaining: " << std::dec << cycles << std::endl;

  return 0;
}
