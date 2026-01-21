#include "../include/cpu.h"
#include "../include/instructions.h"
#include <iostream>

void CPU::Reset(Mem &memory) {
    PC = 0xFFFC;
    SP = 0xFF; 
    D = 0;
    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;
    InitTable();
    memory.initialize();
}

void CPU::Execute(u32 &Cycles, Mem &memory) {
    while (Cycles > 0) {
        const Byte OpCode = FetchByte(Cycles, memory);
        const Instruction& Ins = Table[OpCode];
        
        if (Ins.Executor) {
            (this->*Ins.Executor)(OpCode, Cycles, memory);
            std::cout << "Executed: " << Ins.Name << ", Cycles left: " << Cycles << std::endl;

        } else {
            std::cerr << "Illegal Opcode: " << std::hex << "0x" << (int)OpCode << std::endl;
            std::cerr<<"The error occurred at PC: "<<std::hex<<"0x"<<PC-1<<std::endl;
            std::cerr<<Ins.Name<<" Has  the error"<<std::endl;
            Cycles = 0;
            break;
        }
    }
}
