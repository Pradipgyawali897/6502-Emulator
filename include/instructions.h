#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "common.h"

namespace CPUOpCodes {
static constexpr Byte INS_BRK = 0x00;
static constexpr Byte INS_LDA_IM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;
static constexpr Byte INS_LDA_ZPX = 0xB5;
static constexpr Byte INS_JSR = 0x20;
static constexpr Byte INS_ADC_IM = 0x69;
static constexpr Byte INS_ADC_ZP = 0x65;
static constexpr Byte INS_ADC_ZPX = 0x75;
static constexpr Byte INS_ADC_ABS = 0x6D;
static constexpr Byte INS_ADC_ABSX = 0x7D;
static constexpr Byte INS_ADC_ABSY = 0x79;
static constexpr Byte INS_AND_IM= 0x29;
static constexpr Byte INS_AND_ZP= 0x25;
static constexpr Byte INS_AND_ZPX= 0x35;
static constexpr Byte INS_AND_ABS= 0x2D;
static constexpr Byte INS_AND_ABSX= 0x3D;
static constexpr Byte INS_AND_ABSY= 0x39;

} // namespace CPUOpCodes

#endif // INSTRUCTIONS_H
