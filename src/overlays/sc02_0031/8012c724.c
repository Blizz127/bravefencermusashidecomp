/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012C724,8012C750).
 * Offset 0x45CC at overlay base 80128158. SHA256(span)=022c49ec64edef13d079e20c0032788d19412b8a544a826f5cdfb299c543d749.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012c724.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x34428000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B224)
MUSASHI_NATIVE_MIPS_WORD(0xA482000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012C724 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. func_8012C890 is declared here as an s32 value-flow view (opaque word in, opaque word out); the true (src, dst, ctx) prototype lives in staging/hand/func_8012C890.c. Takes two arguments (m2c missed the second): the destination pointer passes through untouched in a1 while a2 is explicitly zeroed, so the context is NULL. */

struct src_8012C724 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    s32 unk10;
};

extern s32 func_8012C890(void *arg0, void *arg1, void *arg2);

void func_8012C724(struct src_8012C724 *arg0, void *arg1) {
    arg0->unkA |= 0x8000;
    func_8012C890(arg0, arg1, 0);
}
#endif
