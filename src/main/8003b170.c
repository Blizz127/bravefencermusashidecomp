/* Main-exec range [8003B170,8003B1EC) from the SLUS executable.
 * SHA256(span)=969a81da35a3865226be9e7620a276e7def4006ee40a4158782b9e4dffaa3ed8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x8C63B548)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x14620016)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC20B548)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC20B584)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC20B588)
MUSASHI_NATIVE_MIPS_WORD(0x0C00EC53)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x8C84B0E0)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173A2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x8C84B0E0)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173B2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8006B0E0;
extern s32 D_8006B548;
extern volatile s32 D_8006B584;
extern s32 D_8006B588;
void func_8003B14C();                                 /* static */
void func_8005CE88(s32);                               /* static */
void func_8005CEC8(s32);                               /* static */
void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */

void func_8003B170(void) {
    if (D_8006B548 == 1) {
        D_8006B548 = 0;
        func_8005CF08();
        D_8006B584 = 0;
        D_8006B588 = 0;
        func_8003B14C(0);
        func_8005CE88(D_8006B0E0);
        func_8005CEC8(D_8006B0E0);
        func_8005CF18();
    }
}
#endif
