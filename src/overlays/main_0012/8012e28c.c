/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_80010A08();
s32 func_80058B40();
void func_8005A600();
void func_80058C6C();
extern u16 D_800B9A02;
typedef struct { u8 *p; u8 pad[16]; } Slot;
extern Slot D_800A651C[];
void func_8012E28C(s32 n, void *src) {
    u8 *slot;
    void *tmp;
    s32 v;
    if (n <= 0) {
        return;
    }
    slot = D_800A651C[D_800B9A02].p + n * 4;
    tmp = func_80010A08(0xC);
    v = func_80058B40(0, src, 0, 0);
    func_8005A600(tmp, 0, 0, (u16)v, 0);
    func_80058C6C(slot, tmp);
}
