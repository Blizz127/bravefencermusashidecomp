#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80157DC4();                                  /* static */
void func_80157FC4();                                  /* static */

void func_80157D74(u16 *arg0) {
    u16 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {                              /* irregular */
    case 36:
        func_80157DC4();
        return;
    case 37:
        func_80157FC4();
        return;
    }
}
