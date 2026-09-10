/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8012AD50();
typedef struct Inner { u8 pad[0x18]; u16 u18, u1A; } Inner;
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    Inner *inner;
    u8 pad24[0xD8]; s16 uFC;
} T;
void func_801426D4(T *p) {
    Inner *in = p->inner;
    if (p->uFC) {
        p->uFC = p->uFC - 0x10;
        in->u18 = in->u18 + 0x800;
        in->u1A = in->u1A + 0x800;
    } else {
        p->u1C = 0xC;
        func_8012AD50(p);
        in->u1A = 0x1800;
        in->u18 = 0x1800;
    }
}
