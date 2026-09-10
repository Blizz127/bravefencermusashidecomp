/* Complete SC02 retail span [801472B4,801472C8).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482007E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482007E)
#else
#include "psx_types.h"


void func_801472B4(s32 a0) {
    *(u16 *)(a0 + 0x7E) &= 0xFFFD;
}
#endif
