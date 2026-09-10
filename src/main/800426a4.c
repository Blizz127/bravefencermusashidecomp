/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_800426A4 (main.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. D_8006CB84 is a LOADED struct pointer (lw) shared
 * with func_80042718's dispatch table; this unit calls the callback
 * at +0x18 Callback at +0x18, no args (lw/jalr). Body is m2c's verbatim with the member typed. */

struct cb84_800426A4 {
    u8 pad[0x18];
    void (*unk18)();
};

extern struct cb84_800426A4 *D_8006CB84;

void func_800426A4(void) {
    D_8006CB84->unk18();
}
