/* Overlay range [8012C2D0,8012C2E0) from MAIN.CD member 0012.
 * SHA256(span)=46ab55de2b62c0abfcc301481c157818413892f00266f9e74c6432c79bc45da5.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24630194)
MUSASHI_NATIVE_MIPS_WORD(0x0804B0BA)
MUSASHI_NATIVE_MIPS_WORD(0x2464658C)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8012C2E8();                                  /* extern */

void func_8012C2D0(void) {
    func_8012C2E8();
}
#endif
