/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8012C218();
typedef struct Q { u8 pad[0xA]; u16 uA; } Q;
typedef struct {
    u8 pad[0x68]; Q *u68;
    u8 pad6C[6]; s16 u72;
} T;
void func_8012C098(T *p) {
    Q *q = p->u68;
    if (q && (p->u72 & 0x8000)) {
        q->uA &= 0x7FFF;
    }
    func_8012C218(p);
}
