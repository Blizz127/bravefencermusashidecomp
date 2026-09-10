/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015CB94,8015CBCC).
 * Offset 0x34A3C at overlay base 80128158. SHA256(span)=ef565d9eac79845130e7b19542e982fd313e5ac048d939666e11eb7bf82faca4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015cb94.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C0554F0)
MUSASHI_NATIVE_MIPS_WORD(0xAE000170)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8015CB94 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shape: arg0->unk170 = 0 on a void*. The disassembly stores a
 * word of zero (sw $zero +0x170), so the model declares one s32 at
 * +0x170. func_80154A74 was missing from the draft's declarations
 * and is added per the repo pipeline convention. Body is m2c's
 * verbatim. */

struct data_8015CB94 {
    u8 pad[0x170];
    s32 unk170;
};

void func_801553C0();
void func_80154A74();

void func_8015CB94(struct data_8015CB94 *arg0) {
    arg0->unk170 = 0;
    func_801553C0();
    func_80154A74(arg0, 0x11);
}
#endif
