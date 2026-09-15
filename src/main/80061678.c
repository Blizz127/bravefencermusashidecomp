/* Main-exec range [80061678,800616D0) from the SLUS executable.
 * SHA256(span)=90bde11fd2119eedede462c5c96af44942d16459b763c49ca18804cc40d24f34.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x10820011)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x28820002)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1080000D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x080185B2)
MUSASHI_NATIVE_MIPS_WORD(0x34838000)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x10820005)
MUSASHI_NATIVE_MIPS_WORD(0x24020004)
MUSASHI_NATIVE_MIPS_WORD(0x10820006)
MUSASHI_NATIVE_MIPS_WORD(0x24030003)
MUSASHI_NATIVE_MIPS_WORD(0x080185B2)
MUSASHI_NATIVE_MIPS_WORD(0x34838000)
MUSASHI_NATIVE_MIPS_WORD(0x080185B2)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x24030002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80061678(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (arg0 != 1) {
        if (arg0 < 2) {
            if (arg0 != 0) {
                var_v1 = arg0 | 0x8000;
            }
        } else if (arg0 != 2) {
            var_v1 = 3;
            if (arg0 != 4) {
                var_v1 = arg0 | 0x8000;
            }
        } else {
            var_v1 = 1;
        }
    } else {
        var_v1 = 2;
    }
    return var_v1;
}
#endif
