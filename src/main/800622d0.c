#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173d2)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173c2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c0188e5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00008021)
MUSASHI_NATIVE_MIPS_WORD(0x0c0189f6)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173c6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */
void func_8005CF48();                                 /* static */
s32 func_80062394();                                /* static */
void func_800627D8(s32);                               /* static */

void func_800622D0(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
    func_8005CF48(0);
    func_8005CF08();
    if (func_80062394() == 0) {
        var_s0 = 0;
    }
    func_800627D8(var_s0);
    func_8005CF18();
}
