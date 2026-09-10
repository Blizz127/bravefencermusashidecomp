/* SC02 resident retail span [801656E8,80165700). Offset 0x3D590 at base 80128158.
 * SHA256(span)=30a2c5c8c36bf4c1bb94ac4ba2e293689c134853b9db6f98400f362563b7b69e.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8018111C->D_80187A0C.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x90227A0C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_80187A0C[];
s32 func_801656E8(s32 a0, u32 a1) {
    return D_80187A0C[a1 & 0x7F];
}
#endif
