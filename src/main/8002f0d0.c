/* Exact retail word export for [8002F0D0,8002F0F4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020054)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xAC2064B0)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x0441FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (9/9 words at 0x8002F0D0). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

extern u8 D_800A64B0[];

void func_8002F0D0(void) {
    s32 i;

    for (i = 0x54; i >= 0; i -= 0xC) {
        *(s32 *) (D_800A64B0 + i) = 0;
    }
}
#endif
