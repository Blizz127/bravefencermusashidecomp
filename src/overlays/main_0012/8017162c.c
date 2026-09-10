#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_801716AC(s32, s32, s32 *);                     /* static */
void func_80171928(s32);                               /* static */
extern s32 D_8011F738;

void func_8017162C(s32 arg0) {
    s32 sp10;
    s32 temp_s0;

    temp_s0 = D_8011F738;
    sp10 = 0;
    func_801716AC(0, temp_s0, &sp10);
    func_801716AC(1, temp_s0, &sp10);
    func_801716AC(2, temp_s0, &sp10);
    if (sp10 == 0) {
        func_80171928(arg0);
    }
}
