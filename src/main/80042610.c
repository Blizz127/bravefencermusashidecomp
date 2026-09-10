/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Exact retail word export for [80042610,80042644); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42CB84)
MUSASHI_NATIVE_MIPS_WORD(0x00802821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C420014)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x24040004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80042610 (main.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. D_8006CB84 is a LOADED struct pointer (lw) shared
 * with func_80042718's dispatch table; this unit calls the callback
 * at +0x14 Callback at +0x14 with (4, arg0) (lw/jalr). Body is m2c's verbatim with the member typed. */

struct cb84_80042610 {
    u8 pad[0x14];
    void (*unk14)(s32, s32);
};

extern struct cb84_80042610 *D_8006CB84;

void func_80042610(s32 arg0) {
    D_8006CB84->unk14(4, arg0);
}
#endif
