#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012A018(s32 (*)(), s32);                     /* static */
void func_8012A0E0();                                  /* static */
void func_80174BBC(void *);                               /* static */
void func_80174BF4(void *);                               /* static */
extern s32 *D_80126948;

void func_80174B6C(void) {
    func_80174BBC(&D_80126948);
    func_8012A018(func_80174BF4, 0);
    func_8012A0E0();
    func_80174BF4(&D_80126948);
}
