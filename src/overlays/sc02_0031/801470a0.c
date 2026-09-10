/* Complete SC02 retail span [801470A0,801470AC).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820220)
#else
#include "psx_types.h"


s32 func_801470A0(void *a0) {
    s32 r = 1;
    *(s8 *)((char *)a0 + 0x220) = (s8)r;
    return r;
}
#endif
