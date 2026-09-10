/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80049324();
extern s16 D_80126CAC;
extern s16 D_80126CB0;
typedef struct { s32 x, y, z; } V;
s32 func_80132E6C(s16 *p) {
    V in, out;
    in.x = p[3] - D_80126CAC;
    in.y = 0;
    in.z = p[7] - D_80126CB0;
    func_80049324(&in, &out);
    return out.x + out.z;
}
