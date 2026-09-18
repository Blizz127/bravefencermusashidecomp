/* Overlay range [8012CB64,8012CBA4) from MAIN.CD member 0012.
 * SHA256(span)=7473d57666284aac10e2e0d3e80cb3ece9fdc897d8441a12a5066d45ec2a64c8.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84830000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA80010)
MUSASHI_NATIVE_MIPS_WORD(0x0065282A)
MUSASHI_NATIVE_MIPS_WORD(0x14A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0066182A)
MUSASHI_NATIVE_MIPS_WORD(0x10600007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84840004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0087182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0088102A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012CB64 - 16 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    v0 = 0;
    v1 = *(s16*)arg0;
    if (((arg1 <= v1) && (v1 < arg2)) && (arg3 <= *(s16*)(arg0 + 4))) {
        v0 = *(s16*)(arg0 + 4) < arg4;
    }
    return v0;
}
#endif
