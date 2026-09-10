/* MAIN.CD member 0010 retail span [800CF8B4,800CF8CC). Offset 0x20ABC at base 800AEDF8.
 * SHA256(span)=b0a5a591e143a29928f2ed70bbf71ab86ce22c01d0ad010e64836679b09b3d9d.
 * Words are the retail member image (extracted/overlays/main/0010.bin); the C is
 * written from that disassembly because the registry has no member-0010 entry
 * for this address. Oracle MATCH 6/6.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x944299F0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x38420009)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
#else
#include "psx_types.h"

extern u16 D_800B99F0;

s32 func_800CF8B4(void) {
    return (D_800B99F0 ^ 9) < 1;
}
#endif
