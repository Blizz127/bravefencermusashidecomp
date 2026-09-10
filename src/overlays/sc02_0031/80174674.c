/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174674,80174684).
 * Offset 0x4C51C at overlay base 80128158. SHA256(span)=0f1291b00bcc4c4bff16672efec439e8af6c259f3a91ae713e9fb97877509a76.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174674.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC2070BC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_801270BC;

void func_80174674(void) {
    D_801270BC = 0;
}
#endif
