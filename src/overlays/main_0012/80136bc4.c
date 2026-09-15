/* Overlay range [80136BC4,80136C1C) from MAIN.CD member 0012.
 * SHA256(span)=480288f84195d8170e11a9a7aa663f5f5962f32e49df56cee7e6a54ecc30ea1a.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830008)
MUSASHI_NATIVE_MIPS_WORD(0x24020020)
MUSASHI_NATIVE_MIPS_WORD(0x14620011)
MUSASHI_NATIVE_MIPS_WORD(0x24830020)
MUSASHI_NATIVE_MIPS_WORD(0x8C82000C)
MUSASHI_NATIVE_MIPS_WORD(0xAC830008)
MUSASHI_NATIVE_MIPS_WORD(0x8C830014)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC82000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C820010)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0xAC830014)
MUSASHI_NATIVE_MIPS_WORD(0x8C83001C)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820018)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0xAC83001C)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820018)
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

void func_80136BC4(void *arg0) {
    if (arg0->unk8 == (void *)0x20) {
        arg0->unk8 = (void *) (arg0 + 0x20);
        arg0->unkC = (void *) (arg0->unkC + arg0);
        arg0->unk14 = (void *) (arg0->unk14 + arg0);
        arg0->unk10 = (void *) (arg0->unk10 + arg0);
        arg0->unk1C = (void *) (arg0->unk1C + arg0);
        arg0->unk18 = (void *) (arg0->unk18 + arg0);
    }
}
#endif
