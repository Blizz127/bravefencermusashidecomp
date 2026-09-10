/* Exact retail word export for [8005C324,8005C358); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x1080000a)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x18c00007)
MUSASHI_NATIVE_MIPS_WORD(0x00801821)
MUSASHI_NATIVE_MIPS_WORD(0x90a20000)
MUSASHI_NATIVE_MIPS_WORD(0x24a50001)
MUSASHI_NATIVE_MIPS_WORD(0x24c6ffff)
MUSASHI_NATIVE_MIPS_WORD(0xa0820000)
MUSASHI_NATIVE_MIPS_WORD(0x1cc0fffb)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

u8 *func_8005C324(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 var_a2;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_v0;
    u8 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    var_v0 = 0;
    if (var_a0 != 0) {
        temp_v1 = var_a0;
        if (var_a2 > 0) {
            do {
                temp_v0 = *var_a1;
                var_a1 += 1;
                var_a2 -= 1;
                *var_a0 = temp_v0;
                var_a0 += 1;
            } while (var_a2 > 0);
        }
        var_v0 = temp_v1;
    }
    return var_v0;
}
#endif
