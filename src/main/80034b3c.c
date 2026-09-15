/* Main-exec range [80034B3C,80034B98) from the SLUS executable.
 * SHA256(span)=3673a206afc685a37f3fc0e64183a08cc916d4c1ee1184ecbbb28b8a6a46cb00.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x8C63AEF8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42AEFC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1062000D)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x9063620C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30620080)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x30630020)
MUSASHI_NATIVE_MIPS_WORD(0x0800D2E4)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x10600005)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0800D2E4)
MUSASHI_NATIVE_MIPS_WORD(0x24020004)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA020620C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8007620C;

s32 func_80034B3C(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_8006AEF8 != D_8006AEFC) {
        if (D_8007620C & 0x80) {
            return 2;
        }
        var_v0 = 1;
        if (D_8007620C & 0x20) {
            return 4;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return var_v0;
    }
    D_8007620C = 0;
    return var_v0;
}
#endif
