/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8013A9F8();
typedef struct {
    u8 pad[0x18]; u16 u18;
    u8 pad1A[0x26]; void *u40;
} T;
void func_80138D58(T *p, u16 a1) {
    if (p->u40 && (u16)(p->u18 - 2) < 5 && (u16)(a1 - 2) < 5) {
        p->u18 = a1;
        func_8013A9F8(p->u40, a1);
    }
}
