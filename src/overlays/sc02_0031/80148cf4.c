/* Complete SC02 retail span [80148CF4,80148D0C).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24A5FA00)
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x30A50FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4450012)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
#else
#include "psx_types.h"

s32 func_80148CF4(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x600) & 0xFFF;
    return 1;
}
#endif
