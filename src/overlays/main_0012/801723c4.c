/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801599A4();
void func_80147078();
void func_8014A1B0();
typedef struct { u8 pad[0x178]; s32 f178; } T;
void func_801723C4(T *p, s32 a1) {
    func_801599A4(p);
    func_80147078(p, 0xD);
    p->f178 = a1;
    func_8014A1B0(p, a1);
}
