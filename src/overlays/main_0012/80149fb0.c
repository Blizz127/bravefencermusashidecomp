/* Overlay range [80149FB0,8014A048) from MAIN.CD member 0012.
 * SHA256(span)=c0b00bc1387cc6482062e6cc6d51d5b3ca133b621846f50ef3e8f0ae67e2732a.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028018)
MUSASHI_NATIVE_MIPS_WORD(0x2442FF38)
MUSASHI_NATIVE_MIPS_WORD(0x8C430000)
MUSASHI_NATIVE_MIPS_WORD(0x3C068008)
MUSASHI_NATIVE_MIPS_WORD(0x24C68E78)
MUSASHI_NATIVE_MIPS_WORD(0x1060000A)
MUSASHI_NATIVE_MIPS_WORD(0x24420004)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800C)
MUSASHI_NATIVE_MIPS_WORD(0x84A59A08)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10A30013)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C430000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1460FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x24420004)
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420400)
MUSASHI_NATIVE_MIPS_WORD(0x14400010)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x848201C8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440000C)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x948200AC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420100)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x08052810)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x90C30048)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x38630080)
MUSASHI_NATIVE_MIPS_WORD(0xA0C30048)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8017FF38;
extern s32 *D_80078E78;
extern s16 D_800B9A08;

s32 func_80149FB0(void *arg0) {
    s32 *var_v0_2;
    s32 var_v0;
    s32 var_v1;

    var_v1 = D_8017FF38;
    var_v0_2 = D_8017FF38 + 4;
    if (var_v1 != 0) {
loop_2:
        if (D_800B9A08 != var_v1) {
            var_v1 = *var_v0_2;
            var_v0_2 += 4;
            if (var_v1 == 0) {
                goto block_4;
            }
            goto loop_2;
        }
        goto block_7;
    }
block_4:
    var_v0 = 0;
    if (!(M2C_FIELD(arg0, s32 *, 0x44) & 0x400)) {
        var_v0 = 0;
        if (M2C_FIELD(arg0, s16 *, 0x1C8) == 0) {
            var_v0 = 1;
            if (!(M2C_FIELD(arg0, u16 *, 0xAC) & 0x100)) {
block_7:
                return 0;
            }
            M2C_FIELD(&D_80078E78, u8 *, 0x48) = (u8) (M2C_FIELD(&D_80078E78, u8 *, 0x48) ^ 0x80);
            /* Duplicate return node #9. Try simplifying control flow for better match */
            return var_v0;
        }
    }
    return var_v0;
}
#endif
