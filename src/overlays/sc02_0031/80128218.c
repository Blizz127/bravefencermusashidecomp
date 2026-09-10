/* SC02 resident retail span [80128218,80128228). Offset 0xC0 at base 80128158.
 * SHA256(span)=838b34049533ad069b4fa45c8d858297006ead52bed045a0073f084b5eedc833.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_80182D1C->D_801B5128.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C425128)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_801B5128;

s32 func_80128218(void) {
    return D_801B5128;
}

#endif
