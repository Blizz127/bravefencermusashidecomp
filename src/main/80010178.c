#include "psx_types.h"

/* Exact startup caller overlay [80010178,8001020C).  It deliberately ends
 * at the retail jump delay slot: the callee owns the continuation at
 * 80010214, while this body owns the saved-register frame. */
__asm__(
    ".set noreorder\n"
    ".globl func_80010178\n"
    ".type func_80010178, @function\n"
    "func_80010178:\n"
    "addiu $sp, $sp, -0x38\n"
    "sw    $ra, 0x34($sp)\n"
    "sw    $fp, 0x30($sp)\n"
    "sw    $s1, 0x2c($sp)\n"
    "sw    $s0, 0x28($sp)\n"
    "addu  $fp, $sp, $zero\n"
    ".word 0x0c004028 /* jal func_800100A0 */\n"
    "nop\n"
    "lui   $s0, %hi(D_800BA118)\n"
    "addiu $s0, $s0, %lo(D_800BA118)\n"
    "lui   $s1, %hi(D_800AF630)\n"
    "addiu $s1, $s1, %lo(D_800AF630)\n"
    "addu  $a0, $zero, $zero\n"
    ".word 0x0c010c18 /* jal func_80043060 */\n"
    "nop\n"
    "addiu $v0, $zero, 0x3e0\n"
    "lui   $at, %hi(D_80074778)\n"
    "sw    $v0, %lo(D_80074778)($at)\n"
    ".word 0x0c00507c /* jal func_800141F0 */\n"
    "nop\n"
    "addu  $a0, $zero, $zero\n"
    ".word 0x0c017f1a /* jal func_8005FC68 */\n"
    "nop\n"
    ".word 0x0c017f2e /* jal func_8005FCB8 */\n"
    "nop\n"
    ".word 0x0c006246 /* jal func_80018918 */\n"
    "nop\n"
    ".word 0x0c010cc0 /* jal func_80043300 */\n"
    "nop\n"
    "lui   $at, %hi(D_800A2B7C)\n"
    "sw    $v0, %lo(D_800A2B7C)($at)\n"
    ".word 0x0c00b23d /* jal func_8002C8F4 */\n"
    "nop\n"
    ".word 0x0c0065c7 /* jal func_8001971C */\n"
    "nop\n"
    ".L10178_continue:\n"
    ".word 0x08004085 /* j func_80010214 */\n"
    "nop\n"
    ".size func_80010178, .-func_80010178\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffc8) MUSASHI_NATIVE_MIPS_WORD(0xafbf0034)
MUSASHI_NATIVE_MIPS_WORD(0xafbe0030) MUSASHI_NATIVE_MIPS_WORD(0xafb1002c)
MUSASHI_NATIVE_MIPS_WORD(0xafb00028) MUSASHI_NATIVE_MIPS_WORD(0x03a0f021)
MUSASHI_NATIVE_MIPS_WORD(0x0c004028) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c10800c) MUSASHI_NATIVE_MIPS_WORD(0x2610a118)
MUSASHI_NATIVE_MIPS_WORD(0x3c11800b) MUSASHI_NATIVE_MIPS_WORD(0x2631f630)
MUSASHI_NATIVE_MIPS_WORD(0x00002021) MUSASHI_NATIVE_MIPS_WORD(0x0c010c18)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x240203e0)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007) MUSASHI_NATIVE_MIPS_WORD(0xac224778)
MUSASHI_NATIVE_MIPS_WORD(0x0c00507c) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002021) MUSASHI_NATIVE_MIPS_WORD(0x0c017f1a)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x0c017f2e)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x0c006246)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x0c010cc0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xac222b7c) MUSASHI_NATIVE_MIPS_WORD(0x0c00b23d)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x0c0065c7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000) MUSASHI_NATIVE_MIPS_WORD(0x08004085)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
