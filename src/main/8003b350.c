/* Main-exec range [8003B350,8003B3D0) from the SLUS executable.
 * SHA256(span)=7b07e72e3c307deb9852178fe091cbf6224147ea96282ca27513224e18b7ed5e.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B5B0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x3C088000)
MUSASHI_NATIVE_MIPS_WORD(0x0800ECF2)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C074000)
MUSASHI_NATIVE_MIPS_WORD(0x3C060FFF)
MUSASHI_NATIVE_MIPS_WORD(0x34C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00402821)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00681024)
MUSASHI_NATIVE_MIPS_WORD(0x1440000C)
MUSASHI_NATIVE_MIPS_WORD(0x00671024)
MUSASHI_NATIVE_MIPS_WORD(0x1440000C)
MUSASHI_NATIVE_MIPS_WORD(0x00661824)
MUSASHI_NATIVE_MIPS_WORD(0x0064102B)
MUSASHI_NATIVE_MIPS_WORD(0x1040000A)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00621021)
MUSASHI_NATIVE_MIPS_WORD(0x0082102B)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0800ECDF)
MUSASHI_NATIVE_MIPS_WORD(0x24A50008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8006B5B0;

s32 func_8003B350(u32 arg0) {
    s32 temp_v1;
    s32 var_v0;
    u32 temp_v1_2;
    void *var_a1;

    if (D_8006B5B0 == 0) {
        return 0;
    }
    var_a1 = D_8006B5B0;
loop_3:
    temp_v1 = M2C_FIELD(var_a1, s32 *, 0);
    if (temp_v1 & 0x80000000) {
block_7:
        var_a1 += 8;
        goto loop_3;
    }
    temp_v1_2 = temp_v1 & 0x0FFFFFFF;
    if (!(temp_v1 & 0x40000000)) {
        var_v0 = 1;
        if (temp_v1_2 < arg0) {
            var_v0 = 1;
            if (arg0 >= (u32) (temp_v1_2 + M2C_FIELD(var_a1, s32 *, 4))) {
                goto block_7;
            }
        }
    } else {
        var_v0 = 0;
    }
    return var_v0;
}
#endif
