/* Complete SC02 retail span [80146DE8,80146DF8).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xAC850024)
MUSASHI_NATIVE_MIPS_WORD(0xAC860028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC87002C)
#else
#include "psx_types.h"


void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3) {
    *(s32 *)((s32)a0 + 0x24) = a1;
    *(s32 *)((s32)a0 + 0x28) = a2;
    *(s32 *)((s32)a0 + 0x2C) = a3;
}
#endif
