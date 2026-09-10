/* Complete SC02 retail span [8014607C,80146128).
 * Ahead leaf.
 * Words from pinned SC02.CD member31 PAC0 decode (live-guest identity).
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C031F80)
MUSASHI_NATIVE_MIPS_WORD(0x346303FC)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00604021)
MUSASHI_NATIVE_MIPS_WORD(0xAD1D0000)
MUSASHI_NATIVE_MIPS_WORD(0x2508FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x0100E821)
MUSASHI_NATIVE_MIPS_WORD(0x0C05184A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC2263F8)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBD0000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C4263F8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400014)
MUSASHI_NATIVE_MIPS_WORD(0x3C031F80)
MUSASHI_NATIVE_MIPS_WORD(0x346303FC)
MUSASHI_NATIVE_MIPS_WORD(0x00604021)
MUSASHI_NATIVE_MIPS_WORD(0xAD1D0000)
MUSASHI_NATIVE_MIPS_WORD(0x2508FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x0100E821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0518D8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBD0000)
MUSASHI_NATIVE_MIPS_WORD(0x3C031F80)
MUSASHI_NATIVE_MIPS_WORD(0x346303FC)
MUSASHI_NATIVE_MIPS_WORD(0x00604021)
MUSASHI_NATIVE_MIPS_WORD(0xAD1D0000)
MUSASHI_NATIVE_MIPS_WORD(0x2508FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x0100E821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0518E8)
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


extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);
extern s32 D_801B63F8;

/* Load-bearing SP scratchpad barrier (SC02_031 site). */
void func_8014607C(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146128\n"
        "lui   $at, %%hi(D_801B63F8)\n"
        "sw    $v0, %%lo(D_801B63F8)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B63F8)\n"
        "lw    $v0, %%lo(D_801B63F8)($v0)\n"
        "nop\n"
        "beqz  $v0, .L80146114\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146360\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801463A0\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        ".L80146114:\n"
        "nop\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}
#endif
