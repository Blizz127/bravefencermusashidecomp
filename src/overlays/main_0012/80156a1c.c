/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147324();
extern u8 D_8011520C[];
extern u16 D_80180654[];
typedef struct { u8 pad[0xDA]; u8 uDA; } T;
void func_80156A1C(T *p, s32 a1) {
    if (p->uDA) {
        return;
    }
    func_80147324(D_80180654[D_8011520C[a1]]);
    p->uDA++;
}
