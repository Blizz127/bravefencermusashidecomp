/* Main-exec range [80051D78,80051DC8) from the SLUS executable.
 * SHA256(span)=b096f04a8aded97409fb838a52099375501261af496b816374e6c520a19b30b8.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C8B000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C8C0010)
MUSASHI_NATIVE_MIPS_WORD(0x48C80000)
MUSASHI_NATIVE_MIPS_WORD(0x48C90800)
MUSASHI_NATIVE_MIPS_WORD(0x48CA1000)
MUSASHI_NATIVE_MIPS_WORD(0x48CB1800)
MUSASHI_NATIVE_MIPS_WORD(0x48CC2000)
MUSASHI_NATIVE_MIPS_WORD(0xC8A00000)
MUSASHI_NATIVE_MIPS_WORD(0xC8A10004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A486012)
MUSASHI_NATIVE_MIPS_WORD(0xE8D90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8DA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8DB0008)
MUSASHI_NATIVE_MIPS_WORD(0x00C01021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80051D78\n"
    ".type func_80051D78, @function\n"
    "func_80051D78:\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "lw $t3, 0xC($a0)\n"
    "lw $t4, 0x10($a0)\n"
    "ctc2 $t0, $0\n"
    "ctc2 $t1, $1\n"
    "ctc2 $t2, $2\n"
    "ctc2 $t3, $3\n"
    "ctc2 $t4, $4\n"
    "lwc2 $0, 0x0($a1)\n"
    "lwc2 $1, 0x4($a1)\n"
    "nop\n"
    ".word 0x4A486012\n"
    "swc2 $25, 0x0($a2)\n"
    "swc2 $26, 0x4($a2)\n"
    "swc2 $27, 0x8($a2)\n"
    "addu $v0, $a2, $zero\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80051D78, .-func_80051D78\n"
    ".set reorder\n"
);
#endif
