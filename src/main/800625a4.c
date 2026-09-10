#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */
void func_8005E178(s32, void *);                            /* static */
extern s32 *D_80078D08;

s32 func_800625A4(void) {
    func_8005CF08();
    func_8005E178(1, &D_80078D08);
    func_8005CF18();
    return 1;
}
