/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8017B0E4();
extern s16 D_8018534C;
extern s16 D_80185C08;
void func_8017BCA0(void *p) {
    func_8017B0E4(p, 0xC);
    D_8018534C = D_8018534C + 1;
    if (D_8018534C >= 0x1F) {
        D_80185C08 = 2;
    }
}
