/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8016B448 (main_0012.s), decoded manually from
 * raw asm (0x74 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): v0 =
 * 8014C050(&D_80126B58, 0x1E); when nonzero calls 8016B984(v0)
 * (v0 set in the jal delay slot). Then 80146A6C(0x1E, obj, lh
 * +0x7C, lh +0x7E, lh +0x80, arg1, 0): the last three ride stack
 * slots 0x10 (in the jal delay slot), 0x14 (incoming arg1 saved
 * early), 0x18 (zero). Same 7-arg callee as func_8016AA50's
 * tail, which passes (0x1D, ...) with (0, arg1)/(7, 0). */

struct obj_8016B448 {
    u8 pad[0x7C];
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
};

extern u8 D_80126B58;
extern s32 func_8014C050(void *arg0, s32 arg1);
extern void func_8016B984(s32 arg0);
extern void func_80146A6C(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_8016B448(void *arg0, s32 arg1) {
    struct obj_8016B448 *o;
    s32 v0;

    o = (struct obj_8016B448 *) arg0;
    v0 = func_8014C050(&D_80126B58, 0x1E);
    if (v0 != 0) {
        func_8016B984(v0);
    }
    func_80146A6C(0x1E, arg0, o->unk7C, o->unk7E, o->unk80, arg1, 0);
}
