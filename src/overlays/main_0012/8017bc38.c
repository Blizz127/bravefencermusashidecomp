/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80185394[10];
void func_8017BC38(void *p) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (D_80185394[i])
            D_80185394[i](p);
    }
}
