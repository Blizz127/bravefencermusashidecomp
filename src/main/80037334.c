/* Exact retail word export for [80037334,80037358); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xA0206251)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0x0441FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80076251;

void func_80037334(void) {
    s32 var_v0;

    var_v0 = 0x40;
    do {
        *(&D_80076251 + var_v0) = 0;
        var_v0 -= 0x10;
    } while (var_v0 >= 0);
}
#endif
