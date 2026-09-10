/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8013767C();
void func_801719A4();
void func_80171928();
extern void *D_8011F738;
typedef struct { u8 pad_0[0x198]; void *ptr; } T;
void func_801700B8(T *p) {
    func_801719A4(p, 1);
    p->ptr = func_8013767C(D_8011F738);
    func_80171928(p);
}
