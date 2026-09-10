/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171A44,80171A58).
 * Offset 0x498EC at overlay base 80128158. SHA256(span)=644201adf9e62ea5c692e8b48283d884789be91789b01e92f76fab9ca3dbb982.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171a44.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x90820215)
MUSASHI_NATIVE_MIPS_WORD(0xA0800216)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820215)
#else
#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 u214, u215, u216; } T;
void func_80171A44(T *p) {
    p->u216 = 0;
    p->u215 = p->u215 + 1;
}
#endif
