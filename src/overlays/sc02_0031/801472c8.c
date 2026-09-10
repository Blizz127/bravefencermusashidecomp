/* Complete SC02 retail span [801472C8,801472DC).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482007E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482007E)
#else
#include "psx_types.h"


s32 func_801472C8(s32 a0) {
    s32 v0 = *(u16 *)(a0 + 0x7E) | 2;

    *(u16 *)(a0 + 0x7E) = v0;
    return v0;
}
#endif
