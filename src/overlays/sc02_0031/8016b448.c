/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016B448,8016B4BC).
 * Offset 0x432F0 at overlay base 80128158. SHA256(span)=0832a7dd988296e5d7f677adcdc51afd242a03d0705bdb92477f24bd0e505be4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016b448.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10024)
MUSASHI_NATIVE_MIPS_WORD(0x00A08821)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x24846B58)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x0C053014)
MUSASHI_NATIVE_MIPS_WORD(0x2405001E)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x2404001E)
MUSASHI_NATIVE_MIPS_WORD(0x0C05AE61)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x2404001E)
MUSASHI_NATIVE_MIPS_WORD(0x8606007C)
MUSASHI_NATIVE_MIPS_WORD(0x8607007E)
MUSASHI_NATIVE_MIPS_WORD(0x86020080)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0xAFA00018)
MUSASHI_NATIVE_MIPS_WORD(0x0C051A9B)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0030)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8016B448 (main_0012.s), decoded manually from
 * raw asm (0x74 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): v0 =
 * 8014C050(&D_80126B58, 0x1E); when nonzero calls 8016B984(v0)
 * (v0 set in the jal delay slot). Then 80146A6C(0x1E, obj, lh
 * +0x7C, lh +0x7E, lh +0x80, arg1, 0): the last three ride stack
 * slots 0x10 (in the jal delay slot), 0x14 (incoming arg1 saved
 * early), 0x18 (zero). Same 7-arg callee as func_8016AA50's
 * tail, which passes (0x1D, ...) with (0, arg1)/(7, 0). */

struct obj_8016B448 {
    u8 pad[0x7C];
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
};

extern u8 D_80126B58;
extern s32 func_8014C050(void *arg0, s32 arg1);
extern void func_8016B984(s32 arg0);
extern void func_80146A6C(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_8016B448(void *arg0, s32 arg1) {
    struct obj_8016B448 *o;
    s32 v0;

    o = (struct obj_8016B448 *) arg0;
    v0 = func_8014C050(&D_80126B58, 0x1E);
    if (v0 != 0) {
        func_8016B984(v0);
    }
    func_80146A6C(0x1E, arg0, o->unk7C, o->unk7E, o->unk80, arg1, 0);
}
#endif
