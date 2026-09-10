/* Complete SC02 retail span [80146E90,80146E98).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC85001C)
#else
#include "psx_types.h"


void func_80146E90(s32 *a0, s32 a1) {
    *(s32 *)((s32)a0 + 0x1C) = a1;
}
#endif
