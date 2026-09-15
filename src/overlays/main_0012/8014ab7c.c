/* Overlay range [8014AB7C,8014ABF0) from MAIN.CD member 0012.
 * SHA256(span)=352b5db80e4f8c3f1b6501b301b19c4c0ba4ae659f8052a1aabc576bdd01abe6.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x2610F9D0)
MUSASHI_NATIVE_MIPS_WORD(0x26030820)
MUSASHI_NATIVE_MIPS_WORD(0x0203102B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x1040000C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00609021)
MUSASHI_NATIVE_MIPS_WORD(0x96020000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14510003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C058B33)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x26100068)
MUSASHI_NATIVE_MIPS_WORD(0x0212102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
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

void func_80162CCC(u16 *);                             /* static */
extern u16 D_8011F9D0;

void func_8014AB7C(s32 arg0) {
    u16 *temp_v1;
    u16 *var_s0;

    var_s0 = &D_8011F9D0;
    temp_v1 = &D_8011F9D0 + 0x820;
    if ((u32) &D_8011F9D0 < (u32) temp_v1) {
        do {
            if (*var_s0 == arg0) {
                func_80162CCC(var_s0);
            }
            var_s0 += 0x68;
        } while ((u32) var_s0 < (u32) temp_v1);
    }
}
#endif
