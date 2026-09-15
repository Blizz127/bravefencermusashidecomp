/* Overlay range [80177F84,80178004) from MAIN.CD member 0012.
 * SHA256(span)=bed8f3b04b51ef580ed5ea79d423f6ed955c6b21d88e5e6043358e88815c0ce0.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24080100)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x240A0005)
MUSASHI_NATIVE_MIPS_WORD(0x2409FEFF)
MUSASHI_NATIVE_MIPS_WORD(0x2486000C)
MUSASHI_NATIVE_MIPS_WORD(0x00051403)
MUSASHI_NATIVE_MIPS_WORD(0x3042000F)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104A0003)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x10800002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x24C60014)
MUSASHI_NATIVE_MIPS_WORD(0x24E20001)
MUSASHI_NATIVE_MIPS_WORD(0x00403821)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x28420005)
MUSASHI_NATIVE_MIPS_WORD(0xA0C30000)
MUSASHI_NATIVE_MIPS_WORD(0x00892024)
MUSASHI_NATIVE_MIPS_WORD(0x01042025)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE8)
MUSASHI_NATIVE_MIPS_WORD(0xA4C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80177F84(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 var_a3;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_t0;
    void *var_a2;

    var_a1 = arg1;
    var_t0 = 0x100;
    var_a3 = 0;
    var_a2 = arg0 + 0xC;
    do {
        temp_v0_2 = (var_a1 >> 0x10) & 0xF;
        temp_v1 = temp_v0_2;
        temp_a0 = temp_v0_2;
        var_a1 *= 0x10;
        if ((var_a3 == 5) || (temp_a0 != 0)) {
            var_t0 = 0;
        }
        var_a2 += 0x14;
        temp_v0 = var_a3 + 1;
        var_a3 = temp_v0;
        M2C_FIELD(var_a2, s8 *, 0) = (s8) ((temp_v1 * 8) + 8);
        M2C_FIELD(var_a2, u16 *, -2) = (u16) (var_t0 | (M2C_FIELD(var_a2, u16 *, -2) & ~0x100));
    } while (temp_v0 < 5);
}
#endif
