/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80159A20();
typedef struct { u8 pad[0x4D]; u8 unk4D; } T;
void func_801599E0(T *p) {
    func_80159A20(p);
    p->unk4D++;
}
