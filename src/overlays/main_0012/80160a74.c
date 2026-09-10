#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80147078(s32, s32);                            /* static */
void func_80159B70(s32);                               /* static */
void func_80160B00();                                  /* static */
extern u8 D_80078EBF;

void func_80160A74(s32 arg0) {
    if (D_80078EBF == 0x80) {
        func_80160B00();
        return;
    }
    func_80147078(arg0, 0);
    func_80159B70(arg0);
}
