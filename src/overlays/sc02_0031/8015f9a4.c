/* SC02 resident retail span [8015F9A4,8015FA24). Offset 0x3784C at base 80128158.
 * SHA256(span)=2d2dedac2197135e19829a03ab000931630eac1ff468f5023c63bdd1af10cffa.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_80180A1C->D_8018730C.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x960200B8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30428000)
MUSASHI_NATIVE_MIPS_WORD(0x10400011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x96020000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22730C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0566DC)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x08057E84)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C058482)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8015F9A4 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unkB8 and arg0->unk0 on a void*, plus a callback
 * table call `*(D_8018730C + (unk0 * 4))()`. The disassembly loads both
 * members as halfwords (lhu +0xB8 and +0x0) and calls the table via
 * sll-2/addu/lw/jalr, so the model declares two u16 members and an
 * extern table of unchecked-prototype function pointers indexed by
 * unk0. No other layout is guessed. Body is m2c's verbatim. */

struct data_8015F9A4 {
    u16 unk0;
    u8 pad[0xB6];
    u16 unkB8;
};

typedef void (*callback_8015F9A4)();
extern callback_8015F9A4 D_8018730C[];

void func_80147078(void *, s32);
void func_80159B70(void *);
void func_80161208(void *);

void func_8015F9A4(struct data_8015F9A4 *arg0) {
    if (arg0->unkB8 & 0x8000) {
        D_8018730C[arg0->unk0]();
        func_80147078(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    func_80161208(arg0);
}
#endif
