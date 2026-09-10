/* Complete SC02 retail span [801474D8,801474EC).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA4800136)
MUSASHI_NATIVE_MIPS_WORD(0xA4800134)
MUSASHI_NATIVE_MIPS_WORD(0xA4800132)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4800130)
#else
#include "psx_types.h"


void func_801474D8(s32 a0) {
    *(s16 *)(a0 + 0x136) = 0;
    *(s16 *)(a0 + 0x134) = 0;
    *(s16 *)(a0 + 0x132) = 0;
    *(s16 *)(a0 + 0x130) = 0;
}
#endif
