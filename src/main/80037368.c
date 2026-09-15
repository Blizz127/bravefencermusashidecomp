/* Exact retail word export for [80037368,800373D0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3C068007)
MUSASHI_NATIVE_MIPS_WORD(0x24C66220)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0xA0C00000)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90226251)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90226250)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0xA0226220)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24630010)
MUSASHI_NATIVE_MIPS_WORD(0x28620050)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEF)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x24426220)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC850000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 D_80076220;
extern s32 *D_80076250;
extern s32 *D_80076251;

u8 *func_80037368(s32 *arg0) {
    s32 var_a1;
    s32 var_v1;
    u8 *var_a2;

    var_a1 = 0;
    var_a2 = &D_80076220;
    var_v1 = 0;
    do {
        *var_a2 = 0;
        var_a2 += 1;
        if (*(&D_80076251 + var_v1) != 0) {
            (&D_80076220)[var_a1] = *(&D_80076250 + var_v1);
            var_a1 += 1;
        }
        var_v1 += 0x10;
    } while (var_v1 < 0x50);
    *arg0 = var_a1;
    return &D_80076220;
}
#endif
