/* Overlay range [80128ED8,80128FAC) from MAIN.CD member 0012.
 * SHA256(span)=c66504fc74987bd8b54f6b189f0c397c5077a8a6773a973be4c47c79bee895e6.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF0)
MUSASHI_NATIVE_MIPS_WORD(0x84A20006)
MUSASHI_NATIVE_MIPS_WORD(0x8CA80000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x0804A3E8)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x2462FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20006)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x1C400027)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x000310C0)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x00603821)
MUSASHI_NATIVE_MIPS_WORD(0x8C460004)
MUSASHI_NATIVE_MIPS_WORD(0x240200C0)
MUSASHI_NATIVE_MIPS_WORD(0x30C300C0)
MUSASHI_NATIVE_MIPS_WORD(0x14620004)
MUSASHI_NATIVE_MIPS_WORD(0x30C20080)
MUSASHI_NATIVE_MIPS_WORD(0xA4A00006)
MUSASHI_NATIVE_MIPS_WORD(0x0804A3E8)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x24E20001)
MUSASHI_NATIVE_MIPS_WORD(0x0804A3D4)
MUSASHI_NATIVE_MIPS_WORD(0xA4A00004)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20004)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x8C420004)
MUSASHI_NATIVE_MIPS_WORD(0x00681821)
MUSASHI_NATIVE_MIPS_WORD(0x3042003F)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20006)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820028)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x00481021)
MUSASHI_NATIVE_MIPS_WORD(0x94420002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA482002A)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0010)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80128ED8 - 53 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_80128ED8(s32 param_1, s32 *param_2) {
    register s32 iVar4 __asm__("$8");   /* base ptr, lives whole fn in $t0 */
    register s32 cnt   __asm__("$2");   /* decremented count in $v0 */
    register s32 cc    __asm__("$3");   /* preserved count copy in $v1 (forces the bne-delay-slot copy) */
    register s32 idx   __asm__("$3");   /* offset-4 index, loaded into $v1 */
    register s32 idc   __asm__("$7");   /* $a3: preserved idx copy, forced SEPARATE from the multiply */
    u32 uVar3;
    s32 frame_pad[4];                   /* phantom 0x10 frame the target reserves (induce via clobber anchor) */
    __asm__ __volatile__("" : : "r"(&frame_pad) : "memory");
    iVar4 = *param_2;
    cnt = *(s16 *)((s32)param_2 + 6);
    if (cnt == 0) {
        return 1;
    }
    cc = cnt;
    __asm__ __volatile__("" : "=r"(cc) : "0"(cc));   /* force the count-preserve copy ($v1=$v0) */
    cnt = cc - 1;
    *(s16 *)((s32)param_2 + 6) = (s16)cnt;
    if (cnt * 0x10000 < 1) {
        idx = *(s16 *)((s32)param_2 + 4);
        __asm__ __volatile__("" : "=r"(idx) : "0"(idx));   /* pin the index into $v1 */
        uVar3 = *(u32 *)(idx * 8 + iVar4 + 4);
        idc = idx;
        if ((uVar3 & 0xc0) == 0xc0) {
            *(s16 *)((s32)param_2 + 6) = 0;
            return 1;
        }
        if ((uVar3 & 0x80) != 0) {
            *(s16 *)((s32)param_2 + 4) = 0;
        } else {
            cnt = idc + 1;                       /* reuse the dead $v0 pin so idc+1 lands in $v0, not $a3 */
            *(s16 *)((s32)param_2 + 4) = cnt;
        }
        *(u16 *)((s32)param_2 + 6) =
            (u16)(*(u32 *)((s16)param_2[1] * 8 + iVar4 + 4) & 0x3f);
        *(u16 *)(param_1 + 0x28) = *(u16 *)((s16)param_2[1] * 8 + iVar4);
        *(u16 *)(param_1 + 0x2a) = *(u16 *)((s16)param_2[1] * 8 + iVar4 + 2);
    }
    return 0;
}
#endif
