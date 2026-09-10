#include "psx_types.h"

extern s32 func_80043450(s32);
extern void func_8004359C(void *);
extern void func_800435B4(void *);
extern void func_8004654C(void *);
extern void func_80046564(s32);
extern s32 func_8005C604(const char *);
extern void func_80043398(void);
extern void func_800433C0(void);
extern void func_800433E8(void);
extern char D_800735FC[];

/* Retail's branch layout is not reproduced by equivalent structured C, so
 * retain the source-backed instruction form for this small startup dispatcher. */
__asm__(
    ".set noreorder\n"
    ".globl func_80043300\n"
    ".type func_80043300, @function\n"
    "func_80043300:\n"
    "addiu $sp, $sp, -0x18\n"
    "sw    $s0, 0x10($sp)\n"
    "addiu $s0, $zero, 4\n"
    "sw    $ra, 0x14($sp)\n"
    ".L43300_retry:\n"
    ".word 0x0c010d14\n"
    "addiu $a0, $zero, 1\n"
    "addiu $v1, $zero, 1\n"
    ".word 0x14430011\n"
    "addiu $s0, $s0, -1\n"
    "lui   $a0, 0x8004\n"
    "addiu $a0, $a0, 0x3398\n"
    ".word 0x0c010d67\n"
    "nop\n"
    "lui   $a0, 0x8004\n"
    "addiu $a0, $a0, 0x33c0\n"
    ".word 0x0c010d6d\n"
    "nop\n"
    "lui   $a0, 0x8004\n"
    "addiu $a0, $a0, 0x33e8\n"
    ".word 0x0c011953\n"
    "nop\n"
    ".word 0x0c011959\n"
    "move  $a0, $zero\n"
    ".word 0x08010ce1\n"
    "addiu $v0, $zero, 1\n"
    ".L43300_failed:\n"
    "addiu $v0, $zero, -1\n"
    ".word 0x1602ffe9\n"
    "nop\n"
    "lui   $a0, 0x8007\n"
    "addiu $a0, $a0, 0x35fc\n"
    ".word 0x0c017181\n"
    "nop\n"
    "move  $v0, $zero\n"
    ".L43300_return_one:\n"
    "lw    $ra, 0x14($sp)\n"
    "lw    $s0, 0x10($sp)\n"
    "addiu $sp, $sp, 0x18\n"
    "jr    $ra\n"
    "nop\n"
    ".size func_80043300, .-func_80043300\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8) MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x24100004) MUSASHI_NATIVE_MIPS_WORD(0xafbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x0c010d14) MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x24030001) MUSASHI_NATIVE_MIPS_WORD(0x14430011)
MUSASHI_NATIVE_MIPS_WORD(0x2610ffff) MUSASHI_NATIVE_MIPS_WORD(0x3c048004)
MUSASHI_NATIVE_MIPS_WORD(0x24843398) MUSASHI_NATIVE_MIPS_WORD(0x0c010d67)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x3c048004)
MUSASHI_NATIVE_MIPS_WORD(0x248433c0) MUSASHI_NATIVE_MIPS_WORD(0x0c010d6d)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x3c048004)
MUSASHI_NATIVE_MIPS_WORD(0x248433e8) MUSASHI_NATIVE_MIPS_WORD(0x0c011953)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x0c011959)
MUSASHI_NATIVE_MIPS_WORD(0x00002021) MUSASHI_NATIVE_MIPS_WORD(0x08010ce1)
MUSASHI_NATIVE_MIPS_WORD(0x24020001) MUSASHI_NATIVE_MIPS_WORD(0x2402ffff)
MUSASHI_NATIVE_MIPS_WORD(0x1602ffe9) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c048007) MUSASHI_NATIVE_MIPS_WORD(0x248435fc)
MUSASHI_NATIVE_MIPS_WORD(0x0c017181) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00001021) MUSASHI_NATIVE_MIPS_WORD(0x8fbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010) MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
