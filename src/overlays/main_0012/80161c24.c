/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147324();
typedef struct { u16 a, b; } E;
extern E D_80180E38[];
typedef struct { u8 pad[0xDA]; u8 uDA; } T;
void func_80161C24(T *p, u32 a1) {
    if (a1 >= 8) {
        return;
    }
    if (p->uDA) {
        func_80147324(D_80180E38[a1].a);
        p->uDA = 0;
        return;
    }
    func_80147324(D_80180E38[a1].b);
    p->uDA = 1;
}
