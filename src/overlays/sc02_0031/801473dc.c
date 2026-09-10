/* Complete SC02 retail span [801473DC,801473EC).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xAC800018)
MUSASHI_NATIVE_MIPS_WORD(0xAC800014)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800010)
#else
#include "psx_types.h"


void func_801473DC(s32 a0) {
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x14) = 0;
    *(s32 *)(a0 + 0x10) = 0;
}
#endif
