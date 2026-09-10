/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80062C04;
void func_80019064();
void func_80149020();
void func_801472C8();
void func_8014CBF8();
void func_801474EC();
void func_80155440();
void func_80146CA0();
typedef struct { u8 pad[0xDE]; u8 fDE; } T;
void func_801530E4(T *p) {
    func_80019064(&D_80062C04);
    func_80149020(p);
    func_801472C8(p);
    p->fDE = 0x40;
    func_8014CBF8(p);
    func_801474EC(p);
    func_80155440(p);
    func_80146CA0(p);
}
