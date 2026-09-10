/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_8004914C(void *);                               /* extern */
void func_800491AC(void *);                               /* extern */
extern s32 *D_800AF648;

void func_8012E32C(void) {
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
}
