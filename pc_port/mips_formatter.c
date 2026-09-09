#include "musashi_boot_memory.h"
#include "musashi_callback_registration.h"
#include "musashi_mips_div.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

static const uint32_t kCrt80010000Words[] = {
#include "80010000_words.inc"
};
static const uint32_t kConstructor800100A0Words[] = {
#include "800100a0_words.inc"
};
static const uint32_t kCaller80010178Words[] = {
#include "80010178_words.inc"
};
static const uint32_t kMain80010214Words[] = {
#include "80010214_words.inc"
};
static const uint32_t kMain80014238Words[] = {
#include "80014238_words.inc"
};
static const uint32_t kMain8001C044Words[] = {
#include "8001c044_words.inc"
};
static const uint32_t kMain80015310Words[] = {
#include "80015310_words.inc"
};
static const uint32_t kMain80028A48Words[] = {
#include "80028a48_words.inc"
};
static const uint32_t kMain80028C50Words[] = {
#include "80028c50_words.inc"
};
static const uint32_t kMain80014928Words[] = {
#include "80014928_words.inc"
};
static const uint32_t kMain8005CE18Words[] = {
#include "8005ce18_words.inc"
};
static const uint32_t kDraw800143ACWords[] = {
#include "800143ac_words.inc"
};
static const uint32_t kMain80014390Words[] = {
#include "80014390_words.inc"
};
static const uint32_t kMain800191A8Words[] = {
#include "800191a8_words.inc"
};
static const uint32_t kMain80010A98Words[] = {
#include "80010a98_words.inc"
};
static const uint32_t kMain800595FCWords[] = {
#include "800595fc_words.inc"
};
static const uint32_t kMain80042610Words[] = {
#include "80042610_words.inc"
};
static const uint32_t kMain800189A8Words[] = {
#include "800189a8_words.inc"
};
static const uint32_t kMain80018A20Words[] = {
#include "80018a20_words.inc"
};
static const uint32_t kMain8005D184Words[] = {
#include "8005d184_words.inc"
};
static const uint32_t kMain8005F704Words[] = {
#include "8005f704_words.inc"
};
static const uint32_t kMain8005D244Words[] = {
#include "8005d244_words.inc"
};
static const uint32_t kMain80028D58Words[] = {
#include "80028d58_words.inc"
};
static const uint32_t kMain80029178Words[] = {
#include "80029178_words.inc"
};
static const uint32_t kMain8005D538Words[] = {
#include "8005d538_words.inc"
};
static const uint32_t kMain8005E188Words[] = {
#include "8005e188_words.inc"
};
static const uint32_t kMain8005D4B8Words[] = {
#include "8005d4b8_words.inc"
};
static const uint32_t kMain8005E79CWords[] = {
#include "8005e79c_words.inc"
};
static const uint32_t kMain80018C64Words[] = {
#include "80018c64_words.inc"
};
static const uint32_t kMain80018F88Words[] = {
#include "80018f88_words.inc"
};
static const uint32_t kMain80018CE8Words[] = {
#include "80018ce8_words.inc"
};
static const uint32_t kMain80018F20Words[] = {
#include "80018f20_words.inc"
};
static const uint32_t kMain80018E9CWords[] = {
#include "80018e9c_words.inc"
};
static const uint32_t kMain800291B4Words[] = {
#include "800291b4_words.inc"
};
static const uint32_t kMain80028D78Words[] = {
#include "80028d78_words.inc"
};
static const uint32_t kMain80015208Words[] = {
#include "80015208_words.inc"
};
static const uint32_t kMain80059BFCWords[] = {
#include "80059bfc_words.inc"
};
static const uint32_t kMain80059CF4Words[] = {
#include "80059cf4_words.inc"
};
static const uint32_t kMain8003500CWords[] = {
#include "8003500c_words.inc"
};
static const uint32_t kMain8002D034Words[] = {
#include "8002d034_words.inc"
};
static const uint32_t kMain8002D240Words[] = {
#include "8002d240_words.inc"
};
static const uint32_t kMain8002D29CWords[] = {
#include "8002d29c_words.inc"
};
static const uint32_t kMain8002DC68Words[] = {
#include "8002dc68_words.inc"
};
static const uint32_t kMain8002DF80Words[] = {
#include "8002df80_words.inc"
};
static const uint32_t kMain8002E138Words[] = {
#include "8002e138_words.inc"
};
static const uint32_t kMain8002E5BCWords[] = {
#include "8002e5bc_words.inc"
};
static const uint32_t kMain8002E5F8Words[] = {
#include "8002e5f8_words.inc"
};
static const uint32_t kMain8002E638Words[] = {
#include "8002e638_words.inc"
};
static const uint32_t kMain8002E700Words[] = {
#include "8002e700_words.inc"
};
static const uint32_t kMain8002E79CWords[] = {
#include "8002e79c_words.inc"
};
static const uint32_t kMain8002E818Words[] = {
#include "8002e818_words.inc"
};
static const uint32_t kMain8002E8DCWords[] = {
#include "8002e8dc_words.inc"
};
static const uint32_t kMain8002E94CWords[] = {
#include "8002e94c_words.inc"
};
static const uint32_t kMain8002EA10Words[] = {
#include "8002ea10_words.inc"
};
static const uint32_t kMain8002EAB0Words[] = {
#include "8002eab0_words.inc"
};
static const uint32_t kMain8002EB10Words[] = {
#include "8002eb10_words.inc"
};
static const uint32_t kMain8002EBACWords[] = {
#include "8002ebac_words.inc"
};
static const uint32_t kMain8002EDE4Words[] = {
#include "8002ede4_words.inc"
};
static const uint32_t kMain8002EE90Words[] = {
#include "8002ee90_words.inc"
};
static const uint32_t kMain8002EEB8Words[] = {
#include "8002eeb8_words.inc"
};
static const uint32_t kMain8002EED8Words[] = {
#include "8002eed8_words.inc"
};
static const uint32_t kMain8002EFD0Words[] = {
#include "8002efd0_words.inc"
};
static const uint32_t kMain8002F0D0Words[] = {
#include "8002f0d0_words.inc"
};
static const uint32_t kMain8002F248Words[] = {
#include "8002f248_words.inc"
};
static const uint32_t kMain8002F4E4Words[] = {
#include "8002f4e4_words.inc"
};
static const uint32_t kMain8002F714Words[] = {
#include "8002f714_words.inc"
};
static const uint32_t kMain80031B7CWords[] = {
#include "80031b7c_words.inc"
};
static const uint32_t kMain80031CC8Words[] = {
#include "80031cc8_words.inc"
};
static const uint32_t kMain80031DECWords[] = {
#include "80031dec_words.inc"
};
static const uint32_t kMain80031E94Words[] = {
#include "80031e94_words.inc"
};
static const uint32_t kMain80031F14Words[] = {
#include "80031f14_words.inc"
};
static const uint32_t kMain80031FC8Words[] = {
#include "80031fc8_words.inc"
};
static const uint32_t kMain80032048Words[] = {
#include "80032048_words.inc"
};
static const uint32_t kMain800322A8Words[] = {
#include "800322a8_words.inc"
};
static const uint32_t kMain800324A4Words[] = {
#include "800324a4_words.inc"
};
static const uint32_t kMain80032774Words[] = {
#include "80032774_words.inc"
};
static const uint32_t kMain80032A74Words[] = {
#include "80032a74_words.inc"
};
static const uint32_t kMain8003310CWords[] = {
#include "8003310c_words.inc"
};
static const uint32_t kMain800331D4Words[] = {
#include "800331d4_words.inc"
};
static const uint32_t kMain8003324CWords[] = {
#include "8003324c_words.inc"
};
static const uint32_t kMain80033398Words[] = {
#include "80033398_words.inc"
};
static const uint32_t kMain8003350CWords[] = {
#include "8003350c_words.inc"
};
static const uint32_t kMain800335B8Words[] = {
#include "800335b8_words.inc"
};
static const uint32_t kMain80034314Words[] = {
#include "80034314_words.inc"
};
static const uint32_t kMain800346D0Words[] = {
#include "800346d0_words.inc"
};
static const uint32_t kMain80034844Words[] = {
#include "80034844_words.inc"
};
static const uint32_t kMain800348A8Words[] = {
#include "800348a8_words.inc"
};
static const uint32_t kMain8003491CWords[] = {
#include "8003491c_words.inc"
};
static const uint32_t kMain80034A54Words[] = {
#include "80034a54_words.inc"
};
static const uint32_t kMain80034A9CWords[] = {
#include "80034a9c_words.inc"
};
static const uint32_t kMain80034AE0Words[] = {
#include "80034ae0_words.inc"
};
static const uint32_t kMain80034B0CWords[] = {
#include "80034b0c_words.inc"
};
static const uint32_t kMain80034CF0Words[] = {
#include "80034cf0_words.inc"
};
static const uint32_t kMain80034DFCWords[] = {
#include "80034dfc_words.inc"
};
static const uint32_t kMain80036D58Words[] = {
#include "80036d58_words.inc"
};
static const uint32_t kMain80036EB4Words[] = {
#include "80036eb4_words.inc"
};
static const uint32_t kMain80036EE8Words[] = {
#include "80036ee8_words.inc"
};
static const uint32_t kMain80036F18Words[] = {
#include "80036f18_words.inc"
};
static const uint32_t kMain800381E4Words[] = {
#include "800381e4_words.inc"
};
static const uint32_t kMain800383A4Words[] = {
#include "800383a4_words.inc"
};
static const uint32_t kMain800384A8Words[] = {
#include "800384a8_words.inc"
};
static const uint32_t kMain800385C0Words[] = {
#include "800385c0_words.inc"
};
static const uint32_t kMain80038668Words[] = {
#include "80038668_words.inc"
};
static const uint32_t kMain80038698Words[] = {
#include "80038698_words.inc"
};
static const uint32_t kMain800387C0Words[] = {
#include "800387c0_words.inc"
};
static const uint32_t kMain80038838Words[] = {
#include "80038838_words.inc"
};
static const uint32_t kMain80038908Words[] = {
#include "80038908_words.inc"
};
static const uint32_t kMain8003916CWords[] = {
#include "8003916c_words.inc"
};
static const uint32_t kMain8003AB84Words[] = {
#include "8003ab84_words.inc"
};
static const uint32_t kMain8003AF4CWords[] = {
#include "8003af4c_words.inc"
};
static const uint32_t kMain8003B08CWords[] = {
#include "8003b08c_words.inc"
};
static const uint32_t kMain8003B0B8Words[] = {
#include "8003b0b8_words.inc"
};
static const uint32_t kMain8003C0A0Words[] = {
#include "8003c0a0_words.inc"
};
static const uint32_t kMain8003C92CWords[] = {
#include "8003c92c_words.inc"
};
static const uint32_t kMain8003CFF8Words[] = {
#include "8003cff8_words.inc"
};
static const uint32_t kMain8003EDE8Words[] = {
#include "8003ede8_words.inc"
};
static const uint32_t kMain80043974Words[] = {
#include "80043974_words.inc"
};
static const uint32_t kMain80044A8CWords[] = {
#include "80044a8c_words.inc"
};
static const uint32_t kMain8005CE98Words[] = {
#include "8005ce98_words.inc"
};
static const uint32_t kMain8001A0FCWords[] = {
#include "8001a0fc_words.inc"
};
static const uint32_t kMain8001A114Words[] = {
#include "8001a114_words.inc"
};
static const uint32_t kMain8001AF34Words[] = {
#include "8001af34_words.inc"
};
static const uint32_t kMain8001B0D4Words[] = {
#include "8001b0d4_words.inc"
};
static const uint32_t kMain8001B394Words[] = {
#include "8001b394_words.inc"
};
static const uint32_t kMain8001B3C4Words[] = {
#include "8001b3c4_words.inc"
};
static const uint32_t kMain8001B710Words[] = {
#include "8001b710_words.inc"
};
static const uint32_t kMain8001B788Words[] = {
#include "8001b788_words.inc"
};
static const uint32_t kMain8001B7C4Words[] = {
#include "8001b7c4_words.inc"
};
static const uint32_t kMain8002D4C8Words[] = {
#include "8002d4c8_words.inc"
};
static const uint32_t kMain8002D7FCWords[] = {
#include "8002d7fc_words.inc"
};
static const uint32_t kMain8002ED90Words[] = {
#include "8002ed90_words.inc"
};
static const uint32_t kMain8002FD14Words[] = {
#include "8002fd14_words.inc"
};
static const uint32_t kMain8002FDE8Words[] = {
#include "8002fde8_words.inc"
};
static const uint32_t kMain8002FF0CWords[] = {
#include "8002ff0c_words.inc"
};
static const uint32_t kMain80030730Words[] = {
#include "80030730_words.inc"
};
static const uint32_t kMain80030A14Words[] = {
#include "80030a14_words.inc"
};
static const uint32_t kMain80031A98Words[] = {
#include "80031a98_words.inc"
};
static const uint32_t kMain800363CCWords[] = {
#include "800363cc_words.inc"
};
static const uint32_t kMain80036AF8Words[] = {
#include "80036af8_words.inc"
};
static const uint32_t kMain80037144Words[] = {
#include "80037144_words.inc"
};
static const uint32_t kMain80037334Words[] = {
#include "80037334_words.inc"
};
static const uint32_t kMain80037358Words[] = {
#include "80037358_words.inc"
};
static const uint32_t kMain80037368Words[] = {
#include "80037368_words.inc"
};
static const uint32_t kMain800373D0Words[] = {
#include "800373d0_words.inc"
};
static const uint32_t kMain800374CCWords[] = {
#include "800374cc_words.inc"
};
static const uint32_t kMain8003750CWords[] = {
#include "8003750c_words.inc"
};
static const uint32_t kMain800377D8Words[] = {
#include "800377d8_words.inc"
};
static const uint32_t kMain8003775CWords[] = {
#include "8003775c_words.inc"
};
static const uint32_t kMain80037CD8Words[] = {
#include "80037cd8_words.inc"
};
static const uint32_t kMain80037D74Words[] = {
#include "80037d74_words.inc"
};
static const uint32_t kMain800401CCWords[] = {
#include "800401cc_words.inc"
};
static const uint32_t kMain800415A8Words[] = {
#include "800415a8_words.inc"
};
static const uint32_t kMain8004162CWords[] = {
#include "8004162c_words.inc"
};
static const uint32_t kMain800416A8Words[] = {
#include "800416a8_words.inc"
};
static const uint32_t kMain800419B0Words[] = {
#include "800419b0_words.inc"
};
static const uint32_t kMain80041A80Words[] = {
#include "80041a80_words.inc"
};
static const uint32_t kMain80041AB0Words[] = {
#include "80041ab0_words.inc"
};
static const uint32_t kMain80041E8CWords[] = {
#include "80041e8c_words.inc"
};
static const uint32_t kMain80042374Words[] = {
#include "80042374_words.inc"
};
static const uint32_t kMain800439D4Words[] = {
#include "800439d4_words.inc"
};
static const uint32_t kMain80046630Words[] = {
#include "80046630_words.inc"
};
static const uint32_t kMain8004674CWords[] = {
#include "8004674c_words.inc"
};
static const uint32_t kMain8001AAA0Words[] = {
#include "8001aaa0_words.inc"
};
static const uint32_t kMain80014CACWords[] = {
#include "80014cac_words.inc"
};
static const uint32_t kMain8001AA98Words[] = {
#include "8001aa98_words.inc"
};
static const uint32_t kMain8001534CWords[] = {
#include "8001534c_words.inc"
};
static const uint32_t kMain800153A4Words[] = {
#include "800153a4_words.inc"
};
static const uint32_t kMain80010DA0Words[] = {
#include "80010da0_words.inc"
};
static const uint32_t kMain800110CCWords[] = {
#include "800110cc_words.inc"
};
static const uint32_t kMain80011220Words[] = {
#include "80011220_words.inc"
};
static const uint32_t kMain8001125CWords[] = {
#include "8001125c_words.inc"
};
static const uint32_t kMain800111BCWords[] = {
#include "800111bc_words.inc"
};
static const uint32_t kMain80011144Words[] = {
#include "80011144_words.inc"
};
static const uint32_t kMain8001A9F8Words[] = {
#include "8001a9f8_words.inc"
};
static const uint32_t kMain80010F80Words[] = {
#include "80010f80_words.inc"
};
static const uint32_t kMain80029514Words[] = {
#include "80029514_words.inc"
};
static const uint32_t kMain80010ED4Words[] = {
#include "80010ed4_words.inc"
};
static const uint32_t kMain80014338Words[] = {
#include "80014338_words.inc"
};
static const uint32_t kMain80010D60Words[] = {
#include "80010d60_words.inc"
};
static const uint32_t kMain8002FDC8Words[] = {
#include "8002fdc8_words.inc"
};
static const uint32_t kMain8002FC64Words[] = {
#include "8002fc64_words.inc"
};
static const uint32_t kMain8003C438Words[] = {
#include "8003c438_words.inc"
};
static const uint32_t kMain8003C498Words[] = {
#include "8003c498_words.inc"
};
static const uint32_t kMain8003AE14Words[] = {
#include "8003ae14_words.inc"
};
static const uint32_t kMain800301A4Words[] = {
#include "800301a4_words.inc"
};
static const uint32_t kMain8002FB08Words[] = {
#include "8002fb08_words.inc"
};
static const uint32_t kMain8001ABBCWords[] = {
#include "8001abbc_words.inc"
};
static const uint32_t kMain8001ACF0Words[] = {
#include "8001acf0_words.inc"
};
static const uint32_t kMain8001AE90Words[] = {
#include "8001ae90_words.inc"
};
static const uint32_t kMain800149E0Words[] = {
#include "800149e0_words.inc"
};
static const uint32_t kMain80014C28Words[] = {
#include "80014c28_words.inc"
};
static const uint32_t kMain80014D30Words[] = {
#include "80014d30_words.inc"
};
static const uint32_t kMain80014CF8Words[] = {
#include "80014cf8_words.inc"
};
static const uint32_t kMain800167F0Words[] = {
#include "800167f0_words.inc"
};
static const uint32_t kMain80053290Words[] = {
#include "80053290_words.inc"
};
static const uint32_t kMain800553D8Words[] = {
#include "800553d8_words.inc"
};
static const uint32_t kMain800553F4Words[] = {
#include "800553f4_words.inc"
};
static const uint32_t kMain8001C9D0Words[] = {
#include "8001c9d0_words.inc"
};
static const uint32_t kMain8001C2C4Words[] = {
#include "8001c2c4_words.inc"
};
static const uint32_t kMain8001C320Words[] = {
#include "8001c320_words.inc"
};
static const uint32_t kMain800285ACWords[] = {
#include "800285ac_words.inc"
};
static const uint32_t kMain8005C4CCWords[] = {
#include "8005c4cc_words.inc"
};
static const uint32_t kMain80011E24Words[] = {
#include "80011e24_words.inc"
};
static const uint32_t kMain800295D4Words[] = {
#include "800295d4_words.inc"
};
static const uint32_t kMain80029664Words[] = {
#include "80029664_words.inc"
};
static const uint32_t kMain80011380Words[] = {
#include "80011380_words.inc"
};
static const uint32_t kMain800118ACWords[] = {
#include "800118ac_words.inc"
};
static const uint32_t kMain80010A84Words[] = {
#include "80010a84_words.inc"
};
static const uint32_t kMain800146B0Words[] = {
#include "800146b0_words.inc"
};
static const uint32_t kMain800527C4Words[] = {
#include "800527c4_words.inc"
};
static const uint32_t kMain80053EECWords[] = {
#include "80053eec_words.inc"
};
static const uint32_t kMain8001BFF8Words[] = {
#include "8001bff8_words.inc"
};
static const uint32_t kMain80011928Words[] = {
#include "80011928_words.inc"
};
static const uint32_t kMain8001BFE8Words[] = {
#include "8001bfe8_words.inc"
};
static const uint32_t kMain800116E0Words[] = {
#include "800116e0_words.inc"
};
static const uint32_t kMain80029000Words[] = {
#include "80029000_words.inc"
};
static const uint32_t kMain80028D9CWords[] = {
#include "80028d9c_words.inc"
};
static const uint32_t kMain80028FBCWords[] = {
#include "80028fbc_words.inc"
};
static const uint32_t kMain800183E0Words[] = {
#include "800183e0_words.inc"
};
static const uint32_t kMain800167B8Words[] = {
#include "800167b8_words.inc"
};
static const uint32_t kMain80016224Words[] = {
#include "80016224_words.inc"
};
static const uint32_t kMain80010A08Words[] = {
#include "80010a08_words.inc"
};
static const uint32_t kMain80016638Words[] = {
#include "80016638_words.inc"
};
static const uint32_t kMain80010CECWords[] = {
#include "80010cec_words.inc"
};
static const uint32_t kMain80011818Words[] = {
#include "80011818_words.inc"
};
static const uint32_t kMain80011A3CWords[] = {
#include "80011a3c_words.inc"
};
/* MAIN.CD member0000 at base 800CE5F8, file offset 0x804. Live RAM at STOP
 * matched these 17 words. Not EXE-sourced; overlay bytes are the authority. */
static const uint32_t kOverlay800CEDFCWords[] = {
    0x3c03800cu, 0x946399e4u, 0x27bdffe8u, 0x2c620008u,
    0x10400008u, 0xafbf0010u, 0x00031080u, 0x3c01800du,
    0x00220821u, 0x8c22f450u, 0x00000000u, 0x0040f809u,
    0x00000000u, 0x8fbf0010u, 0x27bd0018u, 0x03e00008u,
    0x00000000u
};
_Static_assert(sizeof(kOverlay800CEDFCWords) / sizeof(uint32_t) == 17,
               "overlay 800CEDFC source span changed");
/* MAIN.CD member0007 at base 800CEDF8, file offset 0x34. Full func_800CEE2C
 * (prologue + A3B4 dispatcher + table[0..3]). 80010F80 jals 800CEEC8
 * mid-function; native redirects that jal to 800CEE2C so ra is saved. */
static const uint32_t kOverlay800CEE2CWords[] = {
    0x27bdffe0u, 0x24040001u, 0x3c02800du, 0x2442fabfu,
    0x2445fff5u, 0x24060060u, 0x3c03800cu, 0x906399e4u,
    0x24070064u, 0xafbf001cu, 0xafb00018u, 0xafa00010u,
    0xafa00014u, 0x24630030u, 0x0c0054d3u, 0xa0430000u,
    0x3c02800du, 0x8c421364u, 0x3c10800bu, 0x2610f630u,
    0x10400005u, 0x24040002u, 0x3c05800du, 0x24a5fac4u,
    0x08033ba9u, 0x24060060u, 0x24040003u, 0x3c05800du,
    0x24a5fad4u, 0x24060060u, 0x24070070u, 0xafa00010u,
    0x0c0054d3u, 0xafa00014u, 0x3c010001u, 0x02010821u,
    0x9423a3b4u, 0x00000000u, 0x2c620004u, 0x10400007u,
    0x00031080u, 0x3c01800du, 0x00220821u, 0x8c22fadcu,
    0x00000000u, 0x0040f809u, 0x00000000u, 0x8fbf001cu,
    0x8fb00018u, 0x27bd0020u, 0x03e00008u, 0x00000000u,
    0x27bdffe8u, 0x24020001u, 0xafbf0010u, 0x3c01800cu,
    0xa0229a11u, 0x0c007011u, 0x00000000u, 0x0c0054c4u,
    0x00000000u, 0x3c04800du, 0x2484130cu, 0x3c01800du,
    0xac201364u, 0x0c0060f8u, 0x00000000u, 0x0c0059eeu,
    0x00002021u, 0x3c01800cu, 0xa42099e8u, 0x0c00462bu,
    0x00000000u, 0x8fbf0010u, 0x27bd0018u, 0x03e00008u,
    0x00000000u, 0x27bdffe8u, 0xafbf0010u, 0x0c0059fcu,
    0x00002021u, 0x3042ffffu, 0x10400003u, 0x00000000u,
    0x0c00462bu, 0x00000000u, 0x8fbf0010u, 0x27bd0018u,
    0x03e00008u, 0x00000000u, 0x3c02800cu, 0x944299e8u,
    0x27bdffe8u, 0xafbf0010u, 0x24420001u, 0x3c01800cu,
    0xa42299e8u, 0x00021400u, 0x00021403u, 0x28420081u,
    0x10400006u, 0x00002021u, 0x0c00532bu, 0x24050800u,
    0x00021400u, 0x10400005u, 0x00000000u, 0x0c0059eeu,
    0x24040004u, 0x0c00462bu, 0x00000000u, 0x8fbf0010u,
    0x27bd0018u, 0x03e00008u, 0x00000000u, 0x27bdffe8u,
    0xafbf0010u, 0x0c0059fcu, 0x24040004u, 0x3042ffffu,
    0x10400003u, 0x24020001u, 0x3c01800cu, 0xa42299e6u,
    0x8fbf0010u, 0x27bd0018u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CEE2CWords) / sizeof(uint32_t) == 128,
               "overlay 800CEE2C source span changed");
/* Remainder of member0007 after 800CEE2C: 800CF02C dispatcher through
 * file end 800D1378 (OPDEMO0.PAT request, Start → A3B6). */
static const uint32_t kOverlay800CF02CWords[] = {
#include "800cf02c_overlay_words.inc"
};
_Static_assert(sizeof(kOverlay800CF02CWords) / sizeof(uint32_t) == 2259,
               "overlay 800CF02C source span changed");
static int g_overlay_0004_words;
static int g_overlay_0007_words;
static int g_overlay_0010_words;
static const uint32_t kOverlay0010_800CEDFCWords[] = {
#include "800cedfc_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CEDFCWords) / sizeof(uint32_t) == 194,
               "overlay 0010 800CEDFC source span changed");
static const uint32_t kOverlay0010_800CFBBCWords[] = {
#include "800cfbbc_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CFBBCWords) / sizeof(uint32_t) == 4, "overlay 0010 CFBBC span changed");
static const uint32_t kOverlay0010_800D0488Words[] = {
#include "800d0488_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800D0488Words) / sizeof(uint32_t) == 64, "overlay 0010 800D0488 span changed");
static const uint32_t kOverlay0010_800CF370Words[] = {
#include "800cf370_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF370Words) / sizeof(uint32_t) == 10, "overlay 0010 800CF370 span changed");
static const uint32_t kOverlay0010_800CF398Words[] = {
#include "800cf398_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF398Words) / sizeof(uint32_t) == 8, "overlay 0010 800CF398 span changed");
static const uint32_t kOverlay0010_800CF3B8Words[] = {
#include "800cf3b8_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF3B8Words) / sizeof(uint32_t) == 49, "overlay 0010 800CF3B8 span changed");
static const uint32_t kOverlay0010_800CF47CWords[] = {
#include "800cf47c_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF47CWords) / sizeof(uint32_t) == 22, "overlay 0010 800CF47C span changed");
static const uint32_t kOverlay0010_800CF4D4Words[] = {
#include "800cf4d4_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF4D4Words) / sizeof(uint32_t) == 204, "overlay 0010 800CF4D4 span changed");
static const uint32_t kOverlay0010_800CFBF8Words[] = {
#include "800cfbf8_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CFBF8Words) / sizeof(uint32_t) == 124, "overlay 0010 800CFBF8 span changed");
static const uint32_t kOverlay0010_800CFE60Words[] = {
#include "800cfe60_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CFE60Words) / sizeof(uint32_t) == 237, "overlay 0010 800CFE60 span changed");
static const uint32_t kOverlay0010_800CF94CWords[] = {
#include "800cf94c_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF94CWords) / sizeof(uint32_t) == 17,
               "overlay 0010 800CF94C source span changed");
static const uint32_t kOverlaySc02_80128420Words[] = {
#include "80128420_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129220Words[] = {
#include "80129220_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129248Words[] = {
#include "80129248_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129258Words[] = {
#include "80129258_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801378F0Words[] = {
#include "801378f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A860Words[] = {
#include "8013a860_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128C14Words[] = {
#include "80128c14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C98CWords[] = {
#include "8013c98c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129C40Words[] = {
#include "80129c40_sc02_0031_words.inc"
};
static const uint32_t kOverlay0010_800D05E8Words[] = {
#include "800d05e8_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D0588Words[] = {
#include "800d0588_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800CF854Words[] = {
#include "800cf854_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D1E20Words[] = {
#include "800d1e20_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D18DCWords[] = {
#include "800d18dc_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800D18DCWords) / sizeof(uint32_t) == 23,
               "overlay 0010 800D18DC source span changed");
static const uint32_t kOverlay0010_800D1938Words[] = {
#include "800d1938_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800D1938Words) / sizeof(uint32_t) == 19,
               "overlay 0010 800D1938 source span changed");
static const uint32_t kOverlay0010_800D1984Words[] = {
#include "800d1984_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800D1984Words) / sizeof(uint32_t) == 22,
               "overlay 0010 800D1984 source span changed");
static const uint32_t kOverlay0010_800D1F58Words[] = {
#include "800d1f58_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800D1F58Words) / sizeof(uint32_t) == 14,
               "overlay 0010 800D1F58 source span changed");
static const uint32_t kOverlay0010_800D02C0Words[] = {
#include "800d02c0_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D0630Words[] = {
#include "800d0630_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D065CWords[] = {
#include "800d065c_overlay0010_words.inc"
};
static const uint32_t kOverlaySc02_80145CECWords[] = {
#include "80145cec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801552F4Words[] = {
#include "801552f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147084Words[] = {
#include "80147084_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147098Words[] = {
#include "80147098_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801470ACWords[] = {
#include "801470ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016533CWords[] = {
#include "8016533c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801659DCWords[] = {
#include "801659dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165A18Words[] = {
#include "80165a18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801627C0Words[] = {
#include "801627c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162AF4Words[] = {
#include "80162af4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165C78Words[] = {
#include "80165c78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801468C8Words[] = {
#include "801468c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145EE8Words[] = {
#include "80145ee8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146014Words[] = {
#include "80146014_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C968Words[] = {
#include "8014c968_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C6D0Words[] = {
#include "8014c6d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165938Words[] = {
#include "80165938_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C8CWords[] = {
#include "80153c8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144B9CWords[] = {
#include "80144b9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801457A4Words[] = {
#include "801457a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80180D74Words[] = {
#include "80180d74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80180DB0Words[] = {
#include "80180db0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181224Words[] = {
#include "80181224_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EE40Words[] = {
#include "8016ee40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EF78Words[] = {
#include "8016ef78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8018129CWords[] = {
#include "8018129c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A018Words[] = {
#include "8012a018_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A048Words[] = {
#include "8012a048_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A094Words[] = {
#include "8012a094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8018133CWords[] = {
#include "8018133c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181378Words[] = {
#include "80181378_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801814E4Words[] = {
#include "801814e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B83CWords[] = {
#include "8013b83c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D53CWords[] = {
#include "8013d53c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D8FCWords[] = {
#include "8013d8fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CF68Words[] = {
#include "8013cf68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801832F4Words[] = {
#include "801832f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183314Words[] = {
#include "80183314_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183458Words[] = {
#include "80183458_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183808Words[] = {
#include "80183808_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183810Words[] = {
#include "80183810_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183A20Words[] = {
#include "80183a20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183BB0Words[] = {
#include "80183bb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183D84Words[] = {
#include "80183d84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183DC0Words[] = {
#include "80183dc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80183FECWords[] = {
#include "80183fec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184028Words[] = {
#include "80184028_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8018418CWords[] = {
#include "8018418c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184318Words[] = {
#include "80184318_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181868Words[] = {
#include "80181868_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181938Words[] = {
#include "80181938_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801843B4Words[] = {
#include "801843b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801843F0Words[] = {
#include "801843f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801844C4Words[] = {
#include "801844c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801844ECWords[] = {
#include "801844ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801844F4Words[] = {
#include "801844f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184640Words[] = {
#include "80184640_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C354Words[] = {
#include "8012c354_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C438Words[] = {
#include "8012c438_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C51CWords[] = {
#include "8012c51c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C588Words[] = {
#include "8012c588_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CB7CWords[] = {
#include "8017cb7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CBB8Words[] = {
#include "8017cbb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CC04Words[] = {
#include "8017cc04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CCF8Words[] = {
#include "8017ccf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CD78Words[] = {
#include "8017cd78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CE2CWords[] = {
#include "8017ce2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CE98Words[] = {
#include "8017ce98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CF24Words[] = {
#include "8017cf24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CF44Words[] = {
#include "8017cf44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CF98Words[] = {
#include "8017cf98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017CFD4Words[] = {
#include "8017cfd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017E39CWords[] = {
#include "8017e39c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017E538Words[] = {
#include "8017e538_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017E73CWords[] = {
#include "8017e73c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017EB30Words[] = {
#include "8017eb30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017ECB0Words[] = {
#include "8017ecb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017EE3CWords[] = {
#include "8017ee3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F050Words[] = {
#include "8017f050_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F124Words[] = {
#include "8017f124_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F24CWords[] = {
#include "8017f24c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F3C0Words[] = {
#include "8017f3c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017C2B0Words[] = {
#include "8017c2b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017C63CWords[] = {
#include "8017c63c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017C8B4Words[] = {
#include "8017c8b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017C9FCWords[] = {
#include "8017c9fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801788B8Words[] = {
#include "801788b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C658Words[] = {
#include "8012c658_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E8E0Words[] = {
#include "8012e8e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144988Words[] = {
#include "80144988_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801449C8Words[] = {
#include "801449c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144A04Words[] = {
#include "80144a04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144A2CWords[] = {
#include "80144a2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144A68Words[] = {
#include "80144a68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144A90Words[] = {
#include "80144a90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144A98Words[] = {
#include "80144a98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144AECWords[] = {
#include "80144aec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144B14Words[] = {
#include "80144b14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD44Words[] = {
#include "8012ad44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801848A8Words[] = {
#include "801848a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801848E4Words[] = {
#include "801848e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8018496CWords[] = {
#include "8018496c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184A2CWords[] = {
#include "80184a2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184A9CWords[] = {
#include "80184a9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80184B94Words[] = {
#include "80184b94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143970Words[] = {
#include "80143970_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801439FCWords[] = {
#include "801439fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143B6CWords[] = {
#include "80143b6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143CD4Words[] = {
#include "80143cd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143D28Words[] = {
#include "80143d28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143EB4Words[] = {
#include "80143eb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143EBCWords[] = {
#include "80143ebc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144054Words[] = {
#include "80144054_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144090Words[] = {
#include "80144090_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801442F8Words[] = {
#include "801442f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144364Words[] = {
#include "80144364_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144458Words[] = {
#include "80144458_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144558Words[] = {
#include "80144558_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014462CWords[] = {
#include "8014462c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801446A4Words[] = {
#include "801446a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014477CWords[] = {
#include "8014477c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80144880Words[] = {
#include "80144880_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801458E0Words[] = {
#include "801458e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801458E8Words[] = {
#include "801458e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145934Words[] = {
#include "80145934_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145A2CWords[] = {
#include "80145a2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145B24Words[] = {
#include "80145b24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145BF8Words[] = {
#include "80145bf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80145C54Words[] = {
#include "80145c54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A828Words[] = {
#include "8012a828_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C218Words[] = {
#include "8012c218_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AAACWords[] = {
#include "8012aaac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012ACA0Words[] = {
#include "8012aca0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182070Words[] = {
#include "80182070_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182078Words[] = {
#include "80182078_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801820E0Words[] = {
#include "801820e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182174Words[] = {
#include "80182174_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801821F4Words[] = {
#include "801821f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182328Words[] = {
#include "80182328_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801824E4Words[] = {
#include "801824e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801825E0Words[] = {
#include "801825e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182618Words[] = {
#include "80182618_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182674Words[] = {
#include "80182674_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182848Words[] = {
#include "80182848_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182994Words[] = {
#include "80182994_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801829A0Words[] = {
#include "801829a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801829A8Words[] = {
#include "801829a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801829BCWords[] = {
#include "801829bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801829F8Words[] = {
#include "801829f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182A7CWords[] = {
#include "80182a7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182AB4Words[] = {
#include "80182ab4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182B64Words[] = {
#include "80182b64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182BA0Words[] = {
#include "80182ba0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182BE0Words[] = {
#include "80182be0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182C24Words[] = {
#include "80182c24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182C60Words[] = {
#include "80182c60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80182CF4Words[] = {
#include "80182cf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801832D0Words[] = {
#include "801832d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CAE4Words[] = {
#include "8012cae4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B2CCWords[] = {
#include "8012b2cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B14CWords[] = {
#include "8012b14c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181EF0Words[] = {
#include "80181ef0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181BB4Words[] = {
#include "80181bb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181B78Words[] = {
#include "80181b78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD50Words[] = {
#include "8012ad50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181A24Words[] = {
#include "80181a24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801819E8Words[] = {
#include "801819e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181F5CWords[] = {
#include "80181f5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181FA4Words[] = {
#include "80181fa4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181F20Words[] = {
#include "80181f20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C194Words[] = {
#include "8012c194_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C1B8Words[] = {
#include "8012c1b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C1DCWords[] = {
#include "8012c1dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013221CWords[] = {
#include "8013221c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131FDCWords[] = {
#include "80131fdc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C890Words[] = {
#include "8012c890_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C750Words[] = {
#include "8012c750_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E4B4Words[] = {
#include "8013e4b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178608Words[] = {
#include "80178608_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128564Words[] = {
#include "80128564_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801285D4Words[] = {
#include "801285d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801285E4Words[] = {
#include "801285e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128714Words[] = {
#include "80128714_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801287B8Words[] = {
#include "801287b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801288E8Words[] = {
#include "801288e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128A28Words[] = {
#include "80128a28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128AF4Words[] = {
#include "80128af4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146074Words[] = {
#include "80146074_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014607CWords[] = {
#include "8014607c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146128Words[] = {
#include "80146128_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146360Words[] = {
#include "80146360_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801463A0Words[] = {
#include "801463a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146534Words[] = {
#include "80146534_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146554Words[] = {
#include "80146554_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146578Words[] = {
#include "80146578_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014659CWords[] = {
#include "8014659c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801465C0Words[] = {
#include "801465c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801465E4Words[] = {
#include "801465e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146608Words[] = {
#include "80146608_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801466B4Words[] = {
#include "801466b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801466F0Words[] = {
#include "801466f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146750Words[] = {
#include "80146750_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014680CWords[] = {
#include "8014680c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146924Words[] = {
#include "80146924_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146994Words[] = {
#include "80146994_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801469C8Words[] = {
#include "801469c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146A6CWords[] = {
#include "80146a6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146AB4Words[] = {
#include "80146ab4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146AFCWords[] = {
#include "80146afc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146B9CWords[] = {
#include "80146b9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146C3CWords[] = {
#include "80146c3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146C98Words[] = {
#include "80146c98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146CA0Words[] = {
#include "80146ca0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146CB4Words[] = {
#include "80146cb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146CC8Words[] = {
#include "80146cc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146D30Words[] = {
#include "80146d30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146D80Words[] = {
#include "80146d80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146D90Words[] = {
#include "80146d90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146DB8Words[] = {
#include "80146db8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146DE8Words[] = {
#include "80146de8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146DF8Words[] = {
#include "80146df8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146E90Words[] = {
#include "80146e90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146E98Words[] = {
#include "80146e98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146EC0Words[] = {
#include "80146ec0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146F58Words[] = {
#include "80146f58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80146FC4Words[] = {
#include "80146fc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014704CWords[] = {
#include "8014704c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147054Words[] = {
#include "80147054_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147060Words[] = {
#include "80147060_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014706CWords[] = {
#include "8014706c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147078Words[] = {
#include "80147078_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014708CWords[] = {
#include "8014708c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801470A0Words[] = {
#include "801470a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801470B4Words[] = {
#include "801470b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801470C0Words[] = {
#include "801470c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147118Words[] = {
#include "80147118_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147264Words[] = {
#include "80147264_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147290Words[] = {
#include "80147290_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801472B4Words[] = {
#include "801472b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801472C8Words[] = {
#include "801472c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801472DCWords[] = {
#include "801472dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801472F0Words[] = {
#include "801472f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147300Words[] = {
#include "80147300_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147324Words[] = {
#include "80147324_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147364Words[] = {
#include "80147364_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801473DCWords[] = {
#include "801473dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801473ECWords[] = {
#include "801473ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147460Words[] = {
#include "80147460_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147478Words[] = {
#include "80147478_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801474D8Words[] = {
#include "801474d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801474ECWords[] = {
#include "801474ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147514Words[] = {
#include "80147514_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147628Words[] = {
#include "80147628_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147718Words[] = {
#include "80147718_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147788Words[] = {
#include "80147788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801477A8Words[] = {
#include "801477a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801477C8Words[] = {
#include "801477c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801477E8Words[] = {
#include "801477e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147814Words[] = {
#include "80147814_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147860Words[] = {
#include "80147860_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801478B8Words[] = {
#include "801478b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147928Words[] = {
#include "80147928_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147948Words[] = {
#include "80147948_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014799CWords[] = {
#include "8014799c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801479BCWords[] = {
#include "801479bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147A10Words[] = {
#include "80147a10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147A30Words[] = {
#include "80147a30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147A84Words[] = {
#include "80147a84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147AACWords[] = {
#include "80147aac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147AD4Words[] = {
#include "80147ad4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147B18Words[] = {
#include "80147b18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147B5CWords[] = {
#include "80147b5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147C30Words[] = {
#include "80147c30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147CC8Words[] = {
#include "80147cc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147D38Words[] = {
#include "80147d38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147DC0Words[] = {
#include "80147dc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147E44Words[] = {
#include "80147e44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147F50Words[] = {
#include "80147f50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80147F78Words[] = {
#include "80147f78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148038Words[] = {
#include "80148038_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148094Words[] = {
#include "80148094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801483E8Words[] = {
#include "801483e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801484B0Words[] = {
#include "801484b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801484E8Words[] = {
#include "801484e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148534Words[] = {
#include "80148534_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014856CWords[] = {
#include "8014856c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801485B8Words[] = {
#include "801485b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148634Words[] = {
#include "80148634_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148648Words[] = {
#include "80148648_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801487F4Words[] = {
#include "801487f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012853CWords[] = {
#include "8012853c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175494Words[] = {
#include "80175494_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E8F0Words[] = {
#include "8016e8f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178004Words[] = {
#include "80178004_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80176144Words[] = {
#include "80176144_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178298Words[] = {
#include "80178298_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80177940Words[] = {
#include "80177940_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80177B5CWords[] = {
#include "80177b5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80177EA4Words[] = {
#include "80177ea4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801770E0Words[] = {
#include "801770e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801777BCWords[] = {
#include "801777bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801783D0Words[] = {
#include "801783d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80177784Words[] = {
#include "80177784_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80176D94Words[] = {
#include "80176d94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175AB8Words[] = {
#include "80175ab8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017742CWords[] = {
#include "8017742c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175DA8Words[] = {
#include "80175da8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801757A0Words[] = {
#include "801757a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175308Words[] = {
#include "80175308_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801284F0Words[] = {
#include "801284f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801284B8Words[] = {
#include "801284b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D3D4Words[] = {
#include "8013d3d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C0F8Words[] = {
#include "8013c0f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C08CWords[] = {
#include "8013c08c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B568Words[] = {
#include "8013b568_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136BC4Words[] = {
#include "80136bc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801336E8Words[] = {
#include "801336e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012944CWords[] = {
#include "8012944c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129398Words[] = {
#include "80129398_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F14CWords[] = {
#include "8012f14c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148800Words[] = {
#include "80148800_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014880CWords[] = {
#include "8014880c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148818Words[] = {
#include "80148818_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148824Words[] = {
#include "80148824_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801488A8Words[] = {
#include "801488a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014891CWords[] = {
#include "8014891c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148980Words[] = {
#include "80148980_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801489E8Words[] = {
#include "801489e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148A48Words[] = {
#include "80148a48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148AACWords[] = {
#include "80148aac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148AFCWords[] = {
#include "80148afc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C18Words[] = {
#include "80148c18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C20Words[] = {
#include "80148c20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C34Words[] = {
#include "80148c34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C4CWords[] = {
#include "80148c4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C64Words[] = {
#include "80148c64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C7CWords[] = {
#include "80148c7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C84Words[] = {
#include "80148c84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148C9CWords[] = {
#include "80148c9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148CB4Words[] = {
#include "80148cb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148CCCWords[] = {
#include "80148ccc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148CE4Words[] = {
#include "80148ce4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148CECWords[] = {
#include "80148cec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148CF4Words[] = {
#include "80148cf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148D0CWords[] = {
#include "80148d0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148D24Words[] = {
#include "80148d24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148D3CWords[] = {
#include "80148d3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148D44Words[] = {
#include "80148d44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148E54Words[] = {
#include "80148e54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F60Words[] = {
#include "80148f60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F68Words[] = {
#include "80148f68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F74Words[] = {
#include "80148f74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F80Words[] = {
#include "80148f80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F8CWords[] = {
#include "80148f8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148F98Words[] = {
#include "80148f98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FA0Words[] = {
#include "80148fa0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FACWords[] = {
#include "80148fac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FB8Words[] = {
#include "80148fb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FC4Words[] = {
#include "80148fc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FD0Words[] = {
#include "80148fd0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FD8Words[] = {
#include "80148fd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FE0Words[] = {
#include "80148fe0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FECWords[] = {
#include "80148fec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80148FF8Words[] = {
#include "80148ff8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149004Words[] = {
#include "80149004_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014900CWords[] = {
#include "8014900c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149020Words[] = {
#include "80149020_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149034Words[] = {
#include "80149034_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149048Words[] = {
#include "80149048_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014905CWords[] = {
#include "8014905c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149078Words[] = {
#include "80149078_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801490E0Words[] = {
#include "801490e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801490E8Words[] = {
#include "801490e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801490F0Words[] = {
#include "801490f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801490F8Words[] = {
#include "801490f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149184Words[] = {
#include "80149184_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801491C4Words[] = {
#include "801491c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149204Words[] = {
#include "80149204_sc02_0031_words.inc"
};
static const uint32_t kMain80012C6CWords[] = {
#include "80012c6c_words.inc"
};
static const uint32_t kMain80012ABCWords[] = {
#include "80012abc_words.inc"
};
static const uint32_t kOverlaySc02_80149210Words[] = {
#include "80149210_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149228Words[] = {
#include "80149228_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149284Words[] = {
#include "80149284_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149290Words[] = {
#include "80149290_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149350Words[] = {
#include "80149350_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149374Words[] = {
#include "80149374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801493D0Words[] = {
#include "801493d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014942CWords[] = {
#include "8014942c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149450Words[] = {
#include "80149450_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801494CCWords[] = {
#include "801494cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149544Words[] = {
#include "80149544_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149584Words[] = {
#include "80149584_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801495C4Words[] = {
#include "801495c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014964CWords[] = {
#include "8014964c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801496D4Words[] = {
#include "801496d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149704Words[] = {
#include "80149704_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149724Words[] = {
#include "80149724_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149744Words[] = {
#include "80149744_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149788Words[] = {
#include "80149788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801497A8Words[] = {
#include "801497a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149864Words[] = {
#include "80149864_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149884Words[] = {
#include "80149884_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801498C0Words[] = {
#include "801498c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801498E0Words[] = {
#include "801498e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149954Words[] = {
#include "80149954_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149A64Words[] = {
#include "80149a64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149AA8Words[] = {
#include "80149aa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149AD4Words[] = {
#include "80149ad4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149B14Words[] = {
#include "80149b14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149B54Words[] = {
#include "80149b54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149BACWords[] = {
#include "80149bac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149BECWords[] = {
#include "80149bec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149C08Words[] = {
#include "80149c08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149C94Words[] = {
#include "80149c94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149CB4Words[] = {
#include "80149cb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149CD4Words[] = {
#include "80149cd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149D10Words[] = {
#include "80149d10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149D9CWords[] = {
#include "80149d9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149DD8Words[] = {
#include "80149dd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149E94Words[] = {
#include "80149e94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149F2CWords[] = {
#include "80149f2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149FA8Words[] = {
#include "80149fa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80149FB0Words[] = {
#include "80149fb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A048Words[] = {
#include "8014a048_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A1B0Words[] = {
#include "8014a1b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A218Words[] = {
#include "8014a218_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A238Words[] = {
#include "8014a238_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A2E4Words[] = {
#include "8014a2e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A380Words[] = {
#include "8014a380_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A3E0Words[] = {
#include "8014a3e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A454Words[] = {
#include "8014a454_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A4B4Words[] = {
#include "8014a4b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A4FCWords[] = {
#include "8014a4fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A51CWords[] = {
#include "8014a51c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A59CWords[] = {
#include "8014a59c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A638Words[] = {
#include "8014a638_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A738Words[] = {
#include "8014a738_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A850Words[] = {
#include "8014a850_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AA04Words[] = {
#include "8014aa04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AA28Words[] = {
#include "8014aa28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AB5CWords[] = {
#include "8014ab5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AB7CWords[] = {
#include "8014ab7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ABF0Words[] = {
#include "8014abf0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AC10Words[] = {
#include "8014ac10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ACC0Words[] = {
#include "8014acc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ACE8Words[] = {
#include "8014ace8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AD30Words[] = {
#include "8014ad30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014AD7CWords[] = {
#include "8014ad7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ADA8Words[] = {
#include "8014ada8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ADE0Words[] = {
#include "8014ade0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B00CWords[] = {
#include "8014b00c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B034Words[] = {
#include "8014b034_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B084Words[] = {
#include "8014b084_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B12CWords[] = {
#include "8014b12c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B154Words[] = {
#include "8014b154_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B160Words[] = {
#include "8014b160_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B190Words[] = {
#include "8014b190_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B2A8Words[] = {
#include "8014b2a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B2D0Words[] = {
#include "8014b2d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B2F8Words[] = {
#include "8014b2f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B310Words[] = {
#include "8014b310_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B33CWords[] = {
#include "8014b33c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B350Words[] = {
#include "8014b350_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B4C4Words[] = {
#include "8014b4c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B4D4Words[] = {
#include "8014b4d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B504Words[] = {
#include "8014b504_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B598Words[] = {
#include "8014b598_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B5B0Words[] = {
#include "8014b5b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B5B8Words[] = {
#include "8014b5b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B5C4Words[] = {
#include "8014b5c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B5D0Words[] = {
#include "8014b5d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B5D8Words[] = {
#include "8014b5d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B6F0Words[] = {
#include "8014b6f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B768Words[] = {
#include "8014b768_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B7A4Words[] = {
#include "8014b7a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014B944Words[] = {
#include "8014b944_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BB0CWords[] = {
#include "8014bb0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BB24Words[] = {
#include "8014bb24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BC0CWords[] = {
#include "8014bc0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BC44Words[] = {
#include "8014bc44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BC80Words[] = {
#include "8014bc80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BCC0Words[] = {
#include "8014bcc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BCECWords[] = {
#include "8014bcec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BD24Words[] = {
#include "8014bd24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BD60Words[] = {
#include "8014bd60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BD98Words[] = {
#include "8014bd98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BDC8Words[] = {
#include "8014bdc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BDE0Words[] = {
#include "8014bde0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BDE8Words[] = {
#include "8014bde8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BE78Words[] = {
#include "8014be78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BE9CWords[] = {
#include "8014be9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BEC0Words[] = {
#include "8014bec0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BEF8Words[] = {
#include "8014bef8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BF18Words[] = {
#include "8014bf18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BF48Words[] = {
#include "8014bf48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BF6CWords[] = {
#include "8014bf6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BF8CWords[] = {
#include "8014bf8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BFB0Words[] = {
#include "8014bfb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BFD4Words[] = {
#include "8014bfd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014BFF4Words[] = {
#include "8014bff4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C010Words[] = {
#include "8014c010_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C050Words[] = {
#include "8014c050_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C088Words[] = {
#include "8014c088_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C0C8Words[] = {
#include "8014c0c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C118Words[] = {
#include "8014c118_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C168Words[] = {
#include "8014c168_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C1A0Words[] = {
#include "8014c1a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C1C8Words[] = {
#include "8014c1c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C278Words[] = {
#include "8014c278_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C2B0Words[] = {
#include "8014c2b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C308Words[] = {
#include "8014c308_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C3A4Words[] = {
#include "8014c3a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C3D0Words[] = {
#include "8014c3d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C43CWords[] = {
#include "8014c43c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C4ACWords[] = {
#include "8014c4ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C568Words[] = {
#include "8014c568_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C59CWords[] = {
#include "8014c59c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C5D0Words[] = {
#include "8014c5d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C5FCWords[] = {
#include "8014c5fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C6ACWords[] = {
#include "8014c6ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C6C0Words[] = {
#include "8014c6c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C6E0Words[] = {
#include "8014c6e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C6F4Words[] = {
#include "8014c6f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C860Words[] = {
#include "8014c860_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C88CWords[] = {
#include "8014c88c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C8C8Words[] = {
#include "8014c8c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C8F0Words[] = {
#include "8014c8f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C918Words[] = {
#include "8014c918_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C978Words[] = {
#include "8014c978_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C98CWords[] = {
#include "8014c98c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014C99CWords[] = {
#include "8014c99c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CA00Words[] = {
#include "8014ca00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CA14Words[] = {
#include "8014ca14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CA70Words[] = {
#include "8014ca70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CA88Words[] = {
#include "8014ca88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CAE4Words[] = {
#include "8014cae4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CAFCWords[] = {
#include "8014cafc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB0CWords[] = {
#include "8014cb0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB1CWords[] = {
#include "8014cb1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB2CWords[] = {
#include "8014cb2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB58Words[] = {
#include "8014cb58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB68Words[] = {
#include "8014cb68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB7CWords[] = {
#include "8014cb7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB8CWords[] = {
#include "8014cb8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CB9CWords[] = {
#include "8014cb9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CBD8Words[] = {
#include "8014cbd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CBE8Words[] = {
#include "8014cbe8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CBF8Words[] = {
#include "8014cbf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CC28Words[] = {
#include "8014cc28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CCB4Words[] = {
#include "8014ccb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CD0CWords[] = {
#include "8014cd0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CD80Words[] = {
#include "8014cd80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014CF04Words[] = {
#include "8014cf04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D04CWords[] = {
#include "8014d04c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D0A4Words[] = {
#include "8014d0a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D12CWords[] = {
#include "8014d12c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D2A0Words[] = {
#include "8014d2a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D3E0Words[] = {
#include "8014d3e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D438Words[] = {
#include "8014d438_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D4C0Words[] = {
#include "8014d4c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D610Words[] = {
#include "8014d610_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D738Words[] = {
#include "8014d738_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D790Words[] = {
#include "8014d790_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014D820Words[] = {
#include "8014d820_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014DCE0Words[] = {
#include "8014dce0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014DD8CWords[] = {
#include "8014dd8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014DF3CWords[] = {
#include "8014df3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014DF94Words[] = {
#include "8014df94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E048Words[] = {
#include "8014e048_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E284Words[] = {
#include "8014e284_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E434Words[] = {
#include "8014e434_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E48CWords[] = {
#include "8014e48c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E514Words[] = {
#include "8014e514_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E5B4Words[] = {
#include "8014e5b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E6A0Words[] = {
#include "8014e6a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E6F8Words[] = {
#include "8014e6f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E790Words[] = {
#include "8014e790_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E83CWords[] = {
#include "8014e83c_sc02_0031_words.inc"
};
static int g_overlay_sc02_0031_words;
static const uint32_t kOverlaySc02_80128158Words[] = {
#include "80128158_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc01_80128158Words[] = {
#include "80128158_sc01_0000_words.inc"
};
static const uint32_t kOverlay0004_800CEEC8Words[] = {
#include "800ceec8_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D1E18Words[] = {
#include "800d1e18_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CFB3CWords[] = {
#include "800cfb3c_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D1E9CWords[] = {
#include "800d1e9c_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2394Words[] = {
#include "800d2394_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2454Words[] = {
#include "800d2454_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2AA0Words[] = {
#include "800d2aa0_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2D44Words[] = {
#include "800d2d44_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2A24Words[] = {
#include "800d2a24_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2704Words[] = {
#include "800d2704_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D298CWords[] = {
#include "800d298c_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2C0CWords[] = {
#include "800d2c0c_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2C88Words[] = {
#include "800d2c88_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D24D0Words[] = {
#include "800d24d0_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2D68Words[] = {
#include "800d2d68_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D27A0Words[] = {
#include "800d27a0_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D3234Words[] = {
#include "800d3234_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2E64Words[] = {
#include "800d2e64_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2EF8Words[] = {
#include "800d2ef8_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D2F88Words[] = {
#include "800d2f88_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D3020Words[] = {
#include "800d3020_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800D30D0Words[] = {
#include "800d30d0_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CFFECWords[] = {
#include "800cffec_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CF3E8Words[] = {
#include "800cf3e8_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CFC1CWords[] = {
#include "800cfc1c_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CF3A4Words[] = {
#include "800cf3a4_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CF370Words[] = {
#include "800cf370_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CF300Words[] = {
#include "800cf300_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CF104Words[] = {
#include "800cf104_overlay0004_words.inc"
};
static const uint32_t kOverlay0004_800CFE00Words[] = {
#include "800cfe00_overlay0004_words.inc"
};
static const uint32_t kOverlay0012_80128158Words[] = {
#include "80128158_overlay0012_words.inc"
};
static const uint32_t kOverlay0012_80128288Words[] = {
#include "80128288_overlay0012_words.inc"
};
static const uint32_t kOverlay0012_80128228Words[] = {
#include "80128228_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_80128228Words) / sizeof(uint32_t) == 8,
               "overlay 0012 80128228 source span changed");
static const uint32_t kOverlay0012_80128A28Words[] = {
#include "80128a28_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_80128A28Words) / sizeof(uint32_t) == 51,
               "overlay 0012 80128A28 source span changed");
static const uint32_t kOverlay0012_8017BEBCWords[] = {
#include "8017bebc_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_8017BEBCWords) / sizeof(uint32_t) == 10,
               "overlay 0012 8017BEBC source span changed");
static const uint32_t kOverlay0012_8017BEE4Words[] = {
#include "8017bee4_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_8017BEE4Words) / sizeof(uint32_t) == 21,
               "overlay 0012 8017BEE4 source span changed");
static const uint32_t kOverlay0012_8017BF38Words[] = {
#include "8017bf38_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_8017BF38Words) / sizeof(uint32_t) == 14,
               "overlay 0012 8017BF38 source span changed");
static const uint32_t kOverlay0012_8017C008Words[] = {
#include "8017c008_overlay0012_words.inc"
};
_Static_assert(sizeof(kOverlay0012_8017C008Words) / sizeof(uint32_t) == 30,
               "overlay 0012 8017C008 source span changed");

void musashi_boot_select_overlay_0004_words(int enable) {
    g_overlay_0004_words = enable ? 1 : 0;
    if (enable) g_overlay_0007_words = g_overlay_0010_words = 0;
}

void musashi_boot_select_overlay_0007_words(int enable) {
    g_overlay_0007_words = enable ? 1 : 0;
    if (enable) g_overlay_0010_words = g_overlay_0004_words = 0;
}

void musashi_boot_select_overlay_0010_words(int enable) {
    g_overlay_0010_words = enable ? 1 : 0;
    if (enable) g_overlay_0007_words = g_overlay_0004_words = 0;
}
static const uint32_t kOverlay800CEE40Words[] = {
    0x27bdffe8u, 0x24020001u, 0xafbf0010u, 0x3c01800cu,
    0xa0229a11u, 0x0c007011u, 0x00000000u, 0x0c0054c4u,
    0x00000000u, 0x0c0051acu, 0x24040007u, 0x0c016596u,
    0x00002021u, 0x0c0108e7u, 0x00002021u, 0x0c016596u,
    0x24040001u, 0x3c01800cu, 0xac209a18u, 0x0c0059eeu,
    0x00002021u, 0x3c04800du, 0x24843abcu, 0x0c0060f8u,
    0x00000000u, 0x3c01800du, 0xac203c0cu, 0x3c01800du,
    0xac203c10u, 0x0c0045b8u, 0x00000000u, 0x3c01800cu,
    0xa42099e8u, 0x0c006ffau, 0x00000000u, 0x10400005u,
    0x00000000u, 0x0c00464au, 0x24040003u, 0x08033bbdu,
    0x00000000u, 0x0c006ffeu, 0x00000000u, 0x0c00462bu,
    0x00000000u, 0x8fbf0010u, 0x27bd0018u, 0x03e00008u,
    0x00000000u
};
_Static_assert(sizeof(kOverlay800CEE40Words) / sizeof(uint32_t) == 49,
               "overlay 800CEE40 source span changed");
static const uint32_t kOverlay800CEF04Words[] = {
    0x3c02800du, 0x8c423c10u, 0x27bdffe8u, 0xafbf0010u,
    0x24420010u, 0x3c01800du, 0xac223c10u, 0x28420080u,
    0x14400005u, 0x24020080u, 0x3c01800du, 0xac223c10u,
    0x0c00462bu, 0x00000000u, 0x0c033ca4u, 0x00000000u,
    0x8fbf0010u, 0x27bd0018u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CEF04Words) / sizeof(uint32_t) == 20,
               "overlay 800CEF04 source span changed");
static const uint32_t kOverlay800CF290Words[] = {
    0x3c03e100u, 0x3463008au, 0x3c08e100u, 0x3508008cu,
    0x3c02800du, 0x24423aecu, 0x24060005u, 0x240d0064u,
    0x240e7840u, 0x240cffe4u, 0x240b0038u, 0x240a0100u,
    0x3c07800cu, 0x94e79a02u, 0x24090060u, 0x00072840u,
    0x00a72821u, 0x000528c0u, 0x00a22021u, 0x24420004u,
    0x00a21021u, 0xa0860003u, 0xac430000u, 0x2402ff00u,
    0xa08d000bu, 0xa482000cu, 0x3c02800du, 0x90423c10u,
    0x00073b80u, 0xa48e0012u, 0xa48c000eu, 0xa0800010u,
    0xa08b0011u, 0xa48a0014u, 0xa4890016u, 0xa082000au,
    0xa0820009u, 0xa0820008u, 0x3c02800du, 0x24423b1cu,
    0x00a21821u, 0x24420004u, 0x00a22821u, 0xa0660003u,
    0xaca80000u, 0x3c0800ffu, 0x8c660000u, 0x3508ffffu,
    0xa06d000bu, 0x3c02800du, 0x90423c10u, 0x3c05ff00u,
    0xa46e0012u, 0xa460000cu, 0xa46c000eu, 0xa0600010u,
    0xa06b0011u, 0xa46a0014u, 0xa4690016u, 0xa062000au,
    0xa0620009u, 0xa0620008u, 0x3c02800bu, 0x2442a60cu,
    0x00e23821u, 0x8ce20000u, 0x00c53024u, 0x00481024u,
    0x00c23025u, 0xac660000u, 0x8ce20000u, 0x00681824u,
    0x00451024u, 0x00431025u, 0xace20000u, 0x8c830000u,
    0x00481024u, 0x00651824u, 0x00621825u, 0xac830000u,
    0x8ce20000u, 0x00882024u, 0x00451024u, 0x00441025u,
    0x03e00008u, 0xace20000u
};
_Static_assert(sizeof(kOverlay800CF290Words) / sizeof(uint32_t) == 86,
               "overlay 800CF290 source span changed");
static const uint32_t kOverlay800CEF54Words[] = {
    0x27bdffe8u, 0xafbf0010u, 0x0c033ca4u, 0x00000000u,
    0x3c02800cu, 0x944299eeu, 0x00000000u, 0x24420001u,
    0x3c01800cu, 0xa42299eeu, 0x00021400u, 0x00021403u,
    0x28420105u, 0x14400003u, 0x00000000u, 0x0c00462bu,
    0x00000000u, 0x8fbf0010u, 0x27bd0018u, 0x03e00008u,
    0x00000000u
};
_Static_assert(sizeof(kOverlay800CEF54Words) / sizeof(uint32_t) == 21,
               "overlay 800CEF54 source span changed");
static const uint32_t kOverlay800CEFA8Words[] = {
    0x3c02800du, 0x8c423c10u, 0x27bdffe8u, 0xafbf0010u,
    0x2442fffcu, 0x3c01800du, 0xac223c10u, 0x1c400005u,
    0x00000000u, 0x3c01800du, 0xac203c10u, 0x0c00462bu,
    0x00000000u, 0x0c033ca4u, 0x00000000u, 0x8fbf0010u,
    0x27bd0018u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CEFA8Words) / sizeof(uint32_t) == 19,
               "overlay 800CEFA8 source span changed");
static const uint32_t kOverlay800CEFF4Words[] = {
    0x27bdffe8u, 0xafbf0010u, 0x0c033c60u, 0x00000000u,
    0x0c033c45u, 0x00000000u, 0x0c0059fcu, 0x00002021u,
    0x3042ffffu, 0x10400003u, 0x00000000u, 0x0c00462bu,
    0x00000000u, 0x8fbf0010u, 0x27bd0018u, 0x03e00008u,
    0x00000000u
};
_Static_assert(sizeof(kOverlay800CEFF4Words) / sizeof(uint32_t) == 17,
               "overlay 800CEFF4 source span changed");
static const uint32_t kOverlay800CF038Words[] = {
    0x27bdffe8u, 0xafbf0010u, 0x0c033c60u, 0x00000000u,
    0x0c033c45u, 0x00000000u, 0x3c02800cu, 0x944299e8u,
    0x00000000u, 0x24420001u, 0x3c01800cu, 0xa42299e8u,
    0x0c005278u, 0x00002021u, 0x3c03800du, 0x8c633c0cu,
    0x00000000u, 0x1060000du, 0x00402021u, 0x3c02800cu,
    0x844299e8u, 0x00000000u, 0x28420081u, 0x10400003u,
    0x30820840u, 0x10400005u, 0x00000000u, 0x0c0059eeu,
    0x24040004u, 0x0c00462bu, 0x00000000u, 0x8fbf0010u,
    0x27bd0018u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CF038Words) / sizeof(uint32_t) == 35,
               "overlay 800CF038 source span changed");
static const uint32_t kOverlay800CF0C4Words[] = {
    0x27bdffe8u, 0xafbf0010u, 0x0c033c60u, 0x00000000u,
    0x0c0059fcu, 0x24040004u, 0x3042ffffu, 0x10400008u,
    0x24020001u, 0x3c01800cu, 0xa42299e6u, 0x0c0051acu,
    0x24040001u, 0x24020002u, 0x3c01800cu, 0xac229a18u,
    0x8fbf0010u, 0x27bd0018u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CF0C4Words) / sizeof(uint32_t) == 20,
               "overlay 800CF0C4 source span changed");
static const uint32_t kOverlay800CF114Words[] = {
    0x3c02800du, 0x8c423c0cu, 0x27bdffe0u, 0x14400013u,
    0xafbf0018u, 0x3c03800cu, 0x24637c60u, 0x3c02800au,
    0x24422e20u, 0x00002021u, 0x00002821u, 0x3c06800bu,
    0x24c6e840u, 0x00003821u, 0xac600000u, 0x3c01800cu,
    0xac227c64u, 0x0c006aefu, 0xafa30010u, 0x10400003u,
    0x24020001u, 0x3c01800du, 0xac223c0cu, 0x8fbf0018u,
    0x27bd0020u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CF114Words) / sizeof(uint32_t) == 27,
               "overlay 800CF114 source span changed");
static const uint32_t kOverlay800CF180Words[] = {
    0x3c0800ffu, 0x3508ffffu, 0x3c09800du, 0x2529f3f0u,
    0x3c02800cu, 0x94429a02u, 0x3c07ff00u, 0x00021840u,
    0x00621821u, 0x000318c0u, 0x00691821u, 0x00021380u,
    0x8c640000u, 0x3c01800bu, 0x00220821u, 0x8c22a60cu,
    0x00872024u, 0x00481024u, 0x00822025u, 0xac640000u,
    0x3c04800cu, 0x94849a02u, 0x3c06800bu, 0x24c6a60cu,
    0x00042b80u, 0x00a62821u, 0x00041040u, 0x00441021u,
    0x000210c0u, 0x00491021u, 0x8ca30000u, 0x00481024u,
    0x00671824u, 0x00621825u, 0xaca30000u, 0x3c02800cu,
    0x94429a02u, 0x3c09800du, 0x2529f420u, 0x00021840u,
    0x00621821u, 0x000318c0u, 0x00691821u, 0x00021380u,
    0x00461021u, 0x8c640000u, 0x8c420000u, 0x00872024u,
    0x00481024u, 0x00822025u, 0xac640000u, 0x3c04800cu,
    0x94849a02u, 0x27bdfff8u, 0x00042b80u, 0x00a62821u,
    0x00041040u, 0x00441021u, 0x000210c0u, 0x00491021u,
    0x8ca30000u, 0x00481024u, 0x00671824u, 0x00621825u,
    0xaca30000u, 0x27bd0008u, 0x03e00008u, 0x00000000u
};
_Static_assert(sizeof(kOverlay800CF180Words) / sizeof(uint32_t) == 68,
               "overlay 800CF180 source span changed");
static const uint32_t kMain8005B1C4Words[] = {
#include "8005b1c4_words.inc"
};
static const uint32_t kMain80010C7CWords[] = {
#include "80010c7c_words.inc"
};
static const uint32_t kMain8001513CWords[] = {
#include "8001513c_words.inc"
};
static const uint32_t kMain80015608Words[] = {
#include "80015608_words.inc"
};
static const uint32_t kMain80015760Words[] = {
#include "80015760_words.inc"
};
static const uint32_t kMain80059A80Words[] = {
#include "80059a80_words.inc"
};
static const uint32_t kMain80019018Words[] = {
#include "80019018_words.inc"
};
static const uint32_t kMain80018E78Words[] = {
#include "80018e78_words.inc"
};
static const uint32_t kMain8002AB64Words[] = {
#include "8002ab64_words.inc"
};
static const uint32_t kMain8002AC00Words[] = {
#include "8002ac00_words.inc"
};
static const uint32_t kMain80015978Words[] = {
#include "80015978_words.inc"
};
static const uint32_t kMain80012CB8Words[] = {
#include "80012cb8_words.inc"
};
static const uint32_t kMain80012B04Words[] = {
#include "80012b04_words.inc"
};
static const uint32_t kMain80012B58Words[] = {
#include "80012b58_words.inc"
};
static const uint32_t kMain80012D0CWords[] = {
#include "80012d0c_words.inc"
};
static const uint32_t kMain80049CACWords[] = {
#include "80049cac_words.inc"
};
static const uint32_t kMain8004914CWords[] = {
#include "8004914c_words.inc"
};
static const uint32_t kMain800491ACWords[] = {
#include "800491ac_words.inc"
};
static const uint32_t kMain8004945CWords[] = {
#include "8004945c_words.inc"
};
static const uint32_t kMain80011E84Words[] = {
#include "80011e84_words.inc"
};
static const uint32_t kMain8005A600Words[] = {
#include "8005a600_words.inc"
};
static const uint32_t kMain80024054Words[] = {
#include "80024054_words.inc"
};
static const uint32_t kMain8001C214Words[] = {
#include "8001c214_words.inc"
};
static const uint32_t kMain8001C810Words[] = {
#include "8001c810_words.inc"
};
static const uint32_t kMain8001D050Words[] = {
#include "8001d050_words.inc"
};
static const uint32_t kMain8001CD50Words[] = {
#include "8001cd50_words.inc"
};
static const uint32_t kMain800233CCWords[] = {
#include "800233cc_words.inc"
};
static const uint32_t kMain800234E4Words[] = {
#include "800234e4_words.inc"
};
static const uint32_t kMain80023570Words[] = {
#include "80023570_words.inc"
};
static const uint32_t kMain8001CA1CWords[] = {
#include "8001ca1c_words.inc"
};
static const uint32_t kMain8001CA88Words[] = {
#include "8001ca88_words.inc"
};
static const uint32_t kMain8001CB00Words[] = {
#include "8001cb00_words.inc"
};
static const uint32_t kMain8001CB6CWords[] = {
#include "8001cb6c_words.inc"
};
static const uint32_t kMain8001CBDCWords[] = {
#include "8001cbdc_words.inc"
};
static const uint32_t kMain8001CC3CWords[] = {
#include "8001cc3c_words.inc"
};
static const uint32_t kMain8001CCA0Words[] = {
#include "8001cca0_words.inc"
};
static const uint32_t kMain8001CD04Words[] = {
#include "8001cd04_words.inc"
};
static const uint32_t kMain8001CD9CWords[] = {
#include "8001cd9c_words.inc"
};
static const uint32_t kMain8001CDE8Words[] = {
#include "8001cde8_words.inc"
};
static const uint32_t kMain8001CE28Words[] = {
#include "8001ce28_words.inc"
};
static const uint32_t kMain8001CE68Words[] = {
#include "8001ce68_words.inc"
};
static const uint32_t kMain8001CEC0Words[] = {
#include "8001cec0_words.inc"
};
static const uint32_t kMain8001CF00Words[] = {
#include "8001cf00_words.inc"
};
static const uint32_t kMain8001CF30Words[] = {
#include "8001cf30_words.inc"
};
static const uint32_t kMain8001CF48Words[] = {
#include "8001cf48_words.inc"
};
static const uint32_t kMain8001CFB8Words[] = {
#include "8001cfb8_words.inc"
};
static const uint32_t kMain8001D074Words[] = {
#include "8001d074_words.inc"
};
static const uint32_t kMain8001D0E8Words[] = {
#include "8001d0e8_words.inc"
};
static const uint32_t kMain8001D0F4Words[] = {
#include "8001d0f4_words.inc"
};
static const uint32_t kMain8001D130Words[] = {
#include "8001d130_words.inc"
};
static const uint32_t kMain8001D150Words[] = {
#include "8001d150_words.inc"
};
static const uint32_t kMain8001C8C4Words[] = {
#include "8001c8c4_words.inc"
};
static const uint32_t kMain8001C924Words[] = {
#include "8001c924_words.inc"
};
static const uint32_t kMain8001C97CWords[] = {
#include "8001c97c_words.inc"
};
static const uint32_t kMain8001CFDCWords[] = {
#include "8001cfdc_words.inc"
};
static const uint32_t kMain800599B8Words[] = {
#include "800599b8_words.inc"
};
static const uint32_t kMain80053D44Words[] = {
#include "80053d44_words.inc"
};
static const uint32_t kMain80058890Words[] = {
#include "80058890_words.inc"
};
static const uint32_t kMain8001FB8CWords[] = {
#include "8001fb8c_words.inc"
};
static const uint32_t kMain8001D388Words[] = {
#include "8001d388_words.inc"
};
static const uint32_t kMain80015908Words[] = {
#include "80015908_words.inc"
};
static const uint32_t kMain80015A74Words[] = {
#include "80015a74_words.inc"
};
static const uint32_t kMain8005B75CWords[] = {
#include "8005b75c_words.inc"
};
static const uint32_t kMain80058B7CWords[] = {
#include "80058b7c_words.inc"
};
static const uint32_t kMain8005E8E8Words[] = {
#include "8005e8e8_words.inc"
};
static const uint32_t kMain8004974CWords[] = {
#include "8004974c_words.inc"
};
static const uint32_t kMain80052FCCWords[] = {
#include "80052fcc_words.inc"
};
static const uint32_t kMain80054514Words[] = {
#include "80054514_words.inc"
};
static const uint32_t kMain80048EACWords[] = {
#include "80048eac_words.inc"
};
static const uint32_t kMain80053050Words[] = {
#include "80053050_words.inc"
};
static const uint32_t kMain8005AE80Words[] = {
#include "8005ae80_words.inc"
};
static const uint32_t kMain8005C054Words[] = {
#include "8005c054_words.inc"
};
static const uint32_t kMain80010B40Words[] = {
#include "80010b40_words.inc"
};
static const uint32_t kMain80010BB4Words[] = {
#include "80010bb4_words.inc"
};
static const uint32_t kMain80029690Words[] = {
#include "80029690_words.inc"
};
static const uint32_t kMain80029274Words[] = {
#include "80029274_words.inc"
};
static const uint32_t kMain8002941CWords[] = {
#include "8002941c_words.inc"
};
static const uint32_t kMain8002AEF8Words[] = {
#include "8002aef8_words.inc"
};
_Static_assert(sizeof(kMain8002AEF8Words) / sizeof(uint32_t) == 4, "main 8002AEF8 source span changed");
static const uint32_t kMain80029254Words[] = {
#include "80029254_words.inc"
};
_Static_assert(sizeof(kMain80029254Words) / sizeof(uint32_t) == 4, "main 80029254 source span changed");
static const uint32_t kMain80011DCCWords[] = {
#include "80011dcc_words.inc"
};
_Static_assert(sizeof(kMain80011DCCWords) / sizeof(uint32_t) == 10, "main 80011DCC source span changed");
static const uint32_t kMain8001B384Words[] = {
#include "8001b384_words.inc"
};
_Static_assert(sizeof(kMain8001B384Words) / sizeof(uint32_t) == 4, "main 8001B384 source span changed");
static const uint32_t kMain8001C0C8Words[] = {
#include "8001c0c8_words.inc"
};
_Static_assert(sizeof(kMain8001C0C8Words) / sizeof(uint32_t) == 33, "main 8001C0C8 source span changed");
static const uint32_t kMain8001B85CWords[] = {
#include "8001b85c_words.inc"
};
_Static_assert(sizeof(kMain8001B85CWords) / sizeof(uint32_t) == 4, "main 8001B85C source span changed");
static const uint32_t kMain80011CFCWords[] = {
#include "80011cfc_words.inc"
};
_Static_assert(sizeof(kMain80011CFCWords) / sizeof(uint32_t) == 22, "main 80011CFC source span changed");
static const uint32_t kMain80011D54Words[] = {
#include "80011d54_words.inc"
};
_Static_assert(sizeof(kMain80011D54Words) / sizeof(uint32_t) == 19, "main 80011D54 source span changed");
static const uint32_t kMain800191D4Words[] = {
#include "800191d4_words.inc"
};
_Static_assert(sizeof(kMain800191D4Words) / sizeof(uint32_t) == 26, "main 800191D4 source span changed");
static const uint32_t kMain800191BCWords[] = {
#include "800191bc_words.inc"
};
_Static_assert(sizeof(kMain800191BCWords) / sizeof(uint32_t) == 6, "main 800191BC source span changed");
static const uint32_t kMain8001AF04Words[] = {
#include "8001af04_words.inc"
};
_Static_assert(sizeof(kMain8001AF04Words) / sizeof(uint32_t) == 12, "main 8001AF04 source span changed");
static const uint32_t kMain8002F648Words[] = {
#include "8002f648_words.inc"
};
_Static_assert(sizeof(kMain8002F648Words) / sizeof(uint32_t) == 4, "main 8002F648 source span changed");
static const uint32_t kMain8002F620Words[] = {
#include "8002f620_words.inc"
};
_Static_assert(sizeof(kMain8002F620Words) / sizeof(uint32_t) == 10, "main 8002F620 source span changed");
static const uint32_t kMain80029504Words[] = {
#include "80029504_words.inc"
};
_Static_assert(sizeof(kMain80029504Words) / sizeof(uint32_t) == 4, "main 80029504 source span changed");
static const uint32_t kMain8002F658Words[] = {
#include "8002f658_words.inc"
};
_Static_assert(sizeof(kMain8002F658Words) / sizeof(uint32_t) == 9, "main 8002F658 source span changed");
static const uint32_t kMain8002F5C8Words[] = {
#include "8002f5c8_words.inc"
};
_Static_assert(sizeof(kMain8002F5C8Words) / sizeof(uint32_t) == 22, "main 8002F5C8 source span changed");
static const uint32_t kMain80018714Words[] = {
#include "80018714_words.inc"
};
_Static_assert(sizeof(kMain80018714Words) / sizeof(uint32_t) == 7, "main 80018714 source span changed");
static const uint32_t kMain80018730Words[] = {
#include "80018730_words.inc"
};
_Static_assert(sizeof(kMain80018730Words) / sizeof(uint32_t) == 122, "main 80018730 source span changed");
static const uint32_t kMain8002D858Words[] = {
#include "8002d858_words.inc"
};
_Static_assert(sizeof(kMain8002D858Words) / sizeof(uint32_t) == 20, "main 8002D858 source span changed");
static const uint32_t kMain8003D650Words[] = {
#include "8003d650_words.inc"
};
_Static_assert(sizeof(kMain8003D650Words) / sizeof(uint32_t) == 37, "main 8003D650 source span changed");
static const uint32_t kMain8001BFA0Words[] = {
#include "8001bfa0_words.inc"
};
_Static_assert(sizeof(kMain8001BFA0Words) / sizeof(uint32_t) == 4, "main 8001BFA0 source span changed");
static const uint32_t kMain8001BFB0Words[] = {
#include "8001bfb0_words.inc"
};
_Static_assert(sizeof(kMain8001BFB0Words) / sizeof(uint32_t) == 8, "main 8001BFB0 source span changed");
static const uint32_t kMain8004657CWords[] = {
#include "8004657c_words.inc"
};
_Static_assert(sizeof(kMain8004657CWords) / sizeof(uint32_t) == 37, "main 8004657C source span changed");
static const uint32_t kMain80046B44Words[] = {
#include "80046b44_words.inc"
};
_Static_assert(sizeof(kMain80046B44Words) / sizeof(uint32_t) == 46, "main 80046B44 source span changed");
static const uint32_t kMain80046C38Words[] = {
#include "80046c38_words.inc"
};
_Static_assert(sizeof(kMain80046C38Words) / sizeof(uint32_t) == 49, "main 80046C38 source span changed");
static const uint32_t kMain80046D1CWords[] = {
#include "80046d1c_words.inc"
};
_Static_assert(sizeof(kMain80046D1CWords) / sizeof(uint32_t) == 604, "main 80046D1C source span changed");
static const uint32_t kMain80043088Words[] = {
#include "80043088_words.inc"
};
_Static_assert(sizeof(kMain80043088Words) / sizeof(uint32_t) == 12, "main 80043088 source span changed");
static const uint32_t kMain8004689CWords[] = {
#include "8004689c_words.inc"
};
_Static_assert(sizeof(kMain8004689CWords) / sizeof(uint32_t) == 24, "main 8004689C source span changed");
static const uint32_t kMain80046ABCWords[] = {
#include "80046abc_words.inc"
};
_Static_assert(sizeof(kMain80046ABCWords) / sizeof(uint32_t) == 34, "main 80046ABC source span changed");
static const uint32_t kMain800468FCWords[] = {
#include "800468fc_words.inc"
};
_Static_assert(sizeof(kMain800468FCWords) / sizeof(uint32_t) == 33, "main 800468FC source span changed");
static const uint32_t kMain80046BFCWords[] = {
#include "80046bfc_words.inc"
};
_Static_assert(sizeof(kMain80046BFCWords) / sizeof(uint32_t) == 15, "main 80046BFC source span changed");
static const uint32_t kMain80046CFCWords[] = {
#include "80046cfc_words.inc"
};
_Static_assert(sizeof(kMain80046CFCWords) / sizeof(uint32_t) == 8, "main 80046CFC source span changed");
static const uint32_t kMain800469A8Words[] = {
#include "800469a8_words.inc"
};
_Static_assert(sizeof(kMain800469A8Words) / sizeof(uint32_t) == 9, "main 800469A8 source span changed");
static const uint32_t kMain80046994Words[] = {
#include "80046994_words.inc"
};
_Static_assert(sizeof(kMain80046994Words) / sizeof(uint32_t) == 5, "main 80046994 source span changed");
static const uint32_t kMain800469CCWords[] = {
#include "800469cc_words.inc"
};
_Static_assert(sizeof(kMain800469CCWords) / sizeof(uint32_t) == 36, "main 800469CC source span changed");
static const uint32_t kMain80046610Words[] = {
#include "80046610_words.inc"
};
_Static_assert(sizeof(kMain80046610Words) / sizeof(uint32_t) == 8, "main 80046610 source span changed");
static const uint32_t kMain8004768CWords[] = {
#include "8004768c_words.inc"
};
_Static_assert(sizeof(kMain8004768CWords) / sizeof(uint32_t) == 13, "main 8004768C source span changed");
static const uint32_t kMain800476C0Words[] = {
#include "800476c0_words.inc"
};
_Static_assert(sizeof(kMain800476C0Words) / sizeof(uint32_t) == 111, "main 800476C0 source span changed");
static const uint32_t kMain8002D8D4Words[] = {
#include "8002d8d4_words.inc"
};
_Static_assert(sizeof(kMain8002D8D4Words) / sizeof(uint32_t) == 12, "main 8002D8D4 source span changed");
static const uint32_t kMain80014B10Words[] = {
#include "80014b10_words.inc"
};
_Static_assert(sizeof(kMain80014B10Words) / sizeof(uint32_t) == 59, "main 80014B10 source span changed");
static const uint32_t kMain80029344Words[] = {
#include "80029344_words.inc"
};
_Static_assert(sizeof(kMain80029344Words) / sizeof(uint32_t) == 54,
               "main 80029344 source span changed");
static const uint32_t kMain80010AE0Words[] = {
#include "80010ae0_words.inc"
};
static const uint32_t kMain80011B7CWords[] = {
#include "80011b7c_words.inc"
};
static const uint32_t kMain80011C10Words[] = {
#include "80011c10_words.inc"
};
_Static_assert(sizeof(kMain80011C10Words) / sizeof(uint32_t) == 31,
               "main 80011C10 source span changed");
static const uint32_t kMain80011778Words[] = {
#include "80011778_words.inc"
};
static const uint32_t kMain80015498Words[] = {
#include "80015498_words.inc"
};
static const uint32_t kMain80058B40Words[] = {
#include "80058b40_words.inc"
};
static const uint32_t kMain8001C00CWords[] = {
#include "8001c00c_words.inc"
};
static const uint32_t kMain8001F9F8Words[] = {
#include "8001f9f8_words.inc"
};
static const uint32_t kMain8001D1C4Words[] = {
#include "8001d1c4_words.inc"
};
static const uint32_t kMain800184F0Words[] = {
#include "800184f0_words.inc"
};
static const uint32_t kMain800596F4Words[] = {
#include "800596f4_words.inc"
};
static const uint32_t kMain8005BED8Words[] = {
#include "8005bed8_words.inc"
};
static const uint32_t kMain8002CDD8Words[] = {
#include "8002cdd8_words.inc"
};
static const uint32_t kMain8003D25CWords[] = {
#include "8003d25c_words.inc"
};
static const uint32_t kMain8002CFE4Words[] = {
#include "8002cfe4_words.inc"
};
static const uint32_t kMain8002D904Words[] = {
#include "8002d904_words.inc"
};
static const uint32_t kMain80037FC4Words[] = {
#include "80037fc4_words.inc"
};
static const uint32_t kMain8002EC10Words[] = {
#include "8002ec10_words.inc"
};
static const uint32_t kMain8003836CWords[] = {
#include "8003836c_words.inc"
};
static const uint32_t kMain8003C4F0Words[] = {
#include "8003c4f0_words.inc"
};
static const uint32_t kMain80030F80Words[] = {
#include "80030f80_words.inc"
};
static const uint32_t kMain8002D320Words[] = {
#include "8002d320_words.inc"
};
static const uint32_t kMain8002EE64Words[] = {
#include "8002ee64_words.inc"
};
static const uint32_t kMain8002EFF8Words[] = {
#include "8002eff8_words.inc"
};
static const uint32_t kMain800314DCWords[] = {
#include "800314dc_words.inc"
};
static const uint32_t kMain800316F8Words[] = {
#include "800316f8_words.inc"
};
static const uint32_t kMain80031988Words[] = {
#include "80031988_words.inc"
};
static const uint32_t kMain8003819CWords[] = {
#include "8003819c_words.inc"
};
static const uint32_t kMain80038210Words[] = {
#include "80038210_words.inc"
};
static const uint32_t kMain80038308Words[] = {
#include "80038308_words.inc"
};
static const uint32_t kMain8003834CWords[] = {
#include "8003834c_words.inc"
};
static const uint32_t kMain80038638Words[] = {
#include "80038638_words.inc"
};
static const uint32_t kMain8003B250Words[] = {
#include "8003b250_words.inc"
};
static const uint32_t kMain8003C23CWords[] = {
#include "8003c23c_words.inc"
};
static const uint32_t kMain8003D3B4Words[] = {
#include "8003d3b4_words.inc"
};
static const uint32_t kMain80031BE0Words[] = {
#include "80031be0_words.inc"
};
static const uint32_t kMain8002F064Words[] = {
#include "8002f064_words.inc"
};
static const uint32_t kMain80030CA4Words[] = {
#include "80030ca4_words.inc"
};
static const uint32_t kMain80030D80Words[] = {
#include "80030d80_words.inc"
};
static const uint32_t kMain800336A8Words[] = {
#include "800336a8_words.inc"
};
static const uint32_t kMain8003388CWords[] = {
#include "8003388c_words.inc"
};
static const uint32_t kMain80034650Words[] = {
#include "80034650_words.inc"
};
static const uint32_t kMain8003F144Words[] = {
#include "8003f144_words.inc"
};
static const uint32_t kMain8003F380Words[] = {
#include "8003f380_words.inc"
};
static const uint32_t kMain800414E4Words[] = {
#include "800414e4_words.inc"
};
static const uint32_t kDraw800145ECWords[] = {
#include "800145ec_words.inc"
};
static const uint32_t kDraw800525DCWords[] = {
#include "800525dc_words.inc"
};
static const uint32_t kDraw80052654Words[] = {
#include "80052654_words.inc"
};
static const uint32_t kDraw80059D68Words[] = {
#include "80059d68_words.inc"
};
static const uint32_t kDraw8005A870Words[] = {
#include "8005a870_words.inc"
};
static const uint32_t kDraw8005AB00Words[] = {
#include "8005ab00_words.inc"
};
static const uint32_t kDraw8005AB58Words[] = {
#include "8005ab58_words.inc"
};
static const uint32_t kDraw8005AC24Words[] = {
#include "8005ac24_words.inc"
};
static const uint32_t kDraw8005ACF0Words[] = {
#include "8005acf0_words.inc"
};
static const uint32_t kDraw8005AD34Words[] = {
#include "8005ad34_words.inc"
};
static const uint32_t kDraw8005B7B0Words[] = {
#include "8005b7b0_words.inc"
};
static const uint32_t kDraw8005BA90Words[] = {
#include "8005ba90_words.inc"
};
static const uint32_t kMain8001099CWords[] = {
#include "8001099c_words.inc"
};
static const uint32_t kMain80058CE4Words[] = {
#include "80058ce4_words.inc"
};
static const uint32_t kDraw8005B710Words[] = {
#include "8005b710_words.inc"
};
static const uint32_t kDraw8005C020Words[] = {
#include "8005c020_words.inc"
};
static const uint32_t kDisplay80043078Words[] = {
#include "80043078_words.inc"
};
static const uint32_t kDisplay80059FC0Words[] = {
#include "80059fc0_words.inc"
};
static const uint32_t kDisplay8005B684Words[] = {
#include "8005b684_words.inc"
};
static const uint32_t kDraw800426FCWords[] = {
#include "800426fc_words.inc"
};
static const uint32_t kGte80053CF8Words[] = {
#include "80053cf8_words.inc"
};
static const uint32_t kProjection8005283CWords[] = {
#include "8005283c_words.inc"
};
static const uint32_t kProjection80052D00Words[] = {
#include "80052d00_words.inc"
};
static const uint32_t kProjection80052D90Words[] = {
#include "80052d90_words.inc"
};
static const uint32_t kProjection80052BECWords[] = {
#include "80052bec_words.inc"
};
static const uint32_t kProjection80053178Words[] = {
#include "80053178_words.inc"
};
static const uint32_t kDrawFollowup80053218Words[] = {
#include "80053218_words.inc"
};
static const uint32_t kDrawFollowup80014774Words[] = {
#include "80014774_words.inc"
};
static const uint32_t kDrawFollowup800147B8Words[] = {
#include "800147b8_words.inc"
};
static const uint32_t kCamera800144D4Words[] = {
#include "800144d4_words.inc"
};
static const uint32_t kCamera80053308Words[] = {
#include "80053308_words.inc"
};
static const uint32_t kCamera80053328Words[] = {
#include "80053328_words.inc"
};
static const uint32_t kCamera8005386CWords[] = {
#include "8005386c_words.inc"
};
static const uint32_t kCamera80053804Words[] = {
#include "80053804_words.inc"
};
static const uint32_t kCamera800538BCWords[] = {
#include "800538bc_words.inc"
};
static const uint32_t kCamera800538ECWords[] = {
#include "800538ec_words.inc"
};
static const uint32_t kCamera80053F6CWords[] = {
#include "80053f6c_words.inc"
};
static const uint32_t kCamera80053E28Words[] = {
#include "80053e28_words.inc"
};
static const uint32_t kCamera80048D9CWords[] = {
#include "80048d9c_words.inc"
};
static const uint32_t kCamera800484ECWords[] = {
#include "800484ec_words.inc"
};
static const uint32_t kCamera80053B20Words[] = {
#include "80053b20_words.inc"
};
static const uint32_t kCamera8004787CWords[] = {
#include "8004787c_words.inc"
};
static const uint32_t kCamera800478B8Words[] = {
#include "800478b8_words.inc"
};
static const uint32_t kCamera80047948Words[] = {
#include "80047948_words.inc"
};
static const uint32_t kCamera80054340Words[] = {
#include "80054340_words.inc"
};
static const uint32_t kCamera80054430Words[] = {
#include "80054430_words.inc"
};
static const uint32_t kCamera800544F8Words[] = {
#include "800544f8_words.inc"
};
static const uint32_t kCamera80047D3CWords[] = {
#include "80047d3c_words.inc"
};
static const uint32_t kSecondGeom80014444Words[] = {
#include "80014444_words.inc"
};
static const uint32_t kSecondGeom8004923CWords[] = {
#include "8004923c_words.inc"
};
static const uint32_t kSecondGeom80014554Words[] = {
#include "80014554_words.inc"
};
static const uint32_t kSecondGeom8002850CWords[] = {
#include "8002850c_words.inc"
};
static const uint32_t kSecondGeom80053AF8Words[] = {
#include "80053af8_words.inc"
};
static const uint32_t kSecondGeom8002823CWords[] = {
#include "8002823c_words.inc"
};
static const uint32_t kSecondGeom80028620Words[] = {
#include "80028620_words.inc"
};
static const uint32_t kDrawEnv80058A4CWords[] = {
#include "80058a4c_words.inc"
};
static const uint32_t kDrawEnv80058B04Words[] = {
#include "80058b04_words.inc"
};
static const uint32_t kDrawEnv80014960Words[] = {
#include "80014960_words.inc"
};
static const uint32_t kDrawEnv80014998Words[] = {
#include "80014998_words.inc"
};
static const uint32_t kClearImage80059888Words[] = {
#include "80059888_words.inc"
};
static const uint32_t kClearImage80059760Words[] = {
#include "80059760_words.inc"
};
static const uint32_t kClearImage8005AF68Words[] = {
#include "8005af68_words.inc"
};
static const uint32_t kGte80047CB4Words[] = {
#include "80047cb4_words.inc"
};
static const uint32_t kGte8004D16CWords[] = {
#include "8004d16c_words.inc"
};
static const uint32_t kGte80053AD8Words[] = {
#include "80053ad8_words.inc"
};
static const uint32_t kGte800491FCWords[] = {
#include "800491fc_words.inc"
};
static const uint32_t kGte8004921CWords[] = {
#include "8004921c_words.inc"
};
static const uint32_t kGte8005CE28Words[] = {
#include "8005ce28_words.inc"
};
static const uint32_t kSys1Words[] = {
#include "8005cf08_words.inc"
};
static const uint32_t kSys2Words[] = {
#include "8005cf18_words.inc"
};

static const uint32_t kInputDigital8005DE78Words[] = {
#include "8005de78_words.inc"
};
static const uint32_t kInputDigital8005E13CWords[] = {
#include "8005e13c_words.inc"
};
static const uint32_t kInputDigital8005E1A4Words[] = {
#include "8005e1a4_words.inc"
};
static const uint32_t kInputDigital8005EA34Words[] = {
#include "8005ea34_words.inc"
};
static const uint32_t kInputDigital8005EA54Words[] = {
#include "8005ea54_words.inc"
};
static const uint32_t kInputDigital8005EA68Words[] = {
#include "8005ea68_words.inc"
};
static const uint32_t kInputDigital8005EA88Words[] = {
#include "8005ea88_words.inc"
};
static const uint32_t kInputDigital8005EAA8Words[] = {
#include "8005eaa8_words.inc"
};
static const uint32_t kInputDigital8005EAC8Words[] = {
#include "8005eac8_words.inc"
};
static const uint32_t kInputDigital8005EB28Words[] = {
#include "8005eb28_words.inc"
};
static const uint32_t kInputDigital8005EC00Words[] = {
#include "8005ec00_words.inc"
};
static const uint32_t kInputDigital8005ECC0Words[] = {
#include "8005ecc0_words.inc"
};
static const uint32_t kInputDigital8005ED4CWords[] = {
#include "8005ed4c_words.inc"
};
static const uint32_t kInputDigital8005F290Words[] = {
#include "8005f290_words.inc"
};
static const uint32_t kInputDigital8005F394Words[] = {
#include "8005f394_words.inc"
};
static const uint32_t kInputDigital8005F450Words[] = {
#include "8005f450_words.inc"
};
static const uint32_t kInputDigital8005F6CCWords[] = {
#include "8005f6cc_words.inc"
};
static const uint32_t kInputDigital8005FA94Words[] = {
#include "8005fa94_words.inc"
};

static const uint32_t kInputVerifierWords[] = {
#include "8005d6cc_words.inc"
};
static const uint32_t kInputHandlerWords[] = {
#include "8005d734_words.inc"
};
static const uint32_t kInputHandlerClear8005D8A0Words[] = {
#include "8005d8a0_words.inc"
};
static const uint32_t kInputStop8005D980Words[] = {
#include "8005d980_words.inc"
};
static const uint32_t kInputSerialStartWords[] = {
#include "8005d9c4_words.inc"
};
static const uint32_t kInputSerialNextWords[] = {
#include "8005dbd8_words.inc"
};
static const uint32_t kInputSerialDispatchWords[] = {
#include "8005eae8_words.inc"
};
static const uint32_t kInputSerialPadWords[] = {
#include "8005f75c_words.inc"
};
static const uint32_t kInputSerialTransferWords[] = {
#include "8005dca0_words.inc"
};
static const uint32_t kInputSerialIrqWords[] = {
#include "8005e0ac_words.inc"
};
static const uint32_t kInputTimerStartWords[] = {
#include "8005fba8_words.inc"
};
static const uint32_t kInputTimerPollWords[] = {
#include "8005fbc8_words.inc"
};
static const uint32_t kInputResponseWords[] = {
#include "8005f830_words.inc"
};
static const uint32_t kInputResponseStatusWords[] = {
#include "8005fb70_words.inc"
};
static const uint32_t kInputResponseModeWords[] = {
#include "8005e228_words.inc"
};
static const uint32_t kInputResponse8005E374Words[] = {
#include "8005e374_words.inc"
};
static const uint32_t kInputResponse8005E3ACWords[] = {
#include "8005e3ac_words.inc"
};
static const uint32_t kInputResponseClearWords[] = {
#include "8005f384_words.inc"
};
static const uint32_t kEventRegisterWords[] = {
#include "8006189c_words.inc"
};
static const uint32_t kEventTestWords[] = {
#include "80061b58_words.inc"
};
static const uint32_t kEventCallbackWords[8][5] = {
{
#include "800617cc_words.inc"
},
{
#include "800617e0_words.inc"
},
{
#include "800617f4_words.inc"
},
{
#include "80061808_words.inc"
},
{
#include "8006181c_words.inc"
},
{
#include "80061830_words.inc"
},
{
#include "80061844_words.inc"
},
{
#include "80061858_words.inc"
},
};

extern void func_8005C388_native(int32_t value, uint8_t *classification,
                                 int32_t *column, void *userdata);

/* The generated initializer is derived at configure time from the exact
 * inline-assembly overlay. Keeping it in the native build proves that no
 * retail media or separately transcribed opcode table is being consumed. */
static const uint32_t kFormatter8005C640Words[] = {
#include "8005c640_words.inc"
};
static const uint32_t kFormatter8005C604Words[] = {
#include "8005c604_words.inc"
};
static const uint32_t kResetGraph80059234Words[] = {
#include "80059234_words.inc"
};
static const uint32_t kCallbackWrapper80042580Words[] = {
#include "80042580_words.inc"
};
static const uint32_t kCallbackDispatch80042644Words[] = {
#include "80042644_words.inc"
};
static const uint32_t kCallbackInitializer80042718Words[] = {
#include "80042718_words.inc"
};
static const uint32_t kCallbackInstaller80042C90Words[] = {
#include "80042c90_words.inc"
};
static const uint32_t kCallbackSlotWrite80042D60Words[] = {
#include "80042d60_words.inc"
};
static const uint32_t kCallbackChannelInstaller80042DB8Words[] = {
#include "80042db8_words.inc"
};
static const uint32_t kStartupMode800594CCWords[] = {
#include "800594cc_words.inc"
};
static const uint32_t kStartupGraphics80059658Words[] = {
#include "80059658_words.inc"
};
static const uint32_t kFinalInit800142C8Words[] = {
#include "800142c8_words.inc"
};
static const uint32_t kPostRecordClear80018FC8Words[] = {
#include "80018fc8_words.inc"
};
static const uint32_t kStartupRecordSetup80018918Words[] = {
#include "80018918_words.inc"
};
static const uint32_t kStartupGlobalReset8001B324Words[] = {
#include "8001b324_words.inc"
};
static const uint32_t kStartupGlobalResetLeaf8001B34CWords[] = {
#include "8001b34c_words.inc"
};
static const uint32_t kStartupSelector2C80028FDCWords[] = {
#include "80028fdc_words.inc"
};
static const uint32_t kStartupSelector2D80029020Words[] = {
#include "80029020_words.inc"
};
static const uint32_t kStartupSelectorStore800291A0Words[] = {
#include "800291a0_words.inc"
};
static const uint32_t kStartupBit0C80028DBCWords[] = {
#include "80028dbc_words.inc"
};
static const uint32_t kStartupBit0D80028E00Words[] = {
#include "80028e00_words.inc"
};
static const uint32_t kStartupBitStore80029124Words[] = {
#include "80029124_words.inc"
};
static const uint32_t kCdStart8005FC68Words[] = {
#include "8005fc68_words.inc"
};
static const uint32_t kCdInit8006186CWords[] = {
#include "8006186c_words.inc"
};
static const uint32_t kCdInitA800622D0Words[] = {
#include "800622d0_words.inc"
};
static const uint32_t kCdInitB80062328Words[] = {
#include "80062328_words.inc"
};
static const uint32_t kCdCallback80062394Words[] = {
#include "80062394_words.inc"
};
static const uint32_t kEventStart8005FCB8Words[] = {
#include "8005fcb8_words.inc"
};
static const uint32_t kEventReset80062888Words[] = {
#include "80062888_words.inc"
};
static const uint32_t kStartupAllocatorPrefix8005F0C8Words[] = {
#include "8005f0c8_words.inc"
};
static const uint32_t kStartupCallbackTable8005F728Words[] = {
#include "8005f728_words.inc"
};
static const uint32_t kGuardedClear8005C2C8Words[] = {
#include "8005c2c8_words.inc"
};
static const uint32_t kStartupTableInit8005D6A0Words[] = {
#include "8005d6a0_words.inc"
};
static const uint32_t kInputStartupWrapper8005D0F8Words[] = {
#include "8005d0f8_words.inc"
};
static const uint32_t kInputStartupPrefix8005D8B4Words[] = {
#include "8005d8b4_words.inc"
};
static const uint32_t kInputRecordCallback8005F228Words[] = {
#include "8005f228_words.inc"
};
/* Assembly-backed continuation bridge, not a recovered C implementation. */
static const uint32_t kCdCommandFullWords[] = {
#include "80044670_full_words.inc"
};
_Static_assert(sizeof(kCdCommandFullWords) / sizeof(kCdCommandFullWords[0]) == 263,
               "80044670 full instruction count changed");
static const uint32_t kStartupRetry80043450Words[] = {
#include "80043450_words.inc"
};
static const uint32_t kStartupRetryAlternate80044BF4Words[] = {
#include "80044bf4_words.inc"
};
static const uint32_t kStartupCallbackSetter8004359CWords[] = {
#include "8004359c_words.inc"
};
static const uint32_t kStartupCallbackSetter800435B4Words[] = {
#include "800435b4_words.inc"
};
static const uint32_t kStartupCallbackSetter8004654CWords[] = {
#include "8004654c_words.inc"
};
static const uint32_t kStartupCallbackControl80046564Words[] = {
#include "80046564_words.inc"
};
static const uint32_t kCdInitializer80044D38Words[] = {
#include "80044d38_words.inc"
};
static const uint32_t kCdCommandPrefix80044670Words[] = {
#include "80044670_words.inc"
};
static const uint32_t kCdCommandContinuation800446D4Words[] = {
#include "800446d4_words.inc"
};
static const uint32_t kTickQuery8004239CMinusOneWords[] = {
#include "8004239c_minus_one_words.inc"
};
/* Exact first-two-call SPU streams. Split bodies remain contiguous;
 * the outer caller is admitted through the common-attribute return at8002C974. */
static const uint32_t kSpu8003BE24Words[] = {
#include "8003be24_words.inc"
};
_Static_assert(sizeof(kSpu8003BE24Words) / sizeof(uint32_t) == 20,
               "SPU 8003BE24 source span changed");
static const uint32_t kSpu8003B3D0Words[] = {
#include "8003b3d0_words.inc"
};
_Static_assert(sizeof(kSpu8003B3D0Words) / sizeof(uint32_t) == 35,
               "SPU 8003B3D0 source span changed");
static const uint32_t kSpu8002D1F0Words[] = {
#include "8002d1f0_words.inc"
};
_Static_assert(sizeof(kSpu8002D1F0Words) / sizeof(uint32_t) == 20,
               "SPU 8002D1F0 source span changed");
static const uint32_t kSpu8003B45CWords[] = {
#include "8003b45c_words.inc"
};
_Static_assert(sizeof(kSpu8003B45CWords) / sizeof(uint32_t) == 318,
               "SPU 8003B45C source span changed");
static const uint32_t kSpu8003B954Words[] = {
#include "8003b954_words.inc"
};
_Static_assert(sizeof(kSpu8003B954Words) / sizeof(uint32_t) == 308,
               "SPU 8003B954 source span changed");
static const uint32_t kSpu8003B280Words[] = {
#include "8003b280_words.inc"
};
_Static_assert(sizeof(kSpu8003B280Words) / sizeof(uint32_t) == 52,
               "SPU 8003B280 source span changed");
static const uint32_t kFile80019A24Words[] = {
#include "80019a24_words.inc"
};
_Static_assert(sizeof(kFile80019A24Words) / sizeof(uint32_t) == 53,
               "LIST source 80019A24 span changed");
static const uint32_t kFile80034B98Words[] = {
#include "80034b98_words.inc"
};
_Static_assert(sizeof(kFile80034B98Words) / sizeof(uint32_t) == 35,
               "LIST source 80034B98 span changed");
static const uint32_t kFile80019AF8Words[] = {
#include "80019af8_words.inc"
};
_Static_assert(sizeof(kFile80019AF8Words) / sizeof(uint32_t) == 385,
               "LIST source 80019AF8 span changed");
static const uint32_t kFile8001A338Words[] = {
#include "8001a338_words.inc"
};
_Static_assert(sizeof(kFile8001A338Words) / sizeof(uint32_t) == 424,
               "LIST source 8001A338 span changed");
static const uint32_t kFile8004355CWords[] = {
#include "8004355c_words.inc"
};
_Static_assert(sizeof(kFile8004355CWords) / sizeof(uint32_t) == 8,
               "LIST source 8004355C span changed");
static const uint32_t kFile8004239CWords[] = {
#include "8004239c_words.inc"
};
_Static_assert(sizeof(kFile8004239CWords) / sizeof(uint32_t) == 26,
               "LIST source 8004239C span changed");
static const uint32_t kFile80042404Words[] = {
#include "80042404_words.inc"
};
_Static_assert(sizeof(kFile80042404Words) / sizeof(uint32_t) == 56,
               "LIST source 80042404 span changed");
static const uint32_t kFile800424E4Words[] = {
#include "800424e4_words.inc"
};
_Static_assert(sizeof(kFile800424E4Words) / sizeof(uint32_t) == 39,
               "LIST source 800424E4 span changed");
static const uint32_t kFile80044DBCWords[] = {
#include "80044dbc_words.inc"
};
_Static_assert(sizeof(kFile80044DBCWords) / sizeof(uint32_t) == 26,
               "LIST source 80044DBC span changed");
static const uint32_t kFile8001971CWords[] = {
#include "8001971c_words.inc"
};
_Static_assert(sizeof(kFile8001971CWords) / sizeof(uint32_t) == 133,
               "File loader 8001971C source span changed");
static const uint32_t kFile80019990Words[] = {
#include "80019990_words.inc"
};
_Static_assert(sizeof(kFile80019990Words) / sizeof(uint32_t) == 32,
               "File loader 80019990 source span changed");
static const uint32_t kFile80045374Words[] = {
#include "80045374_words.inc"
};
_Static_assert(sizeof(kFile80045374Words) / sizeof(uint32_t) == 179,
               "File search 80045374 source span changed");
static const uint32_t kFile80045640Words[] = {
#include "80045640_words.inc"
};
_Static_assert(sizeof(kFile80045640Words) / sizeof(uint32_t) == 8,
               "PVD identifier helper 80045640 source span changed");
static const uint32_t kFile80045660Words[] = {
#include "80045660_words.inc"
};
_Static_assert(sizeof(kFile80045660Words) / sizeof(uint32_t) == 184,
               "ISO reader 80045660 source span changed");
static const uint32_t kFile80045940Words[] = {
#include "80045940_words.inc"
};
_Static_assert(sizeof(kFile80045940Words) / sizeof(uint32_t) == 42,
               "Directory lookup 80045940 source span changed");
static const uint32_t kFile800459E8Words[] = {
#include "800459e8_words.inc"
};
_Static_assert(sizeof(kFile800459E8Words) / sizeof(uint32_t) == 171,
               "Directory parser 800459E8 source span changed");
static const uint32_t kFile8005C324Words[] = {
#include "8005c324_words.inc"
};
_Static_assert(sizeof(kFile8005C324Words) / sizeof(uint32_t) == 13,
               "PVD copy helper 8005C324 source span changed");
static const uint32_t kFile8005C358Words[] = {
#include "8005c358_words.inc"
};
_Static_assert(sizeof(kFile8005C358Words) / sizeof(uint32_t) == 12,
               "byte-fill helper 8005C358 source span changed");
static const uint32_t kFile80045C94Words[] = {
#include "80045c94_words.inc"
};
_Static_assert(sizeof(kFile80045C94Words) / sizeof(uint32_t) == 27,
               "ISO sector request 80045C94 source span changed");
static const uint32_t kFile80043A18Words[] = {
#include "80043a18_words.inc"
};
_Static_assert(sizeof(kFile80043A18Words) / sizeof(uint32_t) == 65,
               "Sector to BCD 80043A18 source span changed");
static const uint32_t kFile80043398Words[] = {
#include "80043398_words.inc"
};
_Static_assert(sizeof(kFile80043398Words) / sizeof(uint32_t) == 10,
               "CD read 80043398 source span changed");
static const uint32_t kFile800433C0Words[] = {
#include "800433c0_words.inc"
};
_Static_assert(sizeof(kFile800433C0Words) / sizeof(uint32_t) == 10,
               "CD read 800433C0 source span changed");
static const uint32_t kFile800433E8Words[] = {
#include "800433e8_words.inc"
};
_Static_assert(sizeof(kFile800433E8Words) / sizeof(uint32_t) == 10,
               "CD read 800433E8 source span changed");
static const uint32_t kFile80043410Words[] = {
#include "80043410_words.inc"
};
_Static_assert(sizeof(kFile80043410Words) / sizeof(uint32_t) == 4,
               "CD read 80043410 source span changed");
static const uint32_t kFile800435CCWords[] = {
#include "800435cc_words.inc"
};
_Static_assert(sizeof(kFile800435CCWords) / sizeof(uint32_t) == 78,
               "CD read 800435CC source span changed");
static const uint32_t kFile80043704Words[] = {
#include "80043704_words.inc"
};
_Static_assert(sizeof(kFile80043704Words) / sizeof(uint32_t) == 75,
               "CD read 80043704 source span changed");
static const uint32_t kFile80043994Words[] = {
#include "80043994_words.inc"
};
_Static_assert(sizeof(kFile80043994Words) / sizeof(uint32_t) == 8,
               "CD read 80043994 source span changed");
static const uint32_t kFile80043B1CWords[] = {
#include "80043b1c_words.inc"
};
_Static_assert(sizeof(kFile80043B1CWords) / sizeof(uint32_t) == 32,
               "CD read 80043B1C source span changed");
static const uint32_t kFile800443A4Words[] = {
#include "800443a4_words.inc"
};
_Static_assert(sizeof(kFile800443A4Words) / sizeof(uint32_t) == 179,
               "CD sync 800443A4 source span changed");
static const uint32_t kFile80045090Words[] = {
#include "80045090_words.inc"
};
_Static_assert(sizeof(kFile80045090Words) / sizeof(uint32_t) == 64,
               "CD read 80045090 source span changed");
static const uint32_t kFile80045D00Words[] = {
#include "80045d00_words.inc"
};
_Static_assert(sizeof(kFile80045D00Words) / sizeof(uint32_t) == 180,
               "CD read 80045D00 source span changed");
static const uint32_t kFile800460CCWords[] = {
#include "800460cc_words.inc"
};
_Static_assert(sizeof(kFile800460CCWords) / sizeof(uint32_t) == 133,
               "CD read 800460CC source span changed");
static const uint32_t kFile8004637CWords[] = {
#include "8004637c_words.inc"
};
_Static_assert(sizeof(kFile8004637CWords) / sizeof(uint32_t) == 65,
               "CD read 8004637C source span changed");
static const uint32_t kFile80046480Words[] = {
#include "80046480_words.inc"
};
_Static_assert(sizeof(kFile80046480Words) / sizeof(uint32_t) == 51,
               "CD read 80046480 source span changed");
static const uint32_t kFile8005C584Words[] = {
#include "8005c584_words.inc"
};
_Static_assert(sizeof(kFile8005C584Words) / sizeof(uint32_t) == 32,
               "8005C584 source export changed");
static const uint32_t kFile8005C4DCWords[] = {
#include "8005c4dc_words.inc"
};
_Static_assert(sizeof(kFile8005C4DCWords) / sizeof(uint32_t) == 25,
               "Directory compare 8005C4DC source span changed");
static const uint32_t kFile8005CE68Words[] = {
#include "8005ce68_words.inc"
};
_Static_assert(sizeof(kFile8005CE68Words) / sizeof(uint32_t) == 3,
               "CD read 8005CE68 source span changed");
static const uint32_t kFile8005CEA8Words[] = {
#include "8005cea8_words.inc"
};
_Static_assert(sizeof(kFile8005CEA8Words) / sizeof(uint32_t) == 3,
               "BIOS TestEvent 8005CEA8 source span changed");
static const uint32_t kFile80043420Words[] = {
#include "80043420_words.inc"
};
_Static_assert(sizeof(kFile80043420Words) / sizeof(uint32_t) == 4,
               "CD query 80043420 source span changed");
static const uint32_t kFile80043440Words[] = {
#include "80043440_words.inc"
};
_Static_assert(sizeof(kFile80043440Words) / sizeof(uint32_t) == 4,
               "CD query 80043440 source span changed");
static const uint32_t kFile8004357CWords[] = {
#include "8004357c_words.inc"
};
_Static_assert(sizeof(kFile8004357CWords) / sizeof(uint32_t) == 8,
               "CD query 8004357C source span changed");
static const uint32_t kSpu80037D98Words[] = {
#include "80037d98_words.inc"
};
_Static_assert(sizeof(kSpu80037D98Words) / sizeof(uint32_t) == 66,
               "Sound 80037D98 source span changed");
static const uint32_t kSpu8003D424Words[] = {
#include "8003d424_words.inc"
};
_Static_assert(sizeof(kSpu8003D424Words) / sizeof(uint32_t) == 4,
               "Sound 8003D424 source span changed");
static const uint32_t kSpu8002CC4CWords[] = {
#include "8002cc4c_words.inc"
};
_Static_assert(sizeof(kSpu8002CC4CWords) / sizeof(uint32_t) == 26,
               "Sound 8002CC4C source span changed");
static const uint32_t kSpu8002FAE0Words[] = {
#include "8002fae0_words.inc"
};
_Static_assert(sizeof(kSpu8002FAE0Words) / sizeof(uint32_t) == 10,
               "Sound 8002FAE0 source span changed");
static const uint32_t kSpu8002C8BCWords[] = {
#include "8002c8bc_words.inc"
};
_Static_assert(sizeof(kSpu8002C8BCWords) / sizeof(uint32_t) == 14,
               "Sound 8002C8BC source span changed");
static const uint32_t kSpu80037CC8Words[] = {
#include "80037cc8_words.inc"
};
_Static_assert(sizeof(kSpu80037CC8Words) / sizeof(uint32_t) == 4,
               "Sound 80037CC8 source span changed");
static const uint32_t kSpu8003BE74Words[] = {
#include "8003be74_words.inc"
};
_Static_assert(sizeof(kSpu8003BE74Words) / sizeof(uint32_t) == 9,
               "Sound 8003BE74 source span changed");
static const uint32_t kSpu8003BE98Words[] = {
#include "8003be98_words.inc"
};
_Static_assert(sizeof(kSpu8003BE98Words) / sizeof(uint32_t) == 130,
               "Sound 8003BE98 source span changed");
static const uint32_t kSpu8003B1ECWords[] = {
#include "8003b1ec_words.inc"
};
_Static_assert(sizeof(kSpu8003B1ECWords) / sizeof(uint32_t) == 25,
               "Sound 8003B1EC source span changed");
static const uint32_t kSpu80034C24Words[] = {
#include "80034c24_words.inc"
};
_Static_assert(sizeof(kSpu80034C24Words) / sizeof(uint32_t) == 51,
               "Sound 80034C24 source span changed");
static const uint32_t kSpu800430B8Words[] = {
#include "800430b8_words.inc"
};
_Static_assert(sizeof(kSpu800430B8Words) / sizeof(uint32_t) == 9,
               "Sound 800430B8 source span changed");
static const uint32_t kSpu800430DCWords[] = {
#include "800430dc_words.inc"
};
_Static_assert(sizeof(kSpu800430DCWords) / sizeof(uint32_t) == 137,
               "Sound 800430DC source span changed");
static const uint32_t kSpu80043830Words[] = {
#include "80043830_words.inc"
};
_Static_assert(sizeof(kSpu80043830Words) / sizeof(uint32_t) == 81,
               "Sound 80043830 source span changed");
static const uint32_t kSpu80037004Words[] = {
#include "80037004_words.inc"
};
_Static_assert(sizeof(kSpu80037004Words) / sizeof(uint32_t) == 9,
               "Sound 80037004 source span changed");
static const uint32_t kSpu8003C598Words[] = {
#include "8003c598_words.inc"
};
_Static_assert(sizeof(kSpu8003C598Words) / sizeof(uint32_t) == 229,
               "8003C598 source export changed");
static const uint32_t kSpu8002C8F4Words[] = {
#include "8002c8f4_words.inc"
};
_Static_assert(sizeof(kSpu8002C8F4Words) / sizeof(uint32_t) == 214,
               "8002C8F4 source export changed");
static const uint32_t kSpu8003A424Words[] = {
#include "8003a424_words.inc"
};
_Static_assert(sizeof(kSpu8003A424Words) / sizeof(uint32_t) == 8,
               "8003A424 source export changed");
static const uint32_t kSpu8003A444Words[] = {
#include "8003a444_words.inc"
};
_Static_assert(sizeof(kSpu8003A444Words) / sizeof(uint32_t) == 62,
               "8003A444 source export changed");
static const uint32_t kSpu8003A53CWords[] = {
#include "8003a53c_words.inc"
};
_Static_assert(sizeof(kSpu8003A53CWords) / sizeof(uint32_t) == 31,
               "8003A53C source export changed");
static const uint32_t kSpu8003A5B8Words[] = {
#include "8003a5b8_words.inc"
};
_Static_assert(sizeof(kSpu8003A5B8Words) / sizeof(uint32_t) == 165,
               "8003A5B8 source export changed");
static const uint32_t kSpu8003A84CWords[] = {
#include "8003a84c_words.inc"
};
_Static_assert(sizeof(kSpu8003A84CWords) / sizeof(uint32_t) == 115,
               "8003A84C source export changed");
static const uint32_t kSpu8003AF04Words[] = {
#include "8003af04_words.inc"
};
_Static_assert(sizeof(kSpu8003AF04Words) / sizeof(uint32_t) == 18,
               "8003AF04 source export changed");
static const uint32_t kSpu8003B0E4Words[] = {
#include "8003b0e4_words.inc"
};
_Static_assert(sizeof(kSpu8003B0E4Words) / sizeof(uint32_t) == 26,
               "8003B0E4 source export changed");
static const uint32_t kSpu8003B14CWords[] = {
#include "8003b14c_words.inc"
};
_Static_assert(sizeof(kSpu8003B14CWords) / sizeof(uint32_t) == 9,
               "8003B14C source export changed");
static const uint32_t kSpu8003D518Words[] = {
#include "8003d518_words.inc"
};
_Static_assert(sizeof(kSpu8003D518Words) / sizeof(uint32_t) == 12,
               "8003D518 source export changed");
static const uint32_t kSpu8003D548Words[] = {
#include "8003d548_words.inc"
};
_Static_assert(sizeof(kSpu8003D548Words) / sizeof(uint32_t) == 58,
               "8003D548 source export changed");
static const uint32_t kSpu8003FE3CWords[] = {
#include "8003fe3c_words.inc"
};
_Static_assert(sizeof(kSpu8003FE3CWords) / sizeof(uint32_t) == 196,
               "8003FE3C source export changed");
static const uint32_t kSpu8004014CWords[] = {
#include "8004014c_words.inc"
};
_Static_assert(sizeof(kSpu8004014CWords) / sizeof(uint32_t) == 21,
               "8004014C source export changed");
static const uint32_t kSpu800401A0Words[] = {
#include "800401a0_words.inc"
};
_Static_assert(sizeof(kSpu800401A0Words) / sizeof(uint32_t) == 11,
               "800401A0 source export changed");
static const uint32_t kSpu80040868Words[] = {
#include "80040868_words.inc"
};
_Static_assert(sizeof(kSpu80040868Words) / sizeof(uint32_t) == 52,
               "80040868 source export changed");
static const uint32_t kSpu8003FA64Words[] = {
#include "8003fa64_words.inc"
};
_Static_assert(sizeof(kSpu8003FA64Words) / sizeof(uint32_t) == 237,
               "8003FA64 source export changed");
static const uint32_t kSpu800425E0Words[] = {
#include "800425e0_words.inc"
};
_Static_assert(sizeof(kSpu800425E0Words) / sizeof(uint32_t) == 12,
               "800425E0 source export changed");
static const uint32_t kSpu80042F8CWords[] = {
#include "80042f8c_words.inc"
};
_Static_assert(sizeof(kSpu80042F8CWords) / sizeof(uint32_t) == 42,
               "80042F8C source export changed");
static const uint32_t kReadyQuery800426D4Words[] = {
#include "800426d4_words.inc"
};
static const uint32_t kStatusFirstPoll80044124Words[] = {
#include "80044124_first_poll_words.inc"
};
static const uint32_t kStatusTimeout80044198Words[] = {
#include "80044198_timeout_prefix_words.inc"
};
static const uint32_t kStatusDiagnostic800441D8Words[] = {
#include "800441d8_diagnostic_prefix_words.inc"
};
static const uint32_t kStatusLoop80044250Words[] = {
#include "80044250_status_loop_words.inc"
};
/* 80043B9C has not been promoted to a C decompilation yet. This bridge is
 * deliberately generated from tracked, audited assembly rather than media. */
static const uint32_t kStatusWorker80043B9CWords[] = {
#include "80043b9c_words.inc"
};
static const uint32_t kCdIrq80045290Words[] = {
#include "80045290_words.inc"
};
static const uint32_t kCdStateReset80044B14Words[] = {
#include "80044b14_words.inc"
};
static const uint32_t kCdStateResetWrapper800434BCWords[] = {
#include "800434bc_words.inc"
};
static const uint32_t kStartupDispatcher80043300Words[] = {
#include "80043300_words.inc"
};
static const uint32_t kSavedContext8005CD98Words[] = {
#include "8005cd98_words.inc"
};
static const uint32_t kStartup800141F0Words[] = {
#include "800141f0_words.inc"
};

enum {
    FORMATTER_ENTRY = 0x8005c640u,
    FORMATTER_END = 0x8005ccc8u,
    FORMATTER_WRAPPER_ENTRY = 0x8005c604u,
    FORMATTER_WRAPPER_END = 0x8005c640u,
    RESETGRAPH_ENTRY = 0x80059234u,
    RESETGRAPH_END = 0x800593b8u,
    CALLBACK_WRAPPER_ENTRY = 0x80042580u,
    CALLBACK_WRAPPER_END = 0x800425b0u,
    CALLBACK_DISPATCH_ENTRY = 0x80042644u,
    CALLBACK_DISPATCH_END = 0x80042674u,
    CALLBACK_INITIALIZER = 0x80042718u,
    CALLBACK_INITIALIZER_END = 0x800427f4u,
    CALLBACK_INSTALLER_ENTRY = 0x80042c90u,
    CALLBACK_INSTALLER_END = 0x80042ce8u,
    CALLBACK_SLOT_WRITE_ENTRY = 0x80042d60u,
    CALLBACK_SLOT_WRITE_END = 0x80042d8cu,
    CALLBACK_CHANNEL_INSTALLER_ENTRY = 0x80042db8u,
    CALLBACK_CHANNEL_INSTALLER_END = 0x80042e08u,
    SAVED_CONTEXT_ENTRY = 0x8005cd98u,
    SAVED_CONTEXT_END = 0x8005ce10u,
    STARTUP_ENTRY = 0x800141f0u,
    STARTUP_END = 0x80014238u,
    RESETGRAPH_FILL = 0x8005c29cu,
    CALLBACK_CLEAR = 0x80042c64u,
    CALLBACK_BIOS_B0_19 = 0x8005cef8u,
    CALLBACK_INSTALLER = 0x80042c90u,
    CALLBACK_INSTALLER_CLEAR = 0x80042d8cu,
    CALLBACK_CHANNEL_CLEAR = 0x80043034u,
    CALLBACK_REGISTER_WRAPPER = 0x800425b0u,
    CALLBACK_CHANNEL_INSTALLER = 0x80042db8u,
    CALLBACK_BIOS_A0_72 = 0x8005ce50u,
    CALLBACK_EXIT_CRITICAL = 0x8005cf18u,
    CALLBACK_INITIALIZER_RETURN = 0x800427f0u,
    STARTUP_AFTER_RESETGRAPH = 0x800594ccu,
    STARTUP_MODE_END = 0x80059530u,
    STARTUP_AFTER_MODE = 0x80059658u,
    STARTUP_GRAPHICS_END = 0x800596f4u,
    STARTUP_GRAPHICS_RESET = 0x8005b684u,
    RESETGRAPH_GPU_CW = 0x8005ce38u,
    RESETGRAPH_DEVICE_RESET = 0x8005bd7cu,
    STARTUP_ENVIRONMENT_CLEAR = 0x80016714u,
    STARTUP_FINAL_INIT = 0x800142c8u,
    STARTUP_FINAL_INIT_END = 0x80014338u,
    STARTUP_CLEAR_29044 = 0x80029044u,
    STARTUP_CLEAR_2906C = 0x8002906cu,
    STARTUP_CLEAR_29094 = 0x80029094u,
    STARTUP_CLEAR_29218 = 0x80029218u,
    STARTUP_RECORD_CLEAR = 0x8001903cu,
    STARTUP_AFTER_RECORD_CLEAR = 0x80018fc8u,
    STARTUP_AFTER_RECORD_CLEAR_END = 0x80019018u,
    STARTUP_RECORD_SETUP = 0x80018918u,
    STARTUP_RECORD_SETUP_END = 0x800189a8u,
    STARTUP_AFTER_POST_RECORD_CLEAR = 0x8001b324u,
    STARTUP_AFTER_POST_RECORD_CLEAR_END = 0x8001b34cu,
    STARTUP_GLOBAL_RESET_LEAF = 0x8001b34cu,
    STARTUP_GLOBAL_RESET_LEAF_END = 0x8001b374u,
    STARTUP_AFTER_GLOBAL_RESET = 0x80028fdcu,
    STARTUP_SELECTOR_2C_END = 0x80029000u,
    STARTUP_SELECTOR_2D = 0x80029020u,
    STARTUP_SELECTOR_2D_END = 0x80029044u,
    STARTUP_SELECTOR_STORE = 0x800291a0u,
    STARTUP_SELECTOR_STORE_END = 0x800291b4u,
    STARTUP_AFTER_SELECTOR_STORES = 0x80028dbcu,
    STARTUP_BIT_0C_END = 0x80028de0u,
    STARTUP_BIT_0D = 0x80028e00u,
    STARTUP_BIT_0D_END = 0x80028e24u,
    STARTUP_BIT_STORE = 0x80029124u,
    STARTUP_BIT_STORE_END = 0x80029178u,
    STARTUP_FINAL_INIT_RETURN = 0x80014330u,
    CD_START = 0x8005fc68u,
    CD_START_END = 0x8005fc98u,
    CD_INIT = 0x8006186cu,
    CD_INIT_END = 0x8006189cu,
    CD_INIT_A = 0x800622d0u,
    CD_INIT_A_END = 0x80062328u,
    CD_INIT_B = 0x80062328u,
    CD_INIT_B_END = 0x80062360u,
    CD_CALLBACK = 0x80062394u,
    CD_CALLBACK_END = 0x800623a4u,
    CD_ENTER_CRITICAL = 0x8005cf08u,
    CD_EXIT_CRITICAL = 0x8005cf18u,
    CD_B0_5B = 0x8005cf48u,
    CD_B0_4A = 0x800627d8u,
    CD_B0_4B = 0x800627e8u,
    CD_A0_70 = 0x80061f38u,
    EVENT_START = 0x8005fcb8u,
    EVENT_START_END = 0x8005fd18u,
    EVENT_RESET = 0x80062888u,
    EVENT_RESET_END = 0x8006289cu,
    STARTUP_ALLOCATOR_PREFIX = 0x8005f0c8u,
    STARTUP_ALLOCATOR_PREFIX_END = 0x8005f228u,
    STARTUP_CALLBACK_TABLE = 0x8005f728u,
    STARTUP_CALLBACK_TABLE_END = 0x8005f75cu,
    STARTUP_GUARDED_CLEAR = 0x8005c2c8u,
    STARTUP_GUARDED_CLEAR_END = 0x8005c2f8u,
    STARTUP_TABLE_INIT = 0x8005d6a0u,
    STARTUP_TABLE_INIT_END = 0x8005d6ccu,
    INPUT_STARTUP_WRAPPER = 0x8005d0f8u,
    INPUT_STARTUP_WRAPPER_END = 0x8005d118u,
    INPUT_STARTUP_PREFIX = 0x8005d8b4u,
    INPUT_STARTUP_PREFIX_END = 0x8005d980u,
    INPUT_RECORD_CALLBACK = 0x8005f228u,
    INPUT_RECORD_CALLBACK_END = 0x8005f290u,
    INPUT_C0_3 = 0x8005e178u,
    INPUT_C0_2 = 0x8005e168u,
    INPUT_C0_0A = 0x8005cf58u,
    STARTUP_RETRY = 0x80043450u,
    STARTUP_RETRY_END = 0x800434bcu,
    STARTUP_RETRY_PROBE = 0x80044d38u,
    CD_INITIALIZER = 0x80044dbcu,
    CD_INITIALIZER_CALL = 0x80044e94u,
    CD_INITIALIZER_END = 0x80044f24u,
    CD_INITIALIZER_STRING_EMIT = 0x8005cd48u,
    CD_INITIALIZER_COMMAND = 0x80044670u,
    CD_COMMAND_PREFIX_END = 0x800446d4u,
    CD_COMMAND_CONTINUATION = 0x800446d4u,
    CD_COMMAND_CONTINUATION_END = 0x8004473cu,
    CD_COMMAND_END = 0x80044a8cu,
    CD_COMMAND_STATUS = 0x80044124u,
    TICK_QUERY_ENTRY = 0x8004239cu,
    TICK_QUERY_BRANCH_END = 0x80042400u,
    TICK_QUERY_RETURN = 0x800424ccu,
    TICK_QUERY_RETURN_END = 0x800424e4u,
    STATUS_FIRST_POLL = 0x80044124u,
    STATUS_FIRST_POLL_END = 0x80044198u,
    STATUS_TIMEOUT = 0x80044198u,
    STATUS_TIMEOUT_END = 0x800441d8u,
    STATUS_TIMEOUT_DIAGNOSTIC = 0x800441d8u,
    STATUS_TIMEOUT_CONTINUE = 0x8004424cu,
    STATUS_DIAGNOSTIC_END = 0x8004424cu,
    STATUS_POST_DIAGNOSTIC = 0x80044250u,
    STATUS_LOOP_END = 0x800443a4u,
    STATUS_READY_QUERY = 0x800426d4u,
    STATUS_CALLBACK_QUERY = 0x80043b9cu,
    STATUS_WORKER = 0x80043b9cu,
    STATUS_WORKER_END = 0x80044124u,
    CD_STATE_RESET = 0x80044b14u,
    CD_STATE_RESET_END = 0x80044bf4u,
    CD_STATE_RESET_WRAPPER = 0x800434bcu,
    CD_STATE_RESET_WRAPPER_END = 0x800434dcu,
    CD_COMMAND_DIAGNOSTIC = 0x8005c604u,
    STARTUP_RETRY_ALTERNATE = 0x80044bf4u,
    STARTUP_RETRY_ALTERNATE_END = 0x80044ce8u,
    STARTUP_DISPATCH = 0x80043300u,
    STARTUP_DISPATCH_END = 0x80043398u,
    /* 80043300 passes 80043398 as a callback argument to this B0:7 wrapper;
     * the first unbound control transfer is the wrapper itself. */
    STARTUP_DISPATCH_SUCCESS = 0x8004359cu,
    STARTUP_CALLBACK_SETTER_END = 0x800435b4u,
    STARTUP_CALLBACK_SETTER_B = 0x800435b4u,
    STARTUP_CALLBACK_SETTER_B_END = 0x800435ccu,
    STARTUP_CALLBACK_SETTER_C = 0x8004654cu,
    STARTUP_CALLBACK_SETTER_C_END = 0x80046564u,
    STARTUP_CALLBACK_CONTROL = 0x80046564u,
    STARTUP_CALLBACK_CONTROL_END = 0x8004657cu,
    EVENT_REGISTER = 0x8006189cu,
    FORMATTER_CONSOLE_CHAR = 0x8005c388u,
    FORMATTER_SEARCH = 0x8005ccc8u,
    FORMATTER_STRING_LENGTH = 0x8005cd18u,
    FORMATTER_STEP_LIMIT = 1000000u,
    /* Whole cold startup includes source polling and IRQ/device lifetimes.
     * The retained LIST run exhausted 1m during valid directory searches.
     * This host observation budget changes no guest clock or completion. */
    /* Logo/demo/title needs many VSync frames; 10M then 200M exhausted
     * during Square Soft with CD/SPU/epoch healthy. */
    STARTUP_ENTRY_STEP_LIMIT = 2000000000u,
};

typedef struct FormatterCpu {
    uint32_t r[32];
    uint32_t hi, lo;
    uint32_t pc, npc;
    const MusashiCallbackDevice *callback_device;
    const MusashiCdDevice *cd_device;
    const MusashiEventDevice *event_device;
    const MusashiInputDevice *input_device;
    MusashiBiosCallbackFrame *bios_frame;
    MusashiCdIrqFrame *cd_irq_frame;
    const MusashiExecutionClock *clock;
    const MusashiCdRegisterDevice *cd_register_device;
    const MusashiCdSpuDevice *cd_spu_device;
    const MusashiHeapDevice *heap_device;
    const MusashiGpuIoDevice *gpu_io_device;
    const MusashiCpuTransferDevice *cpu_transfer;
    const MusashiBiosImageDevice *bios_image;
    uint32_t merge_value;
    uint32_t merge_next_pc;
    uint8_t merge_reg;
    uint8_t merge_kind;
    uint8_t merge_pending;
    /* MFC2 result belongs to this CPU until its source delay instruction
     * retires; an IRQ or a refused clock must not flush it early. */
    uint32_t gte_load_value;
    uint32_t gte_load_next_pc;
    uint8_t gte_load_reg;
    uint8_t gte_load_pending;
    /* Branch origin survives even an untaken branch's delay slot. */
    uint8_t delay_slot;
    uint32_t branch_pc;
} FormatterCpu;

typedef struct FormatterConsoleContext {
    MusashiConsoleSink sink;
    void *userdata;
} FormatterConsoleContext;

static void *callback_hook_userdata(const MusashiCallbackDevice *device) {
    if (device->hook_entry_int_userdata)
        return device->hook_entry_int_userdata;
    return device->userdata;
}

static int read8(MusashiBootMemory *memory, uint32_t address, uint8_t *value) {
    uint8_t *span = musashi_boot_ram_span(memory, address, 1);
    if (!span)
        return 0;
    *value = *span;
    return 1;
}

static int callback_read16(const FormatterCpu *cpu, uint32_t address, uint16_t *value) {
    if (cpu->input_device && cpu->input_device->read16 &&
        (address == 0x1f801044u || address == 0x1f801048u ||
         address == 0x1f80104au || address == 0x1f80104eu ||
         address == 0x1f801070u || address == 0x1f801074u ||
         address == 0x1f801120u || address == 0x1f801124u || address == 0x1f801128u))
        return cpu->input_device->read16(cpu->input_device->userdata, address, value);
    if (cpu->cd_spu_device && cpu->cd_spu_device->read16 &&
        (address >= 0x1f801c00u && address <= 0x1f801dfeu))
        return cpu->cd_spu_device->read16(cpu->cd_spu_device->userdata, address, value);
    if (!cpu->callback_device || !cpu->callback_device->read16 ||
        (address != 0x1f801070u && address != 0x1f801074u && address != 0x1f801110u))
        return 0;
    *value = cpu->callback_device->read16(cpu->callback_device->userdata, address);
    return 1;
}

static int callback_write16(const FormatterCpu *cpu, uint32_t address, uint16_t value) {
    if (cpu->input_device && cpu->input_device->write16 &&
        (address == 0x1f801048u || address == 0x1f80104au || address == 0x1f80104eu ||
         address == 0x1f801070u || address == 0x1f801074u))
        return cpu->input_device->write16(cpu->input_device->userdata, address, value);
    if (cpu->cd_spu_device && cpu->cd_spu_device->write16 &&
        (address >= 0x1f801c00u && address <= 0x1f801dfeu))
        return cpu->cd_spu_device->write16(cpu->cd_spu_device->userdata, address, value);
    if (!cpu->callback_device || !cpu->callback_device->write16 ||
        (address != 0x1f801070u && address != 0x1f801074u))
        return 0;
    cpu->callback_device->write16(cpu->callback_device->userdata, address, value);
    return 1;
}

static int callback_write32(const FormatterCpu *cpu, uint32_t address, uint32_t value) {
    if (!cpu->callback_device || !cpu->callback_device->write32 ||
        (address != 0x1f8010f0u && address != 0x1f8010f4u &&
         address != 0x1f801114u && address != 0x1f801020u))
        return 0;
    cpu->callback_device->write32(cpu->callback_device->userdata, address, value);
    return 1;
}

static uint8_t *cpu_ram_span(MusashiBootMemory *memory, const FormatterCpu *cpu,
                             uint32_t address, unsigned width) {
    uint32_t physical = address & 0x1fffffffu;
    if (address & (width - 1u)) return NULL;
    if (cpu->bios_image && (!cpu->bios_image->intersects ||
        cpu->bios_image->intersects(address, width))) return NULL;
    if (cpu->bios_frame && physical < 0x10000u) {
        /* Only physical, cached and uncached RAM aliases belong to this
         * dedicated BIOS frame. Never fall through to the game's low RAM. */
        if ((address != physical && address != (physical | 0x80000000u) &&
             address != (physical | 0xa0000000u)) ||
            physical < MUSASHI_BIOS_CALLBACK_STACK_BASE ||
            physical > MUSASHI_BIOS_CALLBACK_STACK_TOP - width) return NULL;
        return cpu->bios_frame->scratch + physical - MUSASHI_BIOS_CALLBACK_STACK_BASE;
    }
    if (memory && physical >= 0x1f800000u && physical + width <= 0x1f800400u) {
        /* 1KB data-cache scratchpad. musashi_boot_ram_span still refuses it. */
        uint32_t kseg = address & 0xe0000000u;
        if (kseg != 0 && kseg != 0x80000000u && kseg != 0xa0000000u) return NULL;
        return memory->scratchpad + (physical - 0x1f800000u);
    }
    return musashi_boot_ram_span(memory, address, width);
}

static int cpu_read8(MusashiBootMemory *memory, const FormatterCpu *cpu,
                      uint32_t address, uint8_t *value) {
    const uint8_t *p = cpu_ram_span(memory, cpu, address, 1);
    uint8_t accepted;
    if (!value) return 0;
    if (p) { *value = *p; return 1; }
    if (address>=0x1f8010f0u && address<=0x1f8010f7u) {
        uint32_t word;
        const MusashiGpuDevice *bus=cpu->callback_device ? cpu->callback_device->reset_device : NULL;
        if (!bus || !bus->read32) return 0;
        word=bus->read32(bus->userdata,address&~3u);
        *value=(uint8_t)(word>>((address&3u)*8u)); return 1;
    }
    if (address == 0x1f801040u && cpu->input_device && cpu->input_device->read8) {
        if (!cpu->input_device->read8(cpu->input_device->userdata, address, &accepted)) return 0;
    } else if (address >= 0x1f801800u && address <= 0x1f801803u &&
               cpu->cd_register_device && cpu->cd_register_device->read8) {
        if (!cpu->cd_register_device->read8(cpu->cd_register_device->userdata, address, &accepted)) return 0;
    } else return 0;
    *value = accepted;
    return 1;
}

static int cpu_write8(MusashiBootMemory *memory, const FormatterCpu *cpu,
                       uint32_t address, uint32_t value) {
    uint8_t *p = cpu_ram_span(memory, cpu, address, 1);
    if (p) { *p = value; return 1; }
    /* On-die DMA registers ignore byte enables: SB drives the full source
     * word shifted by the byte offset. Preserve source high bits here.
     * https://psx-spx.consoledev.net/partialwordwrites/ */
    if (address>=0x1f8010f0u && address<=0x1f8010f7u)
        return callback_write32(cpu,address&~3u,value<<((address&3u)*8u));
    if (address == 0x1f801040u && cpu->input_device && cpu->input_device->write8)
        return cpu->input_device->write8(cpu->input_device->userdata, address, value);
    return address >= 0x1f801800u && address <= 0x1f801803u &&
        cpu->cd_register_device && cpu->cd_register_device->write8 &&
        cpu->cd_register_device->write8(cpu->cd_register_device->userdata, address, value);
}

static int cpu_read16(MusashiBootMemory *memory, const FormatterCpu *cpu,
                       uint32_t address, uint16_t *value) {
    const uint8_t *p = cpu_ram_span(memory, cpu, address, 2);
    uint16_t accepted;
    if (!value || (address & 1u)) return 0;
    if (p) { *value = (uint16_t)(p[0] | (uint16_t)p[1] << 8); return 1; }
    if (!callback_read16(cpu, address, &accepted)) return 0;
    *value = accepted;
    return 1;
}

static int cpu_write16(MusashiBootMemory *memory, const FormatterCpu *cpu,
                        uint32_t address, uint16_t value) {
    uint8_t *p = cpu_ram_span(memory, cpu, address, 2);
    if (address & 1u) return 0;
    if (p) { p[0] = (uint8_t)value; p[1] = (uint8_t)(value >> 8); return 1; }
    return callback_write16(cpu, address, value);
}

static int cpu_read32(MusashiBootMemory *memory, const FormatterCpu *cpu,
                       uint32_t address, uint32_t *value) {
    const uint8_t *p = cpu_ram_span(memory, cpu, address, 4);
    uint32_t accepted;
    if (!value || (address & 3u)) return 0;
    if (cpu->bios_image && cpu->bios_image->intersects &&
        cpu->bios_image->intersects(address, 4)) {
        if (!cpu->bios_image->read32 || !cpu->bios_image->read32(
            cpu->bios_image->userdata, address, &accepted)) return 0;
        *value = accepted;
        return 1;
    }
    if (p) {
        *value = p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
        return 1;
    }
    if ((address == 0x1f801820u || address == 0x1f801824u ||
         (address >= 0x1f801080u && address <= 0x1f801098u) ||
         address == 0x1f801810u || address == 0x1f801814u ||
         address == 0x1f8010a0u || address == 0x1f8010a4u || address == 0x1f8010a8u ||
         address == 0x1f8010e0u || address == 0x1f8010e4u || address == 0x1f8010e8u) &&
        cpu->gpu_io_device) {
        if (!cpu->gpu_io_device->read32 ||
            !cpu->gpu_io_device->read32(cpu->gpu_io_device->userdata,address,&accepted)) return 0;
        *value=accepted;
        return 1;
    }
    if (address == 0x1f801014u || address == 0x1f801018u || address == 0x1f8010b0u ||
        address == 0x1f8010b4u || address == 0x1f8010b8u ||
        address == 0x1f8010c0u || address == 0x1f8010c4u || address == 0x1f8010c8u ||
        (address == 0x1f8010f0u && cpu->cd_register_device && cpu->cd_register_device->read32)) {
        if (!cpu->cd_register_device || !cpu->cd_register_device->read32 ||
            !cpu->cd_register_device->read32(cpu->cd_register_device->userdata, address, &accepted)) return 0;
        *value = accepted;
        return 1;
    }
    if ((address == 0x1f801814u || address == 0x1f8010f0u ||
         address == 0x1f8010f4u) && cpu->callback_device &&
        cpu->callback_device->reset_device &&
        cpu->callback_device->reset_device->read32) {
        const MusashiGpuDevice *gpu = cpu->callback_device->reset_device;
        *value = gpu->read32(gpu->userdata, address);
        return 1;
    }
    if (address == 0x1f801110u) {
        uint16_t count;
        /* The reference's word and halfword COUNT reads return the same
         * 16-bit counter value. Retail 800423C0 consumes it with LW. */
        if (!callback_read16(cpu, address, &count)) return 0;
        *value = count;
        return 1;
    }
    if (!cpu->input_device || !cpu->input_device->read32 ||
        (address != 0x1f801070u && address != 0x1f801074u) ||
        !cpu->input_device->read32(cpu->input_device->userdata, address, &accepted)) return 0;
    *value = accepted;
    return 1;
}

static int cpu_write32(MusashiBootMemory *memory, const FormatterCpu *cpu,
                        uint32_t address, uint32_t value) {
    uint8_t *p = cpu_ram_span(memory, cpu, address, 4);
    if (address & 3u) return 0;
    if (cpu->bios_image && cpu->bios_image->intersects &&
        cpu->bios_image->intersects(address, 4))
        return cpu->bios_image->write32 && cpu->bios_image->write32(
            cpu->bios_image->userdata, address, value);
    if (p) {
        p[0] = (uint8_t)value; p[1] = (uint8_t)(value >> 8);
        p[2] = (uint8_t)(value >> 16); p[3] = (uint8_t)(value >> 24);
        return 1;
    }
    if (address == 0x1f801820u || address == 0x1f801824u ||
        (address >= 0x1f801080u && address <= 0x1f801098u) ||
        address == 0x1f801810u || address == 0x1f801814u ||
        address == 0x1f8010a0u || address == 0x1f8010a4u || address == 0x1f8010a8u ||
        address == 0x1f8010e0u || address == 0x1f8010e4u || address == 0x1f8010e8u)
        return cpu->gpu_io_device && cpu->gpu_io_device->write32 &&
            cpu->gpu_io_device->write32(cpu->gpu_io_device->userdata,address,value);
    if (address == 0x1f801014u || address == 0x1f801018u || address == 0x1f8010b0u ||
        address == 0x1f8010b4u || address == 0x1f8010b8u ||
        address == 0x1f8010c0u || address == 0x1f8010c4u || address == 0x1f8010c8u ||
        ((address == 0x1f801020u || address == 0x1f8010f0u) &&
         cpu->cd_register_device && cpu->cd_register_device->write32))
        return cpu->cd_register_device && cpu->cd_register_device->write32 &&
            cpu->cd_register_device->write32(cpu->cd_register_device->userdata, address, value);
    if (cpu->input_device && cpu->input_device->write32 &&
        (address == 0x1f801070u || address == 0x1f801074u))
        return cpu->input_device->write32(cpu->input_device->userdata, address, value);
    return callback_write32(cpu, address, value);
}

static int formatter_return(FormatterCpu *cpu) {
    if (cpu->gte_load_pending) return 0;
    cpu->delay_slot = 0;
    cpu->branch_pc = 0;
    cpu->pc = cpu->r[31];
    cpu->npc = cpu->r[31] + 4u;
    return 1;
}

/* Compiled bulk intrinsics use BootMemory directly after this ownership
 * check. They cannot silently modify/read the separately published BIOS image. */
static int intrinsic_span(const FormatterCpu *cpu, uint32_t address, size_t size) {
    return !size || !cpu->bios_image || (cpu->bios_image->intersects &&
        !cpu->bios_image->intersects(address, size));
}

static int intrinsic_string(MusashiBootMemory *memory, const FormatterCpu *cpu,
                            uint32_t address) {
    uint32_t length;
    uint8_t value;
    for (length = 0; length < MUSASHI_RAM_SIZE; ++length) {
        if (address > UINT32_MAX - length ||
            !cpu_read8(memory, cpu, address + length, &value)) return 0;
        if (!value) return 1;
    }
    return 0;
}

static int formatter_call(MusashiBootMemory *memory, FormatterCpu *cpu,
                           MusashiConsoleSink sink, void *userdata) {
    uint32_t address = cpu->pc;
    if (cpu->gte_load_pending) return 0;
    if (address == FORMATTER_CONSOLE_CHAR) {
        uint8_t *classes = musashi_boot_ram_span(memory, 0x800728a9u, 0x100u);
        uint32_t column_word;
        int32_t column;
        if (!classes || !sink || !musashi_boot_read32(memory, 0x80078978u, &column_word))
            return 0;
        memcpy(&column, &column_word, sizeof(column));
        func_8005C388_native((int32_t)cpu->r[4], classes, &column, userdata);
        memcpy(&column_word, &column, sizeof(column_word));
        if (!musashi_boot_write32(memory, 0x80078978u, column_word))
            return 0;
        return formatter_return(cpu);
    }
    if (address == FORMATTER_SEARCH) {
        uint32_t source = cpu->r[4];
        int32_t count = (int32_t)cpu->r[6];
        uint8_t needle = (uint8_t)cpu->r[5];
        uint8_t value;
        if (count > 0 && !intrinsic_span(cpu, source, (size_t)count)) return 0;
        cpu->r[2] = 0;
        if (count > 0) {
            if (!musashi_boot_ram_span(memory, source, (size_t)count))
                return 0;
            while (count-- > 0) {
                if (!cpu_read8(memory, cpu, source, &value))
                    return 0;
                if (value == needle) {
                    cpu->r[2] = source;
                    break;
                }
                source++;
            }
        }
        return formatter_return(cpu);
    }
    if (address == FORMATTER_STRING_LENGTH) {
        uint32_t source = cpu->r[4];
        uint8_t value;
        uint32_t length = 0;
        while (length < MUSASHI_RAM_SIZE) {
            if (source > UINT32_MAX - length ||
                !cpu_read8(memory, cpu, source + length, &value))
                return 0;
            if (value == 0)
                break;
            length++;
        }
        if (length == MUSASHI_RAM_SIZE)
            return 0;
        cpu->r[2] = length;
        return formatter_return(cpu);
    }
    if (address == RESETGRAPH_FILL) {
        if (!intrinsic_span(cpu, cpu->r[4], cpu->r[6])) return 0;
        if (!musashi_boot_call_8005c29c(memory, cpu->r[4], (int32_t)cpu->r[5], cpu->r[6]))
            return 0;
        return formatter_return(cpu);
    }
    if (address == CALLBACK_CLEAR) {
        if (cpu->r[5] > MUSASHI_RAM_SIZE / 4u ||
            !intrinsic_span(cpu, cpu->r[4], (size_t)cpu->r[5] * 4u)) return 0;
        if (!musashi_boot_call_80042c64(memory, cpu->r[4], cpu->r[5]))
            return 0;
        return formatter_return(cpu);
    }
    if (address == CALLBACK_INSTALLER_CLEAR) {
        if (cpu->r[5] > MUSASHI_RAM_SIZE / 4u ||
            !intrinsic_span(cpu, cpu->r[4], (size_t)cpu->r[5] * 4u)) return 0;
        if (!musashi_boot_call_80042c64(memory, cpu->r[4], cpu->r[5]))
            return 0;
        return formatter_return(cpu);
    }
    if (address == CALLBACK_CHANNEL_CLEAR) {
        if (cpu->r[5] > MUSASHI_RAM_SIZE / 4u ||
            !intrinsic_span(cpu, cpu->r[4], (size_t)cpu->r[5] * 4u)) return 0;
        if (!musashi_boot_call_80042c64(memory, cpu->r[4], cpu->r[5]))
            return 0;
        return formatter_return(cpu);
    }
    if (address == CALLBACK_REGISTER_WRAPPER) {
        uint32_t previous;
        if (!cpu->callback_device ||
            !musashi_boot_call_800425b0(memory, cpu->callback_device->registration_device,
                                       (int32_t)cpu->r[4], cpu->r[5], &previous))
            return 0;
        cpu->r[2] = previous;
        return formatter_return(cpu);
    }
    if (address == STARTUP_ENVIRONMENT_CLEAR) {
        if (!intrinsic_span(cpu, cpu->r[4], cpu->r[5])) return 0;
        if (!musashi_boot_call_80016714(memory, cpu->r[4], cpu->r[5]))
            return 0;
        return formatter_return(cpu);
    }
    if (address == STARTUP_CLEAR_29044) {
        if (!musashi_boot_call_80029044(memory)) return 0;
        return formatter_return(cpu);
    }
    if (address == STARTUP_CLEAR_2906C) {
        if (!musashi_boot_call_8002906c(memory)) return 0;
        return formatter_return(cpu);
    }
    if (address == STARTUP_CLEAR_29094) {
        if (!musashi_boot_call_80016714(memory, 0x800ba2b8u, 0x60u)) return 0;
        return formatter_return(cpu);
    }
    if (address == STARTUP_CLEAR_29218) {
        if (!musashi_boot_call_80016714(memory, 0x800ae6a8u, 0x3cu)) return 0;
        return formatter_return(cpu);
    }
    if (address == STARTUP_RECORD_CLEAR) {
        if (!musashi_boot_call_8001903c(memory)) return 0;
        return formatter_return(cpu);
    }
    return 0;
}

static uint32_t formatter_sra(uint32_t value, uint32_t shift) {
    uint32_t result = value >> shift;
    if (shift && (value & 0x80000000u))
        result |= UINT32_MAX << (32u - shift);
    return result;
}

/* First-two-call SPU closure retains live pointer cells and refuses unknown
 * indirect dispatch before it can enter another admitted source stream. */
static int spu_source_guard(MusashiBootMemory *memory, const FormatterCpu *cpu) {
    uint32_t value;
    switch (cpu->pc) {
    case 0x8002c8f4u:
        return cpu->cd_spu_device != NULL;
    case 0x8003a5b8u:
    case 0x8003a84cu:
    case 0x8003af04u:
    case 0x8003c598u:
    case 0x8003b45cu:
    case 0x8003b954u:
    case 0x8003b280u:
        return musashi_boot_read32(memory, 0x8006b54cu, &value) && value == 0x1f801c00u;
    case 0x8003be98u:
        return cpu->r[6] == 0xccu && cpu->r[7] == 0xcdu &&
            musashi_boot_read32(memory, 0x8006b54cu, &value) && value == 0x1f801c00u;
    case 0x8003fe3cu:
    case 0x8003fa64u:
        return musashi_boot_read32(memory, 0x8006b8fcu, &value) && value == 0x1f801c00u;
    case 0x8003a5d4u:
        return cpu->r[4] == 0x1f8010f0u;
    case 0x800425f8u:
        return cpu->r[2] == 0x80042f8cu;
    case 0x80042f8cu:
        /* Channel 4 is the SPU DMA complete callback. Channel 2 is the GPU
         * queue/DrawOTag callback registered from 8005B8F8 / cleared from
         * 8005BA90. MAIN4 registers its loaded MDEC-output handler on channel1. */
        return (cpu->r[4] == 4u && cpu->r[5] == 0x8003aa18u) ||
               (cpu->r[4] == 2u && (cpu->r[5] == 0x8005ba90u || cpu->r[5] == 0)) ||
               (g_overlay_0004_words && cpu->r[4] == 1u &&
                (cpu->r[5] == 0x800d24d0u || cpu->r[5] == 0)) ||
               (g_overlay_0004_words && cpu->r[4] == 3u &&
                (cpu->r[5] == 0x800469ccu || cpu->r[5] == 0));
    case 0x80042fc8u:
        /* The source has already published CBD4 before this device read. */
        return cpu->r[5] == 0x1f8010f4u;
    case 0x8003c5ecu:
    case 0x8003c6b4u: {
        static const uint32_t targets[2][8] = {
            {0x8003c62cu,0x8003c5f4u,0x8003c5fcu,0x8003c604u,
             0x8003c60cu,0x8003c614u,0x8003c61cu,0x8003c624u},
            {0x8003c6f4u,0x8003c6bcu,0x8003c6c4u,0x8003c6ccu,
             0x8003c6d4u,0x8003c6dcu,0x8003c6e4u,0x8003c6ecu}
        };
        /* Index and loaded target remain the source's live values. */
        return cpu->r[3] < 8u &&
            cpu->r[2] == targets[cpu->pc == 0x8003c6b4u][cpu->r[3]];
    }
    case 0x8003fc2cu:
    case 0x8003fc58u:
        return 0; /* Active voice callbacks have no bound native executor. */
    case 0x800442bcu:
    case 0x800442f0u:
        /* The dedicated IRQ executor checks exact ancestry, live slot,
         * arguments and return frame after executing link/delay. Mainline
         * still has no inline callback capability. */
        return cpu->cd_irq_frame != NULL;
    case 0x80044544u:
        return g_overlay_0004_words && cpu->cd_irq_frame != NULL;
    case 0x80044578u:
    case 0x800449b4u:
    case 0x800449e8u:
        /* Inline CD completion callbacks need their own source/return
         * binding. TOC temporarily clears the callback; a mapped address
         * alone does not authorize an arbitrary live callback target. */
        return 0;
    default:
        return 1;
    }
}

enum {
    MERGE_NONE = 0,
    MERGE_LWL = 1,
    MERGE_LWR = 2,
    MERGE_SWL = 3,
    MERGE_SWR = 4,
};

static int merge_kind_for(uint32_t pc, uint32_t instruction) {
    switch (pc) {
    case 0x8012a0a4u: return instruction == 0x88820023u ? MERGE_LWL : MERGE_NONE;
    case 0x8012a0a8u: return instruction == 0x98820020u ? MERGE_LWR : MERGE_NONE;
    case 0x8012a0acu: return instruction == 0x88830027u ? MERGE_LWL : MERGE_NONE;
    case 0x8012a0b0u: return instruction == 0x98830024u ? MERGE_LWR : MERGE_NONE;
    case 0x8012a0b4u: return instruction == 0xa882001bu ? MERGE_SWL : MERGE_NONE;
    case 0x8012a0b8u: return instruction == 0xb8820018u ? MERGE_SWR : MERGE_NONE;
    case 0x8012a0bcu: return instruction == 0xa883001fu ? MERGE_SWL : MERGE_NONE;
    case 0x8012a0c0u: return instruction == 0xb883001cu ? MERGE_SWR : MERGE_NONE;
    case 0x800d2514u: return instruction == 0x88a20003u ? MERGE_LWL : MERGE_NONE;
    case 0x800d2518u: return instruction == 0x98a20000u ? MERGE_LWR : MERGE_NONE;
    case 0x800d251cu: return instruction == 0x88a30007u ? MERGE_LWL : MERGE_NONE;
    case 0x800d2520u: return instruction == 0x98a30004u ? MERGE_LWR : MERGE_NONE;
    case 0x800d2524u: return instruction == 0xaba20013u ? MERGE_SWL : MERGE_NONE;
    case 0x800d2528u: return instruction == 0xbba20010u ? MERGE_SWR : MERGE_NONE;
    case 0x800d252cu: return instruction == 0xaba30017u ? MERGE_SWL : MERGE_NONE;
    case 0x800d2530u: return instruction == 0xbba30014u ? MERGE_SWR : MERGE_NONE;
    case 0x800469fcu: return instruction == 0x8862001fu ? MERGE_LWL : MERGE_NONE;
    case 0x80046a00u: return instruction == 0x9862001cu ? MERGE_LWR : MERGE_NONE;
    case 0x80046a08u: return instruction == 0xa8c20003u ? MERGE_SWL : MERGE_NONE;
    case 0x80046a0cu: return instruction == 0xb8c20000u ? MERGE_SWR : MERGE_NONE;
    case 0x80046fd0u: return instruction == 0x8ba4002bu ? MERGE_LWL : MERGE_NONE;
    case 0x80046fd4u: return instruction == 0x9ba40028u ? MERGE_LWR : MERGE_NONE;
    case 0x80046fdcu: return instruction == 0xa844001fu ? MERGE_SWL : MERGE_NONE;
    case 0x80046fe0u: return instruction == 0xb844001cu ? MERGE_SWR : MERGE_NONE;
    case 0x8013d5fcu: return instruction == 0x882355a3u ? MERGE_LWL : MERGE_NONE;
    case 0x8013d608u: return instruction == 0x982355a0u ? MERGE_LWR : MERGE_NONE;
    case 0x8013d614u: return instruction == 0x882455a7u ? MERGE_LWL : MERGE_NONE;
    case 0x8013d620u: return instruction == 0x982455a4u ? MERGE_LWR : MERGE_NONE;
    case 0x8013d630u: return instruction == 0xa8c30003u ? MERGE_SWL : MERGE_NONE;
    case 0x8013d634u: return instruction == 0xb8c30000u ? MERGE_SWR : MERGE_NONE;
    case 0x8013d638u: return instruction == 0xa8c40007u ? MERGE_SWL : MERGE_NONE;
    case 0x8013d63cu: return instruction == 0xb8c40004u ? MERGE_SWR : MERGE_NONE;
    case 0x8013d654u: return instruction == 0x88a20003u ? MERGE_LWL : MERGE_NONE;
    case 0x8013d658u: return instruction == 0x98a20000u ? MERGE_LWR : MERGE_NONE;
    case 0x8013d65cu: return instruction == 0x88a30007u ? MERGE_LWL : MERGE_NONE;
    case 0x8013d660u: return instruction == 0x98a30004u ? MERGE_LWR : MERGE_NONE;
    case 0x8013d664u: return instruction == 0xa8820003u ? MERGE_SWL : MERGE_NONE;
    case 0x8013d668u: return instruction == 0xb8820000u ? MERGE_SWR : MERGE_NONE;
    case 0x8013d66cu: return instruction == 0xa8830007u ? MERGE_SWL : MERGE_NONE;
    case 0x8013d670u: return instruction == 0xb8830004u ? MERGE_SWR : MERGE_NONE;
    case 0x80045720u: return instruction == 0x88a20003u ? MERGE_LWL : MERGE_NONE;
    case 0x80045724u: return instruction == 0x98a20000u ? MERGE_LWR : MERGE_NONE;
    case 0x8004572cu: return instruction == 0xaba2001bu ? MERGE_SWL : MERGE_NONE;
    case 0x80045730u: return instruction == 0xbba20018u ? MERGE_SWR : MERGE_NONE;
    case 0x800457e4u: return instruction == 0x8a230005u ? MERGE_LWL : MERGE_NONE;
    case 0x800457e8u: return instruction == 0x9a230002u ? MERGE_LWR : MERGE_NONE;
    case 0x800457f0u: return instruction == 0xa8430003u ? MERGE_SWL : MERGE_NONE;
    case 0x800457f4u: return instruction == 0xb8430000u ? MERGE_SWR : MERGE_NONE;
    case 0x80045ae4u: return instruction == 0x8a020005u ? MERGE_LWL : MERGE_NONE;
    case 0x80045ae8u: return instruction == 0x9a020002u ? MERGE_LWR : MERGE_NONE;
    case 0x80045af0u: return instruction == 0xaba2001bu ? MERGE_SWL : MERGE_NONE;
    case 0x80045af4u: return instruction == 0xbba20018u ? MERGE_SWR : MERGE_NONE;
    case 0x80045b0cu: return instruction == 0x8a03000du ? MERGE_LWL : MERGE_NONE;
    case 0x80045b10u: return instruction == 0x9a03000au ? MERGE_LWR : MERGE_NONE;
    case 0x80045b18u: return instruction == 0xa8430003u ? MERGE_SWL : MERGE_NONE;
    case 0x80045b1cu: return instruction == 0xb8430000u ? MERGE_SWR : MERGE_NONE;
    /* SC02 8017C2B0 unaligned 16-byte copy (two paths). */
    case 0x8017c4ccu: return instruction == 0x88c20003u ? MERGE_LWL : MERGE_NONE;
    case 0x8017c4d0u: return instruction == 0x98c20000u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c4d4u: return instruction == 0x88c30007u ? MERGE_LWL : MERGE_NONE;
    case 0x8017c4d8u: return instruction == 0x98c30004u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c4dcu: return instruction == 0x88c4000bu ? MERGE_LWL : MERGE_NONE;
    case 0x8017c4e0u: return instruction == 0x98c40008u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c4e4u: return instruction == 0x88c5000fu ? MERGE_LWL : MERGE_NONE;
    case 0x8017c4e8u: return instruction == 0x98c5000cu ? MERGE_LWR : MERGE_NONE;
    case 0x8017c4ecu: return instruction == 0xa8e20003u ? MERGE_SWL : MERGE_NONE;
    case 0x8017c4f0u: return instruction == 0xb8e20000u ? MERGE_SWR : MERGE_NONE;
    case 0x8017c4f4u: return instruction == 0xa8e30007u ? MERGE_SWL : MERGE_NONE;
    case 0x8017c4f8u: return instruction == 0xb8e30004u ? MERGE_SWR : MERGE_NONE;
    case 0x8017c4fcu: return instruction == 0xa8e4000bu ? MERGE_SWL : MERGE_NONE;
    case 0x8017c500u: return instruction == 0xb8e40008u ? MERGE_SWR : MERGE_NONE;
    case 0x8017c504u: return instruction == 0xa8e5000fu ? MERGE_SWL : MERGE_NONE;
    case 0x8017c508u: return instruction == 0xb8e5000cu ? MERGE_SWR : MERGE_NONE;
    case 0x8017c54cu: return instruction == 0x88c20003u ? MERGE_LWL : MERGE_NONE;
    case 0x8017c550u: return instruction == 0x98c20000u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c554u: return instruction == 0x88c30007u ? MERGE_LWL : MERGE_NONE;
    case 0x8017c558u: return instruction == 0x98c30004u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c55cu: return instruction == 0x88c4000bu ? MERGE_LWL : MERGE_NONE;
    case 0x8017c560u: return instruction == 0x98c40008u ? MERGE_LWR : MERGE_NONE;
    case 0x8017c564u: return instruction == 0xa8e20003u ? MERGE_SWL : MERGE_NONE;
    case 0x8017c568u: return instruction == 0xb8e20000u ? MERGE_SWR : MERGE_NONE;
    case 0x8017c56cu: return instruction == 0xa8e30007u ? MERGE_SWL : MERGE_NONE;
    case 0x8017c570u: return instruction == 0xb8e30004u ? MERGE_SWR : MERGE_NONE;
    case 0x8017c574u: return instruction == 0xa8e4000bu ? MERGE_SWL : MERGE_NONE;
    case 0x8017c578u: return instruction == 0xb8e40008u ? MERGE_SWR : MERGE_NONE;
    default: return MERGE_NONE;
    }
}

static int merge_pending_matches(const FormatterCpu *cpu, uint32_t instruction) {
    if (!cpu->merge_pending) return 1;
    if (cpu->pc != cpu->merge_next_pc) return 0;
    if (cpu->pc >= 0x8013d5fcu && cpu->pc < 0x8013d680u) {
        /* Retail nine-byte copies: the first pairs retire across LUI;
         * the second copy interleaves adjacent pairs and their stores. */
        static const struct { uint32_t pc, word; uint8_t reg, kind; } sites[] = {
            {0x8013d600u,0x3c018018u,3,MERGE_LWL},
            {0x8013d60cu,0x3c018018u,3,MERGE_LWR},
            {0x8013d618u,0x3c018018u,4,MERGE_LWL},
            {0x8013d624u,0x3c018018u,4,MERGE_LWR},
            {0x8013d658u,0x98a20000u,2,MERGE_LWL},
            {0x8013d65cu,0x88a30007u,2,MERGE_LWR},
            {0x8013d660u,0x98a30004u,3,MERGE_LWL},
            {0x8013d664u,0xa8820003u,3,MERGE_LWR}
        };
        unsigned i;
        if (cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc) return 0;
        for (i=0;i<sizeof(sites)/sizeof(sites[0]);++i)
            if (sites[i].pc == cpu->pc && sites[i].word == instruction &&
                sites[i].reg == cpu->merge_reg && sites[i].kind == cpu->merge_kind) return 1;
        return 0;
    }
    if (cpu->merge_kind == MERGE_LWL)
        return merge_kind_for(cpu->pc, instruction) == MERGE_LWR;
    if (cpu->merge_kind == MERGE_LWR &&
        ((cpu->pc == 0x8012a0acu && instruction == 0x88830027u && cpu->merge_reg == 2u) ||
         (cpu->pc == 0x8012a0b4u && instruction == 0xa882001bu && cpu->merge_reg == 3u)))
        return 1;
    if (cpu->merge_kind == MERGE_LWR &&
        ((cpu->pc == 0x800d251cu && instruction == 0x88a30007u && cpu->merge_reg == 2u) ||
         (cpu->pc == 0x800d2524u && instruction == 0xaba20013u && cpu->merge_reg == 3u)))
        return 1;
    if (cpu->merge_kind == MERGE_LWR &&
        ((cpu->pc == 0x8017c4d4u && instruction == 0x88c30007u && cpu->merge_reg == 2u) ||
         (cpu->pc == 0x8017c4dcu && instruction == 0x88c4000bu && cpu->merge_reg == 3u) ||
         (cpu->pc == 0x8017c4e4u && instruction == 0x88c5000fu && cpu->merge_reg == 4u) ||
         (cpu->pc == 0x8017c4ecu && instruction == 0xa8e20003u && cpu->merge_reg == 5u) ||
         (cpu->pc == 0x8017c554u && instruction == 0x88c30007u && cpu->merge_reg == 2u) ||
         (cpu->pc == 0x8017c55cu && instruction == 0x88c4000bu && cpu->merge_reg == 3u) ||
         (cpu->pc == 0x8017c564u && instruction == 0xa8e20003u && cpu->merge_reg == 4u)))
        return 1;
    if (cpu->merge_kind == MERGE_LWR)
        return (cpu->pc == 0x80045728u || cpu->pc == 0x800457ecu ||
                cpu->pc == 0x80045aecu || cpu->pc == 0x80045b14u ||
                cpu->pc == 0x80046fd8u || cpu->pc == 0x80046a04u) && instruction == 0;
    return 0;
}

static int merge_memory_available(MusashiBootMemory *memory,
                                  const FormatterCpu *cpu, int kind,
                                  uint32_t address) {
    (void)kind;
    return musashi_boot_ram_span(memory, address & ~3u, 4u) != NULL &&
           cpu_ram_span(memory, cpu, address & ~3u, 4u) != NULL;
}

static uint32_t merge_lwl_value(uint32_t memory, uint32_t prior, unsigned shift) {
    static const uint32_t mask[4] = {0x00ffffffu, 0x0000ffffu,
                                     0x000000ffu, 0x00000000u};
    static const unsigned amount[4] = {24u, 16u, 8u, 0u};
    return (memory << amount[shift]) | (prior & mask[shift]);
}

static uint32_t merge_lwr_value(uint32_t memory, uint32_t prior, unsigned shift) {
    static const uint32_t mask[4] = {0x00000000u, 0xff000000u,
                                     0xffff0000u, 0xffffff00u};
    static const unsigned amount[4] = {0u, 8u, 16u, 24u};
    return (memory >> amount[shift]) | (prior & mask[shift]);
}

static uint32_t merge_swl_value(uint32_t memory, uint32_t value, unsigned shift) {
    static const uint32_t mask[4] = {0xffffff00u, 0xffff0000u,
                                     0xff000000u, 0x00000000u};
    static const unsigned amount[4] = {24u, 16u, 8u, 0u};
    return (value >> amount[shift]) | (memory & mask[shift]);
}

static uint32_t merge_swr_value(uint32_t memory, uint32_t value, unsigned shift) {
    static const uint32_t mask[4] = {0x00000000u, 0x000000ffu,
                                     0x0000ffffu, 0x00ffffffu};
    static const unsigned amount[4] = {0u, 8u, 16u, 24u};
    return (value << amount[shift]) | (memory & mask[shift]);
}

/* One immutable source-word lookup is shared by execution and exception
 * provenance. This never reads a replacement opcode from writable guest RAM. */
static int formatter_fetch(const FormatterCpu *cpu, uint32_t *out) {
    uint32_t instruction;
    if (!cpu || !out || (cpu->pc & 3u)) return 0;
    if (cpu->pc >= 0x80010000u && cpu->pc < 0x800100a0u)
        instruction = kCrt80010000Words[(cpu->pc - 0x80010000u) / 4u];
    else if (cpu->pc >= 0x800100a0u && cpu->pc < 0x80010110u)
        instruction = kConstructor800100A0Words[(cpu->pc - 0x800100a0u) / 4u];
    else if (cpu->pc >= 0x80010178u && cpu->pc < 0x8001020cu)
        instruction = kCaller80010178Words[(cpu->pc - 0x80010178u) / 4u];
    else if (cpu->pc >= 0x80010214u && cpu->pc < 0x80010938u)
        instruction = kMain80010214Words[(cpu->pc - 0x80010214u) / 4u];
    else if (cpu->pc >= 0x80014238u && cpu->pc < 0x800142c8u)
        instruction = kMain80014238Words[(cpu->pc - 0x80014238u) / 4u];
    else if (cpu->pc >= 0x8001c044u && cpu->pc < 0x8001c0c8u)
        instruction = kMain8001C044Words[(cpu->pc - 0x8001c044u) / 4u];
    else if (cpu->pc >= 0x80015310u && cpu->pc < 0x8001534cu)
        instruction = kMain80015310Words[(cpu->pc - 0x80015310u) / 4u];
    else if (cpu->pc >= 0x80028a48u && cpu->pc < 0x80028c50u)
        instruction = kMain80028A48Words[(cpu->pc - 0x80028a48u) / 4u];
    else if (cpu->pc >= 0x80028c50u && cpu->pc < 0x80028d58u)
        instruction = kMain80028C50Words[(cpu->pc - 0x80028c50u) / 4u];
    else if (cpu->pc >= 0x80014928u && cpu->pc < 0x80014960u)
        instruction = kMain80014928Words[(cpu->pc - 0x80014928u) / 4u];
    else if (cpu->pc >= 0x8005ce18u && cpu->pc < 0x8005ce24u)
        instruction = kMain8005CE18Words[(cpu->pc - 0x8005ce18u) / 4u];
    else if (cpu->pc >= 0x800143acu && cpu->pc < 0x80014444u)
        instruction = kDraw800143ACWords[(cpu->pc - 0x800143acu) / 4u];
    else if (cpu->pc >= 0x80014390u && cpu->pc < 0x800143acu)
        instruction = kMain80014390Words[(cpu->pc - 0x80014390u) / 4u];
    else if (cpu->pc >= 0x800191a8u && cpu->pc < 0x800191bcu)
        instruction = kMain800191A8Words[(cpu->pc - 0x800191a8u) / 4u];
    else if (cpu->pc >= 0x80010a98u && cpu->pc < 0x80010ae0u)
        instruction = kMain80010A98Words[(cpu->pc - 0x80010a98u) / 4u];
    else if (cpu->pc >= 0x800595fcu && cpu->pc < 0x80059658u)
        instruction = kMain800595FCWords[(cpu->pc - 0x800595fcu) / 4u];
    else if (cpu->pc >= 0x80042610u && cpu->pc < 0x80042644u)
        instruction = kMain80042610Words[(cpu->pc - 0x80042610u) / 4u];
    else if (cpu->pc >= 0x800189a8u && cpu->pc < 0x80018a20u)
        instruction = kMain800189A8Words[(cpu->pc - 0x800189a8u) / 4u];
    else if (cpu->pc >= 0x80018a20u && cpu->pc < 0x80018c64u)
        instruction = kMain80018A20Words[(cpu->pc - 0x80018a20u) / 4u];
    else if (cpu->pc >= 0x8005d184u && cpu->pc < 0x8005d244u)
        instruction = kMain8005D184Words[(cpu->pc - 0x8005d184u) / 4u];
    else if (cpu->pc >= 0x8005f704u && cpu->pc < 0x8005f728u)
        instruction = kMain8005F704Words[(cpu->pc - 0x8005f704u) / 4u];
    else if (cpu->pc >= 0x8005d244u && cpu->pc < 0x8005d4b8u)
        instruction = kMain8005D244Words[(cpu->pc - 0x8005d244u) / 4u];
    else if (cpu->pc >= 0x80028d58u && cpu->pc < 0x80028d78u)
        instruction = kMain80028D58Words[(cpu->pc - 0x80028d58u) / 4u];
    else if (cpu->pc >= 0x80029178u && cpu->pc < 0x800291a0u)
        instruction = kMain80029178Words[(cpu->pc - 0x80029178u) / 4u];
    else if (cpu->pc >= 0x8005d538u && cpu->pc < 0x8005d6a0u)
        instruction = kMain8005D538Words[(cpu->pc - 0x8005d538u) / 4u];
    else if (cpu->pc >= 0x8005e188u && cpu->pc < 0x8005e1a4u)
        instruction = kMain8005E188Words[(cpu->pc - 0x8005e188u) / 4u];
    else if (cpu->pc >= 0x8005d4b8u && cpu->pc < 0x8005d538u)
        instruction = kMain8005D4B8Words[(cpu->pc - 0x8005d4b8u) / 4u];
    else if (cpu->pc >= 0x8005e79cu && cpu->pc < 0x8005e8e8u)
        instruction = kMain8005E79CWords[(cpu->pc - 0x8005e79cu) / 4u];
    else if (cpu->pc >= 0x80018c64u && cpu->pc < 0x80018ce8u)
        instruction = kMain80018C64Words[(cpu->pc - 0x80018c64u) / 4u];
    else if (cpu->pc >= 0x80018f88u && cpu->pc < 0x80018fc8u)
        instruction = kMain80018F88Words[(cpu->pc - 0x80018f88u) / 4u];
    else if (cpu->pc >= 0x80018ce8u && cpu->pc < 0x80018e78u)
        instruction = kMain80018CE8Words[(cpu->pc - 0x80018ce8u) / 4u];
    else if (cpu->pc >= 0x80018f20u && cpu->pc < 0x80018f88u)
        instruction = kMain80018F20Words[(cpu->pc - 0x80018f20u) / 4u];
    else if (cpu->pc >= 0x80018e9cu && cpu->pc < 0x80018f20u)
        instruction = kMain80018E9CWords[(cpu->pc - 0x80018e9cu) / 4u];
    else if (cpu->pc >= 0x800291b4u && cpu->pc < 0x800291c8u)
        instruction = kMain800291B4Words[(cpu->pc - 0x800291b4u) / 4u];
    else if (cpu->pc >= 0x80028d78u && cpu->pc < 0x80028d9cu)
        instruction = kMain80028D78Words[(cpu->pc - 0x80028d78u) / 4u];
    else if (cpu->pc >= 0x80015208u && cpu->pc < 0x800152f4u)
        instruction = kMain80015208Words[(cpu->pc - 0x80015208u) / 4u];
    else if (cpu->pc >= 0x80059bfcu && cpu->pc < 0x80059cf4u)
        instruction = kMain80059BFCWords[(cpu->pc - 0x80059bfcu) / 4u];
    else if (cpu->pc >= 0x80059cf4u && cpu->pc < 0x80059d68u)
        instruction = kMain80059CF4Words[(cpu->pc - 0x80059cf4u) / 4u];
    else if (cpu->pc >= 0x8003500cu && cpu->pc < 0x800351e8u)
        instruction = kMain8003500CWords[(cpu->pc - 0x8003500cu) / 4u];
    else if (cpu->pc >= 0x8002d034u && cpu->pc < 0x8002d1f0u)
        instruction = kMain8002D034Words[(cpu->pc - 0x8002d034u) / 4u];
    else if (cpu->pc >= 0x8002d240u && cpu->pc < 0x8002d29cu)
        instruction = kMain8002D240Words[(cpu->pc - 0x8002d240u) / 4u];
    else if (cpu->pc >= 0x8002d29cu && cpu->pc < 0x8002d320u)
        instruction = kMain8002D29CWords[(cpu->pc - 0x8002d29cu) / 4u];
    else if (cpu->pc >= 0x8002dc68u && cpu->pc < 0x8002df80u)
        instruction = kMain8002DC68Words[(cpu->pc - 0x8002dc68u) / 4u];
    else if (cpu->pc >= 0x8002df80u && cpu->pc < 0x8002e138u)
        instruction = kMain8002DF80Words[(cpu->pc - 0x8002df80u) / 4u];
    else if (cpu->pc >= 0x8002e138u && cpu->pc < 0x8002e5bcu)
        instruction = kMain8002E138Words[(cpu->pc - 0x8002e138u) / 4u];
    else if (cpu->pc >= 0x8002e5bcu && cpu->pc < 0x8002e5f8u)
        instruction = kMain8002E5BCWords[(cpu->pc - 0x8002e5bcu) / 4u];
    else if (cpu->pc >= 0x8002e5f8u && cpu->pc < 0x8002e638u)
        instruction = kMain8002E5F8Words[(cpu->pc - 0x8002e5f8u) / 4u];
    else if (cpu->pc >= 0x8002e638u && cpu->pc < 0x8002e700u)
        instruction = kMain8002E638Words[(cpu->pc - 0x8002e638u) / 4u];
    else if (cpu->pc >= 0x8002e700u && cpu->pc < 0x8002e79cu)
        instruction = kMain8002E700Words[(cpu->pc - 0x8002e700u) / 4u];
    else if (cpu->pc >= 0x8002e79cu && cpu->pc < 0x8002e818u)
        instruction = kMain8002E79CWords[(cpu->pc - 0x8002e79cu) / 4u];
    else if (cpu->pc >= 0x8002e818u && cpu->pc < 0x8002e8dcu)
        instruction = kMain8002E818Words[(cpu->pc - 0x8002e818u) / 4u];
    else if (cpu->pc >= 0x8002e8dcu && cpu->pc < 0x8002e94cu)
        instruction = kMain8002E8DCWords[(cpu->pc - 0x8002e8dcu) / 4u];
    else if (cpu->pc >= 0x8002e94cu && cpu->pc < 0x8002ea10u)
        instruction = kMain8002E94CWords[(cpu->pc - 0x8002e94cu) / 4u];
    else if (cpu->pc >= 0x8002ea10u && cpu->pc < 0x8002eab0u)
        instruction = kMain8002EA10Words[(cpu->pc - 0x8002ea10u) / 4u];
    else if (cpu->pc >= 0x8002eab0u && cpu->pc < 0x8002eb10u)
        instruction = kMain8002EAB0Words[(cpu->pc - 0x8002eab0u) / 4u];
    else if (cpu->pc >= 0x8002eb10u && cpu->pc < 0x8002ebacu)
        instruction = kMain8002EB10Words[(cpu->pc - 0x8002eb10u) / 4u];
    else if (cpu->pc >= 0x8002ebacu && cpu->pc < 0x8002ec10u)
        instruction = kMain8002EBACWords[(cpu->pc - 0x8002ebacu) / 4u];
    else if (cpu->pc >= 0x8002ede4u && cpu->pc < 0x8002ee64u)
        instruction = kMain8002EDE4Words[(cpu->pc - 0x8002ede4u) / 4u];
    else if (cpu->pc >= 0x8002ee90u && cpu->pc < 0x8002eeb8u)
        instruction = kMain8002EE90Words[(cpu->pc - 0x8002ee90u) / 4u];
    else if (cpu->pc >= 0x8002eeb8u && cpu->pc < 0x8002eed8u)
        instruction = kMain8002EEB8Words[(cpu->pc - 0x8002eeb8u) / 4u];
    else if (cpu->pc >= 0x8002eed8u && cpu->pc < 0x8002efd0u)
        instruction = kMain8002EED8Words[(cpu->pc - 0x8002eed8u) / 4u];
    else if (cpu->pc >= 0x8002efd0u && cpu->pc < 0x8002eff8u)
        instruction = kMain8002EFD0Words[(cpu->pc - 0x8002efd0u) / 4u];
    else if (cpu->pc >= 0x8002f0d0u && cpu->pc < 0x8002f0f4u)
        instruction = kMain8002F0D0Words[(cpu->pc - 0x8002f0d0u) / 4u];
    else if (cpu->pc >= 0x8002f248u && cpu->pc < 0x8002f4e4u)
        instruction = kMain8002F248Words[(cpu->pc - 0x8002f248u) / 4u];
    else if (cpu->pc >= 0x8002f4e4u && cpu->pc < 0x8002f5c8u)
        instruction = kMain8002F4E4Words[(cpu->pc - 0x8002f4e4u) / 4u];
    else if (cpu->pc >= 0x8002f714u && cpu->pc < 0x8002f80cu)
        instruction = kMain8002F714Words[(cpu->pc - 0x8002f714u) / 4u];
    else if (cpu->pc >= 0x80031b7cu && cpu->pc < 0x80031be0u)
        instruction = kMain80031B7CWords[(cpu->pc - 0x80031b7cu) / 4u];
    else if (cpu->pc >= 0x80031cc8u && cpu->pc < 0x80031d70u)
        instruction = kMain80031CC8Words[(cpu->pc - 0x80031cc8u) / 4u];
    else if (cpu->pc >= 0x80031decu && cpu->pc < 0x80031e94u)
        instruction = kMain80031DECWords[(cpu->pc - 0x80031decu) / 4u];
    else if (cpu->pc >= 0x80031e94u && cpu->pc < 0x80031f14u)
        instruction = kMain80031E94Words[(cpu->pc - 0x80031e94u) / 4u];
    else if (cpu->pc >= 0x80031f14u && cpu->pc < 0x80031fc8u)
        instruction = kMain80031F14Words[(cpu->pc - 0x80031f14u) / 4u];
    else if (cpu->pc >= 0x80031fc8u && cpu->pc < 0x80032048u)
        instruction = kMain80031FC8Words[(cpu->pc - 0x80031fc8u) / 4u];
    else if (cpu->pc >= 0x80032048u && cpu->pc < 0x800322a8u)
        instruction = kMain80032048Words[(cpu->pc - 0x80032048u) / 4u];
    else if (cpu->pc >= 0x800322a8u && cpu->pc < 0x800324a4u)
        instruction = kMain800322A8Words[(cpu->pc - 0x800322a8u) / 4u];
    else if (cpu->pc >= 0x800324a4u && cpu->pc < 0x80032774u)
        instruction = kMain800324A4Words[(cpu->pc - 0x800324a4u) / 4u];
    else if (cpu->pc >= 0x80032774u && cpu->pc < 0x80032a74u)
        instruction = kMain80032774Words[(cpu->pc - 0x80032774u) / 4u];
    else if (cpu->pc >= 0x80032a74u && cpu->pc < 0x8003310cu)
        instruction = kMain80032A74Words[(cpu->pc - 0x80032a74u) / 4u];
    else if (cpu->pc >= 0x8003310cu && cpu->pc < 0x800331d4u)
        instruction = kMain8003310CWords[(cpu->pc - 0x8003310cu) / 4u];
    else if (cpu->pc >= 0x800331d4u && cpu->pc < 0x8003324cu)
        instruction = kMain800331D4Words[(cpu->pc - 0x800331d4u) / 4u];
    else if (cpu->pc >= 0x8003324cu && cpu->pc < 0x80033324u)
        instruction = kMain8003324CWords[(cpu->pc - 0x8003324cu) / 4u];
    else if (cpu->pc >= 0x80033398u && cpu->pc < 0x8003350cu)
        instruction = kMain80033398Words[(cpu->pc - 0x80033398u) / 4u];
    else if (cpu->pc >= 0x8003350cu && cpu->pc < 0x800335b8u)
        instruction = kMain8003350CWords[(cpu->pc - 0x8003350cu) / 4u];
    else if (cpu->pc >= 0x800335b8u && cpu->pc < 0x800336a8u)
        instruction = kMain800335B8Words[(cpu->pc - 0x800335b8u) / 4u];
    else if (cpu->pc >= 0x80034314u && cpu->pc < 0x80034650u)
        instruction = kMain80034314Words[(cpu->pc - 0x80034314u) / 4u];
    else if (cpu->pc >= 0x800346d0u && cpu->pc < 0x800347c8u)
        instruction = kMain800346D0Words[(cpu->pc - 0x800346d0u) / 4u];
    else if (cpu->pc >= 0x80034844u && cpu->pc < 0x800348a8u)
        instruction = kMain80034844Words[(cpu->pc - 0x80034844u) / 4u];
    else if (cpu->pc >= 0x800348a8u && cpu->pc < 0x8003491cu)
        instruction = kMain800348A8Words[(cpu->pc - 0x800348a8u) / 4u];
    else if (cpu->pc >= 0x8003491cu && cpu->pc < 0x80034a54u)
        instruction = kMain8003491CWords[(cpu->pc - 0x8003491cu) / 4u];
    else if (cpu->pc >= 0x80034a54u && cpu->pc < 0x80034a9cu)
        instruction = kMain80034A54Words[(cpu->pc - 0x80034a54u) / 4u];
    else if (cpu->pc >= 0x80034a9cu && cpu->pc < 0x80034ae0u)
        instruction = kMain80034A9CWords[(cpu->pc - 0x80034a9cu) / 4u];
    else if (cpu->pc >= 0x80034ae0u && cpu->pc < 0x80034b0cu)
        instruction = kMain80034AE0Words[(cpu->pc - 0x80034ae0u) / 4u];
    else if (cpu->pc >= 0x80034b0cu && cpu->pc < 0x80034b3cu)
        instruction = kMain80034B0CWords[(cpu->pc - 0x80034b0cu) / 4u];
    else if (cpu->pc >= 0x80034cf0u && cpu->pc < 0x80034dfcu)
        instruction = kMain80034CF0Words[(cpu->pc - 0x80034cf0u) / 4u];
    else if (cpu->pc >= 0x80034dfcu && cpu->pc < 0x8003500cu)
        instruction = kMain80034DFCWords[(cpu->pc - 0x80034dfcu) / 4u];
    else if (cpu->pc >= 0x80036d58u && cpu->pc < 0x80036eb4u)
        instruction = kMain80036D58Words[(cpu->pc - 0x80036d58u) / 4u];
    else if (cpu->pc >= 0x80036eb4u && cpu->pc < 0x80036ee8u)
        instruction = kMain80036EB4Words[(cpu->pc - 0x80036eb4u) / 4u];
    else if (cpu->pc >= 0x80036ee8u && cpu->pc < 0x80036f18u)
        instruction = kMain80036EE8Words[(cpu->pc - 0x80036ee8u) / 4u];
    else if (cpu->pc >= 0x80036f18u && cpu->pc < 0x80036f98u)
        instruction = kMain80036F18Words[(cpu->pc - 0x80036f18u) / 4u];
    else if (cpu->pc >= 0x800381e4u && cpu->pc < 0x80038210u)
        instruction = kMain800381E4Words[(cpu->pc - 0x800381e4u) / 4u];
    else if (cpu->pc >= 0x800383a4u && cpu->pc < 0x800384a8u)
        instruction = kMain800383A4Words[(cpu->pc - 0x800383a4u) / 4u];
    else if (cpu->pc >= 0x800384a8u && cpu->pc < 0x800385c0u)
        instruction = kMain800384A8Words[(cpu->pc - 0x800384a8u) / 4u];
    else if (cpu->pc >= 0x800385c0u && cpu->pc < 0x80038638u)
        instruction = kMain800385C0Words[(cpu->pc - 0x800385c0u) / 4u];
    else if (cpu->pc >= 0x80038668u && cpu->pc < 0x80038698u)
        instruction = kMain80038668Words[(cpu->pc - 0x80038668u) / 4u];
    else if (cpu->pc >= 0x80038698u && cpu->pc < 0x800387c0u)
        instruction = kMain80038698Words[(cpu->pc - 0x80038698u) / 4u];
    else if (cpu->pc >= 0x800387c0u && cpu->pc < 0x80038838u)
        instruction = kMain800387C0Words[(cpu->pc - 0x800387c0u) / 4u];
    else if (cpu->pc >= 0x80038838u && cpu->pc < 0x800388e8u)
        instruction = kMain80038838Words[(cpu->pc - 0x80038838u) / 4u];
    else if (cpu->pc >= 0x80038908u && cpu->pc < 0x80038958u)
        instruction = kMain80038908Words[(cpu->pc - 0x80038908u) / 4u];
    else if (cpu->pc >= 0x8003916cu && cpu->pc < 0x800391d4u)
        instruction = kMain8003916CWords[(cpu->pc - 0x8003916cu) / 4u];
    else if (cpu->pc >= 0x8003ab84u && cpu->pc < 0x8003ae14u)
        instruction = kMain8003AB84Words[(cpu->pc - 0x8003ab84u) / 4u];
    else if (cpu->pc >= 0x8003af4cu && cpu->pc < 0x8003aff0u)
        instruction = kMain8003AF4CWords[(cpu->pc - 0x8003af4cu) / 4u];
    else if (cpu->pc >= 0x8003b08cu && cpu->pc < 0x8003b0b8u)
        instruction = kMain8003B08CWords[(cpu->pc - 0x8003b08cu) / 4u];
    else if (cpu->pc >= 0x8003b0b8u && cpu->pc < 0x8003b0e4u)
        instruction = kMain8003B0B8Words[(cpu->pc - 0x8003b0b8u) / 4u];
    else if (cpu->pc >= 0x8003c0a0u && cpu->pc < 0x8003c23cu)
        instruction = kMain8003C0A0Words[(cpu->pc - 0x8003c0a0u) / 4u];
    else if (cpu->pc >= 0x8003c92cu && cpu->pc < 0x8003cf68u)
        instruction = kMain8003C92CWords[(cpu->pc - 0x8003c92cu) / 4u];
    else if (cpu->pc >= 0x8003cff8u && cpu->pc < 0x8003d134u)
        instruction = kMain8003CFF8Words[(cpu->pc - 0x8003cff8u) / 4u];
    else if (cpu->pc >= 0x8003ede8u && cpu->pc < 0x8003eee4u)
        instruction = kMain8003EDE8Words[(cpu->pc - 0x8003ede8u) / 4u];
    else if (cpu->pc >= 0x80043974u && cpu->pc < 0x80043994u)
        instruction = kMain80043974Words[(cpu->pc - 0x80043974u) / 4u];
    else if (cpu->pc >= 0x80044a8cu && cpu->pc < 0x80044b14u)
        instruction = kMain80044A8CWords[(cpu->pc - 0x80044a8cu) / 4u];
    else if (cpu->pc >= 0x8005ce98u && cpu->pc < 0x8005cea4u)
        instruction = kMain8005CE98Words[(cpu->pc - 0x8005ce98u) / 4u];
    else if (cpu->pc >= 0x8001a0fcu && cpu->pc < 0x8001a114u)
        instruction = kMain8001A0FCWords[(cpu->pc - 0x8001a0fcu) / 4u];
    else if (cpu->pc >= 0x8001a114u && cpu->pc < 0x8001a338u)
        instruction = kMain8001A114Words[(cpu->pc - 0x8001a114u) / 4u];
    else if (cpu->pc >= 0x8001af34u && cpu->pc < 0x8001b0d4u)
        instruction = kMain8001AF34Words[(cpu->pc - 0x8001af34u) / 4u];
    else if (cpu->pc >= 0x8001b0d4u && cpu->pc < 0x8001b22cu)
        instruction = kMain8001B0D4Words[(cpu->pc - 0x8001b0d4u) / 4u];
    else if (cpu->pc >= 0x8001b394u && cpu->pc < 0x8001b3c4u)
        instruction = kMain8001B394Words[(cpu->pc - 0x8001b394u) / 4u];
    else if (cpu->pc >= 0x8001b3c4u && cpu->pc < 0x8001b710u)
        instruction = kMain8001B3C4Words[(cpu->pc - 0x8001b3c4u) / 4u];
    else if (cpu->pc >= 0x8001b710u && cpu->pc < 0x8001b788u)
        instruction = kMain8001B710Words[(cpu->pc - 0x8001b710u) / 4u];
    else if (cpu->pc >= 0x8001b788u && cpu->pc < 0x8001b7c4u)
        instruction = kMain8001B788Words[(cpu->pc - 0x8001b788u) / 4u];
    else if (cpu->pc >= 0x8001b7c4u && cpu->pc < 0x8001b85cu)
        instruction = kMain8001B7C4Words[(cpu->pc - 0x8001b7c4u) / 4u];
    else if (cpu->pc >= 0x8002d4c8u && cpu->pc < 0x8002d59cu)
        instruction = kMain8002D4C8Words[(cpu->pc - 0x8002d4c8u) / 4u];
    else if (cpu->pc >= 0x8002d7fcu && cpu->pc < 0x8002d80cu)
        instruction = kMain8002D7FCWords[(cpu->pc - 0x8002d7fcu) / 4u];
    else if (cpu->pc >= 0x8002ed90u && cpu->pc < 0x8002ede4u)
        instruction = kMain8002ED90Words[(cpu->pc - 0x8002ed90u) / 4u];
    else if (cpu->pc >= 0x8002fd14u && cpu->pc < 0x8002fdc8u)
        instruction = kMain8002FD14Words[(cpu->pc - 0x8002fd14u) / 4u];
    else if (cpu->pc >= 0x8002fde8u && cpu->pc < 0x8002ff0cu)
        instruction = kMain8002FDE8Words[(cpu->pc - 0x8002fde8u) / 4u];
    else if (cpu->pc >= 0x8002ff0cu && cpu->pc < 0x800301a4u)
        instruction = kMain8002FF0CWords[(cpu->pc - 0x8002ff0cu) / 4u];
    else if (cpu->pc >= 0x80030730u && cpu->pc < 0x80030a14u)
        instruction = kMain80030730Words[(cpu->pc - 0x80030730u) / 4u];
    else if (cpu->pc >= 0x80030a14u && cpu->pc < 0x80030ca4u)
        instruction = kMain80030A14Words[(cpu->pc - 0x80030a14u) / 4u];
    else if (cpu->pc >= 0x80031a98u && cpu->pc < 0x80031b7cu)
        instruction = kMain80031A98Words[(cpu->pc - 0x80031a98u) / 4u];
    else if (cpu->pc >= 0x800363ccu && cpu->pc < 0x80036af8u)
        instruction = kMain800363CCWords[(cpu->pc - 0x800363ccu) / 4u];
    else if (cpu->pc >= 0x80036af8u && cpu->pc < 0x80036d24u)
        instruction = kMain80036AF8Words[(cpu->pc - 0x80036af8u) / 4u];
    else if (cpu->pc >= 0x80037144u && cpu->pc < 0x80037334u)
        instruction = kMain80037144Words[(cpu->pc - 0x80037144u) / 4u];
    else if (cpu->pc >= 0x80037334u && cpu->pc < 0x80037358u)
        instruction = kMain80037334Words[(cpu->pc - 0x80037334u) / 4u];
    else if (cpu->pc >= 0x80037358u && cpu->pc < 0x80037368u)
        instruction = kMain80037358Words[(cpu->pc - 0x80037358u) / 4u];
    else if (cpu->pc >= 0x80037368u && cpu->pc < 0x800373d0u)
        instruction = kMain80037368Words[(cpu->pc - 0x80037368u) / 4u];
    else if (cpu->pc >= 0x800373d0u && cpu->pc < 0x800374ccu)
        instruction = kMain800373D0Words[(cpu->pc - 0x800373d0u) / 4u];
    else if (cpu->pc >= 0x800374ccu && cpu->pc < 0x8003750cu)
        instruction = kMain800374CCWords[(cpu->pc - 0x800374ccu) / 4u];
    else if (cpu->pc >= 0x8003750cu && cpu->pc < 0x8003775cu)
        instruction = kMain8003750CWords[(cpu->pc - 0x8003750cu) / 4u];
    else if (cpu->pc >= 0x800377d8u && cpu->pc < 0x80037cc8u)
        instruction = kMain800377D8Words[(cpu->pc - 0x800377d8u)/4u];
    else if (cpu->pc >= 0x8003775cu && cpu->pc < 0x800377d8u)
        instruction = kMain8003775CWords[(cpu->pc - 0x8003775cu) / 4u];
    else if (cpu->pc >= 0x80037cd8u && cpu->pc < 0x80037d74u)
        instruction = kMain80037CD8Words[(cpu->pc - 0x80037cd8u) / 4u];
    else if (cpu->pc >= 0x80037d74u && cpu->pc < 0x80037d98u)
        instruction = kMain80037D74Words[(cpu->pc - 0x80037d74u) / 4u];
    else if (cpu->pc >= 0x800401ccu && cpu->pc < 0x800401e4u)
        instruction = kMain800401CCWords[(cpu->pc - 0x800401ccu) / 4u];
    else if (cpu->pc >= 0x800415a8u && cpu->pc < 0x8004162cu)
        instruction = kMain800415A8Words[(cpu->pc - 0x800415a8u) / 4u];
    else if (cpu->pc >= 0x8004162cu && cpu->pc < 0x800416a8u)
        instruction = kMain8004162CWords[(cpu->pc - 0x8004162cu) / 4u];
    else if (cpu->pc >= 0x800416a8u && cpu->pc < 0x800419b0u)
        instruction = kMain800416A8Words[(cpu->pc - 0x800416a8u) / 4u];
    else if (cpu->pc >= 0x800419b0u && cpu->pc < 0x80041a20u)
        instruction = kMain800419B0Words[(cpu->pc - 0x800419b0u) / 4u];
    else if (cpu->pc >= 0x80041a80u && cpu->pc < 0x80041ab0u)
        instruction = kMain80041A80Words[(cpu->pc - 0x80041a80u) / 4u];
    else if (cpu->pc >= 0x80041ab0u && cpu->pc < 0x80041e8cu)
        instruction = kMain80041AB0Words[(cpu->pc - 0x80041ab0u) / 4u];
    else if (cpu->pc >= 0x80041e8cu && cpu->pc < 0x80042004u)
        instruction = kMain80041E8CWords[(cpu->pc - 0x80041e8cu) / 4u];
    else if (cpu->pc >= 0x80042374u && cpu->pc < 0x8004239cu)
        instruction = kMain80042374Words[(cpu->pc - 0x80042374u) / 4u];
    else if (cpu->pc >= 0x800439d4u && cpu->pc < 0x800439f8u)
        instruction = kMain800439D4Words[(cpu->pc - 0x800439d4u) / 4u];
    else if (cpu->pc >= 0x80046630u && cpu->pc < 0x8004674cu)
        instruction = kMain80046630Words[(cpu->pc - 0x80046630u) / 4u];
    else if (cpu->pc >= 0x8004674cu && cpu->pc < 0x8004689cu)
        instruction = kMain8004674CWords[(cpu->pc - 0x8004674cu) / 4u];
    else if (cpu->pc >= 0x8001aaa0u && cpu->pc < 0x8001aad0u)
        instruction = kMain8001AAA0Words[(cpu->pc - 0x8001aaa0u) / 4u];
    else if (cpu->pc >= 0x80014cacu && cpu->pc < 0x80014cf8u)
        instruction = kMain80014CACWords[(cpu->pc - 0x80014cacu) / 4u];
    else if (cpu->pc >= 0x8001aa98u && cpu->pc < 0x8001aaa0u)
        instruction = kMain8001AA98Words[(cpu->pc - 0x8001aa98u) / 4u];
    else if (cpu->pc >= 0x8001534cu && cpu->pc < 0x800153a4u)
        instruction = kMain8001534CWords[(cpu->pc - 0x8001534cu) / 4u];
    else if (cpu->pc >= 0x800153a4u && cpu->pc < 0x800153ccu)
        instruction = kMain800153A4Words[(cpu->pc - 0x800153a4u) / 4u];
    else if (cpu->pc >= 0x80010da0u && cpu->pc < 0x80010de0u)
        instruction = kMain80010DA0Words[(cpu->pc - 0x80010da0u) / 4u];
    else if (cpu->pc >= 0x800110ccu && cpu->pc < 0x80011144u)
        instruction = kMain800110CCWords[(cpu->pc - 0x800110ccu) / 4u];
    else if (cpu->pc >= 0x80011220u && cpu->pc < 0x8001125cu)
        instruction = kMain80011220Words[(cpu->pc - 0x80011220u) / 4u];
    else if (cpu->pc >= 0x8001125cu && cpu->pc < 0x800112a8u)
        instruction = kMain8001125CWords[(cpu->pc - 0x8001125cu) / 4u];
    else if (cpu->pc >= 0x800111bcu && cpu->pc < 0x80011220u)
        instruction = kMain800111BCWords[(cpu->pc - 0x800111bcu) / 4u];
    else if (cpu->pc >= 0x80011144u && cpu->pc < 0x800111bcu)
        instruction = kMain80011144Words[(cpu->pc - 0x80011144u) / 4u];
    else if (cpu->pc >= 0x8001a9f8u && cpu->pc < 0x8001aa78u)
        instruction = kMain8001A9F8Words[(cpu->pc - 0x8001a9f8u) / 4u];
    else if (cpu->pc >= 0x80010f80u && cpu->pc < 0x800110ccu)
        instruction = kMain80010F80Words[(cpu->pc - 0x80010f80u) / 4u];
    else if (cpu->pc >= 0x80029514u && cpu->pc < 0x80029524u)
        instruction = kMain80029514Words[(cpu->pc - 0x80029514u) / 4u];
    else if (cpu->pc >= 0x80010ed4u && cpu->pc < 0x80010f80u)
        instruction = kMain80010ED4Words[(cpu->pc - 0x80010ed4u) / 4u];
    else if (cpu->pc >= 0x80014338u && cpu->pc < 0x80014390u)
        instruction = kMain80014338Words[(cpu->pc - 0x80014338u) / 4u];
    else if (cpu->pc >= 0x80010d60u && cpu->pc < 0x80010da0u)
        instruction = kMain80010D60Words[(cpu->pc - 0x80010d60u) / 4u];
    else if (cpu->pc >= 0x8002fdc8u && cpu->pc < 0x8002fde8u)
        instruction = kMain8002FDC8Words[(cpu->pc - 0x8002fdc8u) / 4u];
    else if (cpu->pc >= 0x8002fc64u && cpu->pc < 0x8002fd14u)
        instruction = kMain8002FC64Words[(cpu->pc - 0x8002fc64u) / 4u];
    else if (cpu->pc >= 0x8003c438u && cpu->pc < 0x8003c498u)
        instruction = kMain8003C438Words[(cpu->pc - 0x8003c438u) / 4u];
    else if (cpu->pc >= 0x8003c498u && cpu->pc < 0x8003c4f0u)
        instruction = kMain8003C498Words[(cpu->pc - 0x8003c498u) / 4u];
    else if (cpu->pc >= 0x8003ae14u && cpu->pc < 0x8003ae9cu)
        instruction = kMain8003AE14Words[(cpu->pc - 0x8003ae14u) / 4u];
    else if (cpu->pc >= 0x800301a4u && cpu->pc < 0x800301c8u)
        instruction = kMain800301A4Words[(cpu->pc - 0x800301a4u) / 4u];
    else if (cpu->pc >= 0x8002fb08u && cpu->pc < 0x8002fc64u)
        instruction = kMain8002FB08Words[(cpu->pc - 0x8002fb08u) / 4u];
    else if (cpu->pc >= 0x8001abbcu && cpu->pc < 0x8001acf0u)
        instruction = kMain8001ABBCWords[(cpu->pc - 0x8001abbcu) / 4u];
    else if (cpu->pc >= 0x8001acf0u && cpu->pc < 0x8001ae90u)
        instruction = kMain8001ACF0Words[(cpu->pc - 0x8001acf0u) / 4u];
    else if (cpu->pc >= 0x8001ae90u && cpu->pc < 0x8001af04u)
        instruction = kMain8001AE90Words[(cpu->pc - 0x8001ae90u) / 4u];
    else if (cpu->pc >= 0x800149e0u && cpu->pc < 0x80014b10u)
        instruction = kMain800149E0Words[(cpu->pc - 0x800149e0u) / 4u];
    else if (cpu->pc >= 0x80014c28u && cpu->pc < 0x80014c54u)
        instruction = kMain80014C28Words[(cpu->pc - 0x80014c28u) / 4u];
    else if (cpu->pc >= 0x80014d30u && cpu->pc < 0x80014d68u)
        instruction = kMain80014D30Words[(cpu->pc - 0x80014d30u) / 4u];
    else if (cpu->pc >= 0x80014cf8u && cpu->pc < 0x80014d30u)
        instruction = kMain80014CF8Words[(cpu->pc - 0x80014cf8u) / 4u];
    else if (cpu->pc >= 0x800167f0u && cpu->pc < 0x800168b4u)
        instruction = kMain800167F0Words[(cpu->pc - 0x800167f0u) / 4u];
    else if (cpu->pc >= 0x80053290u && cpu->pc < 0x80053308u)
        instruction = kMain80053290Words[(cpu->pc - 0x80053290u)/4u];
    else if (cpu->pc >= 0x800553d8u && cpu->pc < 0x800553f4u)
        instruction = kMain800553D8Words[(cpu->pc - 0x800553d8u)/4u];
    else if (cpu->pc >= 0x800553f4u && cpu->pc < 0x80055d40u)
        instruction = kMain800553F4Words[(cpu->pc - 0x800553f4u)/4u];
    else if (cpu->pc >= 0x8001c9d0u && cpu->pc < 0x8001ca1cu)
        instruction = kMain8001C9D0Words[(cpu->pc - 0x8001c9d0u)/4u];
    else if (cpu->pc >= 0x8001c2c4u && cpu->pc < 0x8001c320u)
        instruction = kMain8001C2C4Words[(cpu->pc - 0x8001c2c4u)/4u];
    else if (cpu->pc >= 0x8001c320u && cpu->pc < 0x8001c448u)
        instruction = kMain8001C320Words[(cpu->pc - 0x8001c320u)/4u];
    else if (cpu->pc >= 0x800285acu && cpu->pc < 0x800285ccu)
        instruction = kMain800285ACWords[(cpu->pc - 0x800285acu)/4u];
    else if (cpu->pc >= 0x8005c4ccu && cpu->pc < 0x8005c4dcu)
        instruction = kMain8005C4CCWords[(cpu->pc - 0x8005c4ccu) / 4u];
    else if (cpu->pc >= 0x80011e24u && cpu->pc < 0x80011e84u)
        instruction = kMain80011E24Words[(cpu->pc - 0x80011e24u) / 4u];
    else if (cpu->pc >= 0x800295d4u && cpu->pc < 0x80029664u)
        instruction = kMain800295D4Words[(cpu->pc - 0x800295d4u) / 4u];
    else if (cpu->pc >= 0x80029664u && cpu->pc < 0x80029690u)
        instruction = kMain80029664Words[(cpu->pc - 0x80029664u) / 4u];
    else if (cpu->pc >= 0x80011380u && cpu->pc < 0x80011680u)
        instruction = kMain80011380Words[(cpu->pc - 0x80011380u) / 4u];
    else if (cpu->pc >= 0x800118acu && cpu->pc < 0x80011928u)
        instruction = kMain800118ACWords[(cpu->pc - 0x800118acu) / 4u];
    else if (cpu->pc >= 0x80010a84u && cpu->pc < 0x80010a98u)
        instruction = kMain80010A84Words[(cpu->pc - 0x80010a84u) / 4u];
    else if (cpu->pc >= 0x800146b0u && cpu->pc < 0x80014774u)
        instruction = kMain800146B0Words[(cpu->pc - 0x800146b0u) / 4u];
    else if (cpu->pc >= 0x800527c4u && cpu->pc < 0x8005283cu)
        instruction = kMain800527C4Words[(cpu->pc - 0x800527c4u) / 4u];
    else if (cpu->pc >= 0x80053eecu && cpu->pc < 0x80053f6cu)
        instruction = kMain80053EECWords[(cpu->pc - 0x80053eecu) / 4u];
    else if (cpu->pc >= 0x8001bff8u && cpu->pc < 0x8001c00cu)
        instruction = kMain8001BFF8Words[(cpu->pc - 0x8001bff8u) / 4u];
    else if (cpu->pc >= 0x80011928u && cpu->pc < 0x80011998u)
        instruction = kMain80011928Words[(cpu->pc - 0x80011928u) / 4u];
    else if (cpu->pc >= 0x8001bfe8u && cpu->pc < 0x8001bff8u)
        instruction = kMain8001BFE8Words[(cpu->pc - 0x8001bfe8u) / 4u];
    else if (cpu->pc >= 0x800116e0u && cpu->pc < 0x80011778u)
        instruction = kMain800116E0Words[(cpu->pc - 0x800116e0u) / 4u];
    else if (cpu->pc >= 0x80029000u && cpu->pc < 0x80029020u)
        instruction = kMain80029000Words[(cpu->pc - 0x80029000u) / 4u];
    else if (cpu->pc >= 0x80028d9cu && cpu->pc < 0x80028dbcu)
        instruction = kMain80028D9CWords[(cpu->pc - 0x80028d9cu) / 4u];
    else if (cpu->pc >= 0x80028fbcu && cpu->pc < 0x80028fdcu)
        instruction = kMain80028FBCWords[(cpu->pc - 0x80028fbcu) / 4u];
    else if (cpu->pc >= 0x800183e0u && cpu->pc < 0x80018450u)
        instruction = kMain800183E0Words[(cpu->pc - 0x800183e0u) / 4u];
    else if (cpu->pc >= 0x800167b8u && cpu->pc < 0x800167f0u)
        instruction = kMain800167B8Words[(cpu->pc - 0x800167b8u) / 4u];
    else if (cpu->pc >= 0x80016224u && cpu->pc < 0x80016450u)
        instruction = kMain80016224Words[(cpu->pc - 0x80016224u) / 4u];
    else if (cpu->pc >= 0x80010a08u && cpu->pc < 0x80010a84u)
        instruction = kMain80010A08Words[(cpu->pc - 0x80010a08u) / 4u];
    else if (cpu->pc >= 0x80016638u && cpu->pc < 0x800166e8u)
        instruction = kMain80016638Words[(cpu->pc - 0x80016638u) / 4u];
    else if (cpu->pc >= 0x80010cecu && cpu->pc < 0x80010d60u)
        instruction = kMain80010CECWords[(cpu->pc - 0x80010cecu) / 4u];
    else if (cpu->pc >= 0x80011818u && cpu->pc < 0x800118acu)
        instruction = kMain80011818Words[(cpu->pc - 0x80011818u) / 4u];
    else if (cpu->pc >= 0x80011a3cu && cpu->pc < 0x80011adcu)
        instruction = kMain80011A3CWords[(cpu->pc - 0x80011a3cu) / 4u];
    else if (cpu->pc >= 0x8005b1c4u && cpu->pc < 0x8005b400u)
        instruction = kMain8005B1C4Words[(cpu->pc - 0x8005b1c4u) / 4u];
    else if (cpu->pc >= 0x80010c7cu && cpu->pc < 0x80010cecu)
        instruction = kMain80010C7CWords[(cpu->pc - 0x80010c7cu) / 4u];
    else if (cpu->pc >= 0x8001513cu && cpu->pc < 0x80015144u)
        instruction = kMain8001513CWords[(cpu->pc - 0x8001513cu) / 4u];
    else if (cpu->pc >= 0x80015608u && cpu->pc < 0x80015760u)
        instruction = kMain80015608Words[(cpu->pc - 0x80015608u) / 4u];
    else if (cpu->pc >= 0x80015760u && cpu->pc < 0x80015908u)
        instruction = kMain80015760Words[(cpu->pc - 0x80015760u) / 4u];
    else if (cpu->pc >= 0x80059a80u && cpu->pc < 0x80059b44u)
        instruction = kMain80059A80Words[(cpu->pc - 0x80059a80u)/4u];
    else if (cpu->pc >= 0x80019018u && cpu->pc < 0x80019028u)
        instruction = kMain80019018Words[(cpu->pc - 0x80019018u)/4u];
    else if (cpu->pc >= 0x80018e78u && cpu->pc < 0x80018e9cu)
        instruction = kMain80018E78Words[(cpu->pc - 0x80018e78u)/4u];
    else if (cpu->pc >= 0x8002ab64u && cpu->pc < 0x8002ac00u)
        instruction = kMain8002AB64Words[(cpu->pc - 0x8002ab64u)/4u];
    else if (cpu->pc >= 0x8002ac00u && cpu->pc < 0x8002ac98u)
        instruction = kMain8002AC00Words[(cpu->pc - 0x8002ac00u)/4u];
    else if (cpu->pc >= 0x80015978u && cpu->pc < 0x8001599cu)
        instruction = kMain80015978Words[(cpu->pc - 0x80015978u)/4u];
    else if (cpu->pc >= 0x80012c6cu && cpu->pc < 0x80012cb8u)
        instruction = kMain80012C6CWords[(cpu->pc - 0x80012c6cu)/4u];
    else if (cpu->pc >= 0x80012abcu && cpu->pc < 0x80012b04u)
        instruction = kMain80012ABCWords[(cpu->pc - 0x80012abcu)/4u];
    else if (cpu->pc >= 0x80012cb8u && cpu->pc < 0x80012d0cu)
        instruction = kMain80012CB8Words[(cpu->pc - 0x80012cb8u)/4u];
    else if (cpu->pc >= 0x80012b04u && cpu->pc < 0x80012b58u)
        instruction = kMain80012B04Words[(cpu->pc - 0x80012b04u)/4u];
    else if (cpu->pc >= 0x80012b58u && cpu->pc < 0x80012c6cu)
        instruction = kMain80012B58Words[(cpu->pc - 0x80012b58u)/4u];
    else if (cpu->pc >= 0x80012d0cu && cpu->pc < 0x80012dbcu)
        instruction = kMain80012D0CWords[(cpu->pc - 0x80012d0cu)/4u];
    else if (cpu->pc >= 0x80049cacu && cpu->pc < 0x80049f38u)
        instruction = kMain80049CACWords[(cpu->pc - 0x80049cacu)/4u];
    else if (cpu->pc >= 0x8004914cu && cpu->pc < 0x8004917cu)
        instruction = kMain8004914CWords[(cpu->pc - 0x8004914cu)/4u];
    else if (cpu->pc >= 0x800491acu && cpu->pc < 0x800491ccu)
        instruction = kMain800491ACWords[(cpu->pc - 0x800491acu)/4u];
    else if (cpu->pc >= 0x8004945cu && cpu->pc < 0x8004948cu)
        instruction = kMain8004945CWords[(cpu->pc - 0x8004945cu)/4u];
    else if (cpu->pc >= 0x80011e84u && cpu->pc < 0x80011eb4u)
        instruction = kMain80011E84Words[(cpu->pc - 0x80011e84u)/4u];
    else if (cpu->pc >= 0x8005a600u && cpu->pc < 0x8005a658u)
        instruction = kMain8005A600Words[(cpu->pc - 0x8005a600u)/4u];
    else if (cpu->pc >= 0x80024054u && cpu->pc < 0x800241c0u)
        instruction = kMain80024054Words[(cpu->pc - 0x80024054u)/4u];
    else if (cpu->pc >= 0x8001c214u && cpu->pc < 0x8001c2c4u)
        instruction = kMain8001C214Words[(cpu->pc - 0x8001c214u)/4u];
    else if (cpu->pc >= 0x8001c810u && cpu->pc < 0x8001c8c4u)
        instruction = kMain8001C810Words[(cpu->pc - 0x8001c810u)/4u];
    else if (cpu->pc >= 0x8001d050u && cpu->pc < 0x8001d074u)
        instruction = kMain8001D050Words[(cpu->pc - 0x8001d050u)/4u];
    else if (cpu->pc >= 0x8001cd50u && cpu->pc < 0x8001cd9cu)
        instruction = kMain8001CD50Words[(cpu->pc - 0x8001cd50u)/4u];
    else if (cpu->pc >= 0x800233ccu && cpu->pc < 0x800234e4u)
        instruction = kMain800233CCWords[(cpu->pc - 0x800233ccu)/4u];
    else if (cpu->pc >= 0x800234e4u && cpu->pc < 0x80023570u)
        instruction = kMain800234E4Words[(cpu->pc - 0x800234e4u)/4u];
    else if (cpu->pc >= 0x80023570u && cpu->pc < 0x8002374cu)
        instruction = kMain80023570Words[(cpu->pc - 0x80023570u)/4u];
    else if (cpu->pc >= 0x8001ca1cu && cpu->pc < 0x8001ca88u)
        instruction = kMain8001CA1CWords[(cpu->pc - 0x8001ca1cu)/4u];
    else if (cpu->pc >= 0x8001ca88u && cpu->pc < 0x8001cb00u)
        instruction = kMain8001CA88Words[(cpu->pc - 0x8001ca88u)/4u];
    else if (cpu->pc >= 0x8001cb00u && cpu->pc < 0x8001cb6cu)
        instruction = kMain8001CB00Words[(cpu->pc - 0x8001cb00u)/4u];
    else if (cpu->pc >= 0x8001cb6cu && cpu->pc < 0x8001cbdcu)
        instruction = kMain8001CB6CWords[(cpu->pc - 0x8001cb6cu)/4u];
    else if (cpu->pc >= 0x8001cbdcu && cpu->pc < 0x8001cc3cu)
        instruction = kMain8001CBDCWords[(cpu->pc - 0x8001cbdcu)/4u];
    else if (cpu->pc >= 0x8001cc3cu && cpu->pc < 0x8001cca0u)
        instruction = kMain8001CC3CWords[(cpu->pc - 0x8001cc3cu)/4u];
    else if (cpu->pc >= 0x8001cca0u && cpu->pc < 0x8001cd04u)
        instruction = kMain8001CCA0Words[(cpu->pc - 0x8001cca0u)/4u];
    else if (cpu->pc >= 0x8001cd04u && cpu->pc < 0x8001cd50u)
        instruction = kMain8001CD04Words[(cpu->pc - 0x8001cd04u)/4u];
    else if (cpu->pc >= 0x8001cd9cu && cpu->pc < 0x8001cde8u)
        instruction = kMain8001CD9CWords[(cpu->pc - 0x8001cd9cu)/4u];
    else if (cpu->pc >= 0x8001cde8u && cpu->pc < 0x8001ce28u)
        instruction = kMain8001CDE8Words[(cpu->pc - 0x8001cde8u)/4u];
    else if (cpu->pc >= 0x8001ce28u && cpu->pc < 0x8001ce68u)
        instruction = kMain8001CE28Words[(cpu->pc - 0x8001ce28u)/4u];
    else if (cpu->pc >= 0x8001ce68u && cpu->pc < 0x8001cec0u)
        instruction = kMain8001CE68Words[(cpu->pc - 0x8001ce68u)/4u];
    else if (cpu->pc >= 0x8001cec0u && cpu->pc < 0x8001cf00u)
        instruction = kMain8001CEC0Words[(cpu->pc - 0x8001cec0u)/4u];
    else if (cpu->pc >= 0x8001cf00u && cpu->pc < 0x8001cf30u)
        instruction = kMain8001CF00Words[(cpu->pc - 0x8001cf00u)/4u];
    else if (cpu->pc >= 0x8001cf30u && cpu->pc < 0x8001cf48u)
        instruction = kMain8001CF30Words[(cpu->pc - 0x8001cf30u)/4u];
    else if (cpu->pc >= 0x8001cf48u && cpu->pc < 0x8001cfb8u)
        instruction = kMain8001CF48Words[(cpu->pc - 0x8001cf48u)/4u];
    else if (cpu->pc >= 0x8001cfb8u && cpu->pc < 0x8001cfdcu)
        instruction = kMain8001CFB8Words[(cpu->pc - 0x8001cfb8u)/4u];
    else if (cpu->pc >= 0x8001d074u && cpu->pc < 0x8001d0e8u)
        instruction = kMain8001D074Words[(cpu->pc - 0x8001d074u)/4u];
    else if (cpu->pc >= 0x8001d0e8u && cpu->pc < 0x8001d0f4u)
        instruction = kMain8001D0E8Words[(cpu->pc - 0x8001d0e8u)/4u];
    else if (cpu->pc >= 0x8001d0f4u && cpu->pc < 0x8001d130u)
        instruction = kMain8001D0F4Words[(cpu->pc - 0x8001d0f4u)/4u];
    else if (cpu->pc >= 0x8001d130u && cpu->pc < 0x8001d150u)
        instruction = kMain8001D130Words[(cpu->pc - 0x8001d130u)/4u];
    else if (cpu->pc >= 0x8001d150u && cpu->pc < 0x8001d16cu)
        instruction = kMain8001D150Words[(cpu->pc - 0x8001d150u)/4u];
    else if (cpu->pc >= 0x8001c8c4u && cpu->pc < 0x8001c924u)
        instruction = kMain8001C8C4Words[(cpu->pc - 0x8001c8c4u)/4u];
    else if (cpu->pc >= 0x8001c924u && cpu->pc < 0x8001c97cu)
        instruction = kMain8001C924Words[(cpu->pc - 0x8001c924u)/4u];
    else if (cpu->pc >= 0x8001c97cu && cpu->pc < 0x8001c9d0u)
        instruction = kMain8001C97CWords[(cpu->pc - 0x8001c97cu)/4u];
    else if (cpu->pc >= 0x8001cfdcu && cpu->pc < 0x8001d050u)
        instruction = kMain8001CFDCWords[(cpu->pc - 0x8001cfdcu)/4u];
    else if (cpu->pc >= 0x800599b8u && cpu->pc < 0x80059a80u)
        instruction = kMain800599B8Words[(cpu->pc - 0x800599b8u) / 4u];
    else if (cpu->pc >= 0x80053d44u && cpu->pc < 0x80053e28u)
        instruction = kMain80053D44Words[(cpu->pc - 0x80053d44u) / 4u];
    else if (cpu->pc >= 0x80058890u && cpu->pc < 0x80058a4cu)
        instruction = kMain80058890Words[(cpu->pc - 0x80058890u) / 4u];
    else if (cpu->pc >= 0x8001fb8cu && cpu->pc < 0x8001fc08u)
        instruction = kMain8001FB8CWords[(cpu->pc - 0x8001fb8cu) / 4u];
    else if (cpu->pc >= 0x8001d388u && cpu->pc < 0x8001d3fcu)
        instruction = kMain8001D388Words[(cpu->pc - 0x8001d388u) / 4u];
    else if (cpu->pc >= 0x80015908u && cpu->pc < 0x80015954u)
        instruction = kMain80015908Words[(cpu->pc - 0x80015908u) / 4u];
    else if (cpu->pc >= 0x80015a74u && cpu->pc < 0x80015ad0u)
        instruction = kMain80015A74Words[(cpu->pc - 0x80015a74u) / 4u];
    else if (cpu->pc >= 0x8005b75cu && cpu->pc < 0x8005b7b0u)
        instruction = kMain8005B75CWords[(cpu->pc - 0x8005b75cu) / 4u];
    else if (cpu->pc >= 0x80058b7cu && cpu->pc < 0x80058c6cu)
        instruction = kMain80058B7CWords[(cpu->pc - 0x80058b7cu) / 4u];
    else if (cpu->pc >= 0x8005e8e8u && cpu->pc < 0x8005ea34u)
        instruction = kMain8005E8E8Words[(cpu->pc - 0x8005e8e8u) / 4u];
    else if (cpu->pc >= 0x8004974cu && cpu->pc < 0x8004978cu)
        instruction = kMain8004974CWords[(cpu->pc - 0x8004974cu) / 4u];
    else if (cpu->pc >= 0x80052fccu && cpu->pc < 0x80053050u)
        instruction = kMain80052FCCWords[(cpu->pc - 0x80052fccu) / 4u];
    else if (cpu->pc >= 0x80054514u && cpu->pc < 0x800547d8u)
        instruction = kMain80054514Words[(cpu->pc - 0x80054514u) / 4u];
    else if (cpu->pc >= 0x80048eacu && cpu->pc < 0x80048fb8u)
        instruction = kMain80048EACWords[(cpu->pc - 0x80048eacu) / 4u];
    else if (cpu->pc >= 0x80053050u && cpu->pc < 0x80053178u)
        instruction = kMain80053050Words[(cpu->pc - 0x80053050u) / 4u];
    else if (cpu->pc >= 0x8005ae80u && cpu->pc < 0x8005af68u)
        instruction = kMain8005AE80Words[(cpu->pc - 0x8005ae80u) / 4u];
    else if (cpu->pc >= 0x8005c054u && cpu->pc < 0x8005c1c0u)
        instruction = kMain8005C054Words[(cpu->pc - 0x8005c054u) / 4u];
    else if (cpu->pc >= 0x80010b40u && cpu->pc < 0x80010bb4u)
        instruction = kMain80010B40Words[(cpu->pc - 0x80010b40u) / 4u];
    else if (cpu->pc >= 0x80010bb4u && cpu->pc < 0x80010c7cu)
        instruction = kMain80010BB4Words[(cpu->pc - 0x80010bb4u) / 4u];
    else if (cpu->pc >= 0x80029690u && cpu->pc < 0x800296f8u)
        instruction = kMain80029690Words[(cpu->pc - 0x80029690u) / 4u];
    else if (cpu->pc >= 0x80029274u && cpu->pc < 0x8002931cu)
        instruction = kMain80029274Words[(cpu->pc - 0x80029274u) / 4u];
    else if (cpu->pc >= 0x8002aef8u && cpu->pc < 0x8002af08u)
        instruction = kMain8002AEF8Words[(cpu->pc - 0x8002aef8u) / 4u];
    else if (cpu->pc >= 0x80029254u && cpu->pc < 0x80029264u)
        instruction = kMain80029254Words[(cpu->pc - 0x80029254u) / 4u];
    else if (cpu->pc >= 0x80011dccu && cpu->pc < 0x80011df4u)
        instruction = kMain80011DCCWords[(cpu->pc - 0x80011dccu) / 4u];
    else if (cpu->pc >= 0x8001b384u && cpu->pc < 0x8001b394u)
        instruction = kMain8001B384Words[(cpu->pc - 0x8001b384u) / 4u];
    else if (cpu->pc >= 0x8001c0c8u && cpu->pc < 0x8001c14cu)
        instruction = kMain8001C0C8Words[(cpu->pc - 0x8001c0c8u) / 4u];
    else if (cpu->pc >= 0x8001b85cu && cpu->pc < 0x8001b86cu)
        instruction = kMain8001B85CWords[(cpu->pc - 0x8001b85cu) / 4u];
    else if (cpu->pc >= 0x80011cfcu && cpu->pc < 0x80011d54u)
        instruction = kMain80011CFCWords[(cpu->pc - 0x80011cfcu) / 4u];
    else if (cpu->pc >= 0x80011d54u && cpu->pc < 0x80011da0u)
        instruction = kMain80011D54Words[(cpu->pc - 0x80011d54u) / 4u];
    else if (cpu->pc >= 0x800191d4u && cpu->pc < 0x8001923cu)
        instruction = kMain800191D4Words[(cpu->pc - 0x800191d4u) / 4u];
    else if (cpu->pc >= 0x800191bcu && cpu->pc < 0x800191d4u)
        instruction = kMain800191BCWords[(cpu->pc - 0x800191bcu) / 4u];
    else if (cpu->pc >= 0x8001af04u && cpu->pc < 0x8001af34u)
        instruction = kMain8001AF04Words[(cpu->pc - 0x8001af04u) / 4u];
    else if (cpu->pc >= 0x8002f648u && cpu->pc < 0x8002f658u)
        instruction = kMain8002F648Words[(cpu->pc - 0x8002f648u) / 4u];
    else if (cpu->pc >= 0x8002f620u && cpu->pc < 0x8002f648u)
        instruction = kMain8002F620Words[(cpu->pc - 0x8002f620u) / 4u];
    else if (cpu->pc >= 0x80029504u && cpu->pc < 0x80029514u)
        instruction = kMain80029504Words[(cpu->pc - 0x80029504u) / 4u];
    else if (cpu->pc >= 0x8002f658u && cpu->pc < 0x8002f67cu)
        instruction = kMain8002F658Words[(cpu->pc - 0x8002f658u) / 4u];
    else if (cpu->pc >= 0x8002f5c8u && cpu->pc < 0x8002f620u)
        instruction = kMain8002F5C8Words[(cpu->pc - 0x8002f5c8u) / 4u];
    else if (cpu->pc >= 0x80018714u && cpu->pc < 0x80018730u)
        instruction = kMain80018714Words[(cpu->pc - 0x80018714u) / 4u];
    else if (cpu->pc >= 0x80018730u && cpu->pc < 0x80018918u)
        instruction = kMain80018730Words[(cpu->pc - 0x80018730u) / 4u];
    else if (cpu->pc >= 0x8002d858u && cpu->pc < 0x8002d8a8u)
        instruction = kMain8002D858Words[(cpu->pc - 0x8002d858u) / 4u];
    else if (cpu->pc >= 0x8003d650u && cpu->pc < 0x8003d6e4u)
        instruction = kMain8003D650Words[(cpu->pc - 0x8003d650u) / 4u];
    else if (cpu->pc >= 0x8001bfa0u && cpu->pc < 0x8001bfb0u)
        instruction = kMain8001BFA0Words[(cpu->pc - 0x8001bfa0u) / 4u];
    else if (cpu->pc >= 0x8001bfb0u && cpu->pc < 0x8001bfd0u)
        instruction = kMain8001BFB0Words[(cpu->pc - 0x8001bfb0u) / 4u];
    else if (cpu->pc >= 0x8004657cu && cpu->pc < 0x80046610u)
        instruction = kMain8004657CWords[(cpu->pc - 0x8004657cu) / 4u];
    else if (cpu->pc >= 0x80046b44u && cpu->pc < 0x80046bfcu)
        instruction = kMain80046B44Words[(cpu->pc - 0x80046b44u) / 4u];
    else if (cpu->pc >= 0x80046c38u && cpu->pc < 0x80046cfcu)
        instruction = kMain80046C38Words[(cpu->pc - 0x80046c38u) / 4u];
    else if (cpu->pc >= 0x80046d1cu && cpu->pc < 0x8004768cu)
        instruction = kMain80046D1CWords[(cpu->pc - 0x80046d1cu) / 4u];
    else if (cpu->pc >= 0x80043088u && cpu->pc < 0x800430b8u)
        instruction = kMain80043088Words[(cpu->pc - 0x80043088u) / 4u];
    else if (cpu->pc >= 0x8004689cu && cpu->pc < 0x800468fcu)
        instruction = kMain8004689CWords[(cpu->pc - 0x8004689cu) / 4u];
    else if (cpu->pc >= 0x80046abcu && cpu->pc < 0x80046b44u)
        instruction = kMain80046ABCWords[(cpu->pc - 0x80046abcu) / 4u];
    else if (cpu->pc >= 0x800468fcu && cpu->pc < 0x80046980u)
        instruction = kMain800468FCWords[(cpu->pc - 0x800468fcu) / 4u];
    else if (cpu->pc >= 0x80046bfcu && cpu->pc < 0x80046c38u)
        instruction = kMain80046BFCWords[(cpu->pc - 0x80046bfcu) / 4u];
    else if (cpu->pc >= 0x80046cfcu && cpu->pc < 0x80046d1cu)
        instruction = kMain80046CFCWords[(cpu->pc - 0x80046cfcu) / 4u];
    else if (cpu->pc >= 0x800469a8u && cpu->pc < 0x800469ccu)
        instruction = kMain800469A8Words[(cpu->pc - 0x800469a8u) / 4u];
    else if (cpu->pc >= 0x80046994u && cpu->pc < 0x800469a8u)
        instruction = kMain80046994Words[(cpu->pc - 0x80046994u) / 4u];
    else if (cpu->pc >= 0x800469ccu && cpu->pc < 0x80046a5cu)
        instruction = kMain800469CCWords[(cpu->pc - 0x800469ccu) / 4u];
    else if (cpu->pc >= 0x80046610u && cpu->pc < 0x80046630u)
        instruction = kMain80046610Words[(cpu->pc - 0x80046610u) / 4u];
    else if (cpu->pc >= 0x8004768cu && cpu->pc < 0x800476c0u)
        instruction = kMain8004768CWords[(cpu->pc - 0x8004768cu) / 4u];
    else if (cpu->pc >= 0x800476c0u && cpu->pc < 0x8004787cu)
        instruction = kMain800476C0Words[(cpu->pc - 0x800476c0u) / 4u];
    else if (cpu->pc >= 0x8002d8d4u && cpu->pc < 0x8002d904u)
        instruction = kMain8002D8D4Words[(cpu->pc - 0x8002d8d4u) / 4u];
    else if (cpu->pc >= 0x80014b10u && cpu->pc < 0x80014bfcu)
        instruction = kMain80014B10Words[(cpu->pc - 0x80014b10u) / 4u];
    else if (cpu->pc >= 0x80029344u && cpu->pc < 0x8002941cu)
        instruction = kMain80029344Words[(cpu->pc - 0x80029344u) / 4u];
    else if (cpu->pc >= 0x8002941cu && cpu->pc < 0x80029444u)
        instruction = kMain8002941CWords[(cpu->pc - 0x8002941cu) / 4u];
    else if (cpu->pc >= 0x80010ae0u && cpu->pc < 0x80010b10u)
        instruction = kMain80010AE0Words[(cpu->pc - 0x80010ae0u) / 4u];
    else if (cpu->pc >= 0x80011b7cu && cpu->pc < 0x80011c10u)
        instruction = kMain80011B7CWords[(cpu->pc - 0x80011b7cu) / 4u];
    else if (cpu->pc >= 0x80011c10u && cpu->pc < 0x80011c8cu)
        instruction = kMain80011C10Words[(cpu->pc - 0x80011c10u) / 4u];
    else if (cpu->pc >= 0x80011778u && cpu->pc < 0x80011818u)
        instruction = kMain80011778Words[(cpu->pc - 0x80011778u) / 4u];
    else if (cpu->pc >= 0x80015498u && cpu->pc < 0x80015608u)
        instruction = kMain80015498Words[(cpu->pc - 0x80015498u) / 4u];
    else if (cpu->pc >= 0x80058b40u && cpu->pc < 0x80058b7cu)
        instruction = kMain80058B40Words[(cpu->pc - 0x80058b40u) / 4u];
    else if (cpu->pc >= 0x8001c00cu && cpu->pc < 0x8001c044u)
        instruction = kMain8001C00CWords[(cpu->pc - 0x8001c00cu) / 4u];
    else if (cpu->pc >= 0x8001f9f8u && cpu->pc < 0x8001fb8cu)
        instruction = kMain8001F9F8Words[(cpu->pc - 0x8001f9f8u) / 4u];
    else if (cpu->pc >= 0x8001d1c4u && cpu->pc < 0x8001d388u)
        instruction = kMain8001D1C4Words[(cpu->pc - 0x8001d1c4u) / 4u];
    else if (cpu->pc >= 0x800184f0u && cpu->pc < 0x80018714u)
        instruction = kMain800184F0Words[(cpu->pc - 0x800184f0u) / 4u];
    else if (cpu->pc >= 0x800596f4u && cpu->pc < 0x80059760u)
        instruction = kMain800596F4Words[(cpu->pc - 0x800596f4u) / 4u];
    else if (cpu->pc >= 0x8005bed8u && cpu->pc < 0x8005c020u)
        instruction = kMain8005BED8Words[(cpu->pc - 0x8005bed8u) / 4u];
    else if (cpu->pc >= 0x8002cdd8u && cpu->pc < 0x8002cfe4u)
        instruction = kMain8002CDD8Words[(cpu->pc - 0x8002cdd8u) / 4u];
    else if (cpu->pc >= 0x8003d25cu && cpu->pc < 0x8003d32cu)
        instruction = kMain8003D25CWords[(cpu->pc - 0x8003d25cu) / 4u];
    else if (cpu->pc >= 0x8002cfe4u && cpu->pc < 0x8002d034u)
        instruction = kMain8002CFE4Words[(cpu->pc - 0x8002cfe4u) / 4u];
    else if (cpu->pc >= 0x8002d904u && cpu->pc < 0x8002dc68u)
        instruction = kMain8002D904Words[(cpu->pc - 0x8002d904u) / 4u];
    else if (cpu->pc >= 0x80037fc4u && cpu->pc < 0x8003819cu)
        instruction = kMain80037FC4Words[(cpu->pc - 0x80037fc4u) / 4u];
    else if (cpu->pc >= 0x8002ec10u && cpu->pc < 0x8002ed90u)
        instruction = kMain8002EC10Words[(cpu->pc - 0x8002ec10u) / 4u];
    else if (cpu->pc >= 0x8003836cu && cpu->pc < 0x800383a4u)
        instruction = kMain8003836CWords[(cpu->pc - 0x8003836cu) / 4u];
    else if (cpu->pc >= 0x8003c4f0u && cpu->pc < 0x8003c598u)
        instruction = kMain8003C4F0Words[(cpu->pc - 0x8003c4f0u) / 4u];
    else if (cpu->pc >= 0x80030f80u && cpu->pc < 0x800314dcu)
        instruction = kMain80030F80Words[(cpu->pc - 0x80030f80u) / 4u];
    else if (cpu->pc >= 0x8002d320u && cpu->pc < 0x8002d4b8u)
        instruction = kMain8002D320Words[(cpu->pc - 0x8002d320u) / 4u];
    else if (cpu->pc >= 0x8002ee64u && cpu->pc < 0x8002ee90u)
        instruction = kMain8002EE64Words[(cpu->pc - 0x8002ee64u) / 4u];
    else if (cpu->pc >= 0x8002eff8u && cpu->pc < 0x8002f064u)
        instruction = kMain8002EFF8Words[(cpu->pc - 0x8002eff8u) / 4u];
    else if (cpu->pc >= 0x800314dcu && cpu->pc < 0x800316f8u)
        instruction = kMain800314DCWords[(cpu->pc - 0x800314dcu) / 4u];
    else if (cpu->pc >= 0x800316f8u && cpu->pc < 0x80031988u)
        instruction = kMain800316F8Words[(cpu->pc - 0x800316f8u) / 4u];
    else if (cpu->pc >= 0x80031988u && cpu->pc < 0x80031a98u)
        instruction = kMain80031988Words[(cpu->pc - 0x80031988u) / 4u];
    else if (cpu->pc >= 0x8003819cu && cpu->pc < 0x800381e4u)
        instruction = kMain8003819CWords[(cpu->pc - 0x8003819cu) / 4u];
    else if (cpu->pc >= 0x80038210u && cpu->pc < 0x80038308u)
        instruction = kMain80038210Words[(cpu->pc - 0x80038210u) / 4u];
    else if (cpu->pc >= 0x80038308u && cpu->pc < 0x8003834cu)
        instruction = kMain80038308Words[(cpu->pc - 0x80038308u) / 4u];
    else if (cpu->pc >= 0x8003834cu && cpu->pc < 0x8003836cu)
        instruction = kMain8003834CWords[(cpu->pc - 0x8003834cu) / 4u];
    else if (cpu->pc >= 0x80038638u && cpu->pc < 0x80038668u)
        instruction = kMain80038638Words[(cpu->pc - 0x80038638u) / 4u];
    else if (cpu->pc >= 0x8003b250u && cpu->pc < 0x8003b280u)
        instruction = kMain8003B250Words[(cpu->pc - 0x8003b250u) / 4u];
    else if (cpu->pc >= 0x8003c23cu && cpu->pc < 0x8003c438u)
        instruction = kMain8003C23CWords[(cpu->pc - 0x8003c23cu) / 4u];
    else if (cpu->pc >= 0x8003d3b4u && cpu->pc < 0x8003d3f8u)
        instruction = kMain8003D3B4Words[(cpu->pc - 0x8003d3b4u) / 4u];
    else if (cpu->pc >= 0x80031be0u && cpu->pc < 0x80031cc8u)
        instruction = kMain80031BE0Words[(cpu->pc - 0x80031be0u) / 4u];
    else if (cpu->pc >= 0x8002f064u && cpu->pc < 0x8002f0d0u)
        instruction = kMain8002F064Words[(cpu->pc - 0x8002f064u) / 4u];
    else if (cpu->pc >= 0x80030ca4u && cpu->pc < 0x80030d80u)
        instruction = kMain80030CA4Words[(cpu->pc - 0x80030ca4u) / 4u];
    else if (cpu->pc >= 0x80030d80u && cpu->pc < 0x80030f80u)
        instruction = kMain80030D80Words[(cpu->pc - 0x80030d80u) / 4u];
    else if (cpu->pc >= 0x800336a8u && cpu->pc < 0x8003388cu)
        instruction = kMain800336A8Words[(cpu->pc - 0x800336a8u) / 4u];
    else if (cpu->pc >= 0x8003388cu && cpu->pc < 0x800342e8u)
        instruction = kMain8003388CWords[(cpu->pc - 0x8003388cu) / 4u];
    else if (cpu->pc >= 0x80034650u && cpu->pc < 0x800346d0u)
        instruction = kMain80034650Words[(cpu->pc - 0x80034650u) / 4u];
    else if (cpu->pc >= 0x8003f144u && cpu->pc < 0x8003f380u)
        instruction = kMain8003F144Words[(cpu->pc - 0x8003f144u) / 4u];
    else if (cpu->pc >= 0x8003f380u && cpu->pc < 0x8003f434u)
        instruction = kMain8003F380Words[(cpu->pc - 0x8003f380u) / 4u];
    else if (cpu->pc >= 0x800414e4u && cpu->pc < 0x800415a8u)
        instruction = kMain800414E4Words[(cpu->pc - 0x800414e4u) / 4u];
    else if (cpu->pc >= 0x800145ecu && cpu->pc < 0x800146b0u)
        instruction = kDraw800145ECWords[(cpu->pc - 0x800145ecu) / 4u];
    else if (cpu->pc >= 0x800525dcu && cpu->pc < 0x80052654u)
        instruction = kDraw800525DCWords[(cpu->pc - 0x800525dcu) / 4u];
    else if (cpu->pc >= 0x80052654u && cpu->pc < 0x800527c4u)
        instruction = kDraw80052654Words[(cpu->pc - 0x80052654u) / 4u];
    else if (cpu->pc >= 0x80059d68u && cpu->pc < 0x80059e6cu)
        instruction = kDraw80059D68Words[(cpu->pc - 0x80059d68u) / 4u];
    else if (cpu->pc >= 0x8005a870u && cpu->pc < 0x8005ab00u)
        instruction = kDraw8005A870Words[(cpu->pc - 0x8005a870u) / 4u];
    else if (cpu->pc >= 0x8005ab00u && cpu->pc < 0x8005ab58u)
        instruction = kDraw8005AB00Words[(cpu->pc - 0x8005ab00u) / 4u];
    else if (cpu->pc >= 0x8005ab58u && cpu->pc < 0x8005ac24u)
        instruction = kDraw8005AB58Words[(cpu->pc - 0x8005ab58u) / 4u];
    else if (cpu->pc >= 0x8005ac24u && cpu->pc < 0x8005acf0u)
        instruction = kDraw8005AC24Words[(cpu->pc - 0x8005ac24u) / 4u];
    else if (cpu->pc >= 0x8005acf0u && cpu->pc < 0x8005ad34u)
        instruction = kDraw8005ACF0Words[(cpu->pc - 0x8005acf0u) / 4u];
    else if (cpu->pc >= 0x8005ad34u && cpu->pc < 0x8005adb8u)
        instruction = kDraw8005AD34Words[(cpu->pc - 0x8005ad34u) / 4u];
    else if (cpu->pc >= 0x8005b7b0u && cpu->pc < 0x8005ba90u)
        instruction = kDraw8005B7B0Words[(cpu->pc - 0x8005b7b0u) / 4u];
    else if (cpu->pc >= 0x8005ba90u && cpu->pc < 0x8005bd7cu)
        instruction = kDraw8005BA90Words[(cpu->pc - 0x8005ba90u) / 4u];
    else if (cpu->pc >= 0x8001099cu && cpu->pc < 0x80010a08u)
        instruction = kMain8001099CWords[(cpu->pc - 0x8001099cu) / 4u];
    else if (cpu->pc >= 0x80058ce4u && cpu->pc < 0x80058d20u)
        instruction = kMain80058CE4Words[(cpu->pc - 0x80058ce4u) / 4u];
    else if (cpu->pc >= 0x8005b710u && cpu->pc < 0x8005b75cu)
        instruction = kDraw8005B710Words[(cpu->pc - 0x8005b710u) / 4u];
    else if (cpu->pc >= 0x8005c020u && cpu->pc < 0x8005c054u)
        instruction = kDraw8005C020Words[(cpu->pc - 0x8005c020u) / 4u];
    else if (cpu->pc >= 0x8005283cu && cpu->pc < 0x80052aa0u)
        instruction = kProjection8005283CWords[(cpu->pc - 0x8005283cu) / 4u];
    else if (cpu->pc >= 0x80052d00u && cpu->pc < 0x80052d90u)
        instruction = kProjection80052D00Words[(cpu->pc - 0x80052d00u) / 4u];
    else if (cpu->pc >= 0x80052d90u && cpu->pc < 0x80052e38u)
        instruction = kProjection80052D90Words[(cpu->pc - 0x80052d90u) / 4u];
    else if (cpu->pc >= 0x80052becu && cpu->pc < 0x80052d00u)
        instruction = kProjection80052BECWords[(cpu->pc - 0x80052becu) / 4u];
    else if (cpu->pc >= 0x80053178u && cpu->pc < 0x80053218u)
        instruction = kProjection80053178Words[(cpu->pc - 0x80053178u) / 4u];
    else if (cpu->pc >= 0x80053218u && cpu->pc < 0x80053290u)
        instruction = kDrawFollowup80053218Words[(cpu->pc - 0x80053218u) / 4u];
    else if (cpu->pc >= 0x80014774u && cpu->pc < 0x800147b8u)
        instruction = kDrawFollowup80014774Words[(cpu->pc - 0x80014774u) / 4u];
    else if (cpu->pc >= 0x800147b8u && cpu->pc < 0x80014928u)
        instruction = kDrawFollowup800147B8Words[(cpu->pc - 0x800147b8u) / 4u];
    else if (cpu->pc >= 0x800144d4u && cpu->pc < 0x80014554u)
        instruction = kCamera800144D4Words[(cpu->pc - 0x800144d4u) / 4u];
    else if (cpu->pc >= 0x80014554u && cpu->pc < 0x800145ecu)
        instruction = kSecondGeom80014554Words[(cpu->pc - 0x80014554u) / 4u];
    else if (cpu->pc >= 0x8002850cu && cpu->pc < 0x80028558u)
        instruction = kSecondGeom8002850CWords[(cpu->pc - 0x8002850cu) / 4u];
    else if (cpu->pc >= 0x80053af8u && cpu->pc < 0x80053b20u)
        instruction = kSecondGeom80053AF8Words[(cpu->pc - 0x80053af8u) / 4u];
    else if (cpu->pc >= 0x8002823cu && cpu->pc < 0x80028304u)
        instruction = kSecondGeom8002823CWords[(cpu->pc - 0x8002823cu) / 4u];
    else if (cpu->pc >= 0x80028620u && cpu->pc < 0x80028694u)
        instruction = kSecondGeom80028620Words[(cpu->pc - 0x80028620u) / 4u];
    else if (cpu->pc >= 0x80053308u && cpu->pc < 0x80053328u)
        instruction = kCamera80053308Words[(cpu->pc - 0x80053308u) / 4u];
    else if (cpu->pc >= 0x80053328u && cpu->pc < 0x80053804u)
        instruction = kCamera80053328Words[(cpu->pc - 0x80053328u) / 4u];
    else if (cpu->pc >= 0x8005386cu && cpu->pc < 0x800538bcu)
        instruction = kCamera8005386CWords[(cpu->pc - 0x8005386cu) / 4u];
    else if (cpu->pc >= 0x80053804u && cpu->pc < 0x8005386cu)
        instruction = kCamera80053804Words[(cpu->pc - 0x80053804u) / 4u];
    else if (cpu->pc >= 0x800538bcu && cpu->pc < 0x800538ecu)
        instruction = kCamera800538BCWords[(cpu->pc - 0x800538bcu) / 4u];
    else if (cpu->pc >= 0x800538ecu && cpu->pc < 0x80053978u)
        instruction = kCamera800538ECWords[(cpu->pc - 0x800538ecu) / 4u];
    else if (cpu->pc >= 0x80053f6cu && cpu->pc < 0x80054340u)
        instruction = kCamera80053F6CWords[(cpu->pc - 0x80053f6cu) / 4u];
    else if (cpu->pc >= 0x80053e28u && cpu->pc < 0x80053eecu)
        instruction = kCamera80053E28Words[(cpu->pc - 0x80053e28u) / 4u];
    else if (cpu->pc >= 0x80048d9cu && cpu->pc < 0x80048eacu)
        instruction = kCamera80048D9CWords[(cpu->pc - 0x80048d9cu) / 4u];
    else if (cpu->pc >= 0x800484ecu && cpu->pc < 0x8004864cu)
        instruction = kCamera800484ECWords[(cpu->pc - 0x800484ecu) / 4u];
    else if (cpu->pc >= 0x80053b20u && cpu->pc < 0x80053bd8u)
        instruction = kCamera80053B20Words[(cpu->pc - 0x80053b20u) / 4u];
    else if (cpu->pc >= 0x8004787cu && cpu->pc < 0x800478b8u)
        instruction = kCamera8004787CWords[(cpu->pc - 0x8004787cu) / 4u];
    else if (cpu->pc >= 0x800478b8u && cpu->pc < 0x80047948u)
        instruction = kCamera800478B8Words[(cpu->pc - 0x800478b8u) / 4u];
    else if (cpu->pc >= 0x80047948u && cpu->pc < 0x800479e8u)
        instruction = kCamera80047948Words[(cpu->pc - 0x80047948u) / 4u];
    else if (cpu->pc >= 0x80054340u && cpu->pc < 0x80054430u)
        instruction = kCamera80054340Words[(cpu->pc - 0x80054340u) / 4u];
    else if (cpu->pc >= 0x80054430u && cpu->pc < 0x800544f8u)
        instruction = kCamera80054430Words[(cpu->pc - 0x80054430u) / 4u];
    else if (cpu->pc >= 0x800544f8u && cpu->pc < 0x80054514u)
        instruction = kCamera800544F8Words[(cpu->pc - 0x800544f8u) / 4u];
    else if (cpu->pc >= 0x80047d3cu && cpu->pc < 0x80047dc0u)
        instruction = kCamera80047D3CWords[(cpu->pc - 0x80047d3cu) / 4u];
    else if (cpu->pc >= 0x80014444u && cpu->pc < 0x800144d4u)
        instruction = kSecondGeom80014444Words[(cpu->pc - 0x80014444u) / 4u];
    else if (cpu->pc >= 0x8004923cu && cpu->pc < 0x80049248u)
        instruction = kSecondGeom8004923CWords[(cpu->pc - 0x8004923cu) / 4u];
    else if (cpu->pc >= 0x80058a4cu && cpu->pc < 0x80058b04u)
        instruction = kDrawEnv80058A4CWords[(cpu->pc - 0x80058a4cu) / 4u];
    else if (cpu->pc >= 0x80058b04u && cpu->pc < 0x80058b40u)
        instruction = kDrawEnv80058B04Words[(cpu->pc - 0x80058b04u) / 4u];
    else if (cpu->pc >= 0x80014960u && cpu->pc < 0x80014998u)
        instruction = kDrawEnv80014960Words[(cpu->pc - 0x80014960u) / 4u];
    else if (cpu->pc >= 0x80014998u && cpu->pc < 0x800149e0u)
        instruction = kDrawEnv80014998Words[(cpu->pc - 0x80014998u) / 4u];
    else if (cpu->pc >= 0x80059888u && cpu->pc < 0x8005991cu)
        instruction = kClearImage80059888Words[(cpu->pc - 0x80059888u) / 4u];
    else if (cpu->pc >= 0x80059760u && cpu->pc < 0x80059888u)
        instruction = kClearImage80059760Words[(cpu->pc - 0x80059760u) / 4u];
    else if (cpu->pc >= 0x8005af68u && cpu->pc < 0x8005b1c4u)
        instruction = kClearImage8005AF68Words[(cpu->pc - 0x8005af68u) / 4u];
    else if (cpu->pc >= 0x80053cf8u && cpu->pc < 0x80053d44u)
        instruction = kGte80053CF8Words[(cpu->pc - 0x80053cf8u) / 4u];
    else if (cpu->pc >= 0x80047cb4u && cpu->pc < 0x80047d34u)
        instruction = kGte80047CB4Words[(cpu->pc - 0x80047cb4u) / 4u];
    else if (cpu->pc >= 0x8004d16cu && cpu->pc < 0x8004d1d4u)
        instruction = kGte8004D16CWords[(cpu->pc - 0x8004d16cu) / 4u];
    else if (cpu->pc >= 0x80053ad8u && cpu->pc < 0x80053af8u)
        instruction = kGte80053AD8Words[(cpu->pc - 0x80053ad8u) / 4u];
    else if (cpu->pc >= 0x800491fcu && cpu->pc < 0x8004921cu)
        instruction = kGte800491FCWords[(cpu->pc - 0x800491fcu) / 4u];
    else if (cpu->pc >= 0x8004921cu && cpu->pc < 0x80049234u)
        instruction = kGte8004921CWords[(cpu->pc - 0x8004921cu) / 4u];
    else if (cpu->pc >= 0x8005ce28u && cpu->pc < 0x8005ce34u)
        instruction = kGte8005CE28Words[(cpu->pc - 0x8005ce28u) / 4u];
    else if (cpu->pc >= 0x80043078u && cpu->pc < 0x80043088u)
        instruction = kDisplay80043078Words[(cpu->pc - 0x80043078u) / 4u];
    else if (cpu->pc >= 0x80059fc0u && cpu->pc < 0x8005a468u)
        instruction = kDisplay80059FC0Words[(cpu->pc - 0x80059fc0u) / 4u];
    else if (cpu->pc >= 0x8005b684u && cpu->pc < 0x8005b6acu)
        instruction = kDisplay8005B684Words[(cpu->pc - 0x8005b684u) / 4u];
    else if (cpu->pc >= 0x800426fcu && cpu->pc < 0x80042718u)
        instruction = kDraw800426FCWords[(cpu->pc - 0x800426fcu) / 4u];
    else if (cpu->pc >= CD_ENTER_CRITICAL && cpu->pc < CD_ENTER_CRITICAL + 16u)
        instruction = kSys1Words[(cpu->pc - CD_ENTER_CRITICAL) / 4u];
    else if (cpu->pc >= CALLBACK_EXIT_CRITICAL && cpu->pc < CALLBACK_EXIT_CRITICAL + 16u)
        instruction = kSys2Words[(cpu->pc - CALLBACK_EXIT_CRITICAL) / 4u];
    else if (cpu->pc >= 0x8005de78u && cpu->pc < 0x8005e0acu)
        instruction = kInputDigital8005DE78Words[(cpu->pc - 0x8005de78u) / 4u];
    else if (cpu->pc >= 0x8005e13cu && cpu->pc < 0x8005e164u)
        instruction = kInputDigital8005E13CWords[(cpu->pc - 0x8005e13cu) / 4u];
    else if (cpu->pc >= 0x8005e1a4u && cpu->pc < 0x8005e228u)
        instruction = kInputDigital8005E1A4Words[(cpu->pc - 0x8005e1a4u) / 4u];
    else if (cpu->pc >= 0x8005ea34u && cpu->pc < 0x8005ea54u)
        instruction = kInputDigital8005EA34Words[(cpu->pc - 0x8005ea34u) / 4u];
    else if (cpu->pc >= 0x8005ea54u && cpu->pc < 0x8005ea68u)
        instruction = kInputDigital8005EA54Words[(cpu->pc - 0x8005ea54u) / 4u];
    else if (cpu->pc >= 0x8005ea68u && cpu->pc < 0x8005ea88u)
        instruction = kInputDigital8005EA68Words[(cpu->pc - 0x8005ea68u) / 4u];
    else if (cpu->pc >= 0x8005ea88u && cpu->pc < 0x8005eaa8u)
        instruction = kInputDigital8005EA88Words[(cpu->pc - 0x8005ea88u) / 4u];
    else if (cpu->pc >= 0x8005eaa8u && cpu->pc < 0x8005eac8u)
        instruction = kInputDigital8005EAA8Words[(cpu->pc - 0x8005eaa8u) / 4u];
    else if (cpu->pc >= 0x8005eac8u && cpu->pc < 0x8005eae8u)
        instruction = kInputDigital8005EAC8Words[(cpu->pc - 0x8005eac8u) / 4u];
    else if (cpu->pc >= 0x8005eb28u && cpu->pc < 0x8005ec00u)
        instruction = kInputDigital8005EB28Words[(cpu->pc - 0x8005eb28u) / 4u];
    else if (cpu->pc >= 0x8005ec00u && cpu->pc < 0x8005ecc0u)
        instruction = kInputDigital8005EC00Words[(cpu->pc - 0x8005ec00u) / 4u];
    else if (cpu->pc >= 0x8005ecc0u && cpu->pc < 0x8005ed4cu)
        instruction = kInputDigital8005ECC0Words[(cpu->pc - 0x8005ecc0u) / 4u];
    else if (cpu->pc >= 0x8005ed4cu && cpu->pc < 0x8005f0c8u)
        instruction = kInputDigital8005ED4CWords[(cpu->pc - 0x8005ed4cu) / 4u];
    else if (cpu->pc >= 0x8005f290u && cpu->pc < 0x8005f384u)
        instruction = kInputDigital8005F290Words[(cpu->pc - 0x8005f290u) / 4u];
    else if (cpu->pc >= 0x8005f394u && cpu->pc < 0x8005f450u)
        instruction = kInputDigital8005F394Words[(cpu->pc - 0x8005f394u) / 4u];
    else if (cpu->pc >= 0x8005f450u && cpu->pc < 0x8005f6ccu)
        instruction = kInputDigital8005F450Words[(cpu->pc - 0x8005f450u) / 4u];
    else if (cpu->pc >= 0x8005f6ccu && cpu->pc < 0x8005f704u)
        instruction = kInputDigital8005F6CCWords[(cpu->pc - 0x8005f6ccu) / 4u];
    else if (cpu->pc >= 0x8005fa94u && cpu->pc < 0x8005fb70u)
        instruction = kInputDigital8005FA94Words[(cpu->pc - 0x8005fa94u) / 4u];
    else if (cpu->pc >= 0x8005d6ccu && cpu->pc < 0x8005d734u)
        instruction = kInputVerifierWords[(cpu->pc - 0x8005d6ccu) / 4u];
    else if (cpu->pc >= 0x8005d734u && cpu->pc < 0x8005d8a0u)
        instruction = kInputHandlerWords[(cpu->pc - 0x8005d734u) / 4u];
    else if (cpu->pc >= 0x8005d8a0u && cpu->pc < 0x8005d8b4u)
        instruction = kInputHandlerClear8005D8A0Words[(cpu->pc - 0x8005d8a0u) / 4u];
    else if (cpu->pc >= 0x8005d980u && cpu->pc < 0x8005d9c4u)
        instruction = kInputStop8005D980Words[(cpu->pc - 0x8005d980u) / 4u];
    else if (cpu->pc >= 0x8005d9c4u && cpu->pc < 0x8005dbd8u)
        instruction = kInputSerialStartWords[(cpu->pc - 0x8005d9c4u) / 4u];
    else if (cpu->pc >= 0x8005dbd8u && cpu->pc < 0x8005dca0u)
        instruction = kInputSerialNextWords[(cpu->pc - 0x8005dbd8u) / 4u];
    else if (cpu->pc >= 0x8005eae8u && cpu->pc < 0x8005eb28u)
        instruction = kInputSerialDispatchWords[(cpu->pc - 0x8005eae8u) / 4u];
    else if (cpu->pc >= 0x8005f75cu && cpu->pc < 0x8005f830u)
        instruction = kInputSerialPadWords[(cpu->pc - 0x8005f75cu) / 4u];
    else if (cpu->pc >= 0x8005dca0u && cpu->pc < 0x8005de78u)
        instruction = kInputSerialTransferWords[(cpu->pc - 0x8005dca0u) / 4u];
    else if (cpu->pc >= 0x8005e0acu && cpu->pc < 0x8005e13cu)
        instruction = kInputSerialIrqWords[(cpu->pc - 0x8005e0acu) / 4u];
    else if (cpu->pc >= 0x8005fba8u && cpu->pc < 0x8005fbc8u)
        instruction = kInputTimerStartWords[(cpu->pc - 0x8005fba8u) / 4u];
    else if (cpu->pc >= 0x8005fbc8u && cpu->pc < 0x8005fc68u)
        instruction = kInputTimerPollWords[(cpu->pc - 0x8005fbc8u) / 4u];
    else if (cpu->pc >= 0x8005f830u && cpu->pc < 0x8005fa94u)
        instruction = kInputResponseWords[(cpu->pc - 0x8005f830u) / 4u];
    else if (cpu->pc >= 0x8005fb70u && cpu->pc < 0x8005fb9cu)
        instruction = kInputResponseStatusWords[(cpu->pc - 0x8005fb70u) / 4u];
    else if (cpu->pc >= 0x8005e228u && cpu->pc < 0x8005e374u)
        instruction = kInputResponseModeWords[(cpu->pc - 0x8005e228u) / 4u];
    else if (cpu->pc >= 0x8005e374u && cpu->pc < 0x8005e3acu)
        instruction = kInputResponse8005E374Words[(cpu->pc - 0x8005e374u) / 4u];
    else if (cpu->pc >= 0x8005e3acu && cpu->pc < 0x8005e79cu)
        instruction = kInputResponse8005E3ACWords[(cpu->pc - 0x8005e3acu) / 4u];
    else if (cpu->pc >= 0x8005f384u && cpu->pc < 0x8005f394u)
        instruction = kInputResponseClearWords[(cpu->pc - 0x8005f384u) / 4u];
    else if (cpu->pc >= EVENT_REGISTER && cpu->pc < EVENT_REGISTER + sizeof(kEventRegisterWords))
        instruction = kEventRegisterWords[(cpu->pc - EVENT_REGISTER) / 4u];
    else if (cpu->pc >= 0x80061b58u && cpu->pc < 0x80061b58u + sizeof(kEventTestWords))
        instruction = kEventTestWords[(cpu->pc - 0x80061b58u) / 4u];
    else if (cpu->pc >= 0x800617ccu && cpu->pc < 0x8006186cu)
        instruction = kEventCallbackWords[(cpu->pc - 0x800617ccu) / 20u]
                                        [((cpu->pc - 0x800617ccu) % 20u) / 4u];
    else if (cpu->pc >= FORMATTER_ENTRY && cpu->pc < FORMATTER_END)
        instruction = kFormatter8005C640Words[(cpu->pc - FORMATTER_ENTRY) / 4u];
    else if (cpu->pc >= FORMATTER_WRAPPER_ENTRY && cpu->pc < FORMATTER_WRAPPER_END)
        instruction = kFormatter8005C604Words[(cpu->pc - FORMATTER_WRAPPER_ENTRY) / 4u];
    else if (cpu->pc >= RESETGRAPH_ENTRY && cpu->pc < RESETGRAPH_END)
        instruction = kResetGraph80059234Words[(cpu->pc - RESETGRAPH_ENTRY) / 4u];
    else if (cpu->pc >= CALLBACK_WRAPPER_ENTRY && cpu->pc < CALLBACK_WRAPPER_END)
        instruction = kCallbackWrapper80042580Words[(cpu->pc - CALLBACK_WRAPPER_ENTRY) / 4u];
    else if (cpu->pc >= CALLBACK_DISPATCH_ENTRY && cpu->pc < CALLBACK_DISPATCH_END)
        instruction = kCallbackDispatch80042644Words[(cpu->pc - CALLBACK_DISPATCH_ENTRY) / 4u];
    else if (cpu->pc >= CALLBACK_INITIALIZER && cpu->pc < CALLBACK_INITIALIZER_END)
        instruction = kCallbackInitializer80042718Words[(cpu->pc - CALLBACK_INITIALIZER) / 4u];
    else if (cpu->pc >= CALLBACK_INSTALLER_ENTRY && cpu->pc < CALLBACK_INSTALLER_END)
        instruction = kCallbackInstaller80042C90Words[(cpu->pc - CALLBACK_INSTALLER_ENTRY) / 4u];
    else if (cpu->pc >= CALLBACK_SLOT_WRITE_ENTRY && cpu->pc < CALLBACK_SLOT_WRITE_END)
        instruction = kCallbackSlotWrite80042D60Words[(cpu->pc - CALLBACK_SLOT_WRITE_ENTRY) / 4u];
    else if (cpu->pc >= CALLBACK_CHANNEL_INSTALLER_ENTRY &&
             cpu->pc < CALLBACK_CHANNEL_INSTALLER_END)
        instruction = kCallbackChannelInstaller80042DB8Words[
            (cpu->pc - CALLBACK_CHANNEL_INSTALLER_ENTRY) / 4u];
    else if (cpu->pc >= SAVED_CONTEXT_ENTRY && cpu->pc < SAVED_CONTEXT_END)
        instruction = kSavedContext8005CD98Words[(cpu->pc - SAVED_CONTEXT_ENTRY) / 4u];
    else if (cpu->pc >= STARTUP_ENTRY && cpu->pc < STARTUP_END)
        instruction = kStartup800141F0Words[(cpu->pc - STARTUP_ENTRY) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_RESETGRAPH && cpu->pc < STARTUP_MODE_END)
        instruction = kStartupMode800594CCWords[(cpu->pc - STARTUP_AFTER_RESETGRAPH) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_MODE && cpu->pc < STARTUP_GRAPHICS_END)
        instruction = kStartupGraphics80059658Words[(cpu->pc - STARTUP_AFTER_MODE) / 4u];
    else if (cpu->pc >= STARTUP_FINAL_INIT && cpu->pc < STARTUP_FINAL_INIT_END)
        instruction = kFinalInit800142C8Words[(cpu->pc - STARTUP_FINAL_INIT) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_RECORD_CLEAR &&
             cpu->pc < STARTUP_AFTER_RECORD_CLEAR_END)
        instruction = kPostRecordClear80018FC8Words[
            (cpu->pc - STARTUP_AFTER_RECORD_CLEAR) / 4u];
    else if (cpu->pc >= STARTUP_RECORD_SETUP && cpu->pc < STARTUP_RECORD_SETUP_END)
        instruction = kStartupRecordSetup80018918Words[
            (cpu->pc - STARTUP_RECORD_SETUP) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_POST_RECORD_CLEAR &&
             cpu->pc < STARTUP_AFTER_POST_RECORD_CLEAR_END)
        instruction = kStartupGlobalReset8001B324Words[
            (cpu->pc - STARTUP_AFTER_POST_RECORD_CLEAR) / 4u];
    else if (cpu->pc >= STARTUP_GLOBAL_RESET_LEAF &&
             cpu->pc < STARTUP_GLOBAL_RESET_LEAF_END)
        instruction = kStartupGlobalResetLeaf8001B34CWords[
            (cpu->pc - STARTUP_GLOBAL_RESET_LEAF) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_GLOBAL_RESET &&
             cpu->pc < STARTUP_SELECTOR_2C_END)
        instruction = kStartupSelector2C80028FDCWords[
            (cpu->pc - STARTUP_AFTER_GLOBAL_RESET) / 4u];
    else if (cpu->pc >= STARTUP_SELECTOR_2D && cpu->pc < STARTUP_SELECTOR_2D_END)
        instruction = kStartupSelector2D80029020Words[
            (cpu->pc - STARTUP_SELECTOR_2D) / 4u];
    else if (cpu->pc >= STARTUP_SELECTOR_STORE && cpu->pc < STARTUP_SELECTOR_STORE_END)
        instruction = kStartupSelectorStore800291A0Words[
            (cpu->pc - STARTUP_SELECTOR_STORE) / 4u];
    else if (cpu->pc >= STARTUP_AFTER_SELECTOR_STORES && cpu->pc < STARTUP_BIT_0C_END)
        instruction = kStartupBit0C80028DBCWords[
            (cpu->pc - STARTUP_AFTER_SELECTOR_STORES) / 4u];
    else if (cpu->pc >= STARTUP_BIT_0D && cpu->pc < STARTUP_BIT_0D_END)
        instruction = kStartupBit0D80028E00Words[(cpu->pc - STARTUP_BIT_0D) / 4u];
    else if (cpu->pc >= STARTUP_BIT_STORE && cpu->pc < STARTUP_BIT_STORE_END)
        instruction = kStartupBitStore80029124Words[(cpu->pc - STARTUP_BIT_STORE) / 4u];
    else if (cpu->pc >= CD_START && cpu->pc < CD_START_END)
        instruction = kCdStart8005FC68Words[(cpu->pc - CD_START) / 4u];
    else if (cpu->pc >= CD_INIT && cpu->pc < CD_INIT_END)
        instruction = kCdInit8006186CWords[(cpu->pc - CD_INIT) / 4u];
    else if (cpu->pc >= CD_INIT_A && cpu->pc < CD_INIT_A_END)
        instruction = kCdInitA800622D0Words[(cpu->pc - CD_INIT_A) / 4u];
    else if (cpu->pc >= CD_INIT_B && cpu->pc < CD_INIT_B_END)
        instruction = kCdInitB80062328Words[(cpu->pc - CD_INIT_B) / 4u];
    else if (cpu->pc >= CD_CALLBACK && cpu->pc < CD_CALLBACK_END)
        instruction = kCdCallback80062394Words[(cpu->pc - CD_CALLBACK) / 4u];
    else if (cpu->pc >= EVENT_START && cpu->pc < EVENT_START_END)
        instruction = kEventStart8005FCB8Words[(cpu->pc - EVENT_START) / 4u];
    else if (cpu->pc >= EVENT_RESET && cpu->pc < EVENT_RESET_END)
        instruction = kEventReset80062888Words[(cpu->pc - EVENT_RESET) / 4u];
    else if (cpu->pc >= STARTUP_ALLOCATOR_PREFIX &&
             cpu->pc < STARTUP_ALLOCATOR_PREFIX_END)
        instruction = kStartupAllocatorPrefix8005F0C8Words[
            (cpu->pc - STARTUP_ALLOCATOR_PREFIX) / 4u];
    else if (cpu->pc >= STARTUP_CALLBACK_TABLE && cpu->pc < STARTUP_CALLBACK_TABLE_END)
        instruction = kStartupCallbackTable8005F728Words[
            (cpu->pc - STARTUP_CALLBACK_TABLE) / 4u];
    else if (cpu->pc >= STARTUP_GUARDED_CLEAR && cpu->pc < STARTUP_GUARDED_CLEAR_END)
        instruction = kGuardedClear8005C2C8Words[(cpu->pc - STARTUP_GUARDED_CLEAR) / 4u];
    else if (cpu->pc >= STARTUP_TABLE_INIT && cpu->pc < STARTUP_TABLE_INIT_END)
        instruction = kStartupTableInit8005D6A0Words[(cpu->pc - STARTUP_TABLE_INIT) / 4u];
    else if (cpu->pc >= INPUT_STARTUP_WRAPPER && cpu->pc < INPUT_STARTUP_WRAPPER_END)
        instruction = kInputStartupWrapper8005D0F8Words[
            (cpu->pc - INPUT_STARTUP_WRAPPER) / 4u];
    else if (cpu->pc >= INPUT_STARTUP_PREFIX && cpu->pc < INPUT_STARTUP_PREFIX_END)
        instruction = kInputStartupPrefix8005D8B4Words[(cpu->pc - INPUT_STARTUP_PREFIX) / 4u];
    else if (cpu->pc >= INPUT_RECORD_CALLBACK && cpu->pc < INPUT_RECORD_CALLBACK_END)
        instruction = kInputRecordCallback8005F228Words[
            (cpu->pc - INPUT_RECORD_CALLBACK) / 4u];
    else if (cpu->pc >= STARTUP_RETRY && cpu->pc < STARTUP_RETRY_END)
        instruction = kStartupRetry80043450Words[(cpu->pc - STARTUP_RETRY) / 4u];
    else if (cpu->pc >= STARTUP_RETRY_ALTERNATE &&
             cpu->pc < STARTUP_RETRY_ALTERNATE_END)
        instruction = kStartupRetryAlternate80044BF4Words[
            (cpu->pc - STARTUP_RETRY_ALTERNATE) / 4u];
    else if (cpu->pc >= STARTUP_DISPATCH_SUCCESS &&
             cpu->pc < STARTUP_CALLBACK_SETTER_END)
        instruction = kStartupCallbackSetter8004359CWords[
            (cpu->pc - STARTUP_DISPATCH_SUCCESS) / 4u];
    else if (cpu->pc >= STARTUP_CALLBACK_SETTER_B &&
             cpu->pc < STARTUP_CALLBACK_SETTER_B_END)
        instruction = kStartupCallbackSetter800435B4Words[
            (cpu->pc - STARTUP_CALLBACK_SETTER_B) / 4u];
    else if (cpu->pc >= STARTUP_CALLBACK_SETTER_C &&
             cpu->pc < STARTUP_CALLBACK_SETTER_C_END)
        instruction = kStartupCallbackSetter8004654CWords[
            (cpu->pc - STARTUP_CALLBACK_SETTER_C) / 4u];
    else if (cpu->pc >= STARTUP_CALLBACK_CONTROL &&
             cpu->pc < STARTUP_CALLBACK_CONTROL_END)
        instruction = kStartupCallbackControl80046564Words[
            (cpu->pc - STARTUP_CALLBACK_CONTROL) / 4u];
    else if (cpu->pc >= STARTUP_RETRY_PROBE && cpu->pc < CD_INITIALIZER_END)
        instruction = kCdInitializer80044D38Words[
            (cpu->pc - STARTUP_RETRY_PROBE) / 4u];
    else if (cpu->pc >= CD_INITIALIZER_COMMAND && cpu->pc < CD_COMMAND_PREFIX_END)
        instruction = kCdCommandPrefix80044670Words[
            (cpu->pc - CD_INITIALIZER_COMMAND) / 4u];
    else if (cpu->pc >= CD_COMMAND_CONTINUATION &&
             cpu->pc < CD_COMMAND_CONTINUATION_END)
        instruction = kCdCommandContinuation800446D4Words[
            (cpu->pc - CD_COMMAND_CONTINUATION) / 4u];
    else if (cpu->pc >= CD_COMMAND_CONTINUATION_END && cpu->pc < CD_COMMAND_END)
        instruction = kCdCommandFullWords[(cpu->pc - CD_INITIALIZER_COMMAND) / 4u];
    else if (cpu->pc >= 0x80019a24u && cpu->pc < 0x80019af8u)
        instruction = kFile80019A24Words[(cpu->pc - 0x80019a24u) / 4u];
    else if (cpu->pc >= 0x80034b98u && cpu->pc < 0x80034c24u)
        instruction = kFile80034B98Words[(cpu->pc - 0x80034b98u) / 4u];
    else if (cpu->pc >= 0x80019af8u && cpu->pc < 0x8001a0fcu)
        instruction = kFile80019AF8Words[(cpu->pc - 0x80019af8u) / 4u];
    else if (cpu->pc >= 0x8001a338u && cpu->pc < 0x8001a9d8u && cpu->cd_irq_frame)
        instruction = kFile8001A338Words[(cpu->pc - 0x8001a338u) / 4u];
    else if (cpu->pc >= 0x8004355cu && cpu->pc < 0x8004357cu)
        instruction = kFile8004355CWords[(cpu->pc - 0x8004355cu) / 4u];
    else if (cpu->pc >= 0x8004239cu && cpu->pc < 0x80042404u)
        instruction = kFile8004239CWords[(cpu->pc - 0x8004239cu) / 4u];
    else if (cpu->pc >= 0x80042404u && cpu->pc < 0x800424e4u)
        instruction = kFile80042404Words[(cpu->pc - 0x80042404u) / 4u];
    else if (cpu->pc >= 0x800424e4u && cpu->pc < 0x80042580u)
        instruction = kFile800424E4Words[(cpu->pc - 0x800424e4u) / 4u];
    else if (cpu->pc >= 0x80044dbcu && cpu->pc < 0x80044f24u)
        instruction = kFile80044DBCWords[(cpu->pc - 0x80044dbcu) / 4u];
    else if (cpu->pc >= STATUS_FIRST_POLL && cpu->pc < STATUS_FIRST_POLL_END)
        instruction = kStatusFirstPoll80044124Words[
            (cpu->pc - STATUS_FIRST_POLL) / 4u];
    else if (cpu->pc >= STATUS_TIMEOUT && cpu->pc < STATUS_TIMEOUT_END)
        instruction = kStatusTimeout80044198Words[(cpu->pc - STATUS_TIMEOUT) / 4u];
    else if (cpu->pc >= STATUS_TIMEOUT_DIAGNOSTIC && cpu->pc < STATUS_DIAGNOSTIC_END)
        instruction = kStatusDiagnostic800441D8Words[
            (cpu->pc - STATUS_TIMEOUT_DIAGNOSTIC) / 4u];
    else if (cpu->pc == STATUS_TIMEOUT_CONTINUE)
        instruction = 0x00001021u; /* 8004424C: addu v0, zero, zero. */
    else if (cpu->pc >= STATUS_POST_DIAGNOSTIC && cpu->pc < STATUS_LOOP_END)
        instruction = kStatusLoop80044250Words[(cpu->pc - STATUS_POST_DIAGNOSTIC) / 4u];
    else if (cpu->pc >= 0x8002c8f4u && cpu->pc < 0x8002cc4cu)
        instruction = kSpu8002C8F4Words[(cpu->pc - 0x8002c8f4u) / 4u];
    else if (cpu->pc >= 0x8003a424u && cpu->pc < 0x8003a444u)
        instruction = kSpu8003A424Words[(cpu->pc - 0x8003a424u) / 4u];
    else if (cpu->pc >= 0x8003a444u && cpu->pc < 0x8003a53cu)
        instruction = kSpu8003A444Words[(cpu->pc - 0x8003a444u) / 4u];
    else if (cpu->pc >= 0x8003a53cu && cpu->pc < 0x8003a5b8u)
        instruction = kSpu8003A53CWords[(cpu->pc - 0x8003a53cu) / 4u];
    else if (cpu->pc >= 0x8003a5b8u && cpu->pc < 0x8003a84cu)
        instruction = kSpu8003A5B8Words[(cpu->pc - 0x8003a5b8u) / 4u];
    else if (cpu->pc >= 0x8003a84cu && cpu->pc < 0x8003aa18u)
        instruction = kSpu8003A84CWords[(cpu->pc - 0x8003a84cu) / 4u];
    else if (cpu->pc >= 0x8003af04u && cpu->pc < 0x8003af4cu)
        instruction = kSpu8003AF04Words[(cpu->pc - 0x8003af04u) / 4u];
    else if (cpu->pc >= 0x8003b0e4u && cpu->pc < 0x8003b14cu)
        instruction = kSpu8003B0E4Words[(cpu->pc - 0x8003b0e4u) / 4u];
    else if (cpu->pc >= 0x8003b14cu && cpu->pc < 0x8003b170u)
        instruction = kSpu8003B14CWords[(cpu->pc - 0x8003b14cu) / 4u];
    else if (cpu->pc >= 0x8003be24u && cpu->pc < 0x8003be74u)
        instruction = kSpu8003BE24Words[(cpu->pc - 0x8003be24u) / 4u];
    else if (cpu->pc >= 0x8003b3d0u && cpu->pc < 0x8003b45cu)
        instruction = kSpu8003B3D0Words[(cpu->pc - 0x8003b3d0u) / 4u];
    else if (cpu->pc >= 0x8002d1f0u && cpu->pc < 0x8002d240u)
        instruction = kSpu8002D1F0Words[(cpu->pc - 0x8002d1f0u) / 4u];
    else if (cpu->pc >= 0x8003b45cu && cpu->pc < 0x8003b954u)
        instruction = kSpu8003B45CWords[(cpu->pc - 0x8003b45cu) / 4u];
    else if (cpu->pc >= 0x8003b954u && cpu->pc < 0x8003be24u)
        instruction = kSpu8003B954Words[(cpu->pc - 0x8003b954u) / 4u];
    else if (cpu->pc >= 0x8003b280u && cpu->pc < 0x8003b350u)
        instruction = kSpu8003B280Words[(cpu->pc - 0x8003b280u) / 4u];
    else if (cpu->pc >= 0x8001971cu && cpu->pc < 0x80019930u)
        instruction = kFile8001971CWords[(cpu->pc - 0x8001971cu) / 4u];
    else if (cpu->pc >= 0x80019990u && cpu->pc < 0x80019a10u)
        instruction = kFile80019990Words[(cpu->pc - 0x80019990u) / 4u];
    else if (cpu->pc >= 0x80045374u && cpu->pc < 0x80045640u)
        instruction = kFile80045374Words[(cpu->pc - 0x80045374u) / 4u];
    else if (cpu->pc >= 0x80045640u && cpu->pc < 0x80045660u)
        instruction = kFile80045640Words[(cpu->pc - 0x80045640u) / 4u];
    else if (cpu->pc >= 0x80045660u && cpu->pc < 0x80045940u)
        instruction = kFile80045660Words[(cpu->pc - 0x80045660u) / 4u];
    else if (cpu->pc >= 0x80045940u && cpu->pc < 0x800459e8u)
        instruction = kFile80045940Words[(cpu->pc - 0x80045940u) / 4u];
    else if (cpu->pc >= 0x800459e8u && cpu->pc < 0x80045c94u)
        instruction = kFile800459E8Words[(cpu->pc - 0x800459e8u) / 4u];
    else if (cpu->pc >= 0x80045c94u && cpu->pc < 0x80045d00u)
        instruction = kFile80045C94Words[(cpu->pc - 0x80045c94u) / 4u];
    else if (cpu->pc >= 0x80043a18u && cpu->pc < 0x80043b1cu)
        instruction = kFile80043A18Words[(cpu->pc - 0x80043a18u) / 4u];
    else if (cpu->pc >= 0x80043398u && cpu->pc < 0x800433c0u)
        instruction = kFile80043398Words[(cpu->pc - 0x80043398u) / 4u];
    else if (cpu->pc >= 0x800433c0u && cpu->pc < 0x800433e8u)
        instruction = kFile800433C0Words[(cpu->pc - 0x800433c0u) / 4u];
    else if (cpu->pc >= 0x800433e8u && cpu->pc < 0x80043410u)
        instruction = kFile800433E8Words[(cpu->pc - 0x800433e8u) / 4u];
    else if (cpu->pc >= 0x80043410u && cpu->pc < 0x80043420u)
        instruction = kFile80043410Words[(cpu->pc - 0x80043410u) / 4u];
    else if (cpu->pc >= 0x800435ccu && cpu->pc < 0x80043704u)
        instruction = kFile800435CCWords[(cpu->pc - 0x800435ccu) / 4u];
    else if (cpu->pc >= 0x80043704u && cpu->pc < 0x80043830u)
        instruction = kFile80043704Words[(cpu->pc - 0x80043704u) / 4u];
    else if (cpu->pc >= 0x80043994u && cpu->pc < 0x800439b4u)
        instruction = kFile80043994Words[(cpu->pc - 0x80043994u) / 4u];
    else if (cpu->pc >= 0x80043b1cu && cpu->pc < 0x80043b9cu)
        instruction = kFile80043B1CWords[(cpu->pc - 0x80043b1cu) / 4u];
    else if (cpu->pc >= 0x800443a4u && cpu->pc < 0x80044670u)
        instruction = kFile800443A4Words[(cpu->pc - 0x800443a4u) / 4u];
    else if (cpu->pc >= 0x80045090u && cpu->pc < 0x80045190u)
        instruction = kFile80045090Words[(cpu->pc - 0x80045090u) / 4u];
    else if (cpu->pc >= 0x80045d00u && cpu->pc < 0x80045fd0u)
        instruction = kFile80045D00Words[(cpu->pc - 0x80045d00u) / 4u];
    else if (cpu->pc >= 0x800460ccu && cpu->pc < 0x800462e0u)
        instruction = kFile800460CCWords[(cpu->pc - 0x800460ccu) / 4u];
    else if (cpu->pc >= 0x8004637cu && cpu->pc < 0x80046480u)
        instruction = kFile8004637CWords[(cpu->pc - 0x8004637cu) / 4u];
    else if (cpu->pc >= 0x80046480u && cpu->pc < 0x8004654cu)
        instruction = kFile80046480Words[(cpu->pc - 0x80046480u) / 4u];
    else if (cpu->pc >= 0x8005c324u && cpu->pc < 0x8005c358u)
        instruction = kFile8005C324Words[(cpu->pc - 0x8005c324u) / 4u];
    else if (cpu->pc >= 0x8005c358u && cpu->pc < 0x8005c388u)
        instruction = kFile8005C358Words[(cpu->pc - 0x8005c358u) / 4u];
    else if (cpu->pc >= 0x8005c4dcu && cpu->pc < 0x8005c540u)
        instruction = kFile8005C4DCWords[(cpu->pc - 0x8005c4dcu) / 4u];
    else if (cpu->pc >= 0x8005c584u && cpu->pc < 0x8005c604u)
        instruction = kFile8005C584Words[(cpu->pc - 0x8005c584u) / 4u];
    else if (cpu->pc >= 0x8005ce68u && cpu->pc < 0x8005ce74u)
        instruction = kFile8005CE68Words[(cpu->pc - 0x8005ce68u) / 4u];
    else if (cpu->pc >= 0x8005cea8u && cpu->pc < 0x8005ceb4u)
        instruction = kFile8005CEA8Words[(cpu->pc - 0x8005cea8u) / 4u];
    else if (cpu->pc >= 0x80043420u && cpu->pc < 0x80043430u)
        instruction = kFile80043420Words[(cpu->pc - 0x80043420u) / 4u];
    else if (cpu->pc >= 0x80043440u && cpu->pc < 0x80043450u)
        instruction = kFile80043440Words[(cpu->pc - 0x80043440u) / 4u];
    else if (cpu->pc >= 0x8004357cu && cpu->pc < 0x8004359cu)
        instruction = kFile8004357CWords[(cpu->pc - 0x8004357cu) / 4u];
    else if (cpu->pc >= 0x80037d98u && cpu->pc < 0x80037ea0u)
        instruction = kSpu80037D98Words[(cpu->pc - 0x80037d98u) / 4u];
    else if (cpu->pc >= 0x8003d424u && cpu->pc < 0x8003d434u)
        instruction = kSpu8003D424Words[(cpu->pc - 0x8003d424u) / 4u];
    else if (cpu->pc >= 0x8002cc4cu && cpu->pc < 0x8002ccb4u)
        instruction = kSpu8002CC4CWords[(cpu->pc - 0x8002cc4cu) / 4u];
    else if (cpu->pc >= 0x8002fae0u && cpu->pc < 0x8002fb08u)
        instruction = kSpu8002FAE0Words[(cpu->pc - 0x8002fae0u) / 4u];
    else if (cpu->pc >= 0x8002c8bcu && cpu->pc < 0x8002c8f4u)
        instruction = kSpu8002C8BCWords[(cpu->pc - 0x8002c8bcu) / 4u];
    else if (cpu->pc >= 0x80037cc8u && cpu->pc < 0x80037cd8u)
        instruction = kSpu80037CC8Words[(cpu->pc - 0x80037cc8u) / 4u];
    else if (cpu->pc >= 0x8003be74u && cpu->pc < 0x8003be98u)
        instruction = kSpu8003BE74Words[(cpu->pc - 0x8003be74u) / 4u];
    else if (cpu->pc >= 0x8003be98u && cpu->pc < 0x8003c0a0u)
        instruction = kSpu8003BE98Words[(cpu->pc - 0x8003be98u) / 4u];
    else if (cpu->pc >= 0x8003b1ecu && cpu->pc < 0x8003b250u)
        instruction = kSpu8003B1ECWords[(cpu->pc - 0x8003b1ecu) / 4u];
    else if (cpu->pc >= 0x80034c24u && cpu->pc < 0x80034cf0u)
        instruction = kSpu80034C24Words[(cpu->pc - 0x80034c24u) / 4u];
    else if (cpu->pc >= 0x800430b8u && cpu->pc < 0x800430dcu)
        instruction = kSpu800430B8Words[(cpu->pc - 0x800430b8u) / 4u];
    else if (cpu->pc >= 0x800430dcu && cpu->pc < 0x80043300u)
        instruction = kSpu800430DCWords[(cpu->pc - 0x800430dcu) / 4u];
    else if (cpu->pc >= 0x80043830u && cpu->pc < 0x80043974u)
        instruction = kSpu80043830Words[(cpu->pc - 0x80043830u) / 4u];
    else if (cpu->pc >= 0x80037004u && cpu->pc < 0x80037028u)
        instruction = kSpu80037004Words[(cpu->pc - 0x80037004u) / 4u];
    else if (cpu->pc >= 0x8003c598u && cpu->pc < 0x8003c92cu)
        instruction = kSpu8003C598Words[(cpu->pc - 0x8003c598u) / 4u];
    else if (cpu->pc >= 0x8003d518u && cpu->pc < 0x8003d548u)
        instruction = kSpu8003D518Words[(cpu->pc - 0x8003d518u) / 4u];
    else if (cpu->pc >= 0x8003d548u && cpu->pc < 0x8003d630u)
        instruction = kSpu8003D548Words[(cpu->pc - 0x8003d548u) / 4u];
    else if (cpu->pc >= 0x8003fe3cu && cpu->pc < 0x8004014cu)
        instruction = kSpu8003FE3CWords[(cpu->pc - 0x8003fe3cu) / 4u];
    else if (cpu->pc >= 0x8004014cu && cpu->pc < 0x800401a0u)
        instruction = kSpu8004014CWords[(cpu->pc - 0x8004014cu) / 4u];
    else if (cpu->pc >= 0x800401a0u && cpu->pc < 0x800401ccu)
        instruction = kSpu800401A0Words[(cpu->pc - 0x800401a0u) / 4u];
    else if (cpu->pc >= 0x80040868u && cpu->pc < 0x80040938u)
        instruction = kSpu80040868Words[(cpu->pc - 0x80040868u) / 4u];
    else if (cpu->pc >= 0x8003fa64u && cpu->pc < 0x8003fe18u)
        instruction = kSpu8003FA64Words[(cpu->pc - 0x8003fa64u) / 4u];
    else if (cpu->pc >= 0x800425e0u && cpu->pc < 0x80042610u)
        instruction = kSpu800425E0Words[(cpu->pc - 0x800425e0u) / 4u];
    else if (cpu->pc >= 0x80042f8cu && cpu->pc < 0x80043034u)
        instruction = kSpu80042F8CWords[(cpu->pc - 0x80042f8cu) / 4u];
    else if (cpu->pc >= STATUS_READY_QUERY && cpu->pc < STATUS_READY_QUERY + 16u)
        instruction = kReadyQuery800426D4Words[(cpu->pc - STATUS_READY_QUERY) / 4u];
    else if (cpu->pc >= STATUS_WORKER && cpu->pc < STATUS_WORKER_END)
        instruction = kStatusWorker80043B9CWords[(cpu->pc - STATUS_WORKER) / 4u];
    else if (cpu->pc >= 0x80045290u && cpu->pc < 0x80045374u)
        instruction = kCdIrq80045290Words[(cpu->pc - 0x80045290u) / 4u];
    else if (cpu->pc >= CD_STATE_RESET && cpu->pc < CD_STATE_RESET_END)
        instruction = kCdStateReset80044B14Words[(cpu->pc - CD_STATE_RESET) / 4u];
    else if (cpu->pc >= CD_STATE_RESET_WRAPPER && cpu->pc < CD_STATE_RESET_WRAPPER_END)
        instruction = kCdStateResetWrapper800434BCWords[
            (cpu->pc - CD_STATE_RESET_WRAPPER) / 4u];
    else if (cpu->pc >= STARTUP_DISPATCH && cpu->pc < STARTUP_DISPATCH_END)
        instruction = kStartupDispatcher80043300Words[(cpu->pc - STARTUP_DISPATCH) / 4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800ceec8u && cpu->pc < 0x800cf104u)
        instruction = kOverlay0004_800CEEC8Words[(cpu->pc - 0x800ceec8u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d1e18u && cpu->pc < 0x800d1e9cu)
        instruction = kOverlay0004_800D1E18Words[(cpu->pc - 0x800d1e18u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cfb3cu && cpu->pc < 0x800cfc1cu)
        instruction = kOverlay0004_800CFB3CWords[(cpu->pc - 0x800cfb3cu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d1e9cu && cpu->pc < 0x800d2394u)
        instruction = kOverlay0004_800D1E9CWords[(cpu->pc - 0x800d1e9cu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2394u && cpu->pc < 0x800d2454u)
        instruction = kOverlay0004_800D2394Words[(cpu->pc - 0x800d2394u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2454u && cpu->pc < 0x800d24d0u)
        instruction = kOverlay0004_800D2454Words[(cpu->pc - 0x800d2454u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2aa0u && cpu->pc < 0x800d2ad8u)
        instruction = kOverlay0004_800D2AA0Words[(cpu->pc - 0x800d2aa0u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2d44u && cpu->pc < 0x800d2d68u)
        instruction = kOverlay0004_800D2D44Words[(cpu->pc - 0x800d2d44u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2a24u && cpu->pc < 0x800d2aa0u)
        instruction = kOverlay0004_800D2A24Words[(cpu->pc - 0x800d2a24u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2704u && cpu->pc < 0x800d27a0u)
        instruction = kOverlay0004_800D2704Words[(cpu->pc - 0x800d2704u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d298cu && cpu->pc < 0x800d2a24u)
        instruction = kOverlay0004_800D298CWords[(cpu->pc - 0x800d298cu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2c0cu && cpu->pc < 0x800d2c88u)
        instruction = kOverlay0004_800D2C0CWords[(cpu->pc - 0x800d2c0cu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2c88u && cpu->pc < 0x800d2ca8u)
        instruction = kOverlay0004_800D2C88Words[(cpu->pc - 0x800d2c88u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d24d0u && cpu->pc < 0x800d2704u)
        instruction = kOverlay0004_800D24D0Words[(cpu->pc - 0x800d24d0u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2d68u && cpu->pc < 0x800d2e64u)
        instruction = kOverlay0004_800D2D68Words[(cpu->pc - 0x800d2d68u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d27a0u && cpu->pc < 0x800d298cu)
        instruction = kOverlay0004_800D27A0Words[(cpu->pc - 0x800d27a0u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d3234u && cpu->pc < 0x800d3540u)
        instruction = kOverlay0004_800D3234Words[(cpu->pc - 0x800d3234u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2e64u && cpu->pc < 0x800d2ef8u)
        instruction = kOverlay0004_800D2E64Words[(cpu->pc - 0x800d2e64u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2ef8u && cpu->pc < 0x800d2f88u)
        instruction = kOverlay0004_800D2EF8Words[(cpu->pc - 0x800d2ef8u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d2f88u && cpu->pc < 0x800d3020u)
        instruction = kOverlay0004_800D2F88Words[(cpu->pc - 0x800d2f88u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d3020u && cpu->pc < 0x800d30b8u)
        instruction = kOverlay0004_800D3020Words[(cpu->pc - 0x800d3020u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800d30d0u && cpu->pc < 0x800d3200u)
        instruction = kOverlay0004_800D30D0Words[(cpu->pc - 0x800d30d0u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cffecu && cpu->pc < 0x800d0100u)
        instruction = kOverlay0004_800CFFECWords[(cpu->pc - 0x800cffecu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cf3e8u && cpu->pc < 0x800cfb3cu)
        instruction = kOverlay0004_800CF3E8Words[(cpu->pc - 0x800cf3e8u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cfc1cu && cpu->pc < 0x800cfe00u)
        instruction = kOverlay0004_800CFC1CWords[(cpu->pc - 0x800cfc1cu)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cf3a4u && cpu->pc < 0x800cf3e8u)
        instruction = kOverlay0004_800CF3A4Words[(cpu->pc - 0x800cf3a4u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cf370u && cpu->pc < 0x800cf3a4u)
        instruction = kOverlay0004_800CF370Words[(cpu->pc - 0x800cf370u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cf300u && cpu->pc < 0x800cf370u)
        instruction = kOverlay0004_800CF300Words[(cpu->pc - 0x800cf300u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cf104u && cpu->pc < 0x800cf300u)
        instruction = kOverlay0004_800CF104Words[(cpu->pc - 0x800cf104u)/4u];
    else if (g_overlay_0004_words &&
             cpu->pc >= 0x800cfe00u && cpu->pc < 0x800cfeb4u)
        instruction = kOverlay0004_800CFE00Words[(cpu->pc - 0x800cfe00u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cedfcu && cpu->pc < 0x800cf104u)
        instruction = kOverlay0010_800CEDFCWords[(cpu->pc - 0x800cedfcu) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cfbbcu && cpu->pc < 0x800cfbccu)
        instruction = kOverlay0010_800CFBBCWords[(cpu->pc - 0x800cfbbcu) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d0488u && cpu->pc < 0x800d0588u)
        instruction = kOverlay0010_800D0488Words[(cpu->pc - 0x800d0488u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf370u && cpu->pc < 0x800cf398u)
        instruction = kOverlay0010_800CF370Words[(cpu->pc - 0x800cf370u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf398u && cpu->pc < 0x800cf3b8u)
        instruction = kOverlay0010_800CF398Words[(cpu->pc - 0x800cf398u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf3b8u && cpu->pc < 0x800cf47cu)
        instruction = kOverlay0010_800CF3B8Words[(cpu->pc - 0x800cf3b8u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf47cu && cpu->pc < 0x800cf4d4u)
        instruction = kOverlay0010_800CF47CWords[(cpu->pc - 0x800cf47cu) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf4d4u && cpu->pc < 0x800cf804u)
        instruction = kOverlay0010_800CF4D4Words[(cpu->pc - 0x800cf4d4u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cfbf8u && cpu->pc < 0x800cfde8u)
        instruction = kOverlay0010_800CFBF8Words[(cpu->pc - 0x800cfbf8u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cfe60u && cpu->pc < 0x800d0214u)
        instruction = kOverlay0010_800CFE60Words[(cpu->pc - 0x800cfe60u) / 4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cf94cu && cpu->pc < 0x800cf990u)
        instruction = kOverlay0010_800CF94CWords[(cpu->pc - 0x800cf94cu) / 4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80128420u && cpu->pc < 0x801284b8u)
        instruction = kOverlaySc02_80128420Words[(cpu->pc - 0x80128420u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80129220u && cpu->pc < 0x80129248u)
        instruction = kOverlaySc02_80129220Words[(cpu->pc - 0x80129220u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80129248u && cpu->pc < 0x80129258u)
        instruction = kOverlaySc02_80129248Words[(cpu->pc - 0x80129248u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80129258u && cpu->pc < 0x8012927cu)
        instruction = kOverlaySc02_80129258Words[(cpu->pc - 0x80129258u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801378f0u && cpu->pc < 0x801379d8u)
        instruction = kOverlaySc02_801378F0Words[(cpu->pc - 0x801378f0u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013a860u && cpu->pc < 0x8013a8b0u)
        instruction = kOverlaySc02_8013A860Words[(cpu->pc - 0x8013a860u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80128c14u && cpu->pc < 0x80128c98u)
        instruction = kOverlaySc02_80128C14Words[(cpu->pc - 0x80128c14u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013c98cu && cpu->pc < 0x8013c9c4u)
        instruction = kOverlaySc02_8013C98CWords[(cpu->pc - 0x8013c98cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80129c40u && cpu->pc < 0x80129cf8u)
        instruction = kOverlaySc02_80129C40Words[(cpu->pc - 0x80129c40u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d05e8u && cpu->pc < 0x800d0630u)
        instruction = kOverlay0010_800D05E8Words[(cpu->pc - 0x800d05e8u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d0588u && cpu->pc < 0x800d05e8u)
        instruction = kOverlay0010_800D0588Words[(cpu->pc - 0x800d0588u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800cf854u && cpu->pc < 0x800cf864u)
        instruction = kOverlay0010_800CF854Words[(cpu->pc - 0x800cf854u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d1e20u && cpu->pc < 0x800d1e28u)
        instruction = kOverlay0010_800D1E20Words[(cpu->pc - 0x800d1e20u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d18dcu && cpu->pc < 0x800d1938u)
        instruction = kOverlay0010_800D18DCWords[(cpu->pc - 0x800d18dcu)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d1938u && cpu->pc < 0x800d1984u)
        instruction = kOverlay0010_800D1938Words[(cpu->pc - 0x800d1938u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d1984u && cpu->pc < 0x800d19dcu)
        instruction = kOverlay0010_800D1984Words[(cpu->pc - 0x800d1984u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d1f58u && cpu->pc < 0x800d1f90u)
        instruction = kOverlay0010_800D1F58Words[(cpu->pc - 0x800d1f58u)/4u];
    else if (g_overlay_0010_words && cpu->pc >= 0x800d02c0u && cpu->pc < 0x800d02d0u)
        instruction = kOverlay0010_800D02C0Words[(cpu->pc - 0x800d02c0u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d0630u && cpu->pc < 0x800d065cu)
        instruction = kOverlay0010_800D0630Words[(cpu->pc - 0x800d0630u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d065cu && cpu->pc < 0x800d0694u)
        instruction = kOverlay0010_800D065CWords[(cpu->pc - 0x800d065cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80145cecu && cpu->pc < 0x80145ee8u)
        instruction = kOverlaySc02_80145CECWords[(cpu->pc - 0x80145cecu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801552f4u && cpu->pc < 0x80155344u)
        instruction = kOverlaySc02_801552F4Words[(cpu->pc - 0x801552f4u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80147084u && cpu->pc < 0x8014708cu)
        instruction = kOverlaySc02_80147084Words[(cpu->pc - 0x80147084u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80147098u && cpu->pc < 0x801470a0u)
        instruction = kOverlaySc02_80147098Words[(cpu->pc - 0x80147098u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801470acu && cpu->pc < 0x801470b4u)
        instruction = kOverlaySc02_801470ACWords[(cpu->pc - 0x801470acu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80149210u && cpu->pc < 0x80149228u)
        instruction = kOverlaySc02_80149210Words[(cpu->pc - 0x80149210u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149228u && cpu->pc < 0x80149284u)
        instruction = kOverlaySc02_80149228Words[(cpu->pc - 0x80149228u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149284u && cpu->pc < 0x80149290u)
        instruction = kOverlaySc02_80149284Words[(cpu->pc - 0x80149284u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149290u && cpu->pc < 0x80149350u)
        instruction = kOverlaySc02_80149290Words[(cpu->pc - 0x80149290u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149350u && cpu->pc < 0x80149374u)
        instruction = kOverlaySc02_80149350Words[(cpu->pc - 0x80149350u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149374u && cpu->pc < 0x801493d0u)
        instruction = kOverlaySc02_80149374Words[(cpu->pc - 0x80149374u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801493d0u && cpu->pc < 0x8014942cu)
        instruction = kOverlaySc02_801493D0Words[(cpu->pc - 0x801493d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014942cu && cpu->pc < 0x80149450u)
        instruction = kOverlaySc02_8014942CWords[(cpu->pc - 0x8014942cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149450u && cpu->pc < 0x801494ccu)
        instruction = kOverlaySc02_80149450Words[(cpu->pc - 0x80149450u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801494ccu && cpu->pc < 0x80149544u)
        instruction = kOverlaySc02_801494CCWords[(cpu->pc - 0x801494ccu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149544u && cpu->pc < 0x80149584u)
        instruction = kOverlaySc02_80149544Words[(cpu->pc - 0x80149544u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149584u && cpu->pc < 0x801495c4u)
        instruction = kOverlaySc02_80149584Words[(cpu->pc - 0x80149584u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801495c4u && cpu->pc < 0x8014964cu)
        instruction = kOverlaySc02_801495C4Words[(cpu->pc - 0x801495c4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014964cu && cpu->pc < 0x801496d4u)
        instruction = kOverlaySc02_8014964CWords[(cpu->pc - 0x8014964cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801496d4u && cpu->pc < 0x80149704u)
        instruction = kOverlaySc02_801496D4Words[(cpu->pc - 0x801496d4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149704u && cpu->pc < 0x80149724u)
        instruction = kOverlaySc02_80149704Words[(cpu->pc - 0x80149704u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149724u && cpu->pc < 0x80149744u)
        instruction = kOverlaySc02_80149724Words[(cpu->pc - 0x80149724u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149744u && cpu->pc < 0x80149788u)
        instruction = kOverlaySc02_80149744Words[(cpu->pc - 0x80149744u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149788u && cpu->pc < 0x801497a8u)
        instruction = kOverlaySc02_80149788Words[(cpu->pc - 0x80149788u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801497a8u && cpu->pc < 0x80149864u)
        instruction = kOverlaySc02_801497A8Words[(cpu->pc - 0x801497a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149864u && cpu->pc < 0x80149884u)
        instruction = kOverlaySc02_80149864Words[(cpu->pc - 0x80149864u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149884u && cpu->pc < 0x801498c0u)
        instruction = kOverlaySc02_80149884Words[(cpu->pc - 0x80149884u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801498c0u && cpu->pc < 0x801498e0u)
        instruction = kOverlaySc02_801498C0Words[(cpu->pc - 0x801498c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801498e0u && cpu->pc < 0x80149954u)
        instruction = kOverlaySc02_801498E0Words[(cpu->pc - 0x801498e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149954u && cpu->pc < 0x80149a64u)
        instruction = kOverlaySc02_80149954Words[(cpu->pc - 0x80149954u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149a64u && cpu->pc < 0x80149aa8u)
        instruction = kOverlaySc02_80149A64Words[(cpu->pc - 0x80149a64u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149aa8u && cpu->pc < 0x80149ad4u)
        instruction = kOverlaySc02_80149AA8Words[(cpu->pc - 0x80149aa8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149ad4u && cpu->pc < 0x80149b14u)
        instruction = kOverlaySc02_80149AD4Words[(cpu->pc - 0x80149ad4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149b14u && cpu->pc < 0x80149b54u)
        instruction = kOverlaySc02_80149B14Words[(cpu->pc - 0x80149b14u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149b54u && cpu->pc < 0x80149bacu)
        instruction = kOverlaySc02_80149B54Words[(cpu->pc - 0x80149b54u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149bacu && cpu->pc < 0x80149becu)
        instruction = kOverlaySc02_80149BACWords[(cpu->pc - 0x80149bacu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149becu && cpu->pc < 0x80149c08u)
        instruction = kOverlaySc02_80149BECWords[(cpu->pc - 0x80149becu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149c08u && cpu->pc < 0x80149c94u)
        instruction = kOverlaySc02_80149C08Words[(cpu->pc - 0x80149c08u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149c94u && cpu->pc < 0x80149cb4u)
        instruction = kOverlaySc02_80149C94Words[(cpu->pc - 0x80149c94u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149cb4u && cpu->pc < 0x80149cd4u)
        instruction = kOverlaySc02_80149CB4Words[(cpu->pc - 0x80149cb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149cd4u && cpu->pc < 0x80149d10u)
        instruction = kOverlaySc02_80149CD4Words[(cpu->pc - 0x80149cd4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149d10u && cpu->pc < 0x80149d9cu)
        instruction = kOverlaySc02_80149D10Words[(cpu->pc - 0x80149d10u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149d9cu && cpu->pc < 0x80149dd8u)
        instruction = kOverlaySc02_80149D9CWords[(cpu->pc - 0x80149d9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149dd8u && cpu->pc < 0x80149e94u)
        instruction = kOverlaySc02_80149DD8Words[(cpu->pc - 0x80149dd8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149e94u && cpu->pc < 0x80149f2cu)
        instruction = kOverlaySc02_80149E94Words[(cpu->pc - 0x80149e94u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149f2cu && cpu->pc < 0x80149fa8u)
        instruction = kOverlaySc02_80149F2CWords[(cpu->pc - 0x80149f2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149fa8u && cpu->pc < 0x80149fb0u)
        instruction = kOverlaySc02_80149FA8Words[(cpu->pc - 0x80149fa8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149fb0u && cpu->pc < 0x8014a048u)
        instruction = kOverlaySc02_80149FB0Words[(cpu->pc - 0x80149fb0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a048u && cpu->pc < 0x8014a1b0u)
        instruction = kOverlaySc02_8014A048Words[(cpu->pc - 0x8014a048u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a1b0u && cpu->pc < 0x8014a218u)
        instruction = kOverlaySc02_8014A1B0Words[(cpu->pc - 0x8014a1b0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a218u && cpu->pc < 0x8014a238u)
        instruction = kOverlaySc02_8014A218Words[(cpu->pc - 0x8014a218u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a238u && cpu->pc < 0x8014a2e4u)
        instruction = kOverlaySc02_8014A238Words[(cpu->pc - 0x8014a238u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a2e4u && cpu->pc < 0x8014a380u)
        instruction = kOverlaySc02_8014A2E4Words[(cpu->pc - 0x8014a2e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a380u && cpu->pc < 0x8014a3e0u)
        instruction = kOverlaySc02_8014A380Words[(cpu->pc - 0x8014a380u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a3e0u && cpu->pc < 0x8014a454u)
        instruction = kOverlaySc02_8014A3E0Words[(cpu->pc - 0x8014a3e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a454u && cpu->pc < 0x8014a4b4u)
        instruction = kOverlaySc02_8014A454Words[(cpu->pc - 0x8014a454u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a4b4u && cpu->pc < 0x8014a4fcu)
        instruction = kOverlaySc02_8014A4B4Words[(cpu->pc - 0x8014a4b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a4fcu && cpu->pc < 0x8014a51cu)
        instruction = kOverlaySc02_8014A4FCWords[(cpu->pc - 0x8014a4fcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a51cu && cpu->pc < 0x8014a59cu)
        instruction = kOverlaySc02_8014A51CWords[(cpu->pc - 0x8014a51cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a59cu && cpu->pc < 0x8014a638u)
        instruction = kOverlaySc02_8014A59CWords[(cpu->pc - 0x8014a59cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a638u && cpu->pc < 0x8014a738u)
        instruction = kOverlaySc02_8014A638Words[(cpu->pc - 0x8014a638u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a738u && cpu->pc < 0x8014a850u)
        instruction = kOverlaySc02_8014A738Words[(cpu->pc - 0x8014a738u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014a850u && cpu->pc < 0x8014aa04u)
        instruction = kOverlaySc02_8014A850Words[(cpu->pc - 0x8014a850u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014aa04u && cpu->pc < 0x8014aa28u)
        instruction = kOverlaySc02_8014AA04Words[(cpu->pc - 0x8014aa04u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014aa28u && cpu->pc < 0x8014ab5cu)
        instruction = kOverlaySc02_8014AA28Words[(cpu->pc - 0x8014aa28u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ab5cu && cpu->pc < 0x8014ab7cu)
        instruction = kOverlaySc02_8014AB5CWords[(cpu->pc - 0x8014ab5cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ab7cu && cpu->pc < 0x8014abf0u)
        instruction = kOverlaySc02_8014AB7CWords[(cpu->pc - 0x8014ab7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014abf0u && cpu->pc < 0x8014ac10u)
        instruction = kOverlaySc02_8014ABF0Words[(cpu->pc - 0x8014abf0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ac10u && cpu->pc < 0x8014acc0u)
        instruction = kOverlaySc02_8014AC10Words[(cpu->pc - 0x8014ac10u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014acc0u && cpu->pc < 0x8014ace8u)
        instruction = kOverlaySc02_8014ACC0Words[(cpu->pc - 0x8014acc0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ace8u && cpu->pc < 0x8014ad30u)
        instruction = kOverlaySc02_8014ACE8Words[(cpu->pc - 0x8014ace8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ad30u && cpu->pc < 0x8014ad7cu)
        instruction = kOverlaySc02_8014AD30Words[(cpu->pc - 0x8014ad30u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ad7cu && cpu->pc < 0x8014ada8u)
        instruction = kOverlaySc02_8014AD7CWords[(cpu->pc - 0x8014ad7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ada8u && cpu->pc < 0x8014ade0u)
        instruction = kOverlaySc02_8014ADA8Words[(cpu->pc - 0x8014ada8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ade0u && cpu->pc < 0x8014b00cu)
        instruction = kOverlaySc02_8014ADE0Words[(cpu->pc - 0x8014ade0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b00cu && cpu->pc < 0x8014b034u)
        instruction = kOverlaySc02_8014B00CWords[(cpu->pc - 0x8014b00cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b034u && cpu->pc < 0x8014b084u)
        instruction = kOverlaySc02_8014B034Words[(cpu->pc - 0x8014b034u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b084u && cpu->pc < 0x8014b12cu)
        instruction = kOverlaySc02_8014B084Words[(cpu->pc - 0x8014b084u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b12cu && cpu->pc < 0x8014b154u)
        instruction = kOverlaySc02_8014B12CWords[(cpu->pc - 0x8014b12cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b154u && cpu->pc < 0x8014b160u)
        instruction = kOverlaySc02_8014B154Words[(cpu->pc - 0x8014b154u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b160u && cpu->pc < 0x8014b190u)
        instruction = kOverlaySc02_8014B160Words[(cpu->pc - 0x8014b160u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b190u && cpu->pc < 0x8014b2a8u)
        instruction = kOverlaySc02_8014B190Words[(cpu->pc - 0x8014b190u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b2a8u && cpu->pc < 0x8014b2d0u)
        instruction = kOverlaySc02_8014B2A8Words[(cpu->pc - 0x8014b2a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b2d0u && cpu->pc < 0x8014b2f8u)
        instruction = kOverlaySc02_8014B2D0Words[(cpu->pc - 0x8014b2d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b2f8u && cpu->pc < 0x8014b310u)
        instruction = kOverlaySc02_8014B2F8Words[(cpu->pc - 0x8014b2f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b310u && cpu->pc < 0x8014b33cu)
        instruction = kOverlaySc02_8014B310Words[(cpu->pc - 0x8014b310u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b33cu && cpu->pc < 0x8014b350u)
        instruction = kOverlaySc02_8014B33CWords[(cpu->pc - 0x8014b33cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b350u && cpu->pc < 0x8014b4c4u)
        instruction = kOverlaySc02_8014B350Words[(cpu->pc - 0x8014b350u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b4c4u && cpu->pc < 0x8014b4d4u)
        instruction = kOverlaySc02_8014B4C4Words[(cpu->pc - 0x8014b4c4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b4d4u && cpu->pc < 0x8014b504u)
        instruction = kOverlaySc02_8014B4D4Words[(cpu->pc - 0x8014b4d4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b504u && cpu->pc < 0x8014b598u)
        instruction = kOverlaySc02_8014B504Words[(cpu->pc - 0x8014b504u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b598u && cpu->pc < 0x8014b5b0u)
        instruction = kOverlaySc02_8014B598Words[(cpu->pc - 0x8014b598u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b5b0u && cpu->pc < 0x8014b5b8u)
        instruction = kOverlaySc02_8014B5B0Words[(cpu->pc - 0x8014b5b0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b5b8u && cpu->pc < 0x8014b5c4u)
        instruction = kOverlaySc02_8014B5B8Words[(cpu->pc - 0x8014b5b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b5c4u && cpu->pc < 0x8014b5d0u)
        instruction = kOverlaySc02_8014B5C4Words[(cpu->pc - 0x8014b5c4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b5d0u && cpu->pc < 0x8014b5d8u)
        instruction = kOverlaySc02_8014B5D0Words[(cpu->pc - 0x8014b5d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b5d8u && cpu->pc < 0x8014b6f0u)
        instruction = kOverlaySc02_8014B5D8Words[(cpu->pc - 0x8014b5d8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b6f0u && cpu->pc < 0x8014b768u)
        instruction = kOverlaySc02_8014B6F0Words[(cpu->pc - 0x8014b6f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b768u && cpu->pc < 0x8014b7a4u)
        instruction = kOverlaySc02_8014B768Words[(cpu->pc - 0x8014b768u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b7a4u && cpu->pc < 0x8014b944u)
        instruction = kOverlaySc02_8014B7A4Words[(cpu->pc - 0x8014b7a4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014b944u && cpu->pc < 0x8014bb0cu)
        instruction = kOverlaySc02_8014B944Words[(cpu->pc - 0x8014b944u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bb0cu && cpu->pc < 0x8014bb24u)
        instruction = kOverlaySc02_8014BB0CWords[(cpu->pc - 0x8014bb0cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bb24u && cpu->pc < 0x8014bc0cu)
        instruction = kOverlaySc02_8014BB24Words[(cpu->pc - 0x8014bb24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bc0cu && cpu->pc < 0x8014bc44u)
        instruction = kOverlaySc02_8014BC0CWords[(cpu->pc - 0x8014bc0cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bc44u && cpu->pc < 0x8014bc80u)
        instruction = kOverlaySc02_8014BC44Words[(cpu->pc - 0x8014bc44u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bc80u && cpu->pc < 0x8014bcc0u)
        instruction = kOverlaySc02_8014BC80Words[(cpu->pc - 0x8014bc80u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bcc0u && cpu->pc < 0x8014bcecu)
        instruction = kOverlaySc02_8014BCC0Words[(cpu->pc - 0x8014bcc0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bcecu && cpu->pc < 0x8014bd24u)
        instruction = kOverlaySc02_8014BCECWords[(cpu->pc - 0x8014bcecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bd24u && cpu->pc < 0x8014bd60u)
        instruction = kOverlaySc02_8014BD24Words[(cpu->pc - 0x8014bd24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bd60u && cpu->pc < 0x8014bd98u)
        instruction = kOverlaySc02_8014BD60Words[(cpu->pc - 0x8014bd60u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bd98u && cpu->pc < 0x8014bdc8u)
        instruction = kOverlaySc02_8014BD98Words[(cpu->pc - 0x8014bd98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bdc8u && cpu->pc < 0x8014bde0u)
        instruction = kOverlaySc02_8014BDC8Words[(cpu->pc - 0x8014bdc8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bde0u && cpu->pc < 0x8014bde8u)
        instruction = kOverlaySc02_8014BDE0Words[(cpu->pc - 0x8014bde0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bde8u && cpu->pc < 0x8014be78u)
        instruction = kOverlaySc02_8014BDE8Words[(cpu->pc - 0x8014bde8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014be78u && cpu->pc < 0x8014be9cu)
        instruction = kOverlaySc02_8014BE78Words[(cpu->pc - 0x8014be78u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8014be9cu && cpu->pc < 0x8014bec0u)
        instruction = kOverlaySc02_8014BE9CWords[(cpu->pc - 0x8014be9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bec0u && cpu->pc < 0x8014bef8u)
        instruction = kOverlaySc02_8014BEC0Words[(cpu->pc - 0x8014bec0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bef8u && cpu->pc < 0x8014bf18u)
        instruction = kOverlaySc02_8014BEF8Words[(cpu->pc - 0x8014bef8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bf18u && cpu->pc < 0x8014bf48u)
        instruction = kOverlaySc02_8014BF18Words[(cpu->pc - 0x8014bf18u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bf48u && cpu->pc < 0x8014bf6cu)
        instruction = kOverlaySc02_8014BF48Words[(cpu->pc - 0x8014bf48u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bf6cu && cpu->pc < 0x8014bf8cu)
        instruction = kOverlaySc02_8014BF6CWords[(cpu->pc - 0x8014bf6cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bf8cu && cpu->pc < 0x8014bfb0u)
        instruction = kOverlaySc02_8014BF8CWords[(cpu->pc - 0x8014bf8cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bfb0u && cpu->pc < 0x8014bfd4u)
        instruction = kOverlaySc02_8014BFB0Words[(cpu->pc - 0x8014bfb0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bfd4u && cpu->pc < 0x8014bff4u)
        instruction = kOverlaySc02_8014BFD4Words[(cpu->pc - 0x8014bfd4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014bff4u && cpu->pc < 0x8014c010u)
        instruction = kOverlaySc02_8014BFF4Words[(cpu->pc - 0x8014bff4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c010u && cpu->pc < 0x8014c050u)
        instruction = kOverlaySc02_8014C010Words[(cpu->pc - 0x8014c010u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c050u && cpu->pc < 0x8014c088u)
        instruction = kOverlaySc02_8014C050Words[(cpu->pc - 0x8014c050u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c088u && cpu->pc < 0x8014c0c8u)
        instruction = kOverlaySc02_8014C088Words[(cpu->pc - 0x8014c088u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c0c8u && cpu->pc < 0x8014c118u)
        instruction = kOverlaySc02_8014C0C8Words[(cpu->pc - 0x8014c0c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c118u && cpu->pc < 0x8014c168u)
        instruction = kOverlaySc02_8014C118Words[(cpu->pc - 0x8014c118u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c168u && cpu->pc < 0x8014c1a0u)
        instruction = kOverlaySc02_8014C168Words[(cpu->pc - 0x8014c168u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c1a0u && cpu->pc < 0x8014c1c8u)
        instruction = kOverlaySc02_8014C1A0Words[(cpu->pc - 0x8014c1a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c1c8u && cpu->pc < 0x8014c278u)
        instruction = kOverlaySc02_8014C1C8Words[(cpu->pc - 0x8014c1c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c278u && cpu->pc < 0x8014c2b0u)
        instruction = kOverlaySc02_8014C278Words[(cpu->pc - 0x8014c278u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c2b0u && cpu->pc < 0x8014c308u)
        instruction = kOverlaySc02_8014C2B0Words[(cpu->pc - 0x8014c2b0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c308u && cpu->pc < 0x8014c3a4u)
        instruction = kOverlaySc02_8014C308Words[(cpu->pc - 0x8014c308u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c3a4u && cpu->pc < 0x8014c3d0u)
        instruction = kOverlaySc02_8014C3A4Words[(cpu->pc - 0x8014c3a4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c3d0u && cpu->pc < 0x8014c43cu)
        instruction = kOverlaySc02_8014C3D0Words[(cpu->pc - 0x8014c3d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c43cu && cpu->pc < 0x8014c4acu)
        instruction = kOverlaySc02_8014C43CWords[(cpu->pc - 0x8014c43cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c4acu && cpu->pc < 0x8014c568u)
        instruction = kOverlaySc02_8014C4ACWords[(cpu->pc - 0x8014c4acu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c568u && cpu->pc < 0x8014c59cu)
        instruction = kOverlaySc02_8014C568Words[(cpu->pc - 0x8014c568u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c59cu && cpu->pc < 0x8014c5d0u)
        instruction = kOverlaySc02_8014C59CWords[(cpu->pc - 0x8014c59cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c5d0u && cpu->pc < 0x8014c5fcu)
        instruction = kOverlaySc02_8014C5D0Words[(cpu->pc - 0x8014c5d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c5fcu && cpu->pc < 0x8014c6acu)
        instruction = kOverlaySc02_8014C5FCWords[(cpu->pc - 0x8014c5fcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c6acu && cpu->pc < 0x8014c6c0u)
        instruction = kOverlaySc02_8014C6ACWords[(cpu->pc - 0x8014c6acu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c6c0u && cpu->pc < 0x8014c6d0u)
        instruction = kOverlaySc02_8014C6C0Words[(cpu->pc - 0x8014c6c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c6e0u && cpu->pc < 0x8014c6f4u)
        instruction = kOverlaySc02_8014C6E0Words[(cpu->pc - 0x8014c6e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c6f4u && cpu->pc < 0x8014c860u)
        instruction = kOverlaySc02_8014C6F4Words[(cpu->pc - 0x8014c6f4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c860u && cpu->pc < 0x8014c88cu)
        instruction = kOverlaySc02_8014C860Words[(cpu->pc - 0x8014c860u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c88cu && cpu->pc < 0x8014c8c8u)
        instruction = kOverlaySc02_8014C88CWords[(cpu->pc - 0x8014c88cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c8c8u && cpu->pc < 0x8014c8f0u)
        instruction = kOverlaySc02_8014C8C8Words[(cpu->pc - 0x8014c8c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c8f0u && cpu->pc < 0x8014c918u)
        instruction = kOverlaySc02_8014C8F0Words[(cpu->pc - 0x8014c8f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c918u && cpu->pc < 0x8014c968u)
        instruction = kOverlaySc02_8014C918Words[(cpu->pc - 0x8014c918u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8016533cu && cpu->pc < 0x80165374u)
        instruction = kOverlaySc02_8016533CWords[(cpu->pc - 0x8016533cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801659dcu && cpu->pc < 0x80165a18u)
        instruction = kOverlaySc02_801659DCWords[(cpu->pc - 0x801659dcu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80165a18u && cpu->pc < 0x80165a20u)
        instruction = kOverlaySc02_80165A18Words[(cpu->pc - 0x80165a18u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801627c0u && cpu->pc < 0x801627e8u)
        instruction = kOverlaySc02_801627C0Words[(cpu->pc - 0x801627c0u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80162af4u && cpu->pc < 0x80162b1cu)
        instruction = kOverlaySc02_80162AF4Words[(cpu->pc - 0x80162af4u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80165c78u && cpu->pc < 0x80165ca0u)
        instruction = kOverlaySc02_80165C78Words[(cpu->pc - 0x80165c78u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801468c8u && cpu->pc < 0x80146924u)
        instruction = kOverlaySc02_801468C8Words[(cpu->pc - 0x801468c8u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80145ee8u && cpu->pc < 0x80146014u)
        instruction = kOverlaySc02_80145EE8Words[(cpu->pc - 0x80145ee8u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80146014u && cpu->pc < 0x80146074u)
        instruction = kOverlaySc02_80146014Words[(cpu->pc - 0x80146014u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8014c968u && cpu->pc < 0x8014c978u)
        instruction = kOverlaySc02_8014C968Words[(cpu->pc - 0x8014c968u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c978u && cpu->pc < 0x8014c98cu)
        instruction = kOverlaySc02_8014C978Words[(cpu->pc - 0x8014c978u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c98cu && cpu->pc < 0x8014c99cu)
        instruction = kOverlaySc02_8014C98CWords[(cpu->pc - 0x8014c98cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014c99cu && cpu->pc < 0x8014ca00u)
        instruction = kOverlaySc02_8014C99CWords[(cpu->pc - 0x8014c99cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ca00u && cpu->pc < 0x8014ca14u)
        instruction = kOverlaySc02_8014CA00Words[(cpu->pc - 0x8014ca00u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ca14u && cpu->pc < 0x8014ca70u)
        instruction = kOverlaySc02_8014CA14Words[(cpu->pc - 0x8014ca14u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ca70u && cpu->pc < 0x8014ca88u)
        instruction = kOverlaySc02_8014CA70Words[(cpu->pc - 0x8014ca70u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ca88u && cpu->pc < 0x8014cae4u)
        instruction = kOverlaySc02_8014CA88Words[(cpu->pc - 0x8014ca88u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cae4u && cpu->pc < 0x8014cafcu)
        instruction = kOverlaySc02_8014CAE4Words[(cpu->pc - 0x8014cae4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cafcu && cpu->pc < 0x8014cb0cu)
        instruction = kOverlaySc02_8014CAFCWords[(cpu->pc - 0x8014cafcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb0cu && cpu->pc < 0x8014cb1cu)
        instruction = kOverlaySc02_8014CB0CWords[(cpu->pc - 0x8014cb0cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb1cu && cpu->pc < 0x8014cb2cu)
        instruction = kOverlaySc02_8014CB1CWords[(cpu->pc - 0x8014cb1cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb2cu && cpu->pc < 0x8014cb58u)
        instruction = kOverlaySc02_8014CB2CWords[(cpu->pc - 0x8014cb2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb58u && cpu->pc < 0x8014cb68u)
        instruction = kOverlaySc02_8014CB58Words[(cpu->pc - 0x8014cb58u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb68u && cpu->pc < 0x8014cb7cu)
        instruction = kOverlaySc02_8014CB68Words[(cpu->pc - 0x8014cb68u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb7cu && cpu->pc < 0x8014cb8cu)
        instruction = kOverlaySc02_8014CB7CWords[(cpu->pc - 0x8014cb7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb8cu && cpu->pc < 0x8014cb9cu)
        instruction = kOverlaySc02_8014CB8CWords[(cpu->pc - 0x8014cb8cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cb9cu && cpu->pc < 0x8014cbd8u)
        instruction = kOverlaySc02_8014CB9CWords[(cpu->pc - 0x8014cb9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cbd8u && cpu->pc < 0x8014cbe8u)
        instruction = kOverlaySc02_8014CBD8Words[(cpu->pc - 0x8014cbd8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cbe8u && cpu->pc < 0x8014cbf8u)
        instruction = kOverlaySc02_8014CBE8Words[(cpu->pc - 0x8014cbe8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cbf8u && cpu->pc < 0x8014cc28u)
        instruction = kOverlaySc02_8014CBF8Words[(cpu->pc - 0x8014cbf8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cc28u && cpu->pc < 0x8014ccb4u)
        instruction = kOverlaySc02_8014CC28Words[(cpu->pc - 0x8014cc28u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014ccb4u && cpu->pc < 0x8014cd0cu)
        instruction = kOverlaySc02_8014CCB4Words[(cpu->pc - 0x8014ccb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cd0cu && cpu->pc < 0x8014cd80u)
        instruction = kOverlaySc02_8014CD0CWords[(cpu->pc - 0x8014cd0cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cd80u && cpu->pc < 0x8014cf04u)
        instruction = kOverlaySc02_8014CD80Words[(cpu->pc - 0x8014cd80u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014cf04u && cpu->pc < 0x8014d04cu)
        instruction = kOverlaySc02_8014CF04Words[(cpu->pc - 0x8014cf04u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d04cu && cpu->pc < 0x8014d0a4u)
        instruction = kOverlaySc02_8014D04CWords[(cpu->pc - 0x8014d04cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d0a4u && cpu->pc < 0x8014d12cu)
        instruction = kOverlaySc02_8014D0A4Words[(cpu->pc - 0x8014d0a4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d12cu && cpu->pc < 0x8014d2a0u)
        instruction = kOverlaySc02_8014D12CWords[(cpu->pc - 0x8014d12cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d2a0u && cpu->pc < 0x8014d3e0u)
        instruction = kOverlaySc02_8014D2A0Words[(cpu->pc - 0x8014d2a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d3e0u && cpu->pc < 0x8014d438u)
        instruction = kOverlaySc02_8014D3E0Words[(cpu->pc - 0x8014d3e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d438u && cpu->pc < 0x8014d4c0u)
        instruction = kOverlaySc02_8014D438Words[(cpu->pc - 0x8014d438u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d4c0u && cpu->pc < 0x8014d610u)
        instruction = kOverlaySc02_8014D4C0Words[(cpu->pc - 0x8014d4c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d610u && cpu->pc < 0x8014d738u)
        instruction = kOverlaySc02_8014D610Words[(cpu->pc - 0x8014d610u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d738u && cpu->pc < 0x8014d790u)
        instruction = kOverlaySc02_8014D738Words[(cpu->pc - 0x8014d738u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d790u && cpu->pc < 0x8014d820u)
        instruction = kOverlaySc02_8014D790Words[(cpu->pc - 0x8014d790u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014d820u && cpu->pc < 0x8014dce0u)
        instruction = kOverlaySc02_8014D820Words[(cpu->pc - 0x8014d820u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014dce0u && cpu->pc < 0x8014dd8cu)
        instruction = kOverlaySc02_8014DCE0Words[(cpu->pc - 0x8014dce0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014dd8cu && cpu->pc < 0x8014df3cu)
        instruction = kOverlaySc02_8014DD8CWords[(cpu->pc - 0x8014dd8cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014df3cu && cpu->pc < 0x8014df94u)
        instruction = kOverlaySc02_8014DF3CWords[(cpu->pc - 0x8014df3cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014df94u && cpu->pc < 0x8014e048u)
        instruction = kOverlaySc02_8014DF94Words[(cpu->pc - 0x8014df94u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e048u && cpu->pc < 0x8014e284u)
        instruction = kOverlaySc02_8014E048Words[(cpu->pc - 0x8014e048u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e284u && cpu->pc < 0x8014e434u)
        instruction = kOverlaySc02_8014E284Words[(cpu->pc - 0x8014e284u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e434u && cpu->pc < 0x8014e48cu)
        instruction = kOverlaySc02_8014E434Words[(cpu->pc - 0x8014e434u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e48cu && cpu->pc < 0x8014e514u)
        instruction = kOverlaySc02_8014E48CWords[(cpu->pc - 0x8014e48cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e514u && cpu->pc < 0x8014e5b4u)
        instruction = kOverlaySc02_8014E514Words[(cpu->pc - 0x8014e514u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e5b4u && cpu->pc < 0x8014e6a0u)
        instruction = kOverlaySc02_8014E5B4Words[(cpu->pc - 0x8014e5b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e6a0u && cpu->pc < 0x8014e6f8u)
        instruction = kOverlaySc02_8014E6A0Words[(cpu->pc - 0x8014e6a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e6f8u && cpu->pc < 0x8014e790u)
        instruction = kOverlaySc02_8014E6F8Words[(cpu->pc - 0x8014e6f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e790u && cpu->pc < 0x8014e83cu)
        instruction = kOverlaySc02_8014E790Words[(cpu->pc - 0x8014e790u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014e83cu && cpu->pc < 0x8014e934u)
        instruction = kOverlaySc02_8014E83CWords[(cpu->pc - 0x8014e83cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8014c6d0u && cpu->pc < 0x8014c6e0u)
        instruction = kOverlaySc02_8014C6D0Words[(cpu->pc - 0x8014c6d0u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80165938u && cpu->pc < 0x80165958u)
        instruction = kOverlaySc02_80165938Words[(cpu->pc - 0x80165938u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80153c8cu && cpu->pc < 0x80153c9cu)
        instruction = kOverlaySc02_80153C8CWords[(cpu->pc - 0x80153c8cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80144b9cu && cpu->pc < 0x801457a4u)
        instruction = kOverlaySc02_80144B9CWords[(cpu->pc - 0x80144b9cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801457a4u && cpu->pc < 0x801458e0u)
        instruction = kOverlaySc02_801457A4Words[(cpu->pc - 0x801457a4u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80180d74u && cpu->pc < 0x80180db0u)
        instruction = kOverlaySc02_80180D74Words[(cpu->pc - 0x80180d74u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80180db0u && cpu->pc < 0x80180df4u)
        instruction = kOverlaySc02_80180DB0Words[(cpu->pc - 0x80180db0u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80181224u && cpu->pc < 0x8018124cu)
        instruction = kOverlaySc02_80181224Words[(cpu->pc - 0x80181224u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8016ee40u && cpu->pc < 0x8016ee94u)
        instruction = kOverlaySc02_8016EE40Words[(cpu->pc - 0x8016ee40u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8016ef78u && cpu->pc < 0x8016efa8u)
        instruction = kOverlaySc02_8016EF78Words[(cpu->pc - 0x8016ef78u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8018129cu && cpu->pc < 0x8018133cu)
        instruction = kOverlaySc02_8018129CWords[(cpu->pc - 0x8018129cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8012a018u && cpu->pc < 0x8012a048u)
        instruction = kOverlaySc02_8012A018Words[(cpu->pc - 0x8012a018u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8012a048u && cpu->pc < 0x8012a094u)
        instruction = kOverlaySc02_8012A048Words[(cpu->pc - 0x8012a048u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8012a094u && cpu->pc < 0x8012a0e0u)
        instruction = kOverlaySc02_8012A094Words[(cpu->pc - 0x8012a094u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8018133cu && cpu->pc < 0x80181378u)
        instruction = kOverlaySc02_8018133CWords[(cpu->pc - 0x8018133cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80181378u && cpu->pc < 0x801814e4u)
        instruction = kOverlaySc02_80181378Words[(cpu->pc - 0x80181378u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x801814e4u && cpu->pc < 0x801816c0u)
        instruction = kOverlaySc02_801814E4Words[(cpu->pc - 0x801814e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013b83cu && cpu->pc < 0x8013bc7cu)
        instruction = kOverlaySc02_8013B83CWords[(cpu->pc - 0x8013b83cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013d53cu && cpu->pc < 0x8013d8fcu)
        instruction = kOverlaySc02_8013D53CWords[(cpu->pc - 0x8013d53cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013d8fcu && cpu->pc < 0x8013d9b0u)
        instruction = kOverlaySc02_8013D8FCWords[(cpu->pc - 0x8013d8fcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013cf68u && cpu->pc < 0x8013d064u)
        instruction = kOverlaySc02_8013CF68Words[(cpu->pc - 0x8013cf68u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801832d0u && cpu->pc < 0x801832f4u)
        instruction = kOverlaySc02_801832D0Words[(cpu->pc - 0x801832d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801832f4u && cpu->pc < 0x80183314u)
        instruction = kOverlaySc02_801832F4Words[(cpu->pc - 0x801832f4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183314u && cpu->pc < 0x80183458u)
        instruction = kOverlaySc02_80183314Words[(cpu->pc - 0x80183314u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183458u && cpu->pc < 0x80183808u)
        instruction = kOverlaySc02_80183458Words[(cpu->pc - 0x80183458u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183808u && cpu->pc < 0x80183810u)
        instruction = kOverlaySc02_80183808Words[(cpu->pc - 0x80183808u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183810u && cpu->pc < 0x80183a20u)
        instruction = kOverlaySc02_80183810Words[(cpu->pc - 0x80183810u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183a20u && cpu->pc < 0x80183bb0u)
        instruction = kOverlaySc02_80183A20Words[(cpu->pc - 0x80183a20u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183bb0u && cpu->pc < 0x80183d84u)
        instruction = kOverlaySc02_80183BB0Words[(cpu->pc - 0x80183bb0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183d84u && cpu->pc < 0x80183dc0u)
        instruction = kOverlaySc02_80183D84Words[(cpu->pc - 0x80183d84u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183dc0u && cpu->pc < 0x80183fecu)
        instruction = kOverlaySc02_80183DC0Words[(cpu->pc - 0x80183dc0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80183fecu && cpu->pc < 0x80184028u)
        instruction = kOverlaySc02_80183FECWords[(cpu->pc - 0x80183fecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184028u && cpu->pc < 0x8018418cu)
        instruction = kOverlaySc02_80184028Words[(cpu->pc - 0x80184028u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8018418cu && cpu->pc < 0x80184318u)
        instruction = kOverlaySc02_8018418CWords[(cpu->pc - 0x8018418cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184318u && cpu->pc < 0x801843f0u)
        instruction = kOverlaySc02_80184318Words[(cpu->pc - 0x80184318u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181868u && cpu->pc < 0x801818a4u)
        instruction = kOverlaySc02_80181868Words[(cpu->pc - 0x80181868u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181938u && cpu->pc < 0x801819e8u)
        instruction = kOverlaySc02_80181938Words[(cpu->pc - 0x80181938u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801843b4u && cpu->pc < 0x801843f0u)
        instruction = kOverlaySc02_801843B4Words[(cpu->pc - 0x801843b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801843f0u && cpu->pc < 0x801844c4u)
        instruction = kOverlaySc02_801843F0Words[(cpu->pc - 0x801843f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801844c4u && cpu->pc < 0x801844ecu)
        instruction = kOverlaySc02_801844C4Words[(cpu->pc - 0x801844c4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801844ecu && cpu->pc < 0x801844f4u)
        instruction = kOverlaySc02_801844ECWords[(cpu->pc - 0x801844ecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801844f4u && cpu->pc < 0x80184640u)
        instruction = kOverlaySc02_801844F4Words[(cpu->pc - 0x801844f4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184640u && cpu->pc < 0x80184760u)
        instruction = kOverlaySc02_80184640Words[(cpu->pc - 0x80184640u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c354u && cpu->pc < 0x8012c438u)
        instruction = kOverlaySc02_8012C354Words[(cpu->pc - 0x8012c354u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c438u && cpu->pc < 0x8012c51cu)
        instruction = kOverlaySc02_8012C438Words[(cpu->pc - 0x8012c438u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c51cu && cpu->pc < 0x8012c588u)
        instruction = kOverlaySc02_8012C51CWords[(cpu->pc - 0x8012c51cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c588u && cpu->pc < 0x8012c658u)
        instruction = kOverlaySc02_8012C588Words[(cpu->pc - 0x8012c588u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cb7cu && cpu->pc < 0x8017cbb8u)
        instruction = kOverlaySc02_8017CB7CWords[(cpu->pc - 0x8017cb7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cbb8u && cpu->pc < 0x8017cc04u)
        instruction = kOverlaySc02_8017CBB8Words[(cpu->pc - 0x8017cbb8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cc04u && cpu->pc < 0x8017ccf8u)
        instruction = kOverlaySc02_8017CC04Words[(cpu->pc - 0x8017cc04u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017ccf8u && cpu->pc < 0x8017cd78u)
        instruction = kOverlaySc02_8017CCF8Words[(cpu->pc - 0x8017ccf8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cd78u && cpu->pc < 0x8017ce2cu)
        instruction = kOverlaySc02_8017CD78Words[(cpu->pc - 0x8017cd78u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017ce2cu && cpu->pc < 0x8017ce98u)
        instruction = kOverlaySc02_8017CE2CWords[(cpu->pc - 0x8017ce2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017ce98u && cpu->pc < 0x8017cf24u)
        instruction = kOverlaySc02_8017CE98Words[(cpu->pc - 0x8017ce98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cf24u && cpu->pc < 0x8017cf44u)
        instruction = kOverlaySc02_8017CF24Words[(cpu->pc - 0x8017cf24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cf44u && cpu->pc < 0x8017cf98u)
        instruction = kOverlaySc02_8017CF44Words[(cpu->pc - 0x8017cf44u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cf98u && cpu->pc < 0x8017cfd4u)
        instruction = kOverlaySc02_8017CF98Words[(cpu->pc - 0x8017cf98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017cfd4u && cpu->pc < 0x8017d010u)
        instruction = kOverlaySc02_8017CFD4Words[(cpu->pc - 0x8017cfd4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017e39cu && cpu->pc < 0x8017e538u)
        instruction = kOverlaySc02_8017E39CWords[(cpu->pc - 0x8017e39cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017e538u && cpu->pc < 0x8017e73cu)
        instruction = kOverlaySc02_8017E538Words[(cpu->pc - 0x8017e538u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017e73cu && cpu->pc < 0x8017eb30u)
        instruction = kOverlaySc02_8017E73CWords[(cpu->pc - 0x8017e73cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017eb30u && cpu->pc < 0x8017ecb0u)
        instruction = kOverlaySc02_8017EB30Words[(cpu->pc - 0x8017eb30u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017ecb0u && cpu->pc < 0x8017ee3cu)
        instruction = kOverlaySc02_8017ECB0Words[(cpu->pc - 0x8017ecb0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017ee3cu && cpu->pc < 0x8017f050u)
        instruction = kOverlaySc02_8017EE3CWords[(cpu->pc - 0x8017ee3cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017f050u && cpu->pc < 0x8017f124u)
        instruction = kOverlaySc02_8017F050Words[(cpu->pc - 0x8017f050u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017f124u && cpu->pc < 0x8017f24cu)
        instruction = kOverlaySc02_8017F124Words[(cpu->pc - 0x8017f124u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017f24cu && cpu->pc < 0x8017f3c0u)
        instruction = kOverlaySc02_8017F24CWords[(cpu->pc - 0x8017f24cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017f3c0u && cpu->pc < 0x8017f400u)
        instruction = kOverlaySc02_8017F3C0Words[(cpu->pc - 0x8017f3c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017c2b0u && cpu->pc < 0x8017c63cu)
        instruction = kOverlaySc02_8017C2B0Words[(cpu->pc - 0x8017c2b0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017c63cu && cpu->pc < 0x8017c8b4u)
        instruction = kOverlaySc02_8017C63CWords[(cpu->pc - 0x8017c63cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017c8b4u && cpu->pc < 0x8017c9fcu)
        instruction = kOverlaySc02_8017C8B4Words[(cpu->pc - 0x8017c8b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017c9fcu && cpu->pc < 0x8017cb7cu)
        instruction = kOverlaySc02_8017C9FCWords[(cpu->pc - 0x8017c9fcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801788b8u && cpu->pc < 0x80178970u)
        instruction = kOverlaySc02_801788B8Words[(cpu->pc - 0x801788b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c658u && cpu->pc < 0x8012c750u)
        instruction = kOverlaySc02_8012C658Words[(cpu->pc - 0x8012c658u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012e8e0u && cpu->pc < 0x8012e9c0u)
        instruction = kOverlaySc02_8012E8E0Words[(cpu->pc - 0x8012e8e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144988u && cpu->pc < 0x801449c8u)
        instruction = kOverlaySc02_80144988Words[(cpu->pc - 0x80144988u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801449c8u && cpu->pc < 0x80144a04u)
        instruction = kOverlaySc02_801449C8Words[(cpu->pc - 0x801449c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144a04u && cpu->pc < 0x80144a2cu)
        instruction = kOverlaySc02_80144A04Words[(cpu->pc - 0x80144a04u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144a2cu && cpu->pc < 0x80144a68u)
        instruction = kOverlaySc02_80144A2CWords[(cpu->pc - 0x80144a2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144a68u && cpu->pc < 0x80144a90u)
        instruction = kOverlaySc02_80144A68Words[(cpu->pc - 0x80144a68u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144a90u && cpu->pc < 0x80144a98u)
        instruction = kOverlaySc02_80144A90Words[(cpu->pc - 0x80144a90u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144a98u && cpu->pc < 0x80144aecu)
        instruction = kOverlaySc02_80144A98Words[(cpu->pc - 0x80144a98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144aecu && cpu->pc < 0x80144b14u)
        instruction = kOverlaySc02_80144AECWords[(cpu->pc - 0x80144aecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144b14u && cpu->pc < 0x80144b9cu)
        instruction = kOverlaySc02_80144B14Words[(cpu->pc - 0x80144b14u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012ad44u && cpu->pc < 0x8012ad50u)
        instruction = kOverlaySc02_8012AD44Words[(cpu->pc - 0x8012ad44u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801848a8u && cpu->pc < 0x801848e4u)
        instruction = kOverlaySc02_801848A8Words[(cpu->pc - 0x801848a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801848e4u && cpu->pc < 0x8018496cu)
        instruction = kOverlaySc02_801848E4Words[(cpu->pc - 0x801848e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8018496cu && cpu->pc < 0x80184a2cu)
        instruction = kOverlaySc02_8018496CWords[(cpu->pc - 0x8018496cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184a2cu && cpu->pc < 0x80184a9cu)
        instruction = kOverlaySc02_80184A2CWords[(cpu->pc - 0x80184a2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184a9cu && cpu->pc < 0x80184b94u)
        instruction = kOverlaySc02_80184A9CWords[(cpu->pc - 0x80184a9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80184b94u && cpu->pc < 0x80184c24u)
        instruction = kOverlaySc02_80184B94Words[(cpu->pc - 0x80184b94u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143970u && cpu->pc < 0x801439fcu)
        instruction = kOverlaySc02_80143970Words[(cpu->pc - 0x80143970u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801439fcu && cpu->pc < 0x80143b6cu)
        instruction = kOverlaySc02_801439FCWords[(cpu->pc - 0x801439fcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143b6cu && cpu->pc < 0x80143cd4u)
        instruction = kOverlaySc02_80143B6CWords[(cpu->pc - 0x80143b6cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143cd4u && cpu->pc < 0x80143d28u)
        instruction = kOverlaySc02_80143CD4Words[(cpu->pc - 0x80143cd4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143d28u && cpu->pc < 0x80143eb4u)
        instruction = kOverlaySc02_80143D28Words[(cpu->pc - 0x80143d28u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143eb4u && cpu->pc < 0x80143ebcu)
        instruction = kOverlaySc02_80143EB4Words[(cpu->pc - 0x80143eb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80143ebcu && cpu->pc < 0x80144054u)
        instruction = kOverlaySc02_80143EBCWords[(cpu->pc - 0x80143ebcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144054u && cpu->pc < 0x80144090u)
        instruction = kOverlaySc02_80144054Words[(cpu->pc - 0x80144054u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144090u && cpu->pc < 0x801442f8u)
        instruction = kOverlaySc02_80144090Words[(cpu->pc - 0x80144090u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801442f8u && cpu->pc < 0x80144364u)
        instruction = kOverlaySc02_801442F8Words[(cpu->pc - 0x801442f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144364u && cpu->pc < 0x80144458u)
        instruction = kOverlaySc02_80144364Words[(cpu->pc - 0x80144364u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144458u && cpu->pc < 0x80144558u)
        instruction = kOverlaySc02_80144458Words[(cpu->pc - 0x80144458u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144558u && cpu->pc < 0x8014462cu)
        instruction = kOverlaySc02_80144558Words[(cpu->pc - 0x80144558u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014462cu && cpu->pc < 0x801446a4u)
        instruction = kOverlaySc02_8014462CWords[(cpu->pc - 0x8014462cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801446a4u && cpu->pc < 0x8014477cu)
        instruction = kOverlaySc02_801446A4Words[(cpu->pc - 0x801446a4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014477cu && cpu->pc < 0x80144880u)
        instruction = kOverlaySc02_8014477CWords[(cpu->pc - 0x8014477cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80144880u && cpu->pc < 0x80144988u)
        instruction = kOverlaySc02_80144880Words[(cpu->pc - 0x80144880u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801458e8u && cpu->pc < 0x80145934u)
        instruction = kOverlaySc02_801458E8Words[(cpu->pc - 0x801458e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80145934u && cpu->pc < 0x80145a2cu)
        instruction = kOverlaySc02_80145934Words[(cpu->pc - 0x80145934u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80145a2cu && cpu->pc < 0x80145b24u)
        instruction = kOverlaySc02_80145A2CWords[(cpu->pc - 0x80145a2cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80145b24u && cpu->pc < 0x80145bf8u)
        instruction = kOverlaySc02_80145B24Words[(cpu->pc - 0x80145b24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80145bf8u && cpu->pc < 0x80145c54u)
        instruction = kOverlaySc02_80145BF8Words[(cpu->pc - 0x80145bf8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80145c54u && cpu->pc < 0x80145cecu)
        instruction = kOverlaySc02_80145C54Words[(cpu->pc - 0x80145c54u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012a828u && cpu->pc < 0x8012a860u)
        instruction = kOverlaySc02_8012A828Words[(cpu->pc - 0x8012a828u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c218u && cpu->pc < 0x8012c284u)
        instruction = kOverlaySc02_8012C218Words[(cpu->pc - 0x8012c218u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012aaacu && cpu->pc < 0x8012aca0u)
        instruction = kOverlaySc02_8012AAACWords[(cpu->pc - 0x8012aaacu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012aca0u && cpu->pc < 0x8012ace0u)
        instruction = kOverlaySc02_8012ACA0Words[(cpu->pc - 0x8012aca0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182070u && cpu->pc < 0x80182078u)
        instruction = kOverlaySc02_80182070Words[(cpu->pc - 0x80182070u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182078u && cpu->pc < 0x801820e0u)
        instruction = kOverlaySc02_80182078Words[(cpu->pc - 0x80182078u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801820e0u && cpu->pc < 0x80182174u)
        instruction = kOverlaySc02_801820E0Words[(cpu->pc - 0x801820e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182174u && cpu->pc < 0x801821f4u)
        instruction = kOverlaySc02_80182174Words[(cpu->pc - 0x80182174u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801821f4u && cpu->pc < 0x80182328u)
        instruction = kOverlaySc02_801821F4Words[(cpu->pc - 0x801821f4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182328u && cpu->pc < 0x801824e4u)
        instruction = kOverlaySc02_80182328Words[(cpu->pc - 0x80182328u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801824e4u && cpu->pc < 0x801825e0u)
        instruction = kOverlaySc02_801824E4Words[(cpu->pc - 0x801824e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801825e0u && cpu->pc < 0x80182618u)
        instruction = kOverlaySc02_801825E0Words[(cpu->pc - 0x801825e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182618u && cpu->pc < 0x80182674u)
        instruction = kOverlaySc02_80182618Words[(cpu->pc - 0x80182618u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182674u && cpu->pc < 0x80182848u)
        instruction = kOverlaySc02_80182674Words[(cpu->pc - 0x80182674u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182848u && cpu->pc < 0x80182994u)
        instruction = kOverlaySc02_80182848Words[(cpu->pc - 0x80182848u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182994u && cpu->pc < 0x801829a0u)
        instruction = kOverlaySc02_80182994Words[(cpu->pc - 0x80182994u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801829a0u && cpu->pc < 0x801829a8u)
        instruction = kOverlaySc02_801829A0Words[(cpu->pc - 0x801829a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801829a8u && cpu->pc < 0x801829bcu)
        instruction = kOverlaySc02_801829A8Words[(cpu->pc - 0x801829a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801829bcu && cpu->pc < 0x801829f8u)
        instruction = kOverlaySc02_801829BCWords[(cpu->pc - 0x801829bcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801829f8u && cpu->pc < 0x80182a7cu)
        instruction = kOverlaySc02_801829F8Words[(cpu->pc - 0x801829f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182a7cu && cpu->pc < 0x80182ab4u)
        instruction = kOverlaySc02_80182A7CWords[(cpu->pc - 0x80182a7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182ab4u && cpu->pc < 0x80182b64u)
        instruction = kOverlaySc02_80182AB4Words[(cpu->pc - 0x80182ab4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182b64u && cpu->pc < 0x80182ba0u)
        instruction = kOverlaySc02_80182B64Words[(cpu->pc - 0x80182b64u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182ba0u && cpu->pc < 0x80182be0u)
        instruction = kOverlaySc02_80182BA0Words[(cpu->pc - 0x80182ba0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182be0u && cpu->pc < 0x80182c24u)
        instruction = kOverlaySc02_80182BE0Words[(cpu->pc - 0x80182be0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182c24u && cpu->pc < 0x80182c60u)
        instruction = kOverlaySc02_80182C24Words[(cpu->pc - 0x80182c24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182c60u && cpu->pc < 0x80182cf4u)
        instruction = kOverlaySc02_80182C60Words[(cpu->pc - 0x80182c60u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80182cf4u && cpu->pc < 0x801832d0u)
        instruction = kOverlaySc02_80182CF4Words[(cpu->pc - 0x80182cf4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012cae4u && cpu->pc < 0x8012cb64u)
        instruction = kOverlaySc02_8012CAE4Words[(cpu->pc - 0x8012cae4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012b2ccu && cpu->pc < 0x8012b370u)
        instruction = kOverlaySc02_8012B2CCWords[(cpu->pc - 0x8012b2ccu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012b14cu && cpu->pc < 0x8012b178u)
        instruction = kOverlaySc02_8012B14CWords[(cpu->pc - 0x8012b14cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181ef0u && cpu->pc < 0x80181f20u)
        instruction = kOverlaySc02_80181EF0Words[(cpu->pc - 0x80181ef0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181bb4u && cpu->pc < 0x80181c2cu)
        instruction = kOverlaySc02_80181BB4Words[(cpu->pc - 0x80181bb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181b78u && cpu->pc < 0x80181bb4u)
        instruction = kOverlaySc02_80181B78Words[(cpu->pc - 0x80181b78u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012ad50u && cpu->pc < 0x8012ad64u)
        instruction = kOverlaySc02_8012AD50Words[(cpu->pc - 0x8012ad50u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181a24u && cpu->pc < 0x80181a44u)
        instruction = kOverlaySc02_80181A24Words[(cpu->pc - 0x80181a24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801819e8u && cpu->pc < 0x80181a24u)
        instruction = kOverlaySc02_801819E8Words[(cpu->pc - 0x801819e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181f5cu && cpu->pc < 0x80181fa4u)
        instruction = kOverlaySc02_80181F5CWords[(cpu->pc - 0x80181f5cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181fa4u && cpu->pc < 0x80182070u)
        instruction = kOverlaySc02_80181FA4Words[(cpu->pc - 0x80181fa4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80181f20u && cpu->pc < 0x80181f5cu)
        instruction = kOverlaySc02_80181F20Words[(cpu->pc - 0x80181f20u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c194u && cpu->pc < 0x8012c1b8u)
        instruction = kOverlaySc02_8012C194Words[(cpu->pc - 0x8012c194u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c1b8u && cpu->pc < 0x8012c1dcu)
        instruction = kOverlaySc02_8012C1B8Words[(cpu->pc - 0x8012c1b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c1dcu && cpu->pc < 0x8012c218u)
        instruction = kOverlaySc02_8012C1DCWords[(cpu->pc - 0x8012c1dcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013221cu && cpu->pc < 0x80132288u)
        instruction = kOverlaySc02_8013221CWords[(cpu->pc - 0x8013221cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80131fdcu && cpu->pc < 0x80132018u)
        instruction = kOverlaySc02_80131FDCWords[(cpu->pc - 0x80131fdcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c890u && cpu->pc < 0x8012cae4u)
        instruction = kOverlaySc02_8012C890Words[(cpu->pc - 0x8012c890u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c750u && cpu->pc < 0x8012c820u)
        instruction = kOverlaySc02_8012C750Words[(cpu->pc - 0x8012c750u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013e4b4u && cpu->pc < 0x8013e558u)
        instruction = kOverlaySc02_8013E4B4Words[(cpu->pc - 0x8013e4b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80178608u && cpu->pc < 0x8017869cu)
        instruction = kOverlaySc02_80178608Words[(cpu->pc - 0x80178608u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80128564u && cpu->pc < 0x801285d4u)
        instruction = kOverlaySc02_80128564Words[(cpu->pc - 0x80128564u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801285d4u && cpu->pc < 0x801285e4u)
        instruction = kOverlaySc02_801285D4Words[(cpu->pc - 0x801285d4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801285e4u && cpu->pc < 0x80128714u)
        instruction = kOverlaySc02_801285E4Words[(cpu->pc - 0x801285e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80128714u && cpu->pc < 0x801287b8u)
        instruction = kOverlaySc02_80128714Words[(cpu->pc - 0x80128714u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801287b8u && cpu->pc < 0x801288e8u)
        instruction = kOverlaySc02_801287B8Words[(cpu->pc - 0x801287b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801288e8u && cpu->pc < 0x80128a28u)
        instruction = kOverlaySc02_801288E8Words[(cpu->pc - 0x801288e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80128a28u && cpu->pc < 0x80128af4u)
        instruction = kOverlaySc02_80128A28Words[(cpu->pc - 0x80128a28u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80128af4u && cpu->pc < 0x80128c14u)
        instruction = kOverlaySc02_80128AF4Words[(cpu->pc - 0x80128af4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146074u && cpu->pc < 0x8014607cu)
        instruction = kOverlaySc02_80146074Words[(cpu->pc - 0x80146074u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014607cu && cpu->pc < 0x80146128u)
        instruction = kOverlaySc02_8014607CWords[(cpu->pc - 0x8014607cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146128u && cpu->pc < 0x80146360u)
        instruction = kOverlaySc02_80146128Words[(cpu->pc - 0x80146128u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146360u && cpu->pc < 0x801463a0u)
        instruction = kOverlaySc02_80146360Words[(cpu->pc - 0x80146360u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801463a0u && cpu->pc < 0x80146534u)
        instruction = kOverlaySc02_801463A0Words[(cpu->pc - 0x801463a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146534u && cpu->pc < 0x80146554u)
        instruction = kOverlaySc02_80146534Words[(cpu->pc - 0x80146534u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146554u && cpu->pc < 0x80146578u)
        instruction = kOverlaySc02_80146554Words[(cpu->pc - 0x80146554u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146578u && cpu->pc < 0x8014659cu)
        instruction = kOverlaySc02_80146578Words[(cpu->pc - 0x80146578u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014659cu && cpu->pc < 0x801465c0u)
        instruction = kOverlaySc02_8014659CWords[(cpu->pc - 0x8014659cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801465c0u && cpu->pc < 0x801465e4u)
        instruction = kOverlaySc02_801465C0Words[(cpu->pc - 0x801465c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801465e4u && cpu->pc < 0x80146608u)
        instruction = kOverlaySc02_801465E4Words[(cpu->pc - 0x801465e4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146608u && cpu->pc < 0x801466b4u)
        instruction = kOverlaySc02_80146608Words[(cpu->pc - 0x80146608u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801466b4u && cpu->pc < 0x801466f0u)
        instruction = kOverlaySc02_801466B4Words[(cpu->pc - 0x801466b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801466f0u && cpu->pc < 0x80146750u)
        instruction = kOverlaySc02_801466F0Words[(cpu->pc - 0x801466f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146750u && cpu->pc < 0x8014680cu)
        instruction = kOverlaySc02_80146750Words[(cpu->pc - 0x80146750u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014680cu && cpu->pc < 0x801468c8u)
        instruction = kOverlaySc02_8014680CWords[(cpu->pc - 0x8014680cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146924u && cpu->pc < 0x80146994u)
        instruction = kOverlaySc02_80146924Words[(cpu->pc - 0x80146924u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146994u && cpu->pc < 0x801469c8u)
        instruction = kOverlaySc02_80146994Words[(cpu->pc - 0x80146994u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801469c8u && cpu->pc < 0x80146a6cu)
        instruction = kOverlaySc02_801469C8Words[(cpu->pc - 0x801469c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146a6cu && cpu->pc < 0x80146ab4u)
        instruction = kOverlaySc02_80146A6CWords[(cpu->pc - 0x80146a6cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146ab4u && cpu->pc < 0x80146afcu)
        instruction = kOverlaySc02_80146AB4Words[(cpu->pc - 0x80146ab4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146afcu && cpu->pc < 0x80146b9cu)
        instruction = kOverlaySc02_80146AFCWords[(cpu->pc - 0x80146afcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146b9cu && cpu->pc < 0x80146c3cu)
        instruction = kOverlaySc02_80146B9CWords[(cpu->pc - 0x80146b9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146c3cu && cpu->pc < 0x80146c98u)
        instruction = kOverlaySc02_80146C3CWords[(cpu->pc - 0x80146c3cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146c98u && cpu->pc < 0x80146ca0u)
        instruction = kOverlaySc02_80146C98Words[(cpu->pc - 0x80146c98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146ca0u && cpu->pc < 0x80146cb4u)
        instruction = kOverlaySc02_80146CA0Words[(cpu->pc - 0x80146ca0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146cb4u && cpu->pc < 0x80146cc8u)
        instruction = kOverlaySc02_80146CB4Words[(cpu->pc - 0x80146cb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146cc8u && cpu->pc < 0x80146d30u)
        instruction = kOverlaySc02_80146CC8Words[(cpu->pc - 0x80146cc8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146d30u && cpu->pc < 0x80146d80u)
        instruction = kOverlaySc02_80146D30Words[(cpu->pc - 0x80146d30u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146d80u && cpu->pc < 0x80146d90u)
        instruction = kOverlaySc02_80146D80Words[(cpu->pc - 0x80146d80u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146d90u && cpu->pc < 0x80146db8u)
        instruction = kOverlaySc02_80146D90Words[(cpu->pc - 0x80146d90u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146db8u && cpu->pc < 0x80146de8u)
        instruction = kOverlaySc02_80146DB8Words[(cpu->pc - 0x80146db8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146de8u && cpu->pc < 0x80146df8u)
        instruction = kOverlaySc02_80146DE8Words[(cpu->pc - 0x80146de8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146df8u && cpu->pc < 0x80146e90u)
        instruction = kOverlaySc02_80146DF8Words[(cpu->pc - 0x80146df8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146e90u && cpu->pc < 0x80146e98u)
        instruction = kOverlaySc02_80146E90Words[(cpu->pc - 0x80146e90u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146e98u && cpu->pc < 0x80146ec0u)
        instruction = kOverlaySc02_80146E98Words[(cpu->pc - 0x80146e98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146ec0u && cpu->pc < 0x80146f58u)
        instruction = kOverlaySc02_80146EC0Words[(cpu->pc - 0x80146ec0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146f58u && cpu->pc < 0x80146fc4u)
        instruction = kOverlaySc02_80146F58Words[(cpu->pc - 0x80146f58u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80146fc4u && cpu->pc < 0x8014704cu)
        instruction = kOverlaySc02_80146FC4Words[(cpu->pc - 0x80146fc4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014704cu && cpu->pc < 0x80147054u)
        instruction = kOverlaySc02_8014704CWords[(cpu->pc - 0x8014704cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147054u && cpu->pc < 0x80147060u)
        instruction = kOverlaySc02_80147054Words[(cpu->pc - 0x80147054u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147060u && cpu->pc < 0x8014706cu)
        instruction = kOverlaySc02_80147060Words[(cpu->pc - 0x80147060u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014706cu && cpu->pc < 0x80147078u)
        instruction = kOverlaySc02_8014706CWords[(cpu->pc - 0x8014706cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147078u && cpu->pc < 0x80147084u)
        instruction = kOverlaySc02_80147078Words[(cpu->pc - 0x80147078u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014708cu && cpu->pc < 0x80147098u)
        instruction = kOverlaySc02_8014708CWords[(cpu->pc - 0x8014708cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801470a0u && cpu->pc < 0x801470acu)
        instruction = kOverlaySc02_801470A0Words[(cpu->pc - 0x801470a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801470b4u && cpu->pc < 0x801470c0u)
        instruction = kOverlaySc02_801470B4Words[(cpu->pc - 0x801470b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801470c0u && cpu->pc < 0x80147118u)
        instruction = kOverlaySc02_801470C0Words[(cpu->pc - 0x801470c0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147118u && cpu->pc < 0x80147264u)
        instruction = kOverlaySc02_80147118Words[(cpu->pc - 0x80147118u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147264u && cpu->pc < 0x80147290u)
        instruction = kOverlaySc02_80147264Words[(cpu->pc - 0x80147264u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147290u && cpu->pc < 0x801472b4u)
        instruction = kOverlaySc02_80147290Words[(cpu->pc - 0x80147290u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801472b4u && cpu->pc < 0x801472c8u)
        instruction = kOverlaySc02_801472B4Words[(cpu->pc - 0x801472b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801472c8u && cpu->pc < 0x801472dcu)
        instruction = kOverlaySc02_801472C8Words[(cpu->pc - 0x801472c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801472dcu && cpu->pc < 0x801472f0u)
        instruction = kOverlaySc02_801472DCWords[(cpu->pc - 0x801472dcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801472f0u && cpu->pc < 0x80147300u)
        instruction = kOverlaySc02_801472F0Words[(cpu->pc - 0x801472f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147300u && cpu->pc < 0x80147324u)
        instruction = kOverlaySc02_80147300Words[(cpu->pc - 0x80147300u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147324u && cpu->pc < 0x80147364u)
        instruction = kOverlaySc02_80147324Words[(cpu->pc - 0x80147324u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147364u && cpu->pc < 0x801473dcu)
        instruction = kOverlaySc02_80147364Words[(cpu->pc - 0x80147364u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801473dcu && cpu->pc < 0x801473ecu)
        instruction = kOverlaySc02_801473DCWords[(cpu->pc - 0x801473dcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801473ecu && cpu->pc < 0x80147460u)
        instruction = kOverlaySc02_801473ECWords[(cpu->pc - 0x801473ecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147460u && cpu->pc < 0x80147478u)
        instruction = kOverlaySc02_80147460Words[(cpu->pc - 0x80147460u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147478u && cpu->pc < 0x801474d8u)
        instruction = kOverlaySc02_80147478Words[(cpu->pc - 0x80147478u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801474d8u && cpu->pc < 0x801474ecu)
        instruction = kOverlaySc02_801474D8Words[(cpu->pc - 0x801474d8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801474ecu && cpu->pc < 0x80147514u)
        instruction = kOverlaySc02_801474ECWords[(cpu->pc - 0x801474ecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147514u && cpu->pc < 0x80147628u)
        instruction = kOverlaySc02_80147514Words[(cpu->pc - 0x80147514u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147628u && cpu->pc < 0x80147718u)
        instruction = kOverlaySc02_80147628Words[(cpu->pc - 0x80147628u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147718u && cpu->pc < 0x80147788u)
        instruction = kOverlaySc02_80147718Words[(cpu->pc - 0x80147718u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147788u && cpu->pc < 0x801477a8u)
        instruction = kOverlaySc02_80147788Words[(cpu->pc - 0x80147788u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801477a8u && cpu->pc < 0x801477c8u)
        instruction = kOverlaySc02_801477A8Words[(cpu->pc - 0x801477a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801477c8u && cpu->pc < 0x801477e8u)
        instruction = kOverlaySc02_801477C8Words[(cpu->pc - 0x801477c8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801477e8u && cpu->pc < 0x80147814u)
        instruction = kOverlaySc02_801477E8Words[(cpu->pc - 0x801477e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147814u && cpu->pc < 0x80147860u)
        instruction = kOverlaySc02_80147814Words[(cpu->pc - 0x80147814u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147860u && cpu->pc < 0x801478b8u)
        instruction = kOverlaySc02_80147860Words[(cpu->pc - 0x80147860u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801478b8u && cpu->pc < 0x80147928u)
        instruction = kOverlaySc02_801478B8Words[(cpu->pc - 0x801478b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147928u && cpu->pc < 0x80147948u)
        instruction = kOverlaySc02_80147928Words[(cpu->pc - 0x80147928u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147948u && cpu->pc < 0x8014799cu)
        instruction = kOverlaySc02_80147948Words[(cpu->pc - 0x80147948u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014799cu && cpu->pc < 0x801479bcu)
        instruction = kOverlaySc02_8014799CWords[(cpu->pc - 0x8014799cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801479bcu && cpu->pc < 0x80147a10u)
        instruction = kOverlaySc02_801479BCWords[(cpu->pc - 0x801479bcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147a10u && cpu->pc < 0x80147a30u)
        instruction = kOverlaySc02_80147A10Words[(cpu->pc - 0x80147a10u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147a30u && cpu->pc < 0x80147a84u)
        instruction = kOverlaySc02_80147A30Words[(cpu->pc - 0x80147a30u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147a84u && cpu->pc < 0x80147aacu)
        instruction = kOverlaySc02_80147A84Words[(cpu->pc - 0x80147a84u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147aacu && cpu->pc < 0x80147ad4u)
        instruction = kOverlaySc02_80147AACWords[(cpu->pc - 0x80147aacu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147ad4u && cpu->pc < 0x80147b18u)
        instruction = kOverlaySc02_80147AD4Words[(cpu->pc - 0x80147ad4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147b18u && cpu->pc < 0x80147b5cu)
        instruction = kOverlaySc02_80147B18Words[(cpu->pc - 0x80147b18u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147b5cu && cpu->pc < 0x80147c30u)
        instruction = kOverlaySc02_80147B5CWords[(cpu->pc - 0x80147b5cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147c30u && cpu->pc < 0x80147cc8u)
        instruction = kOverlaySc02_80147C30Words[(cpu->pc - 0x80147c30u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147cc8u && cpu->pc < 0x80147d38u)
        instruction = kOverlaySc02_80147CC8Words[(cpu->pc - 0x80147cc8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147d38u && cpu->pc < 0x80147dc0u)
        instruction = kOverlaySc02_80147D38Words[(cpu->pc - 0x80147d38u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147dc0u && cpu->pc < 0x80147e44u)
        instruction = kOverlaySc02_80147DC0Words[(cpu->pc - 0x80147dc0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147e44u && cpu->pc < 0x80147f50u)
        instruction = kOverlaySc02_80147E44Words[(cpu->pc - 0x80147e44u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147f50u && cpu->pc < 0x80147f78u)
        instruction = kOverlaySc02_80147F50Words[(cpu->pc - 0x80147f50u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80147f78u && cpu->pc < 0x80148038u)
        instruction = kOverlaySc02_80147F78Words[(cpu->pc - 0x80147f78u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148038u && cpu->pc < 0x80148094u)
        instruction = kOverlaySc02_80148038Words[(cpu->pc - 0x80148038u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148094u && cpu->pc < 0x801483e8u)
        instruction = kOverlaySc02_80148094Words[(cpu->pc - 0x80148094u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801483e8u && cpu->pc < 0x801484b0u)
        instruction = kOverlaySc02_801483E8Words[(cpu->pc - 0x801483e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801484b0u && cpu->pc < 0x801484e8u)
        instruction = kOverlaySc02_801484B0Words[(cpu->pc - 0x801484b0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801484e8u && cpu->pc < 0x80148534u)
        instruction = kOverlaySc02_801484E8Words[(cpu->pc - 0x801484e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148534u && cpu->pc < 0x8014856cu)
        instruction = kOverlaySc02_80148534Words[(cpu->pc - 0x80148534u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014856cu && cpu->pc < 0x801485b8u)
        instruction = kOverlaySc02_8014856CWords[(cpu->pc - 0x8014856cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801485b8u && cpu->pc < 0x80148634u)
        instruction = kOverlaySc02_801485B8Words[(cpu->pc - 0x801485b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148634u && cpu->pc < 0x80148648u)
        instruction = kOverlaySc02_80148634Words[(cpu->pc - 0x80148634u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148648u && cpu->pc < 0x801487f4u)
        instruction = kOverlaySc02_80148648Words[(cpu->pc - 0x80148648u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801487f4u && cpu->pc < 0x80148800u)
        instruction = kOverlaySc02_801487F4Words[(cpu->pc - 0x801487f4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012853cu && cpu->pc < 0x80128564u)
        instruction = kOverlaySc02_8012853CWords[(cpu->pc - 0x8012853cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80175494u && cpu->pc < 0x801754a8u)
        instruction = kOverlaySc02_80175494Words[(cpu->pc - 0x80175494u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8016e8f0u && cpu->pc < 0x8016e918u)
        instruction = kOverlaySc02_8016E8F0Words[(cpu->pc - 0x8016e8f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80178004u && cpu->pc < 0x80178298u)
        instruction = kOverlaySc02_80178004Words[(cpu->pc - 0x80178004u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80176144u && cpu->pc < 0x80176218u)
        instruction = kOverlaySc02_80176144Words[(cpu->pc - 0x80176144u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80178298u && cpu->pc < 0x801783d0u)
        instruction = kOverlaySc02_80178298Words[(cpu->pc - 0x80178298u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80177940u && cpu->pc < 0x80177ad4u)
        instruction = kOverlaySc02_80177940Words[(cpu->pc - 0x80177940u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80177b5cu && cpu->pc < 0x80177da8u)
        instruction = kOverlaySc02_80177B5CWords[(cpu->pc - 0x80177b5cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80177ea4u && cpu->pc < 0x80177f84u)
        instruction = kOverlaySc02_80177EA4Words[(cpu->pc - 0x80177ea4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801770e0u && cpu->pc < 0x80177340u)
        instruction = kOverlaySc02_801770E0Words[(cpu->pc - 0x801770e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801777bcu && cpu->pc < 0x801778a8u)
        instruction = kOverlaySc02_801777BCWords[(cpu->pc - 0x801777bcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801783d0u && cpu->pc < 0x80178438u)
        instruction = kOverlaySc02_801783D0Words[(cpu->pc - 0x801783d0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80177784u && cpu->pc < 0x801777bcu)
        instruction = kOverlaySc02_80177784Words[(cpu->pc - 0x80177784u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80176d94u && cpu->pc < 0x80176ff4u)
        instruction = kOverlaySc02_80176D94Words[(cpu->pc - 0x80176d94u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80175ab8u && cpu->pc < 0x80175da8u)
        instruction = kOverlaySc02_80175AB8Words[(cpu->pc - 0x80175ab8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8017742cu && cpu->pc < 0x801775e0u)
        instruction = kOverlaySc02_8017742CWords[(cpu->pc - 0x8017742cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80175da8u && cpu->pc < 0x80176144u)
        instruction = kOverlaySc02_80175DA8Words[(cpu->pc - 0x80175da8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801757a0u && cpu->pc < 0x801757e0u)
        instruction = kOverlaySc02_801757A0Words[(cpu->pc - 0x801757a0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80175308u && cpu->pc < 0x80175414u)
        instruction = kOverlaySc02_80175308Words[(cpu->pc - 0x80175308u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801284f0u && cpu->pc < 0x8012853cu)
        instruction = kOverlaySc02_801284F0Words[(cpu->pc - 0x801284f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801284b8u && cpu->pc < 0x801284f0u)
        instruction = kOverlaySc02_801284B8Words[(cpu->pc - 0x801284b8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013d3d4u && cpu->pc < 0x8013d53cu)
        instruction = kOverlaySc02_8013D3D4Words[(cpu->pc - 0x8013d3d4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013c0f8u && cpu->pc < 0x8013c360u)
        instruction = kOverlaySc02_8013C0F8Words[(cpu->pc - 0x8013c0f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013c08cu && cpu->pc < 0x8013c0f8u)
        instruction = kOverlaySc02_8013C08CWords[(cpu->pc - 0x8013c08cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013b568u && cpu->pc < 0x8013b598u)
        instruction = kOverlaySc02_8013B568Words[(cpu->pc - 0x8013b568u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80136bc4u && cpu->pc < 0x80136c1cu)
        instruction = kOverlaySc02_80136BC4Words[(cpu->pc - 0x80136bc4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801336e8u && cpu->pc < 0x8013373cu)
        instruction = kOverlaySc02_801336E8Words[(cpu->pc - 0x801336e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012944cu && cpu->pc < 0x8012956cu)
        instruction = kOverlaySc02_8012944CWords[(cpu->pc - 0x8012944cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80129398u && cpu->pc < 0x80129428u)
        instruction = kOverlaySc02_80129398Words[(cpu->pc - 0x80129398u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012f14cu && cpu->pc < 0x8012f1a4u)
        instruction = kOverlaySc02_8012F14CWords[(cpu->pc - 0x8012f14cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148800u && cpu->pc < 0x8014880cu)
        instruction = kOverlaySc02_80148800Words[(cpu->pc - 0x80148800u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014880cu && cpu->pc < 0x80148818u)
        instruction = kOverlaySc02_8014880CWords[(cpu->pc - 0x8014880cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148818u && cpu->pc < 0x80148824u)
        instruction = kOverlaySc02_80148818Words[(cpu->pc - 0x80148818u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148824u && cpu->pc < 0x801488a8u)
        instruction = kOverlaySc02_80148824Words[(cpu->pc - 0x80148824u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801488a8u && cpu->pc < 0x8014891cu)
        instruction = kOverlaySc02_801488A8Words[(cpu->pc - 0x801488a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014891cu && cpu->pc < 0x80148980u)
        instruction = kOverlaySc02_8014891CWords[(cpu->pc - 0x8014891cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148980u && cpu->pc < 0x801489e8u)
        instruction = kOverlaySc02_80148980Words[(cpu->pc - 0x80148980u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801489e8u && cpu->pc < 0x80148a48u)
        instruction = kOverlaySc02_801489E8Words[(cpu->pc - 0x801489e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148a48u && cpu->pc < 0x80148aacu)
        instruction = kOverlaySc02_80148A48Words[(cpu->pc - 0x80148a48u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148aacu && cpu->pc < 0x80148afcu)
        instruction = kOverlaySc02_80148AACWords[(cpu->pc - 0x80148aacu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148afcu && cpu->pc < 0x80148c18u)
        instruction = kOverlaySc02_80148AFCWords[(cpu->pc - 0x80148afcu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c18u && cpu->pc < 0x80148c20u)
        instruction = kOverlaySc02_80148C18Words[(cpu->pc - 0x80148c18u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c20u && cpu->pc < 0x80148c34u)
        instruction = kOverlaySc02_80148C20Words[(cpu->pc - 0x80148c20u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c34u && cpu->pc < 0x80148c4cu)
        instruction = kOverlaySc02_80148C34Words[(cpu->pc - 0x80148c34u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c4cu && cpu->pc < 0x80148c64u)
        instruction = kOverlaySc02_80148C4CWords[(cpu->pc - 0x80148c4cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c64u && cpu->pc < 0x80148c7cu)
        instruction = kOverlaySc02_80148C64Words[(cpu->pc - 0x80148c64u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c7cu && cpu->pc < 0x80148c84u)
        instruction = kOverlaySc02_80148C7CWords[(cpu->pc - 0x80148c7cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c84u && cpu->pc < 0x80148c9cu)
        instruction = kOverlaySc02_80148C84Words[(cpu->pc - 0x80148c84u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148c9cu && cpu->pc < 0x80148cb4u)
        instruction = kOverlaySc02_80148C9CWords[(cpu->pc - 0x80148c9cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148cb4u && cpu->pc < 0x80148cccu)
        instruction = kOverlaySc02_80148CB4Words[(cpu->pc - 0x80148cb4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148cccu && cpu->pc < 0x80148ce4u)
        instruction = kOverlaySc02_80148CCCWords[(cpu->pc - 0x80148cccu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148ce4u && cpu->pc < 0x80148cecu)
        instruction = kOverlaySc02_80148CE4Words[(cpu->pc - 0x80148ce4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148cecu && cpu->pc < 0x80148cf4u)
        instruction = kOverlaySc02_80148CECWords[(cpu->pc - 0x80148cecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148cf4u && cpu->pc < 0x80148d0cu)
        instruction = kOverlaySc02_80148CF4Words[(cpu->pc - 0x80148cf4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148d0cu && cpu->pc < 0x80148d24u)
        instruction = kOverlaySc02_80148D0CWords[(cpu->pc - 0x80148d0cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148d24u && cpu->pc < 0x80148d3cu)
        instruction = kOverlaySc02_80148D24Words[(cpu->pc - 0x80148d24u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148d3cu && cpu->pc < 0x80148d44u)
        instruction = kOverlaySc02_80148D3CWords[(cpu->pc - 0x80148d3cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148d44u && cpu->pc < 0x80148e54u)
        instruction = kOverlaySc02_80148D44Words[(cpu->pc - 0x80148d44u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148e54u && cpu->pc < 0x80148f60u)
        instruction = kOverlaySc02_80148E54Words[(cpu->pc - 0x80148e54u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f60u && cpu->pc < 0x80148f68u)
        instruction = kOverlaySc02_80148F60Words[(cpu->pc - 0x80148f60u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f68u && cpu->pc < 0x80148f74u)
        instruction = kOverlaySc02_80148F68Words[(cpu->pc - 0x80148f68u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f74u && cpu->pc < 0x80148f80u)
        instruction = kOverlaySc02_80148F74Words[(cpu->pc - 0x80148f74u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f80u && cpu->pc < 0x80148f8cu)
        instruction = kOverlaySc02_80148F80Words[(cpu->pc - 0x80148f80u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f8cu && cpu->pc < 0x80148f98u)
        instruction = kOverlaySc02_80148F8CWords[(cpu->pc - 0x80148f8cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148f98u && cpu->pc < 0x80148fa0u)
        instruction = kOverlaySc02_80148F98Words[(cpu->pc - 0x80148f98u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fa0u && cpu->pc < 0x80148facu)
        instruction = kOverlaySc02_80148FA0Words[(cpu->pc - 0x80148fa0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148facu && cpu->pc < 0x80148fb8u)
        instruction = kOverlaySc02_80148FACWords[(cpu->pc - 0x80148facu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fb8u && cpu->pc < 0x80148fc4u)
        instruction = kOverlaySc02_80148FB8Words[(cpu->pc - 0x80148fb8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fc4u && cpu->pc < 0x80148fd0u)
        instruction = kOverlaySc02_80148FC4Words[(cpu->pc - 0x80148fc4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fd0u && cpu->pc < 0x80148fd8u)
        instruction = kOverlaySc02_80148FD0Words[(cpu->pc - 0x80148fd0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fd8u && cpu->pc < 0x80148fe0u)
        instruction = kOverlaySc02_80148FD8Words[(cpu->pc - 0x80148fd8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fe0u && cpu->pc < 0x80148fecu)
        instruction = kOverlaySc02_80148FE0Words[(cpu->pc - 0x80148fe0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148fecu && cpu->pc < 0x80148ff8u)
        instruction = kOverlaySc02_80148FECWords[(cpu->pc - 0x80148fecu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80148ff8u && cpu->pc < 0x80149004u)
        instruction = kOverlaySc02_80148FF8Words[(cpu->pc - 0x80148ff8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149004u && cpu->pc < 0x8014900cu)
        instruction = kOverlaySc02_80149004Words[(cpu->pc - 0x80149004u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014900cu && cpu->pc < 0x80149020u)
        instruction = kOverlaySc02_8014900CWords[(cpu->pc - 0x8014900cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149020u && cpu->pc < 0x80149034u)
        instruction = kOverlaySc02_80149020Words[(cpu->pc - 0x80149020u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149034u && cpu->pc < 0x80149048u)
        instruction = kOverlaySc02_80149034Words[(cpu->pc - 0x80149034u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149048u && cpu->pc < 0x8014905cu)
        instruction = kOverlaySc02_80149048Words[(cpu->pc - 0x80149048u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8014905cu && cpu->pc < 0x80149078u)
        instruction = kOverlaySc02_8014905CWords[(cpu->pc - 0x8014905cu)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149078u && cpu->pc < 0x801490e0u)
        instruction = kOverlaySc02_80149078Words[(cpu->pc - 0x80149078u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801490e0u && cpu->pc < 0x801490e8u)
        instruction = kOverlaySc02_801490E0Words[(cpu->pc - 0x801490e0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801490e8u && cpu->pc < 0x801490f0u)
        instruction = kOverlaySc02_801490E8Words[(cpu->pc - 0x801490e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801490f0u && cpu->pc < 0x801490f8u)
        instruction = kOverlaySc02_801490F0Words[(cpu->pc - 0x801490f0u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801490f8u && cpu->pc < 0x80149184u)
        instruction = kOverlaySc02_801490F8Words[(cpu->pc - 0x801490f8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149184u && cpu->pc < 0x801491c4u)
        instruction = kOverlaySc02_80149184Words[(cpu->pc - 0x80149184u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801491c4u && cpu->pc < 0x80149204u)
        instruction = kOverlaySc02_801491C4Words[(cpu->pc - 0x801491c4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80149204u && cpu->pc < 0x80149210u)
        instruction = kOverlaySc02_80149204Words[(cpu->pc - 0x80149204u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80128158u && cpu->pc < 0x80128420u)
        instruction = kOverlaySc02_80128158Words[(cpu->pc - 0x80128158u)/4u];
    else if (cpu->pc >= 0x80128158u && cpu->pc < 0x80128420u)
        instruction = kOverlaySc01_80128158Words[(cpu->pc - 0x80128158u)/4u];
    else if (cpu->pc >= 0x80128158u && cpu->pc < 0x80128178u)
        instruction = kOverlay0012_80128158Words[(cpu->pc - 0x80128158u)/4u];
    else if (cpu->pc >= 0x80128288u && cpu->pc < 0x801282ccu)
        instruction = kOverlay0012_80128288Words[(cpu->pc - 0x80128288u)/4u];
    else if (cpu->pc >= 0x80128228u && cpu->pc < 0x80128248u)
        instruction = kOverlay0012_80128228Words[(cpu->pc - 0x80128228u) / 4u];
    else if (cpu->pc >= 0x80128a28u && cpu->pc < 0x80128af4u)
        instruction = kOverlay0012_80128A28Words[(cpu->pc - 0x80128a28u) / 4u];
    else if (cpu->pc >= 0x8017bebcu && cpu->pc < 0x8017bee4u)
        instruction = kOverlay0012_8017BEBCWords[(cpu->pc - 0x8017bebcu) / 4u];
    else if (cpu->pc >= 0x8017bee4u && cpu->pc < 0x8017bf38u)
        instruction = kOverlay0012_8017BEE4Words[(cpu->pc - 0x8017bee4u) / 4u];
    else if (cpu->pc >= 0x8017bf38u && cpu->pc < 0x8017bf70u)
        instruction = kOverlay0012_8017BF38Words[(cpu->pc - 0x8017bf38u) / 4u];
    else if (cpu->pc >= 0x8017c008u && cpu->pc < 0x8017c080u)
        instruction = kOverlay0012_8017C008Words[(cpu->pc - 0x8017c008u) / 4u];
    else if (g_overlay_0007_words &&
             cpu->pc >= 0x800cee2cu && cpu->pc < 0x800cf02cu)
        instruction = kOverlay800CEE2CWords[(cpu->pc - 0x800cee2cu) / 4u];
    else if (g_overlay_0007_words &&
             cpu->pc >= 0x800cf02cu && cpu->pc < 0x800d1378u)
        instruction = kOverlay800CF02CWords[(cpu->pc - 0x800cf02cu) / 4u];
    /* A selected overlay must never fetch member-zero words. */
    else if (g_overlay_0004_words || g_overlay_0007_words || g_overlay_0010_words)
        return 0;
    else if (cpu->pc >= 0x800cedfcu && cpu->pc < 0x800cee40u)
        instruction = kOverlay800CEDFCWords[(cpu->pc - 0x800cedfcu) / 4u];
    else if (cpu->pc >= 0x800cee40u && cpu->pc < 0x800cef04u)
        instruction = kOverlay800CEE40Words[(cpu->pc - 0x800cee40u) / 4u];
    else if (cpu->pc >= 0x800cef04u && cpu->pc < 0x800cef54u)
        instruction = kOverlay800CEF04Words[(cpu->pc - 0x800cef04u) / 4u];
    else if (cpu->pc >= 0x800cf290u && cpu->pc < 0x800cf3e8u)
        instruction = kOverlay800CF290Words[(cpu->pc - 0x800cf290u) / 4u];
    else if (cpu->pc >= 0x800cef54u && cpu->pc < 0x800cefa8u)
        instruction = kOverlay800CEF54Words[(cpu->pc - 0x800cef54u) / 4u];
    else if (cpu->pc >= 0x800cefa8u && cpu->pc < 0x800ceff4u)
        instruction = kOverlay800CEFA8Words[(cpu->pc - 0x800cefa8u) / 4u];
    else if (cpu->pc >= 0x800ceff4u && cpu->pc < 0x800cf038u)
        instruction = kOverlay800CEFF4Words[(cpu->pc - 0x800ceff4u) / 4u];
    else if (cpu->pc >= 0x800cf038u && cpu->pc < 0x800cf0c4u)
        instruction = kOverlay800CF038Words[(cpu->pc - 0x800cf038u) / 4u];
    else if (cpu->pc >= 0x800cf0c4u && cpu->pc < 0x800cf114u)
        instruction = kOverlay800CF0C4Words[(cpu->pc - 0x800cf0c4u) / 4u];
    else if (cpu->pc >= 0x800cf114u && cpu->pc < 0x800cf180u)
        instruction = kOverlay800CF114Words[(cpu->pc - 0x800cf114u) / 4u];
    else if (cpu->pc >= 0x800cf180u && cpu->pc < 0x800cf290u)
        instruction = kOverlay800CF180Words[(cpu->pc - 0x800cf180u) / 4u];
    else
        return 0;
    *out = instruction;
    return 1;
}

int musashi_boot_cpu_context(const void *continuation,
    MusashiCpuContextProvenance provenance, MusashiCpuContext *out) {
    const FormatterCpu *cpu = continuation;
    MusashiCpuContext context = {0};
    if (!cpu || !out ||
        (provenance != MUSASHI_CPU_CONTEXT_SOURCE &&
         provenance != MUSASHI_CPU_CONTEXT_HOST_BIOS_SERVICE)) return 0;
    context.identity = continuation;
    context.gpr = cpu->r;
    context.provenance = provenance;
    if (provenance == MUSASHI_CPU_CONTEXT_SOURCE) {
        if ((cpu->pc & 3u) || !formatter_fetch(cpu, &context.instruction) ||
            cpu->delay_slot > 1u ||
            (cpu->delay_slot && cpu->pc != cpu->branch_pc + 4u) ||
            (!cpu->delay_slot && cpu->branch_pc)) return 0;
        context.instruction_valid = 1;
        context.pc = cpu->pc;
        context.npc = cpu->npc;
        context.delay_slot = cpu->delay_slot;
        context.branch_pc = cpu->branch_pc;
    }
    *out = context;
    return 1;
}

int musashi_boot_continuation_host_context(const void *continuation,
    MusashiCpuContext *out) {
    const FormatterCpu *cpu = continuation;
    const MusashiCallbackDevice *callback;
    const MusashiCdDevice *cd;
    const MusashiInputDevice *input;
    const MusashiEventDevice *event;
    int accepted = 0;
    if (!cpu || !out || cpu->gte_load_pending || cpu->npc != cpu->pc + 4u ||
        cpu->delay_slot || cpu->branch_pc) return 0;
    callback = cpu->callback_device;
    cd = cpu->cd_device;
    input = cpu->input_device;
    event = cpu->event_device;
    switch (cpu->pc) {
    case FORMATTER_CONSOLE_CHAR: case FORMATTER_SEARCH:
    case FORMATTER_STRING_LENGTH: case RESETGRAPH_FILL:
    case CALLBACK_CLEAR: case CALLBACK_INSTALLER_CLEAR:
    case CALLBACK_CHANNEL_CLEAR: case STARTUP_ENVIRONMENT_CLEAR:
    case STARTUP_CLEAR_29044: case STARTUP_CLEAR_2906C:
    case STARTUP_CLEAR_29094: case STARTUP_CLEAR_29218:
    case STARTUP_RECORD_CLEAR: case CD_INITIALIZER_STRING_EMIT:
    case 0x80043060u:
        accepted = 1; break;
    case CALLBACK_REGISTER_WRAPPER:
        accepted = callback && callback->registration_device; break;
    case INPUT_C0_3:
        accepted = input && input->dequeue_irq_result; break;
    case INPUT_C0_2:
        accepted = input && input->enqueue_irq_result; break;
    case INPUT_C0_0A:
        accepted = input && input->change_timer_result; break;
    case 0x8005ce78u: accepted = event && event->open_event; break;
    case 0x8005ceb8u: accepted = event && event->enable_event; break;
    case 0x8005cea8u: accepted = event && event->b0_0b; break;
    case CD_B0_5B: accepted = cd && cd->b0_5b; break;
    case CD_B0_4A: accepted = cd && cd->b0_4a; break;
    case CD_B0_4B: accepted = cd && cd->b0_4b; break;
    case CD_A0_70: accepted = cd && cd->a0_70; break;
    case RESETGRAPH_GPU_CW:
        accepted = callback && callback->gpu_cw; break;
    case RESETGRAPH_DEVICE_RESET:
        accepted = callback && callback->reset_device; break;
    case CALLBACK_BIOS_B0_19:
        accepted = callback && callback->hook_entry_int; break;
    case CALLBACK_BIOS_A0_72:
        accepted = callback && callback->a0_72; break;
    case 0xb0u:
        accepted = cpu->r[9] == 0x56u && cpu->r[10] == 0xb0u &&
            cpu->r[31] == 0x8004d188u && cpu->bios_image && cpu->bios_image->table;
        break;
    case 0xa0u:
        if (cpu->r[10] != 0xa0u) break;
        accepted = (cpu->r[9] == 0x44u && cpu->r[31] == 0x8004d1b8u &&
                    cpu->bios_image && cpu->bios_image->publish) ||
                   (cpu->r[9] == 0x39u && cpu->r[31] == 0x80014948u &&
                    cpu->heap_device && cpu->heap_device->init_heap);
        break;
    default: break;
    }
    return accepted && musashi_boot_cpu_context(continuation,
        MUSASHI_CPU_CONTEXT_HOST_BIOS_SERVICE, out);
}

/* MFC2 load-delay successors. The delay-slot instruction runs with the
 * loaded value still pending; the value publishes to its register before
 * the successor executes. Only exact admitted (register, PC, word) triples
 * retire a pending load, and every successor is audited not to consume the
 * pending register. Sources are the 80047D48 leaf (into v0), the three
 * 80048D9C back-to-back MFC2 runs (into t3..t1), and the two 800484EC MAC
 * runs (into t3..t5 and t0..t2); consecutive MFC2s each publish in turn so
 * no value is lost. */
static int gte_load_successor(uint8_t reg, uint32_t pc, uint32_t word) {
    static const struct { uint8_t reg; uint32_t pc, word; } successors[] = {
        {2, 0x80049470u, 0x48035000u},
        {3, 0x80049474u, 0xe8ab0004u},
        {2, 0x80049484u, 0x03e00008u},
        {2, 0x80047d4cu, 0x24010020u},
        {11, 0x80048e04u, 0x480c5000u},
        {12, 0x80048e08u, 0x480d5800u},
        {13, 0x80048e0cu, 0x48880000u},
        {14, 0x80048e38u, 0x480f5000u},
        {15, 0x80048e3cu, 0x48185800u},
        {24, 0x80048e40u, 0x48880000u},
        {8, 0x80048e74u, 0x48095000u},
        {9, 0x80048e78u, 0x3108ffffu},
        {11, 0x800485b0u, 0x480cd000u},
        {12, 0x800485b4u, 0x480dd800u},
        {13, 0x800485b8u, 0x48884800u},
        {8, 0x80048624u, 0x4809d000u},
        {9, 0x80048628u, 0x480ad800u},
        {10, 0x8004862cu, 0x010b4021u}
    };
    unsigned i;
    for (i = 0; i < sizeof(successors)/sizeof(successors[0]); ++i)
        if (successors[i].reg == reg && successors[i].pc == pc &&
            successors[i].word == word) return 1;
    return 0;
}

/* 80048D9C COP2 sites: (PC, word, slot). Slot 0 is MTC2 into V0/V1 via
 * write_data, slot 1 is MFC2 out of IR1/IR2/IR3 via read_data, slot 2 is
 * the MVMVA vector core via command. Callers are the six audited JAL
 * sites bound by gte_48d9c_caller; the slot function must be bound too. */
static int gte_48d9c_caller(uint32_t ra) {
    return ra == 0x8002c520u || ra == 0x80052edcu || ra == 0x80053080u ||
           ra == 0x80053bbcu || ra == 0x80054138u || ra == 0x800541ecu;
}

static int gte_47d3c_caller(uint32_t ra) {
    return ra == 0x80054050u || ra == 0x800540d8u || ra == 0x800533e4u;
}

static int gte_48d9c_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const struct { uint32_t pc, word; uint8_t slot; } sites[] = {
        {0x80048ddcu, 0x48880000u, 0}, {0x80048de0u, 0x488a0800u, 0},
        {0x80048e0cu, 0x48880000u, 0}, {0x80048e10u, 0x488a0800u, 0},
        {0x80048e40u, 0x48880000u, 0}, {0x80048e44u, 0x488a0800u, 0},
        {0x80048e00u, 0x480b4800u, 1}, {0x80048e04u, 0x480c5000u, 1},
        {0x80048e08u, 0x480d5800u, 1}, {0x80048e34u, 0x480e4800u, 1},
        {0x80048e38u, 0x480f5000u, 1}, {0x80048e3cu, 0x48185800u, 1},
        {0x80048e70u, 0x48084800u, 1}, {0x80048e74u, 0x48095000u, 1},
        {0x80048de8u, 0x4a486012u, 2}, {0x80048e18u, 0x4a486012u, 2},
        {0x80048e4cu, 0x4a486012u, 2}
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == word) {
            *slot = sites[i].slot;
            return 1;
        }
    return 0;
}

/* 800484EC COP2 sites: same slot convention (0=MTC2 write_data, 1=MFC2
 * read_data, 2=MVMVA command). MTC2 targets IR1/IR2/IR3, MFC2 sources
 * MAC1/MAC2/MAC3, and both MVMVA words use vector=IR (v=3) with zero
 * translation (cv=3). Callers are the ten EXE JAL sites plus the ten
 * SC02 member31 JAL return aliases when that overlay is selected. */
static int gte_484ec_caller(uint32_t ra) {
    return ra == 0x80013678u || ra == 0x800139acu || ra == 0x80013ce0u ||
           ra == 0x80014158u || ra == 0x800141e0u || ra == 0x8002c58cu ||
           ra == 0x80052f64u || ra == 0x80052ff0u || ra == 0x80053074u ||
           ra == 0x80054224u ||
           /* SC02 member31 JAL return aliases into the same leaf. */
           (g_overlay_sc02_0031_words &&
            (ra == 0x8012b168u || ra == 0x8012b1a4u || ra == 0x8012b1d4u ||
             ra == 0x8012f1c0u || ra == 0x80147e24u || ra == 0x80147ec8u ||
             ra == 0x80148118u || ra == 0x80163078u || ra == 0x80163148u ||
             ra == 0x801631e8u));
}

static int gte_484ec_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const struct { uint32_t pc, word; uint8_t slot; } sites[] = {
        {0x80048598u, 0x488b4800u, 0}, {0x8004859cu, 0x488c5000u, 0},
        {0x800485a0u, 0x488d5800u, 0}, {0x800485b8u, 0x48884800u, 0},
        {0x800485bcu, 0x48895000u, 0}, {0x800485c0u, 0x488a5800u, 0},
        {0x800485acu, 0x480bc800u, 1}, {0x800485b0u, 0x480cd000u, 1},
        {0x800485b4u, 0x480dd800u, 1}, {0x80048620u, 0x4808c800u, 1},
        {0x80048624u, 0x4809d000u, 1}, {0x80048628u, 0x480ad800u, 1},
        {0x800485a8u, 0x4a41e012u, 2}, {0x800485c8u, 0x4a49e012u, 2}
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == word) {
            *slot = sites[i].slot;
            return 1;
        }
    return 0;
}

/* Stepper-side check: a pending MFC2 load may only survive across loop
 * iterations when the loop has reached an admitted delay-slot successor;
 * the word itself is rechecked inside the step. */
static int gte_load_successor_pc(uint32_t pc) {
    static const uint32_t pcs[] = {
        0x80049470u, 0x80049474u, 0x80049484u,
        0x80047d4cu,
        0x80048e04u, 0x80048e08u, 0x80048e0cu,
        0x80048e38u, 0x80048e3cu, 0x80048e40u,
        0x80048e74u, 0x80048e78u,
        0x800485b0u, 0x800485b4u, 0x800485b8u,
        0x80048624u, 0x80048628u, 0x8004862cu
    };
    unsigned i;
    for (i = 0; i < sizeof(pcs)/sizeof(pcs[0]); ++i)
        if (pcs[i] == pc) return 1;
    return 0;
}

static int sc02_entry_matches(MusashiBootMemory *memory) {
    unsigned i;
    uint32_t loaded;
    for (i = 0; i < sizeof(kOverlaySc02_80128158Words) / sizeof(uint32_t); ++i) {
        if (!musashi_boot_read32(memory, 0x80128158u + 4u*i, &loaded) ||
            loaded != kOverlaySc02_80128158Words[i]) return 0;
    }
    return 1;
}

static int formatter_step(MusashiBootMemory *memory, FormatterCpu *cpu) {
    uint32_t instruction, opcode, rs, rt, rd, immediate, old_npc;
    uint32_t target_npc;
    int16_t signed_immediate;
    uint8_t byte;
    uint16_t half;
    int merge_kind;
    int schedule_merge = 0;
    int schedule_gte_load = 0;
    uint32_t scheduled_gte_load = 0;
    FormatterCpu pending_gte_cpu;
    int restore_pending_gte = 0;
    uint32_t scheduled_merge = 0;
    uint32_t scheduled_next_pc = 0;
    uint8_t scheduled_merge_reg = 0;
    if ((cpu->pc & 3u) || !spu_source_guard(memory, cpu))
        return 0;
    /* 8005F704 words still return 80088A48+(a0&0xF0). After 8005F0C8,
     * D_80072990 is the InitPAD PadInfo (80078A48); PadGetState jalrs
     * this getter. Use the live record (identity when 72990==80088A48). */
    if (cpu->pc == 0x8005f704u) {
        uint32_t base = 0;
        if (musashi_boot_read32(memory, 0x80072990u, &base) && base != 0) {
            cpu->r[2] = base + (cpu->r[4] & 0xf0u);
            cpu->pc = cpu->r[31];
            cpu->npc = cpu->r[31] + 4u;
        }
    }
    if (cpu->pc == 0x80128158u)
        g_overlay_sc02_0031_words = sc02_entry_matches(memory);
    if (!formatter_fetch(cpu, &instruction)) return 0;
    if ((cpu->pc >= 0x80128158u && cpu->pc < 0x801fff00u) ||
        (g_overlay_0004_words && cpu->pc >= 0x800cedf8u && cpu->pc < 0x80100000u) ||
        (g_overlay_0010_words && ((cpu->pc >= 0x800d0630u && cpu->pc < 0x800d0694u) ||
                                  (cpu->pc >= 0x800d02c0u && cpu->pc < 0x800d02d0u) ||
                                  (cpu->pc >= 0x800d1e20u && cpu->pc < 0x800d1e28u) ||
                                  (cpu->pc >= 0x800d18dcu && cpu->pc < 0x800d1938u) ||
                                  (cpu->pc >= 0x800d1938u && cpu->pc < 0x800d1984u) ||
                                  (cpu->pc >= 0x800d1984u && cpu->pc < 0x800d19dcu) ||
                                  (cpu->pc >= 0x800d1f58u && cpu->pc < 0x800d1f90u) ||
                                  (cpu->pc >= 0x800d0588u && cpu->pc < 0x800d0630u) ||
                                  (cpu->pc >= 0x800cf854u && cpu->pc < 0x800cf864u)))) {
        uint32_t loaded;
        if (!musashi_boot_read32(memory,cpu->pc,&loaded)) return 0;
        if (loaded != instruction) {
            fprintf(stderr,"native_boot: OVERLAY_WORD_MISMATCH pc=%08x expected=%08x loaded=%08x\n",
                    cpu->pc,instruction,loaded);
            return 0;
        }
    }
    if (cpu->gte_load_pending &&
        (cpu->merge_pending || cpu->gte_load_next_pc != cpu->pc ||
         cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc ||
         !gte_load_successor(cpu->gte_load_reg, cpu->pc, instruction))) return 0;
    opcode = instruction >> 26;
    if (cpu->delay_slot &&
        ((opcode >= 1u && opcode <= 7u) ||
         (opcode == 0u && ((instruction & 63u) == 8u ||
                          (instruction & 63u) == 9u))))
        return 0; /* Branch in a delay slot has no supported CPU semantics. */
    rs = (instruction >> 21) & 31u;
    rt = (instruction >> 16) & 31u;
    rd = (instruction >> 11) & 31u;
    immediate = instruction & 0xffffu;
    signed_immediate = (int16_t)immediate;
    if (opcode == 0u && (instruction & 63u) == 26u &&
        !((g_overlay_0004_words && cpu->pc == 0x800d257cu && instruction == 0x0043001au) ||
          (cpu->pc == 0x80052868u && instruction == 0x0065001au) ||
          (cpu->pc == 0x80054070u && instruction == 0x0212001au) ||
          (cpu->pc == 0x800540e0u && instruction == 0x00d2001au) ||
          (cpu->pc == 0x80054154u && instruction == 0x00b2001au) ||
          (cpu->pc == 0x80054194u && instruction == 0x00d2001au) ||
          (cpu->pc == 0x8005343cu && instruction == 0x0044001au) ||
          (cpu->pc == 0x80053480u && instruction == 0x0044001au) ||
          (cpu->pc == 0x800534c4u && instruction == 0x00c4001au) ||
          (cpu->pc == 0x8005355cu && instruction == 0x0044001au) ||
          (cpu->pc == 0x800535a0u && instruction == 0x0044001au) ||
          (cpu->pc == 0x800535e4u && instruction == 0x00c4001au) ||
          (cpu->pc == 0x80053680u && instruction == 0x0044001au) ||
          (cpu->pc == 0x800536c4u && instruction == 0x0044001au) ||
          (cpu->pc == 0x80053708u && instruction == 0x00c4001au))) return 0;
    /* These optional debug-call branches have no admitted host target yet. */
    if (cpu->pc == 0x8005937cu || cpu->pc == 0x80059698u ||
        cpu->pc == 0x80059844u || cpu->pc == 0x8005986cu) return 0;
    if (cpu->pc == 0x80042598u) {
        uint32_t table, target;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x8006cb84u,&table) || table != 0x8006cb64u ||
            !musashi_boot_read32(memory,table+0xcu,&target) || target != 0x80042718u ||
            cpu->r[2] != target) return 0;
    }
    if (cpu->pc == 0x80059398u || cpu->pc == 0x800596d4u) {
        uint32_t table, target;
        const uint32_t offset=cpu->pc == 0x80059398u ? 0x34u : 0x10u;
        const uint32_t expected=cpu->pc == 0x80059398u ? 0x8005bd7cu : 0x8005b684u;
        /* The source-loaded device table must select the audited operation;
         * another mapped function is not an equivalent device capability. */
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+offset,&target) ||
            target != expected || cpu->r[2] != target)
            return 0;
        if (cpu->pc == 0x80059398u) {
            static const uint32_t pointers[4][2] = {
                {0x8006cb8cu,0x1f801074u}, {0x80072868u,0x1f8010a8u},
                {0x80072878u,0x1f8010f0u}, {0x8007285cu,0x1f801814u}
            };
            unsigned i;
            for (i=0;i<4u;++i)
                if (!musashi_boot_read32(memory,pointers[i][0],&target) ||
                    target != pointers[i][1]) return 0;
        }
    }
    if (cpu->pc == 0x80059dacu) return 0; /* Optional debug callback unbound. */
    if (cpu->pc == 0x8005a004u) return 0; /* Optional display debug callback. */
    if (cpu->pc == 0x8005a080u || cpu->pc == 0x8005a290u ||
        cpu->pc == 0x8005a2bcu || cpu->pc == 0x8005a428u) {
        uint32_t table, target;
        unsigned reg=(cpu->pc == 0x8005a290u || cpu->pc == 0x8005a2bcu) ? 3u : 2u;
        if (instruction != ((reg << 21) | 0x0000f809u) ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+0x10u,&target) || target != 0x8005b684u ||
            cpu->r[reg] != target) return 0;
    }
    if (cpu->pc == 0x8005b690u) {
        uint32_t address;
        if (instruction != 0xac440000u ||
            !musashi_boot_read32(memory,0x8007285cu,&address) ||
            address != 0x1f801814u || cpu->r[2] != address) return 0;
    }
    if (cpu->pc == 0x80059df4u) {
        uint32_t table, dispatch, callback;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+8u,&dispatch) || dispatch != 0x8005b7b0u ||
            !musashi_boot_read32(memory,table+0x18u,&callback) || callback != 0x8005b710u ||
            cpu->r[2] != dispatch || cpu->r[4] != callback ||
            cpu->r[5] != cpu->r[17]+0x1cu || cpu->r[6] != 0x40u ||
            ((cpu->r[5]&3u) || !musashi_boot_ram_span(memory,cpu->r[5],0x40u))) return 0;
    }
    if (cpu->pc == 0x8005b8bcu) {
        uint32_t callback;
        if (instruction != 0x0260f809u || cpu->r[4] != cpu->r[16] || (cpu->r[4]&3u)) return 0;
        if (cpu->r[19] == 0x8005b710u) {
            if (!musashi_boot_read32(memory,0x80072758u,&callback) || callback != cpu->r[19] ||
                cpu->r[18] != 0 || cpu->r[17] != 0x40u ||
                !musashi_boot_ram_span(memory,cpu->r[4],0x40u)) return 0;
        } else if (cpu->r[19] == 0x8005af68u) {
            uint32_t table, caller, rectangle, red_green, blue;
            if (!musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
                !musashi_boot_read32(memory,table+0xcu,&callback) || callback != cpu->r[19] ||
                cpu->r[17] != 8u || !musashi_boot_ram_span(memory,cpu->r[4],8u) ||
                !musashi_boot_read32(memory,cpu->r[29]+0x20u,&caller) || caller != 0x800598fcu ||
                !musashi_boot_read32(memory,cpu->r[29]+0x1cu,&rectangle) || rectangle != cpu->r[16] ||
                !musashi_boot_read32(memory,cpu->r[29]+0x10u,&red_green) ||
                !musashi_boot_read32(memory,cpu->r[29]+0x18u,&blue) ||
                ((red_green|blue)&0xff000000u) || cpu->r[18] != (red_green|blue)) return 0;
        } else return 0;
    }
    if (cpu->pc == 0x800598f4u) {
        uint32_t table, dispatch, callback;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+8u,&dispatch) || dispatch != 0x8005b7b0u ||
            !musashi_boot_read32(memory,table+0xcu,&callback) || callback != 0x8005af68u ||
            cpu->r[2] != dispatch || cpu->r[4] != callback || cpu->r[5] != cpu->r[19] ||
            cpu->r[6] != 8u || (cpu->r[5]&3u) ||
            !musashi_boot_ram_span(memory,cpu->r[5],8u)) return 0;
    }
    if (cpu->pc == 0x8005b154u || cpu->pc == 0x8005b090u) {
        uint32_t address;
        if (instruction != 0x8c440000u ||
            !musashi_boot_read32(memory,0x8007285cu,&address) ||
            address != 0x1f801814u || cpu->r[2] != address) return 0;
    }
    if (cpu->pc == 0x8005b870u || cpu->pc == 0x8005b8a4u ||
        cpu->pc == 0x8005b720u || cpu->pc == 0x8005b730u ||
        cpu->pc == 0x8005b740u || cpu->pc == 0x8005b750u) {
        uint32_t cell, expected, actual, word;
        unsigned reg=2;
        switch (cpu->pc) {
        case 0x8005b870u: cell=0x80072868u; expected=0x1f8010a8u; word=0x8c420000u; break;
        case 0x8005b8a4u: cell=0x8007285cu; expected=0x1f801814u; word=0x8c620000u; reg=3; break;
        case 0x8005b720u:
            cell=0x8007285cu; expected=0x1f801814u; word=0xac430000u;
            if (cpu->r[3] != 0x04000002u) return 0;
            break;
        case 0x8005b730u: cell=0x80072860u; expected=0x1f8010a0u; word=0xac440000u; break;
        case 0x8005b740u: cell=0x80072864u; expected=0x1f8010a4u; word=0xac400000u; break;
        default:
            cell=0x80072868u; expected=0x1f8010a8u; word=0xac430000u;
            if (cpu->r[3] != 0x01000401u) return 0;
            break;
        }
        if (instruction != word || !musashi_boot_read32(memory,cell,&actual) || actual != expected ||
            cpu->r[reg] != expected) return 0;
    }
    if (cpu->pc == 0x80042708u || cpu->pc == 0x8004270cu) {
        uint32_t address;
        if (!musashi_boot_read32(memory,0x8006cb8cu,&address) ||
            address != 0x1f801074u || cpu->r[3] != address) return 0;
    }
    if (cpu->pc == 0x80019b30u) {
        static const uint32_t targets[9] = {
            0x80019b38u,0x80019ba8u,0x80019bf8u,0x80019c3cu,
            0x80019c98u,0x80019da0u,0x80019e64u,0x80019f50u,0x80019fc4u
        };
        uint32_t state, table_target;
        if (instruction != 0x00400008u ||
            !musashi_boot_read32(memory,0x800ae6f0u,&state) ||
            state >= 9u || !targets[state] || cpu->r[3] != state ||
            !musashi_boot_read32(memory,0x80072a4cu+4u*state,&table_target) ||
            table_target != targets[state] || cpu->r[2] != table_target)
            return 0;
    }
    /* Audited directory and palette-copy signed-byte loads. Preflight RAM
     * before advancing time. Their successors do not consume the loaded
     * register until after the retail load-delay slot. */
    if (opcode == 32u) {
        int admitted = (cpu->pc == 0x80045b54u && instruction == 0x80633a1au) ||
            (g_overlay_sc02_0031_words &&
             ((cpu->pc == 0x8013d62cu && instruction == 0x802555a8u) ||
              (cpu->pc == 0x8013d674u && instruction == 0x80a20008u)));
        if (!admitted || !cpu_ram_span(memory, cpu,
                cpu->r[rs] + (uint32_t)(int32_t)signed_immediate, 1)) return 0;
    }
    if (cpu->pc == 0x8004d180u &&
        (instruction != 0x0140f809u || cpu->r[10] != 0xb0u)) return 0;
    if (cpu->pc == 0x8004d190u &&
        (instruction != 0x8c420018u || cpu->r[2] != 0x674u)) return 0;
    if (cpu->pc == 0x8004d1acu) {
        uint32_t offset = cpu->r[2] - 0xc84u;
        if (instruction != 0xac43fffcu || offset >= 56u || (offset & 3u) ||
            cpu->r[10] != 0x8004d1d8u + offset || cpu->r[9] != 0x8004d20cu)
            return 0;
    }
    if (opcode == 16u) {
        int geometry = (cpu->r[31] == 0x80053d08u || cpu->r[31] == 0x80014454u);
        int movie = g_overlay_0004_words && cpu->r[31] == 0x800d2764u;
        if (!cpu->cpu_transfer ||
            !((geometry && cpu->pc == 0x80047cd0u && instruction == 0x40026000u &&
               cpu->cpu_transfer->read_status) ||
              (geometry && cpu->pc == 0x80047cdcu && instruction == 0x40826000u &&
               cpu->cpu_transfer->write_status) ||
              (movie && cpu->pc == 0x800d3524u && instruction == 0x40096000u &&
               cpu->cpu_transfer->read_status) ||
              (movie && cpu->pc == 0x800d3534u && instruction == 0x40896000u &&
               cpu->cpu_transfer->write_status))) return 0;
    }
    if (opcode == 18u && rs != 6u) {
        /* Two admitted leaf callers: first RA54050 via JAL54048, second
         * RA540D8 via JAL540D0. Any other return alias stays refused.
         * The 80048D9C camera sites run under the six audited JAL return
         * aliases; a pending MFC2 load is fine there because the admitted
         * delay-slot successor above already published it. */
        unsigned slot = 99;
        int leaf = 0, camera = 0, camera2 = 0, transform = 0;
        if (cpu->cpu_transfer) {
            transform = g_overlay_sc02_0031_words && cpu->r[31] == 0x8012f188u &&
                (((cpu->pc == 0x8004946cu && instruction == 0x48024800u) ||
                  (cpu->pc == 0x80049470u && instruction == 0x48035000u)) ?
                     cpu->cpu_transfer->read_data != NULL :
                 (cpu->pc == 0x80049480u && instruction == 0x4842f800u) ?
                     cpu->cpu_transfer->read_control != NULL :
                 (cpu->pc == 0x80049468u && instruction == 0x4a480012u) &&
                     cpu->cpu_transfer->command != NULL);
            leaf = !cpu->gte_load_pending &&
                gte_47d3c_caller(cpu->r[31]) &&
                ((cpu->pc == 0x80047d3cu && instruction == 0x4884f000u &&
                  cpu->cpu_transfer->write_data) ||
                 (cpu->pc == 0x80047d48u && instruction == 0x4802f800u &&
                  cpu->cpu_transfer->read_data));
            camera = gte_48d9c_caller(cpu->r[31]) &&
                gte_48d9c_site(cpu->pc, instruction, &slot) &&
                (slot == 0 ? cpu->cpu_transfer->write_data != NULL :
                 slot == 1 ? cpu->cpu_transfer->read_data != NULL :
                             cpu->cpu_transfer->command != NULL);
            slot = 99;
            camera2 = gte_484ec_caller(cpu->r[31]) &&
                gte_484ec_site(cpu->pc, instruction, &slot) &&
                (slot == 0 ? cpu->cpu_transfer->write_data != NULL :
                 slot == 1 ? cpu->cpu_transfer->read_data != NULL :
                             cpu->cpu_transfer->command != NULL);
        }
        if (!cpu->cpu_transfer || cpu->merge_pending ||
            cpu->npc != cpu->pc+4u ||
            cpu->delay_slot || cpu->branch_pc ||
            (!leaf && !camera && !camera2 && !transform)) return 0;
    } else if (opcode == 18u) {
        static const uint32_t sites[][2] = {
            {0x80047ce8u,0x48c8e800u},{0x80047cf4u,0x48c8f000u},
            {0x80047d00u,0x48c8d000u},{0x80047d0cu,0x48c8d800u},
            {0x80047d18u,0x48c8e000u},{0x80047d20u,0x48c0c000u},
            {0x80047d24u,0x48c0c800u},{0x80053ae4u,0x48c4a800u},
            {0x80053ae8u,0x48c5b000u},{0x80053aecu,0x48c6b800u},
            {0x80049224u,0x48c4c000u},{0x80049228u,0x48c5c800u},
            {0x8004923cu,0x48c4d000u},{0x80048db0u,0x48c80000u},
            {0x80048db4u,0x48c90800u},{0x80048db8u,0x48ca1000u},
            {0x80048dbcu,0x48cb1800u},{0x80048dc0u,0x48cc2000u},
            {0x80048500u,0x48c80000u},{0x80048504u,0x48c90800u},
            {0x80048508u,0x48ca1000u},{0x8004850cu,0x48cb1800u},
            {0x80048510u,0x48cc2000u},{0x80049208u,0x48c46800u},
            {0x8004920cu,0x48c57000u},{0x80049210u,0x48c67800u},
            {0x800538d0u,0x48c88000u},{0x800538d4u,0x48c98800u},
            {0x800538d8u,0x48ca9000u},{0x800538dcu,0x48cb9800u},
            {0x800538e0u,0x48cca000u},
            {0x80049160u,0x48c80000u},{0x80049164u,0x48c90800u},
            {0x80049168u,0x48ca1000u},{0x8004916cu,0x48cb1800u},
            {0x80049170u,0x48cc2000u},{0x800491b8u,0x48c82800u},
            {0x800491bcu,0x48c93000u},{0x800491c0u,0x48ca3800u}
        };
        unsigned i;
        if (!cpu->cpu_transfer || !cpu->cpu_transfer->write_control) return 0;
        for (i=0;i<sizeof(sites)/sizeof(sites[0]);++i)
            if (sites[i][0]==cpu->pc && sites[i][1]==instruction) break;
        if (i==sizeof(sites)/sizeof(sites[0])) return 0;
        if (i < 7u) {
            /* Both retail InitGeom callers share the persistent CPU/GTE
             * owners and run the instruction-image publication themselves. */
            if (cpu->r[31] != 0x80053d08u && cpu->r[31] != 0x80014454u) return 0;
        } else if (i == 12u) {
            if (cpu->r[31] != 0x80014468u && cpu->r[31] != 0x80053318u) return 0;
        } else if (i < 13u) {
            if (cpu->r[31] !=
                (i < 10u ? 0x80053d18u : 0x80053d24u)) return 0;
        } else if (i < 18u) {
            if (!gte_48d9c_caller(cpu->r[31])) return 0;
        } else if (i < 23u) {
            if (!gte_484ec_caller(cpu->r[31])) return 0;
        } else if (i < 26u) {
            if (cpu->r[31] != 0x80053b10u) return 0;
        } else if (i < 31u) {
            if (cpu->r[31] != 0x8005385cu) return 0;
        } else if (!g_overlay_sc02_0031_words ||
                   cpu->r[31] != (i < 36u ? 0x8012f170u : 0x8012f178u) ||
                   cpu->merge_pending || cpu->gte_load_pending ||
                   cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc) return 0;
    }
    if (opcode == 50u || (opcode == 58u && cpu->pc == 0x80049474u)) {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        int load = opcode == 50u;
        if (!g_overlay_sc02_0031_words || cpu->r[31] != 0x8012f188u ||
            !cpu->cpu_transfer || cpu->merge_pending ||
            cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc ||
            (address & 3u) || !cpu_ram_span(memory, cpu, address, 4u) ||
            (load ? (!cpu->cpu_transfer->write_data ||
                     !((cpu->pc == 0x8004945cu && instruction == 0xc8800000u) ||
                       (cpu->pc == 0x80049460u && instruction == 0xc8810004u))) :
                    (!cpu->cpu_transfer->read_data || instruction != 0xe8ab0004u))) return 0;
    } else if (opcode == 58u) {
        /* Sole admitted SWC2: the 80048E98 store of light-matrix control
         * 11 under an audited 80048D9C caller. No pending MFC2 load may
         * be live: every 48D9C load retires at its admitted successor. */
        if (!cpu->cpu_transfer || cpu->merge_pending || cpu->gte_load_pending ||
            !gte_48d9c_caller(cpu->r[31]) ||
            cpu->npc != cpu->pc+4u ||
            cpu->delay_slot || cpu->branch_pc ||
            cpu->pc != 0x80048e98u || instruction != 0xe88b0010u ||
            !cpu->cpu_transfer->read_control) return 0;
    }
    merge_kind = merge_kind_for(cpu->pc, instruction);
    if ((opcode == 34u || opcode == 38u || opcode == 42u || opcode == 46u) &&
        merge_kind == MERGE_NONE)
        return 0;
    if (!merge_pending_matches(cpu, instruction))
        return 0;
    if (merge_kind == MERGE_LWL || merge_kind == MERGE_LWR ||
        merge_kind == MERGE_SWL || merge_kind == MERGE_SWR) {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        if (!merge_memory_available(memory, cpu, merge_kind, address))
            return 0;
    }
    if (cpu->clock) {
        /* PCSX-Redux psxinterpreter.cc execBlock: BIAS=2. Its memory
         * read/write entry points add one cycle for an actual data access.
         * Count source delay slots normally. Host intrinsics are outside
         * this relative profile, and an unavailable clock fails closed. */
        uint32_t cost = 2u;
        if (opcode == 32u || opcode == 33u || opcode == 35u || opcode == 36u || opcode == 37u ||
            opcode == 40u || opcode == 41u || opcode == 43u || opcode == 50u || opcode == 58u) ++cost;
        if (merge_kind == MERGE_LWL || merge_kind == MERGE_LWR) ++cost;
        if (merge_kind == MERGE_SWL || merge_kind == MERGE_SWR) cost += 2u;
        if (!cpu->clock->advance || !cpu->clock->advance(cpu->clock->userdata, cost) ||
            (cpu->cd_irq_frame && cpu->cd_irq_frame->faulted))
            return 0;
    }
    if (cpu->gte_load_pending) {
        /* Device refusal must leave the preceding load pending for retry. */
        pending_gte_cpu = *cpu;
        restore_pending_gte = 1;
        /* Every gate above passed, so this is an admitted delay-slot
         * successor: publish the pending MFC2 value before executing it.
         * Publishing here (after clock and all refusal gates) keeps the
         * pinned contract that any refusal leaves the whole CPU unchanged.
         * A successor that is itself an MFC2 schedules its own fresh
         * pending load in the epilogue below. */
        if (cpu->gte_load_reg) cpu->r[cpu->gte_load_reg] = cpu->gte_load_value;
        cpu->gte_load_value = 0;
        cpu->gte_load_next_pc = 0;
        cpu->gte_load_reg = 0;
        cpu->gte_load_pending = 0;
    }
    old_npc = cpu->npc;
    target_npc = old_npc + 4u;

    switch (opcode) {
    case 0:
        switch (instruction & 63u) {
        case 0: cpu->r[rd] = cpu->r[rt] << ((instruction >> 6) & 31u); break;
        case 2: cpu->r[rd] = cpu->r[rt] >> ((instruction >> 6) & 31u); break;
        case 3: cpu->r[rd] = formatter_sra(cpu->r[rt],
                                            (instruction >> 6) & 31u); break;
        case 4: cpu->r[rd] = cpu->r[rt] << (cpu->r[rs] & 31u); break;
        case 6: cpu->r[rd] = cpu->r[rt] >> (cpu->r[rs] & 31u); break;
        case 7: {
            /* SRAV serves only the 47D8C table-index shift of the camera
             * sqrt leaf; signed variable shifts elsewhere stay refused. */
            uint32_t amount;
            if (cpu->pc != 0x80047d8cu || instruction != 0x01646007u ||
                !gte_47d3c_caller(cpu->r[31])) return 0;
            amount = cpu->r[rs] & 31u;
            cpu->r[rd] = formatter_sra(cpu->r[rt], amount);
            break;
        }
        case 8: target_npc = cpu->r[rs]; break;
        case 9: cpu->r[rd] = cpu->pc + 8u; target_npc = cpu->r[rs]; break;
        case 13: return 0;
        case 16: cpu->r[rd] = cpu->hi; break;
        case 18: cpu->r[rd] = cpu->lo; break;
        case 24: {
            /* Signed MULT, used by retail track-number BCD conversion.
             * Widen before subtracting2^32; avoid implementation-defined
             * uint32-to-int32 conversions and signed right shifts. */
            int64_t lhs = cpu->r[rs], rhs = cpu->r[rt];
            uint64_t product;
            if (cpu->r[rs] & 0x80000000u) lhs -= INT64_C(4294967296);
            if (cpu->r[rt] & 0x80000000u) rhs -= INT64_C(4294967296);
            product = (uint64_t)(lhs * rhs);
            cpu->lo = (uint32_t)product;
            cpu->hi = (uint32_t)(product >> 32);
            break;
        }
        case 25: {
            /* MULTU retains the full unsigned 32-by-32-bit product. */
            uint64_t product = (uint64_t)cpu->r[rs] * cpu->r[rt];
            cpu->lo = (uint32_t)product;
            cpu->hi = (uint32_t)(product >> 32);
            break;
        }
        case 26: {
            const MusashiMipsDivResult result = musashi_mips_signed_div(cpu->r[rs], cpu->r[rt]);
            cpu->hi = result.hi; cpu->lo = result.lo;
            break;
        }
        case 27:
            if (!cpu->r[rt]) return 0;
            cpu->lo = cpu->r[rs] / cpu->r[rt]; cpu->hi = cpu->r[rs] % cpu->r[rt]; break;
        case 32: {
            /* Retail movie VLC arithmetic uses trapping ADD. Refuse an
             * overflow before publishing the destination register. */
            int64_t sum = (int64_t)(int32_t)cpu->r[rs] +
                          (int64_t)(int32_t)cpu->r[rt];
            if (sum < INT32_MIN || sum > INT32_MAX) return 0;
            cpu->r[rd] = (uint32_t)sum;
            break;
        }
        case 33: cpu->r[rd] = cpu->r[rs] + cpu->r[rt]; break;
        case 34: {
            /* Trapping SUB serves the camera sqrt and movie VLC sites;
             * signed overflow traps fail closed instead of wrapping. */
            int64_t diff;
            if (!((g_overlay_0004_words && cpu->pc >= 0x800d3234u &&
                   cpu->pc < 0x800d3540u) ||
                  (((cpu->pc == 0x80047d68u && instruction == 0x012a4822u) ||
                    (cpu->pc == 0x80047d88u && instruction == 0x016a5822u)) &&
                   gte_47d3c_caller(cpu->r[31])))) return 0;
            diff = (int64_t)(int32_t)cpu->r[rs] - (int64_t)(int32_t)cpu->r[rt];
            if (diff < INT32_MIN || diff > INT32_MAX) return 0;
            cpu->r[rd] = (uint32_t)(int32_t)diff;
            break;
        }
        case 35: cpu->r[rd] = cpu->r[rs] - cpu->r[rt]; break;
        case 36: cpu->r[rd] = cpu->r[rs] & cpu->r[rt]; break;
        case 37: cpu->r[rd] = cpu->r[rs] | cpu->r[rt]; break;
        case 38: cpu->r[rd] = cpu->r[rs] ^ cpu->r[rt]; break;
        case 39: cpu->r[rd] = ~(cpu->r[rs] | cpu->r[rt]); break;
        case 42: cpu->r[rd] = (int32_t)cpu->r[rs] < (int32_t)cpu->r[rt]; break;
        case 43: cpu->r[rd] = cpu->r[rs] < cpu->r[rt]; break;
        default: return 0;
        }
        break;
    case 1:
        if ((instruction & 0x001f0000u) == 0) { if ((int32_t)cpu->r[rs] < 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); }
        else if ((instruction & 0x001f0000u) == 0x00010000u) { if ((int32_t)cpu->r[rs] >= 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); }
        else return 0;
        break;
    case 2: target_npc = (cpu->pc + 4u & 0xf0000000u) | ((instruction & 0x03ffffffu) << 2); break;
    case 3: cpu->r[31] = cpu->pc + 8u; target_npc = (cpu->pc + 4u & 0xf0000000u) | ((instruction & 0x03ffffffu) << 2); break;
    case 4: if (cpu->r[rs] == cpu->r[rt]) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 5: if (cpu->r[rs] != cpu->r[rt]) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 6: if ((int32_t)cpu->r[rs] <= 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 7: if ((int32_t)cpu->r[rs] > 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 8: {
        int64_t sum = (int64_t)(int32_t)cpu->r[rs] + signed_immediate;
        if (sum < INT32_MIN || sum > INT32_MAX) return 0;
        cpu->r[rt] = (uint32_t)sum;
        break;
    }
    case 9: cpu->r[rt] = cpu->r[rs] + (int32_t)signed_immediate; break;
    case 10: cpu->r[rt] = (int32_t)cpu->r[rs] < (int32_t)signed_immediate; break;
    case 11: cpu->r[rt] = cpu->r[rs] < immediate; break;
    case 12: cpu->r[rt] = cpu->r[rs] & immediate; break;
    case 13: cpu->r[rt] = cpu->r[rs] | immediate; break;
    case 14: cpu->r[rt] = cpu->r[rs] ^ immediate; break;
    case 15: cpu->r[rt] = immediate << 16; break;
    case 16: {
        MusashiCpuContext context;
        uint32_t value;
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context)) return 0;
        if (rs == 0u) {
            if (!cpu->cpu_transfer->read_status(cpu->cpu_transfer->userdata, &context, &value)) return 0;
            cpu->r[rt] = value;
        } else if (!cpu->cpu_transfer->write_status(cpu->cpu_transfer->userdata,
                                                    &context, cpu->r[rt])) return 0;
        break;
    }
    case 18: {
        MusashiCpuContext context;
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context)) goto gte_transfer_refused;
        if (rs == 6u) {
            if (!cpu->cpu_transfer->write_control(cpu->cpu_transfer->userdata,
                                                &context, rd, cpu->r[rt])) goto gte_transfer_refused;
        } else if (rs == 4u) {
            if (!cpu->cpu_transfer->write_data(cpu->cpu_transfer->userdata,
                                             &context, rd, cpu->r[rt])) goto gte_transfer_refused;
        } else if (rs == 2u) {
            if (!cpu->cpu_transfer->read_control(cpu->cpu_transfer->userdata,
                                                &context, rd, &scheduled_gte_load)) goto gte_transfer_refused;
            schedule_gte_load = 1;
        } else if (rs == 18u) {
            /* Admitted MVMVA sites run the shared operator synchronously, no load
             * delay since later MFC2 reads observe the live bank. */
            if (!cpu->cpu_transfer->command(cpu->cpu_transfer->userdata,
                                            &context, instruction)) goto gte_transfer_refused;
        } else {
            if (!cpu->cpu_transfer->read_data(cpu->cpu_transfer->userdata,
                                            &context, rd, &scheduled_gte_load)) goto gte_transfer_refused;
            schedule_gte_load = 1;
        }
        break;
    }
    case 32:
        if (!cpu_read8(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &byte)) return 0;
        cpu->r[rt] = byte < 128u ? byte : 0xffffff00u | byte;
        break;
    case 33:
        if (!cpu_read16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &half)) return 0;
        cpu->r[rt] = (uint32_t)(int32_t)(int16_t)half; break;
    case 35:
        if (!cpu_read32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &cpu->r[rt])) return 0;
        break;
    case 36:
        if (!cpu_read8(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &byte)) return 0;
        cpu->r[rt] = byte; break;
    case 37:
        if (!cpu_read16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &half)) return 0;
        cpu->r[rt] = half; break;
    case 34: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        uint32_t prior = cpu->r[rt];
        if (merge_kind != MERGE_LWL ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value)) return 0;
        if (cpu->merge_pending && cpu->merge_reg == rt)
            prior = cpu->merge_value;
        scheduled_merge = merge_lwl_value(memory_value, prior, address & 3u);
        scheduled_next_pc = cpu->pc + 4u;
        scheduled_merge_reg = (uint8_t)rt;
        schedule_merge = 1;
        break;
    }
    case 38: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        uint32_t prior = cpu->r[rt];
        if (merge_kind != MERGE_LWR ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value)) return 0;
        if (cpu->merge_pending && cpu->merge_reg == rt)
            prior = cpu->merge_value;
        scheduled_merge = merge_lwr_value(memory_value, prior, address & 3u);
        scheduled_next_pc = cpu->pc + 4u;
        scheduled_merge_reg = (uint8_t)rt;
        schedule_merge = 1;
        break;
    }
    case 42: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        if (merge_kind != MERGE_SWL ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value) ||
            !cpu_write32(memory, cpu, address & ~3u,
                         merge_swl_value(memory_value, cpu->r[rt], address & 3u)))
            return 0;
        break;
    }
    case 46: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        if (merge_kind != MERGE_SWR ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value) ||
            !cpu_write32(memory, cpu, address & ~3u,
                         merge_swr_value(memory_value, cpu->r[rt], address & 3u)))
            return 0;
        break;
    }
    case 40: {
        uint32_t address = cpu->r[rs] + (int32_t)signed_immediate;
        if (!cpu_write8(memory, cpu, address, cpu->r[rt])) return 0;
        break;
    }
    case 41: if (!cpu_write16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, (uint16_t)cpu->r[rt])) return 0; break;
    case 43: if (!cpu_write32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, cpu->r[rt])) return 0; break;
    case 50: {
        MusashiCpuContext context;
        uint32_t value;
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context) ||
            !cpu_read32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &value) ||
            !cpu->cpu_transfer->write_data(cpu->cpu_transfer->userdata, &context, rt, value)) return 0;
        break;
    }
    case 58: {
        MusashiCpuContext context;
        uint32_t control;
        /* The SC02 transform stores data IR3; the earlier admitted site
         * retains its separate control-bank transfer. */
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context)) goto gte_transfer_refused;
        if (cpu->pc == 0x80049474u) {
            if (!cpu->cpu_transfer->read_data(cpu->cpu_transfer->userdata,
                                             &context, rt, &control)) goto gte_transfer_refused;
        } else if (!cpu->cpu_transfer->read_control(cpu->cpu_transfer->userdata,
                                                   &context, rt, &control)) goto gte_transfer_refused;
        if (!cpu_write32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, control)) goto gte_transfer_refused;
        break;
    }
    default: return 0;
    }
    if (schedule_gte_load) {
        cpu->gte_load_value = scheduled_gte_load;
        cpu->gte_load_next_pc = old_npc;
        cpu->gte_load_reg = (uint8_t)rt;
        cpu->gte_load_pending = 1;
    } else if (cpu->gte_load_pending) {
        cpu->r[cpu->gte_load_reg] = cpu->gte_load_value;
        cpu->gte_load_value = 0;
        cpu->gte_load_next_pc = 0;
        cpu->gte_load_reg = 0;
        cpu->gte_load_pending = 0;
    }
    if (schedule_merge) {
        /* The source's two-slot delayed-load behavior makes the older
         * partial result visible at the adjacent LWR boundary while the
         * replacement remains pending for the following NOP. */
        if (cpu->merge_pending)
            cpu->r[cpu->merge_reg] = cpu->merge_value;
        cpu->merge_value = scheduled_merge;
        cpu->merge_next_pc = scheduled_next_pc;
        cpu->merge_reg = scheduled_merge_reg;
        cpu->merge_kind = (uint8_t)merge_kind;
        cpu->merge_pending = 1;
    } else if (cpu->merge_pending) {
        cpu->r[cpu->merge_reg] = cpu->merge_value;
        cpu->merge_pending = 0;
        cpu->merge_kind = MERGE_NONE;
    }
    cpu->r[0] = 0;
    cpu->delay_slot = (uint8_t)((opcode >= 1u && opcode <= 7u) ||
        (opcode == 0u && ((instruction & 63u) == 8u || (instruction & 63u) == 9u)));
    cpu->branch_pc = cpu->delay_slot ? cpu->pc : 0u;
    cpu->pc = old_npc;
    cpu->npc = target_npc;
    return 1;

gte_transfer_refused:
    if (restore_pending_gte) *cpu = pending_gte_cpu;
    return 0;
}

int musashi_boot_format_8005c640(MusashiBootMemory *memory,
                                 uint32_t format_address,
                                 uint32_t argument_words_address,
                                 MusashiConsoleSink sink, void *userdata,
                                 int32_t *result) {
    FormatterCpu cpu;
    FormatterConsoleContext console;
    unsigned step;
    _Static_assert(sizeof(kFormatter8005C640Words) / sizeof(kFormatter8005C640Words[0]) == 418,
                   "8005C640 instruction stream changed");
    _Static_assert(sizeof(kFormatter8005C604Words) / sizeof(kFormatter8005C604Words[0]) == 15,
                   "8005C604 instruction stream changed");
    _Static_assert(sizeof(kResetGraph80059234Words) / sizeof(kResetGraph80059234Words[0]) == 97,
                   "80059234 instruction stream changed");
    _Static_assert(sizeof(kCallbackWrapper80042580Words) / sizeof(kCallbackWrapper80042580Words[0]) == 12,
                   "80042580 instruction stream changed");
    _Static_assert(sizeof(kCallbackDispatch80042644Words) / sizeof(kCallbackDispatch80042644Words[0]) == 12,
                   "80042644 instruction stream changed");
    _Static_assert(sizeof(kCallbackInitializer80042718Words) / sizeof(kCallbackInitializer80042718Words[0]) == 55,
                   "80042718 instruction stream changed");
    _Static_assert(sizeof(kCallbackInstaller80042C90Words) / sizeof(kCallbackInstaller80042C90Words[0]) == 22,
                   "80042C90 instruction stream changed");
    _Static_assert(sizeof(kCallbackSlotWrite80042D60Words) / sizeof(kCallbackSlotWrite80042D60Words[0]) == 11,
                   "80042D60 instruction stream changed");
    _Static_assert(sizeof(kCallbackChannelInstaller80042DB8Words) /
                       sizeof(kCallbackChannelInstaller80042DB8Words[0]) == 20,
                   "80042DB8 instruction stream changed");
    _Static_assert(sizeof(kStartupRecordSetup80018918Words) /
                       sizeof(kStartupRecordSetup80018918Words[0]) == 36,
                   "80018918 instruction stream changed");
    _Static_assert(sizeof(kStartupAllocatorPrefix8005F0C8Words) /
                       sizeof(kStartupAllocatorPrefix8005F0C8Words[0]) == 88,
                   "8005F0C8 prefix instruction stream changed");
    _Static_assert(sizeof(kStartupCallbackTable8005F728Words) /
                       sizeof(kStartupCallbackTable8005F728Words[0]) == 13,
                   "8005F728 instruction stream changed");
    _Static_assert(sizeof(kGuardedClear8005C2C8Words) /
                       sizeof(kGuardedClear8005C2C8Words[0]) == 12,
                   "8005C2C8 instruction stream changed");
    _Static_assert(sizeof(kStartupTableInit8005D6A0Words) /
                       sizeof(kStartupTableInit8005D6A0Words[0]) == 11,
                   "8005D6A0 instruction stream changed");
    _Static_assert(sizeof(kInputStartupWrapper8005D0F8Words) /
                       sizeof(kInputStartupWrapper8005D0F8Words[0]) == 8,
                   "8005D0F8 instruction stream changed");
    _Static_assert(sizeof(kInputStartupPrefix8005D8B4Words) /
                       sizeof(kInputStartupPrefix8005D8B4Words[0]) == 51,
                   "8005D8B4 instruction stream changed");
    _Static_assert(sizeof(kInputRecordCallback8005F228Words) /
                       sizeof(kInputRecordCallback8005F228Words[0]) == 26,
                   "8005F228 instruction stream changed");
    _Static_assert(sizeof(kStartupRetry80043450Words) /
                       sizeof(kStartupRetry80043450Words[0]) == 27,
                   "80043450 instruction stream changed");
    _Static_assert(sizeof(kStartupRetryAlternate80044BF4Words) /
                       sizeof(kStartupRetryAlternate80044BF4Words[0]) == 61,
                   "80044BF4 instruction stream changed");
    _Static_assert(sizeof(kStartupCallbackSetter8004359CWords) /
                       sizeof(kStartupCallbackSetter8004359CWords[0]) == 6,
                   "8004359C instruction stream changed");
    _Static_assert(sizeof(kStartupCallbackSetter800435B4Words) /
                       sizeof(kStartupCallbackSetter800435B4Words[0]) == 6,
                   "800435B4 instruction stream changed");
    _Static_assert(sizeof(kStartupCallbackSetter8004654CWords) /
                       sizeof(kStartupCallbackSetter8004654CWords[0]) == 6,
                   "8004654C instruction stream changed");
    _Static_assert(sizeof(kStartupCallbackControl80046564Words) /
                       sizeof(kStartupCallbackControl80046564Words[0]) == 6,
                   "80046564 instruction stream changed");
    _Static_assert(sizeof(kCdInitializer80044D38Words) /
                       sizeof(kCdInitializer80044D38Words[0]) == 123,
                   "80044D38 instruction stream changed");
    _Static_assert(sizeof(kCdCommandPrefix80044670Words) /
                       sizeof(kCdCommandPrefix80044670Words[0]) == 25,
                   "80044670 instruction stream changed");
    _Static_assert(sizeof(kCdCommandContinuation800446D4Words) /
                       sizeof(kCdCommandContinuation800446D4Words[0]) == 26,
                   "800446D4 instruction stream changed");
    _Static_assert(sizeof(kTickQuery8004239CMinusOneWords) /
                       sizeof(kTickQuery8004239CMinusOneWords[0]) == 31,
                   "8004239C minus-one instruction stream changed");
    _Static_assert(sizeof(kStatusFirstPoll80044124Words) /
                       sizeof(kStatusFirstPoll80044124Words[0]) == 29,
                   "80044124 first-poll instruction stream changed");
    _Static_assert(sizeof(kStatusTimeout80044198Words) /
                       sizeof(kStatusTimeout80044198Words[0]) == 16,
                   "80044198 timeout-comparison instruction stream changed");
    _Static_assert(sizeof(kStatusWorker80043B9CWords) /
                       sizeof(kStatusWorker80043B9CWords[0]) == 354,
                   "80043B9C status-worker instruction stream changed");
    _Static_assert(sizeof(kCdStateReset80044B14Words) /
                       sizeof(kCdStateReset80044B14Words[0]) == 56,
                   "80044B14 instruction stream changed");
    _Static_assert(sizeof(kCdStateResetWrapper800434BCWords) /
                       sizeof(kCdStateResetWrapper800434BCWords[0]) == 8,
                   "800434BC instruction stream changed");
    _Static_assert(sizeof(kStartupDispatcher80043300Words) /
                       sizeof(kStartupDispatcher80043300Words[0]) == 38,
                   "80043300 instruction stream changed");
    _Static_assert(sizeof(kSavedContext8005CD98Words) / sizeof(kSavedContext8005CD98Words[0]) == 30,
                   "8005CD98 instruction stream changed");
    _Static_assert(sizeof(kStartup800141F0Words) / sizeof(kStartup800141F0Words[0]) == 18,
                   "800141F0 instruction stream changed");
    _Static_assert(sizeof(kStartupMode800594CCWords) / sizeof(kStartupMode800594CCWords[0]) == 25,
                   "800594CC instruction stream changed");
    if (!memory || !sink || !result || !musashi_boot_ram_span(memory, format_address, 1) ||
        !musashi_boot_ram_span(memory, argument_words_address, 4))
        return 0;
    memset(&cpu, 0, sizeof(cpu));
    console.sink = sink;
    console.userdata = userdata;
    cpu.pc = FORMATTER_ENTRY;
    cpu.npc = FORMATTER_ENTRY + 4u;
    cpu.r[5] = format_address;
    cpu.r[6] = argument_words_address;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            *result = (int32_t)cpu.r[2];
            return 1;
        }
        if (cpu.pc == FORMATTER_CONSOLE_CHAR || cpu.pc == FORMATTER_SEARCH ||
            cpu.pc == FORMATTER_STRING_LENGTH) {
            if (!formatter_call(memory, &cpu, sink, &console)) return 0;
        } else if (!formatter_step(memory, &cpu)) {
            return 0;
        }
    }
    return 0;
}

MusashiResetGraphPrefixStatus musashi_boot_run_800141f0_prefix(
    MusashiBootMemory *memory, MusashiConsoleSink sink, void *userdata,
    int32_t *result, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    FormatterConsoleContext console;
    unsigned step;
    if (!memory || !sink || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    console.sink = sink;
    console.userdata = userdata;
    cpu.pc = STARTUP_ENTRY;
    cpu.npc = STARTUP_ENTRY + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CALLBACK_INITIALIZER) {
            stop->call_address = 0x80042598;
            stop->target_address = CALLBACK_INITIALIZER;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX)
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        if (cpu.pc == FORMATTER_CONSOLE_CHAR || cpu.pc == FORMATTER_SEARCH ||
            cpu.pc == FORMATTER_STRING_LENGTH || cpu.pc == RESETGRAPH_FILL) {
            if (!formatter_call(memory, &cpu, sink, &console))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, &cpu)) {
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_resetgraph_prefix(
    MusashiBootMemory *memory, int32_t mode, MusashiConsoleSink sink,
    void *userdata, int32_t *result, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    FormatterConsoleContext console;
    unsigned step;
    if (!memory || !sink || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    console.sink = sink;
    console.userdata = userdata;
    cpu.pc = RESETGRAPH_ENTRY;
    cpu.npc = RESETGRAPH_ENTRY + 4u;
    cpu.r[4] = (uint32_t)mode;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CALLBACK_INITIALIZER) {
            stop->call_address = 0x80042598;
            stop->target_address = CALLBACK_INITIALIZER;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX) {
            *result = (int32_t)cpu.r[2];
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
        if (cpu.pc == FORMATTER_CONSOLE_CHAR || cpu.pc == FORMATTER_SEARCH ||
            cpu.pc == FORMATTER_STRING_LENGTH || cpu.pc == RESETGRAPH_FILL) {
            if (!formatter_call(memory, &cpu, sink, &console))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, &cpu)) {
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiCallbackInitPrefixStatus musashi_boot_run_callback_init_prefix(
    MusashiBootMemory *memory, const MusashiCallbackDevice *device,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !device->read16 || !device->write16 ||
        !device->write32 || !stop)
        return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.callback_device = device;
    cpu.pc = CALLBACK_INITIALIZER;
    cpu.npc = CALLBACK_INITIALIZER + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CALLBACK_BIOS_B0_19) {
            if (device->hook_entry_int) {
                if (!device->hook_entry_int(callback_hook_userdata(device), cpu.r[4]))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                if (!formatter_return(&cpu))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                continue;
            }
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = CALLBACK_BIOS_B0_19;
            return MUSASHI_CALLBACK_INIT_PREFIX_BIOS_BOUNDARY;
        }
        if (cpu.pc == CALLBACK_INSTALLER) {
            if (device->registration_device) {
                if (!formatter_step(memory, &cpu))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                continue;
            }
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = CALLBACK_INSTALLER;
            return MUSASHI_CALLBACK_INIT_PREFIX_INSTALLER_BOUNDARY;
        }
        if (cpu.pc == CALLBACK_CHANNEL_INSTALLER) {
            if (device->registration_device) {
                if (!formatter_step(memory, &cpu))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                continue;
            }
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = CALLBACK_CHANNEL_INSTALLER;
            return MUSASHI_CALLBACK_INIT_PREFIX_CHANNEL_INSTALLER_BOUNDARY;
        }
        if (cpu.pc == CALLBACK_BIOS_A0_72) {
            if (device->a0_72) {
                if (!device->a0_72(device->userdata, cpu.r[4]))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                if (!formatter_return(&cpu))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                continue;
            }
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = CALLBACK_BIOS_A0_72;
            return MUSASHI_CALLBACK_INIT_PREFIX_A0_72_BOUNDARY;
        }
        if (cpu.pc == CALLBACK_EXIT_CRITICAL) {
            if (device->exit_critical_section) {
                if (!device->exit_critical_section(device->userdata))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                if (!formatter_return(&cpu))
                    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
                continue;
            }
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = CALLBACK_EXIT_CRITICAL;
            return MUSASHI_CALLBACK_INIT_PREFIX_EXIT_CRITICAL_BOUNDARY;
        }
        if (cpu.pc == CALLBACK_INITIALIZER_RETURN) {
            stop->call_address = CALLBACK_INITIALIZER_RETURN;
            stop->target_address = UINT_MAX;
            return MUSASHI_CALLBACK_INIT_PREFIX_RETURN_BOUNDARY;
        }
        if (cpu.pc == UINT_MAX)
            return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
        if (cpu.pc == CALLBACK_CLEAR || cpu.pc == CALLBACK_INSTALLER_CLEAR ||
            cpu.pc == CALLBACK_CHANNEL_CLEAR || cpu.pc == CALLBACK_REGISTER_WRAPPER) {
            if (!formatter_call(memory, &cpu, NULL, NULL))
                return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, &cpu)) {
            return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_CALLBACK_INIT_PREFIX_INVALID_INPUT;
}

static void entry_snapshot(const FormatterCpu *cpu, MusashiEntryCpuSnapshot *out) {
    memcpy(out->r, cpu->r, sizeof(out->r));
    out->hi = cpu->hi;
    out->lo = cpu->lo;
    out->pc = cpu->pc;
    out->npc = cpu->npc;
}

static MusashiResetGraphPrefixStatus run_startup_cpu(
    MusashiBootMemory *memory, FormatterCpu *cpu,
    MusashiConsoleSink sink, void *userdata, int32_t *result,
    MusashiResetGraphPrefixStop *stop, MusashiEntryRunStop *entry_stop,
    MusashiEntryObserver observer, void *observer_userdata) {
    FormatterConsoleContext console;
    const MusashiCallbackDevice *device = cpu->callback_device;
    unsigned step;
    /* 2e9 exhausted in GPU clip after overlay Start; keep unsigned. */
    const unsigned step_limit = entry_stop ? 4000000000u : FORMATTER_STEP_LIMIT;
    console.sink = sink;
    console.userdata = userdata;
    for (step = 0; step < step_limit; ++step) {
        /* Also identify an instruction/device refusal. A missing MMIO
         * provider can stop before reaching any of the named call gates. */
        stop->call_address = cpu->pc;
        stop->target_address = cpu->pc;
        if (entry_stop) {
            entry_snapshot(cpu, &entry_stop->cpu);
            if (observer && (cpu->pc == 0x80047d3cu || cpu->pc == 0x80047d48u ||
                cpu->pc == 0x80047d4cu || cpu->pc == 0x80047d50u || cpu->pc == 0x80047d68u ||
                cpu->pc == 0x80053218u || cpu->pc == 0x80014690u ||
                cpu->pc == 0x80014774u || cpu->pc == 0x80059888u ||
                cpu->pc == 0x80053178u || cpu->pc == 0x80014680u ||
                cpu->pc == 0x8005283cu || cpu->pc == 0x80052d00u ||
                cpu->pc == 0x80052d80u || cpu->pc == 0x80052becu ||
                cpu->pc == 0x80052c74u || cpu->pc == 0x80014650u ||
                cpu->pc == 0x80010000u || cpu->pc == 0x80010178u ||
                cpu->pc == STARTUP_ENTRY || cpu->pc == 0x800101c8u ||
                cpu->pc == CD_START || cpu->pc == CD_B0_5B ||
                cpu->pc == CD_ENTER_CRITICAL || cpu->pc == 0x800622f0u || cpu->pc == CD_B0_4A ||
                cpu->pc == CD_B0_4B || cpu->pc == 0x80062340u || cpu->pc == CD_A0_70 ||
                cpu->pc == 0x8006188cu || cpu->pc == EVENT_REGISTER || cpu->pc == 0x8005fcf8u || cpu->pc == 0x8005d8b4u || cpu->pc == 0x800101e4u || cpu->pc == 0x800101ecu ||
                cpu->pc == 0x8002c8f4u || cpu->pc == 0x8003a424u ||
                cpu->pc == 0x8002c904u || cpu->pc == 0x8003d530u ||
                cpu->pc == 0x8002c90cu || cpu->pc == 0x8003b160u ||
                cpu->pc == 0x8003c598u || cpu->pc == 0x8002c974u ||
                cpu->pc == 0x8003be24u || cpu->pc == 0x8002d1f0u ||
                cpu->pc == 0x8003b954u || cpu->pc == 0x8003b280u ||
                cpu->pc == 0x8002c984u || cpu->pc == 0x8002c98cu ||
                cpu->pc == 0x80037d98u || cpu->pc == 0x8002cc00u ||
                cpu->pc == 0x80034c24u || cpu->pc == 0x800430dcu ||
                cpu->pc == 0x80043830u || cpu->pc == 0x80043938u ||
                cpu->pc == 0x80034cd0u || cpu->pc == 0x8002cc34u ||
                cpu->pc == 0x800101fcu || cpu->pc == 0x8001971cu ||
                cpu->pc == 0x80019990u || cpu->pc == 0x8001974cu ||
                cpu->pc == 0x80019768u || cpu->pc == 0x800197ccu ||
                cpu->pc == 0x800197ecu || cpu->pc == 0x8004544cu ||
                cpu->pc == 0x80019804u || cpu->pc == 0x80019b30u ||
                cpu->pc == 0x80010f80u || cpu->pc == 0x800ceec8u ||
                cpu->pc == 0x800cee2cu || cpu->pc == 0x800ceefcu ||
                cpu->pc == 0x800ceef4u || cpu->pc == 0x800cf02cu ||
                cpu->pc == 0x800cf068u || cpu->pc == 0x800cf3b0u || cpu->pc == 0x800cf104u ||
                cpu->pc == 0x800118acu || cpu->pc == 0x80018ce8u ||
                cpu->pc == 0x800cef94u || cpu->pc == 0x800ceff8u ||
                cpu->pc == 0x80014cacu || cpu->pc == 0x800149e0u ||
                cpu->pc == 0x800cf3d4u || cpu->pc == 0x800cf3e8u ||
                cpu->pc == 0x80011818u || cpu->pc == 0x800110ccu ||
                cpu->pc == 0x80019a24u || cpu->pc == 0x80010fd0u ||
                cpu->pc == 0x8001aa98u || cpu->pc == 0x8001aaa0u ||
                cpu->pc == 0x800198fcu || cpu->pc == 0x80010204u || cpu->pc == 0x80059df4u || cpu->pc == 0x80059dfcu || cpu->pc == 0x8005b870u || cpu->pc == 0x8005b720u || cpu->pc == 0x8005b730u || cpu->pc == 0x8005b690u || cpu->pc == 0x8005279cu || cpu->pc == 0x800525dcu || cpu->pc == 0x800526a8u || cpu->pc == 0x800526fcu || cpu->pc == 0x80014948u || cpu->pc == 0x80014248u ||
                cpu->pc == 0x80045374u || cpu->pc == 0x80045660u ||
                cpu->pc == 0x80045744u || cpu->pc == 0x80045918u ||
                cpu->pc == 0x80045a50u || cpu->pc == 0x80045c14u ||
                cpu->pc == 0x80045c94u || cpu->pc == 0x80045cb8u ||
                cpu->pc == 0x8004637cu || cpu->pc == 0x800460ccu ||
                cpu->pc == 0x80046480u || cpu->pc == 0x80045698u))
                observer(observer_userdata, &entry_stop->cpu);
        }
        if (device->checkpoint && !device->checkpoint(device->userdata, cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        if (cpu->gte_load_pending && !gte_load_successor_pc(cpu->pc))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        if (entry_stop && cpu->pc == EVENT_REGISTER && !cpu->event_device) {
            stop->call_address = cpu->r[31] - 8u;
            stop->target_address = cpu->pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (entry_stop && (cpu->pc == INPUT_C0_3 || cpu->pc == INPUT_C0_2 ||
                           cpu->pc == INPUT_C0_0A)) {
            const MusashiInputDevice *input = cpu->input_device;
            int32_t service_result;
            int accepted = 0;
            if (input) {
                if (cpu->pc == INPUT_C0_3 && input->dequeue_irq_result)
                    accepted = input->dequeue_irq_result(input->userdata, (int32_t)cpu->r[4], cpu->r[5], &service_result);
                else if (cpu->pc == INPUT_C0_2 && input->enqueue_irq_result)
                    accepted = input->enqueue_irq_result(input->userdata, (int32_t)cpu->r[4], cpu->r[5], &service_result);
                else if (cpu->pc == INPUT_C0_0A && input->change_timer_result)
                    accepted = input->change_timer_result(input->userdata, (int32_t)cpu->r[4], (int32_t)cpu->r[5], &service_result);
            }
            if (!accepted) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu->r[2] = (uint32_t)service_result;
            formatter_return(cpu);
            continue;
        }
        if (entry_stop && cpu->pc == 0xb0u && cpu->r[9] == 0x56u) {
            uint32_t table;
            if (cpu->npc != 0xb4u || cpu->r[10] != 0xb0u ||
                cpu->r[31] != 0x8004d188u) return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            if (!cpu->bios_image || !cpu->bios_image->table ||
                !cpu->bios_image->table(cpu->bios_image->userdata, &table)) {
                stop->call_address = 0x8004d180u; stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu->r[2] = table;
            formatter_return(cpu);
            continue;
        }
        if (entry_stop && cpu->pc == 0xa0u && cpu->r[9] == 0x44u) {
            if (cpu->npc != 0xa4u || cpu->r[10] != 0xa0u ||
                cpu->r[31] != 0x8004d1b8u) return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            if (!cpu->bios_image || !cpu->bios_image->publish ||
                !cpu->bios_image->publish(cpu->bios_image->userdata)) {
                stop->call_address = 0x8004d1b0u; stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(cpu); /* A0:44 supplies no invented v0 result. */
            continue;
        }
        if (entry_stop && cpu->pc == 0xa0u) {
            /* Reach the actual BIOS vector through all three 5CE18 words.
             * Only this source-backed heap call is closed here. The selected
             * BIOS preserves v0; callback success never becomes a guest value. */
            if (cpu->npc != 0xa4u || cpu->r[9] != 0x39u ||
                cpu->r[10] != 0xa0u || cpu->r[31] != 0x80014948u)
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            if (!cpu->heap_device || !cpu->heap_device->init_heap ||
                !cpu->heap_device->init_heap(cpu->heap_device->userdata,
                                             cpu->r[4], cpu->r[5])) {
                stop->call_address = 0x80014940u;
                stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(cpu);
            continue;
        }
        if (entry_stop && (cpu->pc == CD_ENTER_CRITICAL + 4u ||
                           cpu->pc == CALLBACK_EXIT_CRITICAL + 4u)) {
            int is_enter = cpu->pc == CD_ENTER_CRITICAL + 4u;
            int accepted = 0;
            int32_t previous;
            uint32_t instruction;
            /* Execute the wrapper's selector and JR/delay instructions. Only
             * the actual SYSCALL crosses into the native exception owner. */
            if (cpu->r[4] != (is_enter ? 1u : 2u) || cpu->npc != cpu->pc + 4u ||
                cpu->delay_slot || cpu->branch_pc || cpu->merge_pending || cpu->gte_load_pending ||
                !formatter_fetch(cpu, &instruction) || instruction != 0x0000000cu)
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            if ((is_enter && (!cpu->cd_device || !cpu->cd_device->enter_critical_result)) ||
                (!is_enter && !device->exit_critical_section))
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            /* Charge the fetched SYSCALL, not an invented BIOS duration. */
            if (cpu->clock && (!cpu->clock->advance ||
                !cpu->clock->advance(cpu->clock->userdata, 2u)))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            if (is_enter) {
                if (cpu->cd_device && cpu->cd_device->enter_critical_result)
                    accepted = cpu->cd_device->enter_critical_result(
                        cpu->cd_device->userdata, &previous);
            } else if (device->exit_critical_section) {
                accepted = device->exit_critical_section(device->userdata);
            }
            if (!accepted) {
                stop->call_address = cpu->pc;
                stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            if (is_enter) cpu->r[2] = (uint32_t)previous;
            cpu->pc = cpu->npc;
            cpu->npc += 4u;
            cpu->delay_slot = 0; cpu->branch_pc = 0;
            continue;
        }
        if ((entry_stop || cpu->event_device) &&
            (cpu->pc == 0x8005ce78u || cpu->pc == 0x8005ceb8u ||
             cpu->pc == 0x8005cea8u)) {
            const MusashiEventDevice *event = cpu->event_device;
            int32_t service_result;
            int accepted = 0;
            if (event) {
                if (cpu->pc == 0x8005ce78u && event->open_event)
                    accepted = event->open_event(event->userdata, cpu->r[4], cpu->r[5],
                                                cpu->r[6], cpu->r[7], &service_result);
                else if (cpu->pc == 0x8005ceb8u && event->enable_event)
                    accepted = event->enable_event(event->userdata, (int32_t)cpu->r[4], &service_result);
                else if (cpu->pc == 0x8005cea8u && event->b0_0b)
                    accepted = event->b0_0b(event->userdata, (int32_t)cpu->r[4], &service_result);
            }
            if (!accepted) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            /* BIOS zero is a guest result, not a host refusal. */
            cpu->r[2] = (uint32_t)service_result;
            formatter_return(cpu);
            continue;
        }
        if (cpu->pc == CD_INITIALIZER_STRING_EMIT) {
            if (!intrinsic_string(memory, cpu, cpu->r[4]) ||
                !musashi_boot_console_string(memory, cpu->r[4], sink, userdata))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            formatter_return(cpu);
            continue;
        }
        if (cpu->pc == 0x80043060u) {
            int32_t previous;
            if (!musashi_boot_call_80043060(memory, (int32_t)cpu->r[4], &previous))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu->r[2] = (uint32_t)previous;
            formatter_return(cpu);
            continue;
        }
        if (entry_stop && (cpu->pc == CD_B0_5B || cpu->pc == CD_B0_4A ||
            cpu->pc == CD_B0_4B || cpu->pc == CD_A0_70)) {
            const MusashiCdDevice *cd = cpu->cd_device;
            int32_t service_result;
            int accepted = 0;
            if (cd) {
                if (cpu->pc == CD_B0_5B && cd->b0_5b)
                    accepted = cd->b0_5b(cd->userdata, (int32_t)cpu->r[4], &service_result);
                else if (cpu->pc == CD_B0_4A && cd->b0_4a)
                    accepted = cd->b0_4a(cd->userdata, (int32_t)cpu->r[4], &service_result);
                else if (cpu->pc == CD_B0_4B && cd->b0_4b)
                    accepted = cd->b0_4b(cd->userdata, &service_result);
                else if (cpu->pc == CD_A0_70 && cd->a0_70)
                    accepted = cd->a0_70(cd->userdata, &service_result);
            }
            if (!accepted) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = cpu->pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu->r[2] = (uint32_t)service_result;
            formatter_return(cpu);
            continue;
        }
        if (cpu->pc == STARTUP_GRAPHICS_RESET && !cpu->gpu_io_device) {
            if (device->reset_device &&
                musashi_boot_call_8005b684(memory, device->reset_device, cpu->r[4])) {
                formatter_return(cpu);
                continue;
            }
            stop->call_address = 0x800596d4u;
            stop->target_address = STARTUP_GRAPHICS_RESET;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu->pc == RESETGRAPH_GPU_CW) {
            int32_t gpu_result;
            if (device->gpu_cw &&
                device->gpu_cw(device->userdata, cpu->r[4], &gpu_result)) {
                cpu->r[2] = (uint32_t)gpu_result;
                formatter_return(cpu);
                continue;
            }
            stop->call_address = 0x800592d4u;
            stop->target_address = RESETGRAPH_GPU_CW;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu->pc == RESETGRAPH_DEVICE_RESET) {
            int32_t reset_result;
            if (device->reset_device &&
                musashi_boot_call_8005bd7c(memory, device->reset_device,
                                            (int32_t)cpu->r[4], &reset_result)) {
                cpu->r[2] = (uint32_t)reset_result;
                formatter_return(cpu);
                continue;
            }
            stop->call_address = cpu->r[31] - 8u;
            stop->target_address = RESETGRAPH_DEVICE_RESET;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu->pc == STARTUP_AFTER_RESETGRAPH) {
            /* Enter the exact arg0=0 routine normally. */
        }
        if (cpu->pc == CALLBACK_BIOS_B0_19) {
            if (!device->hook_entry_int ||
                !device->hook_entry_int(callback_hook_userdata(device), cpu->r[4])) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = CALLBACK_BIOS_B0_19;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(cpu);
            continue;
        }
        if (cpu->pc == CALLBACK_INSTALLER && !device->registration_device) {
            stop->call_address = cpu->r[31] - 8u;
            stop->target_address = CALLBACK_INSTALLER;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu->pc == CALLBACK_CHANNEL_INSTALLER && !device->registration_device) {
            stop->call_address = cpu->r[31] - 8u;
            stop->target_address = CALLBACK_CHANNEL_INSTALLER;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu->pc == CALLBACK_BIOS_A0_72) {
            if (!device->a0_72 || !device->a0_72(device->userdata, cpu->r[4])) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = CALLBACK_BIOS_A0_72;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(cpu);
            continue;
        }
        if (!entry_stop && cpu->pc == CALLBACK_EXIT_CRITICAL) {
            if (!device->exit_critical_section ||
                !device->exit_critical_section(device->userdata)) {
                stop->call_address = cpu->r[31] - 8u;
                stop->target_address = CALLBACK_EXIT_CRITICAL;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(cpu);
            continue;
        }
        if (cpu->pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            *result = (int32_t)cpu->r[2];
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (cpu->pc == FORMATTER_CONSOLE_CHAR || cpu->pc == FORMATTER_SEARCH ||
            cpu->pc == FORMATTER_STRING_LENGTH || cpu->pc == RESETGRAPH_FILL ||
            cpu->pc == CALLBACK_CLEAR || cpu->pc == CALLBACK_INSTALLER_CLEAR ||
            cpu->pc == CALLBACK_CHANNEL_CLEAR || cpu->pc == CALLBACK_REGISTER_WRAPPER ||
            cpu->pc == STARTUP_ENVIRONMENT_CLEAR || cpu->pc == STARTUP_CLEAR_29044 ||
            cpu->pc == STARTUP_CLEAR_2906C || cpu->pc == STARTUP_CLEAR_29094 ||
            cpu->pc == STARTUP_CLEAR_29218 || cpu->pc == STARTUP_RECORD_CLEAR) {
            if (!formatter_call(memory, cpu, sink, &console))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, cpu)) {
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    if (entry_stop) entry_snapshot(cpu, &entry_stop->cpu);
    return MUSASHI_RESETGRAPH_PREFIX_STEP_LIMIT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_800141f0_callback_prefix(
    MusashiBootMemory *memory, const MusashiCallbackDevice *device,
    MusashiConsoleSink sink, void *userdata, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu = {0};
    if (!memory || !device || !sink || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    cpu.callback_device = device;
    cpu.pc = STARTUP_ENTRY;
    cpu.npc = STARTUP_ENTRY + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    return run_startup_cpu(memory, &cpu, sink, userdata, result, stop,
                           NULL, NULL, NULL);
}

void musashi_boot_bios_callback_frame_init(MusashiBiosCallbackFrame *frame) {
    if (frame) memset(frame, 0, sizeof(*frame));
}

static int input_callback_word(uint32_t pc, uint32_t *word) {
    if (pc & 3u) return 0;
    if (pc >= 0x8005d6ccu && pc < 0x8005d734u)
        *word = kInputVerifierWords[(pc-0x8005d6ccu)/4u];
    else if (pc >= 0x8005d734u && pc < 0x8005d8a0u)
        *word = kInputHandlerWords[(pc-0x8005d734u)/4u];
    else if (pc >= 0x8005d8a0u && pc < 0x8005d8b4u)
        *word = kInputHandlerClear8005D8A0Words[(pc-0x8005d8a0u)/4u];
    else if (pc >= 0x8005d9c4u && pc < 0x8005dbd8u)
        *word = kInputSerialStartWords[(pc-0x8005d9c4u)/4u];
    else if (pc >= 0x8005dbd8u && pc < 0x8005dca0u)
        *word = kInputSerialNextWords[(pc-0x8005dbd8u)/4u];
    else if (pc >= 0x8005eae8u && pc < 0x8005eb28u)
        *word = kInputSerialDispatchWords[(pc-0x8005eae8u)/4u];
    else if (pc >= 0x8005f75cu && pc < 0x8005f830u)
        *word = kInputSerialPadWords[(pc-0x8005f75cu)/4u];
    else if (pc >= 0x8005dca0u && pc < 0x8005de78u)
        *word = kInputSerialTransferWords[(pc-0x8005dca0u)/4u];
    else if (pc >= 0x8005e0acu && pc < 0x8005e13cu)
        *word = kInputSerialIrqWords[(pc-0x8005e0acu)/4u];
    else if (pc >= 0x8005fba8u && pc < 0x8005fbc8u)
        *word = kInputTimerStartWords[(pc-0x8005fba8u)/4u];
    else if (pc >= 0x8005fbc8u && pc < 0x8005fc68u)
        *word = kInputTimerPollWords[(pc-0x8005fbc8u)/4u];
    else if (pc >= 0x8005f830u && pc < 0x8005fa94u)
        *word = kInputResponseWords[(pc-0x8005f830u)/4u];
    else if (pc >= 0x8005fb70u && pc < 0x8005fb9cu)
        *word = kInputResponseStatusWords[(pc-0x8005fb70u)/4u];
    else if (pc >= 0x8005e228u && pc < 0x8005e374u)
        *word = kInputResponseModeWords[(pc-0x8005e228u)/4u];
    else if (pc >= 0x8005e374u && pc < 0x8005e3acu)
        *word = kInputResponse8005E374Words[(pc-0x8005e374u)/4u];
    else if (pc >= 0x8005e3acu && pc < 0x8005e79cu)
        *word = kInputResponse8005E3ACWords[(pc-0x8005e3acu)/4u];
    else if (pc >= 0x8005f384u && pc < 0x8005f394u)
        *word = kInputResponseClearWords[(pc-0x8005f384u)/4u];
    else if (pc >= 0x8005f228u && pc < 0x8005f290u)
        *word = kInputRecordCallback8005F228Words[(pc-0x8005f228u)/4u];
    else if (pc >= 0x8005de78u && pc < 0x8005e0acu)
        *word = kInputDigital8005DE78Words[(pc - 0x8005de78u) / 4u];
    else if (pc >= 0x8005e13cu && pc < 0x8005e164u)
        *word = kInputDigital8005E13CWords[(pc - 0x8005e13cu) / 4u];
    else if (pc >= 0x8005e1a4u && pc < 0x8005e228u)
        *word = kInputDigital8005E1A4Words[(pc - 0x8005e1a4u) / 4u];
    else if (pc >= 0x8005ea34u && pc < 0x8005ea54u)
        *word = kInputDigital8005EA34Words[(pc - 0x8005ea34u) / 4u];
    else if (pc >= 0x8005ea54u && pc < 0x8005ea68u)
        *word = kInputDigital8005EA54Words[(pc - 0x8005ea54u) / 4u];
    else if (pc >= 0x8005ea68u && pc < 0x8005ea88u)
        *word = kInputDigital8005EA68Words[(pc - 0x8005ea68u) / 4u];
    else if (pc >= 0x8005ea88u && pc < 0x8005eaa8u)
        *word = kInputDigital8005EA88Words[(pc - 0x8005ea88u) / 4u];
    else if (pc >= 0x8005eaa8u && pc < 0x8005eac8u)
        *word = kInputDigital8005EAA8Words[(pc - 0x8005eaa8u) / 4u];
    else if (pc >= 0x8005eac8u && pc < 0x8005eae8u)
        *word = kInputDigital8005EAC8Words[(pc - 0x8005eac8u) / 4u];
    else if (pc >= 0x8005eb28u && pc < 0x8005ec00u)
        *word = kInputDigital8005EB28Words[(pc - 0x8005eb28u) / 4u];
    else if (pc >= 0x8005ec00u && pc < 0x8005ecc0u)
        *word = kInputDigital8005EC00Words[(pc - 0x8005ec00u) / 4u];
    else if (pc >= 0x8005ecc0u && pc < 0x8005ed4cu)
        *word = kInputDigital8005ECC0Words[(pc - 0x8005ecc0u) / 4u];
    else if (pc >= 0x8005ed4cu && pc < 0x8005f0c8u)
        *word = kInputDigital8005ED4CWords[(pc - 0x8005ed4cu) / 4u];
    else if (pc >= 0x8005f290u && pc < 0x8005f384u)
        *word = kInputDigital8005F290Words[(pc - 0x8005f290u) / 4u];
    else if (pc >= 0x8005f394u && pc < 0x8005f450u)
        *word = kInputDigital8005F394Words[(pc - 0x8005f394u) / 4u];
    else if (pc >= 0x8005f450u && pc < 0x8005f6ccu)
        *word = kInputDigital8005F450Words[(pc - 0x8005f450u) / 4u];
    else if (pc >= 0x8005f6ccu && pc < 0x8005f704u)
        *word = kInputDigital8005F6CCWords[(pc - 0x8005f6ccu) / 4u];
    else if (pc >= 0x8005fa94u && pc < 0x8005fb70u)
        *word = kInputDigital8005FA94Words[(pc - 0x8005fa94u) / 4u];
    else if (pc >= 0x8005c2c8u && pc < 0x8005c2f8u)
        *word = kGuardedClear8005C2C8Words[(pc - 0x8005c2c8u) / 4u];
    else return 0;
    return 1;
}

static int input_callback_call(MusashiBootMemory *memory, const FormatterCpu *cpu,
                                uint32_t instruction, uint32_t target) {
    const MusashiInputDevice *device = cpu->input_device;
    uint32_t slot = 0, expected = 0, live;
    uint32_t expected_word = 0x0040f809u;
    static const uint32_t table[5] = {
        0x8005eae8u, 0x8005eb28u, 0x8005ec00u, 0x8005ecc0u, 0x8005ed4cu
    };
    if (!device->read16 || !device->write16) return 0;
    switch (cpu->pc) {
    case 0x8005d7fcu: return instruction == 0x0c017671u && target == 0x8005d9c4u;
    case 0x8005d858u: return instruction == 0x0c0176f6u && target == 0x8005dbd8u;
    case 0x8005da10u:
    case 0x8005dc2cu: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    default: break;
    }
    /* Both DATA bindings opt into the observed digital source graph. The
     * legacy halfword-only profile retains its DB04 boundary. Nonzero record
     * callbacks, global hooks and future configuration children stay refused. */
    if (!device->read8 || !device->write8) return 0;
    switch (cpu->pc) {
    case 0x8005dc04u:
        /* Check the OLD index and its exact live slot before DC08 increments
         * it. Index five is a hardware pointer, never an executable entry. */
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory, 0x800729a0u, &live) || live >= 5u)
            return 0;
        expected = table[live];
        return target == expected &&
            musashi_boot_read32(memory, 0x800729e0u + live * 4u, &live) &&
            live == expected;
    case 0x8005d818u: slot = 0x8007295cu; expected = 0x8005f290u; break;
    case 0x8005daa0u: slot = 0x8007297cu; expected = 0x8005f830u; expected_word = 0x0060f809u; break;
    case 0x8005db04u: slot = 0x8007297cu; expected = 0x8005f830u; break;
    case 0x8005db18u: slot = 0x80072980u; expected = 0x8005f384u; break;
    case 0x8005db68u: return instruction == 0x0c01784fu && target == 0x8005e13cu;
    case 0x8005dc34u: return instruction == 0x0c01782bu && target == 0x8005e0acu;
    case 0x8005dc50u: slot = 0x8007295cu; expected = 0x8005f290u; break;
    case 0x8005dc88u: slot = 0x8007295cu; expected = 0x8005f290u; break;
    case 0x8005dd1cu: return instruction == 0x0c017ef2u && target == 0x8005fbc8u;
    case 0x8005ddf0u: return instruction == 0x0c017ef2u && target == 0x8005fbc8u;
    case 0x8005deecu: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    case 0x8005e028u: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    case 0x8005e030u: return instruction == 0x0c017ef2u && target == 0x8005fbc8u;
    case 0x8005e0e0u: return instruction == 0x0c017ef2u && target == 0x8005fbc8u;
    case 0x8005e1e8u: return instruction == 0x0c017a95u && target == 0x8005ea54u;
    case 0x8005e1fcu: return instruction == 0x0c017a9au && target == 0x8005ea68u;
    case 0x8005e210u: return instruction == 0x0c017aaau && target == 0x8005eaa8u;
    case 0x8005eafcu: slot = 0x80072974u; expected = 0x8005f75cu; break;
    case 0x8005eb10u: return instruction == 0x0c017728u && target == 0x8005dca0u;
    case 0x8005ebacu: slot = 0x80072974u; expected = 0x8005f75cu; break;
    case 0x8005ebc4u: slot = 0x80072974u; expected = 0x8005f75cu; break;
    case 0x8005ebe8u: return instruction == 0x0c01779eu && target == 0x8005de78u;
    case 0x8005ec2cu: slot = 0x80072974u; expected = 0x8005f75cu; break;
    case 0x8005ec44u: slot = 0x80072974u; expected = 0x8005f75cu; break;
    case 0x8005ec64u: return instruction == 0x0c01779eu && target == 0x8005de78u;
    case 0x8005ed04u: slot = 0x80072964u; expected = 0x8005f394u; break;
    case 0x8005ed10u: return instruction == 0x0c01779eu && target == 0x8005de78u;
    case 0x8005ed74u: slot = 0x80072968u; expected = 0x8005f450u; break;
    case 0x8005edfcu: slot = 0x80072968u; expected = 0x8005f450u; break;
    case 0x8005ee14u: slot = 0x80072964u; expected = 0x8005f394u; break;
    case 0x8005ee20u: return instruction == 0x0c01779eu && target == 0x8005de78u;
    case 0x8005ee30u: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    case 0x8005ee38u: return instruction == 0x0c01782bu && target == 0x8005e0acu;
    case 0x8005eed8u: slot = 0x8007297cu; expected = 0x8005f830u; break;
    case 0x8005ef34u: slot = 0x8007297cu; expected = 0x8005f830u; break;
    case 0x8005ef60u: slot = 0x8007297cu; expected = 0x8005f830u; break;
    case 0x8005ef74u: slot = 0x80072980u; expected = 0x8005f384u; break;
    case 0x8005ef94u: slot = 0x80072964u; expected = 0x8005f394u; break;
    case 0x8005efa0u: return instruction == 0x0c017728u && target == 0x8005dca0u;
    case 0x8005efb0u: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    case 0x8005efb8u: return instruction == 0x0c01782bu && target == 0x8005e0acu;
    case 0x8005f00cu: slot = 0x80072964u; expected = 0x8005f394u; break;
    case 0x8005f018u: return instruction == 0x0c017728u && target == 0x8005dca0u;
    case 0x8005f028u: return instruction == 0x0c017eeau && target == 0x8005fba8u;
    case 0x8005f030u: return instruction == 0x0c01782bu && target == 0x8005e0acu;
    case 0x8005f05cu: return instruction == 0x0c01784fu && target == 0x8005e13cu;
    case 0x8005f098u: slot = 0x8007295cu; expected = 0x8005f290u; break;
    case 0x8005f2f4u: return instruction == 0x0c017ea5u && target == 0x8005fa94u;
    case 0x8005f2fcu: return instruction == 0x0c017ce1u && target == 0x8005f384u;
    case 0x8005f34cu: return instruction == 0x0c017671u && target == 0x8005d9c4u;
    case 0x8005f464u: return instruction == 0x0c0170b2u && target == 0x8005c2c8u;
    case 0x8005f7d8u: return instruction == 0x0c017a8du && target == 0x8005ea34u;
    case 0x8005f7e8u: return instruction == 0x0c017a8du && target == 0x8005ea34u;
    case 0x8005f818u: return instruction == 0x0c017869u && target == 0x8005e1a4u;
    case 0x8005f910u: return instruction == 0x0c017edcu && target == 0x8005fb70u;
    case 0x8005f95cu: slot = 0x80072960u; expected = 0x8005f228u; break;
    case 0x8005f9a4u: slot = 0x80072960u; expected = 0x8005f228u; break;
    case 0x8005fa68u: return instruction == 0x0c01788au && target == 0x8005e228u;
    case 0x8005e31cu: return instruction == 0x0c0178ddu && target == 0x8005e374u;
    case 0x8005e34cu: return instruction == 0x0c0178ebu && target == 0x8005e3acu;
    case 0x8005e3e4u: slot = 0x80072978u; expected = 0x8005fb70u; break;
    case 0x8005e4c8u: return instruction == 0x0c017a9au && target == 0x8005ea68u;
    case 0x8005e4dcu: return instruction == 0x0c017aa2u && target == 0x8005ea88u;
    case 0x8005e500u: return instruction == 0x0c017aaau && target == 0x8005eaa8u;
    case 0x8005e510u: return instruction == 0x0c017ab2u && target == 0x8005eac8u;
    case 0x8005fb24u: slot = 0x80072960u; expected = 0x8005f228u; break;
    default: return 0;
    }
    return instruction == expected_word && target == expected &&
        musashi_boot_read32(memory, slot, &live) && live == expected;
}

/* Each admitted source instruction, including call/return delay slots, costs
 * one budget unit. Exhaustion refuses before the next instruction's effects. */
static int input_callback_step(MusashiBootMemory *memory, FormatterCpu *cpu,
                               unsigned *remaining,
                               MusashiResetGraphPrefixStop *stop) {
    if (*remaining) {
        --*remaining;
        if (formatter_step(memory, cpu)) return 1;
    }
    stop->call_address = stop->target_address = cpu->pc;
    return 0;
}

int musashi_boot_execute_input_bios_callback(MusashiBootMemory *memory,
    const MusashiInputDevice *device, MusashiBiosCallbackFrame *frame,
    uint32_t target, int32_t argument, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu = {0};
    struct { uint32_t pc, sp; } returns[8];
    unsigned remaining = 16384, depth = 0;
    if (!memory || !device || !frame || !result || !stop || frame->busy || frame->faulted ||
        (target != 0x8005d6ccu && target != 0x8005d734u)) return 0;
    frame->busy = 1;
    cpu.bios_frame = frame;
    cpu.input_device = device;
    cpu.clock = device->clock;
    cpu.pc = target; cpu.npc = target + 4;
    cpu.r[4] = (uint32_t)argument;
    cpu.r[28] = 0xf450u;
    cpu.r[29] = cpu.r[30] = MUSASHI_BIOS_CALLBACK_STACK_TOP;
    cpu.r[31] = UINT_MAX;
    for (;;) {
        uint32_t instruction;
        stop->call_address = stop->target_address = cpu.pc;
        if (cpu.pc == UINT_MAX) {
            if (depth || cpu.r[29] != MUSASHI_BIOS_CALLBACK_STACK_TOP) break;
            *result = (int32_t)cpu.r[2];
            frame->busy = 0;
            return 1;
        }
        if (cpu.pc == 0x8005d804u || cpu.pc == 0x8005d858u ||
            cpu.pc == 0x8005dc50u || cpu.pc == 0x8005dc88u) {
            static unsigned tap_cb_logs;
            uint32_t slot = 0, stage = 0;
            (void)musashi_boot_read32(memory, 0x800729b4u, &slot);
            (void)musashi_boot_read32(memory, 0x800729a0u, &stage);
            if (tap_cb_logs < 8u || (tap_cb_logs % 4096u) == 0u)
                fprintf(stderr,
                    "native_boot: TAP_CB pc=%08x v0=%08x a0=%08x 29B4=%08x "
                    "29A0=%08x rem=%u\n",
                    cpu.pc, cpu.r[2], cpu.r[4], slot, stage, remaining);
            if (tap_cb_logs != UINT_MAX) ++tap_cb_logs;
        }
        if (!input_callback_word(cpu.pc, &instruction)) break;
        if ((instruction >> 26) == 3 ||
            ((instruction >> 26) == 0 && (instruction & 63u) == 9)) {
            uint32_t call = cpu.pc;
            uint32_t call_sp = cpu.r[29];
            uint32_t resolved = (instruction >> 26) == 3 ?
                ((call + 4u) & 0xf0000000u) | ((instruction & 0x03ffffffu) << 2) :
                cpu.r[(instruction >> 21) & 31u];
            int supported = input_callback_call(memory, &cpu, instruction, resolved);
            /* Sample the indirect target before its delay slot. Unknown calls
             * retain the exact link/delay effects, even for a mapped alias. */
            if (!input_callback_step(memory, &cpu, &remaining, stop) || !input_callback_step(memory, &cpu, &remaining, stop)) break;
            if (supported && cpu.pc == resolved && depth < 8) {
                returns[depth].pc = call + 8u;
                returns[depth++].sp = call_sp;
                continue;
            }
            stop->call_address = call;
            stop->target_address = cpu.pc;
            break;
        }
        if ((instruction >> 26) == 0 && (instruction & 63u) == 8) {
            uint32_t call = cpu.pc;
            uint32_t expected = depth ? returns[depth - 1].pc : UINT_MAX;
            uint32_t expected_sp = depth ? returns[depth - 1].sp : MUSASHI_BIOS_CALLBACK_STACK_TOP;
            int supported = instruction == 0x03e00008u && cpu.r[31] == expected;
            if (!input_callback_step(memory, &cpu, &remaining, stop) || !input_callback_step(memory, &cpu, &remaining, stop)) break;
            if (!supported || cpu.pc != expected || cpu.r[29] != expected_sp) {
                stop->call_address = call;
                stop->target_address = cpu.pc;
                break;
            }
            if (depth) --depth;
            continue;
        }
        if (!input_callback_step(memory, &cpu, &remaining, stop)) break;
    }
    frame->busy = 0;
    frame->faulted = 1;
    return 0;
}

/* No mutable interrupted CPU is accepted. HookEntryInt supplies saved SP;
 * the owned dispatcher accounts for 28 bytes. Ready-callback workers reach
 * savedSP-158 (six nested JALs). PAC LoadImage from 8001A338 nests
 * 800599B8/8005B7B0/8005BA90/8005B1C4 then VSync(-1): 8005C020 reaches
 * savedSP-170, 8005C054 reaches savedSP-178. */
static int cd_irq_word(uint32_t pc, uint32_t *word) {
    if (pc & 3u) return 0;
#define CD_WORD_RANGE(lo,hi,words) \
    if (pc >= (lo) && pc < (hi)) { *word = (words)[(pc-(lo))/4u]; return 1; }
    CD_WORD_RANGE(0x800377d8u,0x80037cc8u,kMain800377D8Words)
    CD_WORD_RANGE(0x80046610u,0x80046630u,kMain80046610Words)
    CD_WORD_RANGE(0x80046d1cu,0x8004768cu,kMain80046D1CWords)
    CD_WORD_RANGE(0x8004768cu,0x800476c0u,kMain8004768CWords)
    CD_WORD_RANGE(0x800476c0u,0x8004787cu,kMain800476C0Words)
    CD_WORD_RANGE(0x80046bfcu,0x80046c38u,kMain80046BFCWords)
    CD_WORD_RANGE(0x800469ccu,0x80046a5cu,kMain800469CCWords)
    CD_WORD_RANGE(0x8004357cu,0x8004359cu,kFile8004357CWords)
    CD_WORD_RANGE(0x800443a4u,0x80044670u,kFile800443A4Words)
    CD_WORD_RANGE(0x80045290u,0x80045374u,kCdIrq80045290Words)
    CD_WORD_RANGE(0x80018714u,0x80018730u,kMain80018714Words)
    CD_WORD_RANGE(0x80018730u,0x80018918u,kMain80018730Words)
    CD_WORD_RANGE(STATUS_WORKER,STATUS_WORKER_END,kStatusWorker80043B9CWords)
    CD_WORD_RANGE(0x80043398u,0x800433c0u,kFile80043398Words)
    CD_WORD_RANGE(0x800433c0u,0x800433e8u,kFile800433C0Words)
    CD_WORD_RANGE(0x800433e8u,0x80043410u,kFile800433E8Words)
    CD_WORD_RANGE(0x8005ce68u,0x8005ce74u,kFile8005CE68Words)
    CD_WORD_RANGE(0x80045d00u,0x80045fd0u,kFile80045D00Words)
    /* LIST mode3/2 and mode0 PAC share this 424-word body. Live boot's
     * size-0 CdRead hits the PAC magic path; unmapped jal/jr edges still
     * refuse instead of executing foreign callees. */
    if (pc >= 0x8001a338u && pc < 0x8001a9d8u) {
        *word=kFile8001A338Words[(pc-0x8001a338u)/4u]; return 1;
    }
    CD_WORD_RANGE(0x800599b8u,0x80059a80u,kMain800599B8Words)
    CD_WORD_RANGE(0x80059760u,0x80059888u,kClearImage80059760Words)
    CD_WORD_RANGE(0x8005b7b0u,0x8005ba90u,kDraw8005B7B0Words)
    CD_WORD_RANGE(0x8005ba90u,0x8005bd7cu,kDraw8005BA90Words)
    CD_WORD_RANGE(0x8005b1c4u,0x8005b400u,kMain8005B1C4Words)
    CD_WORD_RANGE(0x8005b710u,0x8005b75cu,kDraw8005B710Words)
    CD_WORD_RANGE(0x8005c054u,0x8005c1c0u,kMain8005C054Words)
    CD_WORD_RANGE(0x8005c020u,0x8005c054u,kDraw8005C020Words)
    CD_WORD_RANGE(0x800426fcu,0x80042718u,kDraw800426FCWords)
    CD_WORD_RANGE(0x800425e0u,0x80042610u,kSpu800425E0Words)
    CD_WORD_RANGE(0x8001099cu,0x80010a08u,kMain8001099CWords)
    CD_WORD_RANGE(0x8002fb08u,0x8002fc64u,kMain8002FB08Words)
    CD_WORD_RANGE(0x80037cd8u,0x80037d74u,kMain80037CD8Words)
    CD_WORD_RANGE(0x800301a4u,0x800301c8u,kMain800301A4Words)
    CD_WORD_RANGE(0x80031a98u,0x80031b7cu,kMain80031A98Words)
    CD_WORD_RANGE(0x80030d80u,0x80030f80u,kMain80030D80Words)
    CD_WORD_RANGE(0x8002ec10u,0x8002ed90u,kMain8002EC10Words)
    CD_WORD_RANGE(0x8003836cu,0x800383a4u,kMain8003836CWords)
    CD_WORD_RANGE(0x800383a4u,0x800384a8u,kMain800383A4Words)
    CD_WORD_RANGE(0x800384a8u,0x800385c0u,kMain800384A8Words)
    CD_WORD_RANGE(0x800385c0u,0x80038638u,kMain800385C0Words)
    CD_WORD_RANGE(0x8002eff8u,0x8002f064u,kMain8002EFF8Words)
    CD_WORD_RANGE(0x80031988u,0x80031a98u,kMain80031988Words)
    CD_WORD_RANGE(0x8003916cu,0x800391d4u,kMain8003916CWords)
    CD_WORD_RANGE(0x800415a8u,0x8004162cu,kMain800415A8Words)
    CD_WORD_RANGE(0x8004162cu,0x800416a8u,kMain8004162CWords)
    CD_WORD_RANGE(0x800416a8u,0x800419b0u,kMain800416A8Words)
    CD_WORD_RANGE(0x8002fc64u,0x8002fd14u,kMain8002FC64Words)
    CD_WORD_RANGE(0x8002fdc8u,0x8002fde8u,kMain8002FDC8Words)
    CD_WORD_RANGE(0x8003c438u,0x8003c498u,kMain8003C438Words)
    CD_WORD_RANGE(0x8003c498u,0x8003c4f0u,kMain8003C498Words)
    CD_WORD_RANGE(0x8003c4f0u,0x8003c598u,kMain8003C4F0Words)
    CD_WORD_RANGE(0x8003ae14u,0x8003ae9cu,kMain8003AE14Words)
    CD_WORD_RANGE(0x80037d74u,0x80037d98u,kMain80037D74Words)
    CD_WORD_RANGE(0x8003af4cu,0x8003aff0u,kMain8003AF4CWords)
    CD_WORD_RANGE(0x8003ab84u,0x8003ae14u,kMain8003AB84Words)
    CD_WORD_RANGE(0x8003a84cu,0x8003aa18u,kSpu8003A84CWords)
    CD_WORD_RANGE(0x8003b08cu,0x8003b0b8u,kMain8003B08CWords)
    CD_WORD_RANGE(0x8003b0b8u,0x8003b0e4u,kMain8003B0B8Words)
    CD_WORD_RANGE(0x8003b0e4u,0x8003b14cu,kSpu8003B0E4Words)
    CD_WORD_RANGE(0x80043994u,0x800439b4u,kFile80043994Words)
    CD_WORD_RANGE(0x80045090u,0x80045190u,kFile80045090Words)
    CD_WORD_RANGE(0x80043b1cu,0x80043b9cu,kFile80043B1CWords)
    CD_WORD_RANGE(0x8004359cu,0x800435b4u,kStartupCallbackSetter8004359CWords)
    CD_WORD_RANGE(0x800435b4u,0x800435ccu,kStartupCallbackSetter800435B4Words)
    CD_WORD_RANGE(0x80043704u,0x80043830u,kFile80043704Words)
    CD_WORD_RANGE(CD_INITIALIZER_COMMAND,CD_COMMAND_END,kCdCommandFullWords)
    CD_WORD_RANGE(TICK_QUERY_ENTRY,TICK_QUERY_BRANCH_END,kTickQuery8004239CMinusOneWords)
    if (pc >= TICK_QUERY_RETURN && pc < TICK_QUERY_RETURN_END) {
        *word=kTickQuery8004239CMinusOneWords[25u+(pc-TICK_QUERY_RETURN)/4u]; return 1;
    }
    CD_WORD_RANGE(STATUS_FIRST_POLL,STATUS_FIRST_POLL_END,kStatusFirstPoll80044124Words)
    CD_WORD_RANGE(STATUS_TIMEOUT,STATUS_TIMEOUT_END,kStatusTimeout80044198Words)
    CD_WORD_RANGE(STATUS_TIMEOUT_DIAGNOSTIC,STATUS_DIAGNOSTIC_END,kStatusDiagnostic800441D8Words)
    if (pc == STATUS_TIMEOUT_CONTINUE) { *word=0x00001021u; return 1; }
    CD_WORD_RANGE(STATUS_POST_DIAGNOSTIC,STATUS_LOOP_END,kStatusLoop80044250Words)
    CD_WORD_RANGE(STATUS_READY_QUERY,STATUS_READY_QUERY+16u,kReadyQuery800426D4Words)
#undef CD_WORD_RANGE
    return 0;
}
static int cd_irq_pointers(MusashiBootMemory *memory) {
    unsigned i;
    uint32_t value;
    for (i = 0; i < 4; ++i)
        if (!musashi_boot_read32(memory, 0x8006cf4cu + 4u*i, &value) ||
            value != 0x1f801800u+i) return 0;
    return 1;
}
typedef struct CdIrqReturn {
    uint32_t pc, sp, a0, a1, target;
} CdIrqReturn;
/* A renewed non-decoder allowance requires strictly increasing output and
 * consecutive source sector identities. It cannot hide a stuck decode loop. */
static int cd_irq_pac_progress(uint32_t start, uint32_t end, uint32_t lba,
                               uint32_t previous_end, uint32_t previous_lba) {
    return start >= 0x80000000u && end <= 0x80200000u && end > start &&
        (previous_lba == UINT_MAX ||
         (previous_lba < UINT_MAX-1u && lba == previous_lba+1u && start == previous_end));
}
/* Source1A740 walks a 64-byte bitmap, one bit per 32x32 VRAM tile.
 * Its one-hot mask and byte index give a bounded, monotonic progress key. */
static int cd_irq_image_cursor(uint32_t packed, uint32_t *tile) {
    unsigned mask = (packed >> 16) & 255u, index = packed >> 24, bit = 0;
    if (!mask || (mask & (mask-1u)) || index > 64u || (index == 64u && mask != 1u))
        return 0;
    while (mask > 1u) { mask >>= 1; ++bit; }
    *tile = index*8u+bit;
    return 1;
}
static int cd_irq_sector_progress(uint32_t before, uint32_t after, uint32_t previous) {
    return before < UINT_MAX && after == before+1u &&
        (previous == UINT_MAX || before == previous);
}
/* Only completed active bank states count as productive sector work.
 * A header alone can advance the LBA even on a no-op or error path. */
static int cd_irq_bank_progress(unsigned before_state, unsigned after_state,
    uint32_t before, uint32_t after, uint32_t previous) {
    return before_state >= 1u && before_state <= 3u &&
        after_state >= 1u && after_state <= 4u &&
        cd_irq_sector_progress(before,after,previous);
}
static int cd_irq_ram_word(MusashiBootMemory *memory, uint32_t address, uint32_t expected) {
    uint32_t value;
    return musashi_boot_read32(memory,address,&value) && value == expected;
}
static int cd_irq_data_pointers(MusashiBootMemory *memory) {
    static const uint32_t slots[][2] = {
        {0x8006cf5cu,0x1f801020u}, {0x8006cf80u,0x1f801018u},
        {0x8006cf84u,0x1f8010f0u}, {0x8006cf88u,0x1f8010b0u},
        {0x8006cf8cu,0x1f8010b4u}, {0x8006cf90u,0x1f8010b8u}
    };
    unsigned i;
    for (i=0;i<sizeof(slots)/sizeof(slots[0]);++i)
        if (!cd_irq_ram_word(memory,slots[i][0],slots[i][1])) return 0;
    return 1;
}
/* These guards see the real argument registers AFTER the JAL delay slot.
 * Parent returnPC/depth and callSP bind each edge to the closed source tree.
 * No mapped body alone authorizes a call. */
static int cd_irq_call(MusashiBootMemory *memory, const FormatterCpu *cpu,
    const MusashiCdIrqServices *services, const CdIrqReturn *returns,
    unsigned depth, uint32_t saved_sp, uint32_t call, uint32_t instruction) {
    uint32_t parent=depth ? returns[depth-1].pc : 0u;
    uint32_t a0=cpu->r[4], a1=cpu->r[5], sp=cpu->r[29], target=cpu->pc, live;
    uint8_t kind;
    int ready=depth && returns[0].target == 0x80045d00u && returns[0].pc == 0x80045308u &&
        returns[0].sp == saved_sp-0x50u;
    int list=depth && returns[0].target == 0x8001a338u && returns[0].pc == 0x80045308u &&
        returns[0].sp == saved_sp-0x50u;
    int bank=depth && returns[0].target == 0x800377d8u &&
        returns[0].pc == 0x80045308u && returns[0].sp == saved_sp-0x50u;
    int inline_poll=ready && depth == 4 && parent == 0x8004473cu &&
        returns[1].pc == 0x80045f88u && returns[2].pc == 0x800437dcu &&
        sp == saved_sp-0x128u;
    /* All direct calls have the canonical JAL encoding. */
    if ((instruction >> 26) == 3) {
        if (instruction != (0x0c000000u|((target>>2)&0x03ffffffu))) return 0;
    } else if (instruction != (call == 0x80045fb4u ? 0x0060f809u : 0x0040f809u)) return 0;
    /* Sound-bank reader: a distinct ready-callback tree, never a list-root
     * alias. Arguments are inspected after each retail delay slot. */
    if (bank) {
        switch (call) {
        case 0x80037800u:
            return depth == 1 && sp == saved_sp-0x70u && target == 0x80043994u &&
                a0 == 0x800762a0u && a1 == 3u;
        case 0x80037810u:
            return depth == 1 && sp == saved_sp-0x70u && target == 0x80043b1cu &&
                a0 == 0x800762a0u;
        case 0x8003787cu: case 0x800379fcu: case 0x80037a90u:
            return depth == 1 && sp == saved_sp-0x70u && target == 0x80043994u &&
                a1 == 0x200u && cd_irq_ram_word(memory,0x80076228u,a0) &&
                musashi_boot_ram_span(memory,a0,0x800u) != NULL;
        case 0x8004399cu:
            return depth == 2 && sp == saved_sp-0x88u &&
                (parent == 0x80037808u || parent == 0x80037884u ||
                 parent == 0x80037a04u || parent == 0x80037a98u) &&
                target == 0x80045090u && cd_irq_data_pointers(memory) &&
                a0 == returns[1].a0 && a1 == returns[1].a1;
        case 0x80037a68u: case 0x80037ac4u:
            return depth == 1 && sp == saved_sp-0x70u && target == 0x8003c4f0u && !a0;
        case 0x80037adcu:
            return depth == 1 && sp == saved_sp-0x70u && target == 0x8003c498u &&
                cd_irq_ram_word(memory,0x80076238u,a0);
        case 0x80037b10u: case 0x80037c2cu: {
            uint16_t length;
            if (depth != 1 || sp != saved_sp-0x70u || target != 0x8003c438u ||
                !cd_irq_ram_word(memory,0x80076228u,a0)) return 0;
            if (call == 0x80037c2cu) return a1 == 0x800u;
            return a0 >= 2u && musashi_boot_read16(memory,a0-2u,&length) &&
                a1 == (uint32_t)(int32_t)(int16_t)length;
        }
        case 0x8003c538u: case 0x8003c558u:
            return depth == 2 && sp == saved_sp-0x90u &&
                (parent == 0x80037a70u || parent == 0x80037accu) &&
                target == 0x8005cea8u && services->event && services->event->b0_0b &&
                cd_irq_ram_word(memory,0x8006b0e0u,a0);
        case 0x8003c4b8u:
            return depth == 2 && sp == saved_sp-0x88u && parent == 0x80037ae4u &&
                target == 0x8003af4cu && a0 == UINT_MAX && a1 == returns[1].a0;
        case 0x8003c460u:
            return depth == 2 && sp == saved_sp-0x88u &&
                (parent == 0x80037b18u || parent == 0x80037c34u) &&
                target == 0x8003ae14u && a0 == returns[1].a0 &&
                a1 == (returns[1].a1 > 0x7eff0u ? 0x7eff0u : returns[1].a1);
        case 0x8003ae4cu: case 0x8003ae54u: case 0x8003ae64u:
        case 0x8003aec8u: case 0x8003aed0u: case 0x8003aee0u:
            return depth == 3 && sp == saved_sp-0xa8u && parent == 0x8003c468u &&
                target == 0x8003ab84u;
        case 0x8003ae78u:
            return depth == 3 && sp == saved_sp-0xa8u && parent == 0x8003c468u &&
                target == 0x8003a84cu;
        case 0x8003a884u: case 0x8003a8ecu:
        case 0x8003a964u: case 0x8003a96cu:
            return depth == 4 && sp == saved_sp-0xd8u && parent == 0x8003ae80u &&
                target == 0x8003b0e4u;
        case 0x8003ad5cu: case 0x8003ad6cu:
            return depth == 4 && sp == saved_sp-0xc0u &&
                (parent == 0x8003ae54u || parent == 0x8003ae5cu || parent == 0x8003ae6cu ||
                 parent == 0x8003aed0u || parent == 0x8003aed8u || parent == 0x8003aee8u) &&
                target == (call == 0x8003ad5cu ? 0x8003b0b8u : 0x8003b08cu);
        default: return 0;
        }
    }
    /* Movie ready callback: fixed source JAL edges under its live root.
     * Indirect callbacks remain individually checked below, never inferred. */
    if (g_overlay_0004_words && depth && returns[0].target==0x80046610u &&
        returns[0].pc==0x80045308u && returns[0].sp==saved_sp-0x50u &&
        depth<16u && sp<=saved_sp-0x50u && sp>=saved_sp-0x200u) {
        static const uint32_t stream_edges[][2] = {
            {0x80046618u,0x80046d1cu}, {0x80046da8u,0x8004357cu},
            {0x80043584u,0x800443a4u}, {0x800443d4u,0x8004239cu},
            {0x80044418u,0x8004239cu}, {0x800444e0u,0x800426d4u}, {0x80044508u,0x80043b9cu},
            {0x80046f58u,0x8004768cu},
            {0x80046f84u,0x800476c0u}, {0x80047168u,0x80046bfcu},
            {0x80047238u,0x80046bfcu}, {0x8004752cu,0x8004768cu},
            {0x80047570u,0x800476c0u}, {0x800475d0u,0x8004768cu},
            {0x80047614u,0x800476c0u}, {0x80047674u,0x800469ccu}
        };
        unsigned i;
        for (i=0;i<sizeof(stream_edges)/sizeof(stream_edges[0]);++i)
            if(call==stream_edges[i][0] && target==stream_edges[i][1]) return 1;
    }
    switch (call) {
    case 0x80044544u:
        return g_overlay_0004_words && depth == 4 &&
            returns[0].target == 0x80046610u && returns[0].pc == 0x80045308u &&
            returns[1].pc == 0x80046620u && returns[2].pc == 0x80046db0u &&
            parent == 0x8004358cu && sp == saved_sp-0x100u &&
            target == 0x80046610u && cd_irq_ram_word(memory,0x8006cc88u,target) &&
            read8(memory,0x8006cf65u,&kind) && a0 == kind && a1 == 0x800763e0u;
    case 0x800452c4u:
        return !depth && target == STATUS_WORKER && sp == saved_sp-0x50u;
    case 0x80045334u:
    case 0x800442f0u:
        return (call == 0x80045334u ? !depth && sp == saved_sp-0x50u : inline_poll) &&
            services->deliver_event && target == 0x80043398u &&
            cd_irq_ram_word(memory,0x8006cc84u,target) &&
            read8(memory,0x8006cf64u,&kind) && a0 == kind && a1 == 0x800763d8u;
    case 0x80045300u:
        if (depth || sp != saved_sp-0x50u || !services->deliver_event ||
            !cd_irq_ram_word(memory,0x8006cc88u,target) ||
            !read8(memory,0x8006cf65u,&kind) || a0 != kind || a1 != 0x800763e0u)
            return 0;
        if (target == 0x800377d8u)
            return kind == 1 && cpu->cd_register_device &&
                cpu->cd_register_device->read32 && cpu->cd_register_device->write32 &&
                cd_irq_data_pointers(memory);
        /* A restored live ready callback really delivers its BIOS event. */
        if (target == 0x800433c0u) return kind == 1;
        if (target == 0x80046610u)
            return g_overlay_0004_words && kind==1 && services->callback_device &&
                cpu->cd_register_device && cpu->cd_register_device->read32 &&
                cpu->cd_register_device->write32 && cd_irq_data_pointers(memory);
        if (target == 0x8001a338u)
            return (kind == 1 || kind == 2 || kind == 3) &&
                cpu->cd_register_device->read32 && cpu->cd_register_device->write32 &&
                cd_irq_data_pointers(memory) &&
                musashi_boot_read32(memory,0x800ae6f8u,&live) &&
                (live <= 7u);
        return target == 0x80045d00u && kind == 1 && services->callback_device &&
            cpu->cd_register_device->read32 && cpu->cd_register_device->write32 &&
            cd_irq_data_pointers(memory) &&
            cd_irq_ram_word(memory,0x8006cfb4u,1u) &&
            cd_irq_ram_word(memory,0x8006cfb0u,0x200u) &&
            musashi_boot_read32(memory,0x8006cfd0u,&live) && !(live&1u);
    case 0x80045d9cu:
    case 0x80045e2cu:
        if (!ready || depth != 1 || sp != saved_sp-0x78u || target != 0x80043994u ||
            !musashi_boot_read32(memory,0x8006cfd0u,&live) || (live&1u) ||
            !cd_irq_ram_word(memory,0x8006cfb0u,0x200u)) return 0;
        if (call == 0x80045d9cu) return a0 == sp+0x10u && a1 == 3u;
        return a1 == 0x200u && cd_irq_ram_word(memory,0x8006cfa8u,a0) &&
            musashi_boot_ram_span(memory,a0,0x800u) != NULL;
    case 0x8004399cu:
        return depth == 2 &&
            ((ready && (parent == 0x80045da4u || parent == 0x80045e34u) && sp == saved_sp-0x90u) ||
             (list && (parent == 0x8001a384u || parent == 0x8001a418u ||
                       parent == 0x8001a478u || parent == 0x8001a4f8u ||
                       parent == 0x8001a71cu ||
                       parent == 0x8001a814u || parent == 0x8001a828u ||
                       parent == 0x8001a878u || parent == 0x8001a8bcu ||
                       parent == 0x8001a90cu) &&
              sp == saved_sp-0xa0u)) &&
            target == 0x80045090u && cd_irq_data_pointers(memory) &&
            a0 == returns[1].a0 && a1 == returns[1].a1;
    case 0x8001a37cu:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x80078e40u && a1 == 3u;
    case 0x8001a410u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x80079a70u && a1 == 4u;
    case 0x8001a470u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x8007a280u && a1 == 0x1fcu;
    case 0x8001a4f0u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x800ae758u && a1 == 0x10u;
    case 0x8001a494u:
    case 0x8001a720u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x800599b8u;
    case 0x8001a6a4u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x8002fb08u;
    case 0x8001a6ecu:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80018714u &&
            cd_irq_ram_word(memory,0x800ae72cu,a0) &&
            cd_irq_ram_word(memory,0x800ae728u,a0);
    case 0x8001a904u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x80079a70u && a1 == 0x200u;
    case 0x8001a90cu:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80018730u &&
            a0 == 0x80079a70u;
    case 0x8002fb20u:
        return list && depth == 2 && parent == 0x8001a6acu &&
            target == 0x80037cd8u && sp == saved_sp-0xa0u;
    case 0x80037d14u:
        /* jalr $v0 at 80037D14; 80037D18 is the delay nop. Live PAC INT1
         * refused the delay-slot case. All retail jals to 80037CD8. */
        return list && depth == 3 &&
            (parent == 0x8002fb28u || parent == 0x80030398u ||
             parent == 0x80030488u || parent == 0x80036640u) &&
            target == 0x800301a4u && sp == saved_sp-0xc0u;
    case 0x8002fba8u:
        return list && depth == 2 && parent == 0x8001a6acu &&
            target == 0x80031a98u && sp == saved_sp-0xa0u;
    case 0x8002fbe8u:
        return list && depth == 2 && parent == 0x8001a6acu &&
            target == 0x8002ec10u && sp == saved_sp-0xa0u;
    case 0x8002fbfcu:
        return list && depth == 2 && parent == 0x8001a6acu &&
            target == 0x800415a8u && sp == saved_sp-0xa0u;
    case 0x80031b48u:
        return list && depth == 3 && parent == 0x8002fbb0u &&
            target == 0x80030d80u && sp == saved_sp-0xc0u;
    case 0x80030ef0u:
    case 0x80030f1cu:
        return list && depth == 4 && parent == 0x80031b50u &&
            target == 0x8002eff8u && sp == saved_sp-0xe8u;
    case 0x80030f24u:
        return list && depth == 4 && parent == 0x80031b50u &&
            target == 0x80031988u && sp == saved_sp-0xe8u;
    case 0x8002ec50u:
    case 0x8002ed3cu:
        return list && depth == 3 && parent == 0x8002fbf0u &&
            target == 0x8003836cu && sp == saved_sp-0xb8u;
    case 0x8002ecb0u:
    case 0x8002ed74u:
        return list && depth == 3 && parent == 0x8002fbf0u &&
            target == 0x800385c0u && sp == saved_sp-0xb8u;
    case 0x8002ecd8u:
        return list && depth == 3 && parent == 0x8002fbf0u &&
            target == 0x800383a4u && sp == saved_sp-0xb8u;
    case 0x8002ed54u:
        return list && depth == 3 && parent == 0x8002fbf0u &&
            target == 0x800384a8u && sp == saved_sp-0xb8u;
    case 0x80038438u:
        return list && depth == 4 && parent == 0x8002ece0u &&
            target == 0x8003916cu && sp == saved_sp-0xf0u;
    case 0x80038444u:
        return list && depth == 4 && parent == 0x8002ece0u &&
            target == 0x8002eff8u && sp == saved_sp-0xf0u;
    case 0x80038540u:
        return list && depth == 4 && parent == 0x8002ed5cu &&
            target == 0x8003916cu && sp == saved_sp-0xf0u;
    case 0x8003854cu:
        return list && depth == 4 && parent == 0x8002ed5cu &&
            target == 0x8002eff8u && sp == saved_sp-0xf0u;
    case 0x800415ecu:
        return list && depth == 3 && parent == 0x8002fc04u &&
            target == 0x8004162cu && sp == saved_sp-0xb8u;
    case 0x80041690u:
        return list && depth == 4 && parent == 0x800415f4u &&
            target == 0x800416a8u && sp == saved_sp-0xd8u;
    case 0x800599d8u:
        return list && depth == 2 && parent == 0x8001a728u &&
            target == 0x80059760u && sp == saved_sp-0xa8u;
    case 0x800599fcu:
        return list && depth == 2 && parent == 0x8001a728u &&
            target == 0x8005b7b0u && sp == saved_sp-0xa8u &&
            cpu->gpu_io_device && cpu->gpu_io_device->write32;
    case 0x8005b7d4u:
        return list && depth == 3 && parent == 0x80059a04u &&
            target == 0x8005c020u;
    case 0x8005c028u:
        return list && target == TICK_QUERY_ENTRY && a0 == UINT_MAX &&
            services->callback_device &&
            cd_irq_ram_word(memory,0x8006ba94u,0x1f801814u) &&
            cd_irq_ram_word(memory,0x8006ba98u,0x1f801110u);
    case 0x8005b81cu:
    case 0x8005ba44u:
        return list && depth == 3 && parent == 0x80059a04u &&
            target == 0x800426fcu && services->callback_device;
    case 0x8005bab8u:
    case 0x8005bcd0u:
        return list && depth == 4 && parent == 0x8005ba54u &&
            target == 0x800426fcu && services->callback_device;
    case 0x8005ba4cu:
        return list && depth == 3 && parent == 0x80059a04u &&
            target == 0x8005ba90u && cpu->gpu_io_device && cpu->gpu_io_device->write32;
    case 0x8005bbe4u:
        return list && depth == 4 && parent == 0x8005ba54u &&
            (target == 0x8005b1c4u || target == 0x8005b710u) &&
            cpu->gpu_io_device;
    case 0x8005bd44u:
        return list && depth == 4 && parent == 0x8005ba54u &&
            target == 0x8001099cu;
    case 0x800109bcu:
        return list && depth == 5 && parent == 0x8005bd4cu &&
            target == TICK_QUERY_ENTRY && a0 == 1u && services->callback_device &&
            cd_irq_ram_word(memory,0x8006ba94u,0x1f801814u) &&
            cd_irq_ram_word(memory,0x8006ba98u,0x1f801110u);
    case 0x8005b1e8u:
        return list && depth == 5 && parent == 0x8005bbecu &&
            target == 0x8005c020u;
    case 0x8005b2c8u:
        return list && depth == 5 && parent == 0x8005bbecu &&
            target == 0x8005c054u;
    case 0x8005b900u:
        return list && depth == 3 && parent == 0x80059a04u &&
            target == 0x800425e0u;
    case 0x800425f8u:
        return list && depth == 4 && parent == 0x8005b908u &&
            target == 0x80042f8cu && services->dma;
    case 0x8001a714u:
    case 0x8001a8b4u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a1 == 0x200u;
    case 0x8001a870u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043994u &&
            a0 == 0x80079a70u && cd_irq_ram_word(memory,0x800ae6f8u,4u);
    case 0x8001a87cu:
    case 0x8001a8c0u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x8002fc64u;
    case 0x8001a8e4u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x8002fdc8u;
    case 0x8002fc90u:
        return list && depth == 2 &&
            (parent == 0x8001a884u || parent == 0x8001a8c8u) &&
            target == 0x8003c4f0u && sp == saved_sp-0xa8u;
    case 0x8003c538u:
    case 0x8003c558u:
        return list && depth == 3 && parent == 0x8002fc98u &&
            target == 0x8005cea8u && sp == saved_sp-0xc8u &&
            services->event && services->event->b0_0b;
    case 0x8002fcacu:
        return list && depth == 2 &&
            (parent == 0x8001a884u || parent == 0x8001a8c8u) &&
            target == 0x8003c498u && sp == saved_sp-0xa8u;
    case 0x8002fcbcu:
        return list && depth == 2 &&
            (parent == 0x8001a884u || parent == 0x8001a8c8u) &&
            target == 0x80037d74u && sp == saved_sp-0xa8u;
    case 0x8002fcccu:
        return list && depth == 2 &&
            (parent == 0x8001a884u || parent == 0x8001a8c8u) &&
            target == 0x8003c438u && sp == saved_sp-0xa8u;
    case 0x8002fdd0u:
        return list && depth == 2 && parent == 0x8001a8ecu &&
            target == 0x80037d74u && sp == saved_sp-0xa0u;
    case 0x8003c4b8u:
        return list && depth == 3 && parent == 0x8002fcb4u &&
            target == 0x8003af4cu && sp == saved_sp-0xc0u;
    case 0x8003c460u:
        return list && depth == 3 && parent == 0x8002fcd4u &&
            target == 0x8003ae14u && sp == saved_sp-0xc0u;
    case 0x8003ae4cu:
    case 0x8003ae54u:
    case 0x8003ae64u:
    case 0x8003aec8u:
    case 0x8003aed0u:
    case 0x8003aee0u:
        return list && depth == 4 && parent == 0x8003c468u &&
            target == 0x8003ab84u && sp == saved_sp-0xe0u;
    case 0x8003ae78u:
        return list && depth == 4 && parent == 0x8003c468u &&
            target == 0x8003a84cu && sp == saved_sp-0xe0u;
    case 0x8003ad5cu:
        return list && depth == 5 &&
            (parent == 0x8003ae54u || parent == 0x8003ae5cu || parent == 0x8003ae6cu ||
             parent == 0x8003aed0u || parent == 0x8003aed8u || parent == 0x8003aee8u) &&
            target == 0x8003b0b8u && sp == saved_sp-0xf8u;
    case 0x8003ad6cu:
        return list && depth == 5 &&
            (parent == 0x8003ae54u || parent == 0x8003ae5cu || parent == 0x8003ae6cu ||
             parent == 0x8003aed0u || parent == 0x8003aed8u || parent == 0x8003aee8u) &&
            target == 0x8003b08cu && sp == saved_sp-0xf8u;
    case 0x8001a384u:
        return list && depth == 1 && sp == saved_sp-0x88u && target == 0x80043b1cu &&
            a0 == 0x80078e40u;
    case 0x8001a80cu:
    case 0x8001a820u:
        if (!list || depth != 1 || sp != saved_sp-0x88u || target != 0x80043994u ||
            !cd_irq_ram_word(memory,0x800ae6f8u,3u) ||
            !cd_irq_ram_word(memory,0x800ae728u,a0) ||
            !musashi_boot_read32(memory,0x800ae748u,&live) || !live || live > INT32_MAX ||
            (a0 & 3u)) return 0;
        return a1 == (call == 0x8001a80cu ? live : 512u) &&
            (call == 0x8001a80cu ? live <= 512u : live > 512u) &&
            musashi_boot_ram_span(memory,a0,a1*4u) != NULL;
    case 0x80045da4u:
        return ready && depth == 1 && sp == saved_sp-0x78u &&
            target == 0x80043b1cu && a0 == sp+0x10u;
    case 0x80045ea4u:
    case 0x80045ed0u:
    case 0x80044150u:
    case 0x80044190u:
        return (call < 0x80045000u ? inline_poll : ready && depth == 1 && sp == saved_sp-0x78u) &&
            target == TICK_QUERY_ENTRY && a0 == UINT_MAX && services->callback_device &&
            cd_irq_ram_word(memory,0x8006ba94u,0x1f801814u) &&
            cd_irq_ram_word(memory,0x8006ba98u,0x1f801110u);
    case 0x80045f3cu:
    case 0x80045f4cu:
        live=call == 0x80045f3cu ? 0x80043398u : 0x800433c0u;
        return ready && depth == 1 && sp == saved_sp-0x78u &&
            target == (call == 0x80045f3cu ? 0x8004359cu : 0x800435b4u) &&
            a0 == live && cd_irq_ram_word(memory,call == 0x80045f3cu ? 0x8006cfc4u : 0x8006cfc8u,live) &&
            cd_irq_ram_word(memory,0x8006cfb4u,0u);
    case 0x80045f80u:
        return ready && depth == 1 && sp == saved_sp-0x78u && target == 0x80043704u &&
            a0 == 9u && !a1 && cd_irq_ram_word(memory,0x8006cc84u,0x80043398u) &&
            cd_irq_ram_word(memory,0x8006cc88u,0x800433c0u);
    case 0x800437d4u:
        return ready && depth == 2 && parent == 0x80045f88u && sp == saved_sp-0xa8u &&
            target == CD_INITIALIZER_COMMAND && a0 == 9u && !a1 && !cpu->r[6] && cpu->r[7] == 1u;
    case 0x80044734u:
        return ready && depth == 3 && parent == 0x800437dcu && returns[1].pc == 0x80045f88u &&
            sp == saved_sp-0xf0u && target == STATUS_FIRST_POLL && !a0 && !a1;
    case 0x80044258u:
        return inline_poll && target == STATUS_READY_QUERY;
    case 0x80044280u:
        return inline_poll && target == STATUS_WORKER;
    case 0x800442bcu:
        return inline_poll && services->deliver_event && target == 0x800433c0u &&
            cd_irq_ram_word(memory,0x8006cc88u,target) &&
            read8(memory,0x8006cf65u,&kind) && a0 == kind && a1 == 0x800763e0u;
    case 0x80045fb4u:
        return ready && depth == 1 && sp == saved_sp-0x78u && target == 0x800433e8u &&
            services->deliver_event && cd_irq_ram_word(memory,0x8006cf9cu,target) &&
            cd_irq_ram_word(memory,0x8006cfb4u,0u) && a0 == 2u && a1 == returns[0].a1;
    case 0x800433a8u:
        return services->deliver_event && target == 0x8005ce68u && a0 == 0xf0000003u && a1 == 0x20u &&
            ((depth == 1 && parent == 0x8004533cu && sp == saved_sp-0x68u) ||
             (ready && depth == 5 && parent == 0x800442f8u && sp == saved_sp-0x140u));
    case 0x800433d0u:
        return ((ready && depth == 5 && parent == 0x800442c4u && sp == saved_sp-0x140u) ||
                (depth == 1 && parent == 0x80045308u && returns[0].target == 0x800433c0u &&
                 sp == saved_sp-0x68u)) &&
            services->deliver_event && target == 0x8005ce68u && a0 == 0xf0000003u && a1 == 0x40u;
    case 0x800433f8u:
        return ready && depth == 2 && parent == 0x80045fbcu && sp == saved_sp-0x90u &&
            services->deliver_event && target == 0x8005ce68u && a0 == 0xf0000003u && a1 == 0x40u;
    default: return 0;
    }
}
int musashi_boot_execute_cd_irq_with_services(MusashiBootMemory *memory,
    const MusashiCdRegisterDevice *device, const MusashiExecutionClock *clock,
    const MusashiCdIrqServices *services, MusashiCdIrqFrame *frame, uint32_t context, uint32_t target,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu = {0};
    CdIrqReturn returns[16];
    MusashiCdIrqServices selected = {0};
    uint32_t saved_pc, saved_sp;
    unsigned remaining = 16384, depth = 0;
    /* 80018730 consumes 2048 compressed bytes. A 16-bit match token copies
     * at most 65 bytes (upper six bits + 2). Allowing 1025 match tokens,
     * 16 instructions per copied byte and 128 per input byte gives fewer
     * than 1,329,000 instructions. Keep this separate from the IRQ bound. */
    const unsigned decode_limit = 2097152;
    unsigned decode_remaining = 0;
    uint32_t bank_lba = 0, previous_bank_lba = UINT_MAX;
    uint8_t bank_state = 0;
    unsigned pio_remaining = 0;
    int pio_budget_granted = 0, pio_completed = 0;
    uint32_t pio_lba = 0;
    uint32_t decode_start = 0, decode_lba = 0;
    uint32_t previous_decode_end = 0, previous_decode_lba = UINT_MAX;
    uint32_t image_start = 0, image_lba = 0, previous_image_end = 0;
    uint32_t previous_image_lba = UINT_MAX;
    int image_call = 0;
    uint32_t list_mode = 0, list_lba = 0, previous_list_lba = UINT_MAX;
    if (!frame) return 0;
    if (frame->busy) { frame->faulted = 1; return 0; }
    if (frame->faulted) return 0;
    frame->busy = 1;
    frame->instructions = 0;
    frame->budget_exhausted = 0;
    if (stop) { stop->call_address = target; stop->target_address = target; }
    if (!memory || !device || !device->read8 || !device->write8 || !clock ||
        !clock->advance || !stop || context != 0x8006bb34u || target != 0x80045290u ||
        !musashi_boot_read32(memory, context, &saved_pc) || saved_pc != 0x80042780u ||
        !musashi_boot_read32(memory, context+4u, &saved_sp) || saved_sp != 0x8006cb14u ||
        !cd_irq_pointers(memory)) goto fault;
    if (services) selected = *services;
    cpu.pc = target; cpu.npc = target+4u;
    cpu.r[29] = saved_sp-0x28u;
    cpu.r[31] = UINT_MAX;
    cpu.cd_register_device = device;
    cpu.callback_device = selected.callback_device;
    cpu.gpu_io_device = selected.gpu_io;
    cpu.cd_spu_device = selected.cd_spu;
    cpu.clock = clock;
    cpu.cd_irq_frame = frame;
    for (;;) {
        uint32_t instruction, expected = 0, expected_sp = 0, call;
        int transfer = 0, accepted = 1;
        stop->call_address = stop->target_address = cpu.pc;
        uint32_t live_context_pc, live_context_sp;
        if (frame->faulted || !cd_irq_pointers(memory) ||
            !musashi_boot_read32(memory,context,&live_context_pc) || live_context_pc != saved_pc ||
            !musashi_boot_read32(memory,context+4u,&live_context_sp) || live_context_sp != saved_sp) break;
        if (cpu.pc == UINT_MAX) {
            if (depth || cpu.r[29] != saved_sp-0x28u) break;
            frame->busy = 0;
            return 1;
        }
        if (cpu.pc == 0x80042f8cu) {
            uint32_t previous;
            if (!selected.dma ||
                !musashi_boot_call_80042f8c(memory, selected.dma, (int32_t)cpu.r[4],
                                            cpu.r[5], &previous))
                break;
            cpu.r[2] = previous;
            if (depth && returns[depth-1].target == 0x80042f8cu) --depth;
            if (!formatter_return(&cpu)) break;
            continue;
        }
        if (cpu.pc == 0x8005cea8u) {
            int32_t service_result;
            if (!selected.event || !selected.event->b0_0b ||
                !selected.event->b0_0b(selected.event->userdata, (int32_t)cpu.r[4],
                                       &service_result))
                break;
            cpu.r[2] = (uint32_t)service_result;
            if (depth && returns[depth-1].target == 0x8005cea8u) --depth;
            if (!formatter_return(&cpu)) break;
            continue;
        }
        if (depth && returns[0].pc == 0x80045308u &&
            (returns[0].target == 0x80045d00u || returns[0].target == 0x8001a338u ||
             returns[0].target == 0x800377d8u) &&
            !cd_irq_data_pointers(memory)) break;
        /* The movie's inline CD poll adds one nested ready callback.
         * Keep its source stack bounded separately from the existing lanes. */
        uint32_t stack_bytes = g_overlay_0004_words && depth &&
            returns[0].target == 0x80046610u ? 0x200u : 0x178u;
        if (cpu.r[29] < saved_sp-stack_bytes || cpu.r[29] > saved_sp-0x28u ||
            (cpu.r[29] & 3u) || !cd_irq_word(cpu.pc, &instruction)) break;
        call = cpu.pc;
        if ((instruction >> 26) == 3 ||
            ((instruction >> 26) == 0 && (instruction & 63u) == 9)) {
            expected = (instruction >> 26) == 3 ?
                ((call+4u)&0xf0000000u)|((instruction&0x03ffffffu)<<2) :
                cpu.r[(instruction>>21)&31u];
            /* Exact edge/argument guard runs after the real delay slot. */
            accepted = depth < sizeof(returns)/sizeof(returns[0]);
            expected_sp = cpu.r[29];
            transfer = 1;
        } else if ((instruction >> 26) == 0 && (instruction & 63u) == 8) {
            if (call == 0x80043e00u) {
                uint8_t interrupt, command;
                uint32_t live, policy;
                int worker_frame =
                    (g_overlay_0004_words && depth == 9 &&
                     returns[0].target == 0x80046610u && returns[0].pc == 0x80045308u &&
                     returns[1].pc == 0x80046620u && returns[2].pc == 0x80046db0u &&
                     returns[3].pc == 0x8004358cu && returns[4].pc == 0x8004454cu &&
                     returns[5].pc == 0x80046620u && returns[6].pc == 0x80046db0u &&
                     returns[7].pc == 0x8004358cu && returns[8].pc == 0x80044510u) ||
                    (g_overlay_0004_words && depth == 5 &&
                     returns[0].target == 0x80046610u && returns[0].pc == 0x80045308u &&
                     returns[1].pc == 0x80046620u && returns[2].pc == 0x80046db0u &&
                     returns[3].pc == 0x8004358cu && returns[4].pc == 0x80044510u) ||
                    (depth == 1 && returns[0].pc == 0x800452ccu) ||
                    (depth == 5 && returns[0].pc == 0x80045308u &&
                     returns[1].pc == 0x80045f88u && returns[2].pc == 0x800437dcu &&
                     returns[3].pc == 0x8004473cu && returns[4].pc == 0x80044288u);
                accepted = instruction == 0x00400008u && worker_frame &&
                    cpu_read8(memory,&cpu,cpu.r[29]+0x10u,&interrupt) &&
                    read8(memory,0x8006cca5u,&command);
                if (accepted && interrupt == 1) {
                    /* INT1 bypasses the source's INT3 CE4C policy branch.
                     * ReadN (6) publishes INT1; Setmode (0x0e) issued while
                     * ReadN is still running leaves 8006cca5 as 0x0e.
                     * Source44828 also records Pause (9) before4482C writes
                     * the command; a trailing ReadN INT1 can interrupt there. */
                    expected = 0x80043f54u;
                    accepted = (command == 6 || command == 0x1b || command == 9 || command == 0x0e) &&
                        selected.deliver_event && selected.callback_device;
                } else if (accepted) {
                    accepted = (interrupt == 2 || interrupt == 3) &&
                        (command == 1 || command == 0x0a || command == 0x0c || command == 9 || command == 0x15 ||
                         ((command == 2 || command == 6 || command == 0x1b || command == 0x0e ||
                           command == 0x13 || command == 0x14) && interrupt == 3));
                    expected = interrupt == 2 ? 0x80043f08u : 0x80043e08u;
                    if (accepted) accepted =
                        musashi_boot_read32(memory,0x8006ce4cu+4u*command,&policy) && policy == 1 &&
                        musashi_boot_read32(memory,0x8006cd4cu+4u*command,&policy) &&
                        policy == (command == 0x0a || command == 9 || command == 0x15 ? 1u : 0u);
                }
                if (accepted) accepted =
                    musashi_boot_read32(memory,0x800737ccu+4u*(interrupt-1),&live) &&
                    live == expected && cpu.r[2] == expected;
                transfer = 3;
            } else if (call == 0x8001a3fcu) {
                uint32_t mode, live;
                accepted = instruction == 0x00400008u && depth == 1 &&
                    returns[0].target == 0x8001a338u && returns[0].pc == 0x80045308u &&
                    cpu.r[29] == saved_sp-0x88u &&
                    musashi_boot_read32(memory,0x800ae6f8u,&mode) && mode <= 6u;
                if (accepted) {
                    expected = mode == 2u ? 0x8001a958u :
                        mode == 3u ? 0x8001a7f4u :
                        mode == 4u ? 0x8001a844u :
                        mode == 5u ? 0x8001a8f8u :
                        mode == 6u ? 0x8001a924u :
                        mode == 1u ? 0x8001a6fcu : 0x8001a404u;
                    accepted = cpu.r[3] == mode && cpu.r[2] == expected &&
                        musashi_boot_read32(memory,0x80072a94u+mode*4u,&live) && live == expected;
                }
                transfer = 3;
            } else if (call == 0x8001a45cu) {
                uint32_t live;
                uint8_t kind;
                accepted = instruction == 0x00400008u && depth == 1 &&
                    returns[0].target == 0x8001a338u && returns[0].pc == 0x80045308u &&
                    cpu.r[29] == saved_sp-0x88u &&
                    read8(memory,0x80079a74u,&kind) && kind < 9u;
                if (accepted) {
                    accepted = musashi_boot_read32(memory,0x80072ab4u+(uint32_t)kind*4u,&live) &&
                        cpu.r[2] == live;
                    expected = live;
                }
                transfer = 3;
            } else if (call == 0x80018788u) {
                static const uint32_t states[] = {
                    0x80018824u, 0x80018790u, 0x800187a4u, 0x800187f8u, 0x800188b4u
                };
                uint32_t state, live;
                accepted = instruction == 0x00400008u && depth == 2 &&
                    returns[0].target == 0x8001a338u && returns[0].pc == 0x80045308u &&
                    returns[1].target == 0x80018730u && returns[1].pc == 0x8001a914u &&
                    cpu.r[29] == saved_sp-0x88u &&
                    musashi_boot_read32(memory,0x800c7d24u,&state) && state < 5u;
                if (accepted) {
                    expected = states[state];
                    accepted = cpu.r[3] == state && cpu.r[2] == expected &&
                        musashi_boot_read32(memory,0x80072a38u+4u*state,&live) && live == expected;
                }
                transfer = 3;
            } else if (call == 0x8005ce6cu) {
                /* Verified B0:07 veneer tail. Its delay slot supplies t1=7;
                 * the BIOS service returns to the existing JAL's live RA. */
                expected = 0xb0u;
                expected_sp = cpu.r[29];
                accepted = instruction == 0x01400008u && depth >= 2 &&
                    (returns[depth-1].pc == 0x800433b0u ||
                     returns[depth-1].pc == 0x800433d8u || returns[depth-1].pc == 0x80043400u) &&
                    cpu.r[29] == returns[depth-1].sp && cpu.r[10] == expected &&
                    cpu.r[31] == returns[depth-1].pc && cpu.r[4] == 0xf0000003u &&
                    cpu.r[5] == (returns[depth-1].pc == 0x800433b0u ? 0x20u : 0x40u) &&
                    selected.deliver_event;
                transfer = 4;
            } else {
                expected = depth ? returns[depth-1].pc : UINT_MAX;
                expected_sp = depth ? returns[depth-1].sp : saved_sp-0x28u;
                accepted = instruction == 0x03e00008u && cpu.r[31] == expected;
                transfer = 2;
            }
        }
        int bank_pio = depth >= 4 && returns[0].target == 0x800377d8u &&
            returns[0].pc == 0x80045308u && returns[3].target == 0x8003a84cu &&
            returns[3].pc == 0x8003ae80u;
        unsigned *budget = bank_pio ? &pio_remaining :
            cpu.pc >= 0x80018730u && cpu.pc < 0x80018918u ?
            &decode_remaining : &remaining;
        if (!*budget) { frame->budget_exhausted = budget == &remaining ? 1u : budget == &decode_remaining ? 2u : 3u; break; }
        --*budget; ++frame->instructions;
        if (!formatter_step(memory,&cpu) || frame->faulted) break;
        if (transfer) {
            if (!*budget) { frame->budget_exhausted = budget == &remaining ? 1u : budget == &decode_remaining ? 2u : 3u; break; }
            --*budget; ++frame->instructions;
            if (!formatter_step(memory,&cpu) || frame->faulted) break;
            if (!accepted || cpu.pc != expected) {
                stop->call_address = call; stop->target_address = cpu.pc; break;
            }
            if (transfer == 1) {
                if (cpu.r[29] != expected_sp ||
                    !cd_irq_call(memory,&cpu,&selected,returns,depth,saved_sp,call,instruction)) {
                    stop->call_address = call; stop->target_address = cpu.pc; break;
                }
                if (depth == 0 && call == 0x80045300u && expected == 0x800377d8u) {
                    if (!musashi_boot_read32(memory,0x8007623cu,&bank_lba) ||
                        !read8(memory,0x80076243u,&bank_state)) break;
                }
                if (call == 0x8003ae78u && expected == 0x8003a84cu &&
                    depth == 3 && returns[0].target == 0x800377d8u) {
                    /* Retail PIO uses <=64-byte batches: three fixed 60-loop
                     * delay calls per batch (each <1100 instructions), plus
                     * <=0xF01 status polls (<16 instructions each). 70000 per
                     * batch covers these and stores/control; one extra batch
                     * covers the initial delay and final poll. The clamped
                     * maximum 0x7eff0 gives 569032048, within unsigned range.
                     * A later grant requires the prior PIO return and exactly
                     * one new source sector. Never replenish a stalled loop
                     * or borrow outside the accepted PIO frame. */
                    uint32_t lba;
                    if (cpu.r[5] > 0x7eff0u ||
                        !musashi_boot_read32(memory,0x8007623cu,&lba) ||
                        (pio_budget_granted && (!pio_completed || pio_lba == UINT_MAX ||
                                               lba != pio_lba+1u))) break;
                    pio_remaining = (((cpu.r[5]+63u)/64u)+1u)*70000u+2048u;
                    pio_budget_granted = 1;
                    pio_completed = 0;
                    pio_lba = lba;
                }
                returns[depth].pc = call+8u; returns[depth].sp = expected_sp;
                returns[depth].a0 = cpu.r[4]; returns[depth].a1 = cpu.r[5];
                returns[depth].target = expected; ++depth;
                if (expected == 0x8001a338u) {
                    uint32_t mode, packed;
                    image_call = 0;
                    if (!musashi_boot_read32(memory,0x800ae6f8u,&mode)) break;
                    list_mode = mode;
                    if (!musashi_boot_read32(memory,0x800ae7acu,&list_lba)) break;
                    if (mode == 1u && cpu.r[4] == 1u) {
                        if (!musashi_boot_read32(memory,0x800ae798u,&packed) ||
                            !musashi_boot_read32(memory,0x800ae7acu,&image_lba)) break;
                        image_call = cd_irq_image_cursor(packed,&image_start);
                    }
                }
                /* Each guarded call consumes a fresh 2048-byte sector.
                 * The root handler can drain several sectors before return. */
                if (expected == 0x80018730u) {
                    if (!musashi_boot_read32(memory,0x800747acu,&decode_start) ||
                        !musashi_boot_read32(memory,0x800ae7acu,&decode_lba)) break;
                    decode_remaining = decode_limit;
                }
            } else if (transfer == 4) {
                if (cpu.r[9] != 7u || cpu.r[29] != expected_sp ||
                    !selected.deliver_event(selected.userdata,cpu.r[4],cpu.r[5]) ||
                    frame->faulted) {
                    stop->call_address = call; stop->target_address = cpu.pc; break;
                }
                /* DeliverEvent has a void guest ABI. Host acceptance is NOT
                 * guest v0. The guarded43398/433C0/433E8 paths never consume
                 * the BIOS residue before their caller overwrites it.
                 * Preserve it unclaimed, without asserting register parity.
                 * No physical BIOS frame or recursive IRQ dispatch is added. */
                cpu.pc = returns[depth-1].pc; cpu.npc = cpu.pc+4u; --depth;
            } else if (transfer == 2) {
                if (cpu.r[29] != expected_sp) break;
                if (depth == 1 && returns[0].target == 0x800377d8u &&
                    returns[0].pc == 0x80045308u && returns[0].sp == saved_sp-0x50u) {
                    uint32_t lba;
                    uint8_t state;
                    if (!musashi_boot_read32(memory,0x8007623cu,&lba) ||
                        !read8(memory,0x80076243u,&state)) break;
                    /* The validated callback has returned after consuming one
                     * consecutive sector. Never renew inside a polling loop,
                     * on a nested return, or for inactive/error bank states. */
                    if (cd_irq_bank_progress(bank_state,state,bank_lba,lba,previous_bank_lba)) {
                        remaining = 16384;
                        previous_bank_lba = lba;
                    }
                }
                if (depth == 4 && returns[0].target == 0x800377d8u &&
                    returns[3].target == 0x8003a84cu && returns[3].pc == 0x8003ae80u)
                    pio_completed = 1;
                if (depth && returns[depth-1].target == 0x8001a338u) {
                    uint32_t lba;
                    if (!musashi_boot_read32(memory,0x800ae7acu,&lba)) break;
                    /* Modes2/3/4 consume headers/raw data/SPU data. Source
                     * 1A398 compares the real DMA header before1A3DC advances
                     * this identity. Consecutive completed callbacks are
                     * productive work; a stuck callback retains its limit. */
                    if (cd_irq_sector_progress(list_lba,lba,previous_list_lba)) {
                        if (list_mode >= 2u && list_mode <= 4u) remaining = 16384;
                        previous_list_lba = lba;
                    }
                }
                if (depth && returns[depth-1].target == 0x8001a338u && image_call) {
                    uint32_t packed, end, lba;
                    if (!musashi_boot_read32(memory,0x800ae798u,&packed) ||
                        !musashi_boot_read32(memory,0x800ae7acu,&lba)) break;
                    if (image_lba < UINT_MAX && lba == image_lba+1u &&
                        cd_irq_image_cursor(packed,&end) && end > image_start &&
                        (previous_image_lba == UINT_MAX ||
                         (image_lba == previous_image_lba && image_start == previous_image_end))) {
                        remaining = 16384;
                        previous_image_end = end; previous_image_lba = lba;
                    }
                    image_call = 0;
                }
                if (depth && returns[depth-1].target == 0x80018730u) {
                    uint32_t end, lba;
                    if (!musashi_boot_read32(memory,0x800747acu,&end) ||
                        !musashi_boot_read32(memory,0x800ae7acu,&lba)) break;
                    if (lba == decode_lba && cd_irq_pac_progress(decode_start,end,lba,
                            previous_decode_end,previous_decode_lba)) {
                        remaining = 16384;
                        previous_decode_end = end; previous_decode_lba = lba;
                    }
                }
                if (depth) --depth;
            }
        }
    }
fault:
    frame->busy = 0;
    frame->faulted = 1;
    return 0;
}

int musashi_boot_execute_cd_irq(MusashiBootMemory *memory,
    const MusashiCdRegisterDevice *device, const MusashiExecutionClock *clock,
    MusashiCdIrqFrame *frame, uint32_t context, uint32_t target,
    MusashiResetGraphPrefixStop *stop) {
    return musashi_boot_execute_cd_irq_with_services(memory,device,clock,NULL,
                                                    frame,context,target,stop);
}

int musashi_boot_execute_bios_event(void *userdata, uint32_t callback) {
    MusashiBootMemory *memory = userdata;
    FormatterCpu cpu = {0};
    unsigned step;
    if (!memory || callback < 0x800617ccu || callback >= 0x8006186cu ||
        (callback - 0x800617ccu) % 20u)
        return 0;
    /* BIOS callback frame: these exact leaves only use v0/at/ra. No live
     * startup CPU, checkpoint, interrupt return or guest snapshot is reused. */
    cpu.pc = callback;
    cpu.npc = callback + 4u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < 5; ++step)
        if (!formatter_step(memory, &cpu)) return 0;
    return cpu.pc == UINT_MAX;
}

MusashiResetGraphPrefixStatus musashi_boot_run_entry_with_devices(
    MusashiBootMemory *memory, uint32_t incoming_ra,
    const MusashiStartupPrefixDevice *devices,
    MusashiConsoleSink sink, void *sink_userdata,
    MusashiEntryObserver observer, void *observer_userdata,
    MusashiEntryRunStop *stop) {
    FormatterCpu cpu = {0};
    int32_t result;
    if (!memory || !devices || !devices->callback || !sink || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    cpu.callback_device = devices->callback;
    cpu.cd_device = devices->cd;
    cpu.event_device = devices->event;
    cpu.input_device = devices->input;
    cpu.clock = devices->clock;
    cpu.cd_register_device = devices->cd_registers;
    cpu.cd_spu_device = devices->cd_spu;
    cpu.heap_device = devices->heap;
    cpu.gpu_io_device = devices->gpu_io;
    cpu.cpu_transfer = devices->cpu_transfer;
    cpu.bios_image = devices->bios_image;
    cpu.pc = 0x80010000u;
    cpu.npc = cpu.pc + 4u;
    cpu.r[31] = incoming_ra;
    return run_startup_cpu(memory, &cpu, sink, sink_userdata, &result,
                           &stop->boundary, stop, observer, observer_userdata);
}

MusashiResetGraphPrefixStatus musashi_boot_run_entry(
    MusashiBootMemory *memory, uint32_t incoming_ra,
    const MusashiCallbackDevice *device, const MusashiCdDevice *cd,
    MusashiConsoleSink sink, void *sink_userdata,
    MusashiEntryObserver observer, void *observer_userdata,
    MusashiEntryRunStop *stop) {
    const MusashiStartupPrefixDevice devices = {.callback=device, .cd=cd};
    return musashi_boot_run_entry_with_devices(memory, incoming_ra, &devices,
        sink, sink_userdata, observer, observer_userdata, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_execute_source_function(
    MusashiBootMemory *memory, const MusashiStartupPrefixDevice *devices,
    uint32_t target, MusashiConsoleSink sink, void *sink_userdata,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu = {0};
    int32_t result = 0;
    if (!memory || !devices || !devices->callback || !sink || !stop || (target & 3u))
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    cpu.callback_device = devices->callback;
    cpu.cd_device = devices->cd;
    cpu.event_device = devices->event;
    cpu.input_device = devices->input;
    cpu.clock = devices->clock;
    cpu.cd_register_device = devices->cd_registers;
    cpu.cd_spu_device = devices->cd_spu;
    cpu.heap_device = devices->heap;
    cpu.gpu_io_device = devices->gpu_io;
    cpu.cpu_transfer = devices->cpu_transfer;
    cpu.bios_image = devices->bios_image;
    cpu.pc = target;
    cpu.npc = target + 4u;
    cpu.r[28] = 0x80074750u;
    cpu.r[29] = cpu.r[30] = 0x801ff000u;
    cpu.r[31] = UINT_MAX;
    return run_startup_cpu(memory, &cpu, sink, sink_userdata, &result, stop,
                           NULL, NULL, NULL);
}

MusashiResetGraphPrefixStatus musashi_boot_run_8005fc68_prefix(
    MusashiBootMemory *memory, const MusashiCdDevice *device, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.cd_device = device;
    cpu.pc = CD_START;
    cpu.npc = CD_START + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        int32_t service_result;
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            *result = (int32_t)cpu.r[2];
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (cpu.pc == CD_ENTER_CRITICAL) {
            if (!device->enter_critical_section ||
                !device->enter_critical_section(device->userdata)) {
                stop->call_address = 0x800622e8u;
                stop->target_address = CD_ENTER_CRITICAL;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == CD_EXIT_CRITICAL) {
            if (!device->exit_critical_section ||
                !device->exit_critical_section(device->userdata)) {
                stop->call_address = 0x8006230cu;
                stop->target_address = CD_EXIT_CRITICAL;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == CD_B0_5B) {
            if (!device->b0_5b ||
                !device->b0_5b(device->userdata, (int32_t)cpu.r[4], &service_result)) {
                stop->call_address = cpu.r[31] - 8u;
                stop->target_address = CD_B0_5B;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu.r[2] = (uint32_t)service_result;
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == CD_B0_4A) {
            if (!device->b0_4a ||
                !device->b0_4a(device->userdata, (int32_t)cpu.r[4], &service_result)) {
                stop->call_address = 0x80062304u;
                stop->target_address = CD_B0_4A;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu.r[2] = (uint32_t)service_result;
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == CD_B0_4B) {
            if (!device->b0_4b || !device->b0_4b(device->userdata, &service_result)) {
                stop->call_address = 0x80062338u;
                stop->target_address = CD_B0_4B;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu.r[2] = (uint32_t)service_result;
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == CD_A0_70) {
            if (!device->a0_70 || !device->a0_70(device->userdata, &service_result)) {
                stop->call_address = 0x80061884u;
                stop->target_address = CD_A0_70;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            cpu.r[2] = (uint32_t)service_result;
            formatter_return(&cpu);
            continue;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_8005fcb8_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = EVENT_START;
    cpu.npc = EVENT_START + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == EVENT_REGISTER) {
            stop->call_address = 0x8005fcf0u;
            stop->target_address = EVENT_REGISTER;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX)
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_8005fcb8_event_prefix(
    MusashiBootMemory *memory, const MusashiEventDevice *device, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = EVENT_START;
    cpu.npc = EVENT_START + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == EVENT_REGISTER) {
            if (!musashi_boot_call_8006189c(memory, device, result))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            formatter_return(&cpu);
            continue;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            *result = (int32_t)cpu.r[2];
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80018918_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RECORD_SETUP;
    cpu.npc = STARTUP_RECORD_SETUP + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == STARTUP_ALLOCATOR_PREFIX) {
            MusashiResetGraphPrefixStop allocator_stop;
            if (musashi_boot_run_8005f0c8_prefix(memory, &allocator_stop) !=
                    MUSASHI_RESETGRAPH_PREFIX_COMPLETE ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == 0x8005d8b4u) {
            stop->call_address = 0x8005d100u;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX)
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        if (cpu.pc == STARTUP_ENVIRONMENT_CLEAR ||
            cpu.pc == STARTUP_RECORD_CLEAR) {
            if (!formatter_call(memory, &cpu, NULL, NULL))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, &cpu)) {
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80018918_input_prefix(
    MusashiBootMemory *memory, const MusashiInputDevice *device,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RECORD_SETUP;
    cpu.npc = STARTUP_RECORD_SETUP + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == STARTUP_ALLOCATOR_PREFIX) {
            MusashiResetGraphPrefixStop allocator_stop;
            if (musashi_boot_run_8005f0c8_prefix(memory, &allocator_stop) !=
                    MUSASHI_RESETGRAPH_PREFIX_COMPLETE ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == INPUT_STARTUP_PREFIX) {
            MusashiResetGraphPrefixStop input_stop;
            if (musashi_boot_run_8005d8b4_prefix(memory, device, &input_stop) !=
                    MUSASHI_RESETGRAPH_PREFIX_COMPLETE ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (cpu.pc == STARTUP_ENVIRONMENT_CLEAR || cpu.pc == STARTUP_RECORD_CLEAR) {
            if (!formatter_call(memory, &cpu, NULL, NULL))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        } else if (!formatter_step(memory, &cpu)) {
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_post_entry_prefix(
    MusashiBootMemory *memory, const MusashiStartupPrefixDevice *device,
    MusashiConsoleSink sink, void *userdata, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    MusashiResetGraphPrefixStop nested_stop;
    int32_t service_result;
    if (!memory || !device || !device->callback || !device->cd || !device->event ||
        !device->input || !sink || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    if (musashi_boot_run_800141f0_callback_prefix(memory, device->callback, sink,
                                                   userdata, result, &nested_stop) !=
        MUSASHI_RESETGRAPH_PREFIX_COMPLETE) {
        *stop = nested_stop;
        return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
    }
    if (musashi_boot_run_8005fc68_prefix(memory, device->cd, &service_result,
                                         &nested_stop) !=
        MUSASHI_RESETGRAPH_PREFIX_COMPLETE) {
        *stop = nested_stop;
        return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
    }
    if (musashi_boot_run_8005fcb8_event_prefix(memory, device->event, &service_result,
                                                &nested_stop) !=
        MUSASHI_RESETGRAPH_PREFIX_COMPLETE) {
        *stop = nested_stop;
        return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
    }
    if (musashi_boot_run_80018918_input_prefix(memory, device->input, &nested_stop) !=
        MUSASHI_RESETGRAPH_PREFIX_COMPLETE) {
        *stop = nested_stop;
        return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
    }
    stop->call_address = 0x800101e4u;
    stop->target_address = 0x80043300u;
    return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
}

MusashiResetGraphPrefixStatus musashi_boot_run_post_entry_dispatch_prefix(
    MusashiBootMemory *memory, const MusashiStartupPrefixDevice *device,
    const MusashiStartupRetryDevice *retry_device, MusashiConsoleSink sink,
    void *userdata, int32_t *result, MusashiResetGraphPrefixStop *stop) {
    MusashiResetGraphPrefixStatus status;
    if (!memory || !device || !retry_device || !sink || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    status = musashi_boot_run_post_entry_prefix(memory, device, sink, userdata,
                                                 result, stop);
    if (status != MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL ||
        stop->call_address != 0x800101e4u || stop->target_address != STARTUP_DISPATCH)
        return status;
    return musashi_boot_run_80043300_prefix(memory, retry_device, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044bf4_with_device(
    MusashiBootMemory *memory, const MusashiCdRegisterDevice *cd,
    const MusashiCdSpuDevice *spu, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !cd || !cd->read8 || !cd->write8 || !spu ||
        !spu->read16 || !spu->write16 || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RETRY_ALTERNATE;
    cpu.npc = cpu.pc + 4;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    cpu.cd_register_device = cd;
    cpu.cd_spu_device = spu;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        stop->call_address = cpu.pc;
        stop->target_address = cpu.pc;
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80043450_prefix(
    MusashiBootMemory *memory, const MusashiStartupRetryDevice *device,
    int32_t argument, int32_t *result, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !device->probe_80044d38 || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RETRY;
    cpu.npc = STARTUP_RETRY + 4u;
    cpu.r[4] = (uint32_t)argument;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == STARTUP_RETRY_PROBE) {
            if (!device->probe_80044d38(device->userdata, result))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)*result;
            if (!formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == UINT_MAX) {
            *result = (int32_t)cpu.r[2];
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044d38_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RETRY_PROBE;
    cpu.npc = STARTUP_RETRY_PROBE + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT) {
            stop->call_address = 0x80044d48u;
            stop->target_address = CD_INITIALIZER_STRING_EMIT;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044d38_console_prefix(
    MusashiBootMemory *memory, MusashiConsoleSink sink, void *userdata,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !sink || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RETRY_PROBE;
    cpu.npc = STARTUP_RETRY_PROBE + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT) {
            if (!musashi_boot_console_string(memory, cpu.r[4], sink, userdata) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY) {
            stop->call_address = 0x80044d60u;
            stop->target_address = FORMATTER_WRAPPER_ENTRY;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044d38_console_format_prefix(
    MusashiBootMemory *memory, MusashiConsoleSink sink, void *userdata,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    int32_t formatter_result;
    unsigned step;
    if (!memory || !sink || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_RETRY_PROBE;
    cpu.npc = STARTUP_RETRY_PROBE + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT) {
            if (!musashi_boot_console_string(memory, cpu.r[4], sink, userdata) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY) {
            if (!musashi_boot_format_8005c604(memory, cpu.r[4], cpu.r[5], 0, 0,
                                              sink, userdata, &formatter_result) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)formatter_result;
            continue;
        }
        if (cpu.pc == CALLBACK_WRAPPER_ENTRY) {
            stop->call_address = 0x80044d98u;
            stop->target_address = CALLBACK_WRAPPER_ENTRY;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044d38_callback_prefix(
    MusashiBootMemory *memory, const MusashiCallbackDevice *device,
    MusashiConsoleSink sink, void *userdata, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    MusashiCallbackInitPrefixStatus callback_status;
    MusashiResetGraphPrefixStop callback_stop;
    int32_t formatter_result;
    unsigned step;
    if (!memory || !device || !sink || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.callback_device = device;
    cpu.pc = STARTUP_RETRY_PROBE;
    cpu.npc = STARTUP_RETRY_PROBE + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT) {
            if (!musashi_boot_console_string(memory, cpu.r[4], sink, userdata) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY) {
            if (!musashi_boot_format_8005c604(memory, cpu.r[4], cpu.r[5], 0, 0,
                                              sink, userdata, &formatter_result) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)formatter_result;
            continue;
        }
        if (cpu.pc == CALLBACK_WRAPPER_ENTRY) {
            callback_status = musashi_boot_run_callback_init_prefix(memory, device,
                                                                      &callback_stop);
            if (callback_status != MUSASHI_CALLBACK_INIT_PREFIX_RETURN_BOUNDARY) {
                *stop = callback_stop;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            if (!formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == CD_COMMAND_STATUS) {
            /* Command submission runs in this CPU, preserving its caller's
             * frame and all four argument registers until the poll boundary. */
            stop->call_address = 0x80044734u;
            stop->target_address = CD_COMMAND_STATUS;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == CALLBACK_REGISTER_WRAPPER) {
            if (!formatter_call(memory, &cpu, NULL, NULL)) {
                stop->call_address = 0x80044da8u;
                stop->target_address = CALLBACK_REGISTER_WRAPPER;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            continue;
        }
        if (!formatter_step(memory, &cpu)) {
            stop->call_address = cpu.pc;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044670_prefix(
    MusashiBootMemory *memory, int32_t command, uint32_t payload_address,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = CD_INITIALIZER_COMMAND;
    cpu.npc = CD_INITIALIZER_COMMAND + 4u;
    cpu.r[4] = (uint32_t)command;
    cpu.r[5] = payload_address;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_COMMAND_DIAGNOSTIC) {
            stop->call_address = 0x800446ccu;
            stop->target_address = CD_COMMAND_DIAGNOSTIC;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == CD_COMMAND_STATUS) {
            stop->call_address = 0x80044734u;
            stop->target_address = CD_COMMAND_STATUS;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu)) {
            stop->call_address = cpu.pc;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

static MusashiResetGraphPrefixStatus run_80044124_poll_with_tick(
    MusashiBootMemory *memory, const MusashiTickDevice *device,
    MusashiConsoleSink sink, void *userdata, int continue_diagnostic,
    uint32_t entry, int32_t command, uint32_t payload_address,
    const MusashiCdRegisterDevice *register_device,
    MusashiResetGraphPrefixStop *stop);

MusashiResetGraphPrefixStatus musashi_boot_run_80044670_with_tick(
    MusashiBootMemory *memory, int32_t command, uint32_t payload_address,
    const MusashiTickDevice *device, MusashiResetGraphPrefixStop *stop) {
    return run_80044124_poll_with_tick(memory, device, NULL, NULL, 0,
        CD_INITIALIZER_COMMAND, command, payload_address, NULL, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044670_with_device(
    MusashiBootMemory *memory, int32_t command, uint32_t payload_address,
    const MusashiTickDevice *tick_device,
    const MusashiCdRegisterDevice *register_device,
    MusashiResetGraphPrefixStop *stop) {
    if (!register_device || !register_device->read8 || !register_device->write8)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    return run_80044124_poll_with_tick(memory, tick_device, NULL, NULL, 0,
        CD_INITIALIZER_COMMAND, command, payload_address, register_device, stop);
}

/* Execute the exact 80044DBC initializer through its 80044670 command call.
 * The fixture supplies the caller's live v0/v1 pair and captures the call
 * arguments; the busy flag must already read clear so the poll loop exits
 * without spinning, exactly as observed at boot. */
MusashiResetGraphPrefixStatus musashi_boot_run_80044dbc_command(
    MusashiBootMemory *memory, uint32_t out_value, uint32_t out_address,
    uint32_t call_args[4], MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !out_address || !call_args || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = CD_INITIALIZER;
    cpu.npc = CD_INITIALIZER + 4u;
    cpu.r[2] = out_value;
    cpu.r[3] = out_address;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_INITIALIZER_COMMAND) {
            call_args[0] = cpu.r[4]; call_args[1] = cpu.r[5];
            call_args[2] = cpu.r[6]; call_args[3] = cpu.r[7];
            stop->call_address = CD_INITIALIZER_CALL;
            stop->target_address = CD_INITIALIZER_COMMAND;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu)) {
            stop->call_address = cpu.pc;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_8004239c_minus_one(
    MusashiBootMemory *memory, int32_t *result, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !result || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = TICK_QUERY_ENTRY;
    cpu.npc = TICK_QUERY_ENTRY + 4u;
    cpu.r[4] = UINT32_MAX;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            *result = (int32_t)cpu.r[2];
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044124_first_poll(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned tick_queries = 0;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STATUS_FIRST_POLL;
    cpu.npc = STATUS_FIRST_POLL + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == TICK_QUERY_ENTRY) {
            if (tick_queries++ != 0u) {
                stop->call_address = 0x80044190u;
                stop->target_address = TICK_QUERY_ENTRY;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

static MusashiResetGraphPrefixStatus run_80044124_poll_with_tick(
    MusashiBootMemory *memory, const MusashiTickDevice *device,
    MusashiConsoleSink sink, void *userdata, int continue_diagnostic,
    uint32_t entry, int32_t command, uint32_t payload_address,
    const MusashiCdRegisterDevice *register_device,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    int32_t formatter_result;
    int32_t tick;
    unsigned tick_queries = 0;
    unsigned step;
    if (!memory || !device || !device->refresh_tick || !stop ||
        (continue_diagnostic && !sink))
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = entry;
    cpu.cd_register_device = register_device;
    cpu.npc = entry + 4u;
    cpu.r[4] = (uint32_t)command;
    cpu.r[5] = payload_address;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_COMMAND_DIAGNOSTIC && !continue_diagnostic) {
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == TICK_QUERY_ENTRY) {
            if (tick_queries++ != 0u &&
                (!device->refresh_tick(device->userdata, &tick) ||
                 !musashi_boot_write32(memory, 0x8006cbb8u, (uint32_t)tick)))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
        if (cpu.pc == STATUS_TIMEOUT_DIAGNOSTIC) {
            if (!continue_diagnostic) {
                stop->call_address = 0x800441d0u;
                stop->target_address = STATUS_TIMEOUT_DIAGNOSTIC;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
        }
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT && continue_diagnostic) {
            if (!musashi_boot_console_string(memory, cpu.r[4], sink, userdata) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY && continue_diagnostic) {
            if (!musashi_boot_format_8005c604(memory, cpu.r[4], cpu.r[5], cpu.r[6],
                                              cpu.r[7], sink, userdata,
                                              &formatter_result) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)formatter_result;
            continue;
        }
        if (cpu.pc == STATUS_READY_QUERY) {
            uint16_t ready;
            if (!musashi_boot_call_800426d4(memory, &ready) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = ready;
            continue;
        }
        if ((cpu.pc == CD_INITIALIZER_STRING_EMIT ||
             cpu.pc == FORMATTER_WRAPPER_ENTRY) && !continue_diagnostic) {
            stop->call_address = cpu.r[31] - 8u;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu)) {
            stop->call_address = cpu.pc;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044124_poll_with_tick(
    MusashiBootMemory *memory, const MusashiTickDevice *device,
    MusashiResetGraphPrefixStop *stop) {
    return run_80044124_poll_with_tick(memory, device, NULL, NULL, 0,
        STATUS_FIRST_POLL, 0, 0, NULL, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044124_poll_with_tick_console(
    MusashiBootMemory *memory, const MusashiTickDevice *device,
    MusashiConsoleSink sink, void *userdata, MusashiResetGraphPrefixStop *stop) {
    return run_80044124_poll_with_tick(memory, device, sink, userdata, 1,
        STATUS_FIRST_POLL, 0, 0, NULL, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044198_timeout_prefix(
    MusashiBootMemory *memory, int32_t tick, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STATUS_TIMEOUT;
    cpu.npc = STATUS_TIMEOUT + 4u;
    cpu.r[2] = (uint32_t)tick;
    cpu.r[29] = 0x801fff80u;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == STATUS_TIMEOUT_DIAGNOSTIC) {
            stop->call_address = 0x800441d0u;
            stop->target_address = STATUS_TIMEOUT_DIAGNOSTIC;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == STATUS_TIMEOUT_CONTINUE) {
            stop->call_address = 0x800441d0u;
            stop->target_address = STATUS_TIMEOUT_CONTINUE;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

static MusashiResetGraphPrefixStatus run_80043b9c_prefix(
    MusashiBootMemory *memory, MusashiConsoleSink sink, void *userdata,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    int32_t formatter_result;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STATUS_WORKER;
    cpu.npc = STATUS_WORKER + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (cpu.pc == CD_INITIALIZER_STRING_EMIT) {
            if (!sink) {
                stop->call_address = cpu.r[31] - 8u;
                stop->target_address = cpu.pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            if (!musashi_boot_console_string(memory, cpu.r[4], sink, userdata) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY) {
            if (!sink) {
                stop->call_address = cpu.r[31] - 8u;
                stop->target_address = cpu.pc;
                return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
            }
            if (!musashi_boot_format_8005c604(memory, cpu.r[4], cpu.r[5], cpu.r[6],
                                              cpu.r[7], sink, userdata,
                                              &formatter_result) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)formatter_result;
            continue;
        }
        if (!formatter_step(memory, &cpu)) {
            stop->call_address = cpu.pc;
            stop->target_address = cpu.pc;
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80043b9c_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    return run_80043b9c_prefix(memory, NULL, NULL, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80043b9c_console_prefix(
    MusashiBootMemory *memory, MusashiConsoleSink sink, void *userdata,
    MusashiResetGraphPrefixStop *stop) {
    return run_80043b9c_prefix(memory, sink, userdata, stop);
}

MusashiResetGraphPrefixStatus musashi_boot_run_80044b14_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = CD_STATE_RESET;
    cpu.npc = CD_STATE_RESET + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_800434bc_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    MusashiResetGraphPrefixStop nested_stop;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = CD_STATE_RESET_WRAPPER;
    cpu.npc = CD_STATE_RESET_WRAPPER + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == CD_STATE_RESET) {
            if (musashi_boot_run_80044b14_prefix(memory, &nested_stop) !=
                    MUSASHI_RESETGRAPH_PREFIX_COMPLETE ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80043300_prefix(
    MusashiBootMemory *memory, const MusashiStartupRetryDevice *device,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !device->probe_80044d38 || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_DISPATCH;
    cpu.npc = STARTUP_DISPATCH + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == STARTUP_RETRY_PROBE) {
            int32_t retry_result;
            /* Execute 80043450 in this CPU so its stack frame nests below
             * 80043300. Only the explicit device probe crosses to the host. */
            if (!device->probe_80044d38(device->userdata, &retry_result) ||
                !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            cpu.r[2] = (uint32_t)retry_result;
            continue;
        }
        if (cpu.pc == FORMATTER_WRAPPER_ENTRY) {
            stop->call_address = 0x80043378u;
            stop->target_address = FORMATTER_WRAPPER_ENTRY;
            return MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_80043300_console_prefix(
    MusashiBootMemory *memory, const MusashiStartupRetryDevice *device,
    MusashiConsoleSink sink, void *userdata, int32_t *result,
    MusashiResetGraphPrefixStop *stop) {
    MusashiResetGraphPrefixStatus status;
    status = musashi_boot_run_80043300_prefix(memory, device, stop);
    if (status != MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL ||
        stop->target_address != FORMATTER_WRAPPER_ENTRY || !sink || !result)
        return status;
    if (!musashi_boot_format_8005c604(memory, 0x800735fcu, 0, 0, 0,
                                      sink, userdata, result))
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    *result = 0;
    stop->call_address = 0;
    stop->target_address = UINT_MAX;
    return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
}

MusashiResetGraphPrefixStatus musashi_boot_run_8005f0c8_prefix(
    MusashiBootMemory *memory, MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = STARTUP_ALLOCATOR_PREFIX;
    cpu.npc = STARTUP_ALLOCATOR_PREFIX + 4u;
    cpu.r[4] = 0x80078da0u;
    cpu.r[5] = 0x80078decu;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

MusashiResetGraphPrefixStatus musashi_boot_run_8005d8b4_prefix(
    MusashiBootMemory *memory, const MusashiInputDevice *device,
    MusashiResetGraphPrefixStop *stop) {
    FormatterCpu cpu;
    unsigned step;
    if (!memory || !device || !device->enter_critical_section || !stop)
        return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    memset(&cpu, 0, sizeof(cpu));
    cpu.pc = INPUT_STARTUP_PREFIX;
    cpu.npc = INPUT_STARTUP_PREFIX + 4u;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == 0x8005cf08u) {
            if (!device->enter_critical_section(device->userdata) || !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == INPUT_C0_3) {
            if (!device->c0_3 || !device->c0_3(device->userdata, (int32_t)cpu.r[4],
                                                cpu.r[5]) || !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == INPUT_C0_2) {
            if (!device->c0_2 || !device->c0_2(device->userdata, (int32_t)cpu.r[4],
                                                cpu.r[5]) || !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == INPUT_C0_0A) {
            if (!device->c0_0a || !device->c0_0a(device->userdata, (int32_t)cpu.r[4],
                                                  (int32_t)cpu.r[5]) || !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == CD_EXIT_CRITICAL) {
            if (!device->exit_critical_section ||
                !device->exit_critical_section(device->userdata) || !formatter_return(&cpu))
                return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
            continue;
        }
        if (cpu.pc == UINT_MAX) {
            stop->call_address = 0;
            stop->target_address = UINT_MAX;
            return MUSASHI_RESETGRAPH_PREFIX_COMPLETE;
        }
        if (!formatter_step(memory, &cpu))
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
    }
    return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
}

int musashi_boot_format_8005c604(MusashiBootMemory *memory,
                                 uint32_t format_address, uint32_t arg1,
                                 uint32_t arg2, uint32_t arg3,
                                 MusashiConsoleSink sink, void *userdata,
                                 int32_t *result) {
    FormatterCpu cpu;
    FormatterConsoleContext console;
    unsigned step;
    if (!memory || !sink || !result || !musashi_boot_ram_span(memory, format_address, 1))
        return 0;
    memset(&cpu, 0, sizeof(cpu));
    console.sink = sink;
    console.userdata = userdata;
    cpu.pc = FORMATTER_WRAPPER_ENTRY;
    cpu.npc = FORMATTER_WRAPPER_ENTRY + 4u;
    cpu.r[4] = format_address;
    cpu.r[5] = arg1;
    cpu.r[6] = arg2;
    cpu.r[7] = arg3;
    cpu.r[29] = 0x801fff80u;
    cpu.r[31] = UINT_MAX;
    for (step = 0; step < FORMATTER_STEP_LIMIT; ++step) {
        if (cpu.pc == UINT_MAX) {
            *result = (int32_t)cpu.r[2];
            return 1;
        }
        if (cpu.pc == FORMATTER_CONSOLE_CHAR || cpu.pc == FORMATTER_SEARCH ||
            cpu.pc == FORMATTER_STRING_LENGTH) {
            if (!formatter_call(memory, &cpu, sink, &console)) return 0;
        } else if (!formatter_step(memory, &cpu)) {
            return 0;
        }
    }
    return 0;
}
