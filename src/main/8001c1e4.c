/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80054514();
typedef struct {
    u8 pad[0x30];
    s32 unk30;
    u8 pad34[0x44];
    void *unk78;
} T;
void func_8001C1E4(T *p, u8 *q) {
    s32 tmp[8];
    q += 0x30;
    p->unk78 = q;
    p->unk30 = 0;
    func_80054514(&p->unk30, tmp);
}
