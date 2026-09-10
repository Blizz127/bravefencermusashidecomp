/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 r,g,b,code;
    u8 r2,g2,b2,code2;
    u8 rest[28];
    u32 tag;
} P;
void func_80058F24(P *p) {
    p->code = 9;
    p->code2 = 92;
    p->tag = 0x55555555u;
}
