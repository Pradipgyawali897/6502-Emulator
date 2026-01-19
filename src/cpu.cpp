#include "../include/cpu.h"
#include "../include/instructions.h"
#include <iostream>

void CPU::Reset(Mem &memory) {
    PC = 0xFFFC;
    SP = 0x0100;
    D = 0;
    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;
    memory.initialize();
}

void CPU::LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

Byte CPU::FetchByte(u32 &Cycles, Mem &memory) {
    const Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
}

Word CPU::FetchWord(u32 &Cycles, Mem &memory) {
    Word Data = memory[PC];
    PC++;
    Cycles--;

    Data |= (memory[PC] << 8);
    PC++;
    Cycles--;

    return Data;
}

Byte CPU::ReadByte(u32 &Cycles, const Byte Address, Mem &memory) {
    const Byte Data = memory[Address];
    Cycles--;
    return Data;
}

void CPU::Execute(u32 Cycles, Mem &memory) {
    using namespace CPUOpCodes;
    while (Cycles > 0) {
        const Byte Ins = FetchByte(Cycles, memory);

        switch (Ins) {
        case INS_LDA_IM: {
            const Byte value = FetchByte(Cycles, memory);
            A = value;
            LDASetStatus();
            break;
        }
        case INS_LDA_ZP: {
            Byte ZeroPageAddress = FetchByte(Cycles, memory);
            A = ReadByte(Cycles, ZeroPageAddress, memory);
            LDASetStatus();
            break;
        }
        case INS_LDA_ZPX: {
            Byte ZeroPageAddress = FetchByte(Cycles, memory);
            ZeroPageAddress += X;
            Cycles--;
            A = ReadByte(Cycles, ZeroPageAddress, memory);
            LDASetStatus();
            break;
        }
        case INS_JSR: {
            const Word SubAddr = FetchWord(Cycles, memory);
            memory.WriteWord(Cycles, PC - 1, SP);
            PC = SubAddr;
            Cycles--;
            break;
        }
        default:
            std::cout << "There is problem on excuting the instruction" << " " << (u32)Ins << std::endl;
            break;
        }
    }
}
