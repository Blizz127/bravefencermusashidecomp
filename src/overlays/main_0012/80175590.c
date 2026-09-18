/* Overlay range [80175590,80175624) from MAIN.CD member 0012.
 * SHA256(span)=895672119a341e9208ae72b866491331b5f6c9113feb1a06359e96b4176be4b9.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x92040005)
MUSASHI_NATIVE_MIPS_WORD(0x92020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x304300FF)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0xA2020006)
MUSASHI_NATIVE_MIPS_WORD(0x92020006)
MUSASHI_NATIVE_MIPS_WORD(0x248400FF)
MUSASHI_NATIVE_MIPS_WORD(0xA2040005)
MUSASHI_NATIVE_MIPS_WORD(0xA6030010)
MUSASHI_NATIVE_MIPS_WORD(0xA603000C)
MUSASHI_NATIVE_MIPS_WORD(0xA6020016)
MUSASHI_NATIVE_MIPS_WORD(0xA6020012)
MUSASHI_NATIVE_MIPS_WORD(0xA602000E)
MUSASHI_NATIVE_MIPS_WORD(0xA6020014)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800C)
MUSASHI_NATIVE_MIPS_WORD(0x84849A02)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D5E8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x92020005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x92020001)
MUSASHI_NATIVE_MIPS_WORD(0xA2000008)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA2020001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80175590 - 37 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_801757A0(s32 a0);
extern short D_800B9A02;

void func_80175590(void *arg0) {
    u8 temp_a0;
    register s16 temp_v1 __asm__("$3");
    s32 temp_v0;
    temp_a0 = *(u8 *)((u8 *)arg0 + 5);
    temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
    temp_v1 = -(temp_v0 & 0xFF);
    *(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
    __asm__ __volatile__("" : : : "memory");
    temp_v0 = *(u8 *)((u8 *)arg0 + 6);
    *(u8 *)((u8 *)arg0 + 5) = (u8)(temp_a0 + 0xFF);
    *(s16 *)((u8 *)arg0 + 0x10) = temp_v1;
    *(s16 *)((u8 *)arg0 + 0xC) = temp_v1;
    *(s16 *)((u8 *)arg0 + 0x16) = (s16)temp_v0;
    *(s16 *)((u8 *)arg0 + 0x12) = (s16)temp_v0;
    *(s16 *)((u8 *)arg0 + 0xE) = (s16)temp_v0;
    *(s16 *)((u8 *)arg0 + 0x14) = (s16)temp_v0;
    func_801757A0((s32)D_800B9A02);
    if (*(u8 *)((u8 *)arg0 + 5) == 0) {
        *(u8 *)((u8 *)arg0 + 8) = 0;
        *(u8 *)((u8 *)arg0 + 1) = (u8)(*(u8 *)((u8 *)arg0 + 1) + 1);
    }
}
#endif
