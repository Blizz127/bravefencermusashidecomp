/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801399F0();
void func_80139914();
void func_80129248();
extern u16 D_801270C0;
extern u8 D_800B9A17;
typedef struct { u8 pad[0x198]; void *u198; } T;
void func_80161094(T *p) {
    if (func_801399F0(p->u198)) {
        func_80139914(p->u198);
        p->u198 = 0;
    }
    D_801270C0 = 1;
    func_80129248(1);
    D_800B9A17 = 1;
}
