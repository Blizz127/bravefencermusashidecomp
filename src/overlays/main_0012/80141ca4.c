/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_80029178();                               /* extern */
s32 func_800291B4();                               /* extern */
s32 func_80029504();                                /* extern */
extern s32 *D_80112C04;
extern s32 *D_80112C50;
extern s32 *D_80112C9C;
extern s32 *D_80112CE8;
extern s32 *D_80112D38;
extern s32 *D_80112D78;
extern s32 *D_80112DBC;
extern s32 *D_80112DF4;
extern s32 *D_80112E14;
extern s32 *D_80112E40;
extern s32 *D_80112E6C;
extern s32 *D_80112EBC;
extern s32 *D_80112F0C;
extern s32 *D_80112F48;
extern s32 *D_80112F9C;
extern s32 *D_80112FDC;
extern s32 *D_8011302C;
extern s32 *D_80113074;
extern s32 *D_801130B8;
extern s32 *D_801130E8;
extern s32 *D_80113138;
extern s32 *D_8011317C;
extern s32 *D_801131A8;
extern s32 *D_801131E8;
extern s32 *D_80113214;
extern s32 *D_80113254;
extern s32 *D_80113278;
extern s32 *D_801132B8;
extern s32 *D_801132E4;
extern s32 *D_80113324;
extern s32 *D_80113360;
extern s32 *D_801133A4;
extern s32 *D_801133F4;
extern s32 *D_80113440;
extern s32 *D_80113474;
extern s32 *D_801134B0;
extern s32 *D_801134FC;
extern s32 *D_80113530;
extern s32 *D_80113554;
extern s32 *D_801135A8;
extern s32 *D_80113600;
extern s32 *D_80113650;
extern s32 *D_80113694;
extern s32 *D_801136DC;
extern s32 *D_80113724;
extern s32 *D_80113744;
extern s32 *D_80113770;
extern s32 *D_80113794;
extern s32 *D_801137D8;
extern s32 *D_8011381C;
extern s32 *D_8011383C;
extern s32 *D_8011386C;
extern s32 *D_801138A4;
extern s32 *D_801138D0;
extern s32 *D_80113900;
extern s32 *D_80113944;
extern s32 *D_80113964;
extern s32 *D_8011399C;
extern s32 *D_801139E8;
extern s32 *D_80113A28;
extern s32 *D_80113A50;
extern s32 *D_80113A84;
extern s32 *D_80113AB0;
extern s32 *D_80113AE0;
extern s32 *D_80113B34;
extern s32 *D_80113B68;
extern s32 *D_80113BA4;
extern s32 *D_80113BC0;
extern s32 *D_80113BF0;
extern s32 *D_80113C20;
extern s32 *D_80113C3C;
extern s32 *D_80113C7C;

