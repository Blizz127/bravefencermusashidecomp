/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[8]; } T8;
typedef struct { u8 pad[0x3C]; T8 mid; } Tsrc;
extern Tsrc *D_801151D4;
extern T8 D_80114F24;
void func_8012A464(void) {
    D_80114F24 = D_801151D4->mid;
}
