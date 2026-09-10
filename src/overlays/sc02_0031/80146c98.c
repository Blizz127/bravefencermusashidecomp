/* Complete SC02 retail span [80146C98,80146CA0).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4850002)
#else
#include "psx_types.h"


void func_80146C98(s32 *a0, s16 a1) {
    *(s16 *)((s32)a0 + 0x2) = a1;
}
#endif
