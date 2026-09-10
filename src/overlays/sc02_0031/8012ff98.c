/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012FF98,8013001C).
 * Offset 0x7E40 at overlay base 80128158. SHA256(span)=ee17c8110be49a1e0b26a7b3be5db54271f27642ca72b28cd78766c1fb71b361.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ff98.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E0200B4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420020)
MUSASHI_NATIVE_MIPS_WORD(0x10400012)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8E040020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800005)
MUSASHI_NATIVE_MIPS_WORD(0x3C038000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431026)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AFBA)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C352)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C678)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012FF98 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Flag word at +0xB4 (lw, & 0x20), pointer at +0x20
 * (lw, null-tested) with a word RMW at +0x4 through it (lw/sw,
 * ^ 0x80000000). The model declares s32, pointer, s32. NULL is
 * spelled 0. The ?-prototypes follow the repo pipeline convention
 * (s32 return where compared, void with word-sized params
 * otherwise). Body is m2c's verbatim. */

struct inner_8012FF98 {
    u8 pad[4];
    s32 unk4;
};

struct data_8012FF98 {
    u8 pad[0x20];
    struct inner_8012FF98 *unk20;
    u8 pad2[0x90];
    s32 unkB4;
};

s32 func_8012BEE8(void *);
void func_80130D48(void *);
void func_801319E0(void *);
void func_80131CA8(void *, s32);

void func_8012FF98(struct data_8012FF98 *arg0) {
    struct inner_8012FF98 *temp_a0;

    if (arg0->unkB4 & 0x20) {
        temp_a0 = arg0->unk20;
        if (temp_a0 != 0) {
            temp_a0->unk4 = (s32) (temp_a0->unk4 ^ 0x80000000);
        }
        if (func_8012BEE8(arg0) != 0) {
            func_80130D48(arg0);
            func_801319E0(arg0);
        }
    }
    func_80131CA8(arg0, 0x10);
}
#endif
