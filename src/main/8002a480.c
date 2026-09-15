/* Main-exec range [8002A480,8002A4B8) from the SLUS executable.
 * SHA256(span)=da9e72e94af95182f859b4627351b0100cfd5bae75cc3d6d3cb2de5a346c7a74.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428EEC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24430001)
MUSASHI_NATIVE_MIPS_WORD(0x2862001F)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2403001E)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC238EEC)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC208EF0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078EEC;
extern s32 D_80078EF0;

void func_8002A480(void) {
    s32 var_v1;

    var_v1 = D_80078EEC + 1;
    if (var_v1 >= 0x1F) {
        var_v1 = 0x1E;
    }
    D_80078EEC = var_v1;
    D_80078EF0 = 0;
}
#endif
