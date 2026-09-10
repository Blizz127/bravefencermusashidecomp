/* Complete SC02 retail span [80147078,80147084).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA4850000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4800002)
#else
#include "psx_types.h"


void func_80147078(s32 *a0, s16 a1) {
    *(s16 *)((s32)a0 + 0x0) = a1;
    *(s16 *)((s32)a0 + 0x2) = 0;
}
#endif
