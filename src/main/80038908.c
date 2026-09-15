/* Exact retail word export for [80038908,80038958); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800A)
MUSASHI_NATIVE_MIPS_WORD(0x84424EF8)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800A)
MUSASHI_NATIVE_MIPS_WORD(0x94634EE0)
MUSASHI_NATIVE_MIPS_WORD(0x000229C0)
MUSASHI_NATIVE_MIPS_WORD(0x00A30018)
MUSASHI_NATIVE_MIPS_WORD(0x24860012)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x00002812)
MUSASHI_NATIVE_MIPS_WORD(0x00052B83)
MUSASHI_NATIVE_MIPS_WORD(0x94C20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00A20018)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x24C60008)
MUSASHI_NATIVE_MIPS_WORD(0x00002812)
MUSASHI_NATIVE_MIPS_WORD(0x0461FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x00052B83)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4850010)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u16 D_800A4EE0;
extern s16 D_800A4EF8;

void func_80038908(void *arg0) {
    s32 temp_lo;
    s32 var_a1;
    s32 var_v1;
    u16 *var_a2;

    var_a2 = arg0 + 0x12;
    var_v1 = 0;
    var_a1 = (s32) ((D_800A4EF8 << 7) * D_800A4EE0) >> 0xE;
    do {
        temp_lo = var_a1 * *var_a2;
        var_v1 -= 1;
        var_a2 += 8;
        var_a1 = temp_lo >> 0xE;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, s16 *, 0x10) = (s16) var_a1;
}
#endif
