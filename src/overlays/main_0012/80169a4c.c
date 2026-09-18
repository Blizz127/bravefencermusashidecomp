/* Overlay range [80169A4C,80169B80) from MAIN.CD member 0012.
 * SHA256(span)=6efba6a1c510da232393cdf5943bbf5a252f28003fbaf89e5d771c9170c10070.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFF80)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10074)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20078)
MUSASHI_NATIVE_MIPS_WORD(0x00A09021)
MUSASHI_NATIVE_MIPS_WORD(0x27A40068)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20028)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20020)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2002A)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x3C025000)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF007C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00070)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30022)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0002C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00024)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00014)
MUSASHI_NATIVE_MIPS_WORD(0x92230030)
MUSASHI_NATIVE_MIPS_WORD(0x27B00048)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20040)
MUSASHI_NATIVE_MIPS_WORD(0x00031082)
MUSASHI_NATIVE_MIPS_WORD(0xA3A3003E)
MUSASHI_NATIVE_MIPS_WORD(0xA3A3003A)
MUSASHI_NATIVE_MIPS_WORD(0xA3A30036)
MUSASHI_NATIVE_MIPS_WORD(0xA3A30032)
MUSASHI_NATIVE_MIPS_WORD(0xA3A2003D)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20039)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20035)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20031)
MUSASHI_NATIVE_MIPS_WORD(0xA3A2003C)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20038)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20034)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20030)
MUSASHI_NATIVE_MIPS_WORD(0x9622002C)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2006A)
MUSASHI_NATIVE_MIPS_WORD(0x0C005F71)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20068)
MUSASHI_NATIVE_MIPS_WORD(0x02402021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0123AB)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x86220006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAFA2005C)
MUSASHI_NATIVE_MIPS_WORD(0x8622000A)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20060)
MUSASHI_NATIVE_MIPS_WORD(0x8622000E)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C005DD6)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20064)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x24020007)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00020)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20028)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0002A)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00012)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x0C005DD6)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30022)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF007C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20078)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10074)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00070)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0080)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80169A4C - 77 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);

s32 func_80169A4C(s32 a0, s32 a1) {
    void *arg0 = (void *)a0;
    void *arg1 = (void *)a1;
    u8 buf[0x5C];               /* spans $sp+0x10 .. $sp+0x6B */
    u8 *p = buf + 0x38;          /* $sp+0x48, passed to first 3 calls */
    u8 v1;
    s8 v0;
    u16 t2c;
    register u8 *q __asm__("$4");    /* $sp+0x68, first call a0 */
    register s32 m5 __asm__("$3");   /* -5 -> $v1 */
    register s32 p5 __asm__("$2");   /* 5  -> $v0 */
    q = buf + 0x58;
    __asm__("" : : "r"(q));
    m5 = -5;
    __asm__("" : : "r"(m5));
    p5 = 5;
    *(s16 *)(buf + 0x18) = p5;   /* 0x28 */
    *(s16 *)(buf + 0x10) = p5;   /* 0x20 */
    *(s16 *)(buf + 0x1a) = p5;   /* 0x2A */
    *(s16 *)(buf + 0x0a) = p5;   /* 0x1A */
    *(s16 *)(buf + 0x08) = m5;   /* 0x18 */
    *(s16 *)(buf + 0x00) = m5;   /* 0x10 */
    *(s16 *)(buf + 0x12) = m5;   /* 0x22 */
    *(s16 *)(buf + 0x02) = m5;   /* 0x12 */
    *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */
    *(s16 *)(buf + 0x14) = 0;    /* 0x24 */
    *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */
    *(s16 *)(buf + 0x04) = 0;    /* 0x14 */
    v1 = *(u8 *)((u8 *)arg0 + 0x30);
    *(s32 *)(buf + 0x30) = 0x50000000;  /* 0x40 */
    v0 = (s8)(v1 >> 2);
    *(u8 *)(buf + 0x2e) = v1;     /* 0x3E */
    *(u8 *)(buf + 0x2a) = v1;     /* 0x3A */
    *(u8 *)(buf + 0x26) = v1;     /* 0x36 */
    *(u8 *)(buf + 0x22) = v1;     /* 0x32 */
    *(s8 *)(buf + 0x2d) = v0;     /* 0x3D */
    *(s8 *)(buf + 0x29) = v0;     /* 0x39 */
    *(s8 *)(buf + 0x25) = v0;     /* 0x35 */
    *(s8 *)(buf + 0x21) = v0;     /* 0x31 */
    *(s8 *)(buf + 0x2c) = v0;     /* 0x3C */
    *(s8 *)(buf + 0x28) = v0;     /* 0x38 */
    *(s8 *)(buf + 0x24) = v0;     /* 0x34 */
    *(s8 *)(buf + 0x20) = v0;     /* 0x30 */
    t2c = *(u16 *)((u8 *)arg0 + 0x2c);
    *(u16 *)(q + 0x02) = t2c;  /* 0x6A */
    *(u16 *)(q + 0x00) = t2c;  /* 0x68 */
    func_80017DC4(q, p);
    func_80048EAC(arg1, p);
    *(s32 *)(buf + 0x4c) = (s32)*(s16 *)((u8 *)arg0 + 6);   /* 0x5C */
    *(s32 *)(buf + 0x50) = (s32)*(s16 *)((u8 *)arg0 + 0xa); /* 0x60 */
    *(s32 *)(buf + 0x54) = (s32)*(s16 *)((u8 *)arg0 + 0xe); /* 0x64 */
    func_80017758(buf + 0x00, p);
    *(s16 *)(buf + 0x00) = -7;   /* 0x10 */
    *(s16 *)(buf + 0x10) = 0;    /* 0x20 */
    *(s16 *)(buf + 0x08) = 0;    /* 0x18 */
    *(s16 *)(buf + 0x18) = 7;    /* 0x28 */
    *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */
    *(s16 *)(buf + 0x02) = 0;    /* 0x12 */
    *(s16 *)(buf + 0x0a) = 7;    /* 0x1A */
    *(s16 *)(buf + 0x12) = -7;   /* 0x22 */
    func_80017758(buf + 0x00, p);
}
#endif
