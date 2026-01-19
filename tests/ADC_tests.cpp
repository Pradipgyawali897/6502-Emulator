#include "test_common.h"
#include "instructions.h"

struct ADCTestCase {
    Byte A;
    Byte M;
    bool carryIn;

    Byte expectedA;
    bool expectedC;
    bool expectedZ;
    bool expectedN;
    bool expectedV;
};
class ADCParamTest : public CPUEmulatorTest,
                     public ::testing::WithParamInterface<ADCTestCase> {};


                     
                     
TEST_P(ADCParamTest, ADCImmediateWorksCorrectly) {
    using namespace CPUOpCodes;
    const auto& t = GetParam();

    cpu.Reset(mem);

    cpu.A = t.A;
    cpu.C = t.carryIn;

    // ADC #M
    mem.WriteByte(0xFFFC, INS_ADC_IM);
    mem.WriteByte(0xFFFD, t.M);
    cpu.PC = 0xFFFC;
    cpu.Execute(2, mem);

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
        ADCTestCase{0x10, 0x20, 0, 0x30, 0, 0, 0, 0},
        ADCTestCase{0xFF, 0x01, 0, 0x00, 1, 1, 0, 0},
        ADCTestCase{0x10, 0x10, 1, 0x21, 0, 0, 0, 0},
        ADCTestCase{0x40, 0x40, 0, 0x80, 0, 0, 1, 1},
        ADCTestCase{0x00, 0x00, 0, 0x00, 0, 1, 0, 0},
        ADCTestCase{0x7F, 0x01, 0, 0x80, 0, 0, 1, 1},
        ADCTestCase{0x80, 0x80, 0, 0x00, 1, 1, 0, 1}
    )
);
