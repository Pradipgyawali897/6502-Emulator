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

    mem.WriteByte(0xFFFC, 0x00);
    mem.WriteByte(0xFFFD, 0x80);

    u32 i = 0x8000;

    mem.WriteByte(i++, INS_LDA_IM);
    mem.WriteByte(i++, 0x05);

    mem.WriteByte(i++, INS_JSR);
    mem.WriteByte(i++, 0x06);
    mem.WriteByte(i++, 0x80);

    mem.WriteByte(0x8006, INS_LDA_IM);
    mem.WriteByte(0x8007, 0x0A);

    mem.WriteByte(i++, INS_ADC_IM);
    mem.WriteByte(i++, 0x03);

    cpu.PC = mem[0xFFFC] | (mem[0xFFFD] << 8);

    u32 cycles = 10;
    cpu.Execute(cycles, mem);

    std::cout << "A = " << (int)cpu.A << std::endl;
    std::cout << "PC = 0x" << std::hex << cpu.PC << std::endl;

    return 0;
}
