/* Overlay range [8017DCB0,8017DD28) from MAIN.CD member 0012.
 * SHA256(span)=1c86375acb7f40915e3e3176ee5d35c0f6b0acf52c1c667b16241a0b51a93f46.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x18A00019)
MUSASHI_NATIVE_MIPS_WORD(0x00004821)
MUSASHI_NATIVE_MIPS_WORD(0x3C0A8018)
MUSASHI_NATIVE_MIPS_WORD(0x254A2540)
MUSASHI_NATIVE_MIPS_WORD(0x00041F02)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0x00604021)
MUSASHI_NATIVE_MIPS_WORD(0x10600003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805F73B)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x2408000A)
MUSASHI_NATIVE_MIPS_WORD(0x00042100)
MUSASHI_NATIVE_MIPS_WORD(0x00081080)
MUSASHI_NATIVE_MIPS_WORD(0x004A1021)
MUSASHI_NATIVE_MIPS_WORD(0x8C430000)
MUSASHI_NATIVE_MIPS_WORD(0x25220001)
MUSASHI_NATIVE_MIPS_WORD(0x00404821)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94630000)
MUSASHI_NATIVE_MIPS_WORD(0x0045102A)
MUSASHI_NATIVE_MIPS_WORD(0xA4C30000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEB)
MUSASHI_NATIVE_MIPS_WORD(0x24C60002)
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

extern s32 D_80182540;

void func_8017DCB0(u32 arg0, s16 arg1, u16 *arg2, s32 arg3) {
    s16 temp_v0;
    s16 var_t1;
    s32 var_a3;
    u16 *var_a2;
    u32 temp_v1;
    u32 var_a0;
    u32 var_t0;

    var_a0 = arg0;
    var_a2 = arg2;
    var_a3 = arg3;
    var_t1 = 0;
    if (arg1 > 0) {
        do {
            temp_v1 = var_a0 >> 0x1C;
            var_t0 = temp_v1;
            if ((var_a3 << 0x10) != 0) {
                if (temp_v1 != 0) {
                    var_a3 = 0;
                } else {
                    var_t0 = 0xA;
                }
            }
            var_a0 *= 0x10;
            temp_v0 = var_t1 + 1;
            var_t1 = temp_v0;
            *var_a2 = **((var_t0 * 4) + D_80182540);
            var_a2 += 2;
        } while (temp_v0 < arg1);
    }
}
#endif
