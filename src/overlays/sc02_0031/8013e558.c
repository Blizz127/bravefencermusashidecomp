/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E558,8013E588).
 * Offset 0x16400 at overlay base 80128158. SHA256(span)=d28a3284efc8f47ce717962f75d073e0cc8d17b07285599354313dd82f884459.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e558.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C034928)
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0x3C028014)
MUSASHI_NATIVE_MIPS_WORD(0x24421788)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC22DB24)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void func_800D24A0();
extern void func_80141788();
extern void (*D_8011DB24)();

/* HAND MODEL of func_8013E558 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 frame.
 * Calls func_800D24A0(2) (a0 rides the jal delay slot;
 * unprototyped decl: no further arg facts), then vectors the
 * D_8011DB24 callback slot to func_80141788 (unspecified-args
 * funcptr: the slot also takes func_80141874 in func_8013E588, so
 * no firmer signature is claimed). Void: v0 after the jal is
 * ignored. */
void func_8013E558(void)
{
    func_800D24A0(2);
    D_8011DB24 = func_80141788;
}
#endif
