/* Complete SC02 retail span [801474EC,80147514).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA480011C)
MUSASHI_NATIVE_MIPS_WORD(0xA480011A)
MUSASHI_NATIVE_MIPS_WORD(0xA4800118)
MUSASHI_NATIVE_MIPS_WORD(0xA4800124)
MUSASHI_NATIVE_MIPS_WORD(0xA4800122)
MUSASHI_NATIVE_MIPS_WORD(0xA4800120)
MUSASHI_NATIVE_MIPS_WORD(0xA480012C)
MUSASHI_NATIVE_MIPS_WORD(0xA480012A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4800128)
#else
#include "psx_types.h"


void func_801474EC(s32 a0) {
    *(s16 *)(a0 + 0x11C) = 0;
    *(s16 *)(a0 + 0x11A) = 0;
    *(s16 *)(a0 + 0x118) = 0;
    *(s16 *)(a0 + 0x124) = 0;
    *(s16 *)(a0 + 0x122) = 0;
    *(s16 *)(a0 + 0x120) = 0;
    *(s16 *)(a0 + 0x12C) = 0;
    *(s16 *)(a0 + 0x12A) = 0;
    *(s16 *)(a0 + 0x128) = 0;
}
#endif
