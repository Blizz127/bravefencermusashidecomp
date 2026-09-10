/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80029124();
void func_800291C8();
void func_80016714();
extern void *D_801842A0[3];
void func_801622C4(void) {
    s32 i;
    func_80029124(0x141, 1);
    func_800291C8(8, 0);
    for (i = 0; i < 3; i++) {
        func_80016714(D_801842A0[i], 0x38);
    }
}
