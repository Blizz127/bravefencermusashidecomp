/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016B964,8016B984).
 * Offset 0x4380C at overlay base 80128158. SHA256(span)=841dd8668888a432a18c3d489cead666e0d2bd1fd53ccece6c8583587b2aa5b8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016b964.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20008)
MUSASHI_NATIVE_MIPS_WORD(0x9483000A)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0xA4A2000C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4A3000A)
#else
#include "psx_types.h"
typedef struct { u8 pad[6]; u16 u6; u8 pad8[2]; u16 uA; } T;
typedef struct { u8 pad[8]; u16 u8, uA, uC; } D;
void func_8016B964(T *p, D *d) {
    d->u8 = p->u6;
    d->uA = p->uA;
    d->uC = 3;
}
#endif
