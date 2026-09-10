/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u32 w[41]; } T;
extern T *D_801151D4;
extern T D_80114EE8;
void func_8012A418(void) { D_80114EE8 = *D_801151D4; }
