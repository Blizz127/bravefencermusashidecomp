/* Main-exec range [80062808,80062870) from the SLUS executable.
 * SHA256(span)=66e895b6d0d6ccf524d91264f49085ec54719c78dbe8e53c90bd4a7c90ba9c09.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC3F4764)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x240A00B0)
MUSASHI_NATIVE_MIPS_WORD(0x0140F809)
MUSASHI_NATIVE_MIPS_WORD(0x24090056)
MUSASHI_NATIVE_MIPS_WORD(0x3C0A8006)
MUSASHI_NATIVE_MIPS_WORD(0x3C098006)
MUSASHI_NATIVE_MIPS_WORD(0x8C420018)
MUSASHI_NATIVE_MIPS_WORD(0x254A2870)
MUSASHI_NATIVE_MIPS_WORD(0x2529287C)
MUSASHI_NATIVE_MIPS_WORD(0x8D430000)
MUSASHI_NATIVE_MIPS_WORD(0x254A0004)
MUSASHI_NATIVE_MIPS_WORD(0x24420004)
MUSASHI_NATIVE_MIPS_WORD(0x1549FFFC)
MUSASHI_NATIVE_MIPS_WORD(0xAC43006C)
MUSASHI_NATIVE_MIPS_WORD(0x0C01738A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C1F8007)
MUSASHI_NATIVE_MIPS_WORD(0x8FFF4764)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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

extern s32 *D_80062870;
extern s32 *D_8006287C;
extern s32 D_80074764;
void func_8005CE28();                                  /* static */
void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */

void func_80062808(void) {
    s32 *var_t2;
    s32 temp_v1;
    void *var_v0;

    D_80074764 = (s32) saved_reg_ra;
    func_8005CF08();
    var_v0 = (void *(*)())0xB0()->unk18;
    var_t2 = &D_80062870;
    do {
        temp_v1 = *var_t2;
        var_t2 += 4;
        var_v0 += 4;
        var_v0->unk6C = temp_v1;
    } while (var_t2 != &D_8006287C);
    func_8005CE28();
    func_8005CF18();
}
#endif
