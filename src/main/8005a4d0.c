/* Main-exec range [8005A4D0,8005A50C) from the SLUS executable.
 * SHA256(span)=ab7ee63bde402895e23b768f16f5bf0ed6f9b509bef8456776f1dc4f8d272736.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x00A02021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C016B4D)
MUSASHI_NATIVE_MIPS_WORD(0xA2020003)
MUSASHI_NATIVE_MIPS_WORD(0xAE020004)
MUSASHI_NATIVE_MIPS_WORD(0xAE000008)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8005AD34();
typedef struct { u8 pad[3]; u8 unk3; s32 unk4, unk8; } T;
void func_8005A4D0(T *p, void *a1) {
    p->unk3 = 2;
    p->unk4 = func_8005AD34(a1);
    p->unk8 = 0;
}
#endif
