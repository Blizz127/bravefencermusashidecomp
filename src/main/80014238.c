/* Exact retail word export for [80014238,800142C8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c00524a)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c01648d)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x0c016596)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c0108e7)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3c04800b)
MUSASHI_NATIVE_MIPS_WORD(0x2484f630)
MUSASHI_NATIVE_MIPS_WORD(0x0c0059c5)
MUSASHI_NATIVE_MIPS_WORD(0x3405a444)
MUSASHI_NATIVE_MIPS_WORD(0x0c0050eb)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c005111)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c007011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c005162)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c0054c4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a292)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a314)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c0050b2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c016596)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_800142C8();                                  /* static */
void func_800143AC();                                  /* static */
void func_80014444();                                  /* static */
void func_80014588();                                  /* static */
void func_80014928();                                  /* static */
void func_80015310();                                  /* static */
void func_80016714(void *, s32);                            /* static */
void func_8001C044();                                  /* static */
void func_80028A48();                                  /* static */
void func_80028C50();                                  /* static */
void func_8004239C();                                 /* static */
void func_80059234();                                 /* static */
void func_80059658();                                 /* static */
extern s32 *D_800AF630;

void func_80014238(void) {
    func_80014928();
    func_80059234(1);
    func_80059658(0);
    func_8004239C(0);
    func_80016714(&D_800AF630, 0xA444);
    func_800143AC();
    func_80014444();
    func_8001C044();
    func_80014588();
    func_80015310();
    func_80028A48();
    func_80028C50();
    func_800142C8();
    func_80059658(1);
}
#endif
