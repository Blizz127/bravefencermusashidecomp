/* Overlay range [80139D04,80139DC8) from MAIN.CD member 0012.
 * SHA256(span)=29ee54114f20631d505417d3bd22872cd629cc619cc5dc4f7dccc709bd503947.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00804021)
MUSASHI_NATIVE_MIPS_WORD(0x24092710)
MUSASHI_NATIVE_MIPS_WORD(0x00005021)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x24060005)
MUSASHI_NATIVE_MIPS_WORD(0x3C0BCCCC)
MUSASHI_NATIVE_MIPS_WORD(0x356BCCCD)
MUSASHI_NATIVE_MIPS_WORD(0x30A3FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3122FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062001B)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0007000D)
MUSASHI_NATIVE_MIPS_WORD(0x00001812)
MUSASHI_NATIVE_MIPS_WORD(0x000A1100)
MUSASHI_NATIVE_MIPS_WORD(0x00625025)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x3142FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00C03821)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA1030000)
MUSASHI_NATIVE_MIPS_WORD(0x25080001)
MUSASHI_NATIVE_MIPS_WORD(0x30A3FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3122FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062001B)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0007000D)
MUSASHI_NATIVE_MIPS_WORD(0x00002010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x004B0019)
MUSASHI_NATIVE_MIPS_WORD(0x24C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00006010)
MUSASHI_NATIVE_MIPS_WORD(0x000C48C2)
MUSASHI_NATIVE_MIPS_WORD(0x1CC0FFDE)
MUSASHI_NATIVE_MIPS_WORD(0x00802821)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA1000000)
MUSASHI_NATIVE_MIPS_WORD(0x24E70001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80139D04(s8 *arg0, u32 arg1) {
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_v0;
    s8 *var_t0;
    u32 temp_a0;
    u32 temp_lo;
    u32 var_a1;

    var_a1 = arg1;
    var_t0 = arg0;
    var_t1 = 0x2710;
    var_t2 = 0;
    var_a3 = 0;
    var_a2 = 5;
    do {
        temp_lo = (u32) (var_a1 & 0xFFFF) / (u32) (var_t1 & 0xFFFF);
        var_t2 = temp_lo | (var_t2 * 0x10);
        if (!(var_a3 & 0xFFFF)) {
            var_v0 = var_a3 & 0xFFFF;
            if (var_t2 & 0xFFFF) {
                var_a3 = var_a2;
                var_v0 = var_a3 & 0xFFFF;
            }
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            *var_t0 = (s8) temp_lo;
            var_t0 += 1;
        }
        temp_a0 = (u32) (var_a1 & 0xFFFF) % (u32) (var_t1 & 0xFFFF);
        var_a2 -= 1;
        var_t1 = (var_t1 & 0xFFFF) / 10;
        var_a1 = temp_a0;
    } while (var_a2 > 0);
    if (!(var_a3 & 0xFFFF)) {
        *var_t0 = 0;
        var_a3 += 1;
    }
    return var_a3 & 0xFFFF;
}
#endif
