/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8015DE24();
void func_80157510();
typedef struct { u8 pad[0x178]; s32 f; u8 pad17C[0x1AA-0x17C]; u8 g; } T;
void func_80149BAC(T *p) {
    if (p->f) {
        func_8015DE24(p);
    } else {
        p->g = 1;
        func_80157510(p);
    }
}
