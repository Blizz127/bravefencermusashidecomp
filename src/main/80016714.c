/* Main-exec range [80016714,800167B8) from the SLUS executable.
 * SHA256(span)=58996412878b336abbb2eb32b4501a76201ed20b3c60b76bdca4c3bc60d419ca.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x28A20004)
MUSASHI_NATIVE_MIPS_WORD(0x1040000A)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10A20022)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0800000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14A2FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x080059EC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30820003)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00801821)
MUSASHI_NATIVE_MIPS_WORD(0xA0800000)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x30620003)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00051883)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10620005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC800000)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1462FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x30A50003)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10A20005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0800000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14A2FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MEMSET_BINDING
#include <stdint.h>
#endif

/* Decompiled from retail and verified byte-exact with the identified
 * gcc-2.7.2-psx -O1 build. The separate word counter preserves the retail
 * use of v1 while the original byte count remains in a1 for the tail. */
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
void func_80016714_native(u8 *arg0, s32 arg1) {
#else
void func_80016714(s8 *arg0, s32 arg1) {
#endif
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
    uintptr_t var_address;
    s32 var_word_count;
#else
    u32 var_v1;
#endif

    if (arg1 < 4) {
        arg1--;
        if (arg1 != -1) {
            do {
                *arg0 = 0;
                arg1--;
                arg0++;
            } while (arg1 != -1);
        }
    } else {
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
        var_address = (uintptr_t)arg0;
#else
        var_v1 = (u32)arg0;
#endif
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
        if (var_address & 3) {
#else
        if (var_v1 & 3) {
#endif
            do {
                *arg0 = 0;
                arg0++;
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
                var_address++;
#else
                var_v1++;
#endif
                arg1--;
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
            } while (var_address & 3);
#else
            } while (var_v1 & 3);
#endif
        }
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
        var_word_count = (arg1 >> 2) - 1;
        if (var_word_count != -1) {
#else
        var_v1 = (arg1 >> 2) - 1;
        if (var_v1 != -1) {
#endif
            do {
                *(u32 *)arg0 = 0;
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
                var_word_count--;
#else
                var_v1--;
#endif
                arg0 += 4;
#ifdef MUSASHI_NATIVE_MEMSET_BINDING
            } while (var_word_count != -1);
#else
            } while (var_v1 != -1);
#endif
        }
        arg1 = (arg1 & 3) - 1;
        if (arg1 != -1) {
            do {
                *arg0 = 0;
                arg1--;
                arg0++;
            } while (arg1 != -1);
        }
    }
}
#endif
