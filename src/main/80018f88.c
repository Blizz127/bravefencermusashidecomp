/* Exact retail word export for [80018F88,80018FC8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x24820001)
MUSASHI_NATIVE_MIPS_WORD(0xa040002a)
MUSASHI_NATIVE_MIPS_WORD(0x2463ffff)
MUSASHI_NATIVE_MIPS_WORD(0x0461fffd)
MUSASHI_NATIVE_MIPS_WORD(0x2442ffff)
MUSASHI_NATIVE_MIPS_WORD(0x24030002)
MUSASHI_NATIVE_MIPS_WORD(0x24050080)
MUSASHI_NATIVE_MIPS_WORD(0x00831021)
MUSASHI_NATIVE_MIPS_WORD(0xa045002a)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x28620006)
MUSASHI_NATIVE_MIPS_WORD(0x1440fffb)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (16/16 words at 0x80018F88). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"
#include "m2c_macros.h"

void func_80018F88(s32 arg0) {
    s32 var_v1;
    s32 var_v1_2;
    void *var_v0;

    var_v1 = 1;
    var_v0 = arg0 + 1;
    do {
        M2C_FIELD(var_v0, u8 *, 0x2A) = 0;
        var_v1 -= 1;
        var_v0 -= 1;
    } while (var_v1 >= 0);
    var_v1_2 = 2;
    do {
        M2C_FIELD((arg0 + var_v1_2), u8 *, 0x2A) = 0x80;
        var_v1_2 += 1;
    } while (var_v1_2 < 6);
}
#endif
