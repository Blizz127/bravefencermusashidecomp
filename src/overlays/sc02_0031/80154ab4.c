/* SC02.CD FILE_031 / ov_SC02_031 retail span [80154AB4,80154AE0).
 * Offset 0x2C95C at overlay base 80128158. SHA256(span)=42f695d6622f156bc4e0025602ebab8db010889b86055946f2efa5706e7d4d6e.
 * STOP pc=80154ab4 (func_80154AB4), CPU_BOUNDARY/REFUSED; callee from leaf func_80154A74 (jal 0C0552AD).
 * Donor shape: Druthulu shared/ov/func_80154AB4.h (h_exact 51f0c666…; base=*(a0+0xCC); v1=base[a1];
 *   *(s16*)(a0+0xD6/D4)=1; *(s8*)(a0+0xD8/D9)=0; *(s32*)(a0+0xD0)=v1 in jr delay).
 * NOT MAIN10; NOT in parked PAC0 hole 8014E934…80153C8C; later SC02 text near jr_80154C24 / shared OV body.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8200CC)
MUSASHI_NATIVE_MIPS_WORD(0x00052880)
MUSASHI_NATIVE_MIPS_WORD(0x00A22821)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D6)
MUSASHI_NATIVE_MIPS_WORD(0xA48200D4)
MUSASHI_NATIVE_MIPS_WORD(0xA08000D8)
MUSASHI_NATIVE_MIPS_WORD(0xA08000D9)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8300D0)
#else
#include "psx_types.h"

void func_80154AB4(s32 arg0, s32 arg1) {
    s32 *base = *(s32 **)(arg0 + 0xCC);
    s32 v1 = base[arg1];
    *(s16 *)(arg0 + 0xD6) = 1;
    *(s16 *)(arg0 + 0xD4) = 1;
    *(s8 *)(arg0 + 0xD8) = 0;
    *(s8 *)(arg0 + 0xD9) = 0;
    *(s32 *)(arg0 + 0xD0) = v1;
}
#endif
