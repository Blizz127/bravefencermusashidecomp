/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A79C,8012A7D4).
 * Offset 0x2644 at overlay base 80128158. SHA256(span)=5beb3f8c1cde6fef1179313c3248a3f7630c132e8446c96225f32af9d69c63a5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a79c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x84860000)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0x84830004)
MUSASHI_NATIVE_MIPS_WORD(0x84A50004)
MUSASHI_NATIVE_MIPS_WORD(0x00C22023)
MUSASHI_NATIVE_MIPS_WORD(0x0C0133FB)
MUSASHI_NATIVE_MIPS_WORD(0x00652823)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A79C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. NOTE: func_8004CFEC is declared (s32, s32): func_8012B77C
 * passes full 32-bit differences as the second argument, so the
 * parameter is 32 bits wide even where only 16 arrive (same codegen). CORRECTED: raw asm shows func_8004CFEC takes two args (func_8012A6D0 never sets $a2 before the call); the $a2 load is register allocation for the temp, not a third argument. */

extern s16 func_8004CFEC(s32 arg0, s32 arg1);

struct pt_8012A79C {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

s16 func_8012A79C(struct pt_8012A79C *arg0, struct pt_8012A79C *arg1) {
    s16 temp_a2;

    temp_a2 = arg0->unk0;
    return func_8004CFEC(temp_a2 - arg1->unk0, arg0->unk4 - arg1->unk4);
}
#endif
