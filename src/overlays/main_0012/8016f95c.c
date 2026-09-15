/* Overlay range [8016F95C,8016F9C4) from MAIN.CD member 0012.
 * SHA256(span)=8f0f906a1a18698ef403450d62c1b7857813e1e4bbcaa5785d228aec6acd066c.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x24A5F73E)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x94A60000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14C00005)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C731)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x0805BE68)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C747)
MUSASHI_NATIVE_MIPS_WORD(0x30C600FF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80171928(s32);                               /* static */
s32 func_80171CC4(u16 *, u16);                      /* static */
s32 func_80171D1C(s32, u16 *, s32);                 /* static */
extern u16 D_8011F73E;

void func_8016F95C(s32 arg0) {
    s32 var_v0;

    if (D_8011F73E == 0) {
        var_v0 = func_80171CC4(&D_8011F73E - 6, D_8011F73E);
    } else {
        var_v0 = func_80171D1C(arg0, &D_8011F73E - 6, D_8011F73E & 0xFF);
    }
    if (var_v0 != 0) {
        func_80171928(arg0);
    }
}
#endif
