#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "common.h"

namespace CPUOpCodes {
    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;
    static constexpr Byte INS_LDA_ZPX = 0xB5;
    static constexpr Byte INS_JSR = 0x20;
    static constexpr Byte INS_ADC_IM = 0x69;
}

#endif // INSTRUCTIONS_H
