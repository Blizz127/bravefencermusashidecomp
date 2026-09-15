/* Overlay range [801778A8,80177940) from MAIN.CD member 0012.
 * SHA256(span)=8b5bbfd874d7c4d1ca0c1afe2039f0076689b0c3f3013e36287db414732d5062.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24090100)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x00063403)
MUSASHI_NATIVE_MIPS_WORD(0x18C00020)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x24CBFFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00025403)
MUSASHI_NATIVE_MIPS_WORD(0x240CFEFF)
MUSASHI_NATIVE_MIPS_WORD(0x2487000C)
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00021702)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00081400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104B0003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x144A0002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00004821)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x25020001)
MUSASHI_NATIVE_MIPS_WORD(0x00404021)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94E4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x0046102A)
MUSASHI_NATIVE_MIPS_WORD(0xA0E30000)
MUSASHI_NATIVE_MIPS_WORD(0x008C2024)
MUSASHI_NATIVE_MIPS_WORD(0x01242025)
MUSASHI_NATIVE_MIPS_WORD(0xA4E4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE7)
MUSASHI_NATIVE_MIPS_WORD(0x24E70014)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_801778A8(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    s16 temp_v0;
    s16 var_t0;
    s32 var_a1;
    s32 var_t1;
    u32 temp_v0_2;
    void *var_a3;

    var_a1 = arg1;
    var_t1 = 0x100;
    var_t0 = 0;
    if (arg2 > 0) {
        var_a3 = arg0 + 0xC;
        do {
            temp_v0_2 = (u32) (var_a1 << 0x10) >> 0x1C;
            if ((temp_v0_2 != 0) || (var_t0 == (arg2 - 1)) || (var_t0 == arg3)) {
                var_t1 = 0;
            }
            var_a1 *= 0x10;
            temp_v0 = var_t0 + 1;
            var_t0 = temp_v0;
            M2C_FIELD(var_a3, s8 *, 0) = (s8) ((temp_v0_2 * 8) + 8);
            M2C_FIELD(var_a3, u16 *, -2) = (u16) (var_t1 | (M2C_FIELD(var_a3, u16 *, -2) & ~0x100));
            var_a3 += 0x14;
        } while (temp_v0 < arg2);
    }
}
#endif
