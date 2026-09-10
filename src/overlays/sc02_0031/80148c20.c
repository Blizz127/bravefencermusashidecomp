/* Complete SC02 retail span [80148C20,80148C34).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4450012)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
#else
#include "psx_types.h"

s32 func_80148C20(s32 a0, s16 a1) {
    s32 *p = *(s32 **)(a0 + 0x20);
    *(s16 *)((s32)p + 0x12) = a1;
    return 1;
}
#endif
