/* Overlay range [8015C030,8015C08C) from MAIN.CD member 0012.
 * SHA256(span)=f0aaa22cdf388e25ced7e01778f043ec3a353de79b43278db88fa632e5df7ecb.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x3C030008)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0xAE030238)
MUSASHI_NATIVE_MIPS_WORD(0x000211C0)
MUSASHI_NATIVE_MIPS_WORD(0xAE020234)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x000211C0)
MUSASHI_NATIVE_MIPS_WORD(0x0C055054)
MUSASHI_NATIVE_MIPS_WORD(0xAE02023C)
MUSASHI_NATIVE_MIPS_WORD(0x0C0554EA)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80146CA0(void *);                      /* static */
void func_80154150();                     /* static */
void func_801553A8(void *);                      /* static */

void func_8015C030(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x238) = 0x80000;
    M2C_FIELD(arg0, s32 *, 0x234) = (s32) (M2C_FIELD(arg1, s16 *, 0) << 7);
    M2C_FIELD(arg0, s32 *, 0x23C) = (s32) (M2C_FIELD(arg1, s16 *, 4) << 7);
    func_80154150(0x11);
    func_801553A8(arg0);
    func_80146CA0(arg0);
}
#endif
