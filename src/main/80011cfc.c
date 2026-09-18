/* Main-exec range [80011CFC,80011D54) from the SLUS executable.
 * SHA256(span)=f53c0a5949b548163b099bf38259fbb0759606dd6e11a87648c60b1a52b9586f.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0000)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800B)
MUSASHI_NATIVE_MIPS_WORD(0x2442F630)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00410821)
MUSASHI_NATIVE_MIPS_WORD(0x9423A3CC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24640001)
MUSASHI_NATIVE_MIPS_WORD(0x00801821)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00410821)
MUSASHI_NATIVE_MIPS_WORD(0xA423A3CC)
MUSASHI_NATIVE_MIPS_WORD(0x3C010001)
MUSASHI_NATIVE_MIPS_WORD(0x00410821)
MUSASHI_NATIVE_MIPS_WORD(0xA420A3CE)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* func_80011CFC - 22 words. Promoted from vendor/bfm-decomp
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

void func_80011CFC(void) {
    register u8 *p = D_800AF630;

    (*(u16 *)(p + 0xA3CC))++;
    *(u16 *)(p + 0xA3CE) = 0;
}
#endif
