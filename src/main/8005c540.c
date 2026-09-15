/* Main-exec range [8005C540,8005C584) from the SLUS executable.
 * SHA256(span)=83f1261096a02f2dc5770b577c92ace41c327074183dfadcb9fbd23ab14c3a89.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x1080000E)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000C)
MUSASHI_NATIVE_MIPS_WORD(0x00801821)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24640001)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0xA0620000)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0xA0820000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
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

u8 *func_8005C540(u8 *arg0, u8 *arg1) {
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_v0;
    u8 temp_v0;
    u8 temp_v0_2;

    var_v0 = 0;
    if ((arg0 != 0) && (arg1 != 0)) {
        temp_v0 = *arg1;
        var_a1 = arg1 + 1;
        var_a0 = arg0 + 1;
        *arg0 = temp_v0;
        if (temp_v0 != 0) {
            do {
                temp_v0_2 = *var_a1;
                var_a1 += 1;
                *var_a0 = temp_v0_2;
                var_a0 += 1;
            } while (temp_v0_2 != 0);
        }
        var_v0 = arg0;
    }
    return var_v0;
}
#endif
