/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E370,8013E410).
 * Offset 0x16218 at overlay base 80128158. SHA256(span)=c46abf4ff5b405246a0dae578d33039456a0e0fafc5c052ce8e6e630f81fdc94.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e370.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x8E1074CC)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x1200001A)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x96020006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400016)
MUSASHI_NATIVE_MIPS_WORD(0x26120006)
MUSASHI_NATIVE_MIPS_WORD(0x96420004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30428000)
MUSASHI_NATIVE_MIPS_WORD(0x1440000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F904)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00408821)
MUSASHI_NATIVE_MIPS_WORD(0x1220000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F912)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B1C9)
MUSASHI_NATIVE_MIPS_WORD(0x02202821)
MUSASHI_NATIVE_MIPS_WORD(0x26520014)
MUSASHI_NATIVE_MIPS_WORD(0x96420000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x26100014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

struct src_8012C724;
extern u8 *func_8013E410(void);
extern s32 func_8013E448(u8 *arg0);
extern void func_8012C724(struct src_8012C724 *arg0, void *arg1);
extern u8 *D_801274CC;

/* HAND MODEL of func_8013E370 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), O2 frame.
 * Walks the D_801274CC 0x14-stride record list while each
 * record's +6 halfword stays nonzero: records whose +10 halfword
 * carries 0x8000 are skipped, otherwise a free slot from
 * func_8013E410 (NULL slot aborts the whole walk) is paired with
 * the record through func_8013E448, and a nonzero dispatch result
 * additionally runs func_8012C724(record, slot) (struct decl owned
 * by staging/hand/func_8012C724.c, forward-declared here). Void:
 * no result is produced. */
void func_8013E370(void)
{
    u8 *s0;
    u8 *s2;
    u8 *s1;

    s0 = D_801274CC;
    if (s0 == 0) {
        return;
    }
    s2 = s0 + 6;
    if (*(u16 *)s2 == 0) {
        return;
    }
    do {
        if (!(*(u16 *)(s2 + 4) & 0x8000)) {
            s1 = func_8013E410();
            if (s1 == 0) {
                return;
            }
            if (func_8013E448(s0) != 0) {
                func_8012C724((struct src_8012C724 *)s0, s1);
            }
        }
        s2 += 0x14;
        s0 += 0x14;
    } while (*(u16 *)s2 != 0);
}
#endif
