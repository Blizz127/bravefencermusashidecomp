/* Overlay range [800CF268,800CF2BC) from MAIN.CD member 0007.
 * SHA256(span)=d267ec497c77c884e0708bd1c0a6e1de8c528cf8d25ad54b08f76ca653f0ff66.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x2404FC00)
MUSASHI_NATIVE_MIPS_WORD(0x0C033DB4)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059FC)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x2403FCC0)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800D)
MUSASHI_NATIVE_MIPS_WORD(0x8C421374)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800D)
MUSASHI_NATIVE_MIPS_WORD(0xAC23136C)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800D)
MUSASHI_NATIVE_MIPS_WORD(0xAC221374)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0007.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_800167F0();                               /* extern */
extern s32 D_800D136C;
extern s32 D_800D1374;
void func_800CF6D0(s32, s32);                              /* static */

void func_800CF268(void) {
    func_800CF6D0(-0x400, 0);
    if (func_800167F0(0) & 0xFFFF) {
        D_800D136C = -0x340;
        D_800D1374 = (s32) (D_800D1374 + 1);
    }
}
#endif
