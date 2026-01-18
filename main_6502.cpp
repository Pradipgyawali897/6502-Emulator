#include <iostream>
#include <stdlib.h>
#include "include/common.h"
#include "include/memory.h"
#include "include/cpu.h"
#include "include/instructions.h"

int main() {
    using namespace CPUOpCodes;
    CPU cpu;
    Mem mem;

    cpu.Reset(mem);

    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x80;

    u32 i = 0x8000;

    mem.Data[i++] = INS_LDA_IM;
    mem.Data[i++] = 0x05;

    mem.Data[i++] = INS_JSR;
    mem.Data[i++] = 0x06;
    mem.Data[i++] = 0x80;

    mem.Data[0x8006] = INS_LDA_IM;
    mem.Data[0x8007] = 0x0A;

    cpu.PC = mem[0xFFFC] | (mem[0xFFFD] << 8);

    cpu.Excute(10, mem);

    std::cout << "A = " << (int)cpu.A << std::endl;
    std::cout << "PC = 0x" << std::hex << cpu.PC << std::endl;

    return 0;
}
