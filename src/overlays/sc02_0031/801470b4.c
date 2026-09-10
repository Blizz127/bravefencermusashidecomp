/* Complete SC02 retail span [801470B4,801470C0).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820222)
#else
#include "psx_types.h"


void func_801470B4(s32 arg0) {
    *(s8 *)((u8 *)arg0 + 0x222) = 1;
}
#endif
