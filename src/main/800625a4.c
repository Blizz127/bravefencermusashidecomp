/* Main-exec range [800625A4,800625DC) from the SLUS executable.
 * SHA256(span)=fe7161b5f67ac2bfadaf062a8451fea68f1b751b34a79666f8c296ae53569daf.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C058008)
MUSASHI_NATIVE_MIPS_WORD(0x24A58D08)
MUSASHI_NATIVE_MIPS_WORD(0x0C01785E)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */
void func_8005E178(s32, void *);                            /* static */
extern s32 *D_80078D08;

s32 func_800625A4(void) {
    func_8005CF08();
    func_8005E178(1, &D_80078D08);
    func_8005CF18();
    return 1;
}
#endif
