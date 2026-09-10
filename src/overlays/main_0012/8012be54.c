/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BE54 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. NOTE: func_8004CFEC is declared (s32, s32) per
 * the func_8012B77C evidence. CORRECTED: the BE6C range calls func_8012BE98 (not 800132BC directly) with the caller pointer passed through in a0 and the u16 triple as the second argument; func_8012BE6C is a mid-function label with no separate file. Entry takes only the pointer; a1 is clobbered by the prefix loads. */

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

struct triple_8012BE54 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

void func_8012BE98(void *arg0, struct triple_8012BE54 *arg1);

void func_8012BE54(void *arg0) {
    struct triple_8012BE54 t;

    t.unk0 = D_80126B5E;
    t.unk2 = D_80126B62;
    t.unk4 = D_80126B66;
    func_8012BE98(arg0, &t);
}

