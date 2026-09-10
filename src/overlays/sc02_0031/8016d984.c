/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016D984,8016DA04).
 * Offset 0x4582C at overlay base 80128158. SHA256(span)=3660335be10c1421f43bb7cb0a5770d9c30c015b240feea734876504276a1d70.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016d984.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E02001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0xAE02001C)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B0F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805B67C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0348B9)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8E020010)
MUSASHI_NATIVE_MIPS_WORD(0x8E030014)
MUSASHI_NATIVE_MIPS_WORD(0x00022103)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00032103)
MUSASHI_NATIVE_MIPS_WORD(0xAE020010)
MUSASHI_NATIVE_MIPS_WORD(0x8E020018)
MUSASHI_NATIVE_MIPS_WORD(0x00641823)
MUSASHI_NATIVE_MIPS_WORD(0xAE030014)
MUSASHI_NATIVE_MIPS_WORD(0x00021903)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAE020018)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8016D984 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk1C/unk10/unk14/unk18 on a void*. The disassembly
 * accesses all four as words (lw/sw at +0x10/+0x14/+0x18/+0x1C), so the
 * model declares exactly those four s32 members. Bytes below +0x10 are
 * untouched by this function and left as padding; no other layout is
 * guessed. Control flow and temporaries are m2c's verbatim. */

struct data_8016D984 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

void func_80146C3C();
void func_800D22E4(void *);

void func_8016D984(struct data_8016D984 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    temp_v0 = arg0->unk1C - 1;
    arg0->unk1C = temp_v0;
    if (temp_v0 == 0) {
        func_80146C3C();
        return;
    }
    func_800D22E4(arg0);
    temp_v0_2 = arg0->unk10;
    temp_v1 = arg0->unk14;
    arg0->unk10 = (s32) (temp_v0_2 - (temp_v0_2 >> 4));
    temp_v0_3 = arg0->unk18;
    arg0->unk14 = (s32) (temp_v1 - (temp_v1 >> 4));
    arg0->unk18 = (s32) (temp_v0_3 - (temp_v0_3 >> 4));
}
#endif
