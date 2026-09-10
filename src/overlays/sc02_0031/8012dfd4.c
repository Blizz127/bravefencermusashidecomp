/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012DFD4,8012E014).
 * Offset 0x5E7C at overlay base 80128158. SHA256(span)=9555acfcfdc50fe02a8a586f63ae227a3886277221acd3c01f9c10538f9cd312.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012dfd4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x90820074)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B805)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804B801)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B84E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012DFD4 (main_0012.s), decoded manually from
 * raw asm (0x40 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dispatches on the
 * byte at arg0 + 0x74 (lbu, not a word load) to func_8012E014
 * (nonzero) or func_8012E138 (zero); both jals carry no new
 * arguments in delay slots. Shared func_8012E004 epilogue. */

struct obj_8012DFD4 {
    u8 pad[0x74];
    u8 unk74;
};

extern void func_8012E014(void);
extern void func_8012E138(void);

void func_8012DFD4(struct obj_8012DFD4 *arg0) {
    if (arg0->unk74 != 0) {
        func_8012E014();
    } else {
        func_8012E138();
    }
}
#endif
