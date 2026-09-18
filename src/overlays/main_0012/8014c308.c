/* Overlay range [8014C308,8014C3A4) from MAIN.CD member 0012.
 * SHA256(span)=983efa82dadac635e524d6235ac71916b2d0df65eac78365ac555f6365de4d79.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
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

/* func_8014C308 - 39 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg1 + 0x58) == 0) {
        return 0;
    }
    if (*(u16 *)((u8 *)arg1 + 0x5E) != arg2) {
        if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000) {
            return 0;
        }
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
        }
    }
    return 0;
}
#endif
