/* SC02 resident retail span [80165658,80165670). Offset 0x3D500 at base 80128158.
 * SHA256(span)=3011c053929ec65153c608e016d527f8991581b7409631bc70f0d0e36afbb290.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_80181060->D_80187950.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x90227950)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_80187950[];
s32 func_80165658(s32 a0, u32 a1) {
    return D_80187950[a1 & 0x7F];
}
#endif
