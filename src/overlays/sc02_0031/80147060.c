/* Complete SC02 retail span [80147060,8014706C).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA082004D)
#else
#include "psx_types.h"


s32 func_80147060(u8 *a0) {
    s32 v = 1;
    a0[0x4D] = (u8)v;
    return v;
}
#endif
