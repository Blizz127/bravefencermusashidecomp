/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013BD34,8013BD74).
 * Offset 0x13BDC at overlay base 80128158. SHA256(span)=da5884eee5b24e7d8b8ba2ac8fdc666af1a3336e07ae64cd4b451d0d6cae5ae0.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_80185C10->D_801A5878.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0xAFC40018)
MUSASHI_NATIVE_MIPS_WORD(0x3C04801A)
MUSASHI_NATIVE_MIPS_WORD(0x24845878)
MUSASHI_NATIVE_MIPS_WORD(0x8FC50018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EF5D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void func_8013BD74(u8 *arg0, u8 *arg1);
extern u8 D_801A5878[];

/* HAND MODEL of func_8013BD34 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * fp-frame. Thin wrapper: func_8013BD74(&D_801A5878, arg0). Void:
 * v0 after the jal is ignored. */
void func_8013BD34(u8 *arg0)
{
    func_8013BD74(D_801A5878, arg0);
}
#endif
