#include "psx_types.h"

/* Byte-exact startup constructor guard/loop [800100A0,80010110).
 * The retail image retains a linker-resolved constructor count of zero, so
 * this boundary is represented as an explicit overlay instead of allowing a
 * C compiler to fold the loop away or change its frame layout. */
__asm__(
    ".set noreorder\n"
    ".globl func_800100A0\n"
    ".type func_800100A0, @function\n"
    "func_800100A0:\n"
    "lui   $t0, 0x8006\n"
    "lw    $t0, 0x2998($t0)\n"
    "addiu $sp, $sp, -0x10\n"
    "sw    $s0, 4($sp)\n"
    "sw    $s1, 8($sp)\n"
    "sw    $ra, 0xc($sp)\n"
    "bnez  $t0, .L100a0_return\n"
    "ori   $t0, $zero, 1\n"
    "lui   $at, 0x8006\n"
    "sw    $t0, 0x2998($at)\n"
    "lui   $s0, 0x8001\n"
    "addiu $s0, $s0, 0\n"
    "lui   $s1, 0\n"
    "addiu $s1, $s1, 0\n"
    "beqz  $s1, .L100a0_return\n"
    "nop\n"
    ".L100a0_loop:\n"
    "lw    $t0, 0($s0)\n"
    "addiu $s0, $s0, 4\n"
    "jalr  $t0\n"
    "addiu $s1, $s1, -1\n"
    "bnez  $s1, .L100a0_loop\n"
    "nop\n"
    ".L100a0_return:\n"
    "lw    $ra, 0xc($sp)\n"
    "lw    $s1, 8($sp)\n"
    "lw    $s0, 4($sp)\n"
    "addiu $sp, $sp, 0x10\n"
    "jr    $ra\n"
    "nop\n"
    ".size func_800100A0, .-func_800100A0\n"
    ".set reorder\n"
);

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c088006) MUSASHI_NATIVE_MIPS_WORD(0x8d082998)
MUSASHI_NATIVE_MIPS_WORD(0x27bdfff0) MUSASHI_NATIVE_MIPS_WORD(0xafb00004)
MUSASHI_NATIVE_MIPS_WORD(0xafb10008) MUSASHI_NATIVE_MIPS_WORD(0xafbf000c)
MUSASHI_NATIVE_MIPS_WORD(0x1500000f) MUSASHI_NATIVE_MIPS_WORD(0x34080001)
MUSASHI_NATIVE_MIPS_WORD(0x3c018006) MUSASHI_NATIVE_MIPS_WORD(0xac282998)
MUSASHI_NATIVE_MIPS_WORD(0x3c108001) MUSASHI_NATIVE_MIPS_WORD(0x26100000)
MUSASHI_NATIVE_MIPS_WORD(0x3c110000) MUSASHI_NATIVE_MIPS_WORD(0x26310000)
MUSASHI_NATIVE_MIPS_WORD(0x12200007) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8e080000) MUSASHI_NATIVE_MIPS_WORD(0x26100004)
MUSASHI_NATIVE_MIPS_WORD(0x0100f809) MUSASHI_NATIVE_MIPS_WORD(0x2631ffff)
MUSASHI_NATIVE_MIPS_WORD(0x1620fffb) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf000c) MUSASHI_NATIVE_MIPS_WORD(0x8fb10008)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00004) MUSASHI_NATIVE_MIPS_WORD(0x27bd0010)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
