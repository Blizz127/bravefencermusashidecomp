/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_801806BC[];
void func_80156648();
void func_80147078();
void func_80157D74();
void func_80157D20(void *p, s32 a1) {
    func_80156648(p);
    func_80147078(p, D_801806BC[a1]);
    func_80157D74(p);
}
