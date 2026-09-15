/* Overlay range [800CF0F4,800CF148) from MAIN.CD member 0007.
 * SHA256(span)=f095434f9613bd143548d6534ed420b5acb62ab1f87b68230777d4c62ca51ad8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800D)
MUSASHI_NATIVE_MIPS_WORD(0x8CA51368)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C033D02)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059FC)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800D)
MUSASHI_NATIVE_MIPS_WORD(0x8C421374)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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
extern s32 D_800D1368;
extern s32 D_800D1374;
void func_800CF408(s32, s32);                            /* static */

void func_800CF0F4(void) {
    func_800CF408(0, D_800D1368);
    if (func_800167F0(0) & 0xFFFF) {
        D_800D1374 = (s32) (D_800D1374 + 1);
    }
}
#endif
