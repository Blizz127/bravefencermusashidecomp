/* Overlay range [80146F58,80146FC4) from MAIN.CD member 0012.
 * SHA256(span)=651d802d8df86aedc6ff0f05cddf4b3562889bd5f54d1d498110d76ab957cec3.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFB8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00038)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20040)
MUSASHI_NATIVE_MIPS_WORD(0x00A09021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0044)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A9A3)
MUSASHI_NATIVE_MIPS_WORD(0xAFB1003C)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A9D6)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x27B10018)
MUSASHI_NATIVE_MIPS_WORD(0x02202821)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x0C0125E3)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00014)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0123EF)
MUSASHI_NATIVE_MIPS_WORD(0x02403021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0044)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20040)
MUSASHI_NATIVE_MIPS_WORD(0x8FB1003C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00038)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0048)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80048FBC(void *, s32, s32);                       /* extern */
void func_8004978C(s16 *, void *);                        /* extern */
s16 func_8012A68C();                                /* static */
s16 func_8012A758();                                /* static */

void func_80146F58(s32 arg0, s32 arg1) {
    s32 sp18;
    s16 sp14;
    s16 sp12;
    s16 sp10;

    sp10 = func_8012A68C();
    sp12 = func_8012A758();
    sp14 = 0;
    func_8004978C(&sp10, &sp18);
    func_80048FBC(&sp18, arg0, arg1);
}
#endif
