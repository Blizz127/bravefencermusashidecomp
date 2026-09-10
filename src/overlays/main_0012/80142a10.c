/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8017FA7C[];
extern s16 D_801270C0;
void func_80142A80();
typedef struct { u16 a, idx; u8 pad[0xF8]; s16 unkFC; } T;
void func_80142A10(T *p) {
    if (D_801270C0 != 3) {
        D_8017FA7C[p->idx]();
        if (p->unkFC)
            func_80142A80(p);
    }
}
