/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165658,80165670).
 * Offset 0x3D500 at overlay base 80128158. SHA256(span)=fa17c47a29a0ce4306e0d445b691181959970d8ec060b926b10b99cc70aba34d.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_80181060 here is D_801818E8 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x902218E8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_801818E8[];
s32 func_80165658(s32 a0, u32 a1) {
    return D_801818E8[a1 & 0x7F];
}
#endif
