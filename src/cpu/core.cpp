#include "../include/cpu.h"
#include "../include/instructions.h"
#include <iostream>

void CPU::Reset(Mem &memory) {
    PC = 0xFFFC;
    SP = 0xFF; 
    D = 0;
    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;
    memory.initialize();
}

void CPU::Execute(u32 &Cycles, Mem &memory) {
    using namespace CPUOpCodes;
    while (Cycles > 0) {
        const Byte Ins = FetchByte(Cycles, memory);

        switch (Ins) {
        case INS_LDA_IM:
        case INS_LDA_ZP:
        case INS_LDA_ZPX: {
            ExecuteLDA(Ins, Cycles, memory);
            break;
        }
        case INS_ADC_IM:
        case INS_ADC_ZP:
        case INS_ADC_ZPX:
        case INS_ADC_ZPY: {
            ExecuteADC(Ins, Cycles, memory);
            break;
        }
        case INS_JSR: {
            const Word SubAddr = FetchWord(Cycles, memory);
            PushWord(Cycles, PC - 1, memory);
            PC = SubAddr;
            Cycles--;
            break;
        }
        default:
            std::cerr << "Illegal Opcode: " << std::hex << (int)Ins << std::endl;
            Cycles = 0; // Halt execution
            break;
        }
    }
}
