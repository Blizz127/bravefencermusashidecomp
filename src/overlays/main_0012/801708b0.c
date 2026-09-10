/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern void *D_8011F738;
void func_801484B0();
void func_80149350();
void *func_8014C168();
void func_80171928();
typedef struct { s16 x, y, z; } S;
void func_801708B0(void *p) {
    S a;
    S b;
    u8 *q;
    func_801484B0(&a, &b);
    func_80149350(p, &a, &a);
    q = func_8014C168(p, D_8011F738);
    *(u16 *)(q + 6) = a.x;
    *(u16 *)(q + 10) = a.y;
    *(u16 *)(q + 14) = a.z;
    func_80171928(p);
}
