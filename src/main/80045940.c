/* Exact retail word export for [80045940,800459E8); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffd8)
MUSASHI_NATIVE_MIPS_WORD(0xafb3001c)
MUSASHI_NATIVE_MIPS_WORD(0x00809821)
MUSASHI_NATIVE_MIPS_WORD(0xafb40020)
MUSASHI_NATIVE_MIPS_WORD(0x00a0a021)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x00008021)
MUSASHI_NATIVE_MIPS_WORD(0xafb20018)
MUSASHI_NATIVE_MIPS_WORD(0x3c128007)
MUSASHI_NATIVE_MIPS_WORD(0x26526a0c)
MUSASHI_NATIVE_MIPS_WORD(0xafb10014)
MUSASHI_NATIVE_MIPS_WORD(0x00008821)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0024)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0x00310821)
MUSASHI_NATIVE_MIPS_WORD(0x8c226a04)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040000e)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14530007)
MUSASHI_NATIVE_MIPS_WORD(0x02802021)
MUSASHI_NATIVE_MIPS_WORD(0x0c017137)
MUSASHI_NATIVE_MIPS_WORD(0x02402821)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x2652002c)
MUSASHI_NATIVE_MIPS_WORD(0x08011671)
MUSASHI_NATIVE_MIPS_WORD(0x26020001)
MUSASHI_NATIVE_MIPS_WORD(0x2652002c)
MUSASHI_NATIVE_MIPS_WORD(0x26100001)
MUSASHI_NATIVE_MIPS_WORD(0x2a020080)
MUSASHI_NATIVE_MIPS_WORD(0x1440ffee)
MUSASHI_NATIVE_MIPS_WORD(0x2631002c)
MUSASHI_NATIVE_MIPS_WORD(0x2402ffff)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0024)
MUSASHI_NATIVE_MIPS_WORD(0x8fb40020)
MUSASHI_NATIVE_MIPS_WORD(0x8fb3001c)
MUSASHI_NATIVE_MIPS_WORD(0x8fb20018)
MUSASHI_NATIVE_MIPS_WORD(0x8fb10014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0028)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8005C4DC(s32, void *);                          /* static */
extern s32 *D_80076A04;
extern s32 *D_80076A0C;

s32 func_80045940(s32 arg0, s32 arg1) {
    void *var_s2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s2 = &D_80076A0C;
    var_s1 = 0;
loop_1:
    temp_v0 = *(&D_80076A04 + var_s1);
    if (temp_v0 != 0) {
        if (temp_v0 == arg0) {
            var_s2 += 0x2C;
            if (func_8005C4DC(arg1, var_s2) == 0) {
                return var_s0 + 1;
            }
            goto block_6;
        }
        var_s2 += 0x2C;
block_6:
        var_s0 += 1;
        var_s1 += 0x2C;
        if (var_s0 >= 0x80) {
            goto block_7;
        }
        goto loop_1;
    }
block_7:
    return -1;
}
#endif
