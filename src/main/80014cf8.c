/* Exact retail word export for [80014CF8,80014D30); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x308400FF)
MUSASHI_NATIVE_MIPS_WORD(0x00041080)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x24638D98)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x30A500FF)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x90420032)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Byte-exact C recovery, GCC 2.7.2 / ASPSX 2.56, -O2 -G0.
 * The 0x4c-byte record stride and byte offsets are observed accesses,
 * not a claim about the original record declaration. */
#include "psx_types.h"
extern u8 D_80078D98[];
u8 func_80014CF8(s32 port, s32 axis) {
    u8 *record = D_80078D98 + (port & 0xff) * 0x4c;
    /* Empty register constraint preserves the retail address evaluation order;
     * it emits no instructions. The load and indexing are recovered C. */
    __asm__("" : "=r"(record), "=r"(axis) : "0"(record), "1"(axis));
    return (record + (axis & 0xff))[0x32];
}
#endif
