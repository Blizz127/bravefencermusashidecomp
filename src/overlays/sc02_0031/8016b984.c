/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016B984,8016B9F8).
 * Offset 0x4382C at overlay base 80128158. SHA256(span)=029429cd548923f4dd5875db5df332720c3e28fc1d64903317ac7af088cd3233.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016b984.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E040010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x8E040014)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x8E040018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B0F)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8016B984 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk10/unk14/unk18 on a void*, each passed as an
 * s32 argument. The disassembly loads all three as words straight
 * into $a0 (lw +0x10/+0x14/+0x18), so the model declares three s32
 * members. Callee declarations follow the repo pipeline convention.
 * Body is m2c's verbatim. */

struct data_8016B984 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_80146C3C(void *);
void func_80016714();

void func_8016B984(struct data_8016B984 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = arg0->unk10;
    if (temp_a0 != 0) {
        func_80016714(temp_a0, 0x38);
    }
    temp_a0_2 = arg0->unk14;
    if (temp_a0_2 != 0) {
        func_80016714(temp_a0_2, 0x38);
    }
    temp_a0_3 = arg0->unk18;
    if (temp_a0_3 != 0) {
        func_80016714(temp_a0_3, 0x38);
    }
    func_80146C3C(arg0);
}
#endif
