/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012AD64,8012AD6C).
 * Offset 0x2C0C at overlay base 80128158. SHA256(span)=8a02e31281d9f26d2aba6661e7ee809cf475aea3e1dc2f9414d0f3223fd7bcc8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ad64.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4850034)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD64 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Store width grounded from raw asm (sh at 0x34). */

struct obj_8012AD64 {
    u8 pad[0x34];
    s16 unk34;
};

void func_8012AD64(struct obj_8012AD64 *arg0, s16 arg1) {
    arg0->unk34 = arg1;
}
#endif
