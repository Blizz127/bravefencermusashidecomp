/* Complete SC02 retail span [80148F80,80148F8C).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24820200)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30420FFF)
#else
#include "psx_types.h"

s32 func_80148F80(s32 a0) {
    return (a0 + 0x200) & 0xFFF;
}
#endif
