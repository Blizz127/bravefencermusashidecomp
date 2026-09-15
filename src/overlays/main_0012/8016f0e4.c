/* Overlay range [8016F0E4,8016F14C) from MAIN.CD member 0012.
 * SHA256(span)=3d9cda4c88f1d26aca6651c7fee5bfbf51f735aa6d46cc4adfc6e952bafbd37e.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAE0001F8)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C65B)
MUSASHI_NATIVE_MIPS_WORD(0xAE0001FC)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C18)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05446A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x94428EB4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0229A17)
MUSASHI_NATIVE_MIPS_WORD(0x0C05218D)
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

void func_80147060(void *);                      /* static */
void func_80148634(void *);                      /* static */
void func_801511A8(void *);                      /* static */
void func_8017196C();                     /* static */
extern u16 D_80078EB4;
extern s8 D_800B9A17;

void func_8016F0E4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1F8) = 0;
    M2C_FIELD(arg0, s32 *, 0x1FC) = 0;
    func_8017196C(0);
    func_80147060(arg0);
    func_801511A8(arg0);
    if (D_80078EB4 != 0) {
        D_800B9A17 = 1;
    }
    func_80148634(arg0);
}
#endif
