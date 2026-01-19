#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <gtest/gtest.h>
#include "cpu.h"
#include "memory.h"

class CPUEmulatorTest : public ::testing::Test {
protected:
    CPU cpu;
    Mem mem;

    void SetUp() override {
        cpu.Reset(mem);
    }
};

#endif // TEST_COMMON_H
