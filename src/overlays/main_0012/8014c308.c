/* Overlay range [8014C308,8014C3A4) from MAIN.CD member 0012.
 * SHA256(span)=983efa82dadac635e524d6235ac71916b2d0df65eac78365ac555f6365de4d79.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400022)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20058)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040001E)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x94A2005E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10460019)
MUSASHI_NATIVE_MIPS_WORD(0x34038000)
MUSASHI_NATIVE_MIPS_WORD(0x8CA2005C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042C100)
MUSASHI_NATIVE_MIPS_WORD(0x14430015)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x84A200AE)
MUSASHI_NATIVE_MIPS_WORD(0x30E3FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x1440000F)
MUSASHI_NATIVE_MIPS_WORD(0x24030009)
MUSASHI_NATIVE_MIPS_WORD(0x10C3000E)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x24030011)
MUSASHI_NATIVE_MIPS_WORD(0x10C3000B)
MUSASHI_NATIVE_MIPS_WORD(0x24030029)
MUSASHI_NATIVE_MIPS_WORD(0x10C30009)
MUSASHI_NATIVE_MIPS_WORD(0x2403000A)
MUSASHI_NATIVE_MIPS_WORD(0x10C30007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820178)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451026)
MUSASHI_NATIVE_MIPS_WORD(0x080530E7)
MUSASHI_NATIVE_MIPS_WORD(0x0002102B)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8014C308(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 var_v0;

    var_v0 = 0;
    if (M2C_FIELD(arg1, u16 *, 0) != 0) {
        var_v0 = 0;
        if (M2C_FIELD(arg1, s32 *, 0x58) != 0) {
            if (M2C_FIELD(arg1, u16 *, 0x5E) != arg2) {
                var_v0 = 0;
                if ((M2C_FIELD(arg1, s32 *, 0x5C) & 0xC100) == 0x8000) {
                    if (!(M2C_FIELD(arg1, s16 *, 0xAE) & (arg3 & 0xFFFF))) {
                        var_v0 = 1;
                        if ((arg2 != 9) && (arg2 != 0x11) && (arg2 != 0x29) && (arg2 != 0xA)) {
                            return M2C_FIELD(arg0, s32 *, 0x178) != (s32) arg1;
                        }
                        /* Duplicate return node #11. Try simplifying control flow for better match */
                        return var_v0;
                    }
                    goto block_10;
                }
                /* Duplicate return node #11. Try simplifying control flow for better match */
                return var_v0;
            }
block_10:
            var_v0 = 0;
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return var_v0;
        }
    }
    return var_v0;
}
#endif
