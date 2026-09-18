/* Overlay range [80153204,8015327C) from MAIN.CD member 0012.
 * SHA256(span)=f2d1cad87bf953b957e6d6557b32d0b9b74cf4a54a8cf569c89b62b04ddc96ec.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00020)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x0C052408)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C054E00)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x14400011)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x96020088)
MUSASHI_NATIVE_MIPS_WORD(0x9603008A)
MUSASHI_NATIVE_MIPS_WORD(0x9605008C)
MUSASHI_NATIVE_MIPS_WORD(0xA6000004)
MUSASHI_NATIVE_MIPS_WORD(0xA6000008)
MUSASHI_NATIVE_MIPS_WORD(0xA600000C)
MUSASHI_NATIVE_MIPS_WORD(0xA6020006)
MUSASHI_NATIVE_MIPS_WORD(0xA603000A)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B64)
MUSASHI_NATIVE_MIPS_WORD(0xA605000E)
MUSASHI_NATIVE_MIPS_WORD(0x0C054C9F)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0566CF)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0595C6)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80153204 - 30 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80149020(s32 *a0);
extern s32 func_80153800(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);

void func_80153204(s32 *a0) {
    /* reserved stack local sets frame 0x28 (16-byte local region) */
    volatile s32 pad[4];
    func_80149020(a0);
    if (func_80153800((s32)a0) == 0) {
        *(u16 *)((u8 *)a0 + 0x4) = 0;
        *(u16 *)((u8 *)a0 + 0x8) = 0;
        *(u16 *)((u8 *)a0 + 0xC) = 0;
        *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88);
        *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A);
        *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C);
        func_80146D90((s32)a0);
        func_8015327C((s32)a0);
        func_80159B3C((s32)a0);
        func_80165718((s32)a0);
    }
}
#endif
