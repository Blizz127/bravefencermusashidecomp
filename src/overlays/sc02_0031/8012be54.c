/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012BE54,8012BE98).
 * Offset 0x3CFC at overlay base 80128158. SHA256(span)=ab0d85af5ecbe6858488550d192613e04d4f3545c3c9dca1b6807ea3cfeff5a1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012be54.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x94426B5E)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x94636B62)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x94A56B66)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A50014)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AFA6)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BE54 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. NOTE: func_8004CFEC is declared (s32, s32) per
 * the func_8012B77C evidence. CORRECTED: the BE6C range calls func_8012BE98 (not 800132BC directly) with the caller pointer passed through in a0 and the u16 triple as the second argument; func_8012BE6C is a mid-function label with no separate file. Entry takes only the pointer; a1 is clobbered by the prefix loads. */

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

struct triple_8012BE54 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

void func_8012BE98(void *arg0, struct triple_8012BE54 *arg1);

void func_8012BE54(void *arg0) {
    struct triple_8012BE54 t;

    t.unk0 = D_80126B5E;
    t.unk2 = D_80126B62;
    t.unk4 = D_80126B66;
    func_8012BE98(arg0, &t);
}
#endif
