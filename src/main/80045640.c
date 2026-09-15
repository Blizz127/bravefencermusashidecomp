/* Exact retail word export for [80045640,80045660); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c017161)
MUSASHI_NATIVE_MIPS_WORD(0x2406000c)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x2c420001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (8/8 words at 0x80045640). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

s32 func_8005C584(s32, s32, s32);

s32 func_80045640(s32 arg0, s32 arg1) {
    return func_8005C584(arg0, arg1, 0xC) == 0;
}
#endif
