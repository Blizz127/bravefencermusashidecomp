#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0x00240821)
MUSASHI_NATIVE_MIPS_WORD(0xa025a1b8)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Decompiled from main.s. The byte table element is the only observed effect;
 * the inferred array type is not evidence of the original declaration. */
extern u8 D_800BA1B8[];

void func_800291A0(s32 selector, s32 value) {
    D_800BA1B8[selector] = value;
}
