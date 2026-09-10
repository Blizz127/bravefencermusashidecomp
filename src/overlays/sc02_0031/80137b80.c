/* SC02 resident retail span [80137B80,80137BD8). Offset 0xFA28 at base 80128158.
 * SHA256(span)=8ea263b70ff00ebe9f1d145aacea2fecb66468074fd5c7ed40bfddcde663658c.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017E980->D_80185270.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x248469F0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C830000)
MUSASHI_NATIVE_MIPS_WORD(0x24020024)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC227548)
MUSASHI_NATIVE_MIPS_WORD(0x10600003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04E2F8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028018)
MUSASHI_NATIVE_MIPS_WORD(0x8C425270)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0xAC225270)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80137B80 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), 0x18
 * frame. D_80127548 = 0x24, then if (D_801269F0[0].w0 != 0)
 * func_80138BE0(&D_801269F0[0]) (a0 = base throughout, no a-reg
 * writes precede the jal), then D_80185270++ (asm order: the
 * store precedes the call). Results ignored. Slot
 * view (0x4C stride, word 0) matches func_801379FC's; 38BE0 decl
 * likewise. */

struct slot_80137B80 {
    u32 w0;
    u8 pad[0x48];
};

extern struct slot_80137B80 D_801269F0[];
extern u32 D_80127548;
extern s32 D_80185270;
extern void func_80138BE0(struct slot_80137B80 *arg0);

void func_80137B80(void) {
    D_80127548 = 0x24;
    if (D_801269F0[0].w0 != 0) {
        func_80138BE0(&D_801269F0[0]);
    }
    D_80185270++;
}
#endif
