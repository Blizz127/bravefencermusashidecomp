/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8014C168();
s32 func_80171AB0();
void func_80171928();
extern void *D_8011F738;
typedef struct { u8 pad[6]; u16 a; u8 pad8[2]; u16 b; u8 padC[2]; u16 c; } S;
void func_80170374(void *p) {
    s16 tmp[4];
    S *q = func_8014C168(p, D_8011F738);
    tmp[0] = q->a;
    tmp[1] = q->b;
    tmp[2] = q->c;
    if ((s16)func_80171AB0(p, tmp) == 0) {
        func_80171928(p);
    }
}
