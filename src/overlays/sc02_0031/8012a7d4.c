/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A7D4,8012A828).
 * Offset 0x267C at overlay base 80128158. SHA256(span)=00a50a76c5d500ff1147ab5963e770514560d73c521cd169967905359688ee59.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a7d4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x8C6351D4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C62003C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820000)
MUSASHI_NATIVE_MIPS_WORD(0x8C620040)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820002)
MUSASHI_NATIVE_MIPS_WORD(0x8C620044)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820004)
MUSASHI_NATIVE_MIPS_WORD(0x8C620048)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20000)
MUSASHI_NATIVE_MIPS_WORD(0x8C62004C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20002)
MUSASHI_NATIVE_MIPS_WORD(0x8C620050)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20004)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A7D4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Widths grounded from raw asm: six lw loads from the pointer block, six sh stores into the two out structs. */

struct src_8012A7D4 {
    u8 pad[0x3C];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
};

struct pair_8012A7D4 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern struct src_8012A7D4 *D_801151D4;

void func_8012A7D4(struct pair_8012A7D4 *arg0, struct pair_8012A7D4 *arg1) {
    arg0->unk0 = D_801151D4->unk3C;
    arg0->unk2 = D_801151D4->unk40;
    arg0->unk4 = D_801151D4->unk44;
    arg1->unk0 = D_801151D4->unk48;
    arg1->unk2 = D_801151D4->unk4C;
    arg1->unk4 = D_801151D4->unk50;
}
#endif
