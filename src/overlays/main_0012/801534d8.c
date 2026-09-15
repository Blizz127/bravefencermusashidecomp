/* Overlay range [801534D8,80153550) from MAIN.CD member 0012.
 * SHA256(span)=c88971cee32bb8dbd5b7314b5a96cbeb36dd367758d76edb9caf6ea3872f976a.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
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
MUSASHI_NATIVE_MIPS_WORD(0x0C054D54)
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

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80146D90(void *, u16);                 /* static */
void func_80149020();                            /* static */
void func_80153550(void *);                      /* static */
s32 func_80153800(void *);                          /* static */
void func_80159B3C(void *);                      /* static */
void func_80165718(void *);                      /* static */

void func_801534D8(void *arg0) {
    u16 temp_a1;

    func_80149020();
    if (func_80153800(arg0) == 0) {
        temp_a1 = M2C_FIELD(arg0, u16 *, 0x8C);
        M2C_FIELD(arg0, s16 *, 4) = 0;
        M2C_FIELD(arg0, s16 *, 8) = 0;
        M2C_FIELD(arg0, s16 *, 0xC) = 0;
        M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0x88);
        M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x8A);
        M2C_FIELD(arg0, u16 *, 0xE) = temp_a1;
        func_80146D90(arg0, temp_a1);
        func_80153550(arg0);
        func_80159B3C(arg0);
        func_80165718(arg0);
    }
}
#endif
