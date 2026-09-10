/* Complete SC02 retail span [80147054,80147060).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA082004C)
#else
#include "psx_types.h"


s32 func_80147054(void *a0) {
    s32 r = 1;
    *(s8 *)((char *)a0 + 0x4C) = (s8)r;
    return r;
}
#endif
