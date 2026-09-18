/* Exact retail word export for [8004787C,800478B8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0x04800005)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c011e2e)
MUSASHI_NATIVE_MIPS_WORD(0x30840fff)
MUSASHI_NATIVE_MIPS_WORD(0x08011e2a)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00042023)
MUSASHI_NATIVE_MIPS_WORD(0x0c011e2e)
MUSASHI_NATIVE_MIPS_WORD(0x30840fff)
MUSASHI_NATIVE_MIPS_WORD(0x00021023)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 func_800478B8(s32);

/* Structured `if/else`-return form inverts the test to `bgez` and swaps
 * the blocks. The convergent `goto` form keeps `bltz`-to-`neg` with the
 * positive path falling through, both `andi` setups sinking into the
 * call delay slots, and a bare `nop` in the join jump. */
s32 func_8004787C(s32 arg0) {
    s32 rc;

    if (arg0 < 0) {
        goto neg;
    }
    rc = func_800478B8(arg0 & 0xFFF);
    goto done;
neg:
    rc = -func_800478B8((-arg0) & 0xFFF);
done:
    return rc;
}
#endif
