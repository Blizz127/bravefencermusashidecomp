/* Exact retail word export for [80058B40,80058B7C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30820003)
MUSASHI_NATIVE_MIPS_WORD(0x000211C0)
MUSASHI_NATIVE_MIPS_WORD(0x30A50003)
MUSASHI_NATIVE_MIPS_WORD(0x00052940)
MUSASHI_NATIVE_MIPS_WORD(0x00451025)
MUSASHI_NATIVE_MIPS_WORD(0x30E30100)
MUSASHI_NATIVE_MIPS_WORD(0x00031903)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x30C603FF)
MUSASHI_NATIVE_MIPS_WORD(0x00063183)
MUSASHI_NATIVE_MIPS_WORD(0x00461025)
MUSASHI_NATIVE_MIPS_WORD(0x30E70200)
MUSASHI_NATIVE_MIPS_WORD(0x00073880)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00471025)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80058B40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return ((arg0 & 3) << 7) | ((arg1 & 3) << 5) | ((s32) (arg3 & 0x100) >> 4) | ((s32) (arg2 & 0x3FF) >> 6) | ((arg3 & 0x200) * 4);
}
#endif
