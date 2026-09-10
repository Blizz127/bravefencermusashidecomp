/* Complete SC02 retail span [8014704C,80147054).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA080004C)
#else
#include "psx_types.h"


void func_8014704C(s32 *a0) {
    *(s8 *)((s32)a0 + 0x4C) = 0;
}
#endif
