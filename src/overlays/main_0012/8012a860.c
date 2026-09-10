/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012ACE0();
void func_8012AAAC();
typedef struct {
    u8 pad[0x72]; u16 f72;
    u8 pad74[0x1C]; s32 u90, u94;
    u8 pad98[2]; s16 u9a; s32 u9c;
} T;
void func_8012A860(T *p, s32 a1) {
    s32 v;
    p->u90 = a1;
    v = func_8012ACE0(p);
    p->u94 = v - 1;
    p->u9c = 0;
    p->u9a = 0;
    p->f72 |= 0x200;
    func_8012AAAC(p);
}
