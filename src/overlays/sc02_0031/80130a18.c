/* SC02.CD FILE_031 / ov_SC02_031 retail span [80130A18,80130AC4).
 * Offset 0x88C0 at overlay base 80128158. SHA256(span)=ae12e882306afe6e088d534c4bcb7afa90e64af6bc8680b4a2f8f03988e21d5d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80130a18.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x9602005C)
MUSASHI_NATIVE_MIPS_WORD(0x24050034)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0xA602005C)
MUSASHI_NATIVE_MIPS_WORD(0x1440001C)
MUSASHI_NATIVE_MIPS_WORD(0x24040011)
MUSASHI_NATIVE_MIPS_WORD(0x96020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9602000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x9602000E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x96020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20018)
MUSASHI_NATIVE_MIPS_WORD(0x9602000A)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x24420008)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x9602000E)
MUSASHI_NATIVE_MIPS_WORD(0x27A60018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04CDE1)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001C)
MUSASHI_NATIVE_MIPS_WORD(0x30426000)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x24020011)
MUSASHI_NATIVE_MIPS_WORD(0xA20200C1)
MUSASHI_NATIVE_MIPS_WORD(0x24020078)
MUSASHI_NATIVE_MIPS_WORD(0xA60200AC)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80130A18 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s0->unk5C &= ~1 (jal
 * delay slot, lands before the call); if func_80131CA8(s0, 0x34)
 * != 0 (a0 = 0x11 set in the branch delay slot, dead), done. Else
 * builds two u16 triples (second triple's last half stored in the
 * jal delay slot) and calls func_80133784(0x11, t1, t2) -- a0 is
 * the 0x11 constant left by the earlier branch delay slot, not
 * s0. If the result & 0x6000, s0->unkC1 = 0x11, s0->unkAC = 0x78.
 * Returns void. */

struct obj_80130A18 {
    u8 pad[0x6];
    u16 unk6;
    u16 pad6;
    u16 unkA;
    u16 padA;
    u16 unkE;
    u8 pad2[0x5C - 0x10];
    u16 unk5C;
    u8 pad3[0xAC - 0x5E];
    u16 unkAC;
    u8 pad4[0xC1 - 0xAE];
    u8 unkC1;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);
extern s32 func_80133784(s32 arg0, void *arg1, void *arg2);

void func_80130A18(struct obj_80130A18 *arg0) {
    u16 t1[3];
    u16 t2[3];

    arg0->unk5C &= ~1;
    if (func_80131CA8(arg0, 0x34) == 0) {
        t1[0] = arg0->unk6;
        t1[1] = arg0->unkA - 0x10;
        t1[2] = arg0->unkE;
        t2[0] = arg0->unk6;
        t2[1] = arg0->unkA + 8;
        t2[2] = arg0->unkE;
        if (func_80133784(0x11, t1, t2) & 0x6000) {
            arg0->unkC1 = 0x11;
            arg0->unkAC = 0x78;
        }
    }
}
#endif
