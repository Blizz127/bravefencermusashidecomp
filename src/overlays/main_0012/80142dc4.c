/* Overlay range [80142DC4,80142E38) from MAIN.CD member 0012.
 * SHA256(span)=1622fd6dbbb0db6692e3d9d1fa7245be827fb46f6515bfc3c611af28727666a1.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B06E)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0xAE220020)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B2B9)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x08050B88)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C058018)
MUSASHI_NATIVE_MIPS_WORD(0x24A5F7BC)
MUSASHI_NATIVE_MIPS_WORD(0x0C007287)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x24021800)
MUSASHI_NATIVE_MIPS_WORD(0xA602001A)
MUSASHI_NATIVE_MIPS_WORD(0xA6020018)
MUSASHI_NATIVE_MIPS_WORD(0x0C050ACB)
MUSASHI_NATIVE_MIPS_WORD(0xA48000FC)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8001CA1C(void *, s32 (*)());       /* extern */
extern s32 D_8017F7BC;
void *func_8012C1B8();                              /* static */
void func_8012CAE4(void *);                      /* static */
void func_80142B2C(void *);                      /* static */

void func_80142DC4(void *arg0) {
    void *temp_v0;

    temp_v0 = func_8012C1B8();
    M2C_FIELD(arg0, void **, 0x20) = temp_v0;
    if (temp_v0 == 0) {
        func_8012CAE4(arg0);
        return;
    }
    func_8001CA1C(temp_v0, D_8017F7BC);
    M2C_FIELD(temp_v0, s16 *, 0x1A) = 0x1800;
    M2C_FIELD(temp_v0, s16 *, 0x18) = 0x1800;
    M2C_FIELD(arg0, s16 *, 0xFC) = 0;
    func_80142B2C(arg0);
}
#endif
