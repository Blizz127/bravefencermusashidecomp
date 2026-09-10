/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128288,801282CC).
 * Offset 0x130 at overlay base 80128158. SHA256(span)=d3828479810b47f71c3e0d5c8d1552ad701db27782a373fb433339db4b3eece4.
 * Member-0012 source is itself a word export, so the C body comes from its
 * #else branch. Only the overlay dispatch table shifts (D_8017E618 is
 * D_8017EEA0 here, +0x888); the main-RAM counter D_800B99F6 is unchanged.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03800C)
MUSASHI_NATIVE_MIPS_WORD(0x946399F6)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x2C620009)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00031080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22EEA0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Recovered across splat's fall-through label at 0x80128290 and verified
 * byte-exact against the registered main_0012 retail blob.  The dispatch
 * table declaration is constrained only by the observed code generation. */

extern u16 D_800B99F6;
extern void (*D_8017EEA0[])(void);

void func_80128288(void) {
    if (D_800B99F6 < 9U) {
        D_8017EEA0[D_800B99F6]();
    }
}
#endif
