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

void CPU::LDASetStatus() {
    Z = (A == 0);
    N = (A & 0b10000000) > 0;
}

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

Byte CPU::ReadByte(u32 &Cycles, const Byte Address, Mem &memory) {
    const Byte Data = memory.ReadByte(Address);
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
