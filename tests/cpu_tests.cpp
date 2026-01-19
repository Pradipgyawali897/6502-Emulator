#include <gtest/gtest.h>
#include "cpu.h"
#include "memory.h"
#include "instructions.h"

class CPUEmulatorTest : public ::testing::Test {
protected:
    CPU cpu;
    Mem mem;

    void SetUp() override {
        cpu.Reset(mem);
    }
};

TEST_F(CPUEmulatorTest, CPUCanReset) {
    EXPECT_EQ(cpu.PC, 0xFFFC);
    EXPECT_EQ(cpu.SP, 0x0100);
    EXPECT_EQ(cpu.A, 0);
    EXPECT_EQ(cpu.X, 0);
    EXPECT_EQ(cpu.Y, 0);
    EXPECT_FALSE(cpu.C);
    EXPECT_FALSE(cpu.Z);
}

TEST_F(CPUEmulatorTest, LDAImmediateCanLoadAValue) {
    using namespace CPUOpCodes;
    mem.Data[0xFFFC] = INS_LDA_IM;
    mem.Data[0xFFFD] = 0x84;
    
    cpu.PC = 0xFFFC;
    cpu.Execute(2, mem);

    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
}

TEST_F(CPUEmulatorTest, LDAImmediateCanLoadZero) {
    using namespace CPUOpCodes;
    mem.Data[0xFFFC] = INS_LDA_IM;
    mem.Data[0xFFFD] = 0x00;
    
    cpu.PC = 0xFFFC;
    cpu.Execute(2, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}
