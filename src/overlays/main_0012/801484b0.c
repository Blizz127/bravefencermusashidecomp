/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x20]; u8 *p20; } G;
extern G *D_80126B78;
void func_801485B8();
void func_801484B0(void *a, void *b) {
    func_801485B8(D_80126B78->p20 - 0x10, a, b);
}
