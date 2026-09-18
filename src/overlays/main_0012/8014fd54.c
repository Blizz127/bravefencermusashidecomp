/* Overlay range [8014FD54,8014FDF4) from MAIN.CD member 0012.
 * SHA256(span)=af63cdd965d25481ff9443812a6f0a28d266d5c7b14b74dec1bbe07477e6bc2f.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x24020007)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00012)
MUSASHI_NATIVE_MIPS_WORD(0x0C0524A4)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x27B00018)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x02003021)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFE8)
MUSASHI_NATIVE_MIPS_WORD(0xA7A00018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001A)
MUSASHI_NATIVE_MIPS_WORD(0x0C0524A4)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001C)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04CDE1)
MUSASHI_NATIVE_MIPS_WORD(0x02003021)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x10600008)
MUSASHI_NATIVE_MIPS_WORD(0x30638000)
MUSASHI_NATIVE_MIPS_WORD(0x10600007)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x93A2001E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x38420015)
MUSASHI_NATIVE_MIPS_WORD(0x08053F78)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014FD54 - 40 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80149290(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    register int result __asm__("$2");
    buf1[0] = 0;
    buf1[1] = 0;
    buf1[2] = 7;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf1, buf1);
    buf2[0] = 0;
    buf2[1] = 0;
    buf2[2] = (short)0xffe8;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2);
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
}
#endif
