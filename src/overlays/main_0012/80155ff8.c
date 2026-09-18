/* Overlay range [80155FF8,80156044) from MAIN.CD member 0012.
 * SHA256(span)=5c14daaabcf08990f47fc15d7c5f8379bb91c4eac1b5d9c88775a0c1ca58ff09.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C021F80)
MUSASHI_NATIVE_MIPS_WORD(0x344203FC)
MUSASHI_NATIVE_MIPS_WORD(0x00404021)
MUSASHI_NATIVE_MIPS_WORD(0x8D090000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAD3D0000)
MUSASHI_NATIVE_MIPS_WORD(0x2529FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x0120E821)
MUSASHI_NATIVE_MIPS_WORD(0x0C055811)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBD0000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80155FF8 - 19 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80156044(int arg, int a1);

int func_80155FF8(int arg, int a1) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $ra, 16($sp)\n"
        "lui   $v0, 0x1f80\n"
        "ori   $v0, $v0, 0x03fc\n"
        "addu  $t0, $v0, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_80156044\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "nop\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}
#endif
