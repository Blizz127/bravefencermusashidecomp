/* Exact retail word export for [80043440,80043450); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x2442cca0)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled and verified byte-exact against the registered retail EXE. */
extern u8 D_8006CCA0[];

void *func_80043440(void) {
    return D_8006CCA0;
}
#endif
