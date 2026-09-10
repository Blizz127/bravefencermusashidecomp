/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800484EC();
typedef struct { u8 pad[0x10]; s32 u10; u8 pad14[4]; s32 u18; } Inner;
typedef struct { u8 pad[0x10]; s32 u10; u8 pad14[4]; s32 u18; u8 pad1C[4]; u8 *inner; } T;
void func_8012B1B4(T *p, void *a1) {
    s32 tmp[4];
    func_800484EC(p->inner + 0x34, a1, tmp);
    p->u10 = tmp[0];
    p->u18 = tmp[2];
}
