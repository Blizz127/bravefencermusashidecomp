/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8013767C();
void func_80147324();
void func_80146CA0();
extern void *D_80180D78[];
typedef struct {
    u8 pad[0x198];
    void *ptr;
    u8 pad19C[4];
    u8 idx;
} T;
void func_8015FD74(T *p) {
    func_80147324(0x18);
    p->ptr = func_8013767C(D_80180D78[p->idx]);
    func_80146CA0(p);
}
