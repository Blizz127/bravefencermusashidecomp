/* Overlay range [80141B90,80141C04) from MAIN.CD member 0012.
 * SHA256(span)=cf1a2a2bd684069512140c012eb258f575344f7e3f22df5e56a9f7134b55b461.
 * Word export for the native seam; the body below is a
 * verified MATCH (29/29 words at 0x80141B90, -O2). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x94429A02)
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C2251C8)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xAC2251D0)
MUSASHI_NATIVE_MIPS_WORD(0x0C04FEBE)
MUSASHI_NATIVE_MIPS_WORD(0x24050003)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x94425116)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x94425112)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0209A15)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA4225112)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* Verified byte-exact against retail by tools/match_function.py
 * (29/29 words at 0x80141B90). Two findings: the index has no *4
 * (plain s32-indexed load), and retail's 32-byte frame needs an
 * address-taken dead local — `(void) &du` emits nothing but reserves
 * the 8 bytes (verified: no $sp traffic either side). That construct
 * is a codegen constraint, not a claim about the original source,
 * which may have held a leftover or debug local there. Other types
 * and signatures are whatever reproduces the bytes; they are not
 * evidence of the original declaration. */

void func_8013FAF8(s32, s32);                              /* static */
extern u16 D_800B9A02;
extern s8 D_800B9A15;
extern u16 D_80115112;
extern u16 D_80115116;
extern s32 *D_801151C8;
extern s32 D_801151D0;

void func_80141B90(void) {
    s32 du;
    (void) &du;
    D_801151D0 = *(&D_801151C8 + D_800B9A02);
    func_8013FAF8(2, 3);
    if (D_80115116 == 0) {
        D_800B9A15 = 0;
        D_80115112 += 1;
    }
}
#endif
