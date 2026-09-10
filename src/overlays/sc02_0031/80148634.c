/* Complete SC02 retail span [80148634,80148648).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x34028080)
MUSASHI_NATIVE_MIPS_WORD(0xA48000AA)
MUSASHI_NATIVE_MIPS_WORD(0xA48000AC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48200AE)
#else
#include "psx_types.h"


void func_80148634(void *a0) {
    *(u16 *)((s32)a0 + 0xAA) = 0;
    *(u16 *)((s32)a0 + 0xAC) = 0;
    *(u16 *)((s32)a0 + 0xAE) = 0x8080;
}

#endif
