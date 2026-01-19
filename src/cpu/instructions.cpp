#include "../include/cpu.h"
#include "../include/instructions.h"

void CPU::LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

void CPU::LDA(Byte value) {
    A = value;
    LDASetStatus();
}

void CPU::ADC(Byte value) {
    const Word sum = static_cast<Word>(A) + static_cast<Word>(value) + static_cast<Word>(C);
    V = (~(static_cast<Word>(A) ^ static_cast<Word>(value)) & (static_cast<Word>(A) ^ sum) & 0x80) ? 1 : 0;
    A = static_cast<Byte>(sum & 0xFF); 
    C = (sum > 0xFF) ? 1 : 0;
    LDASetStatus();
}

void CPU::ExecuteLDA(Byte OpCode, u32 &Cycles, Mem &memory) {
    using namespace CPUOpCodes;
    switch (OpCode) {
    case INS_LDA_IM: {
        LDA(FetchByte(Cycles, memory));
        break;
    }
    case INS_LDA_ZP: {
        LDA(FetchByteByZero(Cycles, memory));
        break;
    }
    case INS_LDA_ZPX: {
        LDA(FetchByteByZeroX(Cycles, memory));
        break;
    }
    }
}

void CPU::ExecuteADC(Byte OpCode, u32 &Cycles, Mem &memory) {
    using namespace CPUOpCodes;
    switch (OpCode) {
    case INS_ADC_IM: {
        ADC(FetchByte(Cycles, memory));
        break;
    }
    case INS_ADC_ZP: {
        ADC(FetchByteByZero(Cycles, memory));
        break;
    }
    case INS_ADC_ZPX: {
        ADC(FetchByteByZeroX(Cycles, memory));
        break;
    }
    case INS_ADC_ZPY: {
        ADC(FetchByteByZeroY(Cycles, memory));
        break;
    }
    }
}

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
        const char* name;
        void (CPU::*exec)(Byte, u32&, Mem&);
    };

    Descriptor entries[] = {
        { INS_LDA_IM, "LDA_IM", &CPU::ExecuteLDA },
        { INS_LDA_ZP, "LDA_ZP", &CPU::ExecuteLDA },
        { INS_LDA_ZPX, "LDA_ZPX", &CPU::ExecuteLDA },
        { INS_ADC_IM, "ADC_IM", &CPU::ExecuteADC },
        { INS_ADC_ZP, "ADC_ZP", &CPU::ExecuteADC },
        { INS_ADC_ZPX, "ADC_ZPX", &CPU::ExecuteADC },
        { INS_ADC_ZPY, "ADC_ZPY", &CPU::ExecuteADC },
        { INS_JSR, "JSR", &CPU::ExecuteJSR }
    };

    for (const auto& i : entries) {
        Table[i.op] = { i.name, i.exec };
    }
}
