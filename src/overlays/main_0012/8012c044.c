/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012C044 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Prefix-fallthrough pair #4 (same shape as func_8012A328): func_8012C044 loads the hook pointer D_801274D4 with no jr and falls into the range labelled func_8012C04C, which calls it indirectly (jalr, no arg setup beyond the live registers) or runs the 80013478 default path returning (t >= D_801274E0) via slt+xori. func_8012C04C is a mid-function label with no separate file. Entry takes only arg0; the indirect callee sees the live registers, modelled by passing arg0. */

extern void *D_801274D4;
extern s32 D_801274E0;
extern u8 D_80126CAC;

extern s32 func_80013478(void *arg0, void *arg1);

s32 func_8012C044(s32 arg0) {
    s32 (*hook)(s32);
    s32 t;

    hook = (s32 (*)(s32)) D_801274D4;
    if (hook != 0) {
        return hook(arg0);
    }
    t = func_80013478((void *) (arg0 + 4), &D_80126CAC);
    return t >= D_801274E0;
}

