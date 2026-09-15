/* Main-exec range [8004948C,800494C4) from the SLUS executable.
 * SHA256(span)=995d98a5ee25019aee6603a6a691b0e7ca00fafc6161a86532535e2b7e8f4ed5.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x84830002)
MUSASHI_NATIVE_MIPS_WORD(0x48824800)
MUSASHI_NATIVE_MIPS_WORD(0x48835000)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA80428)
MUSASHI_NATIVE_MIPS_WORD(0x48024800)
MUSASHI_NATIVE_MIPS_WORD(0x48035000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0004)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A30002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004948C\n"
    ".type func_8004948C, @function\n"
    "func_8004948C:\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x2($a0)\n"
    "mtc2 $v0, $9\n"
    "mtc2 $v1, $10\n"
    "lwc2 $11, 0x4($a0)\n"
    "nop\n"
    ".word 0x4AA80428\n"
    "mfc2 $v0, $9\n"
    "mfc2 $v1, $10\n"
    "swc2 $11, 0x4($a1)\n"
    "sh $v0, 0x0($a1)\n"
    "sh $v1, 0x2($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_8004948C, .-func_8004948C\n"
    ".set reorder\n"
);
#endif
