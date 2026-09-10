/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[41]; } T41;
extern T41 *D_801151D4;
extern T41 D_80126DB8;
extern u8 D_80127504;

extern T41 D_80114EE8;
void func_8012A4BC(void) {
    D_80126DB8 = *D_801151D4;
    *D_801151D4 = D_80114EE8;
    D_80127504 = 0x30;
}
