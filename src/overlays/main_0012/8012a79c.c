/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A79C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. NOTE: func_8004CFEC is declared (s32, s32): func_8012B77C
 * passes full 32-bit differences as the second argument, so the
 * parameter is 32 bits wide even where only 16 arrive (same codegen). CORRECTED: raw asm shows func_8004CFEC takes two args (func_8012A6D0 never sets $a2 before the call); the $a2 load is register allocation for the temp, not a third argument. */

extern s16 func_8004CFEC(s32 arg0, s32 arg1);

struct pt_8012A79C {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

s16 func_8012A79C(struct pt_8012A79C *arg0, struct pt_8012A79C *arg1) {
    s16 temp_a2;

    temp_a2 = arg0->unk0;
    return func_8004CFEC(temp_a2 - arg1->unk0, arg0->unk4 - arg1->unk4);
}

