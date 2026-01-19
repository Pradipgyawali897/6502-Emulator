#include "test_common.h"
#include "instructions.h"

struct ADCTestCase {
    Byte opcode;
    Byte operand;
    Byte A;
    bool carryIn;
    Byte expectedA;
    bool expectedC;
    bool expectedZ;
    bool expectedN;
    bool expectedV;
    u32 expectedCycles;
};

class ADCParamTest : public CPUEmulatorTest,
                     public ::testing::WithParamInterface<ADCTestCase> {};

TEST_P(ADCParamTest, ADCWorksCorrectly) {
    const auto& t = GetParam();

    cpu.Reset(mem);
    cpu.A = t.A;
    cpu.C = t.carryIn;
    cpu.PC = 0xFFFC;

    mem.WriteByte(0xFFFC, t.opcode);

    if (t.opcode == CPUOpCodes::INS_ADC_IM) {
        mem.WriteByte(0xFFFD, t.operand);
    }
    else if (t.opcode == CPUOpCodes::INS_ADC_ZP) {
        mem.WriteByte(0xFFFD, 0x10);
        mem.WriteByte(0x10, t.operand);
    }
    else if (t.opcode == CPUOpCodes::INS_ADC_ZPX) {
        cpu.X = 0x05;
        mem.WriteByte(0xFFFD, 0x10);
        mem.WriteByte(0x15, t.operand);
    }
    else if (t.opcode == CPUOpCodes::INS_ADC_ZPY) {
        cpu.Y = 0x05;
        mem.WriteByte(0xFFFD, 0x10);
        mem.WriteByte(0x15, t.operand);
    }

    u32 cyclesUsed = t.expectedCycles;
    cpu.Execute(cyclesUsed, mem);

    EXPECT_EQ(cyclesUsed, 0);
    EXPECT_EQ(cpu.A, t.expectedA);
    EXPECT_EQ(cpu.C, t.expectedC);
    EXPECT_EQ(cpu.Z, t.expectedZ);
    EXPECT_EQ(cpu.N, t.expectedN);
    EXPECT_EQ(cpu.V, t.expectedV);
}

INSTANTIATE_TEST_SUITE_P(
    ADCAllCases,
    ADCParamTest,
    ::testing::Values(
        ADCTestCase{0x69, 0x01, 0x01, 0, 0x02, 0, 0, 0, 0, 2},
        ADCTestCase{0x69, 0xFF, 0x01, 0, 0x00, 1, 1, 0, 0, 2},
        ADCTestCase{0x69, 0x80, 0x80, 0, 0x00, 1, 1, 0, 1, 2},
        ADCTestCase{0x69, 0x7F, 0x01, 0, 0x80, 0, 0, 1, 1, 2},
        ADCTestCase{0x69, 0x01, 0x7F, 0, 0x80, 0, 0, 1, 1, 2},
        ADCTestCase{0x65, 0x01, 0x01, 0, 0x02, 0, 0, 0, 0, 3},
        ADCTestCase{0x65, 0xFF, 0x01, 0, 0x00, 1, 1, 0, 0, 3},
        ADCTestCase{0x75, 0x01, 0x01, 0, 0x02, 0, 0, 0, 0, 4},
        ADCTestCase{0x75, 0xFF, 0x01, 0, 0x00, 1, 1, 0, 0, 4},
        ADCTestCase{0x79, 0x01, 0x01, 0, 0x02, 0, 0, 0, 0, 4},
        ADCTestCase{0x79, 0xFF, 0x01, 0, 0x00, 1, 1, 0, 0, 4},
        ADCTestCase{0x69, 0x05, 0x05, 1, 0x0B, 0, 0, 0, 0, 2},
        ADCTestCase{0x69, 0x00, 0x00, 0, 0x00, 0, 1, 0, 0, 2},
        ADCTestCase{0x69, 0x7F, 0x7F, 0, 0xFE, 0, 0, 1, 1, 2},
        ADCTestCase{0x69, 0x80, 0xFF, 0, 0x7F, 1, 0, 0, 1, 2}
    )
);
