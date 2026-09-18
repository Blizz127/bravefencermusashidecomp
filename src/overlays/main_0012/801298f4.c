/* Overlay range [801298F4,801299C8) from MAIN.CD member 0012.
 * SHA256(span)=85a655fbd2c89b7495210a290d4d76f0cd585027849366d7dce6aa80f1e7b4c8.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00803821)
MUSASHI_NATIVE_MIPS_WORD(0x8CE3004C)
MUSASHI_NATIVE_MIPS_WORD(0x8CE20050)
MUSASHI_NATIVE_MIPS_WORD(0x94E60038)
MUSASHI_NATIVE_MIPS_WORD(0x94E5003E)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x24420004)
MUSASHI_NATIVE_MIPS_WORD(0x90440000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA4E40002)
MUSASHI_NATIVE_MIPS_WORD(0x90440000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA4E40004)
MUSASHI_NATIVE_MIPS_WORD(0x90440000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA0E40000)
MUSASHI_NATIVE_MIPS_WORD(0x90440000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xACE30008)
MUSASHI_NATIVE_MIPS_WORD(0xACE2000C)
MUSASHI_NATIVE_MIPS_WORD(0xA0E40001)
MUSASHI_NATIVE_MIPS_WORD(0x90620006)
MUSASHI_NATIVE_MIPS_WORD(0x94E3003A)
MUSASHI_NATIVE_MIPS_WORD(0x94E4003C)
MUSASHI_NATIVE_MIPS_WORD(0xA4E60014)
MUSASHI_NATIVE_MIPS_WORD(0xA4E5001A)
MUSASHI_NATIVE_MIPS_WORD(0x000211C2)
MUSASHI_NATIVE_MIPS_WORD(0x00021600)
MUSASHI_NATIVE_MIPS_WORD(0xA4E30016)
MUSASHI_NATIVE_MIPS_WORD(0x3C030800)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xA4E40018)
MUSASHI_NATIVE_MIPS_WORD(0xACE20010)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x944299F0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0xA4E0001E)
MUSASHI_NATIVE_MIPS_WORD(0xA4E0001C)
MUSASHI_NATIVE_MIPS_WORD(0xA0E20022)
MUSASHI_NATIVE_MIPS_WORD(0xA0E20021)
MUSASHI_NATIVE_MIPS_WORD(0xA0E20020)
MUSASHI_NATIVE_MIPS_WORD(0x240200A0)
MUSASHI_NATIVE_MIPS_WORD(0xA4E20028)
MUSASHI_NATIVE_MIPS_WORD(0x24020078)
MUSASHI_NATIVE_MIPS_WORD(0xA4E2002A)
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xACE70024)
MUSASHI_NATIVE_MIPS_WORD(0xA4E2002E)
MUSASHI_NATIVE_MIPS_WORD(0xA4E2002C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACE00030)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801298F4 - 53 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern unsigned short D_800B99F0;

void func_801298F4(void *arg0) {
    register u8 *a __asm__("$7");
    register s32 base4C __asm__("$3");
    register u32 b __asm__("$4");
    register u16 f38 __asm__("$6");
    register u16 f3E __asm__("$5");
    register u32 sh __asm__("$2");
    u8 *p;
    a = (u8 *) arg0;
    base4C = *(s32 *)(a + 0x4C);
    p = *(u8 **)(a + 0x50);
    f38 = *(u16 *)(a + 0x38);
    f3E = *(u16 *)(a + 0x3E);
    base4C += 8;
    p += 4;
    b = *p++; *(s16 *)(a + 0x2) = (u16) b;
    b = *p++; *(s16 *)(a + 0x4) = (u16) b;
    b = *p++; *(u8 *)(a + 0x0) = b;
    b = *p++; *(s32 *)(a + 0x8) = base4C;
    *(s32 *)(a + 0xC) = (s32) p;
    *(u8 *)(a + 0x1) = b;
    sh = ((u32)(u8) *(u8 *)(base4C + 0x6) >> 7) << 0x18;
    base4C = *(u16 *)(a + 0x3A);
    b = *(u16 *)(a + 0x3C);
    *(s16 *)(a + 0x14) = f38;
    *(s16 *)(a + 0x1A) = f3E;
    *(s16 *)(a + 0x16) = base4C;
    *(s16 *)(a + 0x18) = b;
    *(s32 *)(a + 0x10) = sh | 0x08000000;
    if (D_800B99F0 == 0) {
        *(s16 *)(a + 0x1E) = 0;
        *(s16 *)(a + 0x1C) = 0;
    }
    *(u8 *)(a + 0x22) = 0x80;
    *(u8 *)(a + 0x21) = 0x80;
    *(u8 *)(a + 0x20) = 0x80;
    *(s16 *)(a + 0x28) = 0xA0;
    *(s16 *)(a + 0x2A) = 0x78;
    *(s32 *)(a + 0x24) = (s32) a;
    *(s16 *)(a + 0x2E) = 0x1000;
    *(s16 *)(a + 0x2C) = 0x1000;
    *(s32 *)(a + 0x30) = 0;
}
#endif
