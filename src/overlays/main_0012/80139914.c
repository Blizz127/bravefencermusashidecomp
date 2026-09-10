/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8013A8B0();
typedef struct {
    s32 u0;
    s16 u4;
    u8 pad6[0x12]; u16 u18;
    u8 pad1A[0x26]; void *u40;
} T;
void func_80139914(T *p) {
    p->u4 = 0;
    p->u0 = 0;
    if (p->u18 && p->u40) {
        func_8013A8B0(p->u40);
    }
}
