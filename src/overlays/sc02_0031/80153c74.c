/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153C74,80153C8C).
 * Offset 0x2BB1C at overlay base 80128158. SHA256(span)=e2a3948ec956746158324482669fff2fda0abeb02fca34c4dde12a7ababc3283.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80153c74.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA424DB0C)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA425DB1A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s16 D_8011DB0C;
extern s16 D_8011DB1A;

void func_80153C74(s16 arg0, s16 arg1) {
    D_8011DB0C = arg0;
    D_8011DB1A = arg1;
}
#endif
