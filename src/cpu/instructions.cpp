#include "instructions.h"
#include "cpu.h"

void CPU::LDASetStatus() {
  Z = (A == 0);
  N = (A & 0b10000000) > 0;
}

void CPU::LDA(Byte value) {
  A = value;
  LDASetStatus();
}

void CPU::ADC(Byte value) {
  const Word sum =
      static_cast<Word>(A) + static_cast<Word>(value) + static_cast<Word>(C);
  V = (~(static_cast<Word>(A) ^ static_cast<Word>(value)) &
       (static_cast<Word>(A) ^ sum) & 0x80)
          ? 1
          : 0;
  A = static_cast<Byte>(sum & 0xFF);
  C = (sum > 0xFF) ? 1 : 0;
  LDASetStatus();
}

void CPU::ExecuteLDA_IM(Byte, u32 &Cycles, Mem &memory) {
  LDA(FetchByte(Cycles, memory));
}

void CPU::ExecuteLDA_ZP(Byte, u32 &Cycles, Mem &memory) {
  LDA(FetchByteByZero(Cycles, memory));
}

void CPU::ExecuteLDA_ZPX(Byte, u32 &Cycles, Mem &memory) {
  LDA(FetchByteByZeroX(Cycles, memory));
}

void CPU::ExecuteADC_IM(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByte(Cycles, memory));
}

void CPU::ExecuteADC_ZP(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByteByZero(Cycles, memory));
}

void CPU::ExecuteADC_ZPX(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByteByZeroX(Cycles, memory));
}

void CPU::ExecuteADC_ABS(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByteByAbsolute(Cycles, memory));
}

void CPU::ExecuteADC_ABSX(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByteByAbsoluteX(Cycles, memory));
}

void CPU::ExecuteADC_ABSY(Byte, u32 &Cycles, Mem &memory) {
  ADC(FetchByteByAbsoluteY(Cycles, memory));
}

void CPU::ExecuteBRK(Byte, u32 &Cycles, Mem &) { Cycles = 0; }

CPU::Instruction CPU::Table[256] = {};

void CPU::ExecuteJSR(Byte, u32 &Cycles, Mem &memory) {
  const Word SubAddr = FetchWord(Cycles, memory);
  PushWord(Cycles, PC - 1, memory);
  PC = SubAddr;
  Cycles--;
}

void CPU::InitTable() {
  using namespace CPUOpCodes;

  struct Descriptor {
    Byte op;
    const char *name;
    void (CPU::*exec)(Byte, u32 &, Mem &);
  };

  Descriptor entries[] = {
      {INS_LDA_IM, "LDA_IM", &CPU::ExecuteLDA_IM},
      {INS_LDA_ZP, "LDA_ZP", &CPU::ExecuteLDA_ZP},
      {INS_LDA_ZPX, "LDA_ZPX", &CPU::ExecuteLDA_ZPX},
      {INS_JSR, "JSR", &CPU::ExecuteJSR},
      {INS_ADC_IM, "ADC_IM", &CPU::ExecuteADC_IM},
      {INS_ADC_ZP, "ADC_ZP", &CPU::ExecuteADC_ZP},
      {INS_ADC_ZPX, "ADC_ZPX", &CPU::ExecuteADC_ZPX},
      {INS_ADC_ABS, "ADC_ABS", &CPU::ExecuteADC_ABS},
      {INS_ADC_ABSX, "ADC_ABSX", &CPU::ExecuteADC_ABSX},
      {INS_ADC_ABSY, "ADC_ABSY", &CPU::ExecuteADC_ABSY},
      {INS_BRK, "BRK", &CPU::ExecuteBRK},
  };

  for (const auto &i : entries) {
    Table[i.op] = {i.name, i.exec};
  }
}
