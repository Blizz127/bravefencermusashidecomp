/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Exact retail word export for [8005E188,8005E1A4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xAC850028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0860034)
MUSASHI_NATIVE_MIPS_WORD(0xA0850036)
MUSASHI_NATIVE_MIPS_WORD(0xAC86002C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0870035)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8005E188 (main.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word store (sw) plus byte store in the delay slot (sb). NOTE: two UNNAMED siblings follow in-range (sb/sw pairs); separate functions, not modeled here. Body is m2c's verbatim with types
 * filled in. */

struct data_8005E188 {
    u8 pad[0x28];
    s32 unk28;
    u8 pad2[0x8];
    u8 unk34;
};

void func_8005E188(struct data_8005E188 *arg0, s32 arg1, s8 arg2) {
    arg0->unk28 = arg1;
    arg0->unk34 = arg2;
}

#endif
