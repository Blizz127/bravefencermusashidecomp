/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[183]; } T_8002AF70;
extern T_8002AF70 D_80075CC0;
extern s32 D_80076040;
void func_80016714();
void func_8002AF70(T_8002AF70 *src, s32 extra) {
    func_80016714(&D_80075CC0, 0x300);
    D_80075CC0 = *src;
    D_80076040 = extra;
}
