/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80053AC0();
void func_80053ACC();
void func_80053AD8();
typedef struct { s16 a; u8 pad2[2]; s32 b; u8 c, d, e; } T;
void func_80053978(T *p) {
    func_80053AC0(p->a);
    func_80053ACC(p->b);
    func_80053AD8(p->c, p->d, p->e);
}
