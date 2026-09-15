/* Exact retail word export for [8004162C,800416A8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x8C63B5A8)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x18600014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x3C094000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028000)
MUSASHI_NATIVE_MIPS_WORD(0x00824025)
MUSASHI_NATIVE_MIPS_WORD(0x00603821)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA5B5B0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00691024)
MUSASHI_NATIVE_MIPS_WORD(0x14400008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14640003)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x080105A4)
MUSASHI_NATIVE_MIPS_WORD(0xACA80000)
MUSASHI_NATIVE_MIPS_WORD(0x00C7102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x24A50008)
MUSASHI_NATIVE_MIPS_WORD(0x0C0105AA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8006B5A8;
extern s32 D_8006B5B0;
void func_800416A8(s32 *, s32, s32);                   /* static */

void func_8004162C(s32 arg0, s32 *arg1, s32 arg3) {
    s32 *var_a1;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;

    var_a1 = arg1;
    var_a3 = arg3;
    var_a2 = 0;
    if (D_8006B5A8 > 0) {
        var_a3 = D_8006B5A8;
        var_a1 = D_8006B5B0;
loop_2:
        temp_v1 = *var_a1;
        if (!(temp_v1 & 0x40000000)) {
            var_a2 += 1;
            if (temp_v1 == arg0) {
                *var_a1 = arg0 | 0x80000000;
            } else {
                var_a1 += 8;
                if (var_a2 < var_a3) {
                    goto loop_2;
                }
            }
        }
    }
    func_800416A8(var_a1, var_a2, var_a3);
}
#endif
