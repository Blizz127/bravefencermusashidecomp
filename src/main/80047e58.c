/* PSY-Q GTE helper [80047E58,80047EC8) from the SLUS executable.
 * SHA256(span)=7a3aef343a090d6f03449b72c27c80a81e2258c965c4be5c155fead336b8a281.
 * Word export only (no registry entry): the native seam needs the retail
 * instruction stream so the guest can execute the helper it calls.
 * No C match claim yet.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0008)
MUSASHI_NATIVE_MIPS_WORD(0x10000011)
MUSASHI_NATIVE_MIPS_WORD(0x03E03821)
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E03821)
MUSASHI_NATIVE_MIPS_WORD(0x0C011FB2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00E0F821)
MUSASHI_NATIVE_MIPS_WORD(0xACA80000)
MUSASHI_NATIVE_MIPS_WORD(0xACA90004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACAA0008)
MUSASHI_NATIVE_MIPS_WORD(0x84880000)
MUSASHI_NATIVE_MIPS_WORD(0x84890002)
MUSASHI_NATIVE_MIPS_WORD(0x848A0004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E03821)
MUSASHI_NATIVE_MIPS_WORD(0x0C011FB2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00E0F821)
MUSASHI_NATIVE_MIPS_WORD(0xA4A80000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A90002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4AA0004)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80047EC8();                                 /* static */

void func_80047E58(void *arg0) {
    func_80047EC8(saved_reg_ra);
    *M2C_ERROR(/* Read from unset register $a1 */) = M2C_ERROR(/* Read from unset register $t0 */);
    M2C_ERROR(/* Read from unset register $a1 */)->unk2 = (s16) M2C_ERROR(/* Read from unset register $t1 */);
    M2C_ERROR(/* Read from unset register $a1 */)->unk4 = (s16) M2C_ERROR(/* Read from unset register $t2 */);
}
#endif
