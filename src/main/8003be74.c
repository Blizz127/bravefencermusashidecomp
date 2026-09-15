/* Exact retail word export for [8003BE74,8003BE98); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x240600cc)
MUSASHI_NATIVE_MIPS_WORD(0x0c00efa6)
MUSASHI_NATIVE_MIPS_WORD(0x240700cd)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (9/9 words at 0x8003BE74). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

void func_8003BE98(s32, s32, s32, s32);

void func_8003BE74(s32 arg0, s32 arg1) {
    func_8003BE98(arg0, arg1, 0xCC, 0xCD);
}
#endif
