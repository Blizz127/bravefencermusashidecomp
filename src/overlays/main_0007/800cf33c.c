/* Overlay range [800CF33C,800CF390) from MAIN.CD member 0007.
 * SHA256(span)=a22f482be6a47ee3d769ed82a1ddfd7a712140eaf6ae76063b74a344caa7873e.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800D)
MUSASHI_NATIVE_MIPS_WORD(0x8C84136C)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C033DB4)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059FC)
MUSASHI_NATIVE_MIPS_WORD(0x24040004)
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
extern s32 D_800D136C;
extern s32 D_800D1374;
void func_800CF6D0(s32, s32);                            /* static */

void func_800CF33C(void) {
    func_800CF6D0(D_800D136C, 0);
    if (func_800167F0(4) & 0xFFFF) {
        D_800D1374 = (s32) (D_800D1374 + 1);
    }
}
#endif
