/* Exact retail word export for [8004239C,80042404); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42ba94)
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c63ba98)
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe0)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0018)
MUSASHI_NATIVE_MIPS_WORD(0xafb10014)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x8c500000)
MUSASHI_NATIVE_MIPS_WORD(0x8c620000)
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c63ba9c)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x04810005)
MUSASHI_NATIVE_MIPS_WORD(0x3051ffff)
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42cbb8)
MUSASHI_NATIVE_MIPS_WORD(0x08010933)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x10820036)
MUSASHI_NATIVE_MIPS_WORD(0x02201021)
MUSASHI_NATIVE_MIPS_WORD(0x18800007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_8006BA94;
extern s32 *D_8006BA98;
extern s32 D_8006BA9C;
extern s32 D_8006BAA0;
extern s32 D_8006CBB8;
void func_800424E4(s32, s32);                          /* static */

s32 func_8004239C(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 var_a1;
    s32 var_v0;

    temp_s1 = (*D_8006BA98 - D_8006BA9C) & 0xFFFF;
    if (arg0 < 0) {
        return D_8006CBB8;
    }
    if (arg0 != 1) {
        if (arg0 > 0) {
            var_v0 = *(s32 *)0x8006BAA0 - 1 + arg0;
        } else {
            var_v0 = D_8006BAA0;
        }
        var_a1 = 0;
        if (arg0 > 0) {
            var_a1 = arg0 - 1;
        }
        func_800424E4(var_v0, var_a1);
        temp_s0 = *D_8006BA94;
        func_800424E4(D_8006CBB8 + 1, 1);
        if ((temp_s0 & 0x400000) && ((temp_s0 ^ *D_8006BA94) >= 0)) {
            do {

            } while (!((temp_s0 ^ *D_8006BA94) & 0x80000000));
        }
        D_8006BAA0 = (s32) D_8006CBB8;
        D_8006BA9C = (s32) *D_8006BA98;
    }
    return temp_s1;
}
#endif
