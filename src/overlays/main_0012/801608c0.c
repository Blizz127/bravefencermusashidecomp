/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801553A8();
void func_80155440();
void func_80154150();
void func_80154A74();
void func_80146CA0();
typedef struct {
    u8 pad_0[68];
    u32 flags;
} T;
void func_801608C0(T *p) {
    p->flags |= 65;
    func_801553A8(p);
    func_80155440(p);
    func_80154150(p, 36);
    func_80154A74(p, 29);
    func_80146CA0(p);
}
