/* Main-exec range [8002C320,8002C3B0) from the SLUS executable.
 * SHA256(span)=bc45b3ac220bb74d8607ba4fbc091accf73c21383711723e353df44dfc53606d.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x00006021)
MUSASHI_NATIVE_MIPS_WORD(0x240E0001)
MUSASHI_NATIVE_MIPS_WORD(0x240D0002)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x24425AC0)
MUSASHI_NATIVE_MIPS_WORD(0x24460010)
MUSASHI_NATIVE_MIPS_WORD(0x244B0002)
MUSASHI_NATIVE_MIPS_WORD(0x00405021)
MUSASHI_NATIVE_MIPS_WORD(0x91420000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040000E)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x95690000)
MUSASHI_NATIVE_MIPS_WORD(0x00C01821)
MUSASHI_NATIVE_MIPS_WORD(0x24C50070)
MUSASHI_NATIVE_MIPS_WORD(0x90620000)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x0065102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x3082FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x15220002)
MUSASHI_NATIVE_MIPS_WORD(0x00ED1004)
MUSASHI_NATIVE_MIPS_WORD(0x00EE1004)
MUSASHI_NATIVE_MIPS_WORD(0x01024025)
MUSASHI_NATIVE_MIPS_WORD(0x24E70008)
MUSASHI_NATIVE_MIPS_WORD(0x24C60080)
MUSASHI_NATIVE_MIPS_WORD(0x256B0080)
MUSASHI_NATIVE_MIPS_WORD(0x258C0001)
MUSASHI_NATIVE_MIPS_WORD(0x29820004)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE9)
MUSASHI_NATIVE_MIPS_WORD(0x254A0080)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x01001021)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 D_80075AC0;

s32 func_8002C320(void) {
    s32 var_a0;
    s32 var_a3;
    s32 var_t0;
    s32 var_t4;
    s32 var_v0;
    u8 *var_a2;
    u8 *var_t2;
    u8 *var_t3;
    u8 *var_v1;
    u8 temp_v0;

    var_t0 = 0;
    var_t4 = 0;
    var_a3 = 0;
    var_a2 = &D_80075AC0 + 0x10;
    var_t3 = &D_80075AC0 + 2;
    var_t2 = &D_80075AC0;
    do {
        var_a0 = 0;
        if (*var_t2 != 0) {
            var_v1 = var_a2;
            do {
                temp_v0 = *var_v1;
                var_v1 += 1;
                var_a0 += temp_v0;
            } while ((s32) var_v1 < (s32) (var_a2 + 0x70));
            var_v0 = 2 << var_a3;
            if (*var_t3 == (var_a0 & 0xFFFF)) {
                var_v0 = 1 << var_a3;
            }
            var_t0 |= var_v0;
        }
        var_a3 += 8;
        var_a2 += 0x80;
        var_t3 += 0x80;
        var_t4 += 1;
        var_t2 += 0x80;
    } while (var_t4 < 4);
    return var_t0;
}
#endif
