/* Main-exec range [800141AC,800141F0) from the SLUS executable.
 * SHA256(span)=88c68ea15e7e114370141d22e28d89a0d20b00d42b69e79f0dc95c6e318b88b7.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC50008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC7000C)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0xAFA30014)
MUSASHI_NATIVE_MIPS_WORD(0xAFA50018)
MUSASHI_NATIVE_MIPS_WORD(0xAFA7001C)
MUSASHI_NATIVE_MIPS_WORD(0x0C01213B)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

typedef struct { s32 x[4]; } T16_800141AC;
extern void func_800484EC(void *, void *, void *);

/* Sibling of func_80014168 with an aligned 16-byte copy (plain
 * struct: `lw`/`sw`, no `lwl`/`swl`). Same staged source pointer
 * passed through as the third call argument. */
void func_800141AC(void *arg0, u8 *arg1) {
    u8 *s = arg1;
    T16_800141AC buf = *(T16_800141AC *)s;

    func_800484EC(arg0, &buf, s);
}
#endif
