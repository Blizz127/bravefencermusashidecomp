/* Main-exec range [80014168,800141AC) from the SLUS executable.
 * SHA256(span)=e057702a93e921a02421e5ec73b0279ffe91b95496c440c5d8ca7d111918d253.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x88C20003)
MUSASHI_NATIVE_MIPS_WORD(0x98C20000)
MUSASHI_NATIVE_MIPS_WORD(0x88C30007)
MUSASHI_NATIVE_MIPS_WORD(0x98C30004)
MUSASHI_NATIVE_MIPS_WORD(0xABA20013)
MUSASHI_NATIVE_MIPS_WORD(0xBBA20010)
MUSASHI_NATIVE_MIPS_WORD(0xABA30017)
MUSASHI_NATIVE_MIPS_WORD(0xBBA30014)
MUSASHI_NATIVE_MIPS_WORD(0x0C0123EF)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

typedef struct { s32 x[2]; } __attribute__((packed)) T8_80014168;
extern void func_80048FBC(void *, void *, void *);

/* Unaligned 8-byte struct copy (`packed` forces `lwl`/`lwr` +
 * `swl`/`swr` instead of plain `lw`/`sw`). The source pointer is
 * staged into a copy because it is also passed through as the third
 * call argument — that copy is what keeps it alive past the `a1`
 * clobber for the buffer address. m2c dropped the third argument
 * and choked on the unaligned pair. */
void func_80014168(void *arg0, u8 *arg1) {
    u8 *s = arg1;
    T8_80014168 buf = *(T8_80014168 *)s;

    func_80048FBC(arg0, &buf, s);
}
#endif
