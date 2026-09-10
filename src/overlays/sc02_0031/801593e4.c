/* SC02.CD FILE_031 / ov_SC02_031 retail span [801593E4,80159404).
 * Offset 0x3128C at overlay base 80128158. SHA256(span)=771f9151705d039ef869f54adf6867ac077432f93908935c61ab56aa10bab5e3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801593e4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94620012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420016)
MUSASHI_NATIVE_MIPS_WORD(0x30420FFF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4620012)
#else
#include "psx_types.h"
typedef struct Inner { u8 pad[0x12]; u16 a; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_801593E4(T *p) {
    p->inner->a = (p->inner->a + 0x16) & 0xFFF;
}
#endif
