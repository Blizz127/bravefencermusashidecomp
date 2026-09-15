/* Overlay range [801457A4,801458C4) from MAIN.CD member 0012.
 * SHA256(span)=4d483a9851eee2f5fd1e2aa24a54eae26379a4a8156eaf023a2f0c692cf0eea4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0000)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0xAFC40008)
MUSASHI_NATIVE_MIPS_WORD(0x8FC20008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2843201B)
MUSASHI_NATIVE_MIPS_WORD(0x1060001A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28432015)
MUSASHI_NATIVE_MIPS_WORD(0x1060002D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24031077)
MUSASHI_NATIVE_MIPS_WORD(0x1043002A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28431078)
MUSASHI_NATIVE_MIPS_WORD(0x10600009)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24031010)
MUSASHI_NATIVE_MIPS_WORD(0x10430024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24031052)
MUSASHI_NATIVE_MIPS_WORD(0x10430021)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805162D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24031094)
MUSASHI_NATIVE_MIPS_WORD(0x1043001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24032013)
MUSASHI_NATIVE_MIPS_WORD(0x10430019)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805162D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28432081)
MUSASHI_NATIVE_MIPS_WORD(0x1060000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2843207A)
MUSASHI_NATIVE_MIPS_WORD(0x10600011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2843205C)
MUSASHI_NATIVE_MIPS_WORD(0x1060001A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28432055)
MUSASHI_NATIVE_MIPS_WORD(0x14600017)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08051621)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2843209E)
MUSASHI_NATIVE_MIPS_WORD(0x10600012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28422097)
MUSASHI_NATIVE_MIPS_WORD(0x1440000F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08051621)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FC20008)
MUSASHI_NATIVE_MIPS_WORD(0x3C03FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x34630FFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00031080)
MUSASHI_NATIVE_MIPS_WORD(0x3C048018)
MUSASHI_NATIVE_MIPS_WORD(0x2484E338)
MUSASHI_NATIVE_MIPS_WORD(0x00441821)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0x08051633)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028018)
MUSASHI_NATIVE_MIPS_WORD(0x8C42E338)
MUSASHI_NATIVE_MIPS_WORD(0x08051633)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8017E338;
void func_801458CC(s32 (*)[]);                         /* static */

void func_801457A4(s32 arg0) {
    if (arg0 < 0x201B) {
        if ((arg0 < 0x2015) && (arg0 != 0x1077)) {
            if (arg0 < 0x1078) {
                if ((arg0 != 0x1010) && (arg0 != 0x1052)) {
                    /* Duplicate return node #20. Try simplifying control flow for better match */
                    func_801458CC();
                    return;
                }
                /* Duplicate return node #18. Try simplifying control flow for better match */
                func_801458CC((s32 (*)[]) D_8017E338);
                return;
            }
            if ((arg0 != 0x1094) && (arg0 != 0x2013)) {
                /* Duplicate return node #20. Try simplifying control flow for better match */
                func_801458CC();
                return;
            }
            /* Duplicate return node #18. Try simplifying control flow for better match */
            func_801458CC((s32 (*)[]) D_8017E338);
            return;
        }
        /* Duplicate return node #18. Try simplifying control flow for better match */
        func_801458CC((s32 (*)[]) D_8017E338);
        return;
    }
    if (arg0 < 0x2081) {
        if (arg0 < 0x207A) {
            if ((arg0 < 0x205C) && (arg0 >= 0x2055)) {
                /* Duplicate return node #18. Try simplifying control flow for better match */
                func_801458CC((s32 (*)[]) D_8017E338);
                return;
            }
            /* Duplicate return node #20. Try simplifying control flow for better match */
            func_801458CC();
            return;
        }
        /* Duplicate return node #18. Try simplifying control flow for better match */
        func_801458CC((s32 (*)[]) D_8017E338);
        return;
    }
    if ((arg0 < 0x209E) && (arg0 >= 0x2097)) {
        func_801458CC((s32 (*)[]) D_8017E338);
        return;
    }
    func_801458CC();
}
#endif
