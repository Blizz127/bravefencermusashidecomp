/* Main-exec range [80010F80,800110CC) from the SLUS executable.
 * SHA256(span)=13e02316b3255d0ed1b9351f2eb40f823c71307530029e22d0c023f9b3c1abfb.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00018)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x3C10800B)
MUSASHI_NATIVE_MIPS_WORD(0x2610F630)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x24428E78)
MUSASHI_NATIVE_MIPS_WORD(0xAFC20010)
MUSASHI_NATIVE_MIPS_WORD(0x0C033BB2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0x9422A3B6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040003B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0046DF)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C007011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0054C4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0x8422A3B8)
MUSASHI_NATIVE_MIPS_WORD(0x24030004)
MUSASHI_NATIVE_MIPS_WORD(0x1443000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0xA022A434)
MUSASHI_NATIVE_MIPS_WORD(0x2404000F)
MUSASHI_NATIVE_MIPS_WORD(0x0C004606)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0800442C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0x8422A3B8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28430002)
MUSASHI_NATIVE_MIPS_WORD(0x1060001E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24023005)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0xA422A3D8)
MUSASHI_NATIVE_MIPS_WORD(0x24023000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0xA422A3DA)
MUSASHI_NATIVE_MIPS_WORD(0x3C048006)
MUSASHI_NATIVE_MIPS_WORD(0x8C8429C8)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A545)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x02010821)
MUSASHI_NATIVE_MIPS_WORD(0x8422A3B8)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x14430009)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2404000A)
MUSASHI_NATIVE_MIPS_WORD(0x0C004606)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2404000B)
MUSASHI_NATIVE_MIPS_WORD(0x0C0046DF)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0800442C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2404000A)
MUSASHI_NATIVE_MIPS_WORD(0x0C004606)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* func_80010F80 - 83 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8  D_800BA118;
extern u8  D_800AF630[];
extern s32 D_80074778;
extern s32 D_800A2B7C;
extern s32 D_800C7C70;
extern s16 D_800C7C74;
extern s32 D_800A5E60;
extern u8  D_8007BA70[];
extern u8  D_800A4F48[];
extern s32 D_800A651C;
extern u8  D_800A6528[];
extern u8  D_800A6610[];
extern u8  D_800AA60C[];
extern s32 D_800AE7BC;
extern s32 D_800AE7C8;
extern u8  D_800BA0D8[];
extern u8  D_800BA0E4[];
extern void func_80043060(s32);
extern void func_800141F0(void);
extern void func_8005FC68(s32);
extern void func_8005FCB8(void);
extern void func_80018918(void);
extern s32  func_80043300(void);
extern void func_8002C8F4(void);
extern void LoaderInitFileTable(void);
extern void func_80014238(void);
extern void func_80014390(void);
extern void func_800191A8(void);
extern void func_80010A98(void);
extern void func_800189A8(void);
extern void func_80015208(void);
extern void func_80059BFC(s32, s32);
extern void GameModeDispatch(void);
extern void func_80015498(void);
extern void func_8001C00C(void);
extern void func_800D25FC(void);
extern void func_800184F0(void);
extern void func_800596F4(s32);
extern s32  VSync(s32);
extern void func_80059FC0(u8 *);
extern void func_80059D68(u8 *);
extern void CatPrim(s32, s32);
extern s32  func_80059CF4(s32);
extern void func_8003500C(void);
extern void func_8002D034(void);
extern void func_8001AF34(void);
extern void func_8001513C(void);
extern void func_80042610(void (*)(void));
extern s32 VSync(s32);
extern u8 D_800AF630[];
extern s32 D_800AE810[];
extern void DrawSyncCallback(void (*func)(void));
extern void func_80042610(void (*func)(void));
extern void func_8001099C(void);
extern void func_8001096C(void);
extern void (*gameModeHandlerTable[])(void);
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_80029690(void);
extern void func_80018FC8(void);
extern void func_8001903C(void);
extern void func_80029274(void);
extern void func_8002941C(void);
extern void func_80010AE0(s32);
extern void func_80011B7C(s32);
extern void func_80011778(void);
extern s16 D_801150D4;
extern s32 D_80074784;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern u8 D_800AE838;
extern void *loadDestPtrTable;
extern void func_800CEDFC(void);
extern void func_80011818(s32);
extern void func_8002D4C8(s32, s32);
extern s32 D_800C7C60;
extern void *D_800C7C64;
extern u8 D_800A2E20[];
extern u8 D_800AE848[];
extern void func_80010AE0(int);
extern void func_80014338(void);
extern void func_800116E0(void);
extern s16 D_800B99DA;
extern void func_800CEEC8(void);
extern void func_80029514(s32);
extern u8 D_80078E78[];
extern s32 D_800629C8;
extern void func_8001A9F8(int);
extern u8 D_800AE880;
extern u8 D_800AE888;
extern void func_800CEE74(void);
extern u8 D_800AE870;
extern s32 D_8007478C;
extern u16 D_800B99E8;
extern s32 D_800629D4[];
extern u8 D_800629D6[];
extern u16 D_800629E8[];
extern u8 D_800D3A68[];
extern s32 D_800AE6A8;
extern void func_800295D4(void);
extern void func_80029664(void);
extern void func_80011DCC(void);
extern void func_80011E24(void);
extern void func_8005C4CC(s32);
extern void func_800118AC(void);
extern void func_80011EB4(void);
extern s32 func_80014CAC(s32, s32);
extern void func_80011DA0(void);
extern void func_800D1724(s32);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern s32 D_80074780;
extern u16 D_80074794;
extern u16 D_80074798;
extern u8 D_800A6610[];

void func_80010F80(void) {
    register u8 *p = D_800AF630;
    u8 *sp10 = D_80078E78;
    func_800CEEC8();
    if (*(u16 *)(p + 0xA3B6) != 0) {
        func_80011B7C(0);
        func_8001C044();
        func_80015310();
        if (*(s16 *)(p + 0xA3B8) == 4) {
            *(u8 *)(p + 0xA434) = 1;
            func_80011818(0xF);
        } else if (*(s16 *)(p + 0xA3B8) < 2) {
            *(s16 *)(p + 0xA3D8) = 0x3005;
            *(s16 *)(p + 0xA3DA) = 0x3000;
            func_80029514(D_800629C8);
            if (*(s16 *)(p + 0xA3B8) == 1) {
                func_80011818(0xA);
                func_80011B7C(0xB);
            } else {
                func_80011818(0xA);
            }
        }
    }
    (void)sp10;
}
#endif
