/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012C044,8012C098).
 * Offset 0x3EEC at overlay base 80128158. SHA256(span)=62e260aaaf377073e90ea01d4475a730db76546249f1fabca8793fbbd61bbe8c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012c044.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C4274D4)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x1440000B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x24A56CAC)
MUSASHI_NATIVE_MIPS_WORD(0x0C004D1E)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x8C6374E0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x0804B022)
MUSASHI_NATIVE_MIPS_WORD(0x38420001)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012C044 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Prefix-fallthrough pair #4 (same shape as func_8012A328): func_8012C044 loads the hook pointer D_801274D4 with no jr and falls into the range labelled func_8012C04C, which calls it indirectly (jalr, no arg setup beyond the live registers) or runs the 80013478 default path returning (t >= D_801274E0) via slt+xori. func_8012C04C is a mid-function label with no separate file. Entry takes only arg0; the indirect callee sees the live registers, modelled by passing arg0. */

extern void *D_801274D4;
extern s32 D_801274E0;
extern u8 D_80126CAC;

extern s32 func_80013478(void *arg0, void *arg1);

s32 func_8012C044(s32 arg0) {
    s32 (*hook)(s32);
    s32 t;

    hook = (s32 (*)(s32)) D_801274D4;
    if (hook != 0) {
        return hook(arg0);
    }
    t = func_80013478((void *) (arg0 + 4), &D_80126CAC);
    return t >= D_801274E0;
}
#endif
