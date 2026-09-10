/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BD3C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Single function with entry at 0x8012BD3C (same prefix-fallthrough shape as func_8012A328: lh D_80126CBA with no jr, falling into the body range labelled func_8012BD44, which is a mid-function label with no separate file). No direct callers found in main_0012; reached via table or another overlay. Second BDBC argument is a sign-extended half (sll/sra pair in raw). */

extern s16 D_80126CBA;
extern u8 D_80126CB4;

extern s32 func_80013478(void *arg0, void *arg1);
extern s32 func_8012BDBC(s32 arg0, s16 arg1);

s32 func_8012BD3C(s32 arg0, s16 arg1, s32 arg2) {
    s32 v;

    if (D_80126CBA != 0) {
        v = 0x7FFFFFFF;
    } else {
        v = func_80013478((void *) (arg0 + 4), &D_80126CB4);
    }
    if (arg2 < v) {
        return 0;
    }
    return func_8012BDBC(arg0, arg1);
}