void *func_80141CA4(void) {
    void *var_v0;
    s32 temp_v0;

    temp_v0 = func_80029504();
    if (temp_v0 < 0xA) {
        return &D_80112C04;
    }
    if (temp_v0 < 0x14) {
        if (func_80029178(0xDF) & 0xFF) {
            return &D_80112D38;
        }
        if (func_80029178(0xE0) & 0xFF) {
            return &D_80112CE8;
        }
        var_v0 = &D_80112C50;
        if (func_80029178(0xDE) & 0xFF) {
            return &D_80112C9C;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x1E) {
        return &D_80112D78;
    }
    if (temp_v0 < 0x28) {
        return &D_80112DBC;
    }
    if (temp_v0 < 0x32) {
        return &D_80113B34;
    }
    if (temp_v0 < 0x3C) {
        var_v0 = &D_80112E14;
        if (!(func_80029178(0xE5) & 0xFF)) {
            return &D_80112DF4;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x46) {
        return &D_80112E40;
    }
    if (temp_v0 < 0x50) {
        return &D_80112E6C;
    }
    if (temp_v0 < 0x5A) {
        return &D_80112EBC;
    }
    if (temp_v0 < 0x64) {
        return &D_80112F0C;
    }
    if (temp_v0 < 0x78) {
        return &D_80112F48;
    }
    if (temp_v0 < 0x82) {
        return &D_80112F9C;
    }
    if (temp_v0 < 0x85) {
        if (func_80029178(0x9E) & 0xFF) {
            return &D_80113074;
        }
        var_v0 = &D_8011302C;
        if (!(func_80029178(0xEF) & 0xFF)) {
            return &D_80112FDC;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x87) {
        return &D_801130B8;
    }
    if (temp_v0 < 0x8C) {
        return &D_801130E8;
    }
    if (temp_v0 < 0x96) {
        return &D_80113138;
    }
    if (temp_v0 < 0xC8) {
        return &D_8011317C;
    }
    if (temp_v0 < 0xD2) {
        return &D_801131A8;
    }
    if (temp_v0 < 0xDC) {
        return &D_801131E8;
    }
    if (temp_v0 < 0xF0) {
        return &D_80113214;
    }
    if (temp_v0 < 0x104) {
        return &D_80113254;
    }
    if (temp_v0 < 0x118) {
        return &D_80113278;
    }
    if (temp_v0 < 0x136) {
        if (func_80029178(0xF9) & 0xFF) {
            return &D_801132E4;
        }
        var_v0 = &D_801132B8;
        if (func_80029178(0xFA) & 0xFF) {
            return &D_80113324;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x140) {
        return &D_80113360;
    }
    if (temp_v0 < 0x14A) {
        var_v0 = &D_801133A4;
        if (func_80029178(0xFF) & 0xFF) {
            return &D_801133F4;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x17C) {
        return &D_80113440;
    }
    if (temp_v0 < 0x186) {
        return &D_80113474;
    }
    if (temp_v0 < 0x190) {
        return &D_801134B0;
    }
    if (temp_v0 < 0x19A) {
        return &D_801134FC;
    }
    if (temp_v0 < 0x1AE) {
        return &D_80113530;
    }
    if (temp_v0 < 0x1CC) {
        return &D_80113554;
    }
    if (temp_v0 < 0x1D1) {
        return &D_801135A8;
    }
    if (temp_v0 < 0x1E0) {
        return &D_80113600;
    }
    if (temp_v0 < 0x258) {
        var_v0 = &D_80113694;
        if (!(func_80029178(0xB3) & 0xFF)) {
            return &D_80113650;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x276) {
        if (func_80029178(0x10C) & 0xFF) {
            return &D_80113744;
        }
        var_v0 = &D_801136DC;
        if (func_80029178(0x10D) & 0xFF) {
            return &D_80113770;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x280) {
        return &D_80113724;
    }
    if (temp_v0 < 0x28A) {
        return &D_80113794;
    }
    if (temp_v0 < 0x29E) {
        return &D_801137D8;
    }
    if (temp_v0 < 0x2A8) {
        return &D_8011381C;
    }
    if (temp_v0 < 0x2BC) {
        return &D_8011383C;
    }
    if (temp_v0 < 0x2C6) {
        return &D_8011386C;
    }
    if (temp_v0 < 0x2D0) {
        return &D_801138A4;
    }
    if (temp_v0 < 0x2DA) {
        return &D_801138D0;
    }
    if (temp_v0 < 0x2E4) {
        return &D_80113900;
    }
    if (temp_v0 < 0x2F8) {
        return &D_80113944;
    }
    if (temp_v0 < 0x384) {
        return &D_80113964;
    }
    if (temp_v0 < 0x3A2) {
        return &D_8011399C;
    }
    if (temp_v0 < 0x3AC) {
        var_v0 = &D_80113A28;
        if ((u32) (func_800291B4(0x3B) & 0xFF) < 0xAU) {
            return &D_801139E8;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x3B6) {
        return &D_80113A50;
    }
    if (temp_v0 < 0x3CA) {
        return &D_80113A28;
    }
    if (temp_v0 < 0x3D4) {
        return &D_80113A84;
    }
    if (temp_v0 < 0x3F2) {
        return &D_80113AB0;
    }
    if (temp_v0 < 0x44C) {
        return &D_80113AE0;
    }
    if (temp_v0 < 0x47E) {
        return &D_80113B68;
    }
    if (temp_v0 < 0x492) {
        return &D_80113BA4;
    }
    if (temp_v0 < 0x4B0) {
        return &D_80113BC0;
    }
    if (temp_v0 < 0x4BA) {
        var_v0 = &D_80113C20;
        if (!(func_80029178(0x138) & 0xFF)) {
            return &D_80113BF0;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    if (temp_v0 < 0x636) {
        var_v0 = &D_80113C3C;
        if (!(func_80029178(0x143) & 0xFF)) {
            return &D_80113C20;
        }
        /* Duplicate return node #137. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = &D_80113C7C;
    return var_v0;
}
