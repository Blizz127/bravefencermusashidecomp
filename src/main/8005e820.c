/* Main-exec range [8005E820,8005E8E8) from the SLUS executable.
 * SHA256(span)=e73427ef14997b01d41e3c530eefc011dfdedd2581171b2c2238a6d6759e4b19.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908200E9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040002B)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x240B00FF)
MUSASHI_NATIVE_MIPS_WORD(0x00005021)
MUSASHI_NATIVE_MIPS_WORD(0x8C850020)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x24030005)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14480002)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24E70001)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0461FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x01421021)
MUSASHI_NATIVE_MIPS_WORD(0x90490002)
MUSASHI_NATIVE_MIPS_WORD(0x8C850020)
MUSASHI_NATIVE_MIPS_WORD(0x15200002)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x24090001)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14480008)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x00E9102A)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0CB005D)
MUSASHI_NATIVE_MIPS_WORD(0x08017A2D)
MUSASHI_NATIVE_MIPS_WORD(0x24E7FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA0C8005D)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x28620006)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x908200E9)
MUSASHI_NATIVE_MIPS_WORD(0x25080001)
MUSASHI_NATIVE_MIPS_WORD(0x0102102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFD9)
MUSASHI_NATIVE_MIPS_WORD(0x254A0005)
MUSASHI_NATIVE_MIPS_WORD(0x240200FE)
MUSASHI_NATIVE_MIPS_WORD(0xA0820046)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8005E820(void *arg0) {
    s32 var_a3;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    s8 var_t0;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 var_t1;
    void *var_a2;

    var_t0 = 0;
    if (M2C_FIELD(arg0, u8 *, 0xE9) != 0) {
        var_t2 = 0;
        do {
            var_a1 = M2C_FIELD(arg0, u8 **, 0x20);
            var_a3 = 0;
            var_v1 = 5;
loop_3:
            var_a1 += 1;
            if (*var_a1 == var_t0) {
                var_a3 += 1;
            }
            var_v1 -= 1;
            if (var_v1 >= 0) {
                goto loop_3;
            }
            var_t1 = M2C_FIELD((var_t2 + M2C_FIELD(arg0, s32 *, 4)), u8 *, 2);
            var_a1_2 = M2C_FIELD(arg0, u8 **, 0x20);
            var_v1_2 = 0;
            if (var_t1 == 0) {
                var_t1 = 1;
            }
            var_a2 = arg0;
loop_9:
            var_a1_2 += 1;
            if (*var_a1_2 == var_t0) {
                if (var_a3 < (s32) var_t1) {
                    M2C_FIELD(var_a2, s8 *, 0x5D) = -1;
                    var_a3 -= 1;
                } else {
                    M2C_FIELD(var_a2, s8 *, 0x5D) = var_t0;
                }
            }
            var_v1_2 += 1;
            var_a2 += 1;
            if (var_v1_2 < 6) {
                goto loop_9;
            }
            var_t0 += 1;
            var_t2 += 5;
        } while (var_t0 < (s32) M2C_FIELD(arg0, u8 *, 0xE9));
    }
    M2C_FIELD(arg0, s8 *, 0x46) = 0xFE;
    return 0;
}
#endif
