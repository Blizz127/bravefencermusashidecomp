/* Main-exec range [800243EC,80024448) from the SLUS executable.
 * SHA256(span)=87c50f80a168332faefbaed9864ffe6a46781277e675322f82aa669a8ad7ab85.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C830000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00031703)
MUSASHI_NATIVE_MIPS_WORD(0x30420007)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC238D88)
MUSASHI_NATIVE_MIPS_WORD(0x30630040)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xAC222B78)
MUSASHI_NATIVE_MIPS_WORD(0x10600005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C009B59)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0800910E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C009112)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80024448();                                  /* static */
void func_80026D64();                                  /* static */
extern s32 D_80078D88;
extern s32 D_800A2B78;

void func_800243EC(s32 *arg0) {
    s32 temp_v1;

    temp_v1 = *arg0;
    D_80078D88 = temp_v1;
    D_800A2B78 = (temp_v1 >> 0x1C) & 7;
    if (temp_v1 & 0x40) {
        func_80026D64();
        return;
    }
    func_80024448();
}
#endif
