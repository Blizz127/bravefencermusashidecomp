/* Exact retail word export for [80014444,800144D4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x0c011f2d)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x240203e8)
MUSASHI_NATIVE_MIPS_WORD(0x3c018012)
MUSASHI_NATIVE_MIPS_WORD(0xac226950)
MUSASHI_NATIVE_MIPS_WORD(0x0c01248f)
MUSASHI_NATIVE_MIPS_WORD(0x240403e8)
MUSASHI_NATIVE_MIPS_WORD(0x0c014c86)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c005135)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c005157)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24040800)
MUSASHI_NATIVE_MIPS_WORD(0x24050800)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a143)
MUSASHI_NATIVE_MIPS_WORD(0x24060800)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a08f)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3c10800b)
MUSASHI_NATIVE_MIPS_WORD(0x2610f630)
MUSASHI_NATIVE_MIPS_WORD(0x0c014b64)
MUSASHI_NATIVE_MIPS_WORD(0x260501a0)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x0c014b64)
MUSASHI_NATIVE_MIPS_WORD(0x260501f0)
MUSASHI_NATIVE_MIPS_WORD(0x0c014e3b)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (36/36 words at 0x80014444). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

void func_800144D4();                                  /* static */
void func_8001455C();                                  /* static */
void func_8002823C();                                  /* static */
void func_8002850C(s32, s32, s32);                           /* static */
void func_80047CB4();                                  /* static */
void func_8004923C();                                 /* static */
void func_80052D90(s32, void *);                         /* static */
void func_80053218();                                  /* static */
void func_800538EC();                                 /* static */
extern u8 D_800AF630[];
extern s32 D_80126950;

void func_80014444(void) {
    u8 *base;
    base = &D_800AF630[0];
    func_80047CB4();
    D_80126950 = 0x3E8;
    func_8004923C(0x3E8);
    func_80053218();
    func_800144D4();
    func_8001455C();
    func_8002850C(0x800, 0x800, 0x800);
    func_8002823C();
    func_80052D90(0, base + 0x1A0);
    func_80052D90(1, base + 0x1F0);
    func_800538EC(0);
}
#endif
