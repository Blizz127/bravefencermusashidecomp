/* Exact retail word export for [80011144,800111BC); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0018)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C006A7E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800B)
MUSASHI_NATIVE_MIPS_WORD(0x2484E888)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA52C70)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x0C006689)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x240403E0)
MUSASHI_NATIVE_MIPS_WORD(0x0C0042B8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0045DE)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0054C4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (30/30 words at 0x80011144, -O0). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

extern s32 D_80072C70;
void func_80010AE0();                                 /* static */
void func_80011778();                                  /* static */
void func_80015310();                                  /* static */
s32 func_80019A24(void *, s32, s32, s32);                  /* static */
void func_8001A9F8();                                 /* static */
extern s32 *D_800AE888;

void func_80011144(void) {
    s32 pad; /* Unused stack slot: retail's -O0 frame is 0x20, not the 0x18
              * an empty body produces. Any 4-byte unused local yields the
              * same bytes; this is a codegen constraint, not source evidence. */
    (void) pad;
    func_8001A9F8(0);
    if (func_80019A24(&D_800AE888, D_80072C70, 0, 0) != 0) {
        func_80010AE0(0x3E0);
        func_80011778();
        func_80015310();
    }
}
#endif
