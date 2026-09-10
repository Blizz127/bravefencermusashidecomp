/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F214,8012F274).
 * Offset 0x70BC at overlay base 80128158. SHA256(span)=d540c6a437ee2771b23a3b8980f74b631ad2af0e5c8471216a64ce35db20a952.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f214.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00018)
MUSASHI_NATIVE_MIPS_WORD(0x00A08021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20020)
MUSASHI_NATIVE_MIPS_WORD(0xAFB1001C)
MUSASHI_NATIVE_MIPS_WORD(0x8C910020)
MUSASHI_NATIVE_MIPS_WORD(0x00C09021)
MUSASHI_NATIVE_MIPS_WORD(0x26310034)
MUSASHI_NATIVE_MIPS_WORD(0x0C012453)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x0C01246B)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x02402821)
MUSASHI_NATIVE_MIPS_WORD(0x0C012517)
MUSASHI_NATIVE_MIPS_WORD(0x27A60010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20020)
MUSASHI_NATIVE_MIPS_WORD(0x8FB1001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F214 (main_0012.s), decoded manually from
 * raw asm (0x60 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): t = unk20 + 0x34;
 * calls 8004914C(t) (t set in the jal delay slot), 800491AC(t),
 * then 8004945C(arg1, arg2, buf) with an 8-byte stack buffer.
 * Same tail shape as func_8012F14C with the GTE-base override. */

struct obj_8012F214 {
    u8 pad[0x20];
    void *unk20;
};

extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern void func_8004945C(void *arg0, void *arg1, void *arg2);

void func_8012F214(struct obj_8012F214 *arg0, void *arg1, void *arg2) {
    u8 *t;
    u8 buf[8];

    t = (u8 *) arg0->unk20 + 0x34;
    func_8004914C(t);
    func_800491AC(t);
    func_8004945C(arg1, arg2, buf);
}
#endif
