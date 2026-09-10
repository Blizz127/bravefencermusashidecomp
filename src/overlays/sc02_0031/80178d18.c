/* SC02 resident retail span [80178D18,80178D40). Offset 0x50BC0 at base 80128158.
 * SHA256(span)=b6fa4207fb98a8dc1c27f334aaed30e032d45f7bf812aabe5d17c9fcae55db97.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_80185C7C->D_801B7B0C.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xA4207B0C)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D1C5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80174714();                                  /* static */
extern s16 D_801B7B0C;

void func_80178D18(void) {
    D_801B7B0C = 0;
    func_80174714();
}
#endif
