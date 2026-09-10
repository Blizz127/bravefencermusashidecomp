/* SC02.CD FILE_031 / ov_SC02_031 retail span [801291C0,80129220).
 * Offset 0x1068 at overlay base 80128158. SHA256(span)=a808cf811dcb87f0136d260cb84a13d7939ea9cdaef0e0970c27d4606e2506b7.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801291c0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x2610DB30)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x96020000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x0804A483)
MUSASHI_NATIVE_MIPS_WORD(0x02001021)
MUSASHI_NATIVE_MIPS_WORD(0x28620080)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF5)
MUSASHI_NATIVE_MIPS_WORD(0x26100038)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801291C0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): scans 0x80 entries
 * of 0x38 bytes from &D_8011DB30 for the first whose u16 tag is
 * 0, zeroes it via func_80016714(slot, 0x38) and returns it;
 * returns NULL (0) when full. Counter increments in the bnez
 * delay slot (always); the found pointer returns via the exit
 * jump's delay slot. */

extern u8 D_8011DB30;
extern void func_80016714(void *arg0, s32 arg1);

u8 *func_801291C0(void) {
    u8 *s0;
    s32 i;

    s0 = &D_8011DB30;
    for (i = 0; i < 0x80; i++) {
        if (*(u16 *) s0 == 0) {
            func_80016714(s0, 0x38);
            return s0;
        }
        s0 += 0x38;
    }
    return 0;
}
#endif
