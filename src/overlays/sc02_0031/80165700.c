/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165700,80165718).
 * Offset 0x3D5A8 at overlay base 80128158. SHA256(span)=d904087896e9435869291e7129b60b635707451c24ba62889a9b2579daf940a0.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8018113C here is D_801819C4 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5007F)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x902219C4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
extern u8 D_801819C4[];
s32 func_80165700(s32 a0, u32 a1) {
    return D_801819C4[a1 & 0x7F];
}
#endif
