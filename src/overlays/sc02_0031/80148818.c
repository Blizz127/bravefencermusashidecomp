/* Complete SC02 retail span [80148818,80148824).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x948200AE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00021202)
#else
#include "psx_types.h"

u16 func_80148818(s32 *a0) {
    return *(u16 *)((s32)a0 + 0xAE) >> 8;
}
#endif
