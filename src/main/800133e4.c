/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80049324();
typedef struct { s32 x, y, z; } V;
s32 func_800133E4(s16 *a, s16 *b) {
    V in, out;
    in.x = a[0] - b[1];
    in.y = a[1] - b[3];
    in.z = a[2] - b[5];
    func_80049324(&in, &out);
    return out.x + out.y + out.z;
}
