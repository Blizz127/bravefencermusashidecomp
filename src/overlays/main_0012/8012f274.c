/* Overlay range [8012F274,8012F2E8) from MAIN.CD member 0012.
 * SHA256(span)=3dfc69ad580b53b6764763984806992d397abf51c95bada83ebe37a5ad49a6ce.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00028)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB1002C)
MUSASHI_NATIVE_MIPS_WORD(0x00A08821)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x0C00565E)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x8E100020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x26100034)
MUSASHI_NATIVE_MIPS_WORD(0x0C012453)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C01246B)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x27A50018)
MUSASHI_NATIVE_MIPS_WORD(0x0C012517)
MUSASHI_NATIVE_MIPS_WORD(0x27A60020)
MUSASHI_NATIVE_MIPS_WORD(0x27A40018)
MUSASHI_NATIVE_MIPS_WORD(0x0C005655)
MUSASHI_NATIVE_MIPS_WORD(0x02202821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x8FB1002C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00028)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80015954(void *, s32);          /* extern */
void func_80015978(s32, void *);          /* extern */
void func_8004914C(s32);                         /* extern */
void func_800491AC(s32);                         /* extern */
void func_8004945C(void *, void *, void *); /* extern */

void func_8012F274(void *arg0, s32 arg1) {
    s32 sp20;
    s32 sp18;
    s32 sp10;
    s32 temp_s0;

    func_80015978(arg1, &sp10);
    temp_s0 = M2C_FIELD(arg0, s32 *, 0x20) + 0x34;
    func_8004914C(temp_s0);
    func_800491AC(temp_s0);
    func_8004945C(&sp10, &sp18, &sp20);
    func_80015954(&sp18, arg1);
}
#endif
