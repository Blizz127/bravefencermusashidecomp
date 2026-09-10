/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800291C8();
void func_80016714();
extern void *D_801842F8[3];
void func_80162760(void) {
    s32 i;
    func_800291C8(0x12, 0);
    for (i = 0; i < 3; i++) {
        func_80016714(D_801842F8[i], 0x38);
    }
}
