/* SC02.CD FILE_031 / ov_SC02_031 retail span [801656E8,80165700).
 * Offset 0x3D590 at overlay base 80128158. SHA256(span)=44d7fcb49253cc3c461f2f7d9422941d1f893d024437b8958554dc2196571f78.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8018111C here is D_801819A4 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x902219A4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_801819A4[];
s32 func_801656E8(s32 a0, u32 a1) {
    return D_801819A4[a1 & 0x7F];
}
#endif
