/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8017B0E4();
void func_8012A4BC();
extern s16 D_8018534C;
extern s16 D_80185C08;
void func_8017BCF4(void *p) {
    func_8017B0E4(p, 6);
    D_8018534C++;
    if (D_8018534C >= 0x19) {
        func_8012A4BC();
        D_80185C08 = 0;
    }
}
