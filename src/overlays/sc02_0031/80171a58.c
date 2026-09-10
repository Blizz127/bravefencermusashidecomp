/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171A58,80171A6C).
 * Offset 0x49900 at overlay base 80128158. SHA256(span)=7865ab33e7d49d35d1f66b5d110722a55d021491932ec531ad19fb50bb364f95.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171a58.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90820216)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820216)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x216]; u8 u216; } T;
void func_80171A58(T *p) {
    p->u216 = p->u216 + 1;
}
#endif
