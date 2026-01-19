#include "test_common.h"
#include "instructions.h"

TEST_F(CPUEmulatorTest, CPUCanReset) {
    EXPECT_EQ(cpu.PC, 0xFFFC);
    EXPECT_EQ(cpu.SP, 0xFF);
    EXPECT_EQ(cpu.A, 0);
    EXPECT_EQ(cpu.X, 0);
    EXPECT_EQ(cpu.Y, 0);
    EXPECT_FALSE(cpu.C);
    EXPECT_FALSE(cpu.Z);
}

TEST_F(CPUEmulatorTest, LDAImmediateCanLoadAValue) {
    using namespace CPUOpCodes;
    mem.WriteByte(0xFFFC, INS_LDA_IM);
    mem.WriteByte(0xFFFD, 0x84);
    cpu.PC = 0xFFFC;
    u32 cycles = 2;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAImmediateCanLoadZero) {
    using namespace CPUOpCodes;
    mem.WriteByte(0xFFFC, INS_LDA_IM);
    mem.WriteByte(0xFFFD, 0x00);
    cpu.PC = 0xFFFC;
    u32 cycles = 2;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAZeroPageCanLoadAValue) {
    using namespace CPUOpCodes;
    mem.WriteByte(0x0020, 0x7F);
    mem.WriteByte(0xFFFC, INS_LDA_ZP);
    mem.WriteByte(0xFFFD, 0x20);
    cpu.PC = 0xFFFC;
    u32 cycles = 3;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x7F);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAZeroPageCanLoadNegativeValue) {
    using namespace CPUOpCodes;
    mem.WriteByte(0x0030, 0xFF);
    mem.WriteByte(0xFFFC, INS_LDA_ZP);
    mem.WriteByte(0xFFFD, 0x30);
    cpu.PC = 0xFFFC;
    u32 cycles = 3;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAZeroPageXCanLoadAValue) {
    using namespace CPUOpCodes;
    cpu.X = 0x05;
    mem.WriteByte(0x0015, 0x42);
    mem.WriteByte(0xFFFC, INS_LDA_ZPX);
    mem.WriteByte(0xFFFD, 0x10);
    cpu.PC = 0xFFFC;
    u32 cycles = 4;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAZeroPageXCanWrapAround) {
    using namespace CPUOpCodes;
    cpu.X = 0xFF;
    mem.WriteByte(0x000F, 0x33);
    mem.WriteByte(0xFFFC, INS_LDA_ZPX);
    mem.WriteByte(0xFFFD, 0x10);
    cpu.PC = 0xFFFC;
    u32 cycles = 4;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x33);
}

TEST_F(CPUEmulatorTest, LDAImmediateRobust) {
    using namespace CPUOpCodes;
    mem.WriteByte(0xFFFC, INS_LDA_IM);
    mem.WriteByte(0xFFFD, 0x55);
    cpu.PC = 0xFFFC;
    u32 cycles = 2;
    cpu.Execute(cycles, mem);
    EXPECT_EQ(cycles, 0);
    EXPECT_EQ(cpu.A, 0x55);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}
