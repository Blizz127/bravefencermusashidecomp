/* SC02.CD FILE_031 / ov_SC02_031 retail span [801656D0,801656E8).
 * Offset 0x3D578 at overlay base 80128158. SHA256(span)=73c31ebd507595318627375367d6e2e7e0c28eb6a5b2000fce19079d32924e4a.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_801810FC here is D_80181984 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x90221984)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_80181984[];
s32 func_801656D0(s32 a0, u32 a1) {
    return D_80181984[a1 & 0x7F];
}
#endif
