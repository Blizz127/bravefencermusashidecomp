/* Complete SC02 retail span [8014706C,80147078).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA082004D)
#else
#include "psx_types.h"


void func_8014706C(void *arg0) {
    *(s8 *)((u8 *)arg0 + 0x4D) = 2;
}
#endif
