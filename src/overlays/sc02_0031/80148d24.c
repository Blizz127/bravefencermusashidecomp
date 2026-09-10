/* Complete SC02 retail span [80148D24,80148D3C).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24A5F800)
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x30A50FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4450012)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
#else
#include "psx_types.h"

s32 func_80148D24(void *a0, s32 a1) {
    s32 p = *(s32 *)((u8 *)a0 + 0x20);
    *(s16 *)(p + 0x12) = (a1 - 0x800) & 0xFFF;
    return 1;
}
#endif
