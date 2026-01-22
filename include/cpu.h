#ifndef CPU_H
#define CPU_H

#include "common.h"
#include "memory.h"

struct CPU {
  Word PC; // Program counter = 16 bit
  Byte SP;

  Byte A, X, Y; // 8 bit Register

  // flags
  Byte C : 1; // Carry
  Byte Z : 1; // Zero
  Byte I : 1; // Interrupt Disable
  Byte D : 1; // Decimal
  Byte B : 1; // Break
  Byte V : 1; // Overflow
  Byte N : 1; // Negative

  void Reset(Mem &memory);
  void LDASetStatus();
  Byte FetchByte(u32 &Cycles, Mem &memory);
  Word FetchWord(u32 &Cycles, Mem &memory);
  Byte ReadByte(u32 &Cycles, const Word Address, Mem &memory);
  Byte FetchByteByZero(u32 &Cycles, Mem &memory);
  Byte FetchByteByZeroX(u32 &Cycles, Mem &memory);
  Byte FetchByteByZeroY(u32 &Cycles, Mem &memory);
  Byte FetchByteByAbsolute(u32 &Cycles, Mem &memory);
  Byte FetchByteByAbsoluteX(u32 &Cycles, Mem &memory);
  Byte FetchByteByAbsoluteY(u32 &Cycles, Mem &memory);
  void Execute(u32 &Cycles, Mem &memory);

  struct Instruction {
    const char *Name;
    void (CPU::*Executor)(Byte, u32 &, Mem &);
  };

  static Instruction Table[256];
  static void InitTable();

private:
  void LDA(Byte value);
  void ADC(Byte value);

  void ExecuteLDA_IM(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteLDA_ZP(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteLDA_ZPX(Byte OpCode, u32 &Cycles, Mem &memory);

  void ExecuteADC_IM(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteADC_ZP(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteADC_ZPX(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteADC_ABS(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteADC_ABSX(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteADC_ABSY(Byte OpCode, u32 &Cycles, Mem &memory);
  void ExecuteBRK(Byte OpCode, u32 &Cycles, Mem &memory);

  void ExecuteJSR(Byte OpCode, u32 &Cycles, Mem &memory);

  void PushByte(u32 &Cycles, Byte Value, Mem &memory);
  void PushWord(u32 &Cycles, Word Value, Mem &memory);
  Byte PopByte(u32 &Cycles, Mem &memory);
  Word PopWord(u32 &Cycles, Mem &memory);
};

#endif // CPU_H
