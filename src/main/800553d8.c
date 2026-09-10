/* Exact retail [800553D8,800553F4). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000610C0)
MUSASHI_NATIVE_MIPS_WORD(0x00461023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0xACA40008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACA00000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* Independently reverified MATCH7/7 at800553D8 with pinned-O2 toolchain.
 * Stores the indexed resource pointer and clears the first word. */

struct data_800553D8 {
    s32 unk0;
    u8 pad[4];
    s32 unk8;
};

void func_800553D8(s32 arg0, struct data_800553D8 *arg1, s32 arg2) {
    arg1->unk8 = (s32) (arg0 + (arg2 * 0x1C));
    arg1->unk0 = 0;
}

#endif
