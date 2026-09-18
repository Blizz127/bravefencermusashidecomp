/* Overlay range [80139D04,80139DC8) from MAIN.CD member 0012.
 * SHA256(span)=29ee54114f20631d505417d3bd22872cd629cc619cc5dc4f7dccc709bd503947.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00804021)
MUSASHI_NATIVE_MIPS_WORD(0x24092710)
MUSASHI_NATIVE_MIPS_WORD(0x00005021)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x24060005)
MUSASHI_NATIVE_MIPS_WORD(0x3C0BCCCC)
MUSASHI_NATIVE_MIPS_WORD(0x356BCCCD)
MUSASHI_NATIVE_MIPS_WORD(0x30A3FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3122FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062001B)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0007000D)
MUSASHI_NATIVE_MIPS_WORD(0x00001812)
MUSASHI_NATIVE_MIPS_WORD(0x000A1100)
MUSASHI_NATIVE_MIPS_WORD(0x00625025)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x3142FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00C03821)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA1030000)
MUSASHI_NATIVE_MIPS_WORD(0x25080001)
MUSASHI_NATIVE_MIPS_WORD(0x30A3FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3122FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062001B)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0007000D)
MUSASHI_NATIVE_MIPS_WORD(0x00002010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x004B0019)
MUSASHI_NATIVE_MIPS_WORD(0x24C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00006010)
MUSASHI_NATIVE_MIPS_WORD(0x000C48C2)
MUSASHI_NATIVE_MIPS_WORD(0x1CC0FFDE)
MUSASHI_NATIVE_MIPS_WORD(0x00802821)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA1000000)
MUSASHI_NATIVE_MIPS_WORD(0x24E70001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30E2FFFF)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80139D04 - 49 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_80139D04(s32 a0, s32 a1) {
    register u8 *p    __asm__("$8");   /* $t0 */
    register u32 div  __asm__("$9");   /* $t1 */
    register u32 acc  __asm__("$10");  /* $t2 */
    register u32 cnt  __asm__("$6");   /* $a2 */
    register u32 flag __asm__("$7");   /* $a3 */
    register u32 param_2 __asm__("$5"); /* $a1 */
    u32 q;
    register u32 rem __asm__("$4");  /* $a0 */
    register u32 hi __asm__("$2");  /* $v0 */
    register u32 pm __asm__("$3");  /* $v1 */
    register u32 dm __asm__("$2");  /* $v0 */
    p = (u8 *)a0;
    param_2 = (u32)a1;
    div = 10000;
    acc = 0;
    flag = 0;
    cnt = 5;
    do {
        q = (param_2 & 0xffff) / (div & 0xffff);
        hi = acc << 4;
        acc = q | hi;
        __asm__ __volatile__("" : : "r"(acc));
        if ((flag & 0xffff) == 0) {
            if ((acc & 0xffff) != 0) {
                flag = cnt;
            }
            if ((flag & 0xffff) != 0) goto store;
        } else {
        store:
            *p = (u8)q;
            p = p + 1;
        }
        pm = param_2 & 0xffff;
        __asm__ __volatile__("" : : "r"(pm));
        dm = div & 0xffff;
        rem = pm % dm;
        div = dm / 10;
        cnt = cnt - 1;
        param_2 = rem;
        if ((s32)cnt < 1) {
            if ((flag & 0xffff) == 0) {
                *p = 0;
                flag = flag + 1;
            }
            return flag & 0xffff;
        }
    } while (1);
}
#endif
