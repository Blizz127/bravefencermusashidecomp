/* Exact retail word export for [80011350,8001136C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdfff8)
MUSASHI_NATIVE_MIPS_WORD(0xafbe0000)
MUSASHI_NATIVE_MIPS_WORD(0x03a0f021)
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c424784)
MUSASHI_NATIVE_MIPS_WORD(0x080044db)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (7/7 words at 0x80011350). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

extern s32 D_80074784;

s32 func_80011350(void) {
    return D_80074784;
}
#endif
