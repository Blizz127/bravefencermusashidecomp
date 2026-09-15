#include "musashi_boot_memory.h"
#include "musashi_callback_registration.h"
#include "musashi_mips_div.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const uint32_t kMain80017758Words[] = {
#include "80017758_words.inc"
};
static const uint32_t kMain80017778Words[] = {
#include "80017778_words.inc"
};
static const uint32_t kMain800178C8Words[] = {
#include "800178c8_words.inc"
};
static const uint32_t kMain800178ECWords[] = {
#include "800178ec_words.inc"
};
static const uint32_t kMain80017910Words[] = {
#include "80017910_words.inc"
};
static const uint32_t kMain80017930Words[] = {
#include "80017930_words.inc"
};
static const uint32_t kMain80017B98Words[] = {
#include "80017b98_words.inc"
};
static const uint32_t kMain80017D98Words[] = {
#include "80017d98_words.inc"
};
static const uint32_t kMain80017DC4Words[] = {
#include "80017dc4_words.inc"
};
static const uint32_t kMain80017DF8Words[] = {
#include "80017df8_words.inc"
};
static const uint32_t kMain80017E30Words[] = {
#include "80017e30_words.inc"
};
static const uint32_t kMain80017E68Words[] = {
#include "80017e68_words.inc"
};
static const uint32_t kMain80017E8CWords[] = {
#include "80017e8c_words.inc"
};
static const uint32_t kMain80017F14Words[] = {
#include "80017f14_words.inc"
};
static const uint32_t kMain80018094Words[] = {
#include "80018094_words.inc"
};
static const uint32_t kMain80018194Words[] = {
#include "80018194_words.inc"
};
static const uint32_t kMain8001820CWords[] = {
#include "8001820c_words.inc"
};
static const uint32_t kMain80018384Words[] = {
#include "80018384_words.inc"
};
static const uint32_t kMain80048384Words[] = {
#include "80048384_words.inc"
};
static const uint32_t kMain80049610Words[] = {
#include "80049610_words.inc"
};
static const uint32_t kMain8004969CWords[] = {
#include "8004969c_words.inc"
};
static const uint32_t kMain80058DE8Words[] = {
#include "80058de8_words.inc"
};
static const uint32_t kMain80058DFCWords[] = {
#include "80058dfc_words.inc"
};
static const uint32_t kMain80058E10Words[] = {
#include "80058e10_words.inc"

/* noinline is load-bearing, not a hint. Inlined into a caller whose table
 * size is a compile-time constant, a table scan gets unrolled and GCC's
 * dominator pass explores the unrolled paths; that cost 12 to 14 of this
 * file's 14 seconds of compile time before the tables below were turned
 * into data. Keeping one out-of-line copy keeps the trip count opaque. */
#if defined(__GNUC__)
#define MUSASHI_FORMATTER_NOINLINE __attribute__((noinline))
#else
#define MUSASHI_FORMATTER_NOINLINE
#endif
};
static const uint32_t kMain80058E24Words[] = {
#include "80058e24_words.inc"
};
static const uint32_t kMain80058E38Words[] = {
#include "80058e38_words.inc"
};
static const uint32_t kMain80058E4CWords[] = {
#include "80058e4c_words.inc"
};
static const uint32_t kMain80058E60Words[] = {
#include "80058e60_words.inc"
};
static const uint32_t kMain80058E74Words[] = {
#include "80058e74_words.inc"
};
static const uint32_t kMain80058E88Words[] = {
#include "80058e88_words.inc"
};
static const uint32_t kMain80058E9CWords[] = {
#include "80058e9c_words.inc"
};
static const uint32_t kMain80058EB0Words[] = {
#include "80058eb0_words.inc"
};
static const uint32_t kMain80058EC4Words[] = {
#include "80058ec4_words.inc"
};
static const uint32_t kMain80058EE4Words[] = {
#include "80058ee4_words.inc"
};
static const uint32_t kMain80058F04Words[] = {
#include "80058f04_words.inc"
};
static const uint32_t kMain80058F24Words[] = {
#include "80058f24_words.inc"
};
static const uint32_t kMain80058F44Words[] = {
#include "80058f44_words.inc"
};
static const uint32_t kMain80058F70Words[] = {
#include "80058f70_words.inc"
};
static const uint32_t kMain80058FD0Words[] = {
#include "80058fd0_words.inc"
};
static const uint32_t kMain8005903CWords[] = {
#include "8005903c_words.inc"
};
static const uint32_t kMain80059074Words[] = {
#include "80059074_words.inc"
};
static const uint32_t kMain80059188Words[] = {
#include "80059188_words.inc"
};
static const uint32_t kMain80059234Words[] = {
#include "80059234_words.inc"
};
static const uint32_t kMain800593B8Words[] = {
#include "800593b8_words.inc"
};
static const uint32_t kMain800594CCWords[] = {
#include "800594cc_words.inc"
};
static const uint32_t kMain80059530Words[] = {
#include "80059530_words.inc"
};
static const uint32_t kMain800595DCWords[] = {
#include "800595dc_words.inc"
};
static const uint32_t kMain800595ECWords[] = {
#include "800595ec_words.inc"
};
static const uint32_t kOverlay0010_800CEFD0Words[] = {
#include "800cefd0_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D20C0Words[] = {
#include "800d20c0_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D21C4Words[] = {
#include "800d21c4_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D22E4Words[] = {
#include "800d22e4_overlay0010_words.inc"
};
static const uint32_t kOverlay0010_800D23D0Words[] = {
#include "800d23d0_overlay0010_words.inc"
};
static const uint32_t kOverlaySc02_80167DBCWords[] = {
#include "80167dbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168070Words[] = {
#include "80168070_sc02_0031_words.inc"
};
static const uint32_t kCrt80010000Words[] = {
#include "80010000_words.inc"
};
static const uint32_t kConstructor800100A0Words[] = {
#include "800100a0_words.inc"
};
static const uint32_t kMain80010110Words[] = {
#include "80010110_words.inc"
};
static const uint32_t kCaller80010178Words[] = {
#include "80010178_words.inc"
};
static const uint32_t kMain8001020CWords[] = {
#include "8001020c_words.inc"
};
static const uint32_t kMain80010214Words[] = {
#include "80010214_words.inc"
};
static const uint32_t kMain80010938Words[] = {
#include "80010938_words.inc"
};
static const uint32_t kMain8001094CWords[] = {
#include "8001094c_words.inc"
};
static const uint32_t kMain8001096CWords[] = {
#include "8001096c_words.inc"
};
static const uint32_t kMain80014238Words[] = {
#include "80014238_words.inc"
};
static const uint32_t kMain800142C8Words[] = {
#include "800142c8_words.inc"
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
static const uint32_t kMain80047EC8Words[] = {
#include "80047ec8_words.inc"
};
static const uint32_t kMain80047F84Words[] = {
#include "80047f84_words.inc"
};
static const uint32_t kMain8004806CWords[] = {
#include "8004806c_words.inc"
};
static const uint32_t kMain800480ECWords[] = {
#include "800480ec_words.inc"
};
static const uint32_t kMain8004818CWords[] = {
#include "8004818c_words.inc"
};
static const uint32_t kMain8004829CWords[] = {
#include "8004829c_words.inc"
};
static const uint32_t kMain80047E58Words[] = {
#include "80047e58_words.inc"
};
static const uint32_t kMain80049440Words[] = {
#include "80049440_words.inc"
};
static const uint32_t kMain800128ECWords[] = {
#include "800128ec_words.inc"
};
static const uint32_t kMain80014070Words[] = {
#include "80014070_words.inc"
};
static const uint32_t kMain80014094Words[] = {
#include "80014094_words.inc"
};
static const uint32_t kMain800140B8Words[] = {
#include "800140b8_words.inc"
};
static const uint32_t kMain80014128Words[] = {
#include "80014128_words.inc"
};
static const uint32_t kMain80014148Words[] = {
#include "80014148_words.inc"
};
static const uint32_t kMain80014168Words[] = {
#include "80014168_words.inc"
};
static const uint32_t kMain800141ACWords[] = {
#include "800141ac_words.inc"
};
static const uint32_t kMain800141F0Words[] = {
#include "800141f0_words.inc"
};
static const uint32_t kMain800128B4Words[] = {
#include "800128b4_words.inc"
};
static const uint32_t kMain80013FE0Words[] = {
#include "80013fe0_words.inc"
};
static const uint32_t kMain80014004Words[] = {
#include "80014004_words.inc"
};
static const uint32_t kMain80014028Words[] = {
#include "80014028_words.inc"
};
static const uint32_t kMain8001404CWords[] = {
#include "8001404c_words.inc"
};
static const uint32_t kMain80013FBCWords[] = {
#include "80013fbc_words.inc"
};
static const uint32_t kMain80013F98Words[] = {
#include "80013f98_words.inc"
};
static const uint32_t kMain80013ED0Words[] = {
#include "80013ed0_words.inc"
};
static const uint32_t kMain8001282CWords[] = {
#include "8001282c_words.inc"
};
static const uint32_t kMain80012558Words[] = {
#include "80012558_words.inc"
};
static const uint32_t kMain800126C4Words[] = {
#include "800126c4_words.inc"
};
static const uint32_t kMain80013F3CWords[] = {
#include "80013f3c_words.inc"
};
static const uint32_t kMain80013F68Words[] = {
#include "80013f68_words.inc"
};
static const uint32_t kMain800129CCWords[] = {
#include "800129cc_words.inc"
};
static const uint32_t kMain80012A60Words[] = {
#include "80012a60_words.inc"
};
static const uint32_t kMain80012AB0Words[] = {
#include "80012ab0_words.inc"
};
static const uint32_t kMain8004CFECWords[] = {
#include "8004cfec_words.inc"
};
static const uint32_t kMain8002D8A8Words[] = {
#include "8002d8a8_words.inc"
};
static const uint32_t kMain800120DCWords[] = {
#include "800120dc_words.inc"
};
static const uint32_t kMain8001212CWords[] = {
#include "8001212c_words.inc"
};
static const uint32_t kMain800123F0Words[] = {
#include "800123f0_words.inc"
};
static const uint32_t kMain80029104Words[] = {
#include "80029104_words.inc"
};
static const uint32_t kMain80029124Words[] = {
#include "80029124_words.inc"
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
static const uint32_t kMain80059658Words[] = {
#include "80059658_words.inc"
};
static const uint32_t kMain80042610Words[] = {
#include "80042610_words.inc"
};
static const uint32_t kMain80042644Words[] = {
#include "80042644_words.inc"
};
static const uint32_t kMain80042674Words[] = {
#include "80042674_words.inc"
};
static const uint32_t kMain800426A4Words[] = {
#include "800426a4_words.inc"
};
static const uint32_t kMain800426D4Words[] = {
#include "800426d4_words.inc"
};
static const uint32_t kMain800426E4Words[] = {
#include "800426e4_words.inc"
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
static const uint32_t kMain8005F728Words[] = {
#include "8005f728_words.inc"
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
static const uint32_t kMain800291A0Words[] = {
#include "800291a0_words.inc"
};
static const uint32_t kMain8005D538Words[] = {
#include "8005d538_words.inc"
};
static const uint32_t kMain8005D6A0Words[] = {
#include "8005d6a0_words.inc"
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
static const uint32_t kMain80018FC8Words[] = {
#include "80018fc8_words.inc"
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
static const uint32_t kMain800291C8Words[] = {
#include "800291c8_words.inc"
};
static const uint32_t kMain800291DCWords[] = {
#include "800291dc_words.inc"
};
static const uint32_t kMain800291F0Words[] = {
#include "800291f0_words.inc"
};
static const uint32_t kMain80029204Words[] = {
#include "80029204_words.inc"
};
static const uint32_t kMain80029218Words[] = {
#include "80029218_words.inc"
};
static const uint32_t kMain80029240Words[] = {
#include "80029240_words.inc"
};
static const uint32_t kMain80028D78Words[] = {
#include "80028d78_words.inc"
};
static const uint32_t kMain80015208Words[] = {
#include "80015208_words.inc"
};
static const uint32_t kMain800152F4Words[] = {
#include "800152f4_words.inc"
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
static const uint32_t kMain800351E8Words[] = {
#include "800351e8_words.inc"
};
static const uint32_t kMain80035210Words[] = {
#include "80035210_words.inc"
};
static const uint32_t kMain80035270Words[] = {
#include "80035270_words.inc"
};
static const uint32_t kMain800359B0Words[] = {
#include "800359b0_words.inc"
};
static const uint32_t kMain80035C4CWords[] = {
#include "80035c4c_words.inc"
};
static const uint32_t kMain8003602CWords[] = {
#include "8003602c_words.inc"
};
static const uint32_t kMain80036130Words[] = {
#include "80036130_words.inc"
};
static const uint32_t kMain800361CCWords[] = {
#include "800361cc_words.inc"
};
static const uint32_t kMain8003621CWords[] = {
#include "8003621c_words.inc"
};
static const uint32_t kMain80036260Words[] = {
#include "80036260_words.inc"
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
static const uint32_t kMain8002F0F4Words[] = {
#include "8002f0f4_words.inc"
};
static const uint32_t kMain8002F12CWords[] = {
#include "8002f12c_words.inc"
};
static const uint32_t kMain8002F150Words[] = {
#include "8002f150_words.inc"
};
static const uint32_t kMain8002F1CCWords[] = {
#include "8002f1cc_words.inc"
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
static const uint32_t kMain8002F80CWords[] = {
#include "8002f80c_words.inc"
};
static const uint32_t kMain8002FA3CWords[] = {
#include "8002fa3c_words.inc"
};
static const uint32_t kMain80031B7CWords[] = {
#include "80031b7c_words.inc"
};
static const uint32_t kMain80031CC8Words[] = {
#include "80031cc8_words.inc"
};
static const uint32_t kMain80031D70Words[] = {
#include "80031d70_words.inc"
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
static const uint32_t kMain80033324Words[] = {
#include "80033324_words.inc"
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
static const uint32_t kMain800347C8Words[] = {
#include "800347c8_words.inc"
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
static const uint32_t kMain80034B3CWords[] = {
#include "80034b3c_words.inc"
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
static const uint32_t kMain80036F98Words[] = {
#include "80036f98_words.inc"
};
static const uint32_t kMain80036FB0Words[] = {
#include "80036fb0_words.inc"
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
static const uint32_t kMain800388E8Words[] = {
#include "800388e8_words.inc"
};
static const uint32_t kMain80038908Words[] = {
#include "80038908_words.inc"
};
static const uint32_t kMain80038958Words[] = {
#include "80038958_words.inc"
};
static const uint32_t kMain80038A00Words[] = {
#include "80038a00_words.inc"
};
static const uint32_t kMain80038A58Words[] = {
#include "80038a58_words.inc"
};
static const uint32_t kMain80038FC4Words[] = {
#include "80038fc4_words.inc"
};
static const uint32_t kMain80038FFCWords[] = {
#include "80038ffc_words.inc"
};
static const uint32_t kMain8003916CWords[] = {
#include "8003916c_words.inc"
};
static const uint32_t kMain800391D4Words[] = {
#include "800391d4_words.inc"
};
static const uint32_t kMain80039300Words[] = {
#include "80039300_words.inc"
};
static const uint32_t kMain80039308Words[] = {
#include "80039308_words.inc"
};
static const uint32_t kMain80039B20Words[] = {
#include "80039b20_words.inc"
};
static const uint32_t kMain80039C5CWords[] = {
#include "80039c5c_words.inc"
};
static const uint32_t kMain80039C70Words[] = {
#include "80039c70_words.inc"
};
static const uint32_t kMain80039DECWords[] = {
#include "80039dec_words.inc"
};
static const uint32_t kMain80039F14Words[] = {
#include "80039f14_words.inc"
};
static const uint32_t kMain80039F50Words[] = {
#include "80039f50_words.inc"
};
static const uint32_t kMain8003A098Words[] = {
#include "8003a098_words.inc"
};
static const uint32_t kMain8003A0D0Words[] = {
#include "8003a0d0_words.inc"
};
static const uint32_t kMain8003A0E4Words[] = {
#include "8003a0e4_words.inc"
};
static const uint32_t kMain8003A234Words[] = {
#include "8003a234_words.inc"
};
static const uint32_t kMain8003A3D8Words[] = {
#include "8003a3d8_words.inc"
};
static const uint32_t kMain8003A404Words[] = {
#include "8003a404_words.inc"
};
static const uint32_t kMain8003AB84Words[] = {
#include "8003ab84_words.inc"
};
static const uint32_t kMain8003AF4CWords[] = {
#include "8003af4c_words.inc"
};
static const uint32_t kMain8003AFF0Words[] = {
#include "8003aff0_words.inc"
};
static const uint32_t kMain8003B02CWords[] = {
#include "8003b02c_words.inc"
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
static const uint32_t kMain8003CF68Words[] = {
#include "8003cf68_words.inc"
};
static const uint32_t kMain8003CFF8Words[] = {
#include "8003cff8_words.inc"
};
static const uint32_t kMain8003D134Words[] = {
#include "8003d134_words.inc"
};
static const uint32_t kMain8003EDE8Words[] = {
#include "8003ede8_words.inc"
};
static const uint32_t kMain8003EEE4Words[] = {
#include "8003eee4_words.inc"
};
static const uint32_t kMain8003F104Words[] = {
#include "8003f104_words.inc"
};
static const uint32_t kMain80043974Words[] = {
#include "80043974_words.inc"
};
static const uint32_t kMain80044A8CWords[] = {
#include "80044a8c_words.inc"
};
static const uint32_t kMain80044B14Words[] = {
#include "80044b14_words.inc"
};
static const uint32_t kMain80044BF4Words[] = {
#include "80044bf4_words.inc"
};
static const uint32_t kMain80044CE8Words[] = {
#include "80044ce8_words.inc"
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
static const uint32_t kMain8001A338Words[] = {
#include "8001a338_words.inc"
};
static const uint32_t kMain8001A9D8Words[] = {
#include "8001a9d8_words.inc"
};
static const uint32_t kMain8001AF34Words[] = {
#include "8001af34_words.inc"
};
static const uint32_t kMain8001B0D4Words[] = {
#include "8001b0d4_words.inc"
};
static const uint32_t kMain8001B22CWords[] = {
#include "8001b22c_words.inc"
};
static const uint32_t kMain8001B23CWords[] = {
#include "8001b23c_words.inc"
};
static const uint32_t kMain8001B26CWords[] = {
#include "8001b26c_words.inc"
};
static const uint32_t kMain8001B324Words[] = {
#include "8001b324_words.inc"
};
static const uint32_t kMain8001B34CWords[] = {
#include "8001b34c_words.inc"
};
static const uint32_t kMain8001B374Words[] = {
#include "8001b374_words.inc"
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
static const uint32_t kMain8002D59CWords[] = {
#include "8002d59c_words.inc"
};
static const uint32_t kMain8002D678Words[] = {
#include "8002d678_words.inc"
};
static const uint32_t kMain8002D6D8Words[] = {
#include "8002d6d8_words.inc"
};
static const uint32_t kMain8002D7F4Words[] = {
#include "8002d7f4_words.inc"
};
static const uint32_t kMain8002D7FCWords[] = {
#include "8002d7fc_words.inc"
};
static const uint32_t kMain8002D80CWords[] = {
#include "8002d80c_words.inc"
};
static const uint32_t kMain8002D834Words[] = {
#include "8002d834_words.inc"
};
static const uint32_t kMain8002D844Words[] = {
#include "8002d844_words.inc"
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
static const uint32_t kMain80036D24Words[] = {
#include "80036d24_words.inc"
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
static const uint32_t kMain800401E4Words[] = {
#include "800401e4_words.inc"
};
static const uint32_t kMain800402A8Words[] = {
#include "800402a8_words.inc"
};
static const uint32_t kMain800403A4Words[] = {
#include "800403a4_words.inc"
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
static const uint32_t kMain80041A20Words[] = {
#include "80041a20_words.inc"
};
static const uint32_t kMain80041A50Words[] = {
#include "80041a50_words.inc"
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
static const uint32_t kMain80042154Words[] = {
#include "80042154_words.inc"
};
static const uint32_t kMain800422B4Words[] = {
#include "800422b4_words.inc"
};
static const uint32_t kMain800422E8Words[] = {
#include "800422e8_words.inc"
};
static const uint32_t kMain80042374Words[] = {
#include "80042374_words.inc"
};
static const uint32_t kMain800439D4Words[] = {
#include "800439d4_words.inc"
};
static const uint32_t kMain800439F8Words[] = {
#include "800439f8_words.inc"
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
static const uint32_t kMain8001AAD0Words[] = {
#include "8001aad0_words.inc"
};
static const uint32_t kMain8001ABB4Words[] = {
#include "8001abb4_words.inc"
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
static const uint32_t kMain800153CCWords[] = {
#include "800153cc_words.inc"
};
static const uint32_t kMain80015424Words[] = {
#include "80015424_words.inc"
};
static const uint32_t kMain8001544CWords[] = {
#include "8001544c_words.inc"
};
static const uint32_t kMain80010DA0Words[] = {
#include "80010da0_words.inc"
};
static const uint32_t kMain80010DE0Words[] = {
#include "80010de0_words.inc"
};
static const uint32_t kMain80010E14Words[] = {
#include "80010e14_words.inc"
};
static const uint32_t kMain80010E48Words[] = {
#include "80010e48_words.inc"
};
static const uint32_t kMain80010E7CWords[] = {
#include "80010e7c_words.inc"
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
static const uint32_t kMain800112A8Words[] = {
#include "800112a8_words.inc"
};
static const uint32_t kMain800112C8Words[] = {
#include "800112c8_words.inc"
};
static const uint32_t kMain80011320Words[] = {
#include "80011320_words.inc"
};
static const uint32_t kMain80011350Words[] = {
#include "80011350_words.inc"
};
static const uint32_t kMain8001136CWords[] = {
#include "8001136c_words.inc"
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
static const uint32_t kMain8001AA78Words[] = {
#include "8001aa78_words.inc"
};
static const uint32_t kMain8001AA88Words[] = {
#include "8001aa88_words.inc"
};
static const uint32_t kMain80010F80Words[] = {
#include "80010f80_words.inc"
};
static const uint32_t kMain80029514Words[] = {
#include "80029514_words.inc"
};
static const uint32_t kMain80029524Words[] = {
#include "80029524_words.inc"
};
static const uint32_t kMain8002953CWords[] = {
#include "8002953c_words.inc"
};
static const uint32_t kMain8002954CWords[] = {
#include "8002954c_words.inc"
};
static const uint32_t kMain8002955CWords[] = {
#include "8002955c_words.inc"
};
static const uint32_t kMain8002957CWords[] = {
#include "8002957c_words.inc"
};
static const uint32_t kMain8002958CWords[] = {
#include "8002958c_words.inc"
};
static const uint32_t kMain8002959CWords[] = {
#include "8002959c_words.inc"
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
static const uint32_t kMain8003AE9CWords[] = {
#include "8003ae9c_words.inc"
};
static const uint32_t kMain800301A4Words[] = {
#include "800301a4_words.inc"
};
static const uint32_t kMain800301C8Words[] = {
#include "800301c8_words.inc"
};
static const uint32_t kMain80030470Words[] = {
#include "80030470_words.inc"
};
static const uint32_t kMain800304C8Words[] = {
#include "800304c8_words.inc"
};
static const uint32_t kMain80030538Words[] = {
#include "80030538_words.inc"
};
static const uint32_t kMain80030604Words[] = {
#include "80030604_words.inc"
};
static const uint32_t kMain80030634Words[] = {
#include "80030634_words.inc"
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
static const uint32_t kMain80014C54Words[] = {
#include "80014c54_words.inc"
};
static const uint32_t kMain80014D30Words[] = {
#include "80014d30_words.inc"
};
static const uint32_t kMain80014D68Words[] = {
#include "80014d68_words.inc"
};
static const uint32_t kMain80014D94Words[] = {
#include "80014d94_words.inc"
};
static const uint32_t kMain80014DC0Words[] = {
#include "80014dc0_words.inc"
};
static const uint32_t kMain80014DECWords[] = {
#include "80014dec_words.inc"
};
static const uint32_t kMain80014E24Words[] = {
#include "80014e24_words.inc"
};
static const uint32_t kMain80014E80Words[] = {
#include "80014e80_words.inc"
};
static const uint32_t kMain80014ED4Words[] = {
#include "80014ed4_words.inc"
};
static const uint32_t kMain80015018Words[] = {
#include "80015018_words.inc"
};
static const uint32_t kMain80015118Words[] = {
#include "80015118_words.inc"
};
static const uint32_t kMain80014CF8Words[] = {
#include "80014cf8_words.inc"
};
static const uint32_t kMain800167F0Words[] = {
#include "800167f0_words.inc"
};
static const uint32_t kMain800168B4Words[] = {
#include "800168b4_words.inc"
};
static const uint32_t kMain800168C4Words[] = {
#include "800168c4_words.inc"
};
static const uint32_t kMain80016940Words[] = {
#include "80016940_words.inc"
};
static const uint32_t kMain80016978Words[] = {
#include "80016978_words.inc"
};
static const uint32_t kMain80016A3CWords[] = {
#include "80016a3c_words.inc"
};
static const uint32_t kMain80016A5CWords[] = {
#include "80016a5c_words.inc"
};
static const uint32_t kMain80016A7CWords[] = {
#include "80016a7c_words.inc"
};
static const uint32_t kMain80016B60Words[] = {
#include "80016b60_words.inc"
};
static const uint32_t kMain80016C28Words[] = {
#include "80016c28_words.inc"
};
static const uint32_t kMain80016D78Words[] = {
#include "80016d78_words.inc"
};
static const uint32_t kMain80016EB0Words[] = {
#include "80016eb0_words.inc"
};
static const uint32_t kMain80016ED4Words[] = {
#include "80016ed4_words.inc"
};
static const uint32_t kMain80016EF8Words[] = {
#include "80016ef8_words.inc"
};
static const uint32_t kMain80016F18Words[] = {
#include "80016f18_words.inc"
};
static const uint32_t kMain80017168Words[] = {
#include "80017168_words.inc"
};
static const uint32_t kMain80017254Words[] = {
#include "80017254_words.inc"
};
static const uint32_t kMain80017274Words[] = {
#include "80017274_words.inc"
};
static const uint32_t kMain80017294Words[] = {
#include "80017294_words.inc"
};
static const uint32_t kMain8001739CWords[] = {
#include "8001739c_words.inc"
};
static const uint32_t kMain800173BCWords[] = {
#include "800173bc_words.inc"
};
static const uint32_t kMain800173DCWords[] = {
#include "800173dc_words.inc"
};
static const uint32_t kMain800174DCWords[] = {
#include "800174dc_words.inc"
};
static const uint32_t kMain800174FCWords[] = {
#include "800174fc_words.inc"
};
static const uint32_t kMain8001751CWords[] = {
#include "8001751c_words.inc"
};
static const uint32_t kMain800176F0Words[] = {
#include "800176f0_words.inc"
};
static const uint32_t kMain80017714Words[] = {
#include "80017714_words.inc"
};
static const uint32_t kMain80017738Words[] = {
#include "80017738_words.inc"
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
static const uint32_t kMain80055D40Words[] = {
#include "80055d40_words.inc"
};
static const uint32_t kMain80056F18Words[] = {
#include "80056f18_words.inc"
};
static const uint32_t kMain80057094Words[] = {
#include "80057094_words.inc"
};
static const uint32_t kMain80057928Words[] = {
#include "80057928_words.inc"
};
static const uint32_t kMain80057B14Words[] = {
#include "80057b14_words.inc"
};
static const uint32_t kMain80057C7CWords[] = {
#include "80057c7c_words.inc"
};
static const uint32_t kMain80057E80Words[] = {
#include "80057e80_words.inc"
};
static const uint32_t kMain80057FFCWords[] = {
#include "80057ffc_words.inc"
};
static const uint32_t kMain80058284Words[] = {
#include "80058284_words.inc"
};
static const uint32_t kMain8005845CWords[] = {
#include "8005845c_words.inc"
};
static const uint32_t kMain800586CCWords[] = {
#include "800586cc_words.inc"
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
static const uint32_t kMain8001C448Words[] = {
#include "8001c448_words.inc"
};
static const uint32_t kMain8001C4A4Words[] = {
#include "8001c4a4_words.inc"
};
static const uint32_t kMain8001C558Words[] = {
#include "8001c558_words.inc"
};
static const uint32_t kMain8001C5B8Words[] = {
#include "8001c5b8_words.inc"
};
static const uint32_t kMain8001C6E4Words[] = {
#include "8001c6e4_words.inc"
};
static const uint32_t kMain8001C744Words[] = {
#include "8001c744_words.inc"
};
static const uint32_t kMain8001C7B0Words[] = {
#include "8001c7b0_words.inc"
};
static const uint32_t kMain800285ACWords[] = {
#include "800285ac_words.inc"
};
static const uint32_t kMain800285CCWords[] = {
#include "800285cc_words.inc"
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
static const uint32_t kMain80011680Words[] = {
#include "80011680_words.inc"
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
static const uint32_t kMain80011998Words[] = {
#include "80011998_words.inc"
};
static const uint32_t kMain800119F0Words[] = {
#include "800119f0_words.inc"
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
static const uint32_t kMain80029020Words[] = {
#include "80029020_words.inc"
};
static const uint32_t kMain80029044Words[] = {
#include "80029044_words.inc"
};
static const uint32_t kMain8002906CWords[] = {
#include "8002906c_words.inc"
};
static const uint32_t kMain80029094Words[] = {
#include "80029094_words.inc"
};
static const uint32_t kMain800290BCWords[] = {
#include "800290bc_words.inc"
};
static const uint32_t kMain800290E0Words[] = {
#include "800290e0_words.inc"
};
static const uint32_t kMain80028D9CWords[] = {
#include "80028d9c_words.inc"
};
static const uint32_t kMain80028DBCWords[] = {
#include "80028dbc_words.inc"
};
static const uint32_t kMain80028DE0Words[] = {
#include "80028de0_words.inc"
};
static const uint32_t kMain80028E00Words[] = {
#include "80028e00_words.inc"
};
static const uint32_t kMain80028E24Words[] = {
#include "80028e24_words.inc"
};
static const uint32_t kMain80028E44Words[] = {
#include "80028e44_words.inc"
};
static const uint32_t kMain80028E68Words[] = {
#include "80028e68_words.inc"
};
static const uint32_t kMain80028E88Words[] = {
#include "80028e88_words.inc"
};
static const uint32_t kMain80028EACWords[] = {
#include "80028eac_words.inc"
};
static const uint32_t kMain80028ECCWords[] = {
#include "80028ecc_words.inc"
};
static const uint32_t kMain80028EF0Words[] = {
#include "80028ef0_words.inc"
};
static const uint32_t kMain80028F10Words[] = {
#include "80028f10_words.inc"
};
static const uint32_t kMain80028F34Words[] = {
#include "80028f34_words.inc"
};
static const uint32_t kMain80028F54Words[] = {
#include "80028f54_words.inc"
};
static const uint32_t kMain80028F78Words[] = {
#include "80028f78_words.inc"
};
static const uint32_t kMain80028F98Words[] = {
#include "80028f98_words.inc"
};
static const uint32_t kMain80028FBCWords[] = {
#include "80028fbc_words.inc"
};
static const uint32_t kMain80028FDCWords[] = {
#include "80028fdc_words.inc"
};
static const uint32_t kMain800183E0Words[] = {
#include "800183e0_words.inc"
};
static const uint32_t kMain80018450Words[] = {
#include "80018450_words.inc"
};
static const uint32_t kMain800167B8Words[] = {
#include "800167b8_words.inc"
};
static const uint32_t kMain80016224Words[] = {
#include "80016224_words.inc"
};
static const uint32_t kMain80016450Words[] = {
#include "80016450_words.inc"
};
static const uint32_t kMain80010A08Words[] = {
#include "80010a08_words.inc"
};
static const uint32_t kMain80016638Words[] = {
#include "80016638_words.inc"
};
static const uint32_t kMain800166E8Words[] = {
#include "800166e8_words.inc"
};
static const uint32_t kMain80016714Words[] = {
#include "80016714_words.inc"
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
static const uint32_t kMain80011ADCWords[] = {
#include "80011adc_words.inc"
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
static const uint32_t kOverlay0010_800CF8B4Words[] = {
#include "800cf8b4_overlay0010_words.inc"
};
_Static_assert(sizeof(kOverlay0010_800CF8B4Words) / sizeof(uint32_t) == 6,
               "overlay 0010 800CF8B4 span changed");
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
static const uint32_t kOverlaySc02_80129CF8Words[] = {
#include "80129cf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A328Words[] = {
#include "8012a328_sc02_0031_words.inc"
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
static const uint32_t kOverlay0010_800D1FC8Words[] = {
#include "800d1fc8_overlay0010_words.inc"
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
static const uint32_t kOverlay0010_800D06E8Words[] = {
#include "800d06e8_overlay0010_words.inc"
};
static const uint32_t kOverlaySc02_80145CECWords[] = {
#include "80145cec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801552F4Words[] = {
#include "801552f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A2D8Words[] = {
#include "8015a2d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801619A4Words[] = {
#include "801619a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161B18Words[] = {
#include "80161b18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159C84Words[] = {
#include "80159c84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015126CWords[] = {
#include "8015126c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158638Words[] = {
#include "80158638_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159A20Words[] = {
#include "80159a20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801654A8Words[] = {
#include "801654a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171EC8Words[] = {
#include "80171ec8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017849CWords[] = {
#include "8017849c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801719A4Words[] = {
#include "801719a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F14CWords[] = {
#include "8016f14c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F1C4Words[] = {
#include "8016f1c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161A90Words[] = {
#include "80161a90_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_801627E8Words[] = {
#include "801627e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162AF4Words[] = {
#include "80162af4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162B1CWords[] = {
#include "80162b1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165C78Words[] = {
#include "80165c78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165CA0Words[] = {
#include "80165ca0_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_801599A4Words[] = {
#include "801599a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A1C8Words[] = {
#include "8015a1c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801553C0Words[] = {
#include "801553c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154A74Words[] = {
#include "80154a74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154AB4Words[] = {
#include "80154ab4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154AE0Words[] = {
#include "80154ae0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154B20Words[] = {
#include "80154b20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154B4CWords[] = {
#include "80154b4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154B7CWords[] = {
#include "80154b7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154B98Words[] = {
#include "80154b98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154BC8Words[] = {
#include "80154bc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154BE4Words[] = {
#include "80154be4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154C24Words[] = {
#include "80154c24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154ED8Words[] = {
#include "80154ed8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154F9CWords[] = {
#include "80154f9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801550FCWords[] = {
#include "801550fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155150Words[] = {
#include "80155150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151944Words[] = {
#include "80151944_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151D24Words[] = {
#include "80151d24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152058Words[] = {
#include "80152058_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801520DCWords[] = {
#include "801520dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152370Words[] = {
#include "80152370_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152698Words[] = {
#include "80152698_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015282CWords[] = {
#include "8015282c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801528B0Words[] = {
#include "801528b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152B6CWords[] = {
#include "80152b6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152D24Words[] = {
#include "80152d24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152DA8Words[] = {
#include "80152da8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153060Words[] = {
#include "80153060_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153320Words[] = {
#include "80153320_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128288Words[] = {
#include "80128288_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801612B8Words[] = {
#include "801612b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80133784Words[] = {
#include "80133784_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80133AB0Words[] = {
#include "80133ab0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159BE4Words[] = {
#include "80159be4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015444CWords[] = {
#include "8015444c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155458Words[] = {
#include "80155458_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128218Words[] = {
#include "80128218_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801288B0Words[] = {
#include "801288b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128940Words[] = {
#include "80128940_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128998Words[] = {
#include "80128998_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801289F0Words[] = {
#include "801289f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128C98Words[] = {
#include "80128c98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128CFCWords[] = {
#include "80128cfc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128FACWords[] = {
#include "80128fac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129010Words[] = {
#include "80129010_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012DB84Words[] = {
#include "8012db84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013373CWords[] = {
#include "8013373c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80133CD4Words[] = {
#include "80133cd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136C90Words[] = {
#include "80136c90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80137B80Words[] = {
#include "80137b80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013AD38Words[] = {
#include "8013ad38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B274Words[] = {
#include "8013b274_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B7ACWords[] = {
#include "8013b7ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B7F4Words[] = {
#include "8013b7f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013BD34Words[] = {
#include "8013bd34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C938Words[] = {
#include "8013c938_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C964Words[] = {
#include "8013c964_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161C24Words[] = {
#include "80161c24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013C9C4Words[] = {
#include "8013c9c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CA14Words[] = {
#include "8013ca14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D330Words[] = {
#include "8013d330_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164E40Words[] = {
#include "80164e40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CABCWords[] = {
#include "8013cabc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CAE8Words[] = {
#include "8013cae8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CB20Words[] = {
#include "8013cb20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CB5CWords[] = {
#include "8013cb5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013CB84Words[] = {
#include "8013cb84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D064Words[] = {
#include "8013d064_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D13CWords[] = {
#include "8013d13c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D164Words[] = {
#include "8013d164_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013D9B0Words[] = {
#include "8013d9b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E054Words[] = {
#include "8013e054_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80140F00Words[] = {
#include "80140f00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014358CWords[] = {
#include "8014358c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153CCCWords[] = {
#include "80153ccc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157788Words[] = {
#include "80157788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801577C8Words[] = {
#include "801577c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157808Words[] = {
#include "80157808_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015879CWords[] = {
#include "8015879c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158814Words[] = {
#include "80158814_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158FA4Words[] = {
#include "80158fa4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015934CWords[] = {
#include "8015934c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C7E4Words[] = {
#include "8015c7e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CA28Words[] = {
#include "8015ca28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CD20Words[] = {
#include "8015cd20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D5E8Words[] = {
#include "8015d5e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016216CWords[] = {
#include "8016216c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801622C4Words[] = {
#include "801622c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162760Words[] = {
#include "80162760_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80163408Words[] = {
#include "80163408_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801634D8Words[] = {
#include "801634d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164EE0Words[] = {
#include "80164ee0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165E2CWords[] = {
#include "80165e2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169F3CWords[] = {
#include "80169f3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B9F8Words[] = {
#include "8016b9f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BEA0Words[] = {
#include "8016bea0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BFA8Words[] = {
#include "8016bfa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DA7CWords[] = {
#include "8016da7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178438Words[] = {
#include "80178438_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178840Words[] = {
#include "80178840_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178CBCWords[] = {
#include "80178cbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178D18Words[] = {
#include "80178d18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A094Words[] = {
#include "8017a094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A0C4Words[] = {
#include "8017a0c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A144Words[] = {
#include "8017a144_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017B1D8Words[] = {
#include "8017b1d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017B7A8Words[] = {
#include "8017b7a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017B880Words[] = {
#include "8017b880_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017B8E8Words[] = {
#include "8017b8e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017BC38Words[] = {
#include "8017bc38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017BCA0Words[] = {
#include "8017bca0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017BCF4Words[] = {
#include "8017bcf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E9C0Words[] = {
#include "8012e9c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F828Words[] = {
#include "8012f828_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F8C8Words[] = {
#include "8012f8c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FCC4Words[] = {
#include "8012fcc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130D0CWords[] = {
#include "80130d0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131E00Words[] = {
#include "80131e00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131EECWords[] = {
#include "80131eec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131F28Words[] = {
#include "80131f28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131F64Words[] = {
#include "80131f64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131FA0Words[] = {
#include "80131fa0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801320D8Words[] = {
#include "801320d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132144Words[] = {
#include "80132144_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801321B0Words[] = {
#include "801321b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136C54Words[] = {
#include "80136c54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80137D08Words[] = {
#include "80137d08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138BE0Words[] = {
#include "80138be0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013BC7CWords[] = {
#include "8013bc7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013BCDCWords[] = {
#include "8013bcdc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80141788Words[] = {
#include "80141788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80141C0CWords[] = {
#include "80141c0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801425CCWords[] = {
#include "801425cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801427ECWords[] = {
#include "801427ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014292CWords[] = {
#include "8014292c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142978Words[] = {
#include "80142978_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801429C4Words[] = {
#include "801429c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142A10Words[] = {
#include "80142a10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143458Words[] = {
#include "80143458_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143B30Words[] = {
#include "80143b30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143C38Words[] = {
#include "80143c38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143C98Words[] = {
#include "80143c98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143E68Words[] = {
#include "80143e68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155580Words[] = {
#include "80155580_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801563ECWords[] = {
#include "801563ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80156A1CWords[] = {
#include "80156a1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157544Words[] = {
#include "80157544_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801578C0Words[] = {
#include "801578c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157D20Words[] = {
#include "80157d20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157DC4Words[] = {
#include "80157dc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157FC4Words[] = {
#include "80157fc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158038Words[] = {
#include "80158038_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015824CWords[] = {
#include "8015824c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158880Words[] = {
#include "80158880_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159698Words[] = {
#include "80159698_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159968Words[] = {
#include "80159968_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159B70Words[] = {
#include "80159b70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A264Words[] = {
#include "8015a264_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015AC48Words[] = {
#include "8015ac48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015AD3CWords[] = {
#include "8015ad3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BE38Words[] = {
#include "8015be38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BFF4Words[] = {
#include "8015bff4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C714Words[] = {
#include "8015c714_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C944Words[] = {
#include "8015c944_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CC74Words[] = {
#include "8015cc74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CFC0Words[] = {
#include "8015cfc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D01CWords[] = {
#include "8015d01c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D104Words[] = {
#include "8015d104_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D414Words[] = {
#include "8015d414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D4E8Words[] = {
#include "8015d4e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DAF8Words[] = {
#include "8015daf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DBD4Words[] = {
#include "8015dbd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DE58Words[] = {
#include "8015de58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DF34Words[] = {
#include "8015df34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E1B8Words[] = {
#include "8015e1b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E344Words[] = {
#include "8015e344_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E588Words[] = {
#include "8015e588_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E698Words[] = {
#include "8015e698_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E8E8Words[] = {
#include "8015e8e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EE08Words[] = {
#include "8015ee08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EE7CWords[] = {
#include "8015ee7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EEE0Words[] = {
#include "8015eee0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F00CWords[] = {
#include "8015f00c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F118Words[] = {
#include "8015f118_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F324Words[] = {
#include "8015f324_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F7D4Words[] = {
#include "8015f7d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F9A4Words[] = {
#include "8015f9a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FAACWords[] = {
#include "8015faac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FBE0Words[] = {
#include "8015fbe0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FCC8Words[] = {
#include "8015fcc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FD74Words[] = {
#include "8015fd74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FE70Words[] = {
#include "8015fe70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160138Words[] = {
#include "80160138_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801602A4Words[] = {
#include "801602a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016039CWords[] = {
#include "8016039c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016084CWords[] = {
#include "8016084c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160920Words[] = {
#include "80160920_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801609B8Words[] = {
#include "801609b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160B34Words[] = {
#include "80160b34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160EA4Words[] = {
#include "80160ea4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161034Words[] = {
#include "80161034_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161C98Words[] = {
#include "80161c98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161CD0Words[] = {
#include "80161cd0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161D20Words[] = {
#include "80161d20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161D88Words[] = {
#include "80161d88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162330Words[] = {
#include "80162330_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162834Words[] = {
#include "80162834_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162870Words[] = {
#include "80162870_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162968Words[] = {
#include "80162968_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80163A58Words[] = {
#include "80163a58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164744Words[] = {
#include "80164744_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164BA0Words[] = {
#include "80164ba0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164EA4Words[] = {
#include "80164ea4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165580Words[] = {
#include "80165580_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165658Words[] = {
#include "80165658_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165670Words[] = {
#include "80165670_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801656D0Words[] = {
#include "801656d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801656E8Words[] = {
#include "801656e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165700Words[] = {
#include "80165700_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165AC8Words[] = {
#include "80165ac8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165B28Words[] = {
#include "80165b28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80166018Words[] = {
#include "80166018_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80166054Words[] = {
#include "80166054_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801663FCWords[] = {
#include "801663fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80166618Words[] = {
#include "80166618_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80166654Words[] = {
#include "80166654_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801678B4Words[] = {
#include "801678b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80167A9CWords[] = {
#include "80167a9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168744Words[] = {
#include "80168744_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801689D8Words[] = {
#include "801689d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168AA8Words[] = {
#include "80168aa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168D58Words[] = {
#include "80168d58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016901CWords[] = {
#include "8016901c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801693CCWords[] = {
#include "801693cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169830Words[] = {
#include "80169830_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169B80Words[] = {
#include "80169b80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169F00Words[] = {
#include "80169f00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016A020Words[] = {
#include "8016a020_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016A700Words[] = {
#include "8016a700_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016AB30Words[] = {
#include "8016ab30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B4BCWords[] = {
#include "8016b4bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BBA4Words[] = {
#include "8016bba4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016C14CWords[] = {
#include "8016c14c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016CB84Words[] = {
#include "8016cb84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D19CWords[] = {
#include "8016d19c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D428Words[] = {
#include "8016d428_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DA30Words[] = {
#include "8016da30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DEA4Words[] = {
#include "8016dea4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DF20Words[] = {
#include "8016df20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E5B8Words[] = {
#include "8016e5b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EAC0Words[] = {
#include "8016eac0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F6E0Words[] = {
#include "8016f6e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F798Words[] = {
#include "8016f798_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F834Words[] = {
#include "8016f834_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F8E4Words[] = {
#include "8016f8e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F9C4Words[] = {
#include "8016f9c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FA84Words[] = {
#include "8016fa84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FB7CWords[] = {
#include "8016fb7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FC90Words[] = {
#include "8016fc90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FDB4Words[] = {
#include "8016fdb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FF30Words[] = {
#include "8016ff30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FFDCWords[] = {
#include "8016ffdc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170150Words[] = {
#include "80170150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170240Words[] = {
#include "80170240_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801702FCWords[] = {
#include "801702fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801703E0Words[] = {
#include "801703e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801704B0Words[] = {
#include "801704b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170548Words[] = {
#include "80170548_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801705F8Words[] = {
#include "801705f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801706ACWords[] = {
#include "801706ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170748Words[] = {
#include "80170748_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170810Words[] = {
#include "80170810_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170AD8Words[] = {
#include "80170ad8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170BD8Words[] = {
#include "80170bd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170C74Words[] = {
#include "80170c74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170D68Words[] = {
#include "80170d68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170E34Words[] = {
#include "80170e34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170EFCWords[] = {
#include "80170efc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170FB0Words[] = {
#include "80170fb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171064Words[] = {
#include "80171064_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171120Words[] = {
#include "80171120_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801711C0Words[] = {
#include "801711c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171260Words[] = {
#include "80171260_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801714E4Words[] = {
#include "801714e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801727D0Words[] = {
#include "801727d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801728E4Words[] = {
#include "801728e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801729F0Words[] = {
#include "801729f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172B44Words[] = {
#include "80172b44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172CA0Words[] = {
#include "80172ca0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172DACWords[] = {
#include "80172dac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173078Words[] = {
#include "80173078_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017319CWords[] = {
#include "8017319c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173220Words[] = {
#include "80173220_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173544Words[] = {
#include "80173544_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801736FCWords[] = {
#include "801736fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801737E8Words[] = {
#include "801737e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017390CWords[] = {
#include "8017390c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173B4CWords[] = {
#include "80173b4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801742A4Words[] = {
#include "801742a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174384Words[] = {
#include "80174384_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174474Words[] = {
#include "80174474_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801747CCWords[] = {
#include "801747cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174888Words[] = {
#include "80174888_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017496CWords[] = {
#include "8017496c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174BF4Words[] = {
#include "80174bf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174F28Words[] = {
#include "80174f28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175184Words[] = {
#include "80175184_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017553CWords[] = {
#include "8017553c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175690Words[] = {
#include "80175690_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175798Words[] = {
#include "80175798_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017BE60Words[] = {
#include "8017be60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128178Words[] = {
#include "80128178_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128198Words[] = {
#include "80128198_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801281B8Words[] = {
#include "801281b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801281D8Words[] = {
#include "801281d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801281F8Words[] = {
#include "801281f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128228Words[] = {
#include "80128228_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128248Words[] = {
#include "80128248_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128268Words[] = {
#include "80128268_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801282CCWords[] = {
#include "801282cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801282ECWords[] = {
#include "801282ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128D60Words[] = {
#include "80128d60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128EA8Words[] = {
#include "80128ea8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80128ED8Words[] = {
#include "80128ed8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801290DCWords[] = {
#include "801290dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012913CWords[] = {
#include "8012913c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801291C0Words[] = {
#include "801291c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012927CWords[] = {
#include "8012927c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801292C8Words[] = {
#include "801292c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012931CWords[] = {
#include "8012931c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129350Words[] = {
#include "80129350_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129374Words[] = {
#include "80129374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129428Words[] = {
#include "80129428_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012943CWords[] = {
#include "8012943c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80129FF4Words[] = {
#include "80129ff4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A0E0Words[] = {
#include "8012a0e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A100Words[] = {
#include "8012a100_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A110Words[] = {
#include "8012a110_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A2F4Words[] = {
#include "8012a2f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A304Words[] = {
#include "8012a304_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A418Words[] = {
#include "8012a418_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A464Words[] = {
#include "8012a464_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A4BCWords[] = {
#include "8012a4bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A568Words[] = {
#include "8012a568_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A598Words[] = {
#include "8012a598_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A5F8Words[] = {
#include "8012a5f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A62CWords[] = {
#include "8012a62c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A68CWords[] = {
#include "8012a68c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A6D0Words[] = {
#include "8012a6d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A758Words[] = {
#include "8012a758_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A79CWords[] = {
#include "8012a79c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A7D4Words[] = {
#include "8012a7d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A860Words[] = {
#include "8012a860_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A8B0Words[] = {
#include "8012a8b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A8E8Words[] = {
#include "8012a8e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A908Words[] = {
#include "8012a908_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012A988Words[] = {
#include "8012a988_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD3CWords[] = {
#include "8012ad3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD64Words[] = {
#include "8012ad64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD6CWords[] = {
#include "8012ad6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012AD80Words[] = {
#include "8012ad80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012ADE4Words[] = {
#include "8012ade4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B178Words[] = {
#include "8012b178_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B1B4Words[] = {
#include "8012b1b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B200Words[] = {
#include "8012b200_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B21CWords[] = {
#include "8012b21c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B23CWords[] = {
#include "8012b23c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B370Words[] = {
#include "8012b370_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B414Words[] = {
#include "8012b414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B6D4Words[] = {
#include "8012b6d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B70CWords[] = {
#include "8012b70c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B744Words[] = {
#include "8012b744_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B864Words[] = {
#include "8012b864_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012B8A4Words[] = {
#include "8012b8a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BC60Words[] = {
#include "8012bc60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BD14Words[] = {
#include "8012bd14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BD3CWords[] = {
#include "8012bd3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BE54Words[] = {
#include "8012be54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BE98Words[] = {
#include "8012be98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BF4CWords[] = {
#include "8012bf4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BF54Words[] = {
#include "8012bf54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BF68Words[] = {
#include "8012bf68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BF7CWords[] = {
#include "8012bf7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012BFA8Words[] = {
#include "8012bfa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C044Words[] = {
#include "8012c044_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C098Words[] = {
#include "8012c098_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C31CWords[] = {
#include "8012c31c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012C724Words[] = {
#include "8012c724_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CBA4Words[] = {
#include "8012cba4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CBCCWords[] = {
#include "8012cbcc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CBF4Words[] = {
#include "8012cbf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CC1CWords[] = {
#include "8012cc1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CC40Words[] = {
#include "8012cc40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012CC64Words[] = {
#include "8012cc64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012D38CWords[] = {
#include "8012d38c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012D3B4Words[] = {
#include "8012d3b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012D4B4Words[] = {
#include "8012d4b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012D5E4Words[] = {
#include "8012d5e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012D624Words[] = {
#include "8012d624_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012DFD4Words[] = {
#include "8012dfd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E27CWords[] = {
#include "8012e27c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E284Words[] = {
#include "8012e284_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E28CWords[] = {
#include "8012e28c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E32CWords[] = {
#include "8012e32c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E504Words[] = {
#include "8012e504_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E544Words[] = {
#include "8012e544_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E57CWords[] = {
#include "8012e57c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E778Words[] = {
#include "8012e778_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E88CWords[] = {
#include "8012e88c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E8A8Words[] = {
#include "8012e8a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012E8C4Words[] = {
#include "8012e8c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012EC04Words[] = {
#include "8012ec04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012EECCWords[] = {
#include "8012eecc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012EF34Words[] = {
#include "8012ef34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012EF70Words[] = {
#include "8012ef70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012EFB8Words[] = {
#include "8012efb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F038Words[] = {
#include "8012f038_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F0BCWords[] = {
#include "8012f0bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F1A4Words[] = {
#include "8012f1a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F214Words[] = {
#include "8012f214_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F2E8Words[] = {
#include "8012f2e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F374Words[] = {
#include "8012f374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F5F4Words[] = {
#include "8012f5f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F75CWords[] = {
#include "8012f75c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F7B4Words[] = {
#include "8012f7b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F87CWords[] = {
#include "8012f87c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012F91CWords[] = {
#include "8012f91c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FB54Words[] = {
#include "8012fb54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FC30Words[] = {
#include "8012fc30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FCA4Words[] = {
#include "8012fca4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FDA8Words[] = {
#include "8012fda8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FE70Words[] = {
#include "8012fe70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FF00Words[] = {
#include "8012ff00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FF4CWords[] = {
#include "8012ff4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8012FF98Words[] = {
#include "8012ff98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130278Words[] = {
#include "80130278_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130314Words[] = {
#include "80130314_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130360Words[] = {
#include "80130360_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801303A0Words[] = {
#include "801303a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801303ECWords[] = {
#include "801303ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130514Words[] = {
#include "80130514_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801305CCWords[] = {
#include "801305cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130650Words[] = {
#include "80130650_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130740Words[] = {
#include "80130740_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801307B0Words[] = {
#include "801307b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130858Words[] = {
#include "80130858_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130898Words[] = {
#include "80130898_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801308DCWords[] = {
#include "801308dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130974Words[] = {
#include "80130974_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130A18Words[] = {
#include "80130a18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80130AF0Words[] = {
#include "80130af0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801319E0Words[] = {
#include "801319e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131C78Words[] = {
#include "80131c78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131D68Words[] = {
#include "80131d68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131E38Words[] = {
#include "80131e38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80131E7CWords[] = {
#include "80131e7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132784Words[] = {
#include "80132784_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132DC4Words[] = {
#include "80132dc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132E6CWords[] = {
#include "80132e6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132EC4Words[] = {
#include "80132ec4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80132EF4Words[] = {
#include "80132ef4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80133060Words[] = {
#include "80133060_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801330E0Words[] = {
#include "801330e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80134310Words[] = {
#include "80134310_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013435CWords[] = {
#include "8013435c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80134A28Words[] = {
#include "80134a28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80134FB8Words[] = {
#include "80134fb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136C1CWords[] = {
#include "80136c1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136C3CWords[] = {
#include "80136c3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136D08Words[] = {
#include "80136d08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136DFCWords[] = {
#include "80136dfc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136ECCWords[] = {
#include "80136ecc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801375ECWords[] = {
#include "801375ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80137614Words[] = {
#include "80137614_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013767CWords[] = {
#include "8013767c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801376C8Words[] = {
#include "801376c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80137840Words[] = {
#include "80137840_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801379D8Words[] = {
#include "801379d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801379ECWords[] = {
#include "801379ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801379FCWords[] = {
#include "801379fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138948Words[] = {
#include "80138948_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138B88Words[] = {
#include "80138b88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138C30Words[] = {
#include "80138c30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138D58Words[] = {
#include "80138d58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80138DB8Words[] = {
#include "80138db8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801391F0Words[] = {
#include "801391f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139220Words[] = {
#include "80139220_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801392C8Words[] = {
#include "801392c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801395D4Words[] = {
#include "801395d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139634Words[] = {
#include "80139634_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139788Words[] = {
#include "80139788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139914Words[] = {
#include "80139914_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139954Words[] = {
#include "80139954_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801399A8Words[] = {
#include "801399a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801399F0Words[] = {
#include "801399f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139A34Words[] = {
#include "80139a34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139A44Words[] = {
#include "80139a44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139A68Words[] = {
#include "80139a68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139B18Words[] = {
#include "80139b18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139C7CWords[] = {
#include "80139c7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139DC8Words[] = {
#include "80139dc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139F0CWords[] = {
#include "80139f0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139FBCWords[] = {
#include "80139fbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80139FE8Words[] = {
#include "80139fe8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A0A4Words[] = {
#include "8013a0a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A164Words[] = {
#include "8013a164_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A1E8Words[] = {
#include "8013a1e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A250Words[] = {
#include "8013a250_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A380Words[] = {
#include "8013a380_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A448Words[] = {
#include "8013a448_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A4C4Words[] = {
#include "8013a4c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A8B0Words[] = {
#include "8013a8b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A8BCWords[] = {
#include "8013a8bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013A9B4Words[] = {
#include "8013a9b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013AA24Words[] = {
#include "8013aa24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013AB54Words[] = {
#include "8013ab54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013B204Words[] = {
#include "8013b204_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E064Words[] = {
#include "8013e064_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E0FCWords[] = {
#include "8013e0fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E194Words[] = {
#include "8013e194_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E22CWords[] = {
#include "8013e22c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E298Words[] = {
#include "8013e298_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E2C4Words[] = {
#include "8013e2c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E370Words[] = {
#include "8013e370_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E410Words[] = {
#include "8013e410_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E558Words[] = {
#include "8013e558_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E588Words[] = {
#include "8013e588_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E67CWords[] = {
#include "8013e67c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E814Words[] = {
#include "8013e814_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014168CWords[] = {
#include "8014168c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801417C4Words[] = {
#include "801417c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801417F8Words[] = {
#include "801417f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80141C04Words[] = {
#include "80141c04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80141C50Words[] = {
#include "80141c50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80141CA4Words[] = {
#include "80141ca4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142414Words[] = {
#include "80142414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801426D4Words[] = {
#include "801426d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142740Words[] = {
#include "80142740_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142778Words[] = {
#include "80142778_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142838Words[] = {
#include "80142838_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801428CCWords[] = {
#include "801428cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142B2CWords[] = {
#include "80142b2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142BB4Words[] = {
#include "80142bb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142C84Words[] = {
#include "80142c84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142D38Words[] = {
#include "80142d38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142DB8Words[] = {
#include "80142db8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142F68Words[] = {
#include "80142f68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142FFCWords[] = {
#include "80142ffc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801430F4Words[] = {
#include "801430f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143188Words[] = {
#include "80143188_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801432FCWords[] = {
#include "801432fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143390Words[] = {
#include "80143390_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801433F0Words[] = {
#include "801433f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014350CWords[] = {
#include "8014350c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143994Words[] = {
#include "80143994_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801439C0Words[] = {
#include "801439c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80143C74Words[] = {
#include "80143c74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A680Words[] = {
#include "8014a680_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A6A8Words[] = {
#include "8014a6a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A6C4Words[] = {
#include "8014a6c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A71CWords[] = {
#include "8014a71c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014A830Words[] = {
#include "8014a830_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150F78Words[] = {
#include "80150f78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150F80Words[] = {
#include "80150f80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150FB4Words[] = {
#include "80150fb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150FD8Words[] = {
#include "80150fd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151014Words[] = {
#include "80151014_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151038Words[] = {
#include "80151038_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151070Words[] = {
#include "80151070_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151094Words[] = {
#include "80151094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801510C8Words[] = {
#include "801510c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801510ECWords[] = {
#include "801510ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151110Words[] = {
#include "80151110_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151138Words[] = {
#include "80151138_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151164Words[] = {
#include "80151164_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151184Words[] = {
#include "80151184_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801511A8Words[] = {
#include "801511a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801511C4Words[] = {
#include "801511c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801511E0Words[] = {
#include "801511e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151204Words[] = {
#include "80151204_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151238Words[] = {
#include "80151238_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151664Words[] = {
#include "80151664_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801516F0Words[] = {
#include "801516f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015173CWords[] = {
#include "8015173c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151878Words[] = {
#include "80151878_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151924Words[] = {
#include "80151924_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151980Words[] = {
#include "80151980_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151AE4Words[] = {
#include "80151ae4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151D60Words[] = {
#include "80151d60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151DB0Words[] = {
#include "80151db0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151E78Words[] = {
#include "80151e78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151ECCWords[] = {
#include "80151ecc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151F38Words[] = {
#include "80151f38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80151FB4Words[] = {
#include "80151fb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152094Words[] = {
#include "80152094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152194Words[] = {
#include "80152194_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015220CWords[] = {
#include "8015220c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801522CCWords[] = {
#include "801522cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801523ACWords[] = {
#include "801523ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801525F4Words[] = {
#include "801525f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801526D4Words[] = {
#include "801526d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152790Words[] = {
#include "80152790_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152868Words[] = {
#include "80152868_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015294CWords[] = {
#include "8015294c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152A08Words[] = {
#include "80152a08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152AC8Words[] = {
#include "80152ac8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152BA8Words[] = {
#include "80152ba8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152BF0Words[] = {
#include "80152bf0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152C40Words[] = {
#include "80152c40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152C80Words[] = {
#include "80152c80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152D60Words[] = {
#include "80152d60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152E4CWords[] = {
#include "80152e4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152EFCWords[] = {
#include "80152efc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80152FBCWords[] = {
#include "80152fbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015309CWords[] = {
#include "8015309c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801530E4Words[] = {
#include "801530e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153150Words[] = {
#include "80153150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801531BCWords[] = {
#include "801531bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015327CWords[] = {
#include "8015327c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015335CWords[] = {
#include "8015335c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801533A4Words[] = {
#include "801533a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153410Words[] = {
#include "80153410_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153490Words[] = {
#include "80153490_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153550Words[] = {
#include "80153550_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015369CWords[] = {
#include "8015369c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153BD8Words[] = {
#include "80153bd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153BF0Words[] = {
#include "80153bf0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C18Words[] = {
#include "80153c18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C30Words[] = {
#include "80153c30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C44Words[] = {
#include "80153c44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C74Words[] = {
#include "80153c74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153C9CWords[] = {
#include "80153c9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153CBCWords[] = {
#include "80153cbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80153D34Words[] = {
#include "80153d34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015410CWords[] = {
#include "8015410c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154134Words[] = {
#include "80154134_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154150Words[] = {
#include "80154150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154190Words[] = {
#include "80154190_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801541D8Words[] = {
#include "801541d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154218Words[] = {
#include "80154218_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154274Words[] = {
#include "80154274_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801542A4Words[] = {
#include "801542a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801542DCWords[] = {
#include "801542dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015430CWords[] = {
#include "8015430c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80154418Words[] = {
#include "80154418_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155344Words[] = {
#include "80155344_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155394Words[] = {
#include "80155394_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801553A8Words[] = {
#include "801553a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155440Words[] = {
#include "80155440_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801554B8Words[] = {
#include "801554b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155518Words[] = {
#include "80155518_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015554CWords[] = {
#include "8015554c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801555BCWords[] = {
#include "801555bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155B20Words[] = {
#include "80155b20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155B9CWords[] = {
#include "80155b9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155F60Words[] = {
#include "80155f60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155F80Words[] = {
#include "80155f80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155FB0Words[] = {
#include "80155fb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80155FD4Words[] = {
#include "80155fd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801565C0Words[] = {
#include "801565c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80156648Words[] = {
#include "80156648_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801567BCWords[] = {
#include "801567bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80156A14Words[] = {
#include "80156a14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157158Words[] = {
#include "80157158_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801574DCWords[] = {
#include "801574dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157510Words[] = {
#include "80157510_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157580Words[] = {
#include "80157580_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015771CWords[] = {
#include "8015771c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015773CWords[] = {
#include "8015773c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157880Words[] = {
#include "80157880_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157A8CWords[] = {
#include "80157a8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157AC8Words[] = {
#include "80157ac8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157B74Words[] = {
#include "80157b74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157CCCWords[] = {
#include "80157ccc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157D74Words[] = {
#include "80157d74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157E00Words[] = {
#include "80157e00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157E38Words[] = {
#include "80157e38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157EA4Words[] = {
#include "80157ea4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80157F64Words[] = {
#include "80157f64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158000Words[] = {
#include "80158000_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158288Words[] = {
#include "80158288_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801582C0Words[] = {
#include "801582c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158548Words[] = {
#include "80158548_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801585ACWords[] = {
#include "801585ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801585ECWords[] = {
#include "801585ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158AB4Words[] = {
#include "80158ab4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80158AE4Words[] = {
#include "80158ae4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801592CCWords[] = {
#include "801592cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801593E4Words[] = {
#include "801593e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801596D4Words[] = {
#include "801596d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159874Words[] = {
#include "80159874_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015987CWords[] = {
#include "8015987c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801598BCWords[] = {
#include "801598bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801599E0Words[] = {
#include "801599e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159B08Words[] = {
#include "80159b08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159B3CWords[] = {
#include "80159b3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80159BACWords[] = {
#include "80159bac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A1FCWords[] = {
#include "8015a1fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A230Words[] = {
#include "8015a230_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015A2A0Words[] = {
#include "8015a2a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015ABD4Words[] = {
#include "8015abd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015AC90Words[] = {
#include "8015ac90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015ACC4Words[] = {
#include "8015acc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015AD08Words[] = {
#include "8015ad08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015AD78Words[] = {
#include "8015ad78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015ADB0Words[] = {
#include "8015adb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015B858Words[] = {
#include "8015b858_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015B8F8Words[] = {
#include "8015b8f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BD8CWords[] = {
#include "8015bd8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BDD0Words[] = {
#include "8015bdd0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BE04Words[] = {
#include "8015be04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BE74Words[] = {
#include "8015be74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BE94Words[] = {
#include "8015be94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BEC4Words[] = {
#include "8015bec4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BEE4Words[] = {
#include "8015bee4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BF04Words[] = {
#include "8015bf04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BF48Words[] = {
#include "8015bf48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BF7CWords[] = {
#include "8015bf7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015BFB0Words[] = {
#include "8015bfb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C08CWords[] = {
#include "8015c08c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C6ACWords[] = {
#include "8015c6ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C6E0Words[] = {
#include "8015c6e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C750Words[] = {
#include "8015c750_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015C788Words[] = {
#include "8015c788_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CB94Words[] = {
#include "8015cb94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CC0CWords[] = {
#include "8015cc0c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CC40Words[] = {
#include "8015cc40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CCB0Words[] = {
#include "8015ccb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CCD0Words[] = {
#include "8015ccd0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CF24Words[] = {
#include "8015cf24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CF58Words[] = {
#include "8015cf58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CF8CWords[] = {
#include "8015cf8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015CFFCWords[] = {
#include "8015cffc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D480Words[] = {
#include "8015d480_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D4B4Words[] = {
#include "8015d4b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D524Words[] = {
#include "8015d524_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D544Words[] = {
#include "8015d544_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015D57CWords[] = {
#include "8015d57c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DA5CWords[] = {
#include "8015da5c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DA90Words[] = {
#include "8015da90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DAC4Words[] = {
#include "8015dac4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DB34Words[] = {
#include "8015db34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DB6CWords[] = {
#include "8015db6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DC84Words[] = {
#include "8015dc84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DD74Words[] = {
#include "8015dd74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DDF0Words[] = {
#include "8015ddf0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DE24Words[] = {
#include "8015de24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DE94Words[] = {
#include "8015de94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DECCWords[] = {
#include "8015decc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015DFE4Words[] = {
#include "8015dfe4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E0D4Words[] = {
#include "8015e0d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E150Words[] = {
#include "8015e150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E184Words[] = {
#include "8015e184_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E1F4Words[] = {
#include "8015e1f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E22CWords[] = {
#include "8015e22c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E288Words[] = {
#include "8015e288_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E40CWords[] = {
#include "8015e40c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E5B0Words[] = {
#include "8015e5b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E714Words[] = {
#include "8015e714_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E84CWords[] = {
#include "8015e84c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E880Words[] = {
#include "8015e880_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E8B4Words[] = {
#include "8015e8b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E924Words[] = {
#include "8015e924_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E95CWords[] = {
#include "8015e95c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015E9B8Words[] = {
#include "8015e9b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EDA0Words[] = {
#include "8015eda0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EDD4Words[] = {
#include "8015edd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EE44Words[] = {
#include "8015ee44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EFA4Words[] = {
#include "8015efa4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015EFD8Words[] = {
#include "8015efd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F048Words[] = {
#include "8015f048_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F080Words[] = {
#include "8015f080_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F260Words[] = {
#include "8015f260_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F2BCWords[] = {
#include "8015f2bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F2F0Words[] = {
#include "8015f2f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F360Words[] = {
#include "8015f360_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F380Words[] = {
#include "8015f380_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F738Words[] = {
#include "8015f738_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F76CWords[] = {
#include "8015f76c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F7A0Words[] = {
#include "8015f7a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F810Words[] = {
#include "8015f810_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F848Words[] = {
#include "8015f848_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015F948Words[] = {
#include "8015f948_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FA24Words[] = {
#include "8015fa24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FA44Words[] = {
#include "8015fa44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015FA78Words[] = {
#include "8015fa78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801600D0Words[] = {
#include "801600d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160104Words[] = {
#include "80160104_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160174Words[] = {
#include "80160174_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801601ACWords[] = {
#include "801601ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801601E4Words[] = {
#include "801601e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160244Words[] = {
#include "80160244_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160334Words[] = {
#include "80160334_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160368Words[] = {
#include "80160368_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801603D8Words[] = {
#include "801603d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801607B8Words[] = {
#include "801607b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801607E4Words[] = {
#include "801607e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160818Words[] = {
#include "80160818_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160888Words[] = {
#include "80160888_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801608C0Words[] = {
#include "801608c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160A28Words[] = {
#include "80160a28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160A74Words[] = {
#include "80160a74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160ACCWords[] = {
#include "80160acc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160B00Words[] = {
#include "80160b00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160B70Words[] = {
#include "80160b70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160BB4Words[] = {
#include "80160bb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160CB4Words[] = {
#include "80160cb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160DECWords[] = {
#include "80160dec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160E3CWords[] = {
#include "80160e3c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160E70Words[] = {
#include "80160e70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160EE0Words[] = {
#include "80160ee0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160F00Words[] = {
#include "80160f00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160F70Words[] = {
#include "80160f70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80160FE0Words[] = {
#include "80160fe0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161094Words[] = {
#include "80161094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161104Words[] = {
#include "80161104_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161124Words[] = {
#include "80161124_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161208Words[] = {
#include "80161208_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161240Words[] = {
#include "80161240_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161278Words[] = {
#include "80161278_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016130CWords[] = {
#include "8016130c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161418Words[] = {
#include "80161418_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161450Words[] = {
#include "80161450_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161488Words[] = {
#include "80161488_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801614E4Words[] = {
#include "801614e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016151CWords[] = {
#include "8016151c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161554Words[] = {
#include "80161554_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016158CWords[] = {
#include "8016158c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801615C4Words[] = {
#include "801615c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161888Words[] = {
#include "80161888_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016191CWords[] = {
#include "8016191c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801619D0Words[] = {
#include "801619d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161A00Words[] = {
#include "80161a00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161A30Words[] = {
#include "80161a30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161A60Words[] = {
#include "80161a60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161B84Words[] = {
#include "80161b84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161BE0Words[] = {
#include "80161be0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80161D58Words[] = {
#include "80161d58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162120Words[] = {
#include "80162120_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016236CWords[] = {
#include "8016236c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801623B8Words[] = {
#include "801623b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162414Words[] = {
#include "80162414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162714Words[] = {
#include "80162714_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162ACCWords[] = {
#include "80162acc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162AE0Words[] = {
#include "80162ae0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162CC4Words[] = {
#include "80162cc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162CCCWords[] = {
#include "80162ccc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162D28Words[] = {
#include "80162d28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162D88Words[] = {
#include "80162d88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162DE8Words[] = {
#include "80162de8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162E48Words[] = {
#include "80162e48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162EA8Words[] = {
#include "80162ea8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162F08Words[] = {
#include "80162f08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162F60Words[] = {
#include "80162f60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162F80Words[] = {
#include "80162f80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162FA0Words[] = {
#include "80162fa0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80162FC0Words[] = {
#include "80162fc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80163234Words[] = {
#include "80163234_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801632E0Words[] = {
#include "801632e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801632F0Words[] = {
#include "801632f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801633A8Words[] = {
#include "801633a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016345CWords[] = {
#include "8016345c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80163664Words[] = {
#include "80163664_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801636D0Words[] = {
#include "801636d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164270Words[] = {
#include "80164270_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801642ACWords[] = {
#include "801642ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164A74Words[] = {
#include "80164a74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164CD4Words[] = {
#include "80164cd4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164D4CWords[] = {
#include "80164d4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164DB0Words[] = {
#include "80164db0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80164DD0Words[] = {
#include "80164dd0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165024Words[] = {
#include "80165024_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165064Words[] = {
#include "80165064_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801650C4Words[] = {
#include "801650c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165124Words[] = {
#include "80165124_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165374Words[] = {
#include "80165374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801653B8Words[] = {
#include "801653b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801655E4Words[] = {
#include "801655e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165624Words[] = {
#include "80165624_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165694Words[] = {
#include "80165694_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165770Words[] = {
#include "80165770_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801657A0Words[] = {
#include "801657a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801657D8Words[] = {
#include "801657d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165840Words[] = {
#include "80165840_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165874Words[] = {
#include "80165874_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801658DCWords[] = {
#include "801658dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801658ECWords[] = {
#include "801658ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165900Words[] = {
#include "80165900_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165958Words[] = {
#include "80165958_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165978Words[] = {
#include "80165978_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165988Words[] = {
#include "80165988_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801659A8Words[] = {
#include "801659a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801659B8Words[] = {
#include "801659b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801659CCWords[] = {
#include "801659cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165A20Words[] = {
#include "80165a20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165A50Words[] = {
#include "80165a50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165A78Words[] = {
#include "80165a78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165B6CWords[] = {
#include "80165b6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165BB4Words[] = {
#include "80165bb4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165BFCWords[] = {
#include "80165bfc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165C58Words[] = {
#include "80165c58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165FA4Words[] = {
#include "80165fa4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801661CCWords[] = {
#include "801661cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80166244Words[] = {
#include "80166244_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016629CWords[] = {
#include "8016629c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801662F4Words[] = {
#include "801662f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016634CWords[] = {
#include "8016634c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801663A4Words[] = {
#include "801663a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801665B4Words[] = {
#include "801665b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016706CWords[] = {
#include "8016706c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016829CWords[] = {
#include "8016829c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168328Words[] = {
#include "80168328_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801683D8Words[] = {
#include "801683d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801684B4Words[] = {
#include "801684b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168540Words[] = {
#include "80168540_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801685ECWords[] = {
#include "801685ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168640Words[] = {
#include "80168640_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168664Words[] = {
#include "80168664_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168780Words[] = {
#include "80168780_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801687CCWords[] = {
#include "801687cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168A14Words[] = {
#include "80168a14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168A88Words[] = {
#include "80168a88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168AE4Words[] = {
#include "80168ae4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168B70Words[] = {
#include "80168b70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80168EC4Words[] = {
#include "80168ec4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801691B8Words[] = {
#include "801691b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016951CWords[] = {
#include "8016951c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801699D0Words[] = {
#include "801699d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169E44Words[] = {
#include "80169e44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80169FE0Words[] = {
#include "80169fe0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016A05CWords[] = {
#include "8016a05c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016A890Words[] = {
#include "8016a890_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B3F4Words[] = {
#include "8016b3f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B428Words[] = {
#include "8016b428_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B448Words[] = {
#include "8016b448_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B91CWords[] = {
#include "8016b91c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B964Words[] = {
#include "8016b964_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016B984Words[] = {
#include "8016b984_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BA48Words[] = {
#include "8016ba48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BA68Words[] = {
#include "8016ba68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BADCWords[] = {
#include "8016badc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BF34Words[] = {
#include "8016bf34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016BF50Words[] = {
#include "8016bf50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D464Words[] = {
#include "8016d464_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D5ECWords[] = {
#include "8016d5ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D64CWords[] = {
#include "8016d64c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016D984Words[] = {
#include "8016d984_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DA04Words[] = {
#include "8016da04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DB34Words[] = {
#include "8016db34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DBD8Words[] = {
#include "8016dbd8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016DEE0Words[] = {
#include "8016dee0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E1CCWords[] = {
#include "8016e1cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E26CWords[] = {
#include "8016e26c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E2E8Words[] = {
#include "8016e2e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E358Words[] = {
#include "8016e358_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E3CCWords[] = {
#include "8016e3cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E5F4Words[] = {
#include "8016e5f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E688Words[] = {
#include "8016e688_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E6E4Words[] = {
#include "8016e6e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E728Words[] = {
#include "8016e728_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E778Words[] = {
#include "8016e778_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016ED6CWords[] = {
#include "8016ed6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016ED8CWords[] = {
#include "8016ed8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EDBCWords[] = {
#include "8016edbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EDECWords[] = {
#include "8016edec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EFA8Words[] = {
#include "8016efa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F094Words[] = {
#include "8016f094_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F0ACWords[] = {
#include "8016f0ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F1ACWords[] = {
#include "8016f1ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F250Words[] = {
#include "8016f250_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F264Words[] = {
#include "8016f264_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F288Words[] = {
#include "8016f288_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F2A8Words[] = {
#include "8016f2a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F2C8Words[] = {
#include "8016f2c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F2ECWords[] = {
#include "8016f2ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F30CWords[] = {
#include "8016f30c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F330Words[] = {
#include "8016f330_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F350Words[] = {
#include "8016f350_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F374Words[] = {
#include "8016f374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F388Words[] = {
#include "8016f388_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F398Words[] = {
#include "8016f398_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F410Words[] = {
#include "8016f410_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F44CWords[] = {
#include "8016f44c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F470Words[] = {
#include "8016f470_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F494Words[] = {
#include "8016f494_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F4C4Words[] = {
#include "8016f4c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F4FCWords[] = {
#include "8016f4fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F540Words[] = {
#include "8016f540_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F578Words[] = {
#include "8016f578_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F5B0Words[] = {
#include "8016f5b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F5E0Words[] = {
#include "8016f5e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F610Words[] = {
#include "8016f610_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F648Words[] = {
#include "8016f648_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F680Words[] = {
#include "8016f680_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F6B0Words[] = {
#include "8016f6b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F71CWords[] = {
#include "8016f71c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F764Words[] = {
#include "8016f764_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F7D4Words[] = {
#include "8016f7d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F804Words[] = {
#include "8016f804_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F870Words[] = {
#include "8016f870_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F8ACWords[] = {
#include "8016f8ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016F920Words[] = {
#include "8016f920_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FA00Words[] = {
#include "8016fa00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FA44Words[] = {
#include "8016fa44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FAC0Words[] = {
#include "8016fac0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FB10Words[] = {
#include "8016fb10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FB50Words[] = {
#include "8016fb50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FBB8Words[] = {
#include "8016fbb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FC24Words[] = {
#include "8016fc24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FC64Words[] = {
#include "8016fc64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FCCCWords[] = {
#include "8016fccc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FD7CWords[] = {
#include "8016fd7c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FDF0Words[] = {
#include "8016fdf0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FE2CWords[] = {
#include "8016fe2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FED0Words[] = {
#include "8016fed0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FF6CWords[] = {
#include "8016ff6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016FFA8Words[] = {
#include "8016ffa8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170018Words[] = {
#include "80170018_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170068Words[] = {
#include "80170068_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801700B8Words[] = {
#include "801700b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170100Words[] = {
#include "80170100_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017018CWords[] = {
#include "8017018c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801701C8Words[] = {
#include "801701c8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017027CWords[] = {
#include "8017027c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801702B8Words[] = {
#include "801702b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170338Words[] = {
#include "80170338_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170374Words[] = {
#include "80170374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017041CWords[] = {
#include "8017041c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017044CWords[] = {
#include "8017044c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801704ECWords[] = {
#include "801704ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017051CWords[] = {
#include "8017051c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170584Words[] = {
#include "80170584_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801705C0Words[] = {
#include "801705c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170634Words[] = {
#include "80170634_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170670Words[] = {
#include "80170670_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801706E8Words[] = {
#include "801706e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170718Words[] = {
#include "80170718_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170784Words[] = {
#include "80170784_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801707D4Words[] = {
#include "801707d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017084CWords[] = {
#include "8017084c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801708B0Words[] = {
#include "801708b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170928Words[] = {
#include "80170928_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170970Words[] = {
#include "80170970_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801709B8Words[] = {
#include "801709b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170A00Words[] = {
#include "80170a00_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170A48Words[] = {
#include "80170a48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170A90Words[] = {
#include "80170a90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170B14Words[] = {
#include "80170b14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170B48Words[] = {
#include "80170b48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170B90Words[] = {
#include "80170b90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170C14Words[] = {
#include "80170c14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170C44Words[] = {
#include "80170c44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170CB0Words[] = {
#include "80170cb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170DA4Words[] = {
#include "80170da4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170DE0Words[] = {
#include "80170de0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170E70Words[] = {
#include "80170e70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170EACWords[] = {
#include "80170eac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170F38Words[] = {
#include "80170f38_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170F74Words[] = {
#include "80170f74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80170FECWords[] = {
#include "80170fec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171028Words[] = {
#include "80171028_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801710A0Words[] = {
#include "801710a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801710DCWords[] = {
#include "801710dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017115CWords[] = {
#include "8017115c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017118CWords[] = {
#include "8017118c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801711FCWords[] = {
#include "801711fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171238Words[] = {
#include "80171238_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017162CWords[] = {
#include "8017162c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801717F4Words[] = {
#include "801717f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171824Words[] = {
#include "80171824_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171854Words[] = {
#include "80171854_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171884Words[] = {
#include "80171884_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801718ACWords[] = {
#include "801718ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171904Words[] = {
#include "80171904_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171928Words[] = {
#include "80171928_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017196CWords[] = {
#include "8017196c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017197CWords[] = {
#include "8017197c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171990Words[] = {
#include "80171990_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A04Words[] = {
#include "80171a04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A10Words[] = {
#include "80171a10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A1CWords[] = {
#include "80171a1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A34Words[] = {
#include "80171a34_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A44Words[] = {
#include "80171a44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A58Words[] = {
#include "80171a58_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171A6CWords[] = {
#include "80171a6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171B10Words[] = {
#include "80171b10_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171B44Words[] = {
#include "80171b44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171C64Words[] = {
#include "80171c64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171CC4Words[] = {
#include "80171cc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80171D1CWords[] = {
#include "80171d1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801722CCWords[] = {
#include "801722cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172310Words[] = {
#include "80172310_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172358Words[] = {
#include "80172358_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801723C4Words[] = {
#include "801723c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172414Words[] = {
#include "80172414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017248CWords[] = {
#include "8017248c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801724ECWords[] = {
#include "801724ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017250CWords[] = {
#include "8017250c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172560Words[] = {
#include "80172560_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172588Words[] = {
#include "80172588_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172590Words[] = {
#include "80172590_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801725A4Words[] = {
#include "801725a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801725B8Words[] = {
#include "801725b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801725CCWords[] = {
#include "801725cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801725E0Words[] = {
#include "801725e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801725F4Words[] = {
#include "801725f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172608Words[] = {
#include "80172608_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017261CWords[] = {
#include "8017261c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172630Words[] = {
#include "80172630_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172644Words[] = {
#include "80172644_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172658Words[] = {
#include "80172658_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172664Words[] = {
#include "80172664_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172670Words[] = {
#include "80172670_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017267CWords[] = {
#include "8017267c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172688Words[] = {
#include "80172688_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172694Words[] = {
#include "80172694_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801726A0Words[] = {
#include "801726a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801726ACWords[] = {
#include "801726ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801726B8Words[] = {
#include "801726b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801726C4Words[] = {
#include "801726c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172710Words[] = {
#include "80172710_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172738Words[] = {
#include "80172738_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172760Words[] = {
#include "80172760_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172780Words[] = {
#include "80172780_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017280CWords[] = {
#include "8017280c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172844Words[] = {
#include "80172844_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172894Words[] = {
#include "80172894_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172920Words[] = {
#include "80172920_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172958Words[] = {
#include "80172958_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801729B0Words[] = {
#include "801729b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172A2CWords[] = {
#include "80172a2c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172A8CWords[] = {
#include "80172a8c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172ACCWords[] = {
#include "80172acc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172B14Words[] = {
#include "80172b14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172B80Words[] = {
#include "80172b80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172BC8Words[] = {
#include "80172bc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172C50Words[] = {
#include "80172c50_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172CDCWords[] = {
#include "80172cdc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172D14Words[] = {
#include "80172d14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172D68Words[] = {
#include "80172d68_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172DE8Words[] = {
#include "80172de8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172E20Words[] = {
#include "80172e20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172E94Words[] = {
#include "80172e94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172ED4Words[] = {
#include "80172ed4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172EFCWords[] = {
#include "80172efc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172F24Words[] = {
#include "80172f24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172F4CWords[] = {
#include "80172f4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172F9CWords[] = {
#include "80172f9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80172FECWords[] = {
#include "80172fec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017303CWords[] = {
#include "8017303c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801730B4Words[] = {
#include "801730b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801730FCWords[] = {
#include "801730fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173174Words[] = {
#include "80173174_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801731D8Words[] = {
#include "801731d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017329CWords[] = {
#include "8017329c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801732C4Words[] = {
#include "801732c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801732F4Words[] = {
#include "801732f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017331CWords[] = {
#include "8017331c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017334CWords[] = {
#include "8017334c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173374Words[] = {
#include "80173374_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801733A4Words[] = {
#include "801733a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801733CCWords[] = {
#include "801733cc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801733FCWords[] = {
#include "801733fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173460Words[] = {
#include "80173460_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173580Words[] = {
#include "80173580_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801735B8Words[] = {
#include "801735b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801735ECWords[] = {
#include "801735ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801736B0Words[] = {
#include "801736b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173738Words[] = {
#include "80173738_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173770Words[] = {
#include "80173770_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801737B8Words[] = {
#include "801737b8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173824Words[] = {
#include "80173824_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801738DCWords[] = {
#include "801738dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173948Words[] = {
#include "80173948_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173980Words[] = {
#include "80173980_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801739D8Words[] = {
#include "801739d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173A28Words[] = {
#include "80173a28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173B88Words[] = {
#include "80173b88_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173BC0Words[] = {
#include "80173bc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80173C64Words[] = {
#include "80173c64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174158Words[] = {
#include "80174158_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174188Words[] = {
#include "80174188_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801741A8Words[] = {
#include "801741a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801741ECWords[] = {
#include "801741ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017427CWords[] = {
#include "8017427c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801742E0Words[] = {
#include "801742e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174318Words[] = {
#include "80174318_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017435CWords[] = {
#include "8017435c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801743C0Words[] = {
#include "801743c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801743F0Words[] = {
#include "801743f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174438Words[] = {
#include "80174438_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801744B0Words[] = {
#include "801744b0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801744E0Words[] = {
#include "801744e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017452CWords[] = {
#include "8017452c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174554Words[] = {
#include "80174554_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174584Words[] = {
#include "80174584_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801745ACWords[] = {
#include "801745ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801745DCWords[] = {
#include "801745dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174604Words[] = {
#include "80174604_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174630Words[] = {
#include "80174630_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174674Words[] = {
#include "80174674_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174684Words[] = {
#include "80174684_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801746A4Words[] = {
#include "801746a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801746DCWords[] = {
#include "801746dc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174714Words[] = {
#include "80174714_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174754Words[] = {
#include "80174754_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174764Words[] = {
#include "80174764_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174774Words[] = {
#include "80174774_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174784Words[] = {
#include "80174784_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801747ACWords[] = {
#include "801747ac_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174808Words[] = {
#include "80174808_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017481CWords[] = {
#include "8017481c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174824Words[] = {
#include "80174824_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017484CWords[] = {
#include "8017484c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801748C4Words[] = {
#include "801748c4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801748E4Words[] = {
#include "801748e4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801748ECWords[] = {
#include "801748ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801749A8Words[] = {
#include "801749a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174B6CWords[] = {
#include "80174b6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174BBCWords[] = {
#include "80174bbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174C60Words[] = {
#include "80174c60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174C80Words[] = {
#include "80174c80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174E9CWords[] = {
#include "80174e9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174ED4Words[] = {
#include "80174ed4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174EF0Words[] = {
#include "80174ef0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174F64Words[] = {
#include "80174f64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174FBCWords[] = {
#include "80174fbc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175014Words[] = {
#include "80175014_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017509CWords[] = {
#include "8017509c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175114Words[] = {
#include "80175114_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175150Words[] = {
#include "80175150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801751D8Words[] = {
#include "801751d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801752BCWords[] = {
#include "801752bc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175414Words[] = {
#include "80175414_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175454Words[] = {
#include "80175454_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175624Words[] = {
#include "80175624_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80175668Words[] = {
#include "80175668_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801757E0Words[] = {
#include "801757e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801787D4Words[] = {
#include "801787d4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178BB8Words[] = {
#include "80178bb8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179B28Words[] = {
#include "80179b28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179D30Words[] = {
#include "80179d30_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179D78Words[] = {
#include "80179d78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179DCCWords[] = {
#include "80179dcc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179DF8Words[] = {
#include "80179df8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179E1CWords[] = {
#include "80179e1c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179E48Words[] = {
#include "80179e48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179E74Words[] = {
#include "80179e74_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179EA0Words[] = {
#include "80179ea0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179EE8Words[] = {
#include "80179ee8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179F14Words[] = {
#include "80179f14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179F44Words[] = {
#include "80179f44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179F6CWords[] = {
#include "80179f6c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179F98Words[] = {
#include "80179f98_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80179FECWords[] = {
#include "80179fec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A040Words[] = {
#include "8017a040_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A0F4Words[] = {
#include "8017a0f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A11CWords[] = {
#include "8017a11c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A180Words[] = {
#include "8017a180_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A1A8Words[] = {
#include "8017a1a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A1D0Words[] = {
#include "8017a1d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A1F8Words[] = {
#include "8017a1f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A220Words[] = {
#include "8017a220_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A248Words[] = {
#include "8017a248_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A270Words[] = {
#include "8017a270_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A298Words[] = {
#include "8017a298_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A2C0Words[] = {
#include "8017a2c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A2E8Words[] = {
#include "8017a2e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A310Words[] = {
#include "8017a310_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A338Words[] = {
#include "8017a338_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A360Words[] = {
#include "8017a360_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017A388Words[] = {
#include "8017a388_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017ADE8Words[] = {
#include "8017ade8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017AE08Words[] = {
#include "8017ae08_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EE40Words[] = {
#include "8016ee40_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EF78Words[] = {
#include "8016ef78_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EFC8Words[] = {
#include "8016efc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801726D0Words[] = {
#include "801726d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80174650Words[] = {
#include "80174650_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_801816C0Words[] = {
#include "801816c0_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8017F53CWords[] = {
#include "8017f53c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F590Words[] = {
#include "8017f590_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8017F5B4Words[] = {
#include "8017f5b4_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_80181A44Words[] = {
#include "80181a44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80181AE0Words[] = {
#include "80181ae0_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_801320D0Words[] = {
#include "801320d0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80134510Words[] = {
#include "80134510_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801345F8Words[] = {
#include "801345f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801347A0Words[] = {
#include "801347a0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80135480Words[] = {
#include "80135480_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80135D20Words[] = {
#include "80135d20_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80135EB0Words[] = {
#include "80135eb0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80136A94Words[] = {
#include "80136a94_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8013E448Words[] = {
#include "8013e448_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80142EC0Words[] = {
#include "80142ec0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014305CWords[] = {
#include "8014305c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80165E90Words[] = {
#include "80165e90_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016EE94Words[] = {
#include "8016ee94_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8017869CWords[] = {
#include "8017869c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178B18Words[] = {
#include "80178b18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178BF8Words[] = {
#include "80178bf8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80178D40Words[] = {
#include "80178d40_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_801754A8Words[] = {
#include "801754a8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E8F0Words[] = {
#include "8016e8f0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8016E95CWords[] = {
#include "8016e95c_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8013B598Words[] = {
#include "8013b598_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8012956CWords[] = {
#include "8012956c_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8014E934Words[] = {
#include "8014e934_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014E98CWords[] = {
#include "8014e98c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014EA4CWords[] = {
#include "8014ea4c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ED28Words[] = {
#include "8014ed28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014ED80Words[] = {
#include "8014ed80_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014EE14Words[] = {
#include "8014ee14_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F1F4Words[] = {
#include "8014f1f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F24CWords[] = {
#include "8014f24c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F2E0Words[] = {
#include "8014f2e0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F3E8Words[] = {
#include "8014f3e8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F468Words[] = {
#include "8014f468_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F4C0Words[] = {
#include "8014f4c0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F6F4Words[] = {
#include "8014f6f4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014F74CWords[] = {
#include "8014f74c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FA04Words[] = {
#include "8014fa04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FA70Words[] = {
#include "8014fa70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FBC0Words[] = {
#include "8014fbc0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FC18Words[] = {
#include "8014fc18_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FCFCWords[] = {
#include "8014fcfc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FD54Words[] = {
#include "8014fd54_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FDF4Words[] = {
#include "8014fdf4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FE60Words[] = {
#include "8014fe60_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8014FFDCWords[] = {
#include "8014ffdc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150150Words[] = {
#include "80150150_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150170Words[] = {
#include "80150170_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801502ECWords[] = {
#include "801502ec_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150460Words[] = {
#include "80150460_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150480Words[] = {
#include "80150480_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801504D8Words[] = {
#include "801504d8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150528Words[] = {
#include "80150528_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801505FCWords[] = {
#include "801505fc_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801506A4Words[] = {
#include "801506a4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150820Words[] = {
#include "80150820_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015086CWords[] = {
#include "8015086c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801508B4Words[] = {
#include "801508b4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_801508F8Words[] = {
#include "801508f8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_8015094CWords[] = {
#include "8015094c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150A70Words[] = {
#include "80150a70_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150B28Words[] = {
#include "80150b28_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150B9CWords[] = {
#include "80150b9c_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150BA4Words[] = {
#include "80150ba4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150BC8Words[] = {
#include "80150bc8_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150C48Words[] = {
#include "80150c48_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150CA0Words[] = {
#include "80150ca0_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150CC4Words[] = {
#include "80150cc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150CE4Words[] = {
#include "80150ce4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150D04Words[] = {
#include "80150d04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150D24Words[] = {
#include "80150d24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150D44Words[] = {
#include "80150d44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150D64Words[] = {
#include "80150d64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150D84Words[] = {
#include "80150d84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150DA4Words[] = {
#include "80150da4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150DC4Words[] = {
#include "80150dc4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150DE4Words[] = {
#include "80150de4_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150E04Words[] = {
#include "80150e04_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150E24Words[] = {
#include "80150e24_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150E44Words[] = {
#include "80150e44_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150E64Words[] = {
#include "80150e64_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150E84Words[] = {
#include "80150e84_sc02_0031_words.inc"
};
static const uint32_t kOverlaySc02_80150EA4Words[] = {
#include "80150ea4_sc02_0031_words.inc"
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
static const uint32_t kOverlaySc02_8017C180Words[] = {
#include "8017c180_sc02_0031_words.inc"
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
static const uint32_t kMain8005B400Words[] = {
#include "8005b400_words.inc"
};
static const uint32_t kMain80010C7CWords[] = {
#include "80010c7c_words.inc"
};
static const uint32_t kMain8001513CWords[] = {
#include "8001513c_words.inc"
};
static const uint32_t kMain80015144Words[] = {
#include "80015144_words.inc"
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
static const uint32_t kMain80059B44Words[] = {
#include "80059b44_words.inc"
};
static const uint32_t kMain80019018Words[] = {
#include "80019018_words.inc"
};
static const uint32_t kMain80019028Words[] = {
#include "80019028_words.inc"
};
static const uint32_t kMain8001903CWords[] = {
#include "8001903c_words.inc"
};
static const uint32_t kMain80019064Words[] = {
#include "80019064_words.inc"
};
static const uint32_t kMain800190ACWords[] = {
#include "800190ac_words.inc"
};
static const uint32_t kMain80019198Words[] = {
#include "80019198_words.inc"
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
static const uint32_t kMain8002AC98Words[] = {
#include "8002ac98_words.inc"
};
static const uint32_t kMain8002AE60Words[] = {
#include "8002ae60_words.inc"
};
static const uint32_t kMain8002AED0Words[] = {
#include "8002aed0_words.inc"
};
static const uint32_t kMain8002AEE4Words[] = {
#include "8002aee4_words.inc"
};
static const uint32_t kMain80015978Words[] = {
#include "80015978_words.inc"
};
static const uint32_t kMain8001599CWords[] = {
#include "8001599c_words.inc"
};
static const uint32_t kMain800159C0Words[] = {
#include "800159c0_words.inc"
};
static const uint32_t kMain800159E4Words[] = {
#include "800159e4_words.inc"
};
static const uint32_t kMain80015A08Words[] = {
#include "80015a08_words.inc"
};
static const uint32_t kMain80015A2CWords[] = {
#include "80015a2c_words.inc"
};
static const uint32_t kMain80015A50Words[] = {
#include "80015a50_words.inc"
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
static const uint32_t kMain80012DBCWords[] = {
#include "80012dbc_words.inc"
};
static const uint32_t kMain80012E0CWords[] = {
#include "80012e0c_words.inc"
};
static const uint32_t kMain80012E6CWords[] = {
#include "80012e6c_words.inc"
};
static const uint32_t kMain80012F74Words[] = {
#include "80012f74_words.inc"
};
static const uint32_t kMain80012FC8Words[] = {
#include "80012fc8_words.inc"
};
static const uint32_t kMain80013028Words[] = {
#include "80013028_words.inc"
};
static const uint32_t kMain800130D0Words[] = {
#include "800130d0_words.inc"
};
static const uint32_t kMain8001311CWords[] = {
#include "8001311c_words.inc"
};
static const uint32_t kMain80013154Words[] = {
#include "80013154_words.inc"
};
static const uint32_t kMain80013200Words[] = {
#include "80013200_words.inc"
};
static const uint32_t kMain80013228Words[] = {
#include "80013228_words.inc"
};
static const uint32_t kMain80013294Words[] = {
#include "80013294_words.inc"
};
static const uint32_t kMain800132BCWords[] = {
#include "800132bc_words.inc"
};
static const uint32_t kMain80013328Words[] = {
#include "80013328_words.inc"
};
static const uint32_t kMain80013350Words[] = {
#include "80013350_words.inc"
};
static const uint32_t kMain800133BCWords[] = {
#include "800133bc_words.inc"
};
static const uint32_t kMain800133E4Words[] = {
#include "800133e4_words.inc"
};
static const uint32_t kMain80013450Words[] = {
#include "80013450_words.inc"
};
static const uint32_t kMain80013478Words[] = {
#include "80013478_words.inc"
};
static const uint32_t kMain800134FCWords[] = {
#include "800134fc_words.inc"
};
static const uint32_t kMain80013694Words[] = {
#include "80013694_words.inc"
};
static const uint32_t kMain8001382CWords[] = {
#include "8001382c_words.inc"
};
static const uint32_t kMain800139C8Words[] = {
#include "800139c8_words.inc"
};
static const uint32_t kMain80013B64Words[] = {
#include "80013b64_words.inc"
};
static const uint32_t kMain80013CFCWords[] = {
#include "80013cfc_words.inc"
};
static const uint32_t kMain80013E94Words[] = {
#include "80013e94_words.inc"
};
static const uint32_t kMain80049CACWords[] = {
#include "80049cac_words.inc"
};
static const uint32_t kMain80049F3CWords[] = {
#include "80049f3c_words.inc"
};
static const uint32_t kMain8004A0DCWords[] = {
#include "8004a0dc_words.inc"
};
static const uint32_t kMain8004A27CWords[] = {
#include "8004a27c_words.inc"
};
static const uint32_t kMain8004A41CWords[] = {
#include "8004a41c_words.inc"
};
static const uint32_t kMain8004A53CWords[] = {
#include "8004a53c_words.inc"
};
static const uint32_t kMain8004A660Words[] = {
#include "8004a660_words.inc"
};
static const uint32_t kMain8004A794Words[] = {
#include "8004a794_words.inc"
};
static const uint32_t kMain8004A8CCWords[] = {
#include "8004a8cc_words.inc"
};
static const uint32_t kMain8004AA18Words[] = {
#include "8004aa18_words.inc"
};
static const uint32_t kMain8004AB68Words[] = {
#include "8004ab68_words.inc"
};
static const uint32_t kMain8004ACCCWords[] = {
#include "8004accc_words.inc"
};
static const uint32_t kMain8004AE3CWords[] = {
#include "8004ae3c_words.inc"
};
static const uint32_t kMain8004AF5CWords[] = {
#include "8004af5c_words.inc"
};
static const uint32_t kMain8004B078Words[] = {
#include "8004b078_words.inc"
};
static const uint32_t kMain8004B1F8Words[] = {
#include "8004b1f8_words.inc"
};
static const uint32_t kMain8004B37CWords[] = {
#include "8004b37c_words.inc"
};
static const uint32_t kMain8004B4C8Words[] = {
#include "8004b4c8_words.inc"
};
static const uint32_t kMain8004B614Words[] = {
#include "8004b614_words.inc"
};
static const uint32_t kMain8004B7E0Words[] = {
#include "8004b7e0_words.inc"
};
static const uint32_t kMain8004B9ACWords[] = {
#include "8004b9ac_words.inc"
};
static const uint32_t kMain8004BACCWords[] = {
#include "8004bacc_words.inc"
};
static const uint32_t kMain8004BBF0Words[] = {
#include "8004bbf0_words.inc"
};
static const uint32_t kMain8004BD38Words[] = {
#include "8004bd38_words.inc"
};
static const uint32_t kMain8004BE8CWords[] = {
#include "8004be8c_words.inc"
};
static const uint32_t kMain8004BFD8Words[] = {
#include "8004bfd8_words.inc"
};
static const uint32_t kMain8004C128Words[] = {
#include "8004c128_words.inc"
};
static const uint32_t kMain8004C2A0Words[] = {
#include "8004c2a0_words.inc"
};
static const uint32_t kMain8004C41CWords[] = {
#include "8004c41c_words.inc"
};
static const uint32_t kMain8004C53CWords[] = {
#include "8004c53c_words.inc"
};
static const uint32_t kMain8004C658Words[] = {
#include "8004c658_words.inc"
};
static const uint32_t kMain8004C7ECWords[] = {
#include "8004c7ec_words.inc"
};
static const uint32_t kMain8004C98CWords[] = {
#include "8004c98c_words.inc"
};
static const uint32_t kMain8004CAD8Words[] = {
#include "8004cad8_words.inc"
};
static const uint32_t kMain8004CC24Words[] = {
#include "8004cc24_words.inc"
};
static const uint32_t kMain8004CE04Words[] = {
#include "8004ce04_words.inc"
};
static const uint32_t kMain8004914CWords[] = {
#include "8004914c_words.inc"
};
static const uint32_t kMain8004917CWords[] = {
#include "8004917c_words.inc"
};
static const uint32_t kMain800491ACWords[] = {
#include "800491ac_words.inc"
};
static const uint32_t kMain800491CCWords[] = {
#include "800491cc_words.inc"
};
static const uint32_t kMain800491ECWords[] = {
#include "800491ec_words.inc"
};
static const uint32_t kMain8004945CWords[] = {
#include "8004945c_words.inc"
};
static const uint32_t kMain8004948CWords[] = {
#include "8004948c_words.inc"
};
static const uint32_t kMain800494C4Words[] = {
#include "800494c4_words.inc"
};
static const uint32_t kMain800494FCWords[] = {
#include "800494fc_words.inc"
};
static const uint32_t kMain8004952CWords[] = {
#include "8004952c_words.inc"
};
static const uint32_t kMain8004955CWords[] = {
#include "8004955c_words.inc"
};
static const uint32_t kMain8004958CWords[] = {
#include "8004958c_words.inc"
};
static const uint32_t kMain800495ECWords[] = {
#include "800495ec_words.inc"
};
static const uint32_t kMain80011E84Words[] = {
#include "80011e84_words.inc"
};
static const uint32_t kMain80011EB4Words[] = {
#include "80011eb4_words.inc"
};
static const uint32_t kMain800120C4Words[] = {
#include "800120c4_words.inc"
};
static const uint32_t kMain8005A600Words[] = {
#include "8005a600_words.inc"
};
static const uint32_t kMain8005A658Words[] = {
#include "8005a658_words.inc"
};
static const uint32_t kMain80024054Words[] = {
#include "80024054_words.inc"
};
static const uint32_t kMain800241C0Words[] = {
#include "800241c0_words.inc"
};
static const uint32_t kMain800242D0Words[] = {
#include "800242d0_words.inc"
};
static const uint32_t kMain800243ECWords[] = {
#include "800243ec_words.inc"
};
static const uint32_t kMain80024448Words[] = {
#include "80024448_words.inc"
};
static const uint32_t kMain800249F0Words[] = {
#include "800249f0_words.inc"
};
static const uint32_t kMain80024BC0Words[] = {
#include "80024bc0_words.inc"
};
static const uint32_t kMain80024DE8Words[] = {
#include "80024de8_words.inc"
};
static const uint32_t kMain80025000Words[] = {
#include "80025000_words.inc"
};
static const uint32_t kMain8002528CWords[] = {
#include "8002528c_words.inc"
};
static const uint32_t kMain80025504Words[] = {
#include "80025504_words.inc"
};
static const uint32_t kMain80025818Words[] = {
#include "80025818_words.inc"
};
static const uint32_t kMain80025A30Words[] = {
#include "80025a30_words.inc"
};
static const uint32_t kMain80025CBCWords[] = {
#include "80025cbc_words.inc"
};
static const uint32_t kMain80025EB8Words[] = {
#include "80025eb8_words.inc"
};
static const uint32_t kMain80026128Words[] = {
#include "80026128_words.inc"
};
static const uint32_t kMain800262D8Words[] = {
#include "800262d8_words.inc"
};
static const uint32_t kMain80026514Words[] = {
#include "80026514_words.inc"
};
static const uint32_t kMain800268D0Words[] = {
#include "800268d0_words.inc"
};
static const uint32_t kMain80026D64Words[] = {
#include "80026d64_words.inc"
};
static const uint32_t kMain80027058Words[] = {
#include "80027058_words.inc"
};
static const uint32_t kMain80027200Words[] = {
#include "80027200_words.inc"
};
static const uint32_t kMain800273F4Words[] = {
#include "800273f4_words.inc"
};
static const uint32_t kMain800275BCWords[] = {
#include "800275bc_words.inc"
};
static const uint32_t kMain800277DCWords[] = {
#include "800277dc_words.inc"
};
static const uint32_t kMain800279ACWords[] = {
#include "800279ac_words.inc"
};
static const uint32_t kMain80027BF0Words[] = {
#include "80027bf0_words.inc"
};
static const uint32_t kMain80027C10Words[] = {
#include "80027c10_words.inc"
};
static const uint32_t kMain80027D20Words[] = {
#include "80027d20_words.inc"
};
static const uint32_t kMain80027F4CWords[] = {
#include "80027f4c_words.inc"
};
static const uint32_t kMain80028200Words[] = {
#include "80028200_words.inc"
};
static const uint32_t kMain80028234Words[] = {
#include "80028234_words.inc"
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
static const uint32_t kMain8002374CWords[] = {
#include "8002374c_words.inc"
};
static const uint32_t kMain80023BF0Words[] = {
#include "80023bf0_words.inc"
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
static const uint32_t kMain8001D16CWords[] = {
#include "8001d16c_words.inc"
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
static const uint32_t kMain8001FC08Words[] = {
#include "8001fc08_words.inc"
};
static const uint32_t kMain80020248Words[] = {
#include "80020248_words.inc"
};
static const uint32_t kMain80020598Words[] = {
#include "80020598_words.inc"
};
static const uint32_t kMain80020A28Words[] = {
#include "80020a28_words.inc"
};
static const uint32_t kMain80020DA4Words[] = {
#include "80020da4_words.inc"
};
static const uint32_t kMain80020F34Words[] = {
#include "80020f34_words.inc"
};
static const uint32_t kMain80021008Words[] = {
#include "80021008_words.inc"
};
static const uint32_t kMain80021050Words[] = {
#include "80021050_words.inc"
};
static const uint32_t kMain8002109CWords[] = {
#include "8002109c_words.inc"
};
static const uint32_t kMain80021120Words[] = {
#include "80021120_words.inc"
};
static const uint32_t kMain80021174Words[] = {
#include "80021174_words.inc"
};
static const uint32_t kMain80021284Words[] = {
#include "80021284_words.inc"
};
static const uint32_t kMain800215F4Words[] = {
#include "800215f4_words.inc"
};
static const uint32_t kMain80021D38Words[] = {
#include "80021d38_words.inc"
};
static const uint32_t kMain800221A8Words[] = {
#include "800221a8_words.inc"
};
static const uint32_t kMain800226C0Words[] = {
#include "800226c0_words.inc"
};
static const uint32_t kMain80023138Words[] = {
#include "80023138_words.inc"
};
static const uint32_t kMain8001D388Words[] = {
#include "8001d388_words.inc"
};
static const uint32_t kMain8001D3FCWords[] = {
#include "8001d3fc_words.inc"
};
static const uint32_t kMain8001D70CWords[] = {
#include "8001d70c_words.inc"
};
static const uint32_t kMain8001D8C4Words[] = {
#include "8001d8c4_words.inc"
};
static const uint32_t kMain8001DA34Words[] = {
#include "8001da34_words.inc"
};
static const uint32_t kMain8001E094Words[] = {
#include "8001e094_words.inc"
};
static const uint32_t kMain8001E378Words[] = {
#include "8001e378_words.inc"
};
static const uint32_t kMain8001E668Words[] = {
#include "8001e668_words.inc"
};
static const uint32_t kMain8001E7E0Words[] = {
#include "8001e7e0_words.inc"
};
static const uint32_t kMain8001EA14Words[] = {
#include "8001ea14_words.inc"
};
static const uint32_t kMain8001EFE0Words[] = {
#include "8001efe0_words.inc"
};
static const uint32_t kMain8001F730Words[] = {
#include "8001f730_words.inc"
};
static const uint32_t kMain8001F974Words[] = {
#include "8001f974_words.inc"
};
static const uint32_t kMain8001F97CWords[] = {
#include "8001f97c_words.inc"
};
static const uint32_t kMain80015908Words[] = {
#include "80015908_words.inc"
};
static const uint32_t kMain80015954Words[] = {
#include "80015954_words.inc"
};
static const uint32_t kMain80015A74Words[] = {
#include "80015a74_words.inc"
};
static const uint32_t kMain80015AD0Words[] = {
#include "80015ad0_words.inc"
};
static const uint32_t kMain80015B6CWords[] = {
#include "80015b6c_words.inc"
};
static const uint32_t kMain80015D4CWords[] = {
#include "80015d4c_words.inc"
};
static const uint32_t kMain80015F04Words[] = {
#include "80015f04_words.inc"
};
static const uint32_t kMain80016110Words[] = {
#include "80016110_words.inc"
};
static const uint32_t kMain8005B75CWords[] = {
#include "8005b75c_words.inc"
};
static const uint32_t kMain80058B7CWords[] = {
#include "80058b7c_words.inc"
};
static const uint32_t kMain80058C6CWords[] = {
#include "80058c6c_words.inc"
};
static const uint32_t kMain80058CA8Words[] = {
#include "80058ca8_words.inc"
};
static const uint32_t kMain8005E8E8Words[] = {
#include "8005e8e8_words.inc"
};
static const uint32_t kMain8004974CWords[] = {
#include "8004974c_words.inc"
};
static const uint32_t kMain8004978CWords[] = {
#include "8004978c_words.inc"
};
static const uint32_t kMain80049A18Words[] = {
#include "80049a18_words.inc"
};
static const uint32_t kMain80052FCCWords[] = {
#include "80052fcc_words.inc"
};
static const uint32_t kMain80054514Words[] = {
#include "80054514_words.inc"
};
static const uint32_t kMain800547D8Words[] = {
#include "800547d8_words.inc"
};
static const uint32_t kMain80054AACWords[] = {
#include "80054aac_words.inc"
};
static const uint32_t kMain80054DCCWords[] = {
#include "80054dcc_words.inc"
};
static const uint32_t kMain80048EACWords[] = {
#include "80048eac_words.inc"
};
static const uint32_t kMain80048FB8Words[] = {
#include "80048fb8_words.inc"
};
static const uint32_t kMain8004901CWords[] = {
#include "8004901c_words.inc"
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
static const uint32_t kMain8005C1C0Words[] = {
#include "8005c1c0_words.inc"
};
static const uint32_t kMain8005C29CWords[] = {
#include "8005c29c_words.inc"
};
static const uint32_t kMain8005C2C8Words[] = {
#include "8005c2c8_words.inc"
};
static const uint32_t kMain8005C2F8Words[] = {
#include "8005c2f8_words.inc"
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
static const uint32_t kMain800296F8Words[] = {
#include "800296f8_words.inc"
};
static const uint32_t kMain80029774Words[] = {
#include "80029774_words.inc"
};
static const uint32_t kMain800298BCWords[] = {
#include "800298bc_words.inc"
};
static const uint32_t kMain8002992CWords[] = {
#include "8002992c_words.inc"
};
static const uint32_t kMain80029A58Words[] = {
#include "80029a58_words.inc"
};
static const uint32_t kMain80029A94Words[] = {
#include "80029a94_words.inc"
};
static const uint32_t kMain80029AACWords[] = {
#include "80029aac_words.inc"
};
static const uint32_t kMain80029AF4Words[] = {
#include "80029af4_words.inc"
};
static const uint32_t kMain80029B4CWords[] = {
#include "80029b4c_words.inc"
};
static const uint32_t kMain80029BC8Words[] = {
#include "80029bc8_words.inc"
};
static const uint32_t kMain80029C44Words[] = {
#include "80029c44_words.inc"
};
static const uint32_t kMain80029CD4Words[] = {
#include "80029cd4_words.inc"
};
static const uint32_t kMain80029D3CWords[] = {
#include "80029d3c_words.inc"
};
static const uint32_t kMain80029DB4Words[] = {
#include "80029db4_words.inc"
};
static const uint32_t kMain80029E30Words[] = {
#include "80029e30_words.inc"
};
static const uint32_t kMain80029E94Words[] = {
#include "80029e94_words.inc"
};
static const uint32_t kMain80029EC0Words[] = {
#include "80029ec0_words.inc"
};
static const uint32_t kMain80029ED4Words[] = {
#include "80029ed4_words.inc"
};
static const uint32_t kMain80029FD4Words[] = {
#include "80029fd4_words.inc"
};
static const uint32_t kMain80029FE4Words[] = {
#include "80029fe4_words.inc"
};
static const uint32_t kMain8002A04CWords[] = {
#include "8002a04c_words.inc"
};
static const uint32_t kMain8002A088Words[] = {
#include "8002a088_words.inc"
};
static const uint32_t kMain8002A108Words[] = {
#include "8002a108_words.inc"
};
static const uint32_t kMain8002A1B4Words[] = {
#include "8002a1b4_words.inc"
};
static const uint32_t kMain8002A200Words[] = {
#include "8002a200_words.inc"
};
static const uint32_t kMain8002A234Words[] = {
#include "8002a234_words.inc"
};
static const uint32_t kMain8002A26CWords[] = {
#include "8002a26c_words.inc"
};
static const uint32_t kMain8002A27CWords[] = {
#include "8002a27c_words.inc"
};
static const uint32_t kMain8002A28CWords[] = {
#include "8002a28c_words.inc"
};
static const uint32_t kMain8002A2B0Words[] = {
#include "8002a2b0_words.inc"
};
static const uint32_t kMain8002A2D4Words[] = {
#include "8002a2d4_words.inc"
};
static const uint32_t kMain8002A354Words[] = {
#include "8002a354_words.inc"
};
static const uint32_t kMain8002A400Words[] = {
#include "8002a400_words.inc"
};
static const uint32_t kMain8002A44CWords[] = {
#include "8002a44c_words.inc"
};
static const uint32_t kMain8002A480Words[] = {
#include "8002a480_words.inc"
};
static const uint32_t kMain8002A4B8Words[] = {
#include "8002a4b8_words.inc"
};
static const uint32_t kMain8002A4C8Words[] = {
#include "8002a4c8_words.inc"
};
static const uint32_t kMain8002A4D8Words[] = {
#include "8002a4d8_words.inc"
};
static const uint32_t kMain8002A4FCWords[] = {
#include "8002a4fc_words.inc"
};
static const uint32_t kMain8002A520Words[] = {
#include "8002a520_words.inc"
};
static const uint32_t kMain8002A544Words[] = {
#include "8002a544_words.inc"
};
static const uint32_t kMain8002A5C4Words[] = {
#include "8002a5c4_words.inc"
};
static const uint32_t kMain8002A670Words[] = {
#include "8002a670_words.inc"
};
static const uint32_t kMain8002A6BCWords[] = {
#include "8002a6bc_words.inc"
};
static const uint32_t kMain8002A6F0Words[] = {
#include "8002a6f0_words.inc"
};
static const uint32_t kMain8002A728Words[] = {
#include "8002a728_words.inc"
};
static const uint32_t kMain8002A738Words[] = {
#include "8002a738_words.inc"
};
static const uint32_t kMain8002A748Words[] = {
#include "8002a748_words.inc"
};
static const uint32_t kMain8002A76CWords[] = {
#include "8002a76c_words.inc"
};
static const uint32_t kMain8002A790Words[] = {
#include "8002a790_words.inc"
};
static const uint32_t kMain8002A7B4Words[] = {
#include "8002a7b4_words.inc"
};
static const uint32_t kMain8002A834Words[] = {
#include "8002a834_words.inc"
};
static const uint32_t kMain8002A8E0Words[] = {
#include "8002a8e0_words.inc"
};
static const uint32_t kMain8002A92CWords[] = {
#include "8002a92c_words.inc"
};
static const uint32_t kMain8002A960Words[] = {
#include "8002a960_words.inc"
};
static const uint32_t kMain8002A998Words[] = {
#include "8002a998_words.inc"
};
static const uint32_t kMain8002A9A8Words[] = {
#include "8002a9a8_words.inc"
};
static const uint32_t kMain8002A9B8Words[] = {
#include "8002a9b8_words.inc"
};
static const uint32_t kMain8002A9DCWords[] = {
#include "8002a9dc_words.inc"
};
static const uint32_t kMain8002AA00Words[] = {
#include "8002aa00_words.inc"
};
static const uint32_t kMain8002AA3CWords[] = {
#include "8002aa3c_words.inc"
};
static const uint32_t kMain8002AAACWords[] = {
#include "8002aaac_words.inc"
};
static const uint32_t kMain8002AAB4Words[] = {
#include "8002aab4_words.inc"
};
static const uint32_t kMain80029274Words[] = {
#include "80029274_words.inc"
};
static const uint32_t kMain8002931CWords[] = {
#include "8002931c_words.inc"
};
static const uint32_t kMain8002941CWords[] = {
#include "8002941c_words.inc"
};
static const uint32_t kMain80029444Words[] = {
#include "80029444_words.inc"
};
static const uint32_t kMain8002AEF8Words[] = {
#include "8002aef8_words.inc"
};
static const uint32_t kMain8002AF08Words[] = {
#include "8002af08_words.inc"
};
static const uint32_t kMain8002AF18Words[] = {
#include "8002af18_words.inc"
};
static const uint32_t kMain8002AF48Words[] = {
#include "8002af48_words.inc"
};
static const uint32_t kMain8002AF60Words[] = {
#include "8002af60_words.inc"
};
static const uint32_t kMain8002AF70Words[] = {
#include "8002af70_words.inc"
};
static const uint32_t kMain8002B00CWords[] = {
#include "8002b00c_words.inc"
};
static const uint32_t kMain8002B064Words[] = {
#include "8002b064_words.inc"
};
static const uint32_t kMain8002B08CWords[] = {
#include "8002b08c_words.inc"
};
static const uint32_t kMain8002B0B4Words[] = {
#include "8002b0b4_words.inc"
};
static const uint32_t kMain8002C320Words[] = {
#include "8002c320_words.inc"
};
static const uint32_t kMain8002C3B0Words[] = {
#include "8002c3b0_words.inc"
};
static const uint32_t kMain8002C410Words[] = {
#include "8002c410_words.inc"
};
_Static_assert(sizeof(kMain8002AEF8Words) / sizeof(uint32_t) == 4, "main 8002AEF8 source span changed");
static const uint32_t kMain80029254Words[] = {
#include "80029254_words.inc"
};
static const uint32_t kMain80029264Words[] = {
#include "80029264_words.inc"
};
_Static_assert(sizeof(kMain80029254Words) / sizeof(uint32_t) == 4, "main 80029254 source span changed");
static const uint32_t kMain80011DCCWords[] = {
#include "80011dcc_words.inc"
};
static const uint32_t kMain80011DF4Words[] = {
#include "80011df4_words.inc"
};
static const uint32_t kMain80011E10Words[] = {
#include "80011e10_words.inc"
};
_Static_assert(sizeof(kMain80011DCCWords) / sizeof(uint32_t) == 10, "main 80011DCC source span changed");
static const uint32_t kMain8001B384Words[] = {
#include "8001b384_words.inc"
};
_Static_assert(sizeof(kMain8001B384Words) / sizeof(uint32_t) == 4, "main 8001B384 source span changed");
static const uint32_t kMain8001C0C8Words[] = {
#include "8001c0c8_words.inc"
};
static const uint32_t kMain8001C14CWords[] = {
#include "8001c14c_words.inc"
};
static const uint32_t kMain8001C1E4Words[] = {
#include "8001c1e4_words.inc"
};
_Static_assert(sizeof(kMain8001C0C8Words) / sizeof(uint32_t) == 33, "main 8001C0C8 source span changed");
static const uint32_t kMain8001B85CWords[] = {
#include "8001b85c_words.inc"
};
static const uint32_t kMain8001B86CWords[] = {
#include "8001b86c_words.inc"
};
static const uint32_t kMain8001BA84Words[] = {
#include "8001ba84_words.inc"
};
static const uint32_t kMain8001BADCWords[] = {
#include "8001badc_words.inc"
};
static const uint32_t kMain8001BB60Words[] = {
#include "8001bb60_words.inc"
};
static const uint32_t kMain8001BBBCWords[] = {
#include "8001bbbc_words.inc"
};
static const uint32_t kMain8001BC6CWords[] = {
#include "8001bc6c_words.inc"
};
static const uint32_t kMain8001BD80Words[] = {
#include "8001bd80_words.inc"
};
static const uint32_t kMain8001BDA0Words[] = {
#include "8001bda0_words.inc"
};
static const uint32_t kMain8001BE20Words[] = {
#include "8001be20_words.inc"
};
static const uint32_t kMain8001BE30Words[] = {
#include "8001be30_words.inc"
};
_Static_assert(sizeof(kMain8001B85CWords) / sizeof(uint32_t) == 4, "main 8001B85C source span changed");
static const uint32_t kMain80011CFCWords[] = {
#include "80011cfc_words.inc"
};
_Static_assert(sizeof(kMain80011CFCWords) / sizeof(uint32_t) == 22, "main 80011CFC source span changed");
static const uint32_t kMain80011D54Words[] = {
#include "80011d54_words.inc"
};
static const uint32_t kMain80011DA0Words[] = {
#include "80011da0_words.inc"
};
_Static_assert(sizeof(kMain80011D54Words) / sizeof(uint32_t) == 19, "main 80011D54 source span changed");
static const uint32_t kMain800191D4Words[] = {
#include "800191d4_words.inc"
};
static const uint32_t kMain8001923CWords[] = {
#include "8001923c_words.inc"
};
static const uint32_t kMain8001931CWords[] = {
#include "8001931c_words.inc"
};
static const uint32_t kMain80019378Words[] = {
#include "80019378_words.inc"
};
static const uint32_t kMain80019388Words[] = {
#include "80019388_words.inc"
};
static const uint32_t kMain80019398Words[] = {
#include "80019398_words.inc"
};
static const uint32_t kMain800193A8Words[] = {
#include "800193a8_words.inc"
};
static const uint32_t kMain800193B8Words[] = {
#include "800193b8_words.inc"
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
static const uint32_t kMain8002F67CWords[] = {
#include "8002f67c_words.inc"
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
static const uint32_t kMain80018918Words[] = {
#include "80018918_words.inc"
};
_Static_assert(sizeof(kMain80018730Words) / sizeof(uint32_t) == 122, "main 80018730 source span changed");
static const uint32_t kMain8002D858Words[] = {
#include "8002d858_words.inc"
};
_Static_assert(sizeof(kMain8002D858Words) / sizeof(uint32_t) == 20, "main 8002D858 source span changed");
static const uint32_t kMain8003D650Words[] = {
#include "8003d650_words.inc"
};
static const uint32_t kMain8003D6E4Words[] = {
#include "8003d6e4_words.inc"
};
static const uint32_t kMain8003D94CWords[] = {
#include "8003d94c_words.inc"
};
static const uint32_t kMain8003D96CWords[] = {
#include "8003d96c_words.inc"
};
static const uint32_t kMain8003D98CWords[] = {
#include "8003d98c_words.inc"
};
static const uint32_t kMain8003D9CCWords[] = {
#include "8003d9cc_words.inc"
};
static const uint32_t kMain8003DA1CWords[] = {
#include "8003da1c_words.inc"
};
static const uint32_t kMain8003DC90Words[] = {
#include "8003dc90_words.inc"
};
static const uint32_t kMain8003DF8CWords[] = {
#include "8003df8c_words.inc"
};
static const uint32_t kMain8003E248Words[] = {
#include "8003e248_words.inc"
};
static const uint32_t kMain8003E2E4Words[] = {
#include "8003e2e4_words.inc"
};
static const uint32_t kMain8003E310Words[] = {
#include "8003e310_words.inc"
};
static const uint32_t kMain8003E418Words[] = {
#include "8003e418_words.inc"
};
static const uint32_t kMain8003E65CWords[] = {
#include "8003e65c_words.inc"
};
static const uint32_t kMain8003EA04Words[] = {
#include "8003ea04_words.inc"
};
static const uint32_t kMain8003EAB4Words[] = {
#include "8003eab4_words.inc"
};
static const uint32_t kMain8003EBB0Words[] = {
#include "8003ebb0_words.inc"
};
static const uint32_t kMain8003EC10Words[] = {
#include "8003ec10_words.inc"
};
static const uint32_t kMain8003ED94Words[] = {
#include "8003ed94_words.inc"
};
static const uint32_t kMain8003EDBCWords[] = {
#include "8003edbc_words.inc"
};
_Static_assert(sizeof(kMain8003D650Words) / sizeof(uint32_t) == 37, "main 8003D650 source span changed");
static const uint32_t kMain8001BFA0Words[] = {
#include "8001bfa0_words.inc"
};
_Static_assert(sizeof(kMain8001BFA0Words) / sizeof(uint32_t) == 4, "main 8001BFA0 source span changed");
static const uint32_t kMain8001BFB0Words[] = {
#include "8001bfb0_words.inc"
};
static const uint32_t kMain8001BFD0Words[] = {
#include "8001bfd0_words.inc"
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
static const uint32_t kMain80046980Words[] = {
#include "80046980_words.inc"
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
static const uint32_t kMain80046A5CWords[] = {
#include "80046a5c_words.inc"
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
static const uint32_t kMain80014BFCWords[] = {
#include "80014bfc_words.inc"
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
static const uint32_t kMain80010B10Words[] = {
#include "80010b10_words.inc"
};
static const uint32_t kMain80010B2CWords[] = {
#include "80010b2c_words.inc"
};
static const uint32_t kMain80011B7CWords[] = {
#include "80011b7c_words.inc"
};
static const uint32_t kMain80011C10Words[] = {
#include "80011c10_words.inc"
};
static const uint32_t kMain80011C8CWords[] = {
#include "80011c8c_words.inc"
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
static const uint32_t kMain8003D32CWords[] = {
#include "8003d32c_words.inc"
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
static const uint32_t kMain8002D4B8Words[] = {
#include "8002d4b8_words.inc"
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
static const uint32_t kMain8003D3F8Words[] = {
#include "8003d3f8_words.inc"
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
static const uint32_t kMain800342E8Words[] = {
#include "800342e8_words.inc"
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
static const uint32_t kMain8003F434Words[] = {
#include "8003f434_words.inc"
};
static const uint32_t kMain8003F7C8Words[] = {
#include "8003f7c8_words.inc"
};
static const uint32_t kMain8003F840Words[] = {
#include "8003f840_words.inc"
};
static const uint32_t kMain8003FA54Words[] = {
#include "8003fa54_words.inc"
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
static const uint32_t kMain80059E6CWords[] = {
#include "80059e6c_words.inc"
};
static const uint32_t kMain80059F88Words[] = {
#include "80059f88_words.inc"
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
static const uint32_t kMain8005ADB8Words[] = {
#include "8005adb8_words.inc"
};
static const uint32_t kMain8005AE68Words[] = {
#include "8005ae68_words.inc"
};
static const uint32_t kDraw8005B7B0Words[] = {
#include "8005b7b0_words.inc"
};
static const uint32_t kDraw8005BA90Words[] = {
#include "8005ba90_words.inc"
};
static const uint32_t kMain8005BD7CWords[] = {
#include "8005bd7c_words.inc"
};
static const uint32_t kMain8001099CWords[] = {
#include "8001099c_words.inc"
};
static const uint32_t kMain80058CE4Words[] = {
#include "80058ce4_words.inc"
};
static const uint32_t kMain80058D20Words[] = {
#include "80058d20_words.inc"
};
static const uint32_t kMain80058D48Words[] = {
#include "80058d48_words.inc"
};
static const uint32_t kMain80058D70Words[] = {
#include "80058d70_words.inc"
};
static const uint32_t kMain80058D84Words[] = {
#include "80058d84_words.inc"
};
static const uint32_t kMain80058D98Words[] = {
#include "80058d98_words.inc"
};
static const uint32_t kMain80058DACWords[] = {
#include "80058dac_words.inc"
};
static const uint32_t kMain80058DC0Words[] = {
#include "80058dc0_words.inc"
};
static const uint32_t kMain80058DD4Words[] = {
#include "80058dd4_words.inc"
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
static const uint32_t kMain8005A468Words[] = {
#include "8005a468_words.inc"
};
static const uint32_t kMain8005A4A0Words[] = {
#include "8005a4a0_words.inc"
};
static const uint32_t kMain8005A4D0Words[] = {
#include "8005a4d0_words.inc"
};
static const uint32_t kMain8005A50CWords[] = {
#include "8005a50c_words.inc"
};
static const uint32_t kMain8005A590Words[] = {
#include "8005a590_words.inc"
};
static const uint32_t kMain8005A5D4Words[] = {
#include "8005a5d4_words.inc"
};
static const uint32_t kDisplay8005B684Words[] = {
#include "8005b684_words.inc"
};
static const uint32_t kMain8005B6ACWords[] = {
#include "8005b6ac_words.inc"
};
static const uint32_t kMain8005B6C0Words[] = {
#include "8005b6c0_words.inc"
};
static const uint32_t kDraw800426FCWords[] = {
#include "800426fc_words.inc"
};
static const uint32_t kMain80042718Words[] = {
#include "80042718_words.inc"
};
static const uint32_t kMain800427F4Words[] = {
#include "800427f4_words.inc"
};
static const uint32_t kMain800429DCWords[] = {
#include "800429dc_words.inc"
};
static const uint32_t kMain80042B30Words[] = {
#include "80042b30_words.inc"
};
static const uint32_t kMain80042BDCWords[] = {
#include "80042bdc_words.inc"
};
static const uint32_t kMain80042C64Words[] = {
#include "80042c64_words.inc"
};
static const uint32_t kMain80042C90Words[] = {
#include "80042c90_words.inc"
};
static const uint32_t kMain80042CE8Words[] = {
#include "80042ce8_words.inc"
};
static const uint32_t kMain80042D60Words[] = {
#include "80042d60_words.inc"
};
static const uint32_t kMain80042D8CWords[] = {
#include "80042d8c_words.inc"
};
static const uint32_t kMain80042DB8Words[] = {
#include "80042db8_words.inc"
};
static const uint32_t kMain80042E08Words[] = {
#include "80042e08_words.inc"
};
static const uint32_t kGte80053CF8Words[] = {
#include "80053cf8_words.inc"
};
static const uint32_t kProjection8005283CWords[] = {
#include "8005283c_words.inc"
};
static const uint32_t kMain80052AA0Words[] = {
#include "80052aa0_words.inc"
};
static const uint32_t kMain80052BDCWords[] = {
#include "80052bdc_words.inc"
};
static const uint32_t kProjection80052D00Words[] = {
#include "80052d00_words.inc"
};
static const uint32_t kProjection80052D90Words[] = {
#include "80052d90_words.inc"
};
static const uint32_t kMain80052E38Words[] = {
#include "80052e38_words.inc"
};
static const uint32_t kMain80052E68Words[] = {
#include "80052e68_words.inc"
};
static const uint32_t kMain80052F04Words[] = {
#include "80052f04_words.inc"
};
static const uint32_t kMain80052F38Words[] = {
#include "80052f38_words.inc"
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
static const uint32_t kMain80053978Words[] = {
#include "80053978_words.inc"
};
static const uint32_t kMain800539C8Words[] = {
#include "800539c8_words.inc"
};
static const uint32_t kMain800539D8Words[] = {
#include "800539d8_words.inc"
};
static const uint32_t kMain800539E8Words[] = {
#include "800539e8_words.inc"
};
static const uint32_t kMain800539F8Words[] = {
#include "800539f8_words.inc"
};
static const uint32_t kMain80053A18Words[] = {
#include "80053a18_words.inc"
};
static const uint32_t kMain80053A2CWords[] = {
#include "80053a2c_words.inc"
};
static const uint32_t kMain80053A40Words[] = {
#include "80053a40_words.inc"
};
static const uint32_t kMain80053A4CWords[] = {
#include "80053a4c_words.inc"
};
static const uint32_t kMain80053A60Words[] = {
#include "80053a60_words.inc"
};
static const uint32_t kMain80053A78Words[] = {
#include "80053a78_words.inc"
};
static const uint32_t kMain80053A8CWords[] = {
#include "80053a8c_words.inc"
};
static const uint32_t kMain80053AA0Words[] = {
#include "80053aa0_words.inc"
};
static const uint32_t kMain80053AB4Words[] = {
#include "80053ab4_words.inc"
};
static const uint32_t kMain80053AC0Words[] = {
#include "80053ac0_words.inc"
};
static const uint32_t kMain80053ACCWords[] = {
#include "80053acc_words.inc"
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
static const uint32_t kMain8004864CWords[] = {
#include "8004864c_words.inc"
};
static const uint32_t kMain8004867CWords[] = {
#include "8004867c_words.inc"
};
static const uint32_t kMain8004871CWords[] = {
#include "8004871c_words.inc"
};
static const uint32_t kMain800487BCWords[] = {
#include "800487bc_words.inc"
};
static const uint32_t kMain8004880CWords[] = {
#include "8004880c_words.inc"
};
static const uint32_t kMain8004891CWords[] = {
#include "8004891c_words.inc"
};
static const uint32_t kMain80048B6CWords[] = {
#include "80048b6c_words.inc"
};
static const uint32_t kMain80048CACWords[] = {
#include "80048cac_words.inc"
};
static const uint32_t kCamera80053B20Words[] = {
#include "80053b20_words.inc"
};
static const uint32_t kMain80053BD8Words[] = {
#include "80053bd8_words.inc"
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
static const uint32_t kMain800479E8Words[] = {
#include "800479e8_words.inc"
};
static const uint32_t kMain80047B3CWords[] = {
#include "80047b3c_words.inc"
};
static const uint32_t kMain80047BD8Words[] = {
#include "80047bd8_words.inc"
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
static const uint32_t kMain80047DCCWords[] = {
#include "80047dcc_words.inc"
};
static const uint32_t kSecondGeom80014444Words[] = {
#include "80014444_words.inc"
};
static const uint32_t kSecondGeom8004923CWords[] = {
#include "8004923c_words.inc"
};
static const uint32_t kMain8004924CWords[] = {
#include "8004924c_words.inc"
};
static const uint32_t kMain80049274Words[] = {
#include "80049274_words.inc"
};
static const uint32_t kMain8004929CWords[] = {
#include "8004929c_words.inc"
};
static const uint32_t kMain800492D8Words[] = {
#include "800492d8_words.inc"
};
static const uint32_t kMain800492FCWords[] = {
#include "800492fc_words.inc"
};
static const uint32_t kMain80049324Words[] = {
#include "80049324_words.inc"
};
static const uint32_t kMain8004934CWords[] = {
#include "8004934c_words.inc"
};
static const uint32_t kMain8004936CWords[] = {
#include "8004936c_words.inc"
};
static const uint32_t kMain80049390Words[] = {
#include "80049390_words.inc"
};
static const uint32_t kMain800493E8Words[] = {
#include "800493e8_words.inc"
};
static const uint32_t kSecondGeom80014554Words[] = {
#include "80014554_words.inc"
};
static const uint32_t kSecondGeom8002850CWords[] = {
#include "8002850c_words.inc"
};
static const uint32_t kMain80028558Words[] = {
#include "80028558_words.inc"
};
static const uint32_t kSecondGeom80053AF8Words[] = {
#include "80053af8_words.inc"
};
static const uint32_t kSecondGeom8002823CWords[] = {
#include "8002823c_words.inc"
};
static const uint32_t kMain80028304Words[] = {
#include "80028304_words.inc"
};
static const uint32_t kMain80028394Words[] = {
#include "80028394_words.inc"
};
static const uint32_t kMain80028428Words[] = {
#include "80028428_words.inc"
};
static const uint32_t kMain80028488Words[] = {
#include "80028488_words.inc"
};
static const uint32_t kSecondGeom80028620Words[] = {
#include "80028620_words.inc"
};
static const uint32_t kMain80028694Words[] = {
#include "80028694_words.inc"
};
static const uint32_t kMain80028A30Words[] = {
#include "80028a30_words.inc"
};
static const uint32_t kMain80028A38Words[] = {
#include "80028a38_words.inc"
};
static const uint32_t kMain80028A40Words[] = {
#include "80028a40_words.inc"
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
static const uint32_t kMain8005991CWords[] = {
#include "8005991c_words.inc"
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
static const uint32_t kMain8004D1DCWords[] = {
#include "8004d1dc_words.inc"
};
static const uint32_t kMain8004D3ACWords[] = {
#include "8004d3ac_words.inc"
};
static const uint32_t kMain8004D420Words[] = {
#include "8004d420_words.inc"
};
static const uint32_t kMain8004D504Words[] = {
#include "8004d504_words.inc"
};
static const uint32_t kMain8004D6BCWords[] = {
#include "8004d6bc_words.inc"
};
static const uint32_t kMain8004D7F8Words[] = {
#include "8004d7f8_words.inc"
};
static const uint32_t kMain8004D938Words[] = {
#include "8004d938_words.inc"
};
static const uint32_t kMain8004DA80Words[] = {
#include "8004da80_words.inc"
};
static const uint32_t kMain8004DBCCWords[] = {
#include "8004dbcc_words.inc"
};
static const uint32_t kMain8004DD34Words[] = {
#include "8004dd34_words.inc"
};
static const uint32_t kMain8004DEA0Words[] = {
#include "8004dea0_words.inc"
};
static const uint32_t kMain8004E018Words[] = {
#include "8004e018_words.inc"
};
static const uint32_t kMain8004E19CWords[] = {
#include "8004e19c_words.inc"
};
static const uint32_t kMain8004E2E4Words[] = {
#include "8004e2e4_words.inc"
};
static const uint32_t kMain8004E424Words[] = {
#include "8004e424_words.inc"
};
static const uint32_t kMain8004E5B4Words[] = {
#include "8004e5b4_words.inc"
};
static const uint32_t kMain8004E74CWords[] = {
#include "8004e74c_words.inc"
};
static const uint32_t kMain8004E8CCWords[] = {
#include "8004e8cc_words.inc"
};
static const uint32_t kMain8004EA40Words[] = {
#include "8004ea40_words.inc"
};
static const uint32_t kMain8004EC20Words[] = {
#include "8004ec20_words.inc"
};
static const uint32_t kMain8004EE0CWords[] = {
#include "8004ee0c_words.inc"
};
static const uint32_t kMain8004EF78Words[] = {
#include "8004ef78_words.inc"
};
static const uint32_t kMain8004F0DCWords[] = {
#include "8004f0dc_words.inc"
};
static const uint32_t kMain8004F24CWords[] = {
#include "8004f24c_words.inc"
};
static const uint32_t kMain8004F3BCWords[] = {
#include "8004f3bc_words.inc"
};
static const uint32_t kMain8004F55CWords[] = {
#include "8004f55c_words.inc"
};
static const uint32_t kMain8004F6F8Words[] = {
#include "8004f6f8_words.inc"
};
static const uint32_t kMain8004F8A4Words[] = {
#include "8004f8a4_words.inc"
};
static const uint32_t kMain8004FA5CWords[] = {
#include "8004fa5c_words.inc"
};
static const uint32_t kMain8004FBD4Words[] = {
#include "8004fbd4_words.inc"
};
static const uint32_t kMain8004FD30Words[] = {
#include "8004fd30_words.inc"
};
static const uint32_t kMain8004FEE4Words[] = {
#include "8004fee4_words.inc"
};
static const uint32_t kMain8005009CWords[] = {
#include "8005009c_words.inc"
};
static const uint32_t kMain80050258Words[] = {
#include "80050258_words.inc"
};
static const uint32_t kMain800503F0Words[] = {
#include "800503f0_words.inc"
};
static const uint32_t kMain800505FCWords[] = {
#include "800505fc_words.inc"
};
static const uint32_t kMain8005080CWords[] = {
#include "8005080c_words.inc"
};
static const uint32_t kMain80051044Words[] = {
#include "80051044_words.inc"
};
static const uint32_t kMain80051804Words[] = {
#include "80051804_words.inc"
};
static const uint32_t kMain80051844Words[] = {
#include "80051844_words.inc"
};
static const uint32_t kMain80051B0CWords[] = {
#include "80051b0c_words.inc"
};
static const uint32_t kMain80051D78Words[] = {
#include "80051d78_words.inc"
};
static const uint32_t kMain80051DC8Words[] = {
#include "80051dc8_words.inc"
};
static const uint32_t kMain80051EA0Words[] = {
#include "80051ea0_words.inc"
};
static const uint32_t kMain80051F34Words[] = {
#include "80051f34_words.inc"
};
static const uint32_t kMain80052430Words[] = {
#include "80052430_words.inc"
};
static const uint32_t kMain80052460Words[] = {
#include "80052460_words.inc"
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
static const uint32_t kMain8005CE50Words[] = {
#include "8005ce50_words.inc"
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
static const uint32_t kMain8005E168Words[] = {
#include "8005e168_words.inc"
};
static const uint32_t kMain8005E178Words[] = {
#include "8005e178_words.inc"
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
static const uint32_t kMain8005F0C8Words[] = {
#include "8005f0c8_words.inc"
};
static const uint32_t kMain8005F228Words[] = {
#include "8005f228_words.inc"
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
static const uint32_t kMain8005D8B4Words[] = {
#include "8005d8b4_words.inc"
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
static const uint32_t kMain8005FC68Words[] = {
#include "8005fc68_words.inc"
};
static const uint32_t kMain8005FC98Words[] = {
#include "8005fc98_words.inc"
};
static const uint32_t kMain8005FCB8Words[] = {
#include "8005fcb8_words.inc"
};
static const uint32_t kMain8005FD18Words[] = {
#include "8005fd18_words.inc"
};
static const uint32_t kMain8005FD58Words[] = {
#include "8005fd58_words.inc"
};
static const uint32_t kMain8005FDD4Words[] = {
#include "8005fdd4_words.inc"
};
static const uint32_t kMain8005FFB4Words[] = {
#include "8005ffb4_words.inc"
};
static const uint32_t kMain80060030Words[] = {
#include "80060030_words.inc"
};
static const uint32_t kMain8006023CWords[] = {
#include "8006023c_words.inc"
};
static const uint32_t kMain800603BCWords[] = {
#include "800603bc_words.inc"
};
static const uint32_t kMain80060404Words[] = {
#include "80060404_words.inc"
};
static const uint32_t kMain800604C4Words[] = {
#include "800604c4_words.inc"
};
static const uint32_t kMain80060614Words[] = {
#include "80060614_words.inc"
};
static const uint32_t kMain800606D4Words[] = {
#include "800606d4_words.inc"
};
static const uint32_t kMain80060824Words[] = {
#include "80060824_words.inc"
};
static const uint32_t kMain80060930Words[] = {
#include "80060930_words.inc"
};
static const uint32_t kMain80060AE0Words[] = {
#include "80060ae0_words.inc"
};
static const uint32_t kMain80060BECWords[] = {
#include "80060bec_words.inc"
};
static const uint32_t kMain80060D9CWords[] = {
#include "80060d9c_words.inc"
};
static const uint32_t kMain80061010Words[] = {
#include "80061010_words.inc"
};
static const uint32_t kMain80061024Words[] = {
#include "80061024_words.inc"
};
static const uint32_t kMain80061114Words[] = {
#include "80061114_words.inc"
};
static const uint32_t kMain80061344Words[] = {
#include "80061344_words.inc"
};
static const uint32_t kMain80061524Words[] = {
#include "80061524_words.inc"
};
static const uint32_t kMain800615BCWords[] = {
#include "800615bc_words.inc"
};
static const uint32_t kMain80061678Words[] = {
#include "80061678_words.inc"
};
static const uint32_t kMain800616D0Words[] = {
#include "800616d0_words.inc"
};
static const uint32_t kMain80061770Words[] = {
#include "80061770_words.inc"
};
static const uint32_t kMain8006186CWords[] = {
#include "8006186c_words.inc"
};
static const uint32_t kMain8006189CWords[] = {
#include "8006189c_words.inc"
};
static const uint32_t kMain80061A80Words[] = {
#include "80061a80_words.inc"
};
static const uint32_t kMain80061AA0Words[] = {
#include "80061aa0_words.inc"
};
static const uint32_t kMain80061B58Words[] = {
#include "80061b58_words.inc"
};
static const uint32_t kMain80061C60Words[] = {
#include "80061c60_words.inc"
};
static const uint32_t kMain80061D3CWords[] = {
#include "80061d3c_words.inc"
};
static const uint32_t kMain80061E18Words[] = {
#include "80061e18_words.inc"
};
static const uint32_t kMain80061E54Words[] = {
#include "80061e54_words.inc"
};
static const uint32_t kMain80061E90Words[] = {
#include "80061e90_words.inc"
};
static const uint32_t kMain80061F38Words[] = {
#include "80061f38_words.inc"
};
static const uint32_t kMain80061F48Words[] = {
#include "80061f48_words.inc"
};
static const uint32_t kMain80061F58Words[] = {
#include "80061f58_words.inc"
};
static const uint32_t kMain80061F68Words[] = {
#include "80061f68_words.inc"
};
static const uint32_t kMain80061F78Words[] = {
#include "80061f78_words.inc"
};
static const uint32_t kMain80061F88Words[] = {
#include "80061f88_words.inc"
};
static const uint32_t kMain80061F98Words[] = {
#include "80061f98_words.inc"
};
static const uint32_t kMain80061FA8Words[] = {
#include "80061fa8_words.inc"
};
static const uint32_t kMain80062144Words[] = {
#include "80062144_words.inc"
};
static const uint32_t kMain80062248Words[] = {
#include "80062248_words.inc"
};
static const uint32_t kMain80062258Words[] = {
#include "80062258_words.inc"
};
static const uint32_t kMain80062268Words[] = {
#include "80062268_words.inc"
};
static const uint32_t kMain80062278Words[] = {
#include "80062278_words.inc"
};
static const uint32_t kMain80062288Words[] = {
#include "80062288_words.inc"
};
static const uint32_t kMain80062298Words[] = {
#include "80062298_words.inc"
};
static const uint32_t kMain800622D0Words[] = {
#include "800622d0_words.inc"
};
static const uint32_t kMain80062328Words[] = {
#include "80062328_words.inc"
};
static const uint32_t kMain80062360Words[] = {
#include "80062360_words.inc"
};
static const uint32_t kMain80062388Words[] = {
#include "80062388_words.inc"
};
static const uint32_t kMain80062394Words[] = {
#include "80062394_words.inc"
};
static const uint32_t kMain800623A4Words[] = {
#include "800623a4_words.inc"
};
static const uint32_t kMain80062434Words[] = {
#include "80062434_words.inc"
};
static const uint32_t kMain800624C4Words[] = {
#include "800624c4_words.inc"
};
static const uint32_t kMain800624F4Words[] = {
#include "800624f4_words.inc"
};
static const uint32_t kMain8006252CWords[] = {
#include "8006252c_words.inc"
};
static const uint32_t kMain800625A4Words[] = {
#include "800625a4_words.inc"
};
static const uint32_t kMain800625DCWords[] = {
#include "800625dc_words.inc"
};
static const uint32_t kMain80062644Words[] = {
#include "80062644_words.inc"
};
static const uint32_t kMain80062688Words[] = {
#include "80062688_words.inc"
};
static const uint32_t kMain80062698Words[] = {
#include "80062698_words.inc"
};
static const uint32_t kMain800626A8Words[] = {
#include "800626a8_words.inc"
};
static const uint32_t kMain800626B8Words[] = {
#include "800626b8_words.inc"
};
static const uint32_t kMain800626C8Words[] = {
#include "800626c8_words.inc"
};
static const uint32_t kMain800626DCWords[] = {
#include "800626dc_words.inc"
};
static const uint32_t kMain800626F0Words[] = {
#include "800626f0_words.inc"
};
static const uint32_t kMain80062768Words[] = {
#include "80062768_words.inc"
};
static const uint32_t kMain800627D8Words[] = {
#include "800627d8_words.inc"
};
static const uint32_t kMain800627E8Words[] = {
#include "800627e8_words.inc"
};
static const uint32_t kMain800627F8Words[] = {
#include "800627f8_words.inc"
};
static const uint32_t kMain80062808Words[] = {
#include "80062808_words.inc"
};
static const uint32_t kMain80062888Words[] = {
#include "80062888_words.inc"
};
static const uint32_t kMain8006289CWords[] = {
#include "8006289c_words.inc"
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
static const uint32_t kMain8003B350Words[] = {
#include "8003b350_words.inc"
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
static const uint32_t kMain80042580Words[] = {
#include "80042580_words.inc"
};
static const uint32_t kMain800425B0Words[] = {
#include "800425b0_words.inc"
};
_Static_assert(sizeof(kFile800424E4Words) / sizeof(uint32_t) == 39,
               "LIST source 800424E4 span changed");
static const uint32_t kMain80044F24Words[] = {
#include "80044f24_words.inc"
};
static const uint32_t kFile8001971CWords[] = {
#include "8001971c_words.inc"
};
static const uint32_t kMain80019930Words[] = {
#include "80019930_words.inc"
};
_Static_assert(sizeof(kFile8001971CWords) / sizeof(uint32_t) == 133,
               "File loader 8001971C source span changed");
static const uint32_t kFile80019990Words[] = {
#include "80019990_words.inc"
};
static const uint32_t kMain80019A10Words[] = {
#include "80019a10_words.inc"
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
static const uint32_t kMain8005C388Words[] = {
#include "8005c388_words.inc"
};
static const uint32_t kMain8005C49CWords[] = {
#include "8005c49c_words.inc"
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
static const uint32_t kMain800439B4Words[] = {
#include "800439b4_words.inc"
};
_Static_assert(sizeof(kFile80043994Words) / sizeof(uint32_t) == 8,
               "CD read 80043994 source span changed");
static const uint32_t kFile80043B1CWords[] = {
#include "80043b1c_words.inc"
};
static const uint32_t kMain80043B9CWords[] = {
#include "80043b9c_words.inc"
};
static const uint32_t kMain80044124Words[] = {
#include "80044124_words.inc"
};
_Static_assert(sizeof(kFile80043B1CWords) / sizeof(uint32_t) == 32,
               "CD read 80043B1C source span changed");
static const uint32_t kFile800443A4Words[] = {
#include "800443a4_words.inc"
};
static const uint32_t kMain80044670Words[] = {
#include "80044670_words.inc"
};
_Static_assert(sizeof(kFile800443A4Words) / sizeof(uint32_t) == 179,
               "CD sync 800443A4 source span changed");
static const uint32_t kFile80045090Words[] = {
#include "80045090_words.inc"
};
static const uint32_t kMain80045190Words[] = {
#include "80045190_words.inc"
};
static const uint32_t kMain80045280Words[] = {
#include "80045280_words.inc"
};
_Static_assert(sizeof(kFile80045090Words) / sizeof(uint32_t) == 64,
               "CD read 80045090 source span changed");
static const uint32_t kFile80045D00Words[] = {
#include "80045d00_words.inc"
};
static const uint32_t kMain80045FD0Words[] = {
#include "80045fd0_words.inc"
};
_Static_assert(sizeof(kFile80045D00Words) / sizeof(uint32_t) == 180,
               "CD read 80045D00 source span changed");
static const uint32_t kFile800460CCWords[] = {
#include "800460cc_words.inc"
};
static const uint32_t kMain800462E0Words[] = {
#include "800462e0_words.inc"
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
static const uint32_t kMain8004654CWords[] = {
#include "8004654c_words.inc"
};
static const uint32_t kMain80046564Words[] = {
#include "80046564_words.inc"
};
_Static_assert(sizeof(kFile80046480Words) / sizeof(uint32_t) == 51,
               "CD read 80046480 source span changed");
static const uint32_t kFile8005C584Words[] = {
#include "8005c584_words.inc"
};
static const uint32_t kMain8005C604Words[] = {
#include "8005c604_words.inc"
};
static const uint32_t kMain8005C640Words[] = {
#include "8005c640_words.inc"
};
static const uint32_t kMain8005CCC8Words[] = {
#include "8005ccc8_words.inc"
};
static const uint32_t kMain8005CD18Words[] = {
#include "8005cd18_words.inc"
};
static const uint32_t kMain8005CD48Words[] = {
#include "8005cd48_words.inc"
};
static const uint32_t kMain8005CD98Words[] = {
#include "8005cd98_words.inc"
};
_Static_assert(sizeof(kFile8005C584Words) / sizeof(uint32_t) == 32,
               "8005C584 source export changed");
static const uint32_t kFile8005C4DCWords[] = {
#include "8005c4dc_words.inc"
};
static const uint32_t kMain8005C540Words[] = {
#include "8005c540_words.inc"
};
_Static_assert(sizeof(kFile8005C4DCWords) / sizeof(uint32_t) == 25,
               "Directory compare 8005C4DC source span changed");
static const uint32_t kFile8005CE68Words[] = {
#include "8005ce68_words.inc"
};
static const uint32_t kMain8005CE78Words[] = {
#include "8005ce78_words.inc"
};
static const uint32_t kMain8005CE88Words[] = {
#include "8005ce88_words.inc"
};
_Static_assert(sizeof(kFile8005CE68Words) / sizeof(uint32_t) == 3,
               "CD read 8005CE68 source span changed");
static const uint32_t kFile8005CEA8Words[] = {
#include "8005cea8_words.inc"
};
static const uint32_t kMain8005CEB8Words[] = {
#include "8005ceb8_words.inc"
};
static const uint32_t kMain8005CEC8Words[] = {
#include "8005cec8_words.inc"
};
static const uint32_t kMain8005CED8Words[] = {
#include "8005ced8_words.inc"
};
static const uint32_t kMain8005CEE8Words[] = {
#include "8005cee8_words.inc"
};
static const uint32_t kMain8005CEF8Words[] = {
#include "8005cef8_words.inc"
};
static const uint32_t kMain8005CF08Words[] = {
#include "8005cf08_words.inc"
};
static const uint32_t kMain8005CF18Words[] = {
#include "8005cf18_words.inc"
};
static const uint32_t kMain8005CF28Words[] = {
#include "8005cf28_words.inc"
};
static const uint32_t kMain8005CF38Words[] = {
#include "8005cf38_words.inc"
};
static const uint32_t kMain8005CF48Words[] = {
#include "8005cf48_words.inc"
};
static const uint32_t kMain8005CF58Words[] = {
#include "8005cf58_words.inc"
};
static const uint32_t kMain8005CF68Words[] = {
#include "8005cf68_words.inc"
};
static const uint32_t kMain8005D004Words[] = {
#include "8005d004_words.inc"
};
static const uint32_t kMain8005D03CWords[] = {
#include "8005d03c_words.inc"
};
static const uint32_t kMain8005D06CWords[] = {
#include "8005d06c_words.inc"
};
static const uint32_t kMain8005D0A0Words[] = {
#include "8005d0a0_words.inc"
};
static const uint32_t kMain8005D0D8Words[] = {
#include "8005d0d8_words.inc"
};
static const uint32_t kMain8005D0F8Words[] = {
#include "8005d0f8_words.inc"
};
static const uint32_t kMain8005D118Words[] = {
#include "8005d118_words.inc"
};
static const uint32_t kMain8005D138Words[] = {
#include "8005d138_words.inc"
};
_Static_assert(sizeof(kFile8005CEA8Words) / sizeof(uint32_t) == 3,
               "BIOS TestEvent 8005CEA8 source span changed");
static const uint32_t kFile80043420Words[] = {
#include "80043420_words.inc"
};
static const uint32_t kMain80043430Words[] = {
#include "80043430_words.inc"
};
_Static_assert(sizeof(kFile80043420Words) / sizeof(uint32_t) == 4,
               "CD query 80043420 source span changed");
static const uint32_t kFile80043440Words[] = {
#include "80043440_words.inc"
};
static const uint32_t kMain80043450Words[] = {
#include "80043450_words.inc"
};
static const uint32_t kMain800434BCWords[] = {
#include "800434bc_words.inc"
};
static const uint32_t kMain800434DCWords[] = {
#include "800434dc_words.inc"
};
static const uint32_t kMain800434F4Words[] = {
#include "800434f4_words.inc"
};
static const uint32_t kMain80043528Words[] = {
#include "80043528_words.inc"
};
_Static_assert(sizeof(kFile80043440Words) / sizeof(uint32_t) == 4,
               "CD query 80043440 source span changed");
static const uint32_t kFile8004357CWords[] = {
#include "8004357c_words.inc"
};
static const uint32_t kMain8004359CWords[] = {
#include "8004359c_words.inc"
};
static const uint32_t kMain800435B4Words[] = {
#include "800435b4_words.inc"
};
_Static_assert(sizeof(kFile8004357CWords) / sizeof(uint32_t) == 8,
               "CD query 8004357C source span changed");
static const uint32_t kSpu80037D98Words[] = {
#include "80037d98_words.inc"
};
static const uint32_t kMain80037EA0Words[] = {
#include "80037ea0_words.inc"
};
static const uint32_t kMain80037F3CWords[] = {
#include "80037f3c_words.inc"
};
_Static_assert(sizeof(kSpu80037D98Words) / sizeof(uint32_t) == 66,
               "Sound 80037D98 source span changed");
static const uint32_t kSpu8003D424Words[] = {
#include "8003d424_words.inc"
};
static const uint32_t kMain8003D434Words[] = {
#include "8003d434_words.inc"
};
static const uint32_t kMain8003D454Words[] = {
#include "8003d454_words.inc"
};
_Static_assert(sizeof(kSpu8003D424Words) / sizeof(uint32_t) == 4,
               "Sound 8003D424 source span changed");
static const uint32_t kSpu8002CC4CWords[] = {
#include "8002cc4c_words.inc"
};
static const uint32_t kMain8002CCB4Words[] = {
#include "8002ccb4_words.inc"
};
static const uint32_t kMain8002CCD8Words[] = {
#include "8002ccd8_words.inc"
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
static const uint32_t kMain80043300Words[] = {
#include "80043300_words.inc"
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
static const uint32_t kMain80037028Words[] = {
#include "80037028_words.inc"
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
static const uint32_t kMain8003AA18Words[] = {
#include "8003aa18_words.inc"
};
static const uint32_t kMain8003AAD8Words[] = {
#include "8003aad8_words.inc"
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
static const uint32_t kMain8003B170Words[] = {
#include "8003b170_words.inc"
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
static const uint32_t kMain8003D630Words[] = {
#include "8003d630_words.inc"
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
static const uint32_t kMain80040938Words[] = {
#include "80040938_words.inc"
};
static const uint32_t kMain80040DE8Words[] = {
#include "80040de8_words.inc"
};
static const uint32_t kMain80041354Words[] = {
#include "80041354_words.inc"
};
static const uint32_t kMain800413B8Words[] = {
#include "800413b8_words.inc"
};
static const uint32_t kMain80041400Words[] = {
#include "80041400_words.inc"
};
static const uint32_t kMain80041448Words[] = {
#include "80041448_words.inc"
};
_Static_assert(sizeof(kSpu80040868Words) / sizeof(uint32_t) == 52,
               "80040868 source export changed");
static const uint32_t kSpu8003FA64Words[] = {
#include "8003fa64_words.inc"
};
static const uint32_t kMain8003FE18Words[] = {
#include "8003fe18_words.inc"
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
static const uint32_t kMain80043034Words[] = {
#include "80043034_words.inc"
};
static const uint32_t kMain80043060Words[] = {
#include "80043060_words.inc"
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

/* Range-indexed instruction lookup for the native seam.
 *
 * The dispatch used to be chains of `else if (pc >= a && pc < b)` tests,
 * one per carved range. At -O2 those chains dominated the compile: 16.7s
 * of a 17s translation unit, against the 30-second budget 83 tests give
 * `cc`, for a seam meant to reach every one of the game's 3,962
 * functions. A sorted table costs O(log n) at run time and almost nothing
 * to compile.
 *
 * Each table below holds ranges that were mutually disjoint as branches,
 * so first-match order carried no information and a binary search is
 * equivalent. Ranges that genuinely overlap -- the SC01/0012 overlay alias
 * at 80128158 -- are still spelled as ordered branches, and so is every
 * branch carrying a condition beyond its pc range.
 */
typedef struct {
    uint32_t start;
    uint32_t end;
    const uint32_t *words;
} FormatterRange;

static int formatter_range_word(const FormatterRange *ranges, size_t count,
                                uint32_t pc, uint32_t *out) {
    size_t low = 0u;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2u;
        if (pc < ranges[middle].start) {
            high = middle;
        } else if (pc >= ranges[middle].end) {
            low = middle + 1u;
        } else {
            *out = ranges[middle].words[(pc - ranges[middle].start) / 4u];
            return 1;
        }
    }
    return 0;
}

static const FormatterRange kFormatterRanges0[] = {
    { 0x80010000u, 0x800100a0u, kCrt80010000Words },
    { 0x800100a0u, 0x80010110u, kConstructor800100A0Words },
    { 0x80010110u, 0x80010178u, kMain80010110Words },
    { 0x80010178u, 0x8001020cu, kCaller80010178Words },
    { 0x8001020cu, 0x80010214u, kMain8001020CWords },
    { 0x80010214u, 0x80010938u, kMain80010214Words },
    { 0x80010938u, 0x8001094cu, kMain80010938Words },
    { 0x8001094cu, 0x8001096cu, kMain8001094CWords },
    { 0x8001096cu, 0x8001099cu, kMain8001096CWords },
    { 0x8001099cu, 0x80010a08u, kMain8001099CWords },
    { 0x80010a08u, 0x80010a84u, kMain80010A08Words },
    { 0x80010a84u, 0x80010a98u, kMain80010A84Words },
    { 0x80010a98u, 0x80010ae0u, kMain80010A98Words },
    { 0x80010ae0u, 0x80010b10u, kMain80010AE0Words },
    { 0x80010b10u, 0x80010b2cu, kMain80010B10Words },
    { 0x80010b2cu, 0x80010b40u, kMain80010B2CWords },
    { 0x80010b40u, 0x80010bb4u, kMain80010B40Words },
    { 0x80010bb4u, 0x80010c7cu, kMain80010BB4Words },
    { 0x80010c7cu, 0x80010cecu, kMain80010C7CWords },
    { 0x80010cecu, 0x80010d60u, kMain80010CECWords },
    { 0x80010d60u, 0x80010da0u, kMain80010D60Words },
    { 0x80010da0u, 0x80010de0u, kMain80010DA0Words },
    { 0x80010de0u, 0x80010e14u, kMain80010DE0Words },
    { 0x80010e14u, 0x80010e48u, kMain80010E14Words },
    { 0x80010e48u, 0x80010e7cu, kMain80010E48Words },
    { 0x80010e7cu, 0x80010ed4u, kMain80010E7CWords },
    { 0x80010ed4u, 0x80010f80u, kMain80010ED4Words },
    { 0x80010f80u, 0x800110ccu, kMain80010F80Words },
    { 0x800110ccu, 0x80011144u, kMain800110CCWords },
    { 0x80011144u, 0x800111bcu, kMain80011144Words },
    { 0x800111bcu, 0x80011220u, kMain800111BCWords },
    { 0x80011220u, 0x8001125cu, kMain80011220Words },
    { 0x8001125cu, 0x800112a8u, kMain8001125CWords },
    { 0x800112a8u, 0x800112c8u, kMain800112A8Words },
    { 0x800112c8u, 0x80011320u, kMain800112C8Words },
    { 0x80011320u, 0x80011350u, kMain80011320Words },
    { 0x80011350u, 0x8001136cu, kMain80011350Words },
    { 0x8001136cu, 0x80011380u, kMain8001136CWords },
    { 0x80011380u, 0x80011680u, kMain80011380Words },
    { 0x80011680u, 0x800116e0u, kMain80011680Words },
    { 0x800116e0u, 0x80011778u, kMain800116E0Words },
    { 0x80011778u, 0x80011818u, kMain80011778Words },
    { 0x80011818u, 0x800118acu, kMain80011818Words },
    { 0x800118acu, 0x80011928u, kMain800118ACWords },
    { 0x80011928u, 0x80011998u, kMain80011928Words },
    { 0x80011998u, 0x800119f0u, kMain80011998Words },
    { 0x800119f0u, 0x80011a3cu, kMain800119F0Words },
    { 0x80011a3cu, 0x80011adcu, kMain80011A3CWords },
    { 0x80011adcu, 0x80011b7cu, kMain80011ADCWords },
    { 0x80011b7cu, 0x80011c10u, kMain80011B7CWords },
    { 0x80011c10u, 0x80011c8cu, kMain80011C10Words },
    { 0x80011c8cu, 0x80011cfcu, kMain80011C8CWords },
    { 0x80011cfcu, 0x80011d54u, kMain80011CFCWords },
    { 0x80011d54u, 0x80011da0u, kMain80011D54Words },
    { 0x80011da0u, 0x80011dccu, kMain80011DA0Words },
    { 0x80011dccu, 0x80011df4u, kMain80011DCCWords },
    { 0x80011df4u, 0x80011e10u, kMain80011DF4Words },
    { 0x80011e10u, 0x80011e24u, kMain80011E10Words },
    { 0x80011e24u, 0x80011e84u, kMain80011E24Words },
    { 0x80011e84u, 0x80011eb4u, kMain80011E84Words },
    { 0x80011eb4u, 0x800120c4u, kMain80011EB4Words },
    { 0x800120c4u, 0x800120dcu, kMain800120C4Words },
    { 0x800120dcu, 0x8001212cu, kMain800120DCWords },
    { 0x8001212cu, 0x800123f0u, kMain8001212CWords },
    { 0x800123f0u, 0x80012558u, kMain800123F0Words },
    { 0x80012558u, 0x800126c4u, kMain80012558Words },
    { 0x800126c4u, 0x8001282cu, kMain800126C4Words },
    { 0x8001282cu, 0x800128b4u, kMain8001282CWords },
    { 0x800128b4u, 0x800128ecu, kMain800128B4Words },
    { 0x800128ecu, 0x800129ccu, kMain800128ECWords },
    { 0x800129ccu, 0x80012a60u, kMain800129CCWords },
    { 0x80012a60u, 0x80012ab0u, kMain80012A60Words },
    { 0x80012ab0u, 0x80012abcu, kMain80012AB0Words },
    { 0x80012abcu, 0x80012b04u, kMain80012ABCWords },
    { 0x80012b04u, 0x80012b58u, kMain80012B04Words },
    { 0x80012b58u, 0x80012c6cu, kMain80012B58Words },
    { 0x80012c6cu, 0x80012cb8u, kMain80012C6CWords },
    { 0x80012cb8u, 0x80012d0cu, kMain80012CB8Words },
    { 0x80012d0cu, 0x80012dbcu, kMain80012D0CWords },
    { 0x80012dbcu, 0x80012e0cu, kMain80012DBCWords },
    { 0x80012e0cu, 0x80012e6cu, kMain80012E0CWords },
    { 0x80012e6cu, 0x80012f74u, kMain80012E6CWords },
    { 0x80012f74u, 0x80012fc8u, kMain80012F74Words },
    { 0x80012fc8u, 0x80013028u, kMain80012FC8Words },
    { 0x80013028u, 0x800130d0u, kMain80013028Words },
    { 0x800130d0u, 0x8001311cu, kMain800130D0Words },
    { 0x8001311cu, 0x80013154u, kMain8001311CWords },
    { 0x80013154u, 0x80013200u, kMain80013154Words },
    { 0x80013200u, 0x80013228u, kMain80013200Words },
    { 0x80013228u, 0x80013294u, kMain80013228Words },
    { 0x80013294u, 0x800132bcu, kMain80013294Words },
    { 0x800132bcu, 0x80013328u, kMain800132BCWords },
    { 0x80013328u, 0x80013350u, kMain80013328Words },
    { 0x80013350u, 0x800133bcu, kMain80013350Words },
    { 0x800133bcu, 0x800133e4u, kMain800133BCWords },
    { 0x800133e4u, 0x80013450u, kMain800133E4Words },
    { 0x80013450u, 0x80013478u, kMain80013450Words },
    { 0x80013478u, 0x800134fcu, kMain80013478Words },
    { 0x800134fcu, 0x80013694u, kMain800134FCWords },
    { 0x80013694u, 0x8001382cu, kMain80013694Words },
    { 0x8001382cu, 0x800139c8u, kMain8001382CWords },
    { 0x800139c8u, 0x80013b64u, kMain800139C8Words },
    { 0x80013b64u, 0x80013cfcu, kMain80013B64Words },
    { 0x80013cfcu, 0x80013e94u, kMain80013CFCWords },
    { 0x80013e94u, 0x80013ed0u, kMain80013E94Words },
    { 0x80013ed0u, 0x80013f3cu, kMain80013ED0Words },
    { 0x80013f3cu, 0x80013f68u, kMain80013F3CWords },
    { 0x80013f68u, 0x80013f98u, kMain80013F68Words },
    { 0x80013f98u, 0x80013fbcu, kMain80013F98Words },
    { 0x80013fbcu, 0x80013fe0u, kMain80013FBCWords },
    { 0x80013fe0u, 0x80014004u, kMain80013FE0Words },
    { 0x80014004u, 0x80014028u, kMain80014004Words },
    { 0x80014028u, 0x8001404cu, kMain80014028Words },
    { 0x8001404cu, 0x80014070u, kMain8001404CWords },
    { 0x80014070u, 0x80014094u, kMain80014070Words },
    { 0x80014094u, 0x800140b8u, kMain80014094Words },
    { 0x800140b8u, 0x80014128u, kMain800140B8Words },
    { 0x80014128u, 0x80014148u, kMain80014128Words },
    { 0x80014148u, 0x80014168u, kMain80014148Words },
    { 0x80014168u, 0x800141acu, kMain80014168Words },
    { 0x800141acu, 0x800141f0u, kMain800141ACWords },
    { 0x800141f0u, 0x80014238u, kMain800141F0Words },
    { 0x80014238u, 0x800142c8u, kMain80014238Words },
    { 0x800142c8u, 0x80014338u, kMain800142C8Words },
    { 0x80014338u, 0x80014390u, kMain80014338Words },
    { 0x80014390u, 0x800143acu, kMain80014390Words },
    { 0x800143acu, 0x80014444u, kDraw800143ACWords },
    { 0x80014444u, 0x800144d4u, kSecondGeom80014444Words },
    { 0x800144d4u, 0x80014554u, kCamera800144D4Words },
    { 0x80014554u, 0x800145ecu, kSecondGeom80014554Words },
    { 0x800145ecu, 0x800146b0u, kDraw800145ECWords },
    { 0x800146b0u, 0x80014774u, kMain800146B0Words },
    { 0x80014774u, 0x800147b8u, kDrawFollowup80014774Words },
    { 0x800147b8u, 0x80014928u, kDrawFollowup800147B8Words },
    { 0x80014928u, 0x80014960u, kMain80014928Words },
    { 0x80014960u, 0x80014998u, kDrawEnv80014960Words },
    { 0x80014998u, 0x800149e0u, kDrawEnv80014998Words },
    { 0x800149e0u, 0x80014b10u, kMain800149E0Words },
    { 0x80014b10u, 0x80014bfcu, kMain80014B10Words },
    { 0x80014bfcu, 0x80014c28u, kMain80014BFCWords },
    { 0x80014c28u, 0x80014c54u, kMain80014C28Words },
    { 0x80014c54u, 0x80014cacu, kMain80014C54Words },
    { 0x80014cacu, 0x80014cf8u, kMain80014CACWords },
    { 0x80014cf8u, 0x80014d30u, kMain80014CF8Words },
    { 0x80014d30u, 0x80014d68u, kMain80014D30Words },
    { 0x80014d68u, 0x80014d94u, kMain80014D68Words },
    { 0x80014d94u, 0x80014dc0u, kMain80014D94Words },
    { 0x80014dc0u, 0x80014decu, kMain80014DC0Words },
    { 0x80014decu, 0x80014e24u, kMain80014DECWords },
    { 0x80014e24u, 0x80014e80u, kMain80014E24Words },
    { 0x80014e80u, 0x80014ed4u, kMain80014E80Words },
    { 0x80014ed4u, 0x80015018u, kMain80014ED4Words },
    { 0x80015018u, 0x80015118u, kMain80015018Words },
    { 0x80015118u, 0x8001513cu, kMain80015118Words },
    { 0x8001513cu, 0x80015144u, kMain8001513CWords },
    { 0x80015144u, 0x80015208u, kMain80015144Words },
    { 0x80015208u, 0x800152f4u, kMain80015208Words },
    { 0x800152f4u, 0x80015310u, kMain800152F4Words },
    { 0x80015310u, 0x8001534cu, kMain80015310Words },
    { 0x8001534cu, 0x800153a4u, kMain8001534CWords },
    { 0x800153a4u, 0x800153ccu, kMain800153A4Words },
    { 0x800153ccu, 0x80015424u, kMain800153CCWords },
    { 0x80015424u, 0x8001544cu, kMain80015424Words },
    { 0x8001544cu, 0x80015498u, kMain8001544CWords },
    { 0x80015498u, 0x80015608u, kMain80015498Words },
    { 0x80015608u, 0x80015760u, kMain80015608Words },
    { 0x80015760u, 0x80015908u, kMain80015760Words },
    { 0x80015908u, 0x80015954u, kMain80015908Words },
    { 0x80015954u, 0x80015978u, kMain80015954Words },
    { 0x80015978u, 0x8001599cu, kMain80015978Words },
    { 0x8001599cu, 0x800159c0u, kMain8001599CWords },
    { 0x800159c0u, 0x800159e4u, kMain800159C0Words },
    { 0x800159e4u, 0x80015a08u, kMain800159E4Words },
    { 0x80015a08u, 0x80015a2cu, kMain80015A08Words },
    { 0x80015a2cu, 0x80015a50u, kMain80015A2CWords },
    { 0x80015a50u, 0x80015a74u, kMain80015A50Words },
    { 0x80015a74u, 0x80015ad0u, kMain80015A74Words },
    { 0x80015ad0u, 0x80015b6cu, kMain80015AD0Words },
    { 0x80015b6cu, 0x80015d4cu, kMain80015B6CWords },
    { 0x80015d4cu, 0x80015f04u, kMain80015D4CWords },
    { 0x80015f04u, 0x80016110u, kMain80015F04Words },
    { 0x80016110u, 0x80016224u, kMain80016110Words },
    { 0x80016224u, 0x80016450u, kMain80016224Words },
    { 0x80016450u, 0x80016638u, kMain80016450Words },
    { 0x80016638u, 0x800166e8u, kMain80016638Words },
    { 0x800166e8u, 0x80016714u, kMain800166E8Words },
    { 0x80016714u, 0x800167b8u, kMain80016714Words },
    { 0x800167b8u, 0x800167f0u, kMain800167B8Words },
    { 0x800167f0u, 0x800168b4u, kMain800167F0Words },
    { 0x800168b4u, 0x800168c4u, kMain800168B4Words },
    { 0x800168c4u, 0x80016940u, kMain800168C4Words },
    { 0x80016940u, 0x80016978u, kMain80016940Words },
    { 0x80016978u, 0x80016a3cu, kMain80016978Words },
    { 0x80016a3cu, 0x80016a5cu, kMain80016A3CWords },
    { 0x80016a5cu, 0x80016a7cu, kMain80016A5CWords },
    { 0x80016a7cu, 0x80016b60u, kMain80016A7CWords },
    { 0x80016b60u, 0x80016c28u, kMain80016B60Words },
    { 0x80016c28u, 0x80016d78u, kMain80016C28Words },
    { 0x80016d78u, 0x80016eb0u, kMain80016D78Words },
    { 0x80016eb0u, 0x80016ed4u, kMain80016EB0Words },
    { 0x80016ed4u, 0x80016ef8u, kMain80016ED4Words },
    { 0x80016ef8u, 0x80016f18u, kMain80016EF8Words },
    { 0x80016f18u, 0x80017168u, kMain80016F18Words },
    { 0x80017168u, 0x80017254u, kMain80017168Words },
    { 0x80017254u, 0x80017274u, kMain80017254Words },
    { 0x80017274u, 0x80017294u, kMain80017274Words },
    { 0x80017294u, 0x8001739cu, kMain80017294Words },
    { 0x8001739cu, 0x800173bcu, kMain8001739CWords },
    { 0x800173bcu, 0x800173dcu, kMain800173BCWords },
    { 0x800173dcu, 0x800174dcu, kMain800173DCWords },
    { 0x800174dcu, 0x800174fcu, kMain800174DCWords },
    { 0x800174fcu, 0x8001751cu, kMain800174FCWords },
    { 0x8001751cu, 0x800176f0u, kMain8001751CWords },
    { 0x800176f0u, 0x80017714u, kMain800176F0Words },
    { 0x80017714u, 0x80017738u, kMain80017714Words },
    { 0x80017738u, 0x80017758u, kMain80017738Words },
    { 0x800183e0u, 0x80018450u, kMain800183E0Words },
    { 0x80018450u, 0x800184f0u, kMain80018450Words },
    { 0x800184f0u, 0x80018714u, kMain800184F0Words },
    { 0x80018714u, 0x80018730u, kMain80018714Words },
    { 0x80018730u, 0x80018918u, kMain80018730Words },
    { 0x80018918u, 0x800189a8u, kMain80018918Words },
    { 0x800189a8u, 0x80018a20u, kMain800189A8Words },
    { 0x80018a20u, 0x80018c64u, kMain80018A20Words },
    { 0x80018c64u, 0x80018ce8u, kMain80018C64Words },
    { 0x80018ce8u, 0x80018e78u, kMain80018CE8Words },
    { 0x80018e78u, 0x80018e9cu, kMain80018E78Words },
    { 0x80018e9cu, 0x80018f20u, kMain80018E9CWords },
    { 0x80018f20u, 0x80018f88u, kMain80018F20Words },
    { 0x80018f88u, 0x80018fc8u, kMain80018F88Words },
    { 0x80018fc8u, 0x80019018u, kMain80018FC8Words },
    { 0x80019018u, 0x80019028u, kMain80019018Words },
    { 0x80019028u, 0x8001903cu, kMain80019028Words },
    { 0x8001903cu, 0x80019064u, kMain8001903CWords },
    { 0x80019064u, 0x800190acu, kMain80019064Words },
    { 0x800190acu, 0x80019198u, kMain800190ACWords },
    { 0x80019198u, 0x800191a8u, kMain80019198Words },
    { 0x800191a8u, 0x800191bcu, kMain800191A8Words },
    { 0x800191bcu, 0x800191d4u, kMain800191BCWords },
    { 0x800191d4u, 0x8001923cu, kMain800191D4Words },
    { 0x8001923cu, 0x8001931cu, kMain8001923CWords },
    { 0x8001931cu, 0x80019378u, kMain8001931CWords },
    { 0x80019378u, 0x80019388u, kMain80019378Words },
    { 0x80019388u, 0x80019398u, kMain80019388Words },
    { 0x80019398u, 0x800193a8u, kMain80019398Words },
    { 0x800193a8u, 0x800193b8u, kMain800193A8Words },
    { 0x800193b8u, 0x8001971cu, kMain800193B8Words },
    { 0x8001a0fcu, 0x8001a114u, kMain8001A0FCWords },
    { 0x8001a114u, 0x8001a338u, kMain8001A114Words },
    { 0x8001a338u, 0x8001a9d8u, kMain8001A338Words },
    { 0x8001a9d8u, 0x8001a9f8u, kMain8001A9D8Words },
    { 0x8001a9f8u, 0x8001aa78u, kMain8001A9F8Words },
    { 0x8001aa78u, 0x8001aa88u, kMain8001AA78Words },
    { 0x8001aa88u, 0x8001aa98u, kMain8001AA88Words },
    { 0x8001aa98u, 0x8001aaa0u, kMain8001AA98Words },
    { 0x8001aaa0u, 0x8001aad0u, kMain8001AAA0Words },
    { 0x8001aad0u, 0x8001abb4u, kMain8001AAD0Words },
    { 0x8001abb4u, 0x8001abbcu, kMain8001ABB4Words },
    { 0x8001abbcu, 0x8001acf0u, kMain8001ABBCWords },
    { 0x8001acf0u, 0x8001ae90u, kMain8001ACF0Words },
    { 0x8001ae90u, 0x8001af04u, kMain8001AE90Words },
    { 0x8001af04u, 0x8001af34u, kMain8001AF04Words },
    { 0x8001af34u, 0x8001b0d4u, kMain8001AF34Words },
    { 0x8001b0d4u, 0x8001b22cu, kMain8001B0D4Words },
    { 0x8001b22cu, 0x8001b23cu, kMain8001B22CWords },
    { 0x8001b23cu, 0x8001b26cu, kMain8001B23CWords },
    { 0x8001b26cu, 0x8001b324u, kMain8001B26CWords },
    { 0x8001b324u, 0x8001b34cu, kMain8001B324Words },
    { 0x8001b34cu, 0x8001b374u, kMain8001B34CWords },
    { 0x8001b374u, 0x8001b384u, kMain8001B374Words },
    { 0x8001b384u, 0x8001b394u, kMain8001B384Words },
    { 0x8001b394u, 0x8001b3c4u, kMain8001B394Words },
    { 0x8001b3c4u, 0x8001b710u, kMain8001B3C4Words },
    { 0x8001b710u, 0x8001b788u, kMain8001B710Words },
    { 0x8001b788u, 0x8001b7c4u, kMain8001B788Words },
    { 0x8001b7c4u, 0x8001b85cu, kMain8001B7C4Words },
    { 0x8001b85cu, 0x8001b86cu, kMain8001B85CWords },
    { 0x8001b86cu, 0x8001ba84u, kMain8001B86CWords },
    { 0x8001ba84u, 0x8001badcu, kMain8001BA84Words },
    { 0x8001badcu, 0x8001bb60u, kMain8001BADCWords },
    { 0x8001bb60u, 0x8001bbbcu, kMain8001BB60Words },
    { 0x8001bbbcu, 0x8001bc6cu, kMain8001BBBCWords },
    { 0x8001bc6cu, 0x8001bd80u, kMain8001BC6CWords },
    { 0x8001bd80u, 0x8001bda0u, kMain8001BD80Words },
    { 0x8001bda0u, 0x8001be20u, kMain8001BDA0Words },
    { 0x8001be20u, 0x8001be30u, kMain8001BE20Words },
    { 0x8001be30u, 0x8001bfa0u, kMain8001BE30Words },
    { 0x8001bfa0u, 0x8001bfb0u, kMain8001BFA0Words },
    { 0x8001bfb0u, 0x8001bfd0u, kMain8001BFB0Words },
    { 0x8001bfd0u, 0x8001bfe8u, kMain8001BFD0Words },
    { 0x8001bfe8u, 0x8001bff8u, kMain8001BFE8Words },
    { 0x8001bff8u, 0x8001c00cu, kMain8001BFF8Words },
    { 0x8001c00cu, 0x8001c044u, kMain8001C00CWords },
    { 0x8001c044u, 0x8001c0c8u, kMain8001C044Words },
    { 0x8001c0c8u, 0x8001c14cu, kMain8001C0C8Words },
    { 0x8001c14cu, 0x8001c1e4u, kMain8001C14CWords },
    { 0x8001c1e4u, 0x8001c214u, kMain8001C1E4Words },
    { 0x8001c214u, 0x8001c2c4u, kMain8001C214Words },
    { 0x8001c2c4u, 0x8001c320u, kMain8001C2C4Words },
    { 0x8001c320u, 0x8001c448u, kMain8001C320Words },
    { 0x8001c448u, 0x8001c4a4u, kMain8001C448Words },
    { 0x8001c4a4u, 0x8001c558u, kMain8001C4A4Words },
    { 0x8001c558u, 0x8001c5b8u, kMain8001C558Words },
    { 0x8001c5b8u, 0x8001c6e4u, kMain8001C5B8Words },
    { 0x8001c6e4u, 0x8001c744u, kMain8001C6E4Words },
    { 0x8001c744u, 0x8001c7b0u, kMain8001C744Words },
    { 0x8001c7b0u, 0x8001c810u, kMain8001C7B0Words },
    { 0x8001c810u, 0x8001c8c4u, kMain8001C810Words },
    { 0x8001c8c4u, 0x8001c924u, kMain8001C8C4Words },
    { 0x8001c924u, 0x8001c97cu, kMain8001C924Words },
    { 0x8001c97cu, 0x8001c9d0u, kMain8001C97CWords },
    { 0x8001c9d0u, 0x8001ca1cu, kMain8001C9D0Words },
    { 0x8001ca1cu, 0x8001ca88u, kMain8001CA1CWords },
    { 0x8001ca88u, 0x8001cb00u, kMain8001CA88Words },
    { 0x8001cb00u, 0x8001cb6cu, kMain8001CB00Words },
    { 0x8001cb6cu, 0x8001cbdcu, kMain8001CB6CWords },
    { 0x8001cbdcu, 0x8001cc3cu, kMain8001CBDCWords },
    { 0x8001cc3cu, 0x8001cca0u, kMain8001CC3CWords },
    { 0x8001cca0u, 0x8001cd04u, kMain8001CCA0Words },
    { 0x8001cd04u, 0x8001cd50u, kMain8001CD04Words },
    { 0x8001cd50u, 0x8001cd9cu, kMain8001CD50Words },
    { 0x8001cd9cu, 0x8001cde8u, kMain8001CD9CWords },
    { 0x8001cde8u, 0x8001ce28u, kMain8001CDE8Words },
    { 0x8001ce28u, 0x8001ce68u, kMain8001CE28Words },
    { 0x8001ce68u, 0x8001cec0u, kMain8001CE68Words },
    { 0x8001cec0u, 0x8001cf00u, kMain8001CEC0Words },
    { 0x8001cf00u, 0x8001cf30u, kMain8001CF00Words },
    { 0x8001cf30u, 0x8001cf48u, kMain8001CF30Words },
    { 0x8001cf48u, 0x8001cfb8u, kMain8001CF48Words },
    { 0x8001cfb8u, 0x8001cfdcu, kMain8001CFB8Words },
    { 0x8001cfdcu, 0x8001d050u, kMain8001CFDCWords },
    { 0x8001d050u, 0x8001d074u, kMain8001D050Words },
    { 0x8001d074u, 0x8001d0e8u, kMain8001D074Words },
    { 0x8001d0e8u, 0x8001d0f4u, kMain8001D0E8Words },
    { 0x8001d0f4u, 0x8001d130u, kMain8001D0F4Words },
    { 0x8001d130u, 0x8001d150u, kMain8001D130Words },
    { 0x8001d150u, 0x8001d16cu, kMain8001D150Words },
    { 0x8001d16cu, 0x8001d1c4u, kMain8001D16CWords },
    { 0x8001d1c4u, 0x8001d388u, kMain8001D1C4Words },
    { 0x8001d388u, 0x8001d3fcu, kMain8001D388Words },
    { 0x8001d3fcu, 0x8001d70cu, kMain8001D3FCWords },
    { 0x8001d70cu, 0x8001d8c4u, kMain8001D70CWords },
    { 0x8001d8c4u, 0x8001da34u, kMain8001D8C4Words },
    { 0x8001da34u, 0x8001e094u, kMain8001DA34Words },
    { 0x8001e094u, 0x8001e378u, kMain8001E094Words },
    { 0x8001e378u, 0x8001e668u, kMain8001E378Words },
    { 0x8001e668u, 0x8001e7e0u, kMain8001E668Words },
    { 0x8001e7e0u, 0x8001ea14u, kMain8001E7E0Words },
    { 0x8001ea14u, 0x8001efe0u, kMain8001EA14Words },
    { 0x8001efe0u, 0x8001f730u, kMain8001EFE0Words },
    { 0x8001f730u, 0x8001f974u, kMain8001F730Words },
    { 0x8001f974u, 0x8001f97cu, kMain8001F974Words },
    { 0x8001f97cu, 0x8001f9f8u, kMain8001F97CWords },
    { 0x8001f9f8u, 0x8001fb8cu, kMain8001F9F8Words },
    { 0x8001fb8cu, 0x8001fc08u, kMain8001FB8CWords },
    { 0x8001fc08u, 0x80020248u, kMain8001FC08Words },
    { 0x80020248u, 0x80020598u, kMain80020248Words },
    { 0x80020598u, 0x80020a28u, kMain80020598Words },
    { 0x80020a28u, 0x80020da4u, kMain80020A28Words },
    { 0x80020da4u, 0x80020f34u, kMain80020DA4Words },
    { 0x80020f34u, 0x80021008u, kMain80020F34Words },
    { 0x80021008u, 0x80021050u, kMain80021008Words },
    { 0x80021050u, 0x8002109cu, kMain80021050Words },
    { 0x8002109cu, 0x80021120u, kMain8002109CWords },
    { 0x80021120u, 0x80021174u, kMain80021120Words },
    { 0x80021174u, 0x80021284u, kMain80021174Words },
    { 0x80021284u, 0x800215f4u, kMain80021284Words },
    { 0x800215f4u, 0x80021d38u, kMain800215F4Words },
    { 0x80021d38u, 0x800221a8u, kMain80021D38Words },
    { 0x800221a8u, 0x800226c0u, kMain800221A8Words },
    { 0x800226c0u, 0x80023138u, kMain800226C0Words },
    { 0x80023138u, 0x800233ccu, kMain80023138Words },
    { 0x800233ccu, 0x800234e4u, kMain800233CCWords },
    { 0x800234e4u, 0x80023570u, kMain800234E4Words },
    { 0x80023570u, 0x8002374cu, kMain80023570Words },
    { 0x8002374cu, 0x80023bf0u, kMain8002374CWords },
    { 0x80023bf0u, 0x80024054u, kMain80023BF0Words },
    { 0x80024054u, 0x800241c0u, kMain80024054Words },
    { 0x800241c0u, 0x800242d0u, kMain800241C0Words },
    { 0x800242d0u, 0x800243ecu, kMain800242D0Words },
    { 0x800243ecu, 0x80024448u, kMain800243ECWords },
    { 0x80024448u, 0x800249f0u, kMain80024448Words },
    { 0x800249f0u, 0x80024bc0u, kMain800249F0Words },
    { 0x80024bc0u, 0x80024de8u, kMain80024BC0Words },
    { 0x80024de8u, 0x80025000u, kMain80024DE8Words },
    { 0x80025000u, 0x8002528cu, kMain80025000Words },
    { 0x8002528cu, 0x80025504u, kMain8002528CWords },
    { 0x80025504u, 0x80025818u, kMain80025504Words },
    { 0x80025818u, 0x80025a30u, kMain80025818Words },
    { 0x80025a30u, 0x80025cbcu, kMain80025A30Words },
    { 0x80025cbcu, 0x80025eb8u, kMain80025CBCWords },
    { 0x80025eb8u, 0x80026128u, kMain80025EB8Words },
    { 0x80026128u, 0x800262d8u, kMain80026128Words },
    { 0x800262d8u, 0x80026514u, kMain800262D8Words },
    { 0x80026514u, 0x800268d0u, kMain80026514Words },
    { 0x800268d0u, 0x80026d64u, kMain800268D0Words },
    { 0x80026d64u, 0x80027058u, kMain80026D64Words },
    { 0x80027058u, 0x80027200u, kMain80027058Words },
    { 0x80027200u, 0x800273f4u, kMain80027200Words },
    { 0x800273f4u, 0x800275bcu, kMain800273F4Words },
    { 0x800275bcu, 0x800277dcu, kMain800275BCWords },
    { 0x800277dcu, 0x800279acu, kMain800277DCWords },
    { 0x800279acu, 0x80027bf0u, kMain800279ACWords },
    { 0x80027bf0u, 0x80027c10u, kMain80027BF0Words },
    { 0x80027c10u, 0x80027d20u, kMain80027C10Words },
    { 0x80027d20u, 0x80027f4cu, kMain80027D20Words },
    { 0x80027f4cu, 0x80028200u, kMain80027F4CWords },
    { 0x80028200u, 0x80028234u, kMain80028200Words },
    { 0x80028234u, 0x8002823cu, kMain80028234Words },
    { 0x8002823cu, 0x80028304u, kSecondGeom8002823CWords },
    { 0x80028304u, 0x80028394u, kMain80028304Words },
    { 0x80028394u, 0x80028428u, kMain80028394Words },
    { 0x80028428u, 0x80028488u, kMain80028428Words },
    { 0x80028488u, 0x8002850cu, kMain80028488Words },
    { 0x8002850cu, 0x80028558u, kSecondGeom8002850CWords },
    { 0x80028558u, 0x800285acu, kMain80028558Words },
    { 0x800285acu, 0x800285ccu, kMain800285ACWords },
    { 0x800285ccu, 0x80028620u, kMain800285CCWords },
    { 0x80028620u, 0x80028694u, kSecondGeom80028620Words },
    { 0x80028694u, 0x80028a30u, kMain80028694Words },
    { 0x80028a30u, 0x80028a38u, kMain80028A30Words },
    { 0x80028a38u, 0x80028a40u, kMain80028A38Words },
    { 0x80028a40u, 0x80028a48u, kMain80028A40Words },
    { 0x80028a48u, 0x80028c50u, kMain80028A48Words },
    { 0x80028c50u, 0x80028d58u, kMain80028C50Words },
    { 0x80028d58u, 0x80028d78u, kMain80028D58Words },
    { 0x80028d78u, 0x80028d9cu, kMain80028D78Words },
    { 0x80028d9cu, 0x80028dbcu, kMain80028D9CWords },
    { 0x80028dbcu, 0x80028de0u, kMain80028DBCWords },
    { 0x80028de0u, 0x80028e00u, kMain80028DE0Words },
    { 0x80028e00u, 0x80028e24u, kMain80028E00Words },
    { 0x80028e24u, 0x80028e44u, kMain80028E24Words },
    { 0x80028e44u, 0x80028e68u, kMain80028E44Words },
    { 0x80028e68u, 0x80028e88u, kMain80028E68Words },
    { 0x80028e88u, 0x80028eacu, kMain80028E88Words },
    { 0x80028eacu, 0x80028eccu, kMain80028EACWords },
    { 0x80028eccu, 0x80028ef0u, kMain80028ECCWords },
    { 0x80028ef0u, 0x80028f10u, kMain80028EF0Words },
    { 0x80028f10u, 0x80028f34u, kMain80028F10Words },
    { 0x80028f34u, 0x80028f54u, kMain80028F34Words },
    { 0x80028f54u, 0x80028f78u, kMain80028F54Words },
    { 0x80028f78u, 0x80028f98u, kMain80028F78Words },
    { 0x80028f98u, 0x80028fbcu, kMain80028F98Words },
    { 0x80028fbcu, 0x80028fdcu, kMain80028FBCWords },
    { 0x80028fdcu, 0x80029000u, kMain80028FDCWords },
    { 0x80029000u, 0x80029020u, kMain80029000Words },
    { 0x80029020u, 0x80029044u, kMain80029020Words },
    { 0x80029044u, 0x8002906cu, kMain80029044Words },
    { 0x8002906cu, 0x80029094u, kMain8002906CWords },
    { 0x80029094u, 0x800290bcu, kMain80029094Words },
    { 0x800290bcu, 0x800290e0u, kMain800290BCWords },
    { 0x800290e0u, 0x80029104u, kMain800290E0Words },
    { 0x80029104u, 0x80029124u, kMain80029104Words },
    { 0x80029124u, 0x80029178u, kMain80029124Words },
    { 0x80029178u, 0x800291a0u, kMain80029178Words },
    { 0x800291a0u, 0x800291b4u, kMain800291A0Words },
    { 0x800291b4u, 0x800291c8u, kMain800291B4Words },
    { 0x800291c8u, 0x800291dcu, kMain800291C8Words },
    { 0x800291dcu, 0x800291f0u, kMain800291DCWords },
    { 0x800291f0u, 0x80029204u, kMain800291F0Words },
    { 0x80029204u, 0x80029218u, kMain80029204Words },
    { 0x80029218u, 0x80029240u, kMain80029218Words },
    { 0x80029240u, 0x80029254u, kMain80029240Words },
    { 0x80029254u, 0x80029264u, kMain80029254Words },
    { 0x80029264u, 0x80029274u, kMain80029264Words },
    { 0x80029274u, 0x8002931cu, kMain80029274Words },
    { 0x8002931cu, 0x80029344u, kMain8002931CWords },
    { 0x80029344u, 0x8002941cu, kMain80029344Words },
    { 0x8002941cu, 0x80029444u, kMain8002941CWords },
    { 0x80029444u, 0x80029504u, kMain80029444Words },
    { 0x80029504u, 0x80029514u, kMain80029504Words },
    { 0x80029514u, 0x80029524u, kMain80029514Words },
    { 0x80029524u, 0x8002953cu, kMain80029524Words },
    { 0x8002953cu, 0x8002954cu, kMain8002953CWords },
    { 0x8002954cu, 0x8002955cu, kMain8002954CWords },
    { 0x8002955cu, 0x8002957cu, kMain8002955CWords },
    { 0x8002957cu, 0x8002958cu, kMain8002957CWords },
    { 0x8002958cu, 0x8002959cu, kMain8002958CWords },
    { 0x8002959cu, 0x800295d4u, kMain8002959CWords },
    { 0x800295d4u, 0x80029664u, kMain800295D4Words },
    { 0x80029664u, 0x80029690u, kMain80029664Words },
    { 0x80029690u, 0x800296f8u, kMain80029690Words },
    { 0x800296f8u, 0x80029774u, kMain800296F8Words },
    { 0x80029774u, 0x800298bcu, kMain80029774Words },
    { 0x800298bcu, 0x8002992cu, kMain800298BCWords },
    { 0x8002992cu, 0x80029a58u, kMain8002992CWords },
    { 0x80029a58u, 0x80029a94u, kMain80029A58Words },
    { 0x80029a94u, 0x80029aacu, kMain80029A94Words },
    { 0x80029aacu, 0x80029af4u, kMain80029AACWords },
    { 0x80029af4u, 0x80029b4cu, kMain80029AF4Words },
    { 0x80029b4cu, 0x80029bc8u, kMain80029B4CWords },
    { 0x80029bc8u, 0x80029c44u, kMain80029BC8Words },
    { 0x80029c44u, 0x80029cd4u, kMain80029C44Words },
    { 0x80029cd4u, 0x80029d3cu, kMain80029CD4Words },
    { 0x80029d3cu, 0x80029db4u, kMain80029D3CWords },
    { 0x80029db4u, 0x80029e30u, kMain80029DB4Words },
    { 0x80029e30u, 0x80029e94u, kMain80029E30Words },
    { 0x80029e94u, 0x80029ec0u, kMain80029E94Words },
    { 0x80029ec0u, 0x80029ed4u, kMain80029EC0Words },
    { 0x80029ed4u, 0x80029fd4u, kMain80029ED4Words },
    { 0x80029fd4u, 0x80029fe4u, kMain80029FD4Words },
    { 0x80029fe4u, 0x8002a04cu, kMain80029FE4Words },
    { 0x8002a04cu, 0x8002a088u, kMain8002A04CWords },
    { 0x8002a088u, 0x8002a108u, kMain8002A088Words },
    { 0x8002a108u, 0x8002a1b4u, kMain8002A108Words },
    { 0x8002a1b4u, 0x8002a200u, kMain8002A1B4Words },
    { 0x8002a200u, 0x8002a234u, kMain8002A200Words },
    { 0x8002a234u, 0x8002a26cu, kMain8002A234Words },
    { 0x8002a26cu, 0x8002a27cu, kMain8002A26CWords },
    { 0x8002a27cu, 0x8002a28cu, kMain8002A27CWords },
    { 0x8002a28cu, 0x8002a2b0u, kMain8002A28CWords },
    { 0x8002a2b0u, 0x8002a2d4u, kMain8002A2B0Words },
    { 0x8002a2d4u, 0x8002a354u, kMain8002A2D4Words },
    { 0x8002a354u, 0x8002a400u, kMain8002A354Words },
    { 0x8002a400u, 0x8002a44cu, kMain8002A400Words },
    { 0x8002a44cu, 0x8002a480u, kMain8002A44CWords },
    { 0x8002a480u, 0x8002a4b8u, kMain8002A480Words },
    { 0x8002a4b8u, 0x8002a4c8u, kMain8002A4B8Words },
    { 0x8002a4c8u, 0x8002a4d8u, kMain8002A4C8Words },
    { 0x8002a4d8u, 0x8002a4fcu, kMain8002A4D8Words },
    { 0x8002a4fcu, 0x8002a520u, kMain8002A4FCWords },
    { 0x8002a520u, 0x8002a544u, kMain8002A520Words },
    { 0x8002a544u, 0x8002a5c4u, kMain8002A544Words },
    { 0x8002a5c4u, 0x8002a670u, kMain8002A5C4Words },
    { 0x8002a670u, 0x8002a6bcu, kMain8002A670Words },
    { 0x8002a6bcu, 0x8002a6f0u, kMain8002A6BCWords },
    { 0x8002a6f0u, 0x8002a728u, kMain8002A6F0Words },
    { 0x8002a728u, 0x8002a738u, kMain8002A728Words },
    { 0x8002a738u, 0x8002a748u, kMain8002A738Words },
    { 0x8002a748u, 0x8002a76cu, kMain8002A748Words },
    { 0x8002a76cu, 0x8002a790u, kMain8002A76CWords },
    { 0x8002a790u, 0x8002a7b4u, kMain8002A790Words },
    { 0x8002a7b4u, 0x8002a834u, kMain8002A7B4Words },
    { 0x8002a834u, 0x8002a8e0u, kMain8002A834Words },
    { 0x8002a8e0u, 0x8002a92cu, kMain8002A8E0Words },
    { 0x8002a92cu, 0x8002a960u, kMain8002A92CWords },
    { 0x8002a960u, 0x8002a998u, kMain8002A960Words },
    { 0x8002a998u, 0x8002a9a8u, kMain8002A998Words },
    { 0x8002a9a8u, 0x8002a9b8u, kMain8002A9A8Words },
    { 0x8002a9b8u, 0x8002a9dcu, kMain8002A9B8Words },
    { 0x8002a9dcu, 0x8002aa00u, kMain8002A9DCWords },
    { 0x8002aa00u, 0x8002aa3cu, kMain8002AA00Words },
    { 0x8002aa3cu, 0x8002aaacu, kMain8002AA3CWords },
    { 0x8002aaacu, 0x8002aab4u, kMain8002AAACWords },
    { 0x8002aab4u, 0x8002ab64u, kMain8002AAB4Words },
    { 0x8002ab64u, 0x8002ac00u, kMain8002AB64Words },
    { 0x8002ac00u, 0x8002ac98u, kMain8002AC00Words },
    { 0x8002ac98u, 0x8002ae60u, kMain8002AC98Words },
    { 0x8002ae60u, 0x8002aed0u, kMain8002AE60Words },
    { 0x8002aed0u, 0x8002aee4u, kMain8002AED0Words },
    { 0x8002aee4u, 0x8002aef8u, kMain8002AEE4Words },
    { 0x8002aef8u, 0x8002af08u, kMain8002AEF8Words },
    { 0x8002af08u, 0x8002af18u, kMain8002AF08Words },
    { 0x8002af18u, 0x8002af48u, kMain8002AF18Words },
    { 0x8002af48u, 0x8002af60u, kMain8002AF48Words },
    { 0x8002af60u, 0x8002af70u, kMain8002AF60Words },
    { 0x8002af70u, 0x8002b00cu, kMain8002AF70Words },
    { 0x8002b00cu, 0x8002b064u, kMain8002B00CWords },
    { 0x8002b064u, 0x8002b08cu, kMain8002B064Words },
    { 0x8002b08cu, 0x8002b0b4u, kMain8002B08CWords },
    { 0x8002b0b4u, 0x8002c320u, kMain8002B0B4Words },
    { 0x8002c320u, 0x8002c3b0u, kMain8002C320Words },
    { 0x8002c3b0u, 0x8002c410u, kMain8002C3B0Words },
    { 0x8002c410u, 0x8002c8bcu, kMain8002C410Words },
    { 0x8002cdd8u, 0x8002cfe4u, kMain8002CDD8Words },
    { 0x8002cfe4u, 0x8002d034u, kMain8002CFE4Words },
    { 0x8002d034u, 0x8002d1f0u, kMain8002D034Words },
    { 0x8002d240u, 0x8002d29cu, kMain8002D240Words },
    { 0x8002d29cu, 0x8002d320u, kMain8002D29CWords },
    { 0x8002d320u, 0x8002d4b8u, kMain8002D320Words },
    { 0x8002d4b8u, 0x8002d4c8u, kMain8002D4B8Words },
    { 0x8002d4c8u, 0x8002d59cu, kMain8002D4C8Words },
    { 0x8002d59cu, 0x8002d678u, kMain8002D59CWords },
    { 0x8002d678u, 0x8002d6d8u, kMain8002D678Words },
    { 0x8002d6d8u, 0x8002d7f4u, kMain8002D6D8Words },
    { 0x8002d7f4u, 0x8002d7fcu, kMain8002D7F4Words },
    { 0x8002d7fcu, 0x8002d80cu, kMain8002D7FCWords },
    { 0x8002d80cu, 0x8002d834u, kMain8002D80CWords },
    { 0x8002d834u, 0x8002d844u, kMain8002D834Words },
    { 0x8002d844u, 0x8002d858u, kMain8002D844Words },
    { 0x8002d858u, 0x8002d8a8u, kMain8002D858Words },
    { 0x8002d8a8u, 0x8002d8d4u, kMain8002D8A8Words },
    { 0x8002d8d4u, 0x8002d904u, kMain8002D8D4Words },
    { 0x8002d904u, 0x8002dc68u, kMain8002D904Words },
    { 0x8002dc68u, 0x8002df80u, kMain8002DC68Words },
    { 0x8002df80u, 0x8002e138u, kMain8002DF80Words },
    { 0x8002e138u, 0x8002e5bcu, kMain8002E138Words },
    { 0x8002e5bcu, 0x8002e5f8u, kMain8002E5BCWords },
    { 0x8002e5f8u, 0x8002e638u, kMain8002E5F8Words },
    { 0x8002e638u, 0x8002e700u, kMain8002E638Words },
    { 0x8002e700u, 0x8002e79cu, kMain8002E700Words },
    { 0x8002e79cu, 0x8002e818u, kMain8002E79CWords },
    { 0x8002e818u, 0x8002e8dcu, kMain8002E818Words },
    { 0x8002e8dcu, 0x8002e94cu, kMain8002E8DCWords },
    { 0x8002e94cu, 0x8002ea10u, kMain8002E94CWords },
    { 0x8002ea10u, 0x8002eab0u, kMain8002EA10Words },
    { 0x8002eab0u, 0x8002eb10u, kMain8002EAB0Words },
    { 0x8002eb10u, 0x8002ebacu, kMain8002EB10Words },
    { 0x8002ebacu, 0x8002ec10u, kMain8002EBACWords },
    { 0x8002ec10u, 0x8002ed90u, kMain8002EC10Words },
    { 0x8002ed90u, 0x8002ede4u, kMain8002ED90Words },
    { 0x8002ede4u, 0x8002ee64u, kMain8002EDE4Words },
    { 0x8002ee64u, 0x8002ee90u, kMain8002EE64Words },
    { 0x8002ee90u, 0x8002eeb8u, kMain8002EE90Words },
    { 0x8002eeb8u, 0x8002eed8u, kMain8002EEB8Words },
    { 0x8002eed8u, 0x8002efd0u, kMain8002EED8Words },
    { 0x8002efd0u, 0x8002eff8u, kMain8002EFD0Words },
    { 0x8002eff8u, 0x8002f064u, kMain8002EFF8Words },
    { 0x8002f064u, 0x8002f0d0u, kMain8002F064Words },
    { 0x8002f0d0u, 0x8002f0f4u, kMain8002F0D0Words },
    { 0x8002f0f4u, 0x8002f12cu, kMain8002F0F4Words },
    { 0x8002f12cu, 0x8002f150u, kMain8002F12CWords },
    { 0x8002f150u, 0x8002f1ccu, kMain8002F150Words },
    { 0x8002f1ccu, 0x8002f248u, kMain8002F1CCWords },
    { 0x8002f248u, 0x8002f4e4u, kMain8002F248Words },
    { 0x8002f4e4u, 0x8002f5c8u, kMain8002F4E4Words },
    { 0x8002f5c8u, 0x8002f620u, kMain8002F5C8Words },
    { 0x8002f620u, 0x8002f648u, kMain8002F620Words },
    { 0x8002f648u, 0x8002f658u, kMain8002F648Words },
    { 0x8002f658u, 0x8002f67cu, kMain8002F658Words },
    { 0x8002f67cu, 0x8002f714u, kMain8002F67CWords },
    { 0x8002f714u, 0x8002f80cu, kMain8002F714Words },
    { 0x8002f80cu, 0x8002fa3cu, kMain8002F80CWords },
    { 0x8002fa3cu, 0x8002fae0u, kMain8002FA3CWords },
    { 0x8002fb08u, 0x8002fc64u, kMain8002FB08Words },
    { 0x8002fc64u, 0x8002fd14u, kMain8002FC64Words },
    { 0x8002fd14u, 0x8002fdc8u, kMain8002FD14Words },
    { 0x8002fdc8u, 0x8002fde8u, kMain8002FDC8Words },
    { 0x8002fde8u, 0x8002ff0cu, kMain8002FDE8Words },
    { 0x8002ff0cu, 0x800301a4u, kMain8002FF0CWords },
    { 0x800301a4u, 0x800301c8u, kMain800301A4Words },
    { 0x800301c8u, 0x80030470u, kMain800301C8Words },
    { 0x80030470u, 0x800304c8u, kMain80030470Words },
    { 0x800304c8u, 0x80030538u, kMain800304C8Words },
    { 0x80030538u, 0x80030604u, kMain80030538Words },
    { 0x80030604u, 0x80030634u, kMain80030604Words },
    { 0x80030634u, 0x80030730u, kMain80030634Words },
    { 0x80030730u, 0x80030a14u, kMain80030730Words },
    { 0x80030a14u, 0x80030ca4u, kMain80030A14Words },
    { 0x80030ca4u, 0x80030d80u, kMain80030CA4Words },
    { 0x80030d80u, 0x80030f80u, kMain80030D80Words },
    { 0x80030f80u, 0x800314dcu, kMain80030F80Words },
    { 0x800314dcu, 0x800316f8u, kMain800314DCWords },
    { 0x800316f8u, 0x80031988u, kMain800316F8Words },
    { 0x80031988u, 0x80031a98u, kMain80031988Words },
    { 0x80031a98u, 0x80031b7cu, kMain80031A98Words },
    { 0x80031b7cu, 0x80031be0u, kMain80031B7CWords },
    { 0x80031be0u, 0x80031cc8u, kMain80031BE0Words },
    { 0x80031cc8u, 0x80031d70u, kMain80031CC8Words },
    { 0x80031d70u, 0x80031decu, kMain80031D70Words },
    { 0x80031decu, 0x80031e94u, kMain80031DECWords },
    { 0x80031e94u, 0x80031f14u, kMain80031E94Words },
    { 0x80031f14u, 0x80031fc8u, kMain80031F14Words },
    { 0x80031fc8u, 0x80032048u, kMain80031FC8Words },
    { 0x80032048u, 0x800322a8u, kMain80032048Words },
    { 0x800322a8u, 0x800324a4u, kMain800322A8Words },
    { 0x800324a4u, 0x80032774u, kMain800324A4Words },
    { 0x80032774u, 0x80032a74u, kMain80032774Words },
    { 0x80032a74u, 0x8003310cu, kMain80032A74Words },
    { 0x8003310cu, 0x800331d4u, kMain8003310CWords },
    { 0x800331d4u, 0x8003324cu, kMain800331D4Words },
    { 0x8003324cu, 0x80033324u, kMain8003324CWords },
    { 0x80033324u, 0x80033398u, kMain80033324Words },
    { 0x80033398u, 0x8003350cu, kMain80033398Words },
    { 0x8003350cu, 0x800335b8u, kMain8003350CWords },
    { 0x800335b8u, 0x800336a8u, kMain800335B8Words },
    { 0x800336a8u, 0x8003388cu, kMain800336A8Words },
    { 0x8003388cu, 0x800342e8u, kMain8003388CWords },
    { 0x800342e8u, 0x80034314u, kMain800342E8Words },
    { 0x80034314u, 0x80034650u, kMain80034314Words },
    { 0x80034650u, 0x800346d0u, kMain80034650Words },
    { 0x800346d0u, 0x800347c8u, kMain800346D0Words },
    { 0x800347c8u, 0x80034844u, kMain800347C8Words },
    { 0x80034844u, 0x800348a8u, kMain80034844Words },
    { 0x800348a8u, 0x8003491cu, kMain800348A8Words },
    { 0x8003491cu, 0x80034a54u, kMain8003491CWords },
    { 0x80034a54u, 0x80034a9cu, kMain80034A54Words },
    { 0x80034a9cu, 0x80034ae0u, kMain80034A9CWords },
    { 0x80034ae0u, 0x80034b0cu, kMain80034AE0Words },
    { 0x80034b0cu, 0x80034b3cu, kMain80034B0CWords },
    { 0x80034b3cu, 0x80034b98u, kMain80034B3CWords },
    { 0x80034cf0u, 0x80034dfcu, kMain80034CF0Words },
    { 0x80034dfcu, 0x8003500cu, kMain80034DFCWords },
    { 0x8003500cu, 0x800351e8u, kMain8003500CWords },
    { 0x800351e8u, 0x80035210u, kMain800351E8Words },
    { 0x80035210u, 0x80035270u, kMain80035210Words },
    { 0x80035270u, 0x800359b0u, kMain80035270Words },
    { 0x800359b0u, 0x80035c4cu, kMain800359B0Words },
    { 0x80035c4cu, 0x8003602cu, kMain80035C4CWords },
    { 0x8003602cu, 0x80036130u, kMain8003602CWords },
    { 0x80036130u, 0x800361ccu, kMain80036130Words },
    { 0x800361ccu, 0x8003621cu, kMain800361CCWords },
    { 0x8003621cu, 0x80036260u, kMain8003621CWords },
    { 0x80036260u, 0x800363ccu, kMain80036260Words },
    { 0x800363ccu, 0x80036af8u, kMain800363CCWords },
    { 0x80036af8u, 0x80036d24u, kMain80036AF8Words },
    { 0x80036d24u, 0x80036d58u, kMain80036D24Words },
    { 0x80036d58u, 0x80036eb4u, kMain80036D58Words },
    { 0x80036eb4u, 0x80036ee8u, kMain80036EB4Words },
    { 0x80036ee8u, 0x80036f18u, kMain80036EE8Words },
    { 0x80036f18u, 0x80036f98u, kMain80036F18Words },
    { 0x80036f98u, 0x80036fb0u, kMain80036F98Words },
    { 0x80036fb0u, 0x80037004u, kMain80036FB0Words },
    { 0x80037144u, 0x80037334u, kMain80037144Words },
    { 0x80037334u, 0x80037358u, kMain80037334Words },
    { 0x80037358u, 0x80037368u, kMain80037358Words },
    { 0x80037368u, 0x800373d0u, kMain80037368Words },
    { 0x800373d0u, 0x800374ccu, kMain800373D0Words },
    { 0x800374ccu, 0x8003750cu, kMain800374CCWords },
    { 0x8003750cu, 0x8003775cu, kMain8003750CWords },
    { 0x8003775cu, 0x800377d8u, kMain8003775CWords },
    { 0x800377d8u, 0x80037cc8u, kMain800377D8Words },
    { 0x80037cd8u, 0x80037d74u, kMain80037CD8Words },
    { 0x80037d74u, 0x80037d98u, kMain80037D74Words },
    { 0x80037fc4u, 0x8003819cu, kMain80037FC4Words },
    { 0x8003819cu, 0x800381e4u, kMain8003819CWords },
    { 0x800381e4u, 0x80038210u, kMain800381E4Words },
    { 0x80038210u, 0x80038308u, kMain80038210Words },
    { 0x80038308u, 0x8003834cu, kMain80038308Words },
    { 0x8003834cu, 0x8003836cu, kMain8003834CWords },
    { 0x8003836cu, 0x800383a4u, kMain8003836CWords },
    { 0x800383a4u, 0x800384a8u, kMain800383A4Words },
    { 0x800384a8u, 0x800385c0u, kMain800384A8Words },
    { 0x800385c0u, 0x80038638u, kMain800385C0Words },
    { 0x80038638u, 0x80038668u, kMain80038638Words },
    { 0x80038668u, 0x80038698u, kMain80038668Words },
    { 0x80038698u, 0x800387c0u, kMain80038698Words },
    { 0x800387c0u, 0x80038838u, kMain800387C0Words },
    { 0x80038838u, 0x800388e8u, kMain80038838Words },
    { 0x800388e8u, 0x80038908u, kMain800388E8Words },
    { 0x80038908u, 0x80038958u, kMain80038908Words },
    { 0x80038958u, 0x80038a00u, kMain80038958Words },
    { 0x80038a00u, 0x80038a58u, kMain80038A00Words },
    { 0x80038a58u, 0x80038fc4u, kMain80038A58Words },
    { 0x80038fc4u, 0x80038ffcu, kMain80038FC4Words },
    { 0x80038ffcu, 0x8003916cu, kMain80038FFCWords },
    { 0x8003916cu, 0x800391d4u, kMain8003916CWords },
    { 0x800391d4u, 0x80039300u, kMain800391D4Words },
    { 0x80039300u, 0x80039308u, kMain80039300Words },
    { 0x80039308u, 0x80039b20u, kMain80039308Words },
    { 0x80039b20u, 0x80039c5cu, kMain80039B20Words },
    { 0x80039c5cu, 0x80039c70u, kMain80039C5CWords },
    { 0x80039c70u, 0x80039decu, kMain80039C70Words },
    { 0x80039decu, 0x80039f14u, kMain80039DECWords },
    { 0x80039f14u, 0x80039f50u, kMain80039F14Words },
    { 0x80039f50u, 0x8003a098u, kMain80039F50Words },
    { 0x8003a098u, 0x8003a0d0u, kMain8003A098Words },
    { 0x8003a0d0u, 0x8003a0e4u, kMain8003A0D0Words },
    { 0x8003a0e4u, 0x8003a234u, kMain8003A0E4Words },
    { 0x8003a234u, 0x8003a3d8u, kMain8003A234Words },
    { 0x8003a3d8u, 0x8003a404u, kMain8003A3D8Words },
    { 0x8003a404u, 0x8003a424u, kMain8003A404Words },
    { 0x8003ab84u, 0x8003ae14u, kMain8003AB84Words },
    { 0x8003ae14u, 0x8003ae9cu, kMain8003AE14Words },
    { 0x8003ae9cu, 0x8003af04u, kMain8003AE9CWords },
    { 0x8003af4cu, 0x8003aff0u, kMain8003AF4CWords },
    { 0x8003aff0u, 0x8003b02cu, kMain8003AFF0Words },
    { 0x8003b02cu, 0x8003b08cu, kMain8003B02CWords },
    { 0x8003b08cu, 0x8003b0b8u, kMain8003B08CWords },
    { 0x8003b0b8u, 0x8003b0e4u, kMain8003B0B8Words },
    { 0x8003b250u, 0x8003b280u, kMain8003B250Words },
    { 0x8003c0a0u, 0x8003c23cu, kMain8003C0A0Words },
    { 0x8003c23cu, 0x8003c438u, kMain8003C23CWords },
    { 0x8003c438u, 0x8003c498u, kMain8003C438Words },
    { 0x8003c498u, 0x8003c4f0u, kMain8003C498Words },
    { 0x8003c4f0u, 0x8003c598u, kMain8003C4F0Words },
    { 0x8003c92cu, 0x8003cf68u, kMain8003C92CWords },
    { 0x8003cf68u, 0x8003cff8u, kMain8003CF68Words },
    { 0x8003cff8u, 0x8003d134u, kMain8003CFF8Words },
    { 0x8003d134u, 0x8003d25cu, kMain8003D134Words },
    { 0x8003d25cu, 0x8003d32cu, kMain8003D25CWords },
    { 0x8003d32cu, 0x8003d3b4u, kMain8003D32CWords },
    { 0x8003d3b4u, 0x8003d3f8u, kMain8003D3B4Words },
    { 0x8003d3f8u, 0x8003d424u, kMain8003D3F8Words },
    { 0x8003d650u, 0x8003d6e4u, kMain8003D650Words },
    { 0x8003d6e4u, 0x8003d94cu, kMain8003D6E4Words },
    { 0x8003d94cu, 0x8003d96cu, kMain8003D94CWords },
    { 0x8003d96cu, 0x8003d98cu, kMain8003D96CWords },
    { 0x8003d98cu, 0x8003d9ccu, kMain8003D98CWords },
    { 0x8003d9ccu, 0x8003da1cu, kMain8003D9CCWords },
    { 0x8003da1cu, 0x8003dc90u, kMain8003DA1CWords },
    { 0x8003dc90u, 0x8003df8cu, kMain8003DC90Words },
    { 0x8003df8cu, 0x8003e248u, kMain8003DF8CWords },
    { 0x8003e248u, 0x8003e2e4u, kMain8003E248Words },
    { 0x8003e2e4u, 0x8003e310u, kMain8003E2E4Words },
    { 0x8003e310u, 0x8003e418u, kMain8003E310Words },
    { 0x8003e418u, 0x8003e65cu, kMain8003E418Words },
    { 0x8003e65cu, 0x8003ea04u, kMain8003E65CWords },
    { 0x8003ea04u, 0x8003eab4u, kMain8003EA04Words },
    { 0x8003eab4u, 0x8003ebb0u, kMain8003EAB4Words },
    { 0x8003ebb0u, 0x8003ec10u, kMain8003EBB0Words },
    { 0x8003ec10u, 0x8003ed94u, kMain8003EC10Words },
    { 0x8003ed94u, 0x8003edbcu, kMain8003ED94Words },
    { 0x8003edbcu, 0x8003ede8u, kMain8003EDBCWords },
    { 0x8003ede8u, 0x8003eee4u, kMain8003EDE8Words },
    { 0x8003eee4u, 0x8003f104u, kMain8003EEE4Words },
    { 0x8003f104u, 0x8003f144u, kMain8003F104Words },
    { 0x8003f144u, 0x8003f380u, kMain8003F144Words },
    { 0x8003f380u, 0x8003f434u, kMain8003F380Words },
    { 0x8003f434u, 0x8003f7c8u, kMain8003F434Words },
    { 0x8003f7c8u, 0x8003f840u, kMain8003F7C8Words },
    { 0x8003f840u, 0x8003fa54u, kMain8003F840Words },
    { 0x8003fa54u, 0x8003fa64u, kMain8003FA54Words },
    { 0x800401ccu, 0x800401e4u, kMain800401CCWords },
    { 0x800401e4u, 0x800402a8u, kMain800401E4Words },
    { 0x800402a8u, 0x800403a4u, kMain800402A8Words },
    { 0x800403a4u, 0x80040868u, kMain800403A4Words },
    { 0x800414e4u, 0x800415a8u, kMain800414E4Words },
    { 0x800415a8u, 0x8004162cu, kMain800415A8Words },
    { 0x8004162cu, 0x800416a8u, kMain8004162CWords },
    { 0x800416a8u, 0x800419b0u, kMain800416A8Words },
    { 0x800419b0u, 0x80041a20u, kMain800419B0Words },
    { 0x80041a20u, 0x80041a50u, kMain80041A20Words },
    { 0x80041a50u, 0x80041a80u, kMain80041A50Words },
    { 0x80041a80u, 0x80041ab0u, kMain80041A80Words },
    { 0x80041ab0u, 0x80041e8cu, kMain80041AB0Words },
    { 0x80041e8cu, 0x80042154u, kMain80041E8CWords },
    { 0x80042154u, 0x800422b4u, kMain80042154Words },
    { 0x800422b4u, 0x800422e8u, kMain800422B4Words },
    { 0x800422e8u, 0x80042374u, kMain800422E8Words },
    { 0x80042374u, 0x8004239cu, kMain80042374Words },
    { 0x80042610u, 0x80042644u, kMain80042610Words },
    { 0x80042644u, 0x80042674u, kMain80042644Words },
    { 0x80042674u, 0x800426a4u, kMain80042674Words },
    { 0x800426a4u, 0x800426d4u, kMain800426A4Words },
    { 0x800426d4u, 0x800426e4u, kMain800426D4Words },
    { 0x800426e4u, 0x800426fcu, kMain800426E4Words },
    { 0x800426fcu, 0x80042718u, kDraw800426FCWords },
    { 0x80042718u, 0x800427f4u, kMain80042718Words },
    { 0x800427f4u, 0x800429dcu, kMain800427F4Words },
    { 0x800429dcu, 0x80042b30u, kMain800429DCWords },
    { 0x80042b30u, 0x80042bdcu, kMain80042B30Words },
    { 0x80042bdcu, 0x80042c64u, kMain80042BDCWords },
    { 0x80042c64u, 0x80042c90u, kMain80042C64Words },
    { 0x80042c90u, 0x80042ce8u, kMain80042C90Words },
    { 0x80042ce8u, 0x80042d60u, kMain80042CE8Words },
    { 0x80042d60u, 0x80042d8cu, kMain80042D60Words },
    { 0x80042d8cu, 0x80042db8u, kMain80042D8CWords },
    { 0x80042db8u, 0x80042e08u, kMain80042DB8Words },
    { 0x80042e08u, 0x80042f8cu, kMain80042E08Words },
    { 0x80043078u, 0x80043088u, kDisplay80043078Words },
    { 0x80043088u, 0x800430b8u, kMain80043088Words },
    { 0x80043974u, 0x80043994u, kMain80043974Words },
    { 0x800439d4u, 0x800439f8u, kMain800439D4Words },
    { 0x800439f8u, 0x80043a18u, kMain800439F8Words },
    { 0x80044a8cu, 0x80044b14u, kMain80044A8CWords },
    { 0x80044b14u, 0x80044bf4u, kMain80044B14Words },
    { 0x80044bf4u, 0x80044ce8u, kMain80044BF4Words },
    { 0x80044ce8u, 0x80044d38u, kMain80044CE8Words },
    { 0x8004657cu, 0x80046610u, kMain8004657CWords },
    { 0x80046610u, 0x80046630u, kMain80046610Words },
    { 0x80046630u, 0x8004674cu, kMain80046630Words },
    { 0x8004674cu, 0x8004689cu, kMain8004674CWords },
    { 0x8004689cu, 0x800468fcu, kMain8004689CWords },
    { 0x800468fcu, 0x80046980u, kMain800468FCWords },
    { 0x80046980u, 0x80046994u, kMain80046980Words },
    { 0x80046994u, 0x800469a8u, kMain80046994Words },
    { 0x800469a8u, 0x800469ccu, kMain800469A8Words },
    { 0x800469ccu, 0x80046a5cu, kMain800469CCWords },
    { 0x80046a5cu, 0x80046abcu, kMain80046A5CWords },
    { 0x80046abcu, 0x80046b44u, kMain80046ABCWords },
    { 0x80046b44u, 0x80046bfcu, kMain80046B44Words },
    { 0x80046bfcu, 0x80046c38u, kMain80046BFCWords },
    { 0x80046c38u, 0x80046cfcu, kMain80046C38Words },
    { 0x80046cfcu, 0x80046d1cu, kMain80046CFCWords },
    { 0x80046d1cu, 0x8004768cu, kMain80046D1CWords },
    { 0x8004768cu, 0x800476c0u, kMain8004768CWords },
    { 0x800476c0u, 0x8004787cu, kMain800476C0Words },
    { 0x8004787cu, 0x800478b8u, kCamera8004787CWords },
    { 0x800478b8u, 0x80047948u, kCamera800478B8Words },
    { 0x80047948u, 0x800479e8u, kCamera80047948Words },
    { 0x800479e8u, 0x80047b3cu, kMain800479E8Words },
    { 0x80047b3cu, 0x80047bd8u, kMain80047B3CWords },
    { 0x80047bd8u, 0x80047cacu, kMain80047BD8Words },
    { 0x80047cb4u, 0x80047d34u, kGte80047CB4Words },
    { 0x80047d3cu, 0x80047dc0u, kCamera80047D3CWords },
    { 0x80047dccu, 0x80047e58u, kMain80047DCCWords },
    { 0x80047e58u, 0x80047ec8u, kMain80047E58Words },
    { 0x80047ec8u, 0x80047f84u, kMain80047EC8Words },
    { 0x80047f84u, 0x80048068u, kMain80047F84Words },
    { 0x8004806cu, 0x800480ecu, kMain8004806CWords },
    { 0x800480ecu, 0x80048180u, kMain800480ECWords },
    { 0x8004818cu, 0x80048298u, kMain8004818CWords },
    { 0x8004829cu, 0x80048384u, kMain8004829CWords },
    { 0x800484ecu, 0x8004864cu, kCamera800484ECWords },
    { 0x8004864cu, 0x8004867cu, kMain8004864CWords },
    { 0x8004867cu, 0x8004871cu, kMain8004867CWords },
    { 0x8004871cu, 0x800487bcu, kMain8004871CWords },
    { 0x800487bcu, 0x80048804u, kMain800487BCWords },
    { 0x8004880cu, 0x8004891cu, kMain8004880CWords },
    { 0x8004891cu, 0x80048b6cu, kMain8004891CWords },
    { 0x80048b6cu, 0x80048ca4u, kMain80048B6CWords },
    { 0x80048cacu, 0x80048d98u, kMain80048CACWords },
    { 0x80048d9cu, 0x80048eacu, kCamera80048D9CWords },
    { 0x80048eacu, 0x80048fb8u, kMain80048EACWords },
    { 0x80048fb8u, 0x80049018u, kMain80048FB8Words },
    { 0x8004901cu, 0x80049140u, kMain8004901CWords },
    { 0x8004914cu, 0x8004917cu, kMain8004914CWords },
    { 0x8004917cu, 0x800491acu, kMain8004917CWords },
    { 0x800491acu, 0x800491ccu, kMain800491ACWords },
    { 0x800491ccu, 0x800491ecu, kMain800491CCWords },
    { 0x800491ecu, 0x800491f8u, kMain800491ECWords },
    { 0x800491fcu, 0x8004921cu, kGte800491FCWords },
    { 0x8004921cu, 0x80049234u, kGte8004921CWords },
    { 0x8004923cu, 0x80049248u, kSecondGeom8004923CWords },
    { 0x8004924cu, 0x80049274u, kMain8004924CWords },
    { 0x80049274u, 0x8004929cu, kMain80049274Words },
    { 0x8004929cu, 0x800492d8u, kMain8004929CWords },
    { 0x800492d8u, 0x800492fcu, kMain800492D8Words },
    { 0x800492fcu, 0x80049324u, kMain800492FCWords },
    { 0x80049324u, 0x8004934cu, kMain80049324Words },
    { 0x8004934cu, 0x8004936cu, kMain8004934CWords },
    { 0x8004936cu, 0x80049390u, kMain8004936CWords },
    { 0x80049390u, 0x800493e8u, kMain80049390Words },
    { 0x800493e8u, 0x80049440u, kMain800493E8Words },
    { 0x80049440u, 0x80049458u, kMain80049440Words },
    { 0x8004945cu, 0x8004948cu, kMain8004945CWords },
    { 0x8004948cu, 0x800494c4u, kMain8004948CWords },
    { 0x800494c4u, 0x800494fcu, kMain800494C4Words },
    { 0x800494fcu, 0x8004952cu, kMain800494FCWords },
    { 0x8004952cu, 0x8004955cu, kMain8004952CWords },
    { 0x8004955cu, 0x80049588u, kMain8004955CWords },
    { 0x8004958cu, 0x800495e0u, kMain8004958CWords },
    { 0x800495ecu, 0x80049610u, kMain800495ECWords },
    { 0x8004974cu, 0x8004978cu, kMain8004974CWords },
    { 0x8004978cu, 0x80049a18u, kMain8004978CWords },
    { 0x80049a18u, 0x80049ca8u, kMain80049A18Words },
    { 0x80049cacu, 0x80049f38u, kMain80049CACWords },
    { 0x80049f3cu, 0x8004a0d4u, kMain80049F3CWords },
    { 0x8004a0dcu, 0x8004a274u, kMain8004A0DCWords },
    { 0x8004a27cu, 0x8004a414u, kMain8004A27CWords },
    { 0x8004a41cu, 0x8004a53cu, kMain8004A41CWords },
    { 0x8004a53cu, 0x8004a660u, kMain8004A53CWords },
    { 0x8004a660u, 0x8004a794u, kMain8004A660Words },
    { 0x8004a794u, 0x8004a8c8u, kMain8004A794Words },
    { 0x8004a8ccu, 0x8004aa18u, kMain8004A8CCWords },
    { 0x8004aa18u, 0x8004ab68u, kMain8004AA18Words },
    { 0x8004ab68u, 0x8004acccu, kMain8004AB68Words },
    { 0x8004acccu, 0x8004ae30u, kMain8004ACCCWords },
    { 0x8004ae3cu, 0x8004af5cu, kMain8004AE3CWords },
    { 0x8004af5cu, 0x8004b078u, kMain8004AF5CWords },
    { 0x8004b078u, 0x8004b1f8u, kMain8004B078Words },
    { 0x8004b1f8u, 0x8004b378u, kMain8004B1F8Words },
    { 0x8004b37cu, 0x8004b4c8u, kMain8004B37CWords },
    { 0x8004b4c8u, 0x8004b614u, kMain8004B4C8Words },
    { 0x8004b614u, 0x8004b7e0u, kMain8004B614Words },
    { 0x8004b7e0u, 0x8004b9acu, kMain8004B7E0Words },
    { 0x8004b9acu, 0x8004baccu, kMain8004B9ACWords },
    { 0x8004baccu, 0x8004bbf0u, kMain8004BACCWords },
    { 0x8004bbf0u, 0x8004bd38u, kMain8004BBF0Words },
    { 0x8004bd38u, 0x8004be80u, kMain8004BD38Words },
    { 0x8004be8cu, 0x8004bfd8u, kMain8004BE8CWords },
    { 0x8004bfd8u, 0x8004c128u, kMain8004BFD8Words },
    { 0x8004c128u, 0x8004c2a0u, kMain8004C128Words },
    { 0x8004c2a0u, 0x8004c418u, kMain8004C2A0Words },
    { 0x8004c41cu, 0x8004c53cu, kMain8004C41CWords },
    { 0x8004c53cu, 0x8004c658u, kMain8004C53CWords },
    { 0x8004c658u, 0x8004c7ecu, kMain8004C658Words },
    { 0x8004c7ecu, 0x8004c980u, kMain8004C7ECWords },
    { 0x8004c98cu, 0x8004cad8u, kMain8004C98CWords },
    { 0x8004cad8u, 0x8004cc24u, kMain8004CAD8Words },
    { 0x8004cc24u, 0x8004ce04u, kMain8004CC24Words },
    { 0x8004ce04u, 0x8004cfe4u, kMain8004CE04Words },
    { 0x8004cfecu, 0x8004d16cu, kMain8004CFECWords },
    { 0x8004d16cu, 0x8004d1d4u, kGte8004D16CWords },
    { 0x8004d1dcu, 0x8004d3acu, kMain8004D1DCWords },
    { 0x8004d3acu, 0x8004d420u, kMain8004D3ACWords },
    { 0x8004d420u, 0x8004d504u, kMain8004D420Words },
    { 0x8004d504u, 0x8004d6b4u, kMain8004D504Words },
    { 0x8004d6bcu, 0x8004d7f8u, kMain8004D6BCWords },
    { 0x8004d7f8u, 0x8004d938u, kMain8004D7F8Words },
    { 0x8004d938u, 0x8004da80u, kMain8004D938Words },
    { 0x8004da80u, 0x8004dbc8u, kMain8004DA80Words },
    { 0x8004dbccu, 0x8004dd34u, kMain8004DBCCWords },
    { 0x8004dd34u, 0x8004dea0u, kMain8004DD34Words },
    { 0x8004dea0u, 0x8004e018u, kMain8004DEA0Words },
    { 0x8004e018u, 0x8004e190u, kMain8004E018Words },
    { 0x8004e19cu, 0x8004e2e4u, kMain8004E19CWords },
    { 0x8004e2e4u, 0x8004e424u, kMain8004E2E4Words },
    { 0x8004e424u, 0x8004e5b4u, kMain8004E424Words },
    { 0x8004e5b4u, 0x8004e744u, kMain8004E5B4Words },
    { 0x8004e74cu, 0x8004e8ccu, kMain8004E74CWords },
    { 0x8004e8ccu, 0x8004ea40u, kMain8004E8CCWords },
    { 0x8004ea40u, 0x8004ec20u, kMain8004EA40Words },
    { 0x8004ec20u, 0x8004ee00u, kMain8004EC20Words },
    { 0x8004ee0cu, 0x8004ef78u, kMain8004EE0CWords },
    { 0x8004ef78u, 0x8004f0dcu, kMain8004EF78Words },
    { 0x8004f0dcu, 0x8004f24cu, kMain8004F0DCWords },
    { 0x8004f24cu, 0x8004f3bcu, kMain8004F24CWords },
    { 0x8004f3bcu, 0x8004f55cu, kMain8004F3BCWords },
    { 0x8004f55cu, 0x8004f6f8u, kMain8004F55CWords },
    { 0x8004f6f8u, 0x8004f8a4u, kMain8004F6F8Words },
    { 0x8004f8a4u, 0x8004fa50u, kMain8004F8A4Words },
    { 0x8004fa5cu, 0x8004fbd4u, kMain8004FA5CWords },
    { 0x8004fbd4u, 0x8004fd30u, kMain8004FBD4Words },
    { 0x8004fd30u, 0x8004fee4u, kMain8004FD30Words },
    { 0x8004fee4u, 0x80050098u, kMain8004FEE4Words },
    { 0x8005009cu, 0x80050258u, kMain8005009CWords },
    { 0x80050258u, 0x800503f0u, kMain80050258Words },
    { 0x800503f0u, 0x800505fcu, kMain800503F0Words },
    { 0x800505fcu, 0x80050808u, kMain800505FCWords },
    { 0x8005080cu, 0x80051044u, kMain8005080CWords },
    { 0x80051044u, 0x80051804u, kMain80051044Words },
    { 0x80051804u, 0x80051844u, kMain80051804Words },
    { 0x80051844u, 0x80051b0cu, kMain80051844Words },
    { 0x80051b0cu, 0x80051d78u, kMain80051B0CWords },
    { 0x80051d78u, 0x80051dc8u, kMain80051D78Words },
    { 0x80051dc8u, 0x80051ea0u, kMain80051DC8Words },
    { 0x80051ea0u, 0x80051f34u, kMain80051EA0Words },
    { 0x80051f34u, 0x80052430u, kMain80051F34Words },
    { 0x80052430u, 0x80052454u, kMain80052430Words },
    { 0x80052460u, 0x800525dcu, kMain80052460Words },
    { 0x800525dcu, 0x80052654u, kDraw800525DCWords },
    { 0x80052654u, 0x800527c4u, kDraw80052654Words },
    { 0x800527c4u, 0x8005283cu, kMain800527C4Words },
    { 0x8005283cu, 0x80052aa0u, kProjection8005283CWords },
    { 0x80052aa0u, 0x80052bdcu, kMain80052AA0Words },
    { 0x80052bdcu, 0x80052becu, kMain80052BDCWords },
    { 0x80052becu, 0x80052d00u, kProjection80052BECWords },
    { 0x80052d00u, 0x80052d90u, kProjection80052D00Words },
    { 0x80052d90u, 0x80052e38u, kProjection80052D90Words },
    { 0x80052e38u, 0x80052e68u, kMain80052E38Words },
    { 0x80052e68u, 0x80052f04u, kMain80052E68Words },
    { 0x80052f04u, 0x80052f38u, kMain80052F04Words },
    { 0x80052f38u, 0x80052fccu, kMain80052F38Words },
    { 0x80052fccu, 0x80053050u, kMain80052FCCWords },
    { 0x80053050u, 0x80053178u, kMain80053050Words },
    { 0x80053178u, 0x80053218u, kProjection80053178Words },
    { 0x80053218u, 0x80053290u, kDrawFollowup80053218Words },
    { 0x80053290u, 0x80053308u, kMain80053290Words },
    { 0x80053308u, 0x80053328u, kCamera80053308Words },
    { 0x80053328u, 0x80053804u, kCamera80053328Words },
    { 0x80053804u, 0x8005386cu, kCamera80053804Words },
    { 0x8005386cu, 0x800538bcu, kCamera8005386CWords },
    { 0x800538bcu, 0x800538ecu, kCamera800538BCWords },
    { 0x800538ecu, 0x80053978u, kCamera800538ECWords },
    { 0x80053978u, 0x800539c8u, kMain80053978Words },
    { 0x800539c8u, 0x800539d8u, kMain800539C8Words },
    { 0x800539d8u, 0x800539e8u, kMain800539D8Words },
    { 0x800539e8u, 0x800539f8u, kMain800539E8Words },
    { 0x800539f8u, 0x80053a18u, kMain800539F8Words },
    { 0x80053a18u, 0x80053a2cu, kMain80053A18Words },
    { 0x80053a2cu, 0x80053a40u, kMain80053A2CWords },
    { 0x80053a40u, 0x80053a4cu, kMain80053A40Words },
    { 0x80053a4cu, 0x80053a60u, kMain80053A4CWords },
    { 0x80053a60u, 0x80053a78u, kMain80053A60Words },
    { 0x80053a78u, 0x80053a8cu, kMain80053A78Words },
    { 0x80053a8cu, 0x80053aa0u, kMain80053A8CWords },
    { 0x80053aa0u, 0x80053ab4u, kMain80053AA0Words },
    { 0x80053ab4u, 0x80053ac0u, kMain80053AB4Words },
    { 0x80053ac0u, 0x80053accu, kMain80053AC0Words },
    { 0x80053accu, 0x80053ad8u, kMain80053ACCWords },
    { 0x80053ad8u, 0x80053af8u, kGte80053AD8Words },
    { 0x80053af8u, 0x80053b20u, kSecondGeom80053AF8Words },
    { 0x80053b20u, 0x80053bd8u, kCamera80053B20Words },
    { 0x80053bd8u, 0x80053cf8u, kMain80053BD8Words },
    { 0x80053cf8u, 0x80053d44u, kGte80053CF8Words },
    { 0x80053d44u, 0x80053e28u, kMain80053D44Words },
    { 0x80053e28u, 0x80053eecu, kCamera80053E28Words },
    { 0x80053eecu, 0x80053f6cu, kMain80053EECWords },
    { 0x80053f6cu, 0x80054340u, kCamera80053F6CWords },
    { 0x80054340u, 0x80054430u, kCamera80054340Words },
    { 0x80054430u, 0x800544f8u, kCamera80054430Words },
    { 0x800544f8u, 0x80054514u, kCamera800544F8Words },
    { 0x80054514u, 0x800547d8u, kMain80054514Words },
    { 0x800547d8u, 0x80054aacu, kMain800547D8Words },
    { 0x80054aacu, 0x80054dccu, kMain80054AACWords },
    { 0x80054dccu, 0x800553d8u, kMain80054DCCWords },
    { 0x800553d8u, 0x800553f4u, kMain800553D8Words },
    { 0x800553f4u, 0x80055d40u, kMain800553F4Words },
    { 0x80055d40u, 0x80056f18u, kMain80055D40Words },
    { 0x80056f18u, 0x80057094u, kMain80056F18Words },
    { 0x80057094u, 0x80057928u, kMain80057094Words },
    { 0x80057928u, 0x80057b14u, kMain80057928Words },
    { 0x80057b14u, 0x80057c7cu, kMain80057B14Words },
    { 0x80057c7cu, 0x80057e80u, kMain80057C7CWords },
    { 0x80057e80u, 0x80057ffcu, kMain80057E80Words },
    { 0x80057ffcu, 0x80058284u, kMain80057FFCWords },
    { 0x80058284u, 0x8005845cu, kMain80058284Words },
    { 0x8005845cu, 0x800586ccu, kMain8005845CWords },
    { 0x800586ccu, 0x80058890u, kMain800586CCWords },
    { 0x80058890u, 0x80058a4cu, kMain80058890Words },
    { 0x80058a4cu, 0x80058b04u, kDrawEnv80058A4CWords },
    { 0x80058b04u, 0x80058b40u, kDrawEnv80058B04Words },
    { 0x80058b40u, 0x80058b7cu, kMain80058B40Words },
    { 0x80058b7cu, 0x80058c6cu, kMain80058B7CWords },
    { 0x80058c6cu, 0x80058ca8u, kMain80058C6CWords },
    { 0x80058ca8u, 0x80058ce4u, kMain80058CA8Words },
    { 0x80058ce4u, 0x80058d20u, kMain80058CE4Words },
    { 0x80058d20u, 0x80058d48u, kMain80058D20Words },
    { 0x80058d48u, 0x80058d70u, kMain80058D48Words },
    { 0x80058d70u, 0x80058d84u, kMain80058D70Words },
    { 0x80058d84u, 0x80058d98u, kMain80058D84Words },
    { 0x80058d98u, 0x80058dacu, kMain80058D98Words },
    { 0x80058dacu, 0x80058dc0u, kMain80058DACWords },
    { 0x80058dc0u, 0x80058dd4u, kMain80058DC0Words },
    { 0x80058dd4u, 0x80058de8u, kMain80058DD4Words },
    { 0x800595fcu, 0x80059658u, kMain800595FCWords },
    { 0x80059658u, 0x800596f4u, kMain80059658Words },
    { 0x800596f4u, 0x80059760u, kMain800596F4Words },
    { 0x80059760u, 0x80059888u, kClearImage80059760Words },
    { 0x80059888u, 0x8005991cu, kClearImage80059888Words },
    { 0x8005991cu, 0x800599b8u, kMain8005991CWords },
    { 0x800599b8u, 0x80059a80u, kMain800599B8Words },
    { 0x80059a80u, 0x80059b44u, kMain80059A80Words },
    { 0x80059b44u, 0x80059bfcu, kMain80059B44Words },
    { 0x80059bfcu, 0x80059cf4u, kMain80059BFCWords },
    { 0x80059cf4u, 0x80059d68u, kMain80059CF4Words },
    { 0x80059d68u, 0x80059e6cu, kDraw80059D68Words },
    { 0x80059e6cu, 0x80059f88u, kMain80059E6CWords },
    { 0x80059f88u, 0x80059fc0u, kMain80059F88Words },
    { 0x80059fc0u, 0x8005a468u, kDisplay80059FC0Words },
    { 0x8005a468u, 0x8005a4a0u, kMain8005A468Words },
    { 0x8005a4a0u, 0x8005a4d0u, kMain8005A4A0Words },
    { 0x8005a4d0u, 0x8005a50cu, kMain8005A4D0Words },
    { 0x8005a50cu, 0x8005a590u, kMain8005A50CWords },
    { 0x8005a590u, 0x8005a5d4u, kMain8005A590Words },
    { 0x8005a5d4u, 0x8005a600u, kMain8005A5D4Words },
    { 0x8005a600u, 0x8005a658u, kMain8005A600Words },
    { 0x8005a658u, 0x8005a870u, kMain8005A658Words },
    { 0x8005a870u, 0x8005ab00u, kDraw8005A870Words },
    { 0x8005ab00u, 0x8005ab58u, kDraw8005AB00Words },
    { 0x8005ab58u, 0x8005ac24u, kDraw8005AB58Words },
    { 0x8005ac24u, 0x8005acf0u, kDraw8005AC24Words },
    { 0x8005acf0u, 0x8005ad34u, kDraw8005ACF0Words },
    { 0x8005ad34u, 0x8005adb8u, kDraw8005AD34Words },
    { 0x8005adb8u, 0x8005ae68u, kMain8005ADB8Words },
    { 0x8005ae68u, 0x8005ae80u, kMain8005AE68Words },
    { 0x8005ae80u, 0x8005af68u, kMain8005AE80Words },
    { 0x8005af68u, 0x8005b1c4u, kClearImage8005AF68Words },
    { 0x8005b1c4u, 0x8005b400u, kMain8005B1C4Words },
    { 0x8005b400u, 0x8005b684u, kMain8005B400Words },
    { 0x8005b684u, 0x8005b6acu, kDisplay8005B684Words },
    { 0x8005b6acu, 0x8005b6c0u, kMain8005B6ACWords },
    { 0x8005b6c0u, 0x8005b710u, kMain8005B6C0Words },
    { 0x8005b710u, 0x8005b75cu, kDraw8005B710Words },
    { 0x8005b75cu, 0x8005b7b0u, kMain8005B75CWords },
    { 0x8005b7b0u, 0x8005ba90u, kDraw8005B7B0Words },
    { 0x8005ba90u, 0x8005bd7cu, kDraw8005BA90Words },
    { 0x8005bd7cu, 0x8005bed8u, kMain8005BD7CWords },
    { 0x8005bed8u, 0x8005c020u, kMain8005BED8Words },
    { 0x8005c020u, 0x8005c054u, kDraw8005C020Words },
    { 0x8005c054u, 0x8005c1c0u, kMain8005C054Words },
    { 0x8005c1c0u, 0x8005c29cu, kMain8005C1C0Words },
    { 0x8005c29cu, 0x8005c2c8u, kMain8005C29CWords },
    { 0x8005c2c8u, 0x8005c2f8u, kMain8005C2C8Words },
    { 0x8005c2f8u, 0x8005c324u, kMain8005C2F8Words },
    { 0x8005c4ccu, 0x8005c4dcu, kMain8005C4CCWords },
    { 0x8005ce18u, 0x8005ce24u, kMain8005CE18Words },
    { 0x8005ce28u, 0x8005ce34u, kGte8005CE28Words },
    { 0x8005ce50u, 0x8005ce5cu, kMain8005CE50Words },
    { 0x8005ce98u, 0x8005cea4u, kMain8005CE98Words },
    { 0x8005d184u, 0x8005d244u, kMain8005D184Words },
    { 0x8005d244u, 0x8005d4b8u, kMain8005D244Words },
    { 0x8005d4b8u, 0x8005d538u, kMain8005D4B8Words },
    { 0x8005d538u, 0x8005d6a0u, kMain8005D538Words },
    { 0x8005d6a0u, 0x8005d6ccu, kMain8005D6A0Words },
    { 0x8005e188u, 0x8005e1a4u, kMain8005E188Words },
    { 0x8005e79cu, 0x8005e8e8u, kMain8005E79CWords },
    { 0x8005e8e8u, 0x8005ea34u, kMain8005E8E8Words },
    { 0x8005f704u, 0x8005f728u, kMain8005F704Words },
    { 0x8005f728u, 0x8005f75cu, kMain8005F728Words },
};

static const FormatterRange kFormatterRanges1[] = {
    { 0x8005d6ccu, 0x8005d734u, kInputVerifierWords },
    { 0x8005d734u, 0x8005d8a0u, kInputHandlerWords },
    { 0x8005d8a0u, 0x8005d8b4u, kInputHandlerClear8005D8A0Words },
    { 0x8005d8b4u, 0x8005d980u, kMain8005D8B4Words },
    { 0x8005d980u, 0x8005d9c4u, kInputStop8005D980Words },
    { 0x8005d9c4u, 0x8005dbd8u, kInputSerialStartWords },
    { 0x8005dbd8u, 0x8005dca0u, kInputSerialNextWords },
    { 0x8005dca0u, 0x8005de78u, kInputSerialTransferWords },
    { 0x8005de78u, 0x8005e0acu, kInputDigital8005DE78Words },
    { 0x8005e0acu, 0x8005e13cu, kInputSerialIrqWords },
    { 0x8005e13cu, 0x8005e164u, kInputDigital8005E13CWords },
    { 0x8005e168u, 0x8005e174u, kMain8005E168Words },
    { 0x8005e178u, 0x8005e184u, kMain8005E178Words },
    { 0x8005e1a4u, 0x8005e228u, kInputDigital8005E1A4Words },
    { 0x8005e228u, 0x8005e374u, kInputResponseModeWords },
    { 0x8005e374u, 0x8005e3acu, kInputResponse8005E374Words },
    { 0x8005e3acu, 0x8005e79cu, kInputResponse8005E3ACWords },
    { 0x8005ea34u, 0x8005ea54u, kInputDigital8005EA34Words },
    { 0x8005ea54u, 0x8005ea68u, kInputDigital8005EA54Words },
    { 0x8005ea68u, 0x8005ea88u, kInputDigital8005EA68Words },
    { 0x8005ea88u, 0x8005eaa8u, kInputDigital8005EA88Words },
    { 0x8005eaa8u, 0x8005eac8u, kInputDigital8005EAA8Words },
    { 0x8005eac8u, 0x8005eae8u, kInputDigital8005EAC8Words },
    { 0x8005eae8u, 0x8005eb28u, kInputSerialDispatchWords },
    { 0x8005eb28u, 0x8005ec00u, kInputDigital8005EB28Words },
    { 0x8005ec00u, 0x8005ecc0u, kInputDigital8005EC00Words },
    { 0x8005ecc0u, 0x8005ed4cu, kInputDigital8005ECC0Words },
    { 0x8005ed4cu, 0x8005f0c8u, kInputDigital8005ED4CWords },
    { 0x8005f0c8u, 0x8005f228u, kMain8005F0C8Words },
    { 0x8005f228u, 0x8005f290u, kMain8005F228Words },
    { 0x8005f290u, 0x8005f384u, kInputDigital8005F290Words },
    { 0x8005f384u, 0x8005f394u, kInputResponseClearWords },
    { 0x8005f394u, 0x8005f450u, kInputDigital8005F394Words },
    { 0x8005f450u, 0x8005f6ccu, kInputDigital8005F450Words },
    { 0x8005f6ccu, 0x8005f704u, kInputDigital8005F6CCWords },
    { 0x8005f75cu, 0x8005f830u, kInputSerialPadWords },
    { 0x8005f830u, 0x8005fa94u, kInputResponseWords },
    { 0x8005fa94u, 0x8005fb70u, kInputDigital8005FA94Words },
    { 0x8005fb70u, 0x8005fb9cu, kInputResponseStatusWords },
    { 0x8005fba8u, 0x8005fbc8u, kInputTimerStartWords },
    { 0x8005fbc8u, 0x8005fc68u, kInputTimerPollWords },
    { 0x8005fc68u, 0x8005fc98u, kMain8005FC68Words },
    { 0x8005fc98u, 0x8005fcb8u, kMain8005FC98Words },
    { 0x8005fcb8u, 0x8005fd18u, kMain8005FCB8Words },
    { 0x8005fd18u, 0x8005fd58u, kMain8005FD18Words },
    { 0x8005fd58u, 0x8005fdd4u, kMain8005FD58Words },
    { 0x8005fdd4u, 0x8005ffb4u, kMain8005FDD4Words },
    { 0x8005ffb4u, 0x80060030u, kMain8005FFB4Words },
    { 0x80060030u, 0x8006023cu, kMain80060030Words },
    { 0x8006023cu, 0x800603bcu, kMain8006023CWords },
    { 0x800603bcu, 0x80060404u, kMain800603BCWords },
    { 0x80060404u, 0x800604c4u, kMain80060404Words },
    { 0x800604c4u, 0x80060614u, kMain800604C4Words },
    { 0x80060614u, 0x800606d4u, kMain80060614Words },
    { 0x800606d4u, 0x80060824u, kMain800606D4Words },
    { 0x80060824u, 0x80060930u, kMain80060824Words },
    { 0x80060930u, 0x80060ae0u, kMain80060930Words },
    { 0x80060ae0u, 0x80060becu, kMain80060AE0Words },
    { 0x80060becu, 0x80060d9cu, kMain80060BECWords },
    { 0x80060d9cu, 0x80061010u, kMain80060D9CWords },
    { 0x80061010u, 0x80061024u, kMain80061010Words },
    { 0x80061024u, 0x80061114u, kMain80061024Words },
    { 0x80061114u, 0x80061344u, kMain80061114Words },
    { 0x80061344u, 0x80061524u, kMain80061344Words },
    { 0x80061524u, 0x800615bcu, kMain80061524Words },
    { 0x800615bcu, 0x80061678u, kMain800615BCWords },
    { 0x80061678u, 0x800616d0u, kMain80061678Words },
    { 0x800616d0u, 0x80061770u, kMain800616D0Words },
    { 0x80061770u, 0x800617ccu, kMain80061770Words },
    { 0x8006186cu, 0x8006189cu, kMain8006186CWords },
    { 0x8006189cu, 0x80061a80u, kMain8006189CWords },
    { 0x80061a80u, 0x80061aa0u, kMain80061A80Words },
    { 0x80061aa0u, 0x80061b58u, kMain80061AA0Words },
    { 0x80061b58u, 0x80061c60u, kMain80061B58Words },
    { 0x80061c60u, 0x80061d3cu, kMain80061C60Words },
    { 0x80061d3cu, 0x80061e18u, kMain80061D3CWords },
    { 0x80061e18u, 0x80061e54u, kMain80061E18Words },
    { 0x80061e54u, 0x80061e90u, kMain80061E54Words },
    { 0x80061e90u, 0x80061f38u, kMain80061E90Words },
    { 0x80061f38u, 0x80061f44u, kMain80061F38Words },
    { 0x80061f48u, 0x80061f54u, kMain80061F48Words },
    { 0x80061f58u, 0x80061f64u, kMain80061F58Words },
    { 0x80061f68u, 0x80061f74u, kMain80061F68Words },
    { 0x80061f78u, 0x80061f84u, kMain80061F78Words },
    { 0x80061f88u, 0x80061f94u, kMain80061F88Words },
    { 0x80061f98u, 0x80061fa4u, kMain80061F98Words },
    { 0x80061fa8u, 0x80062144u, kMain80061FA8Words },
    { 0x80062144u, 0x80062244u, kMain80062144Words },
    { 0x80062248u, 0x80062254u, kMain80062248Words },
    { 0x80062258u, 0x80062264u, kMain80062258Words },
    { 0x80062268u, 0x80062274u, kMain80062268Words },
    { 0x80062278u, 0x80062284u, kMain80062278Words },
    { 0x80062288u, 0x80062294u, kMain80062288Words },
    { 0x80062298u, 0x800622d0u, kMain80062298Words },
    { 0x800622d0u, 0x80062328u, kMain800622D0Words },
    { 0x80062328u, 0x80062360u, kMain80062328Words },
    { 0x80062360u, 0x80062388u, kMain80062360Words },
    { 0x80062388u, 0x80062394u, kMain80062388Words },
    { 0x80062394u, 0x800623a4u, kMain80062394Words },
    { 0x800623a4u, 0x80062434u, kMain800623A4Words },
    { 0x80062434u, 0x800624c4u, kMain80062434Words },
    { 0x800624c4u, 0x800624f4u, kMain800624C4Words },
    { 0x800624f4u, 0x8006252cu, kMain800624F4Words },
    { 0x8006252cu, 0x800625a4u, kMain8006252CWords },
    { 0x800625a4u, 0x800625dcu, kMain800625A4Words },
    { 0x800625dcu, 0x80062644u, kMain800625DCWords },
    { 0x80062644u, 0x80062684u, kMain80062644Words },
    { 0x80062688u, 0x80062694u, kMain80062688Words },
    { 0x80062698u, 0x800626a4u, kMain80062698Words },
    { 0x800626a8u, 0x800626b4u, kMain800626A8Words },
    { 0x800626b8u, 0x800626c4u, kMain800626B8Words },
    { 0x800626c8u, 0x800626dcu, kMain800626C8Words },
    { 0x800626dcu, 0x800626f0u, kMain800626DCWords },
    { 0x800626f0u, 0x80062760u, kMain800626F0Words },
    { 0x80062768u, 0x800627d0u, kMain80062768Words },
    { 0x800627d8u, 0x800627e4u, kMain800627D8Words },
    { 0x800627e8u, 0x800627f4u, kMain800627E8Words },
    { 0x800627f8u, 0x80062804u, kMain800627F8Words },
    { 0x80062808u, 0x80062870u, kMain80062808Words },
    { 0x80062888u, 0x8006289cu, kMain80062888Words },
    { 0x8006289cu, 0x8006291cu, kMain8006289CWords },
};

static const FormatterRange kFormatterRanges2[] = {
    { 0x8004239cu, 0x80042404u, kFile8004239CWords },
    { 0x80042404u, 0x800424e4u, kFile80042404Words },
    { 0x800424e4u, 0x80042580u, kFile800424E4Words },
    { 0x80042580u, 0x800425b0u, kMain80042580Words },
    { 0x800425b0u, 0x800425e0u, kMain800425B0Words },
    { 0x8004355cu, 0x8004357cu, kFile8004355CWords },
    { 0x80044d38u, 0x80044f24u, kCdInitializer80044D38Words },
    { 0x80044f24u, 0x80045090u, kMain80044F24Words },
};

static const FormatterRange kFormatterRanges3[] = {
    { 0x8001971cu, 0x80019930u, kFile8001971CWords },
    { 0x80019930u, 0x80019990u, kMain80019930Words },
    { 0x80019990u, 0x80019a10u, kFile80019990Words },
    { 0x80019a10u, 0x80019a24u, kMain80019A10Words },
    { 0x8002c8bcu, 0x8002c8f4u, kSpu8002C8BCWords },
    { 0x8002c8f4u, 0x8002cc4cu, kSpu8002C8F4Words },
    { 0x8002cc4cu, 0x8002ccb4u, kSpu8002CC4CWords },
    { 0x8002ccb4u, 0x8002ccd8u, kMain8002CCB4Words },
    { 0x8002ccd8u, 0x8002cdd8u, kMain8002CCD8Words },
    { 0x8002d1f0u, 0x8002d240u, kSpu8002D1F0Words },
    { 0x8002fae0u, 0x8002fb08u, kSpu8002FAE0Words },
    { 0x80034c24u, 0x80034cf0u, kSpu80034C24Words },
    { 0x80037004u, 0x80037028u, kSpu80037004Words },
    { 0x80037028u, 0x80037144u, kMain80037028Words },
    { 0x80037cc8u, 0x80037cd8u, kSpu80037CC8Words },
    { 0x80037d98u, 0x80037ea0u, kSpu80037D98Words },
    { 0x80037ea0u, 0x80037f3cu, kMain80037EA0Words },
    { 0x80037f3cu, 0x80037fc4u, kMain80037F3CWords },
    { 0x8003a424u, 0x8003a444u, kSpu8003A424Words },
    { 0x8003a444u, 0x8003a53cu, kSpu8003A444Words },
    { 0x8003a53cu, 0x8003a5b8u, kSpu8003A53CWords },
    { 0x8003a5b8u, 0x8003a84cu, kSpu8003A5B8Words },
    { 0x8003a84cu, 0x8003aa18u, kSpu8003A84CWords },
    { 0x8003aa18u, 0x8003aad8u, kMain8003AA18Words },
    { 0x8003aad8u, 0x8003ab84u, kMain8003AAD8Words },
    { 0x8003af04u, 0x8003af4cu, kSpu8003AF04Words },
    { 0x8003b0e4u, 0x8003b14cu, kSpu8003B0E4Words },
    { 0x8003b14cu, 0x8003b170u, kSpu8003B14CWords },
    { 0x8003b170u, 0x8003b1ecu, kMain8003B170Words },
    { 0x8003b1ecu, 0x8003b250u, kSpu8003B1ECWords },
    { 0x8003b280u, 0x8003b350u, kSpu8003B280Words },
    { 0x8003b350u, 0x8003b3d0u, kMain8003B350Words },
    { 0x8003b3d0u, 0x8003b45cu, kSpu8003B3D0Words },
    { 0x8003b45cu, 0x8003b954u, kSpu8003B45CWords },
    { 0x8003b954u, 0x8003be24u, kSpu8003B954Words },
    { 0x8003be24u, 0x8003be74u, kSpu8003BE24Words },
    { 0x8003be74u, 0x8003be98u, kSpu8003BE74Words },
    { 0x8003be98u, 0x8003c0a0u, kSpu8003BE98Words },
    { 0x8003c598u, 0x8003c92cu, kSpu8003C598Words },
    { 0x8003d424u, 0x8003d434u, kSpu8003D424Words },
    { 0x8003d434u, 0x8003d454u, kMain8003D434Words },
    { 0x8003d454u, 0x8003d518u, kMain8003D454Words },
    { 0x8003d518u, 0x8003d548u, kSpu8003D518Words },
    { 0x8003d548u, 0x8003d630u, kSpu8003D548Words },
    { 0x8003d630u, 0x8003d650u, kMain8003D630Words },
    { 0x8003fa64u, 0x8003fe18u, kSpu8003FA64Words },
    { 0x8003fe18u, 0x8003fe3cu, kMain8003FE18Words },
    { 0x8003fe3cu, 0x8004014cu, kSpu8003FE3CWords },
    { 0x8004014cu, 0x800401a0u, kSpu8004014CWords },
    { 0x800401a0u, 0x800401ccu, kSpu800401A0Words },
    { 0x80040868u, 0x80040938u, kSpu80040868Words },
    { 0x80040938u, 0x80040de8u, kMain80040938Words },
    { 0x80040de8u, 0x80041354u, kMain80040DE8Words },
    { 0x80041354u, 0x800413b8u, kMain80041354Words },
    { 0x800413b8u, 0x80041400u, kMain800413B8Words },
    { 0x80041400u, 0x80041448u, kMain80041400Words },
    { 0x80041448u, 0x800414e4u, kMain80041448Words },
    { 0x800425e0u, 0x80042610u, kSpu800425E0Words },
    { 0x80042f8cu, 0x80043034u, kSpu80042F8CWords },
    { 0x80043034u, 0x80043060u, kMain80043034Words },
    { 0x80043060u, 0x80043078u, kMain80043060Words },
    { 0x800430b8u, 0x800430dcu, kSpu800430B8Words },
    { 0x800430dcu, 0x80043300u, kSpu800430DCWords },
    { 0x80043300u, 0x80043398u, kMain80043300Words },
    { 0x80043398u, 0x800433c0u, kFile80043398Words },
    { 0x800433c0u, 0x800433e8u, kFile800433C0Words },
    { 0x800433e8u, 0x80043410u, kFile800433E8Words },
    { 0x80043410u, 0x80043420u, kFile80043410Words },
    { 0x80043420u, 0x80043430u, kFile80043420Words },
    { 0x80043430u, 0x80043440u, kMain80043430Words },
    { 0x80043440u, 0x80043450u, kFile80043440Words },
    { 0x80043450u, 0x800434bcu, kMain80043450Words },
    { 0x800434bcu, 0x800434dcu, kMain800434BCWords },
    { 0x800434dcu, 0x800434f4u, kMain800434DCWords },
    { 0x800434f4u, 0x80043528u, kMain800434F4Words },
    { 0x80043528u, 0x8004355cu, kMain80043528Words },
    { 0x8004357cu, 0x8004359cu, kFile8004357CWords },
    { 0x8004359cu, 0x800435b4u, kMain8004359CWords },
    { 0x800435b4u, 0x800435ccu, kMain800435B4Words },
    { 0x800435ccu, 0x80043704u, kFile800435CCWords },
    { 0x80043704u, 0x80043830u, kFile80043704Words },
    { 0x80043830u, 0x80043974u, kSpu80043830Words },
    { 0x80043994u, 0x800439b4u, kFile80043994Words },
    { 0x800439b4u, 0x800439d4u, kMain800439B4Words },
    { 0x80043a18u, 0x80043b1cu, kFile80043A18Words },
    { 0x80043b1cu, 0x80043b9cu, kFile80043B1CWords },
    { 0x80043b9cu, 0x80044124u, kMain80043B9CWords },
    { 0x80044124u, 0x800443a4u, kMain80044124Words },
    { 0x800443a4u, 0x80044670u, kFile800443A4Words },
    { 0x80044670u, 0x80044a8cu, kMain80044670Words },
    { 0x80045090u, 0x80045190u, kFile80045090Words },
    { 0x80045190u, 0x80045280u, kMain80045190Words },
    { 0x80045280u, 0x80045290u, kMain80045280Words },
    { 0x80045374u, 0x80045640u, kFile80045374Words },
    { 0x80045640u, 0x80045660u, kFile80045640Words },
    { 0x80045660u, 0x80045940u, kFile80045660Words },
    { 0x80045940u, 0x800459e8u, kFile80045940Words },
    { 0x800459e8u, 0x80045c94u, kFile800459E8Words },
    { 0x80045c94u, 0x80045d00u, kFile80045C94Words },
    { 0x80045d00u, 0x80045fd0u, kFile80045D00Words },
    { 0x80045fd0u, 0x800460ccu, kMain80045FD0Words },
    { 0x800460ccu, 0x800462e0u, kFile800460CCWords },
    { 0x800462e0u, 0x8004637cu, kMain800462E0Words },
    { 0x8004637cu, 0x80046480u, kFile8004637CWords },
    { 0x80046480u, 0x8004654cu, kFile80046480Words },
    { 0x8004654cu, 0x80046564u, kMain8004654CWords },
    { 0x80046564u, 0x8004657cu, kMain80046564Words },
    { 0x8005c324u, 0x8005c358u, kFile8005C324Words },
    { 0x8005c358u, 0x8005c388u, kFile8005C358Words },
    { 0x8005c388u, 0x8005c49cu, kMain8005C388Words },
    { 0x8005c49cu, 0x8005c4ccu, kMain8005C49CWords },
    { 0x8005c4dcu, 0x8005c540u, kFile8005C4DCWords },
    { 0x8005c540u, 0x8005c584u, kMain8005C540Words },
    { 0x8005c584u, 0x8005c604u, kFile8005C584Words },
    { 0x8005c604u, 0x8005c640u, kMain8005C604Words },
    { 0x8005c640u, 0x8005ccc8u, kMain8005C640Words },
    { 0x8005ccc8u, 0x8005cd18u, kMain8005CCC8Words },
    { 0x8005cd18u, 0x8005cd48u, kMain8005CD18Words },
    { 0x8005cd48u, 0x8005cd98u, kMain8005CD48Words },
    { 0x8005cd98u, 0x8005ce10u, kMain8005CD98Words },
    { 0x8005ce68u, 0x8005ce74u, kFile8005CE68Words },
    { 0x8005ce78u, 0x8005ce84u, kMain8005CE78Words },
    { 0x8005ce88u, 0x8005ce94u, kMain8005CE88Words },
    { 0x8005cea8u, 0x8005ceb4u, kFile8005CEA8Words },
    { 0x8005ceb8u, 0x8005cec4u, kMain8005CEB8Words },
    { 0x8005cec8u, 0x8005ced4u, kMain8005CEC8Words },
    { 0x8005ced8u, 0x8005cee4u, kMain8005CED8Words },
    { 0x8005cee8u, 0x8005cef4u, kMain8005CEE8Words },
    { 0x8005cef8u, 0x8005cf04u, kMain8005CEF8Words },
    { 0x8005cf08u, 0x8005cf18u, kMain8005CF08Words },
    { 0x8005cf18u, 0x8005cf28u, kMain8005CF18Words },
    { 0x8005cf28u, 0x8005cf34u, kMain8005CF28Words },
    { 0x8005cf38u, 0x8005cf44u, kMain8005CF38Words },
    { 0x8005cf48u, 0x8005cf54u, kMain8005CF48Words },
    { 0x8005cf58u, 0x8005cf64u, kMain8005CF58Words },
    { 0x8005cf68u, 0x8005d004u, kMain8005CF68Words },
    { 0x8005d004u, 0x8005d03cu, kMain8005D004Words },
    { 0x8005d03cu, 0x8005d06cu, kMain8005D03CWords },
    { 0x8005d06cu, 0x8005d0a0u, kMain8005D06CWords },
    { 0x8005d0a0u, 0x8005d0d4u, kMain8005D0A0Words },
    { 0x8005d0d8u, 0x8005d0f8u, kMain8005D0D8Words },
    { 0x8005d0f8u, 0x8005d118u, kMain8005D0F8Words },
    { 0x8005d118u, 0x8005d138u, kMain8005D118Words },
    { 0x8005d138u, 0x8005d184u, kMain8005D138Words },
};

static const FormatterRange kFormatterRanges4[] = {
    { 0x800ceec8u, 0x800cf104u, kOverlay0004_800CEEC8Words },
    { 0x800cf104u, 0x800cf300u, kOverlay0004_800CF104Words },
    { 0x800cf300u, 0x800cf370u, kOverlay0004_800CF300Words },
    { 0x800cf370u, 0x800cf3a4u, kOverlay0004_800CF370Words },
    { 0x800cf3a4u, 0x800cf3e8u, kOverlay0004_800CF3A4Words },
    { 0x800cf3e8u, 0x800cfb3cu, kOverlay0004_800CF3E8Words },
    { 0x800cfb3cu, 0x800cfc1cu, kOverlay0004_800CFB3CWords },
    { 0x800cfc1cu, 0x800cfe00u, kOverlay0004_800CFC1CWords },
    { 0x800cfe00u, 0x800cfeb4u, kOverlay0004_800CFE00Words },
    { 0x800cffecu, 0x800d0100u, kOverlay0004_800CFFECWords },
    { 0x800d1e18u, 0x800d1e9cu, kOverlay0004_800D1E18Words },
    { 0x800d1e9cu, 0x800d2394u, kOverlay0004_800D1E9CWords },
    { 0x800d2394u, 0x800d2454u, kOverlay0004_800D2394Words },
    { 0x800d2454u, 0x800d24d0u, kOverlay0004_800D2454Words },
    { 0x800d24d0u, 0x800d2704u, kOverlay0004_800D24D0Words },
    { 0x800d2704u, 0x800d27a0u, kOverlay0004_800D2704Words },
    { 0x800d27a0u, 0x800d298cu, kOverlay0004_800D27A0Words },
    { 0x800d298cu, 0x800d2a24u, kOverlay0004_800D298CWords },
    { 0x800d2a24u, 0x800d2aa0u, kOverlay0004_800D2A24Words },
    { 0x800d2aa0u, 0x800d2ad8u, kOverlay0004_800D2AA0Words },
    { 0x800d2c0cu, 0x800d2c88u, kOverlay0004_800D2C0CWords },
    { 0x800d2c88u, 0x800d2ca8u, kOverlay0004_800D2C88Words },
    { 0x800d2d44u, 0x800d2d68u, kOverlay0004_800D2D44Words },
    { 0x800d2d68u, 0x800d2e64u, kOverlay0004_800D2D68Words },
    { 0x800d2e64u, 0x800d2ef8u, kOverlay0004_800D2E64Words },
    { 0x800d2ef8u, 0x800d2f88u, kOverlay0004_800D2EF8Words },
    { 0x800d2f88u, 0x800d3020u, kOverlay0004_800D2F88Words },
    { 0x800d3020u, 0x800d30b8u, kOverlay0004_800D3020Words },
    { 0x800d30d0u, 0x800d3200u, kOverlay0004_800D30D0Words },
    { 0x800d3234u, 0x800d3540u, kOverlay0004_800D3234Words },
};

static const FormatterRange kFormatterRanges5[] = {
    { 0x800cedfcu, 0x800cf104u, kOverlay0010_800CEDFCWords },
    { 0x800cf370u, 0x800cf398u, kOverlay0010_800CF370Words },
    { 0x800cf398u, 0x800cf3b8u, kOverlay0010_800CF398Words },
    { 0x800cf3b8u, 0x800cf47cu, kOverlay0010_800CF3B8Words },
    { 0x800cf47cu, 0x800cf4d4u, kOverlay0010_800CF47CWords },
    { 0x800cf4d4u, 0x800cf804u, kOverlay0010_800CF4D4Words },
    { 0x800cf8b4u, 0x800cf8ccu, kOverlay0010_800CF8B4Words },
    { 0x800cf94cu, 0x800cf990u, kOverlay0010_800CF94CWords },
    { 0x800cfbbcu, 0x800cfbccu, kOverlay0010_800CFBBCWords },
    { 0x800cfbf8u, 0x800cfde8u, kOverlay0010_800CFBF8Words },
    { 0x800cfe60u, 0x800d0214u, kOverlay0010_800CFE60Words },
    { 0x800d0488u, 0x800d0588u, kOverlay0010_800D0488Words },
};

static const FormatterRange kFormatterRanges6[] = {
    { 0x80128420u, 0x801284b8u, kOverlaySc02_80128420Words },
    { 0x80128c14u, 0x80128c98u, kOverlaySc02_80128C14Words },
    { 0x80129220u, 0x80129248u, kOverlaySc02_80129220Words },
    { 0x80129248u, 0x80129258u, kOverlaySc02_80129248Words },
    { 0x80129258u, 0x8012927cu, kOverlaySc02_80129258Words },
    { 0x80129c40u, 0x80129cf8u, kOverlaySc02_80129C40Words },
    { 0x801378f0u, 0x801379d8u, kOverlaySc02_801378F0Words },
    { 0x8013a860u, 0x8013a8b0u, kOverlaySc02_8013A860Words },
    { 0x8013c98cu, 0x8013c9c4u, kOverlaySc02_8013C98CWords },
};

static const FormatterRange kFormatterRanges7[] = {
    { 0x800cf854u, 0x800cf864u, kOverlay0010_800CF854Words },
    { 0x800d02c0u, 0x800d02d0u, kOverlay0010_800D02C0Words },
    { 0x800d0588u, 0x800d05e8u, kOverlay0010_800D0588Words },
    { 0x800d05e8u, 0x800d0630u, kOverlay0010_800D05E8Words },
    { 0x800d0630u, 0x800d065cu, kOverlay0010_800D0630Words },
    { 0x800d065cu, 0x800d0694u, kOverlay0010_800D065CWords },
    { 0x800d06e8u, 0x800d0c48u, kOverlay0010_800D06E8Words },
    { 0x800d18dcu, 0x800d1938u, kOverlay0010_800D18DCWords },
    { 0x800d1938u, 0x800d1984u, kOverlay0010_800D1938Words },
    { 0x800d1984u, 0x800d19dcu, kOverlay0010_800D1984Words },
    { 0x800d1e20u, 0x800d1e28u, kOverlay0010_800D1E20Words },
    { 0x800d1f58u, 0x800d1f90u, kOverlay0010_800D1F58Words },
    { 0x800d1fc8u, 0x800d20c0u, kOverlay0010_800D1FC8Words },
};

static const FormatterRange kFormatterRanges8[] = {
    { 0x80145cecu, 0x80145ee8u, kOverlaySc02_80145CECWords },
    { 0x8015126cu, 0x80151664u, kOverlaySc02_8015126CWords },
    { 0x801552f4u, 0x80155344u, kOverlaySc02_801552F4Words },
    { 0x80158638u, 0x80158794u, kOverlaySc02_80158638Words },
    { 0x80159a20u, 0x80159b08u, kOverlaySc02_80159A20Words },
    { 0x80159c84u, 0x8015a1c8u, kOverlaySc02_80159C84Words },
    { 0x8015a2d8u, 0x8015a3c8u, kOverlaySc02_8015A2D8Words },
    { 0x801619a4u, 0x801619d0u, kOverlaySc02_801619A4Words },
    { 0x80161b18u, 0x80161b84u, kOverlaySc02_80161B18Words },
    { 0x801654a8u, 0x80165580u, kOverlaySc02_801654A8Words },
    { 0x80171ec8u, 0x80171ffcu, kOverlaySc02_80171EC8Words },
};

static const FormatterRange kFormatterRanges9[] = {
    { 0x80147084u, 0x8014708cu, kOverlaySc02_80147084Words },
    { 0x80147098u, 0x801470a0u, kOverlaySc02_80147098Words },
    { 0x801470acu, 0x801470b4u, kOverlaySc02_801470ACWords },
    { 0x80149210u, 0x80149228u, kOverlaySc02_80149210Words },
    { 0x80149228u, 0x80149284u, kOverlaySc02_80149228Words },
    { 0x80149284u, 0x80149290u, kOverlaySc02_80149284Words },
    { 0x80149290u, 0x80149350u, kOverlaySc02_80149290Words },
    { 0x80149350u, 0x80149374u, kOverlaySc02_80149350Words },
    { 0x80149374u, 0x801493d0u, kOverlaySc02_80149374Words },
    { 0x801493d0u, 0x8014942cu, kOverlaySc02_801493D0Words },
    { 0x8014942cu, 0x80149450u, kOverlaySc02_8014942CWords },
    { 0x80149450u, 0x801494ccu, kOverlaySc02_80149450Words },
    { 0x801494ccu, 0x80149544u, kOverlaySc02_801494CCWords },
    { 0x80149544u, 0x80149584u, kOverlaySc02_80149544Words },
    { 0x80149584u, 0x801495c4u, kOverlaySc02_80149584Words },
    { 0x801495c4u, 0x8014964cu, kOverlaySc02_801495C4Words },
    { 0x8014964cu, 0x801496d4u, kOverlaySc02_8014964CWords },
    { 0x801496d4u, 0x80149704u, kOverlaySc02_801496D4Words },
    { 0x80149704u, 0x80149724u, kOverlaySc02_80149704Words },
    { 0x80149724u, 0x80149744u, kOverlaySc02_80149724Words },
    { 0x80149744u, 0x80149788u, kOverlaySc02_80149744Words },
    { 0x80149788u, 0x801497a8u, kOverlaySc02_80149788Words },
    { 0x801497a8u, 0x80149864u, kOverlaySc02_801497A8Words },
    { 0x80149864u, 0x80149884u, kOverlaySc02_80149864Words },
    { 0x80149884u, 0x801498c0u, kOverlaySc02_80149884Words },
    { 0x801498c0u, 0x801498e0u, kOverlaySc02_801498C0Words },
    { 0x801498e0u, 0x80149954u, kOverlaySc02_801498E0Words },
    { 0x80149954u, 0x80149a64u, kOverlaySc02_80149954Words },
    { 0x80149a64u, 0x80149aa8u, kOverlaySc02_80149A64Words },
    { 0x80149aa8u, 0x80149ad4u, kOverlaySc02_80149AA8Words },
    { 0x80149ad4u, 0x80149b14u, kOverlaySc02_80149AD4Words },
    { 0x80149b14u, 0x80149b54u, kOverlaySc02_80149B14Words },
    { 0x80149b54u, 0x80149bacu, kOverlaySc02_80149B54Words },
    { 0x80149bacu, 0x80149becu, kOverlaySc02_80149BACWords },
    { 0x80149becu, 0x80149c08u, kOverlaySc02_80149BECWords },
    { 0x80149c08u, 0x80149c94u, kOverlaySc02_80149C08Words },
    { 0x80149c94u, 0x80149cb4u, kOverlaySc02_80149C94Words },
    { 0x80149cb4u, 0x80149cd4u, kOverlaySc02_80149CB4Words },
    { 0x80149cd4u, 0x80149d10u, kOverlaySc02_80149CD4Words },
    { 0x80149d10u, 0x80149d9cu, kOverlaySc02_80149D10Words },
    { 0x80149d9cu, 0x80149dd8u, kOverlaySc02_80149D9CWords },
    { 0x80149dd8u, 0x80149e94u, kOverlaySc02_80149DD8Words },
    { 0x80149e94u, 0x80149f2cu, kOverlaySc02_80149E94Words },
    { 0x80149f2cu, 0x80149fa8u, kOverlaySc02_80149F2CWords },
    { 0x80149fa8u, 0x80149fb0u, kOverlaySc02_80149FA8Words },
    { 0x80149fb0u, 0x8014a048u, kOverlaySc02_80149FB0Words },
    { 0x8014a048u, 0x8014a1b0u, kOverlaySc02_8014A048Words },
    { 0x8014a1b0u, 0x8014a218u, kOverlaySc02_8014A1B0Words },
    { 0x8014a218u, 0x8014a238u, kOverlaySc02_8014A218Words },
    { 0x8014a238u, 0x8014a2e4u, kOverlaySc02_8014A238Words },
    { 0x8014a2e4u, 0x8014a380u, kOverlaySc02_8014A2E4Words },
    { 0x8014a380u, 0x8014a3e0u, kOverlaySc02_8014A380Words },
    { 0x8014a3e0u, 0x8014a454u, kOverlaySc02_8014A3E0Words },
    { 0x8014a454u, 0x8014a4b4u, kOverlaySc02_8014A454Words },
    { 0x8014a4b4u, 0x8014a4fcu, kOverlaySc02_8014A4B4Words },
    { 0x8014a4fcu, 0x8014a51cu, kOverlaySc02_8014A4FCWords },
    { 0x8014a51cu, 0x8014a59cu, kOverlaySc02_8014A51CWords },
    { 0x8014a59cu, 0x8014a638u, kOverlaySc02_8014A59CWords },
    { 0x8014a638u, 0x8014a738u, kOverlaySc02_8014A638Words },
    { 0x8014a738u, 0x8014a850u, kOverlaySc02_8014A738Words },
    { 0x8014a850u, 0x8014aa04u, kOverlaySc02_8014A850Words },
    { 0x8014aa04u, 0x8014aa28u, kOverlaySc02_8014AA04Words },
    { 0x8014aa28u, 0x8014ab5cu, kOverlaySc02_8014AA28Words },
    { 0x8014ab5cu, 0x8014ab7cu, kOverlaySc02_8014AB5CWords },
    { 0x8014ab7cu, 0x8014abf0u, kOverlaySc02_8014AB7CWords },
    { 0x8014abf0u, 0x8014ac10u, kOverlaySc02_8014ABF0Words },
    { 0x8014ac10u, 0x8014acc0u, kOverlaySc02_8014AC10Words },
    { 0x8014acc0u, 0x8014ace8u, kOverlaySc02_8014ACC0Words },
    { 0x8014ace8u, 0x8014ad30u, kOverlaySc02_8014ACE8Words },
    { 0x8014ad30u, 0x8014ad7cu, kOverlaySc02_8014AD30Words },
    { 0x8014ad7cu, 0x8014ada8u, kOverlaySc02_8014AD7CWords },
    { 0x8014ada8u, 0x8014ade0u, kOverlaySc02_8014ADA8Words },
    { 0x8014ade0u, 0x8014b00cu, kOverlaySc02_8014ADE0Words },
    { 0x8014b00cu, 0x8014b034u, kOverlaySc02_8014B00CWords },
    { 0x8014b034u, 0x8014b084u, kOverlaySc02_8014B034Words },
    { 0x8014b084u, 0x8014b12cu, kOverlaySc02_8014B084Words },
    { 0x8014b12cu, 0x8014b154u, kOverlaySc02_8014B12CWords },
    { 0x8014b154u, 0x8014b160u, kOverlaySc02_8014B154Words },
    { 0x8014b160u, 0x8014b190u, kOverlaySc02_8014B160Words },
    { 0x8014b190u, 0x8014b2a8u, kOverlaySc02_8014B190Words },
    { 0x8014b2a8u, 0x8014b2d0u, kOverlaySc02_8014B2A8Words },
    { 0x8014b2d0u, 0x8014b2f8u, kOverlaySc02_8014B2D0Words },
    { 0x8014b2f8u, 0x8014b310u, kOverlaySc02_8014B2F8Words },
    { 0x8014b310u, 0x8014b33cu, kOverlaySc02_8014B310Words },
    { 0x8014b33cu, 0x8014b350u, kOverlaySc02_8014B33CWords },
    { 0x8014b350u, 0x8014b4c4u, kOverlaySc02_8014B350Words },
    { 0x8014b4c4u, 0x8014b4d4u, kOverlaySc02_8014B4C4Words },
    { 0x8014b4d4u, 0x8014b504u, kOverlaySc02_8014B4D4Words },
    { 0x8014b504u, 0x8014b598u, kOverlaySc02_8014B504Words },
    { 0x8014b598u, 0x8014b5b0u, kOverlaySc02_8014B598Words },
    { 0x8014b5b0u, 0x8014b5b8u, kOverlaySc02_8014B5B0Words },
    { 0x8014b5b8u, 0x8014b5c4u, kOverlaySc02_8014B5B8Words },
    { 0x8014b5c4u, 0x8014b5d0u, kOverlaySc02_8014B5C4Words },
    { 0x8014b5d0u, 0x8014b5d8u, kOverlaySc02_8014B5D0Words },
    { 0x8014b5d8u, 0x8014b6f0u, kOverlaySc02_8014B5D8Words },
    { 0x8014b6f0u, 0x8014b768u, kOverlaySc02_8014B6F0Words },
    { 0x8014b768u, 0x8014b7a4u, kOverlaySc02_8014B768Words },
    { 0x8014b7a4u, 0x8014b944u, kOverlaySc02_8014B7A4Words },
    { 0x8014b944u, 0x8014bb0cu, kOverlaySc02_8014B944Words },
    { 0x8014bb0cu, 0x8014bb24u, kOverlaySc02_8014BB0CWords },
    { 0x8014bb24u, 0x8014bc0cu, kOverlaySc02_8014BB24Words },
    { 0x8014bc0cu, 0x8014bc44u, kOverlaySc02_8014BC0CWords },
    { 0x8014bc44u, 0x8014bc80u, kOverlaySc02_8014BC44Words },
    { 0x8014bc80u, 0x8014bcc0u, kOverlaySc02_8014BC80Words },
    { 0x8014bcc0u, 0x8014bcecu, kOverlaySc02_8014BCC0Words },
    { 0x8014bcecu, 0x8014bd24u, kOverlaySc02_8014BCECWords },
    { 0x8014bd24u, 0x8014bd60u, kOverlaySc02_8014BD24Words },
    { 0x8014bd60u, 0x8014bd98u, kOverlaySc02_8014BD60Words },
    { 0x8014bd98u, 0x8014bdc8u, kOverlaySc02_8014BD98Words },
    { 0x8014bdc8u, 0x8014bde0u, kOverlaySc02_8014BDC8Words },
    { 0x8014bde0u, 0x8014bde8u, kOverlaySc02_8014BDE0Words },
    { 0x8014bde8u, 0x8014be78u, kOverlaySc02_8014BDE8Words },
    { 0x8014be78u, 0x8014be9cu, kOverlaySc02_8014BE78Words },
    { 0x8014be9cu, 0x8014bec0u, kOverlaySc02_8014BE9CWords },
    { 0x8014bec0u, 0x8014bef8u, kOverlaySc02_8014BEC0Words },
    { 0x8014bef8u, 0x8014bf18u, kOverlaySc02_8014BEF8Words },
    { 0x8014bf18u, 0x8014bf48u, kOverlaySc02_8014BF18Words },
    { 0x8014bf48u, 0x8014bf6cu, kOverlaySc02_8014BF48Words },
    { 0x8014bf6cu, 0x8014bf8cu, kOverlaySc02_8014BF6CWords },
    { 0x8014bf8cu, 0x8014bfb0u, kOverlaySc02_8014BF8CWords },
    { 0x8014bfb0u, 0x8014bfd4u, kOverlaySc02_8014BFB0Words },
    { 0x8014bfd4u, 0x8014bff4u, kOverlaySc02_8014BFD4Words },
    { 0x8014bff4u, 0x8014c010u, kOverlaySc02_8014BFF4Words },
    { 0x8014c010u, 0x8014c050u, kOverlaySc02_8014C010Words },
    { 0x8014c050u, 0x8014c088u, kOverlaySc02_8014C050Words },
    { 0x8014c088u, 0x8014c0c8u, kOverlaySc02_8014C088Words },
    { 0x8014c0c8u, 0x8014c118u, kOverlaySc02_8014C0C8Words },
    { 0x8014c118u, 0x8014c168u, kOverlaySc02_8014C118Words },
    { 0x8014c168u, 0x8014c1a0u, kOverlaySc02_8014C168Words },
    { 0x8014c1a0u, 0x8014c1c8u, kOverlaySc02_8014C1A0Words },
    { 0x8014c1c8u, 0x8014c278u, kOverlaySc02_8014C1C8Words },
    { 0x8014c278u, 0x8014c2b0u, kOverlaySc02_8014C278Words },
    { 0x8014c2b0u, 0x8014c308u, kOverlaySc02_8014C2B0Words },
    { 0x8014c308u, 0x8014c3a4u, kOverlaySc02_8014C308Words },
    { 0x8014c3a4u, 0x8014c3d0u, kOverlaySc02_8014C3A4Words },
    { 0x8014c3d0u, 0x8014c43cu, kOverlaySc02_8014C3D0Words },
    { 0x8014c43cu, 0x8014c4acu, kOverlaySc02_8014C43CWords },
    { 0x8014c4acu, 0x8014c568u, kOverlaySc02_8014C4ACWords },
    { 0x8014c568u, 0x8014c59cu, kOverlaySc02_8014C568Words },
    { 0x8014c59cu, 0x8014c5d0u, kOverlaySc02_8014C59CWords },
    { 0x8014c5d0u, 0x8014c5fcu, kOverlaySc02_8014C5D0Words },
    { 0x8014c5fcu, 0x8014c6acu, kOverlaySc02_8014C5FCWords },
    { 0x8014c6acu, 0x8014c6c0u, kOverlaySc02_8014C6ACWords },
    { 0x8014c6c0u, 0x8014c6d0u, kOverlaySc02_8014C6C0Words },
    { 0x8014c6e0u, 0x8014c6f4u, kOverlaySc02_8014C6E0Words },
    { 0x8014c6f4u, 0x8014c860u, kOverlaySc02_8014C6F4Words },
    { 0x8014c860u, 0x8014c88cu, kOverlaySc02_8014C860Words },
    { 0x8014c88cu, 0x8014c8c8u, kOverlaySc02_8014C88CWords },
    { 0x8014c8c8u, 0x8014c8f0u, kOverlaySc02_8014C8C8Words },
    { 0x8014c8f0u, 0x8014c918u, kOverlaySc02_8014C8F0Words },
    { 0x8014c918u, 0x8014c968u, kOverlaySc02_8014C918Words },
    { 0x80161a90u, 0x80161b18u, kOverlaySc02_80161A90Words },
    { 0x801627c0u, 0x801627e8u, kOverlaySc02_801627C0Words },
    { 0x8016533cu, 0x80165374u, kOverlaySc02_8016533CWords },
    { 0x801659dcu, 0x80165a18u, kOverlaySc02_801659DCWords },
    { 0x80165a18u, 0x80165a20u, kOverlaySc02_80165A18Words },
    { 0x8016f14cu, 0x8016f1acu, kOverlaySc02_8016F14CWords },
    { 0x8016f1c4u, 0x8016f250u, kOverlaySc02_8016F1C4Words },
    { 0x801719a4u, 0x80171a04u, kOverlaySc02_801719A4Words },
};

static const FormatterRange kFormatterRanges10[] = {
    { 0x80128218u, 0x80128228u, kOverlaySc02_80128218Words },
    { 0x80128288u, 0x801282ccu, kOverlaySc02_80128288Words },
    { 0x801288b0u, 0x801288e8u, kOverlaySc02_801288B0Words },
    { 0x80128940u, 0x80128998u, kOverlaySc02_80128940Words },
    { 0x80128998u, 0x801289f0u, kOverlaySc02_80128998Words },
    { 0x801289f0u, 0x80128a28u, kOverlaySc02_801289F0Words },
    { 0x80128c98u, 0x80128cfcu, kOverlaySc02_80128C98Words },
    { 0x80128cfcu, 0x80128d60u, kOverlaySc02_80128CFCWords },
    { 0x80128facu, 0x80129010u, kOverlaySc02_80128FACWords },
    { 0x80133784u, 0x80133ab0u, kOverlaySc02_80133784Words },
    { 0x80133ab0u, 0x80133cd4u, kOverlaySc02_80133AB0Words },
    { 0x80144b9cu, 0x801457a4u, kOverlaySc02_80144B9CWords },
    { 0x801457a4u, 0x801458e0u, kOverlaySc02_801457A4Words },
    { 0x80145ee8u, 0x80146014u, kOverlaySc02_80145EE8Words },
    { 0x80146014u, 0x80146074u, kOverlaySc02_80146014Words },
    { 0x801468c8u, 0x80146924u, kOverlaySc02_801468C8Words },
    { 0x8014c6d0u, 0x8014c6e0u, kOverlaySc02_8014C6D0Words },
    { 0x8014c968u, 0x8014c978u, kOverlaySc02_8014C968Words },
    { 0x8014c978u, 0x8014c98cu, kOverlaySc02_8014C978Words },
    { 0x8014c98cu, 0x8014c99cu, kOverlaySc02_8014C98CWords },
    { 0x8014c99cu, 0x8014ca00u, kOverlaySc02_8014C99CWords },
    { 0x8014ca00u, 0x8014ca14u, kOverlaySc02_8014CA00Words },
    { 0x8014ca14u, 0x8014ca70u, kOverlaySc02_8014CA14Words },
    { 0x8014ca70u, 0x8014ca88u, kOverlaySc02_8014CA70Words },
    { 0x8014ca88u, 0x8014cae4u, kOverlaySc02_8014CA88Words },
    { 0x8014cae4u, 0x8014cafcu, kOverlaySc02_8014CAE4Words },
    { 0x8014cafcu, 0x8014cb0cu, kOverlaySc02_8014CAFCWords },
    { 0x8014cb0cu, 0x8014cb1cu, kOverlaySc02_8014CB0CWords },
    { 0x8014cb1cu, 0x8014cb2cu, kOverlaySc02_8014CB1CWords },
    { 0x8014cb2cu, 0x8014cb58u, kOverlaySc02_8014CB2CWords },
    { 0x8014cb58u, 0x8014cb68u, kOverlaySc02_8014CB58Words },
    { 0x8014cb68u, 0x8014cb7cu, kOverlaySc02_8014CB68Words },
    { 0x8014cb7cu, 0x8014cb8cu, kOverlaySc02_8014CB7CWords },
    { 0x8014cb8cu, 0x8014cb9cu, kOverlaySc02_8014CB8CWords },
    { 0x8014cb9cu, 0x8014cbd8u, kOverlaySc02_8014CB9CWords },
    { 0x8014cbd8u, 0x8014cbe8u, kOverlaySc02_8014CBD8Words },
    { 0x8014cbe8u, 0x8014cbf8u, kOverlaySc02_8014CBE8Words },
    { 0x8014cbf8u, 0x8014cc28u, kOverlaySc02_8014CBF8Words },
    { 0x8014cc28u, 0x8014ccb4u, kOverlaySc02_8014CC28Words },
    { 0x8014ccb4u, 0x8014cd0cu, kOverlaySc02_8014CCB4Words },
    { 0x8014cd0cu, 0x8014cd80u, kOverlaySc02_8014CD0CWords },
    { 0x8014cd80u, 0x8014cf04u, kOverlaySc02_8014CD80Words },
    { 0x8014cf04u, 0x8014d04cu, kOverlaySc02_8014CF04Words },
    { 0x8014d04cu, 0x8014d0a4u, kOverlaySc02_8014D04CWords },
    { 0x8014d0a4u, 0x8014d12cu, kOverlaySc02_8014D0A4Words },
    { 0x8014d12cu, 0x8014d2a0u, kOverlaySc02_8014D12CWords },
    { 0x8014d2a0u, 0x8014d3e0u, kOverlaySc02_8014D2A0Words },
    { 0x8014d3e0u, 0x8014d438u, kOverlaySc02_8014D3E0Words },
    { 0x8014d438u, 0x8014d4c0u, kOverlaySc02_8014D438Words },
    { 0x8014d4c0u, 0x8014d610u, kOverlaySc02_8014D4C0Words },
    { 0x8014d610u, 0x8014d738u, kOverlaySc02_8014D610Words },
    { 0x8014d738u, 0x8014d790u, kOverlaySc02_8014D738Words },
    { 0x8014d790u, 0x8014d820u, kOverlaySc02_8014D790Words },
    { 0x8014d820u, 0x8014dce0u, kOverlaySc02_8014D820Words },
    { 0x8014dce0u, 0x8014dd8cu, kOverlaySc02_8014DCE0Words },
    { 0x8014dd8cu, 0x8014df3cu, kOverlaySc02_8014DD8CWords },
    { 0x8014df3cu, 0x8014df94u, kOverlaySc02_8014DF3CWords },
    { 0x8014df94u, 0x8014e048u, kOverlaySc02_8014DF94Words },
    { 0x8014e048u, 0x8014e284u, kOverlaySc02_8014E048Words },
    { 0x8014e284u, 0x8014e434u, kOverlaySc02_8014E284Words },
    { 0x8014e434u, 0x8014e48cu, kOverlaySc02_8014E434Words },
    { 0x8014e48cu, 0x8014e514u, kOverlaySc02_8014E48CWords },
    { 0x8014e514u, 0x8014e5b4u, kOverlaySc02_8014E514Words },
    { 0x8014e5b4u, 0x8014e6a0u, kOverlaySc02_8014E5B4Words },
    { 0x8014e6a0u, 0x8014e6f8u, kOverlaySc02_8014E6A0Words },
    { 0x8014e6f8u, 0x8014e790u, kOverlaySc02_8014E6F8Words },
    { 0x8014e790u, 0x8014e83cu, kOverlaySc02_8014E790Words },
    { 0x8014e83cu, 0x8014e934u, kOverlaySc02_8014E83CWords },
    { 0x8014e934u, 0x8014e98cu, kOverlaySc02_8014E934Words },
    { 0x8014e98cu, 0x8014ea4cu, kOverlaySc02_8014E98CWords },
    { 0x8014ea4cu, 0x8014ed28u, kOverlaySc02_8014EA4CWords },
    { 0x8014ed28u, 0x8014ed80u, kOverlaySc02_8014ED28Words },
    { 0x8014ed80u, 0x8014ee14u, kOverlaySc02_8014ED80Words },
    { 0x8014ee14u, 0x8014f1f4u, kOverlaySc02_8014EE14Words },
    { 0x8014f1f4u, 0x8014f24cu, kOverlaySc02_8014F1F4Words },
    { 0x8014f24cu, 0x8014f2e0u, kOverlaySc02_8014F24CWords },
    { 0x8014f2e0u, 0x8014f3e8u, kOverlaySc02_8014F2E0Words },
    { 0x8014f3e8u, 0x8014f468u, kOverlaySc02_8014F3E8Words },
    { 0x8014f468u, 0x8014f4c0u, kOverlaySc02_8014F468Words },
    { 0x8014f4c0u, 0x8014f6f4u, kOverlaySc02_8014F4C0Words },
    { 0x8014f6f4u, 0x8014f74cu, kOverlaySc02_8014F6F4Words },
    { 0x8014f74cu, 0x8014fa04u, kOverlaySc02_8014F74CWords },
    { 0x8014fa04u, 0x8014fa70u, kOverlaySc02_8014FA04Words },
    { 0x8014fa70u, 0x8014fbc0u, kOverlaySc02_8014FA70Words },
    { 0x8014fbc0u, 0x8014fc18u, kOverlaySc02_8014FBC0Words },
    { 0x8014fc18u, 0x8014fcfcu, kOverlaySc02_8014FC18Words },
    { 0x8014fcfcu, 0x8014fd54u, kOverlaySc02_8014FCFCWords },
    { 0x8014fd54u, 0x8014fdf4u, kOverlaySc02_8014FD54Words },
    { 0x8014fdf4u, 0x8014fe60u, kOverlaySc02_8014FDF4Words },
    { 0x8014fe60u, 0x8014ffdcu, kOverlaySc02_8014FE60Words },
    { 0x8014ffdcu, 0x80150150u, kOverlaySc02_8014FFDCWords },
    { 0x80150150u, 0x80150170u, kOverlaySc02_80150150Words },
    { 0x80150170u, 0x801502ecu, kOverlaySc02_80150170Words },
    { 0x801502ecu, 0x80150460u, kOverlaySc02_801502ECWords },
    { 0x80150460u, 0x80150480u, kOverlaySc02_80150460Words },
    { 0x80150480u, 0x801504d8u, kOverlaySc02_80150480Words },
    { 0x801504d8u, 0x80150528u, kOverlaySc02_801504D8Words },
    { 0x80150528u, 0x801505fcu, kOverlaySc02_80150528Words },
    { 0x801505fcu, 0x801506a4u, kOverlaySc02_801505FCWords },
    { 0x801506a4u, 0x80150820u, kOverlaySc02_801506A4Words },
    { 0x80150820u, 0x8015086cu, kOverlaySc02_80150820Words },
    { 0x8015086cu, 0x801508b4u, kOverlaySc02_8015086CWords },
    { 0x801508b4u, 0x801508f8u, kOverlaySc02_801508B4Words },
    { 0x801508f8u, 0x8015094cu, kOverlaySc02_801508F8Words },
    { 0x8015094cu, 0x80150a70u, kOverlaySc02_8015094CWords },
    { 0x80150a70u, 0x80150b28u, kOverlaySc02_80150A70Words },
    { 0x80150b28u, 0x80150b9cu, kOverlaySc02_80150B28Words },
    { 0x80150b9cu, 0x80150ba4u, kOverlaySc02_80150B9CWords },
    { 0x80150ba4u, 0x80150bc8u, kOverlaySc02_80150BA4Words },
    { 0x80150bc8u, 0x80150c48u, kOverlaySc02_80150BC8Words },
    { 0x80150c48u, 0x80150ca0u, kOverlaySc02_80150C48Words },
    { 0x80150ca0u, 0x80150cc4u, kOverlaySc02_80150CA0Words },
    { 0x80150cc4u, 0x80150ce4u, kOverlaySc02_80150CC4Words },
    { 0x80150ce4u, 0x80150d04u, kOverlaySc02_80150CE4Words },
    { 0x80150d04u, 0x80150d24u, kOverlaySc02_80150D04Words },
    { 0x80150d24u, 0x80150d44u, kOverlaySc02_80150D24Words },
    { 0x80150d44u, 0x80150d64u, kOverlaySc02_80150D44Words },
    { 0x80150d64u, 0x80150d84u, kOverlaySc02_80150D64Words },
    { 0x80150d84u, 0x80150da4u, kOverlaySc02_80150D84Words },
    { 0x80150da4u, 0x80150dc4u, kOverlaySc02_80150DA4Words },
    { 0x80150dc4u, 0x80150de4u, kOverlaySc02_80150DC4Words },
    { 0x80150de4u, 0x80150e04u, kOverlaySc02_80150DE4Words },
    { 0x80150e04u, 0x80150e24u, kOverlaySc02_80150E04Words },
    { 0x80150e24u, 0x80150e44u, kOverlaySc02_80150E24Words },
    { 0x80150e44u, 0x80150e64u, kOverlaySc02_80150E44Words },
    { 0x80150e64u, 0x80150e84u, kOverlaySc02_80150E64Words },
    { 0x80150e84u, 0x80150ea4u, kOverlaySc02_80150E84Words },
    { 0x80150ea4u, 0x80150ec4u, kOverlaySc02_80150EA4Words },
    { 0x80151944u, 0x80151980u, kOverlaySc02_80151944Words },
    { 0x80151d24u, 0x80151d60u, kOverlaySc02_80151D24Words },
    { 0x80152058u, 0x80152094u, kOverlaySc02_80152058Words },
    { 0x801520dcu, 0x80152194u, kOverlaySc02_801520DCWords },
    { 0x80152370u, 0x801523acu, kOverlaySc02_80152370Words },
    { 0x80152698u, 0x801526d4u, kOverlaySc02_80152698Words },
    { 0x8015282cu, 0x80152868u, kOverlaySc02_8015282CWords },
    { 0x801528b0u, 0x8015294cu, kOverlaySc02_801528B0Words },
    { 0x80152b6cu, 0x80152ba8u, kOverlaySc02_80152B6CWords },
    { 0x80152d24u, 0x80152d60u, kOverlaySc02_80152D24Words },
    { 0x80152da8u, 0x80152e4cu, kOverlaySc02_80152DA8Words },
    { 0x80153060u, 0x8015309cu, kOverlaySc02_80153060Words },
    { 0x80153320u, 0x8015335cu, kOverlaySc02_80153320Words },
    { 0x80153c8cu, 0x80153c9cu, kOverlaySc02_80153C8CWords },
    { 0x8015444cu, 0x801549f8u, kOverlaySc02_8015444CWords },
    { 0x80154a74u, 0x80154ab4u, kOverlaySc02_80154A74Words },
    { 0x80154ab4u, 0x80154ae0u, kOverlaySc02_80154AB4Words },
    { 0x80154ae0u, 0x80154b20u, kOverlaySc02_80154AE0Words },
    { 0x80154b20u, 0x80154b4cu, kOverlaySc02_80154B20Words },
    { 0x80154b4cu, 0x80154b7cu, kOverlaySc02_80154B4CWords },
    { 0x80154b7cu, 0x80154b98u, kOverlaySc02_80154B7CWords },
    { 0x80154b98u, 0x80154bc8u, kOverlaySc02_80154B98Words },
    { 0x80154bc8u, 0x80154be4u, kOverlaySc02_80154BC8Words },
    { 0x80154be4u, 0x80154c24u, kOverlaySc02_80154BE4Words },
    { 0x80154c24u, 0x80154ed8u, kOverlaySc02_80154C24Words },
    { 0x80154ed8u, 0x80154f9cu, kOverlaySc02_80154ED8Words },
    { 0x80154f9cu, 0x801550fcu, kOverlaySc02_80154F9CWords },
    { 0x801550fcu, 0x80155150u, kOverlaySc02_801550FCWords },
    { 0x80155150u, 0x801552f4u, kOverlaySc02_80155150Words },
    { 0x801553c0u, 0x80155440u, kOverlaySc02_801553C0Words },
    { 0x80155458u, 0x801554b8u, kOverlaySc02_80155458Words },
    { 0x801599a4u, 0x801599e0u, kOverlaySc02_801599A4Words },
    { 0x80159be4u, 0x80159c84u, kOverlaySc02_80159BE4Words },
    { 0x8015a1c8u, 0x8015a1fcu, kOverlaySc02_8015A1C8Words },
    { 0x801612b8u, 0x8016130cu, kOverlaySc02_801612B8Words },
    { 0x80165938u, 0x80165958u, kOverlaySc02_80165938Words },
    { 0x80180d74u, 0x80180db0u, kOverlaySc02_80180D74Words },
    { 0x80180db0u, 0x80180df4u, kOverlaySc02_80180DB0Words },
    { 0x80181224u, 0x8018124cu, kOverlaySc02_80181224Words },
};

static const FormatterRange kFormatterRanges11[] = {
    { 0x8012db84u, 0x8012dbd0u, kOverlaySc02_8012DB84Words },
    { 0x8013373cu, 0x80133784u, kOverlaySc02_8013373CWords },
    { 0x80133cd4u, 0x80134310u, kOverlaySc02_80133CD4Words },
    { 0x80136c90u, 0x80136d00u, kOverlaySc02_80136C90Words },
    { 0x80137b80u, 0x80137bd8u, kOverlaySc02_80137B80Words },
    { 0x8013ad38u, 0x8013af20u, kOverlaySc02_8013AD38Words },
    { 0x8013b274u, 0x8013b568u, kOverlaySc02_8013B274Words },
    { 0x8013b7acu, 0x8013b7f4u, kOverlaySc02_8013B7ACWords },
    { 0x8013b7f4u, 0x8013b83cu, kOverlaySc02_8013B7F4Words },
    { 0x8013bd34u, 0x8013bd74u, kOverlaySc02_8013BD34Words },
    { 0x8013c938u, 0x8013c964u, kOverlaySc02_8013C938Words },
    { 0x8013c964u, 0x8013c98cu, kOverlaySc02_8013C964Words },
    { 0x8013c9c4u, 0x8013ca14u, kOverlaySc02_8013C9C4Words },
    { 0x80161c24u, 0x80161c98u, kOverlaySc02_80161C24Words },
};

static const FormatterRange kFormatterRanges12[] = {
    { 0x8012e9c0u, 0x8012ea90u, kOverlaySc02_8012E9C0Words },
    { 0x8012f828u, 0x8012f87cu, kOverlaySc02_8012F828Words },
    { 0x8012f8c8u, 0x8012f91cu, kOverlaySc02_8012F8C8Words },
    { 0x8012fcc4u, 0x8012fda8u, kOverlaySc02_8012FCC4Words },
    { 0x80130d0cu, 0x80130d48u, kOverlaySc02_80130D0CWords },
    { 0x80131e00u, 0x80131e38u, kOverlaySc02_80131E00Words },
    { 0x80131eecu, 0x80131f28u, kOverlaySc02_80131EECWords },
    { 0x80131f28u, 0x80131f64u, kOverlaySc02_80131F28Words },
    { 0x80131f64u, 0x80131fa0u, kOverlaySc02_80131F64Words },
    { 0x80131fa0u, 0x80131fdcu, kOverlaySc02_80131FA0Words },
    { 0x801320d8u, 0x80132144u, kOverlaySc02_801320D8Words },
    { 0x80132144u, 0x801321b0u, kOverlaySc02_80132144Words },
    { 0x801321b0u, 0x8013221cu, kOverlaySc02_801321B0Words },
    { 0x80136c54u, 0x80136c90u, kOverlaySc02_80136C54Words },
    { 0x80137d08u, 0x80137dd4u, kOverlaySc02_80137D08Words },
    { 0x80138be0u, 0x80138c30u, kOverlaySc02_80138BE0Words },
    { 0x8013bc7cu, 0x8013bcdcu, kOverlaySc02_8013BC7CWords },
    { 0x8013d064u, 0x8013d13cu, kOverlaySc02_8013D064Words },
    { 0x8013d13cu, 0x8013d164u, kOverlaySc02_8013D13CWords },
    { 0x8013d164u, 0x8013d178u, kOverlaySc02_8013D164Words },
    { 0x8013d9b0u, 0x8013dbe4u, kOverlaySc02_8013D9B0Words },
    { 0x8013e054u, 0x8013e064u, kOverlaySc02_8013E054Words },
    { 0x80140f00u, 0x80141100u, kOverlaySc02_80140F00Words },
    { 0x8014358cu, 0x80143640u, kOverlaySc02_8014358CWords },
    { 0x80153cccu, 0x80153d34u, kOverlaySc02_80153CCCWords },
    { 0x80157788u, 0x801577c8u, kOverlaySc02_80157788Words },
    { 0x801577c8u, 0x80157808u, kOverlaySc02_801577C8Words },
    { 0x80157808u, 0x80157880u, kOverlaySc02_80157808Words },
    { 0x8015879cu, 0x80158814u, kOverlaySc02_8015879CWords },
    { 0x80158814u, 0x80158880u, kOverlaySc02_80158814Words },
    { 0x80158fa4u, 0x80159070u, kOverlaySc02_80158FA4Words },
    { 0x8015934cu, 0x801593e4u, kOverlaySc02_8015934CWords },
    { 0x8015c7e4u, 0x8015c944u, kOverlaySc02_8015C7E4Words },
    { 0x8015ca28u, 0x8015cb94u, kOverlaySc02_8015CA28Words },
    { 0x8015cd20u, 0x8015cf24u, kOverlaySc02_8015CD20Words },
    { 0x8015d5e8u, 0x8015d738u, kOverlaySc02_8015D5E8Words },
    { 0x8016216cu, 0x801621ccu, kOverlaySc02_8016216CWords },
    { 0x801622c4u, 0x80162330u, kOverlaySc02_801622C4Words },
    { 0x80162760u, 0x801627c0u, kOverlaySc02_80162760Words },
    { 0x80163408u, 0x8016345cu, kOverlaySc02_80163408Words },
    { 0x801634d8u, 0x80163534u, kOverlaySc02_801634D8Words },
    { 0x80164ee0u, 0x80164f44u, kOverlaySc02_80164EE0Words },
    { 0x80165e2cu, 0x80165e90u, kOverlaySc02_80165E2CWords },
    { 0x80169f3cu, 0x80169fe0u, kOverlaySc02_80169F3CWords },
    { 0x8016b9f8u, 0x8016ba48u, kOverlaySc02_8016B9F8Words },
    { 0x8016bea0u, 0x8016bf34u, kOverlaySc02_8016BEA0Words },
    { 0x8016bfa8u, 0x8016bfd0u, kOverlaySc02_8016BFA8Words },
    { 0x8016da7cu, 0x8016db34u, kOverlaySc02_8016DA7CWords },
    { 0x80178438u, 0x8017849cu, kOverlaySc02_80178438Words },
    { 0x80178840u, 0x801788b8u, kOverlaySc02_80178840Words },
    { 0x80178cbcu, 0x80178d18u, kOverlaySc02_80178CBCWords },
    { 0x80178d18u, 0x80178d40u, kOverlaySc02_80178D18Words },
    { 0x8017a094u, 0x8017a0c4u, kOverlaySc02_8017A094Words },
    { 0x8017a0c4u, 0x8017a0f4u, kOverlaySc02_8017A0C4Words },
    { 0x8017a144u, 0x8017a180u, kOverlaySc02_8017A144Words },
    { 0x8017b1d8u, 0x8017b238u, kOverlaySc02_8017B1D8Words },
    { 0x8017b7a8u, 0x8017b824u, kOverlaySc02_8017B7A8Words },
    { 0x8017b880u, 0x8017b8e8u, kOverlaySc02_8017B880Words },
    { 0x8017b8e8u, 0x8017b940u, kOverlaySc02_8017B8E8Words },
    { 0x8017bc38u, 0x8017bca0u, kOverlaySc02_8017BC38Words },
    { 0x8017bca0u, 0x8017bcf4u, kOverlaySc02_8017BCA0Words },
    { 0x8017bcf4u, 0x8017bd50u, kOverlaySc02_8017BCF4Words },
};

static const FormatterRange kFormatterRanges13[] = {
    { 0x80141788u, 0x801417c4u, kOverlaySc02_80141788Words },
    { 0x80141c0cu, 0x80141c50u, kOverlaySc02_80141C0CWords },
    { 0x801425ccu, 0x80142608u, kOverlaySc02_801425CCWords },
    { 0x801427ecu, 0x80142838u, kOverlaySc02_801427ECWords },
    { 0x8014292cu, 0x80142978u, kOverlaySc02_8014292CWords },
    { 0x80142978u, 0x801429c4u, kOverlaySc02_80142978Words },
    { 0x801429c4u, 0x80142a10u, kOverlaySc02_801429C4Words },
    { 0x80142a10u, 0x80142a80u, kOverlaySc02_80142A10Words },
    { 0x80143458u, 0x8014350cu, kOverlaySc02_80143458Words },
    { 0x80143b30u, 0x80143b6cu, kOverlaySc02_80143B30Words },
    { 0x80143c38u, 0x80143c74u, kOverlaySc02_80143C38Words },
    { 0x80143c98u, 0x80143cd4u, kOverlaySc02_80143C98Words },
    { 0x80143e68u, 0x80143ea4u, kOverlaySc02_80143E68Words },
    { 0x80155580u, 0x801555bcu, kOverlaySc02_80155580Words },
    { 0x801563ecu, 0x8015640cu, kOverlaySc02_801563ECWords },
    { 0x80156a1cu, 0x80156a88u, kOverlaySc02_80156A1CWords },
    { 0x80157544u, 0x80157580u, kOverlaySc02_80157544Words },
    { 0x801578c0u, 0x8015795cu, kOverlaySc02_801578C0Words },
    { 0x80157d20u, 0x80157d74u, kOverlaySc02_80157D20Words },
    { 0x80157dc4u, 0x80157e00u, kOverlaySc02_80157DC4Words },
    { 0x80157fc4u, 0x80158000u, kOverlaySc02_80157FC4Words },
    { 0x80158038u, 0x801580b4u, kOverlaySc02_80158038Words },
    { 0x8015824cu, 0x80158288u, kOverlaySc02_8015824CWords },
    { 0x80158880u, 0x801588ccu, kOverlaySc02_80158880Words },
    { 0x80159698u, 0x801596d4u, kOverlaySc02_80159698Words },
    { 0x80159968u, 0x801599a4u, kOverlaySc02_80159968Words },
    { 0x80159b70u, 0x80159bacu, kOverlaySc02_80159B70Words },
    { 0x8015a264u, 0x8015a2a0u, kOverlaySc02_8015A264Words },
    { 0x8015ac48u, 0x8015ac90u, kOverlaySc02_8015AC48Words },
    { 0x8015ad3cu, 0x8015ad78u, kOverlaySc02_8015AD3CWords },
    { 0x8015be38u, 0x8015be74u, kOverlaySc02_8015BE38Words },
    { 0x8015bff4u, 0x8015c030u, kOverlaySc02_8015BFF4Words },
    { 0x8015c714u, 0x8015c750u, kOverlaySc02_8015C714Words },
    { 0x8015c944u, 0x8015ca28u, kOverlaySc02_8015C944Words },
    { 0x8015cc74u, 0x8015ccb0u, kOverlaySc02_8015CC74Words },
    { 0x8015cfc0u, 0x8015cffcu, kOverlaySc02_8015CFC0Words },
    { 0x8015d01cu, 0x8015d104u, kOverlaySc02_8015D01CWords },
    { 0x8015d104u, 0x8015d1b8u, kOverlaySc02_8015D104Words },
    { 0x8015d414u, 0x8015d480u, kOverlaySc02_8015D414Words },
    { 0x8015d4e8u, 0x8015d524u, kOverlaySc02_8015D4E8Words },
    { 0x8015daf8u, 0x8015db34u, kOverlaySc02_8015DAF8Words },
    { 0x8015dbd4u, 0x8015dc84u, kOverlaySc02_8015DBD4Words },
    { 0x8015de58u, 0x8015de94u, kOverlaySc02_8015DE58Words },
    { 0x8015df34u, 0x8015dfe4u, kOverlaySc02_8015DF34Words },
    { 0x8015e1b8u, 0x8015e1f4u, kOverlaySc02_8015E1B8Words },
    { 0x8015e344u, 0x8015e40cu, kOverlaySc02_8015E344Words },
    { 0x8015e588u, 0x8015e5b0u, kOverlaySc02_8015E588Words },
    { 0x8015e698u, 0x8015e714u, kOverlaySc02_8015E698Words },
    { 0x8015e8e8u, 0x8015e924u, kOverlaySc02_8015E8E8Words },
    { 0x8015ee08u, 0x8015ee44u, kOverlaySc02_8015EE08Words },
    { 0x8015ee7cu, 0x8015eee0u, kOverlaySc02_8015EE7CWords },
    { 0x8015eee0u, 0x8015ef9cu, kOverlaySc02_8015EEE0Words },
    { 0x8015f00cu, 0x8015f048u, kOverlaySc02_8015F00CWords },
    { 0x8015f118u, 0x8015f260u, kOverlaySc02_8015F118Words },
    { 0x8015f324u, 0x8015f360u, kOverlaySc02_8015F324Words },
    { 0x8015f7d4u, 0x8015f810u, kOverlaySc02_8015F7D4Words },
    { 0x8015f9a4u, 0x8015fa24u, kOverlaySc02_8015F9A4Words },
    { 0x8015faacu, 0x8015fae8u, kOverlaySc02_8015FAACWords },
    { 0x8015fbe0u, 0x8015fcc8u, kOverlaySc02_8015FBE0Words },
    { 0x8015fcc8u, 0x8015fd74u, kOverlaySc02_8015FCC8Words },
    { 0x8015fd74u, 0x8015fdccu, kOverlaySc02_8015FD74Words },
    { 0x8015fe70u, 0x8015ff20u, kOverlaySc02_8015FE70Words },
    { 0x80160138u, 0x80160174u, kOverlaySc02_80160138Words },
    { 0x801602a4u, 0x8016032cu, kOverlaySc02_801602A4Words },
    { 0x8016039cu, 0x801603d8u, kOverlaySc02_8016039CWords },
    { 0x8016084cu, 0x80160888u, kOverlaySc02_8016084CWords },
    { 0x80160920u, 0x801609b8u, kOverlaySc02_80160920Words },
    { 0x801609b8u, 0x80160a28u, kOverlaySc02_801609B8Words },
    { 0x80160b34u, 0x80160b70u, kOverlaySc02_80160B34Words },
    { 0x80160ea4u, 0x80160ee0u, kOverlaySc02_80160EA4Words },
    { 0x80161034u, 0x80161094u, kOverlaySc02_80161034Words },
    { 0x80161c98u, 0x80161cd0u, kOverlaySc02_80161C98Words },
    { 0x80161cd0u, 0x80161d20u, kOverlaySc02_80161CD0Words },
    { 0x80161d20u, 0x80161d58u, kOverlaySc02_80161D20Words },
    { 0x80161d88u, 0x80161e08u, kOverlaySc02_80161D88Words },
    { 0x80162330u, 0x8016236cu, kOverlaySc02_80162330Words },
    { 0x80162834u, 0x80162870u, kOverlaySc02_80162834Words },
    { 0x80162870u, 0x801628f4u, kOverlaySc02_80162870Words },
};

static const FormatterRange kFormatterRanges14[] = {
    { 0x80163a58u, 0x80163a94u, kOverlaySc02_80163A58Words },
    { 0x80164744u, 0x801647a4u, kOverlaySc02_80164744Words },
    { 0x80164ba0u, 0x80164bdcu, kOverlaySc02_80164BA0Words },
    { 0x80164ea4u, 0x80164ee0u, kOverlaySc02_80164EA4Words },
    { 0x80165580u, 0x801655e4u, kOverlaySc02_80165580Words },
    { 0x80165658u, 0x80165670u, kOverlaySc02_80165658Words },
    { 0x80165670u, 0x80165694u, kOverlaySc02_80165670Words },
    { 0x801656d0u, 0x801656e8u, kOverlaySc02_801656D0Words },
    { 0x801656e8u, 0x80165700u, kOverlaySc02_801656E8Words },
    { 0x80165700u, 0x80165718u, kOverlaySc02_80165700Words },
    { 0x80165ac8u, 0x80165b08u, kOverlaySc02_80165AC8Words },
    { 0x80165b28u, 0x80165b6cu, kOverlaySc02_80165B28Words },
    { 0x80166018u, 0x80166054u, kOverlaySc02_80166018Words },
};

static const FormatterRange kFormatterRanges15[] = {
    { 0x801663fcu, 0x80166438u, kOverlaySc02_801663FCWords },
    { 0x80166618u, 0x80166654u, kOverlaySc02_80166618Words },
    { 0x80166654u, 0x80166690u, kOverlaySc02_80166654Words },
    { 0x801678b4u, 0x801678f0u, kOverlaySc02_801678B4Words },
    { 0x80167a9cu, 0x80167ad8u, kOverlaySc02_80167A9CWords },
    { 0x80168744u, 0x80168780u, kOverlaySc02_80168744Words },
    { 0x801689d8u, 0x80168a14u, kOverlaySc02_801689D8Words },
    { 0x80168aa8u, 0x80168ae4u, kOverlaySc02_80168AA8Words },
    { 0x80168d58u, 0x80168d94u, kOverlaySc02_80168D58Words },
    { 0x8016901cu, 0x80169058u, kOverlaySc02_8016901CWords },
    { 0x801693ccu, 0x80169408u, kOverlaySc02_801693CCWords },
    { 0x80169830u, 0x8016986cu, kOverlaySc02_80169830Words },
    { 0x80169b80u, 0x80169bbcu, kOverlaySc02_80169B80Words },
    { 0x80169f00u, 0x80169f3cu, kOverlaySc02_80169F00Words },
    { 0x8016a020u, 0x8016a05cu, kOverlaySc02_8016A020Words },
    { 0x8016a700u, 0x8016a73cu, kOverlaySc02_8016A700Words },
    { 0x8016ab30u, 0x8016ab6cu, kOverlaySc02_8016AB30Words },
    { 0x8016b4bcu, 0x8016b4f8u, kOverlaySc02_8016B4BCWords },
    { 0x8016bba4u, 0x8016bbe0u, kOverlaySc02_8016BBA4Words },
    { 0x8016c14cu, 0x8016c188u, kOverlaySc02_8016C14CWords },
    { 0x8016cb84u, 0x8016cbc0u, kOverlaySc02_8016CB84Words },
    { 0x8016d19cu, 0x8016d1d8u, kOverlaySc02_8016D19CWords },
    { 0x8016d428u, 0x8016d464u, kOverlaySc02_8016D428Words },
    { 0x8016da30u, 0x8016da7cu, kOverlaySc02_8016DA30Words },
    { 0x8016dea4u, 0x8016dee0u, kOverlaySc02_8016DEA4Words },
    { 0x8016df20u, 0x8016df5cu, kOverlaySc02_8016DF20Words },
    { 0x8016e5b8u, 0x8016e5f4u, kOverlaySc02_8016E5B8Words },
    { 0x8016eac0u, 0x8016eb3cu, kOverlaySc02_8016EAC0Words },
    { 0x8016f6e0u, 0x8016f71cu, kOverlaySc02_8016F6E0Words },
    { 0x8016f798u, 0x8016f7d4u, kOverlaySc02_8016F798Words },
    { 0x8016f834u, 0x8016f870u, kOverlaySc02_8016F834Words },
    { 0x8016f8e4u, 0x8016f920u, kOverlaySc02_8016F8E4Words },
    { 0x8016f9c4u, 0x8016fa00u, kOverlaySc02_8016F9C4Words },
    { 0x8016fa84u, 0x8016fac0u, kOverlaySc02_8016FA84Words },
    { 0x8016fb7cu, 0x8016fbb8u, kOverlaySc02_8016FB7CWords },
    { 0x8016fc90u, 0x8016fcccu, kOverlaySc02_8016FC90Words },
    { 0x8016fdb4u, 0x8016fdf0u, kOverlaySc02_8016FDB4Words },
    { 0x8016ff30u, 0x8016ff6cu, kOverlaySc02_8016FF30Words },
    { 0x8016ffdcu, 0x80170018u, kOverlaySc02_8016FFDCWords },
    { 0x80170150u, 0x8017018cu, kOverlaySc02_80170150Words },
    { 0x80170240u, 0x8017027cu, kOverlaySc02_80170240Words },
    { 0x801702fcu, 0x80170338u, kOverlaySc02_801702FCWords },
    { 0x801703e0u, 0x8017041cu, kOverlaySc02_801703E0Words },
    { 0x801704b0u, 0x801704ecu, kOverlaySc02_801704B0Words },
    { 0x80170548u, 0x80170584u, kOverlaySc02_80170548Words },
    { 0x801705f8u, 0x80170634u, kOverlaySc02_801705F8Words },
    { 0x801706acu, 0x801706e8u, kOverlaySc02_801706ACWords },
    { 0x80170748u, 0x80170784u, kOverlaySc02_80170748Words },
    { 0x80170810u, 0x8017084cu, kOverlaySc02_80170810Words },
    { 0x80170ad8u, 0x80170b14u, kOverlaySc02_80170AD8Words },
    { 0x80170bd8u, 0x80170c14u, kOverlaySc02_80170BD8Words },
    { 0x80170c74u, 0x80170cb0u, kOverlaySc02_80170C74Words },
    { 0x80170d68u, 0x80170da4u, kOverlaySc02_80170D68Words },
    { 0x80170e34u, 0x80170e70u, kOverlaySc02_80170E34Words },
    { 0x80170efcu, 0x80170f38u, kOverlaySc02_80170EFCWords },
    { 0x80170fb0u, 0x80170fecu, kOverlaySc02_80170FB0Words },
    { 0x80171064u, 0x801710a0u, kOverlaySc02_80171064Words },
    { 0x80171120u, 0x8017115cu, kOverlaySc02_80171120Words },
    { 0x801711c0u, 0x801711fcu, kOverlaySc02_801711C0Words },
    { 0x80171260u, 0x8017129cu, kOverlaySc02_80171260Words },
    { 0x801714e4u, 0x80171520u, kOverlaySc02_801714E4Words },
    { 0x801727d0u, 0x8017280cu, kOverlaySc02_801727D0Words },
    { 0x801728e4u, 0x80172920u, kOverlaySc02_801728E4Words },
    { 0x801729f0u, 0x80172a2cu, kOverlaySc02_801729F0Words },
    { 0x80172b44u, 0x80172b80u, kOverlaySc02_80172B44Words },
    { 0x80172ca0u, 0x80172cdcu, kOverlaySc02_80172CA0Words },
    { 0x80172dacu, 0x80172de8u, kOverlaySc02_80172DACWords },
    { 0x80173078u, 0x801730b4u, kOverlaySc02_80173078Words },
    { 0x8017319cu, 0x801731d8u, kOverlaySc02_8017319CWords },
    { 0x80173220u, 0x80173294u, kOverlaySc02_80173220Words },
    { 0x80173544u, 0x80173580u, kOverlaySc02_80173544Words },
    { 0x801736fcu, 0x80173738u, kOverlaySc02_801736FCWords },
    { 0x801737e8u, 0x80173824u, kOverlaySc02_801737E8Words },
    { 0x8017390cu, 0x80173948u, kOverlaySc02_8017390CWords },
    { 0x80173b4cu, 0x80173b88u, kOverlaySc02_80173B4CWords },
    { 0x801742a4u, 0x801742e0u, kOverlaySc02_801742A4Words },
    { 0x80174384u, 0x801743c0u, kOverlaySc02_80174384Words },
    { 0x80174474u, 0x801744b0u, kOverlaySc02_80174474Words },
    { 0x801747ccu, 0x80174808u, kOverlaySc02_801747CCWords },
    { 0x80174888u, 0x801748c4u, kOverlaySc02_80174888Words },
    { 0x8017496cu, 0x801749a8u, kOverlaySc02_8017496CWords },
    { 0x80174bf4u, 0x80174c60u, kOverlaySc02_80174BF4Words },
    { 0x80174f28u, 0x80174f64u, kOverlaySc02_80174F28Words },
    { 0x80175184u, 0x801751d8u, kOverlaySc02_80175184Words },
    { 0x8017553cu, 0x80175590u, kOverlaySc02_8017553CWords },
    { 0x80175690u, 0x801756e4u, kOverlaySc02_80175690Words },
};

static const FormatterRange kFormatterRanges16[] = {
    { 0x80128178u, 0x80128198u, kOverlaySc02_80128178Words },
    { 0x80128198u, 0x801281b8u, kOverlaySc02_80128198Words },
    { 0x801281b8u, 0x801281d8u, kOverlaySc02_801281B8Words },
    { 0x801281d8u, 0x801281f8u, kOverlaySc02_801281D8Words },
    { 0x801281f8u, 0x80128218u, kOverlaySc02_801281F8Words },
    { 0x80128228u, 0x80128248u, kOverlaySc02_80128228Words },
    { 0x80128248u, 0x80128268u, kOverlaySc02_80128248Words },
    { 0x80128268u, 0x80128288u, kOverlaySc02_80128268Words },
    { 0x801282ccu, 0x801282ecu, kOverlaySc02_801282CCWords },
    { 0x801282ecu, 0x8012832cu, kOverlaySc02_801282ECWords },
    { 0x80128d60u, 0x80128db4u, kOverlaySc02_80128D60Words },
    { 0x80128ea8u, 0x80128ed8u, kOverlaySc02_80128EA8Words },
    { 0x8017be60u, 0x8017be9cu, kOverlaySc02_8017BE60Words },
};

static const FormatterRange kFormatterRanges17[] = {
    { 0x801290dcu, 0x8012913cu, kOverlaySc02_801290DCWords },
    { 0x8012913cu, 0x801291c0u, kOverlaySc02_8012913CWords },
    { 0x801291c0u, 0x80129220u, kOverlaySc02_801291C0Words },
    { 0x8012927cu, 0x801292c8u, kOverlaySc02_8012927CWords },
    { 0x801292c8u, 0x8012931cu, kOverlaySc02_801292C8Words },
    { 0x8012931cu, 0x80129350u, kOverlaySc02_8012931CWords },
    { 0x80129350u, 0x80129374u, kOverlaySc02_80129350Words },
    { 0x80129374u, 0x80129398u, kOverlaySc02_80129374Words },
    { 0x80129428u, 0x8012943cu, kOverlaySc02_80129428Words },
    { 0x8012943cu, 0x8012944cu, kOverlaySc02_8012943CWords },
    { 0x80129ff4u, 0x8012a018u, kOverlaySc02_80129FF4Words },
    { 0x8012a0e0u, 0x8012a100u, kOverlaySc02_8012A0E0Words },
    { 0x8012a100u, 0x8012a110u, kOverlaySc02_8012A100Words },
    { 0x8012a110u, 0x8012a1bcu, kOverlaySc02_8012A110Words },
    { 0x8012a2f4u, 0x8012a304u, kOverlaySc02_8012A2F4Words },
    { 0x8012a304u, 0x8012a328u, kOverlaySc02_8012A304Words },
    { 0x8012a418u, 0x8012a464u, kOverlaySc02_8012A418Words },
    { 0x8012a464u, 0x8012a4bcu, kOverlaySc02_8012A464Words },
    { 0x8012a4bcu, 0x8012a568u, kOverlaySc02_8012A4BCWords },
    { 0x8012a568u, 0x8012a598u, kOverlaySc02_8012A568Words },
    { 0x8012a598u, 0x8012a5f8u, kOverlaySc02_8012A598Words },
    { 0x8012a5f8u, 0x8012a62cu, kOverlaySc02_8012A5F8Words },
    { 0x8012a62cu, 0x8012a68cu, kOverlaySc02_8012A62CWords },
    { 0x8012a68cu, 0x8012a6d0u, kOverlaySc02_8012A68CWords },
    { 0x8012a6d0u, 0x8012a758u, kOverlaySc02_8012A6D0Words },
    { 0x8012a758u, 0x8012a79cu, kOverlaySc02_8012A758Words },
    { 0x8012a79cu, 0x8012a7d4u, kOverlaySc02_8012A79CWords },
    { 0x8012a7d4u, 0x8012a828u, kOverlaySc02_8012A7D4Words },
    { 0x8012a860u, 0x8012a8b0u, kOverlaySc02_8012A860Words },
    { 0x8012a8b0u, 0x8012a8e8u, kOverlaySc02_8012A8B0Words },
    { 0x8012a8e8u, 0x8012a908u, kOverlaySc02_8012A8E8Words },
    { 0x8012a908u, 0x8012a988u, kOverlaySc02_8012A908Words },
};

static const FormatterRange kFormatterRanges18[] = {
    { 0x8012ad3cu, 0x8012ad44u, kOverlaySc02_8012AD3CWords },
    { 0x8012ad64u, 0x8012ad6cu, kOverlaySc02_8012AD64Words },
    { 0x8012ad6cu, 0x8012ad80u, kOverlaySc02_8012AD6CWords },
    { 0x8012ad80u, 0x8012ade4u, kOverlaySc02_8012AD80Words },
    { 0x8012ade4u, 0x8012ae00u, kOverlaySc02_8012ADE4Words },
    { 0x8012b178u, 0x8012b1b4u, kOverlaySc02_8012B178Words },
    { 0x8012b1b4u, 0x8012b200u, kOverlaySc02_8012B1B4Words },
    { 0x8012b200u, 0x8012b21cu, kOverlaySc02_8012B200Words },
    { 0x8012b21cu, 0x8012b23cu, kOverlaySc02_8012B21CWords },
    { 0x8012b23cu, 0x8012b260u, kOverlaySc02_8012B23CWords },
    { 0x8012b370u, 0x8012b414u, kOverlaySc02_8012B370Words },
    { 0x8012b414u, 0x8012b4b8u, kOverlaySc02_8012B414Words },
    { 0x8012b6d4u, 0x8012b70cu, kOverlaySc02_8012B6D4Words },
    { 0x8012b70cu, 0x8012b744u, kOverlaySc02_8012B70CWords },
    { 0x8012b744u, 0x8012b77cu, kOverlaySc02_8012B744Words },
    { 0x8012b864u, 0x8012b8a4u, kOverlaySc02_8012B864Words },
    { 0x8012b8a4u, 0x8012b8e4u, kOverlaySc02_8012B8A4Words },
    { 0x8012bc60u, 0x8012bcccu, kOverlaySc02_8012BC60Words },
    { 0x8012bd14u, 0x8012bd3cu, kOverlaySc02_8012BD14Words },
    { 0x8012bd3cu, 0x8012bdbcu, kOverlaySc02_8012BD3CWords },
    { 0x8012be54u, 0x8012be98u, kOverlaySc02_8012BE54Words },
    { 0x8012be98u, 0x8012bee8u, kOverlaySc02_8012BE98Words },
    { 0x8012bf4cu, 0x8012bf54u, kOverlaySc02_8012BF4CWords },
    { 0x8012bf54u, 0x8012bf68u, kOverlaySc02_8012BF54Words },
    { 0x8012bf68u, 0x8012bf7cu, kOverlaySc02_8012BF68Words },
    { 0x8012bf7cu, 0x8012bfa8u, kOverlaySc02_8012BF7CWords },
    { 0x8012bfa8u, 0x8012c044u, kOverlaySc02_8012BFA8Words },
    { 0x8012c044u, 0x8012c098u, kOverlaySc02_8012C044Words },
    { 0x8012c098u, 0x8012c0ecu, kOverlaySc02_8012C098Words },
    { 0x8012c31cu, 0x8012c354u, kOverlaySc02_8012C31CWords },
    { 0x8012c724u, 0x8012c750u, kOverlaySc02_8012C724Words },
    { 0x8012cba4u, 0x8012cbccu, kOverlaySc02_8012CBA4Words },
    { 0x8012cbccu, 0x8012cbf4u, kOverlaySc02_8012CBCCWords },
    { 0x8012cbf4u, 0x8012cc1cu, kOverlaySc02_8012CBF4Words },
    { 0x8012cc1cu, 0x8012cc40u, kOverlaySc02_8012CC1CWords },
    { 0x8012cc40u, 0x8012cc64u, kOverlaySc02_8012CC40Words },
    { 0x8012cc64u, 0x8012cc88u, kOverlaySc02_8012CC64Words },
    { 0x8012d38cu, 0x8012d3acu, kOverlaySc02_8012D38CWords },
    { 0x8012d3b4u, 0x8012d4b4u, kOverlaySc02_8012D3B4Words },
    { 0x8012d4b4u, 0x8012d5dcu, kOverlaySc02_8012D4B4Words },
    { 0x8012d5e4u, 0x8012d624u, kOverlaySc02_8012D5E4Words },
    { 0x8012d624u, 0x8012d664u, kOverlaySc02_8012D624Words },
    { 0x8012dfd4u, 0x8012e014u, kOverlaySc02_8012DFD4Words },
    { 0x8012e27cu, 0x8012e284u, kOverlaySc02_8012E27CWords },
    { 0x8012e284u, 0x8012e28cu, kOverlaySc02_8012E284Words },
    { 0x8012e28cu, 0x8012e32cu, kOverlaySc02_8012E28CWords },
    { 0x8012e32cu, 0x8012e364u, kOverlaySc02_8012E32CWords },
    { 0x8012e504u, 0x8012e544u, kOverlaySc02_8012E504Words },
    { 0x8012e544u, 0x8012e57cu, kOverlaySc02_8012E544Words },
    { 0x8012e57cu, 0x8012e5ccu, kOverlaySc02_8012E57CWords },
    { 0x8012e778u, 0x8012e88cu, kOverlaySc02_8012E778Words },
    { 0x8012e88cu, 0x8012e8a8u, kOverlaySc02_8012E88CWords },
    { 0x8012e8a8u, 0x8012e8c4u, kOverlaySc02_8012E8A8Words },
    { 0x8012e8c4u, 0x8012e8e0u, kOverlaySc02_8012E8C4Words },
    { 0x8012ec04u, 0x8012eeccu, kOverlaySc02_8012EC04Words },
    { 0x8012eeccu, 0x8012ef34u, kOverlaySc02_8012EECCWords },
    { 0x8012ef34u, 0x8012ef70u, kOverlaySc02_8012EF34Words },
    { 0x8012ef70u, 0x8012efb8u, kOverlaySc02_8012EF70Words },
    { 0x8012efb8u, 0x8012f038u, kOverlaySc02_8012EFB8Words },
    { 0x8012f038u, 0x8012f0bcu, kOverlaySc02_8012F038Words },
    { 0x8012f0bcu, 0x8012f14cu, kOverlaySc02_8012F0BCWords },
    { 0x8012f1a4u, 0x8012f214u, kOverlaySc02_8012F1A4Words },
    { 0x8012f214u, 0x8012f274u, kOverlaySc02_8012F214Words },
    { 0x8012f2e8u, 0x8012f374u, kOverlaySc02_8012F2E8Words },
    { 0x8012f374u, 0x8012f40cu, kOverlaySc02_8012F374Words },
    { 0x8012f5f4u, 0x8012f68cu, kOverlaySc02_8012F5F4Words },
    { 0x8012f75cu, 0x8012f7b4u, kOverlaySc02_8012F75CWords },
    { 0x8012f7b4u, 0x8012f828u, kOverlaySc02_8012F7B4Words },
    { 0x8012f87cu, 0x8012f8c8u, kOverlaySc02_8012F87CWords },
    { 0x8012f91cu, 0x8012f968u, kOverlaySc02_8012F91CWords },
    { 0x8012fb54u, 0x8012fc30u, kOverlaySc02_8012FB54Words },
    { 0x8012fc30u, 0x8012fca4u, kOverlaySc02_8012FC30Words },
    { 0x8012fca4u, 0x8012fcc4u, kOverlaySc02_8012FCA4Words },
    { 0x8012fda8u, 0x8012fe70u, kOverlaySc02_8012FDA8Words },
    { 0x8012fe70u, 0x8012ff00u, kOverlaySc02_8012FE70Words },
    { 0x8012ff00u, 0x8012ff4cu, kOverlaySc02_8012FF00Words },
    { 0x8012ff4cu, 0x8012ff98u, kOverlaySc02_8012FF4CWords },
    { 0x8012ff98u, 0x8013001cu, kOverlaySc02_8012FF98Words },
    { 0x80130278u, 0x80130314u, kOverlaySc02_80130278Words },
    { 0x80130314u, 0x80130360u, kOverlaySc02_80130314Words },
    { 0x80130360u, 0x801303a0u, kOverlaySc02_80130360Words },
    { 0x801303a0u, 0x801303ecu, kOverlaySc02_801303A0Words },
    { 0x801303ecu, 0x80130438u, kOverlaySc02_801303ECWords },
    { 0x80130514u, 0x801305ccu, kOverlaySc02_80130514Words },
    { 0x801305ccu, 0x80130650u, kOverlaySc02_801305CCWords },
    { 0x80130650u, 0x80130740u, kOverlaySc02_80130650Words },
    { 0x80130740u, 0x801307b0u, kOverlaySc02_80130740Words },
    { 0x801307b0u, 0x80130858u, kOverlaySc02_801307B0Words },
    { 0x80130858u, 0x80130898u, kOverlaySc02_80130858Words },
    { 0x80130898u, 0x801308dcu, kOverlaySc02_80130898Words },
    { 0x801308dcu, 0x80130974u, kOverlaySc02_801308DCWords },
    { 0x80130974u, 0x80130a18u, kOverlaySc02_80130974Words },
    { 0x80130a18u, 0x80130ac4u, kOverlaySc02_80130A18Words },
    { 0x80130af0u, 0x80130c08u, kOverlaySc02_80130AF0Words },
    { 0x801319e0u, 0x80131a34u, kOverlaySc02_801319E0Words },
    { 0x80131c78u, 0x80131ca8u, kOverlaySc02_80131C78Words },
    { 0x80131d68u, 0x80131e00u, kOverlaySc02_80131D68Words },
    { 0x80131e38u, 0x80131e7cu, kOverlaySc02_80131E38Words },
    { 0x80131e7cu, 0x80131ee4u, kOverlaySc02_80131E7CWords },
    { 0x80132784u, 0x80132dc4u, kOverlaySc02_80132784Words },
    { 0x80132dc4u, 0x80132e6cu, kOverlaySc02_80132DC4Words },
    { 0x80132e6cu, 0x80132ec4u, kOverlaySc02_80132E6CWords },
    { 0x80132ec4u, 0x80132ef4u, kOverlaySc02_80132EC4Words },
    { 0x80132ef4u, 0x80132f40u, kOverlaySc02_80132EF4Words },
    { 0x80133060u, 0x801330e0u, kOverlaySc02_80133060Words },
    { 0x801330e0u, 0x80133298u, kOverlaySc02_801330E0Words },
    { 0x80134310u, 0x8013435cu, kOverlaySc02_80134310Words },
    { 0x8013435cu, 0x801343c4u, kOverlaySc02_8013435CWords },
    { 0x80134a28u, 0x80134a74u, kOverlaySc02_80134A28Words },
    { 0x80134fb8u, 0x80135004u, kOverlaySc02_80134FB8Words },
    { 0x80136c1cu, 0x80136c3cu, kOverlaySc02_80136C1CWords },
    { 0x80136c3cu, 0x80136c44u, kOverlaySc02_80136C3CWords },
    { 0x80136d08u, 0x80136dfcu, kOverlaySc02_80136D08Words },
    { 0x80136dfcu, 0x80136ec4u, kOverlaySc02_80136DFCWords },
    { 0x80136eccu, 0x80136f3cu, kOverlaySc02_80136ECCWords },
    { 0x801375ecu, 0x80137614u, kOverlaySc02_801375ECWords },
    { 0x80137614u, 0x8013767cu, kOverlaySc02_80137614Words },
    { 0x8013767cu, 0x801376c8u, kOverlaySc02_8013767CWords },
    { 0x801376c8u, 0x801376e8u, kOverlaySc02_801376C8Words },
    { 0x80137840u, 0x801378f0u, kOverlaySc02_80137840Words },
    { 0x801379d8u, 0x801379ecu, kOverlaySc02_801379D8Words },
    { 0x801379ecu, 0x801379fcu, kOverlaySc02_801379ECWords },
};

static const FormatterRange kFormatterRanges19[] = {
    { 0x80138948u, 0x8013895cu, kOverlaySc02_80138948Words },
    { 0x80138b88u, 0x80138be0u, kOverlaySc02_80138B88Words },
    { 0x80138c30u, 0x80138c60u, kOverlaySc02_80138C30Words },
    { 0x80138d58u, 0x80138db8u, kOverlaySc02_80138D58Words },
    { 0x80138db8u, 0x80138de0u, kOverlaySc02_80138DB8Words },
    { 0x801391f0u, 0x80139220u, kOverlaySc02_801391F0Words },
    { 0x80139220u, 0x801392c8u, kOverlaySc02_80139220Words },
    { 0x801392c8u, 0x801392fcu, kOverlaySc02_801392C8Words },
    { 0x801395d4u, 0x80139634u, kOverlaySc02_801395D4Words },
    { 0x80139634u, 0x80139680u, kOverlaySc02_80139634Words },
    { 0x80139788u, 0x801397b0u, kOverlaySc02_80139788Words },
    { 0x80139914u, 0x80139954u, kOverlaySc02_80139914Words },
    { 0x80139954u, 0x801399a8u, kOverlaySc02_80139954Words },
    { 0x801399a8u, 0x801399f0u, kOverlaySc02_801399A8Words },
    { 0x801399f0u, 0x80139a34u, kOverlaySc02_801399F0Words },
    { 0x80139a34u, 0x80139a44u, kOverlaySc02_80139A34Words },
    { 0x80139a44u, 0x80139a68u, kOverlaySc02_80139A44Words },
    { 0x80139a68u, 0x80139a8cu, kOverlaySc02_80139A68Words },
    { 0x80139b18u, 0x80139be0u, kOverlaySc02_80139B18Words },
    { 0x80139c7cu, 0x80139d04u, kOverlaySc02_80139C7CWords },
    { 0x80139dc8u, 0x80139decu, kOverlaySc02_80139DC8Words },
    { 0x80139f0cu, 0x80139fbcu, kOverlaySc02_80139F0CWords },
    { 0x80139fbcu, 0x80139fe8u, kOverlaySc02_80139FBCWords },
    { 0x80139fe8u, 0x8013a0a4u, kOverlaySc02_80139FE8Words },
    { 0x8013a0a4u, 0x8013a164u, kOverlaySc02_8013A0A4Words },
    { 0x8013a164u, 0x8013a1e8u, kOverlaySc02_8013A164Words },
    { 0x8013a1e8u, 0x8013a250u, kOverlaySc02_8013A1E8Words },
    { 0x8013a250u, 0x8013a2bcu, kOverlaySc02_8013A250Words },
};

static const FormatterRange kFormatterRanges20[] = {
    { 0x8012a018u, 0x8012a048u, kOverlaySc02_8012A018Words },
    { 0x8012a048u, 0x8012a094u, kOverlaySc02_8012A048Words },
    { 0x8012a094u, 0x8012a0e0u, kOverlaySc02_8012A094Words },
    { 0x8013a448u, 0x8013a4c4u, kOverlaySc02_8013A448Words },
    { 0x8013a4c4u, 0x8013a530u, kOverlaySc02_8013A4C4Words },
    { 0x8013a8b0u, 0x8013a8bcu, kOverlaySc02_8013A8B0Words },
    { 0x8013a8bcu, 0x8013a8fcu, kOverlaySc02_8013A8BCWords },
    { 0x8013a9b4u, 0x8013a9f8u, kOverlaySc02_8013A9B4Words },
    { 0x8013aa24u, 0x8013ab54u, kOverlaySc02_8013AA24Words },
    { 0x8013ab54u, 0x8013ad38u, kOverlaySc02_8013AB54Words },
    { 0x8013b204u, 0x8013b274u, kOverlaySc02_8013B204Words },
    { 0x8013e064u, 0x8013e0fcu, kOverlaySc02_8013E064Words },
    { 0x8013e0fcu, 0x8013e194u, kOverlaySc02_8013E0FCWords },
    { 0x8013e194u, 0x8013e22cu, kOverlaySc02_8013E194Words },
    { 0x8013e22cu, 0x8013e298u, kOverlaySc02_8013E22CWords },
    { 0x8013e298u, 0x8013e2c4u, kOverlaySc02_8013E298Words },
    { 0x8013e2c4u, 0x8013e370u, kOverlaySc02_8013E2C4Words },
    { 0x8013e370u, 0x8013e410u, kOverlaySc02_8013E370Words },
    { 0x8013e410u, 0x8013e448u, kOverlaySc02_8013E410Words },
    { 0x8013e558u, 0x8013e588u, kOverlaySc02_8013E558Words },
    { 0x8013e588u, 0x8013e5e8u, kOverlaySc02_8013E588Words },
    { 0x8013e67cu, 0x8013e6acu, kOverlaySc02_8013E67CWords },
    { 0x8013e814u, 0x8013e83cu, kOverlaySc02_8013E814Words },
    { 0x8014168cu, 0x801416d4u, kOverlaySc02_8014168CWords },
    { 0x801417c4u, 0x801417f8u, kOverlaySc02_801417C4Words },
    { 0x801417f8u, 0x80141874u, kOverlaySc02_801417F8Words },
    { 0x80141c04u, 0x80141c0cu, kOverlaySc02_80141C04Words },
    { 0x80141c50u, 0x80141ca4u, kOverlaySc02_80141C50Words },
    { 0x80141ca4u, 0x80142414u, kOverlaySc02_80141CA4Words },
    { 0x80142414u, 0x80142454u, kOverlaySc02_80142414Words },
    { 0x801426d4u, 0x80142740u, kOverlaySc02_801426D4Words },
    { 0x80142740u, 0x80142778u, kOverlaySc02_80142740Words },
    { 0x80142778u, 0x801427dcu, kOverlaySc02_80142778Words },
    { 0x80142838u, 0x801428ccu, kOverlaySc02_80142838Words },
    { 0x801428ccu, 0x8014292cu, kOverlaySc02_801428CCWords },
    { 0x80142b2cu, 0x80142bb4u, kOverlaySc02_80142B2CWords },
    { 0x80142bb4u, 0x80142c7cu, kOverlaySc02_80142BB4Words },
    { 0x80142c84u, 0x80142c9cu, kOverlaySc02_80142C84Words },
    { 0x80142d38u, 0x80142db8u, kOverlaySc02_80142D38Words },
    { 0x80142db8u, 0x80142dc4u, kOverlaySc02_80142DB8Words },
    { 0x80142f68u, 0x80142ffcu, kOverlaySc02_80142F68Words },
    { 0x80142ffcu, 0x8014305cu, kOverlaySc02_80142FFCWords },
    { 0x801430f4u, 0x80143188u, kOverlaySc02_801430F4Words },
    { 0x80143188u, 0x801431e8u, kOverlaySc02_80143188Words },
    { 0x801432fcu, 0x80143390u, kOverlaySc02_801432FCWords },
    { 0x80143390u, 0x801433f0u, kOverlaySc02_80143390Words },
    { 0x801433f0u, 0x80143458u, kOverlaySc02_801433F0Words },
    { 0x8014350cu, 0x8014358cu, kOverlaySc02_8014350CWords },
    { 0x80143994u, 0x801439c0u, kOverlaySc02_80143994Words },
    { 0x801439c0u, 0x801439fcu, kOverlaySc02_801439C0Words },
    { 0x80143c74u, 0x80143c98u, kOverlaySc02_80143C74Words },
    { 0x8014a680u, 0x8014a69cu, kOverlaySc02_8014A680Words },
    { 0x8014a6a8u, 0x8014a6c4u, kOverlaySc02_8014A6A8Words },
    { 0x8014a6c4u, 0x8014a71cu, kOverlaySc02_8014A6C4Words },
    { 0x8014a71cu, 0x8014a738u, kOverlaySc02_8014A71CWords },
    { 0x8014a830u, 0x8014a850u, kOverlaySc02_8014A830Words },
    { 0x80150f78u, 0x80150f80u, kOverlaySc02_80150F78Words },
    { 0x80150f80u, 0x80150fb4u, kOverlaySc02_80150F80Words },
    { 0x80150fb4u, 0x80150fd8u, kOverlaySc02_80150FB4Words },
    { 0x80150fd8u, 0x80151014u, kOverlaySc02_80150FD8Words },
    { 0x80151014u, 0x80151038u, kOverlaySc02_80151014Words },
    { 0x80151038u, 0x80151070u, kOverlaySc02_80151038Words },
    { 0x80151070u, 0x80151094u, kOverlaySc02_80151070Words },
    { 0x80151094u, 0x801510b8u, kOverlaySc02_80151094Words },
    { 0x801510c8u, 0x801510ecu, kOverlaySc02_801510C8Words },
    { 0x801510ecu, 0x80151110u, kOverlaySc02_801510ECWords },
    { 0x80151110u, 0x80151130u, kOverlaySc02_80151110Words },
    { 0x80151138u, 0x8015115cu, kOverlaySc02_80151138Words },
    { 0x80151164u, 0x80151184u, kOverlaySc02_80151164Words },
    { 0x80151184u, 0x801511a8u, kOverlaySc02_80151184Words },
    { 0x801511a8u, 0x801511c4u, kOverlaySc02_801511A8Words },
    { 0x801511c4u, 0x801511e0u, kOverlaySc02_801511C4Words },
    { 0x801511e0u, 0x80151204u, kOverlaySc02_801511E0Words },
    { 0x80151204u, 0x80151238u, kOverlaySc02_80151204Words },
    { 0x80151238u, 0x8015126cu, kOverlaySc02_80151238Words },
    { 0x80151664u, 0x801516f0u, kOverlaySc02_80151664Words },
    { 0x801516f0u, 0x8015173cu, kOverlaySc02_801516F0Words },
    { 0x8015173cu, 0x80151780u, kOverlaySc02_8015173CWords },
    { 0x80151878u, 0x80151880u, kOverlaySc02_80151878Words },
    { 0x80151924u, 0x80151944u, kOverlaySc02_80151924Words },
    { 0x80151980u, 0x801519c8u, kOverlaySc02_80151980Words },
    { 0x80151ae4u, 0x80151b98u, kOverlaySc02_80151AE4Words },
    { 0x80151d60u, 0x80151db0u, kOverlaySc02_80151D60Words },
    { 0x80151db0u, 0x80151e78u, kOverlaySc02_80151DB0Words },
    { 0x80151e78u, 0x80151eccu, kOverlaySc02_80151E78Words },
    { 0x80151eccu, 0x80151f38u, kOverlaySc02_80151ECCWords },
    { 0x80151f38u, 0x80151fb4u, kOverlaySc02_80151F38Words },
    { 0x80151fb4u, 0x80152058u, kOverlaySc02_80151FB4Words },
    { 0x80152094u, 0x801520dcu, kOverlaySc02_80152094Words },
    { 0x80152194u, 0x8015220cu, kOverlaySc02_80152194Words },
    { 0x8015220cu, 0x80152254u, kOverlaySc02_8015220CWords },
    { 0x801522ccu, 0x80152370u, kOverlaySc02_801522CCWords },
    { 0x801523acu, 0x801523f4u, kOverlaySc02_801523ACWords },
    { 0x801525f4u, 0x80152698u, kOverlaySc02_801525F4Words },
    { 0x801526d4u, 0x80152714u, kOverlaySc02_801526D4Words },
    { 0x80152790u, 0x8015282cu, kOverlaySc02_80152790Words },
    { 0x80152868u, 0x801528b0u, kOverlaySc02_80152868Words },
    { 0x8015294cu, 0x80152a08u, kOverlaySc02_8015294CWords },
    { 0x80152a08u, 0x80152a50u, kOverlaySc02_80152A08Words },
    { 0x80152ac8u, 0x80152b6cu, kOverlaySc02_80152AC8Words },
    { 0x80152ba8u, 0x80152bf0u, kOverlaySc02_80152BA8Words },
    { 0x80152bf0u, 0x80152c40u, kOverlaySc02_80152BF0Words },
    { 0x80152c40u, 0x80152c80u, kOverlaySc02_80152C40Words },
    { 0x80152c80u, 0x80152d24u, kOverlaySc02_80152C80Words },
    { 0x80152d60u, 0x80152da8u, kOverlaySc02_80152D60Words },
    { 0x80152e4cu, 0x80152efcu, kOverlaySc02_80152E4CWords },
    { 0x80152efcu, 0x80152f44u, kOverlaySc02_80152EFCWords },
    { 0x80152fbcu, 0x80153060u, kOverlaySc02_80152FBCWords },
    { 0x8015309cu, 0x801530e4u, kOverlaySc02_8015309CWords },
    { 0x801530e4u, 0x80153150u, kOverlaySc02_801530E4Words },
    { 0x80153150u, 0x801531bcu, kOverlaySc02_80153150Words },
    { 0x801531bcu, 0x80153204u, kOverlaySc02_801531BCWords },
    { 0x8015327cu, 0x80153320u, kOverlaySc02_8015327CWords },
    { 0x8015335cu, 0x801533a4u, kOverlaySc02_8015335CWords },
    { 0x801533a4u, 0x80153410u, kOverlaySc02_801533A4Words },
    { 0x80153410u, 0x80153490u, kOverlaySc02_80153410Words },
    { 0x80153490u, 0x801534d8u, kOverlaySc02_80153490Words },
    { 0x80153550u, 0x801535f4u, kOverlaySc02_80153550Words },
    { 0x8015369cu, 0x801536dcu, kOverlaySc02_8015369CWords },
    { 0x80153bd8u, 0x80153bf0u, kOverlaySc02_80153BD8Words },
    { 0x80153bf0u, 0x80153c18u, kOverlaySc02_80153BF0Words },
    { 0x80153c18u, 0x80153c30u, kOverlaySc02_80153C18Words },
    { 0x80153c30u, 0x80153c44u, kOverlaySc02_80153C30Words },
    { 0x80153c44u, 0x80153c74u, kOverlaySc02_80153C44Words },
    { 0x80153c74u, 0x80153c8cu, kOverlaySc02_80153C74Words },
    { 0x80153c9cu, 0x80153cbcu, kOverlaySc02_80153C9CWords },
    { 0x80153cbcu, 0x80153cccu, kOverlaySc02_80153CBCWords },
    { 0x80153d34u, 0x80153d7cu, kOverlaySc02_80153D34Words },
    { 0x8015410cu, 0x80154134u, kOverlaySc02_8015410CWords },
    { 0x80154134u, 0x80154150u, kOverlaySc02_80154134Words },
    { 0x80154150u, 0x80154190u, kOverlaySc02_80154150Words },
    { 0x80154190u, 0x801541d8u, kOverlaySc02_80154190Words },
    { 0x801541d8u, 0x80154218u, kOverlaySc02_801541D8Words },
    { 0x80154218u, 0x80154274u, kOverlaySc02_80154218Words },
    { 0x80154274u, 0x801542a4u, kOverlaySc02_80154274Words },
    { 0x801542a4u, 0x801542dcu, kOverlaySc02_801542A4Words },
    { 0x801542dcu, 0x8015430cu, kOverlaySc02_801542DCWords },
    { 0x8015430cu, 0x80154358u, kOverlaySc02_8015430CWords },
    { 0x80154418u, 0x8015444cu, kOverlaySc02_80154418Words },
    { 0x80155344u, 0x80155394u, kOverlaySc02_80155344Words },
    { 0x80155394u, 0x801553a8u, kOverlaySc02_80155394Words },
    { 0x801553a8u, 0x801553c0u, kOverlaySc02_801553A8Words },
    { 0x80155440u, 0x80155458u, kOverlaySc02_80155440Words },
    { 0x801554b8u, 0x80155518u, kOverlaySc02_801554B8Words },
    { 0x80155518u, 0x8015554cu, kOverlaySc02_80155518Words },
    { 0x8015554cu, 0x80155580u, kOverlaySc02_8015554CWords },
    { 0x801555bcu, 0x801555f4u, kOverlaySc02_801555BCWords },
    { 0x80155b20u, 0x80155b9cu, kOverlaySc02_80155B20Words },
    { 0x80155b9cu, 0x80155c0cu, kOverlaySc02_80155B9CWords },
    { 0x80155f60u, 0x80155f80u, kOverlaySc02_80155F60Words },
    { 0x80155f80u, 0x80155fb0u, kOverlaySc02_80155F80Words },
    { 0x80155fb0u, 0x80155fd4u, kOverlaySc02_80155FB0Words },
    { 0x80155fd4u, 0x80155ff8u, kOverlaySc02_80155FD4Words },
    { 0x801565c0u, 0x80156600u, kOverlaySc02_801565C0Words },
    { 0x80156648u, 0x80156670u, kOverlaySc02_80156648Words },
    { 0x801567bcu, 0x80156848u, kOverlaySc02_801567BCWords },
    { 0x80156a14u, 0x80156a1cu, kOverlaySc02_80156A14Words },
    { 0x80157158u, 0x801571c4u, kOverlaySc02_80157158Words },
    { 0x801574dcu, 0x80157510u, kOverlaySc02_801574DCWords },
    { 0x80157510u, 0x80157544u, kOverlaySc02_80157510Words },
    { 0x80157580u, 0x801575e4u, kOverlaySc02_80157580Words },
    { 0x8015771cu, 0x8015773cu, kOverlaySc02_8015771CWords },
    { 0x8015773cu, 0x80157788u, kOverlaySc02_8015773CWords },
    { 0x80157880u, 0x801578c0u, kOverlaySc02_80157880Words },
    { 0x80157a8cu, 0x80157ac8u, kOverlaySc02_80157A8CWords },
    { 0x80157ac8u, 0x80157b74u, kOverlaySc02_80157AC8Words },
    { 0x80157b74u, 0x80157bc8u, kOverlaySc02_80157B74Words },
    { 0x80157cccu, 0x80157d20u, kOverlaySc02_80157CCCWords },
    { 0x80157d74u, 0x80157dc4u, kOverlaySc02_80157D74Words },
    { 0x80157e00u, 0x80157e38u, kOverlaySc02_80157E00Words },
    { 0x80157e38u, 0x80157ea4u, kOverlaySc02_80157E38Words },
    { 0x80157ea4u, 0x80157f64u, kOverlaySc02_80157EA4Words },
    { 0x80157f64u, 0x80157fc4u, kOverlaySc02_80157F64Words },
    { 0x80158000u, 0x80158038u, kOverlaySc02_80158000Words },
    { 0x80158288u, 0x801582c0u, kOverlaySc02_80158288Words },
    { 0x801582c0u, 0x80158344u, kOverlaySc02_801582C0Words },
    { 0x80158548u, 0x801585a4u, kOverlaySc02_80158548Words },
    { 0x801585acu, 0x801585ecu, kOverlaySc02_801585ACWords },
    { 0x801585ecu, 0x80158638u, kOverlaySc02_801585ECWords },
    { 0x80158ab4u, 0x80158ae4u, kOverlaySc02_80158AB4Words },
    { 0x80158ae4u, 0x80158bb0u, kOverlaySc02_80158AE4Words },
    { 0x801592ccu, 0x8015934cu, kOverlaySc02_801592CCWords },
    { 0x801593e4u, 0x80159404u, kOverlaySc02_801593E4Words },
    { 0x801596d4u, 0x801596f0u, kOverlaySc02_801596D4Words },
    { 0x80159874u, 0x8015987cu, kOverlaySc02_80159874Words },
    { 0x8015987cu, 0x801598bcu, kOverlaySc02_8015987CWords },
    { 0x801598bcu, 0x801598e0u, kOverlaySc02_801598BCWords },
    { 0x801599e0u, 0x80159a18u, kOverlaySc02_801599E0Words },
    { 0x80159b08u, 0x80159b3cu, kOverlaySc02_80159B08Words },
    { 0x80159b3cu, 0x80159b70u, kOverlaySc02_80159B3CWords },
    { 0x80159bacu, 0x80159be4u, kOverlaySc02_80159BACWords },
    { 0x8015a1fcu, 0x8015a230u, kOverlaySc02_8015A1FCWords },
    { 0x8015a230u, 0x8015a264u, kOverlaySc02_8015A230Words },
    { 0x8015a2a0u, 0x8015a2d8u, kOverlaySc02_8015A2A0Words },
    { 0x8015abd4u, 0x8015ac48u, kOverlaySc02_8015ABD4Words },
    { 0x8015ac90u, 0x8015acc4u, kOverlaySc02_8015AC90Words },
    { 0x8015acc4u, 0x8015ad08u, kOverlaySc02_8015ACC4Words },
    { 0x8015ad08u, 0x8015ad3cu, kOverlaySc02_8015AD08Words },
    { 0x8015ad78u, 0x8015adb0u, kOverlaySc02_8015AD78Words },
    { 0x8015adb0u, 0x8015ae2cu, kOverlaySc02_8015ADB0Words },
    { 0x8015b858u, 0x8015b8f8u, kOverlaySc02_8015B858Words },
    { 0x8015b8f8u, 0x8015b950u, kOverlaySc02_8015B8F8Words },
    { 0x8015bd8cu, 0x8015bdd0u, kOverlaySc02_8015BD8CWords },
    { 0x8015bdd0u, 0x8015be04u, kOverlaySc02_8015BDD0Words },
    { 0x8015be04u, 0x8015be38u, kOverlaySc02_8015BE04Words },
    { 0x8015be74u, 0x8015be94u, kOverlaySc02_8015BE74Words },
    { 0x8015be94u, 0x8015bec4u, kOverlaySc02_8015BE94Words },
    { 0x8015bec4u, 0x8015bee4u, kOverlaySc02_8015BEC4Words },
    { 0x8015bee4u, 0x8015bf04u, kOverlaySc02_8015BEE4Words },
    { 0x8015bf04u, 0x8015bf48u, kOverlaySc02_8015BF04Words },
    { 0x8015bf48u, 0x8015bf7cu, kOverlaySc02_8015BF48Words },
    { 0x8015bf7cu, 0x8015bfb0u, kOverlaySc02_8015BF7CWords },
    { 0x8015bfb0u, 0x8015bff4u, kOverlaySc02_8015BFB0Words },
    { 0x8015c08cu, 0x8015c0c4u, kOverlaySc02_8015C08CWords },
    { 0x8015c6acu, 0x8015c6e0u, kOverlaySc02_8015C6ACWords },
    { 0x8015c6e0u, 0x8015c714u, kOverlaySc02_8015C6E0Words },
    { 0x8015c750u, 0x8015c788u, kOverlaySc02_8015C750Words },
    { 0x8015c788u, 0x8015c7e4u, kOverlaySc02_8015C788Words },
    { 0x8015cb94u, 0x8015cbccu, kOverlaySc02_8015CB94Words },
    { 0x8015cc0cu, 0x8015cc40u, kOverlaySc02_8015CC0CWords },
    { 0x8015cc40u, 0x8015cc74u, kOverlaySc02_8015CC40Words },
    { 0x8015ccb0u, 0x8015ccd0u, kOverlaySc02_8015CCB0Words },
    { 0x8015ccd0u, 0x8015cd20u, kOverlaySc02_8015CCD0Words },
    { 0x8015cf24u, 0x8015cf58u, kOverlaySc02_8015CF24Words },
    { 0x8015cf58u, 0x8015cf8cu, kOverlaySc02_8015CF58Words },
    { 0x8015cf8cu, 0x8015cfc0u, kOverlaySc02_8015CF8CWords },
    { 0x8015cffcu, 0x8015d01cu, kOverlaySc02_8015CFFCWords },
    { 0x8015d480u, 0x8015d4b4u, kOverlaySc02_8015D480Words },
    { 0x8015d4b4u, 0x8015d4e8u, kOverlaySc02_8015D4B4Words },
    { 0x8015d524u, 0x8015d544u, kOverlaySc02_8015D524Words },
    { 0x8015d544u, 0x8015d57cu, kOverlaySc02_8015D544Words },
    { 0x8015d57cu, 0x8015d5e8u, kOverlaySc02_8015D57CWords },
    { 0x8015da5cu, 0x8015da90u, kOverlaySc02_8015DA5CWords },
    { 0x8015da90u, 0x8015dac4u, kOverlaySc02_8015DA90Words },
    { 0x8015dac4u, 0x8015daf8u, kOverlaySc02_8015DAC4Words },
    { 0x8015db34u, 0x8015db6cu, kOverlaySc02_8015DB34Words },
    { 0x8015db6cu, 0x8015dbd4u, kOverlaySc02_8015DB6CWords },
    { 0x8015dc84u, 0x8015dcb8u, kOverlaySc02_8015DC84Words },
    { 0x8015dd74u, 0x8015ddf0u, kOverlaySc02_8015DD74Words },
    { 0x8015ddf0u, 0x8015de24u, kOverlaySc02_8015DDF0Words },
    { 0x8015de24u, 0x8015de58u, kOverlaySc02_8015DE24Words },
    { 0x8015de94u, 0x8015deccu, kOverlaySc02_8015DE94Words },
    { 0x8015deccu, 0x8015df34u, kOverlaySc02_8015DECCWords },
    { 0x8015dfe4u, 0x8015e018u, kOverlaySc02_8015DFE4Words },
    { 0x8015e0d4u, 0x8015e150u, kOverlaySc02_8015E0D4Words },
    { 0x8015e150u, 0x8015e184u, kOverlaySc02_8015E150Words },
    { 0x8015e184u, 0x8015e1b8u, kOverlaySc02_8015E184Words },
    { 0x8015e1f4u, 0x8015e22cu, kOverlaySc02_8015E1F4Words },
    { 0x8015e22cu, 0x8015e288u, kOverlaySc02_8015E22CWords },
    { 0x8015e288u, 0x8015e344u, kOverlaySc02_8015E288Words },
    { 0x8015e40cu, 0x8015e4b0u, kOverlaySc02_8015E40CWords },
    { 0x8015e5b0u, 0x8015e698u, kOverlaySc02_8015E5B0Words },
    { 0x8015e714u, 0x8015e84cu, kOverlaySc02_8015E714Words },
    { 0x8015e84cu, 0x8015e880u, kOverlaySc02_8015E84CWords },
    { 0x8015e880u, 0x8015e8b4u, kOverlaySc02_8015E880Words },
    { 0x8015e8b4u, 0x8015e8e8u, kOverlaySc02_8015E8B4Words },
    { 0x8015e924u, 0x8015e95cu, kOverlaySc02_8015E924Words },
    { 0x8015e95cu, 0x8015e9b8u, kOverlaySc02_8015E95CWords },
    { 0x8015e9b8u, 0x8015ea3cu, kOverlaySc02_8015E9B8Words },
    { 0x8015eda0u, 0x8015edd4u, kOverlaySc02_8015EDA0Words },
    { 0x8015edd4u, 0x8015ee08u, kOverlaySc02_8015EDD4Words },
    { 0x8015ee44u, 0x8015ee7cu, kOverlaySc02_8015EE44Words },
    { 0x8015efa4u, 0x8015efd8u, kOverlaySc02_8015EFA4Words },
    { 0x8015efd8u, 0x8015f00cu, kOverlaySc02_8015EFD8Words },
    { 0x8015f048u, 0x8015f080u, kOverlaySc02_8015F048Words },
    { 0x8015f080u, 0x8015f118u, kOverlaySc02_8015F080Words },
    { 0x8015f260u, 0x8015f2bcu, kOverlaySc02_8015F260Words },
    { 0x8015f2bcu, 0x8015f2f0u, kOverlaySc02_8015F2BCWords },
    { 0x8015f2f0u, 0x8015f324u, kOverlaySc02_8015F2F0Words },
    { 0x8015f360u, 0x8015f380u, kOverlaySc02_8015F360Words },
    { 0x8015f380u, 0x8015f448u, kOverlaySc02_8015F380Words },
    { 0x8015f738u, 0x8015f76cu, kOverlaySc02_8015F738Words },
    { 0x8015f76cu, 0x8015f7a0u, kOverlaySc02_8015F76CWords },
    { 0x8015f7a0u, 0x8015f7d4u, kOverlaySc02_8015F7A0Words },
    { 0x8015f810u, 0x8015f848u, kOverlaySc02_8015F810Words },
    { 0x8015f848u, 0x8015f89cu, kOverlaySc02_8015F848Words },
    { 0x8015f948u, 0x8015f9a4u, kOverlaySc02_8015F948Words },
    { 0x8015fa24u, 0x8015fa44u, kOverlaySc02_8015FA24Words },
    { 0x8015fa44u, 0x8015fa78u, kOverlaySc02_8015FA44Words },
    { 0x8015fa78u, 0x8015faacu, kOverlaySc02_8015FA78Words },
    { 0x801600d0u, 0x80160104u, kOverlaySc02_801600D0Words },
    { 0x80160104u, 0x80160138u, kOverlaySc02_80160104Words },
    { 0x80160174u, 0x801601acu, kOverlaySc02_80160174Words },
    { 0x801601acu, 0x801601e4u, kOverlaySc02_801601ACWords },
    { 0x801601e4u, 0x80160244u, kOverlaySc02_801601E4Words },
    { 0x80160244u, 0x801602a4u, kOverlaySc02_80160244Words },
    { 0x80160334u, 0x80160368u, kOverlaySc02_80160334Words },
    { 0x80160368u, 0x8016039cu, kOverlaySc02_80160368Words },
    { 0x801603d8u, 0x80160410u, kOverlaySc02_801603D8Words },
    { 0x801607b8u, 0x801607e4u, kOverlaySc02_801607B8Words },
    { 0x801607e4u, 0x80160818u, kOverlaySc02_801607E4Words },
    { 0x80160818u, 0x8016084cu, kOverlaySc02_80160818Words },
    { 0x80160888u, 0x801608c0u, kOverlaySc02_80160888Words },
    { 0x801608c0u, 0x80160920u, kOverlaySc02_801608C0Words },
    { 0x80160a28u, 0x80160a74u, kOverlaySc02_80160A28Words },
    { 0x80160a74u, 0x80160accu, kOverlaySc02_80160A74Words },
    { 0x80160accu, 0x80160b00u, kOverlaySc02_80160ACCWords },
    { 0x80160b00u, 0x80160b34u, kOverlaySc02_80160B00Words },
    { 0x80160b70u, 0x80160bb4u, kOverlaySc02_80160B70Words },
    { 0x80160bb4u, 0x80160c28u, kOverlaySc02_80160BB4Words },
    { 0x80160cb4u, 0x80160d10u, kOverlaySc02_80160CB4Words },
    { 0x80160decu, 0x80160e3cu, kOverlaySc02_80160DECWords },
    { 0x80160e3cu, 0x80160e70u, kOverlaySc02_80160E3CWords },
    { 0x80160e70u, 0x80160ea4u, kOverlaySc02_80160E70Words },
    { 0x80160ee0u, 0x80160f00u, kOverlaySc02_80160EE0Words },
    { 0x80160f00u, 0x80160f70u, kOverlaySc02_80160F00Words },
    { 0x80160f70u, 0x80160fe0u, kOverlaySc02_80160F70Words },
    { 0x80160fe0u, 0x80161034u, kOverlaySc02_80160FE0Words },
    { 0x80161094u, 0x801610fcu, kOverlaySc02_80161094Words },
    { 0x80161104u, 0x80161124u, kOverlaySc02_80161104Words },
    { 0x80161124u, 0x80161208u, kOverlaySc02_80161124Words },
    { 0x80161208u, 0x80161240u, kOverlaySc02_80161208Words },
    { 0x80161240u, 0x80161278u, kOverlaySc02_80161240Words },
    { 0x80161278u, 0x801612b8u, kOverlaySc02_80161278Words },
    { 0x8016130cu, 0x80161374u, kOverlaySc02_8016130CWords },
    { 0x80161418u, 0x80161450u, kOverlaySc02_80161418Words },
    { 0x80161450u, 0x80161488u, kOverlaySc02_80161450Words },
    { 0x80161488u, 0x801614e4u, kOverlaySc02_80161488Words },
    { 0x801614e4u, 0x8016151cu, kOverlaySc02_801614E4Words },
    { 0x8016151cu, 0x80161554u, kOverlaySc02_8016151CWords },
    { 0x80161554u, 0x8016158cu, kOverlaySc02_80161554Words },
    { 0x8016158cu, 0x801615c4u, kOverlaySc02_8016158CWords },
    { 0x801615c4u, 0x8016163cu, kOverlaySc02_801615C4Words },
    { 0x80161888u, 0x8016191cu, kOverlaySc02_80161888Words },
    { 0x8016191cu, 0x8016197cu, kOverlaySc02_8016191CWords },
    { 0x801619d0u, 0x80161a00u, kOverlaySc02_801619D0Words },
    { 0x80161a00u, 0x80161a30u, kOverlaySc02_80161A00Words },
    { 0x80161a30u, 0x80161a60u, kOverlaySc02_80161A30Words },
    { 0x80161a60u, 0x80161a90u, kOverlaySc02_80161A60Words },
    { 0x80161b84u, 0x80161be0u, kOverlaySc02_80161B84Words },
    { 0x80161be0u, 0x80161c24u, kOverlaySc02_80161BE0Words },
    { 0x80161d58u, 0x80161d88u, kOverlaySc02_80161D58Words },
    { 0x80162120u, 0x8016216cu, kOverlaySc02_80162120Words },
    { 0x8016236cu, 0x801623b8u, kOverlaySc02_8016236CWords },
    { 0x801623b8u, 0x80162414u, kOverlaySc02_801623B8Words },
    { 0x80162414u, 0x80162438u, kOverlaySc02_80162414Words },
    { 0x80162714u, 0x80162760u, kOverlaySc02_80162714Words },
    { 0x80162accu, 0x80162ae0u, kOverlaySc02_80162ACCWords },
    { 0x80162ae0u, 0x80162af4u, kOverlaySc02_80162AE0Words },
    { 0x80162cc4u, 0x80162cccu, kOverlaySc02_80162CC4Words },
    { 0x80162cccu, 0x80162d28u, kOverlaySc02_80162CCCWords },
    { 0x80162d28u, 0x80162d88u, kOverlaySc02_80162D28Words },
    { 0x80162d88u, 0x80162de8u, kOverlaySc02_80162D88Words },
    { 0x80162de8u, 0x80162e48u, kOverlaySc02_80162DE8Words },
    { 0x80162e48u, 0x80162ea8u, kOverlaySc02_80162E48Words },
    { 0x80162ea8u, 0x80162f08u, kOverlaySc02_80162EA8Words },
    { 0x80162f08u, 0x80162f60u, kOverlaySc02_80162F08Words },
    { 0x80162f60u, 0x80162f80u, kOverlaySc02_80162F60Words },
    { 0x80162f80u, 0x80162fa0u, kOverlaySc02_80162F80Words },
    { 0x80162fa0u, 0x80162fc0u, kOverlaySc02_80162FA0Words },
    { 0x80162fc0u, 0x80162ff4u, kOverlaySc02_80162FC0Words },
    { 0x80163234u, 0x8016325cu, kOverlaySc02_80163234Words },
    { 0x801632e0u, 0x801632f0u, kOverlaySc02_801632E0Words },
    { 0x801632f0u, 0x80163328u, kOverlaySc02_801632F0Words },
    { 0x801633a8u, 0x80163408u, kOverlaySc02_801633A8Words },
    { 0x8016345cu, 0x801634d8u, kOverlaySc02_8016345CWords },
    { 0x80163664u, 0x801636d0u, kOverlaySc02_80163664Words },
    { 0x801636d0u, 0x80163764u, kOverlaySc02_801636D0Words },
    { 0x80164270u, 0x801642acu, kOverlaySc02_80164270Words },
    { 0x801642acu, 0x8016432cu, kOverlaySc02_801642ACWords },
    { 0x80164a74u, 0x80164accu, kOverlaySc02_80164A74Words },
    { 0x80164cd4u, 0x80164d4cu, kOverlaySc02_80164CD4Words },
    { 0x80164d4cu, 0x80164db0u, kOverlaySc02_80164D4CWords },
    { 0x80164db0u, 0x80164dd0u, kOverlaySc02_80164DB0Words },
    { 0x80164dd0u, 0x80164e40u, kOverlaySc02_80164DD0Words },
    { 0x80165024u, 0x80165064u, kOverlaySc02_80165024Words },
    { 0x80165064u, 0x801650c4u, kOverlaySc02_80165064Words },
    { 0x801650c4u, 0x80165124u, kOverlaySc02_801650C4Words },
    { 0x80165124u, 0x80165140u, kOverlaySc02_80165124Words },
    { 0x80165374u, 0x801653b8u, kOverlaySc02_80165374Words },
    { 0x801653b8u, 0x801653f4u, kOverlaySc02_801653B8Words },
    { 0x801655e4u, 0x80165624u, kOverlaySc02_801655E4Words },
    { 0x80165624u, 0x80165658u, kOverlaySc02_80165624Words },
    { 0x80165694u, 0x801656d0u, kOverlaySc02_80165694Words },
    { 0x80165770u, 0x801657a0u, kOverlaySc02_80165770Words },
    { 0x801657a0u, 0x801657d8u, kOverlaySc02_801657A0Words },
    { 0x801657d8u, 0x80165840u, kOverlaySc02_801657D8Words },
    { 0x80165840u, 0x80165874u, kOverlaySc02_80165840Words },
    { 0x80165874u, 0x801658dcu, kOverlaySc02_80165874Words },
    { 0x801658dcu, 0x801658ecu, kOverlaySc02_801658DCWords },
    { 0x801658ecu, 0x80165900u, kOverlaySc02_801658ECWords },
    { 0x80165900u, 0x80165910u, kOverlaySc02_80165900Words },
    { 0x80165958u, 0x80165978u, kOverlaySc02_80165958Words },
    { 0x80165978u, 0x80165988u, kOverlaySc02_80165978Words },
    { 0x80165988u, 0x801659a8u, kOverlaySc02_80165988Words },
    { 0x801659a8u, 0x801659b8u, kOverlaySc02_801659A8Words },
    { 0x801659b8u, 0x801659ccu, kOverlaySc02_801659B8Words },
    { 0x801659ccu, 0x801659dcu, kOverlaySc02_801659CCWords },
    { 0x80165a20u, 0x80165a50u, kOverlaySc02_80165A20Words },
    { 0x80165a50u, 0x80165a78u, kOverlaySc02_80165A50Words },
    { 0x80165a78u, 0x80165ac8u, kOverlaySc02_80165A78Words },
    { 0x80165b6cu, 0x80165bb4u, kOverlaySc02_80165B6CWords },
    { 0x80165bb4u, 0x80165bfcu, kOverlaySc02_80165BB4Words },
    { 0x80165bfcu, 0x80165c58u, kOverlaySc02_80165BFCWords },
    { 0x80165c58u, 0x80165c78u, kOverlaySc02_80165C58Words },
    { 0x80165fa4u, 0x80166018u, kOverlaySc02_80165FA4Words },
    { 0x801661ccu, 0x80166244u, kOverlaySc02_801661CCWords },
    { 0x80166244u, 0x8016629cu, kOverlaySc02_80166244Words },
    { 0x8016629cu, 0x801662f4u, kOverlaySc02_8016629CWords },
    { 0x801662f4u, 0x8016634cu, kOverlaySc02_801662F4Words },
    { 0x8016634cu, 0x801663a4u, kOverlaySc02_8016634CWords },
    { 0x801663a4u, 0x801663fcu, kOverlaySc02_801663A4Words },
    { 0x801665b4u, 0x80166618u, kOverlaySc02_801665B4Words },
    { 0x8016706cu, 0x801670e4u, kOverlaySc02_8016706CWords },
    { 0x8016829cu, 0x80168328u, kOverlaySc02_8016829CWords },
    { 0x80168328u, 0x801683d8u, kOverlaySc02_80168328Words },
    { 0x801683d8u, 0x80168430u, kOverlaySc02_801683D8Words },
    { 0x801684b4u, 0x80168540u, kOverlaySc02_801684B4Words },
    { 0x80168540u, 0x801685ecu, kOverlaySc02_80168540Words },
    { 0x801685ecu, 0x80168640u, kOverlaySc02_801685ECWords },
    { 0x80168640u, 0x80168664u, kOverlaySc02_80168640Words },
    { 0x80168664u, 0x80168744u, kOverlaySc02_80168664Words },
    { 0x80168780u, 0x801687ccu, kOverlaySc02_80168780Words },
    { 0x801687ccu, 0x80168828u, kOverlaySc02_801687CCWords },
    { 0x80168a14u, 0x80168a88u, kOverlaySc02_80168A14Words },
    { 0x80168a88u, 0x80168aa8u, kOverlaySc02_80168A88Words },
    { 0x80168ae4u, 0x80168b70u, kOverlaySc02_80168AE4Words },
    { 0x80168b70u, 0x80168bdcu, kOverlaySc02_80168B70Words },
    { 0x80168ec4u, 0x80168f40u, kOverlaySc02_80168EC4Words },
    { 0x801691b8u, 0x80169228u, kOverlaySc02_801691B8Words },
    { 0x8016951cu, 0x80169584u, kOverlaySc02_8016951CWords },
    { 0x801699d0u, 0x80169a4cu, kOverlaySc02_801699D0Words },
    { 0x80169e44u, 0x80169f00u, kOverlaySc02_80169E44Words },
    { 0x80169fe0u, 0x8016a020u, kOverlaySc02_80169FE0Words },
    { 0x8016a05cu, 0x8016a08cu, kOverlaySc02_8016A05CWords },
    { 0x8016a890u, 0x8016a8fcu, kOverlaySc02_8016A890Words },
    { 0x8016b3f4u, 0x8016b428u, kOverlaySc02_8016B3F4Words },
    { 0x8016b428u, 0x8016b448u, kOverlaySc02_8016B428Words },
    { 0x8016b448u, 0x8016b4bcu, kOverlaySc02_8016B448Words },
    { 0x8016b91cu, 0x8016b964u, kOverlaySc02_8016B91CWords },
    { 0x8016b964u, 0x8016b984u, kOverlaySc02_8016B964Words },
    { 0x8016b984u, 0x8016b9f8u, kOverlaySc02_8016B984Words },
    { 0x8016ba48u, 0x8016ba68u, kOverlaySc02_8016BA48Words },
    { 0x8016ba68u, 0x8016badcu, kOverlaySc02_8016BA68Words },
    { 0x8016badcu, 0x8016bba4u, kOverlaySc02_8016BADCWords },
    { 0x8016bf34u, 0x8016bf50u, kOverlaySc02_8016BF34Words },
    { 0x8016bf50u, 0x8016bfa8u, kOverlaySc02_8016BF50Words },
    { 0x8016d464u, 0x8016d4dcu, kOverlaySc02_8016D464Words },
    { 0x8016d5ecu, 0x8016d64cu, kOverlaySc02_8016D5ECWords },
    { 0x8016d64cu, 0x8016d688u, kOverlaySc02_8016D64CWords },
    { 0x8016d984u, 0x8016da04u, kOverlaySc02_8016D984Words },
    { 0x8016da04u, 0x8016da30u, kOverlaySc02_8016DA04Words },
    { 0x8016db34u, 0x8016dbd8u, kOverlaySc02_8016DB34Words },
    { 0x8016dbd8u, 0x8016dc20u, kOverlaySc02_8016DBD8Words },
    { 0x8016dee0u, 0x8016df20u, kOverlaySc02_8016DEE0Words },
    { 0x8016e1ccu, 0x8016e26cu, kOverlaySc02_8016E1CCWords },
    { 0x8016e26cu, 0x8016e2e8u, kOverlaySc02_8016E26CWords },
    { 0x8016e2e8u, 0x8016e358u, kOverlaySc02_8016E2E8Words },
    { 0x8016e358u, 0x8016e3ccu, kOverlaySc02_8016E358Words },
    { 0x8016e3ccu, 0x8016e460u, kOverlaySc02_8016E3CCWords },
    { 0x8016e5f4u, 0x8016e688u, kOverlaySc02_8016E5F4Words },
    { 0x8016e688u, 0x8016e6e4u, kOverlaySc02_8016E688Words },
    { 0x8016e6e4u, 0x8016e728u, kOverlaySc02_8016E6E4Words },
    { 0x8016e728u, 0x8016e778u, kOverlaySc02_8016E728Words },
    { 0x8016e778u, 0x8016e7c8u, kOverlaySc02_8016E778Words },
    { 0x8016ed6cu, 0x8016ed8cu, kOverlaySc02_8016ED6CWords },
    { 0x8016ed8cu, 0x8016edbcu, kOverlaySc02_8016ED8CWords },
    { 0x8016edbcu, 0x8016edecu, kOverlaySc02_8016EDBCWords },
    { 0x8016edecu, 0x8016ee40u, kOverlaySc02_8016EDECWords },
    { 0x8016ee40u, 0x8016ee94u, kOverlaySc02_8016EE40Words },
    { 0x8016ef78u, 0x8016efa8u, kOverlaySc02_8016EF78Words },
    { 0x8016efa8u, 0x8016efc8u, kOverlaySc02_8016EFA8Words },
    { 0x8016efc8u, 0x8016f094u, kOverlaySc02_8016EFC8Words },
    { 0x8016f094u, 0x8016f0acu, kOverlaySc02_8016F094Words },
    { 0x8016f0acu, 0x8016f0e4u, kOverlaySc02_8016F0ACWords },
    { 0x8016f1acu, 0x8016f1c4u, kOverlaySc02_8016F1ACWords },
    { 0x8016f250u, 0x8016f264u, kOverlaySc02_8016F250Words },
    { 0x8016f264u, 0x8016f288u, kOverlaySc02_8016F264Words },
    { 0x8016f288u, 0x8016f2a8u, kOverlaySc02_8016F288Words },
    { 0x8016f2a8u, 0x8016f2c8u, kOverlaySc02_8016F2A8Words },
    { 0x8016f2c8u, 0x8016f2ecu, kOverlaySc02_8016F2C8Words },
    { 0x8016f2ecu, 0x8016f30cu, kOverlaySc02_8016F2ECWords },
    { 0x8016f30cu, 0x8016f330u, kOverlaySc02_8016F30CWords },
    { 0x8016f330u, 0x8016f350u, kOverlaySc02_8016F330Words },
    { 0x8016f350u, 0x8016f374u, kOverlaySc02_8016F350Words },
    { 0x8016f374u, 0x8016f388u, kOverlaySc02_8016F374Words },
    { 0x8016f388u, 0x8016f398u, kOverlaySc02_8016F388Words },
    { 0x8016f398u, 0x8016f410u, kOverlaySc02_8016F398Words },
    { 0x8016f410u, 0x8016f44cu, kOverlaySc02_8016F410Words },
    { 0x8016f44cu, 0x8016f470u, kOverlaySc02_8016F44CWords },
    { 0x8016f470u, 0x8016f494u, kOverlaySc02_8016F470Words },
    { 0x8016f494u, 0x8016f4c4u, kOverlaySc02_8016F494Words },
    { 0x8016f4c4u, 0x8016f4f4u, kOverlaySc02_8016F4C4Words },
    { 0x8016f4fcu, 0x8016f540u, kOverlaySc02_8016F4FCWords },
    { 0x8016f540u, 0x8016f578u, kOverlaySc02_8016F540Words },
    { 0x8016f578u, 0x8016f5b0u, kOverlaySc02_8016F578Words },
    { 0x8016f5b0u, 0x8016f5e0u, kOverlaySc02_8016F5B0Words },
    { 0x8016f5e0u, 0x8016f610u, kOverlaySc02_8016F5E0Words },
    { 0x8016f610u, 0x8016f648u, kOverlaySc02_8016F610Words },
    { 0x8016f648u, 0x8016f680u, kOverlaySc02_8016F648Words },
    { 0x8016f680u, 0x8016f6b0u, kOverlaySc02_8016F680Words },
    { 0x8016f6b0u, 0x8016f6e0u, kOverlaySc02_8016F6B0Words },
    { 0x8016f71cu, 0x8016f764u, kOverlaySc02_8016F71CWords },
    { 0x8016f764u, 0x8016f798u, kOverlaySc02_8016F764Words },
    { 0x8016f7d4u, 0x8016f804u, kOverlaySc02_8016F7D4Words },
    { 0x8016f804u, 0x8016f834u, kOverlaySc02_8016F804Words },
    { 0x8016f870u, 0x8016f8acu, kOverlaySc02_8016F870Words },
    { 0x8016f8acu, 0x8016f8e4u, kOverlaySc02_8016F8ACWords },
    { 0x8016f920u, 0x8016f95cu, kOverlaySc02_8016F920Words },
    { 0x8016fa00u, 0x8016fa44u, kOverlaySc02_8016FA00Words },
    { 0x8016fa44u, 0x8016fa84u, kOverlaySc02_8016FA44Words },
    { 0x8016fac0u, 0x8016fb10u, kOverlaySc02_8016FAC0Words },
    { 0x8016fb10u, 0x8016fb50u, kOverlaySc02_8016FB10Words },
    { 0x8016fb50u, 0x8016fb7cu, kOverlaySc02_8016FB50Words },
    { 0x8016fbb8u, 0x8016fc24u, kOverlaySc02_8016FBB8Words },
    { 0x8016fc24u, 0x8016fc64u, kOverlaySc02_8016FC24Words },
    { 0x8016fc64u, 0x8016fc90u, kOverlaySc02_8016FC64Words },
    { 0x8016fcccu, 0x8016fd08u, kOverlaySc02_8016FCCCWords },
    { 0x8016fd7cu, 0x8016fdb4u, kOverlaySc02_8016FD7CWords },
    { 0x8016fdf0u, 0x8016fe2cu, kOverlaySc02_8016FDF0Words },
    { 0x8016fe2cu, 0x8016fe78u, kOverlaySc02_8016FE2CWords },
    { 0x8016fed0u, 0x8016ff30u, kOverlaySc02_8016FED0Words },
    { 0x8016ff6cu, 0x8016ffa8u, kOverlaySc02_8016FF6CWords },
    { 0x8016ffa8u, 0x8016ffdcu, kOverlaySc02_8016FFA8Words },
    { 0x80170018u, 0x80170068u, kOverlaySc02_80170018Words },
    { 0x80170068u, 0x801700b8u, kOverlaySc02_80170068Words },
    { 0x801700b8u, 0x80170100u, kOverlaySc02_801700B8Words },
    { 0x80170100u, 0x80170150u, kOverlaySc02_80170100Words },
    { 0x8017018cu, 0x801701c8u, kOverlaySc02_8017018CWords },
    { 0x801701c8u, 0x80170240u, kOverlaySc02_801701C8Words },
    { 0x8017027cu, 0x801702b8u, kOverlaySc02_8017027CWords },
    { 0x801702b8u, 0x801702fcu, kOverlaySc02_801702B8Words },
    { 0x80170338u, 0x80170374u, kOverlaySc02_80170338Words },
    { 0x80170374u, 0x801703e0u, kOverlaySc02_80170374Words },
    { 0x8017041cu, 0x8017044cu, kOverlaySc02_8017041CWords },
    { 0x8017044cu, 0x801704b0u, kOverlaySc02_8017044CWords },
    { 0x801704ecu, 0x8017051cu, kOverlaySc02_801704ECWords },
    { 0x8017051cu, 0x80170548u, kOverlaySc02_8017051CWords },
    { 0x80170584u, 0x801705c0u, kOverlaySc02_80170584Words },
    { 0x801705c0u, 0x801705f8u, kOverlaySc02_801705C0Words },
    { 0x80170634u, 0x80170670u, kOverlaySc02_80170634Words },
    { 0x80170670u, 0x801706acu, kOverlaySc02_80170670Words },
    { 0x801706e8u, 0x80170718u, kOverlaySc02_801706E8Words },
    { 0x80170718u, 0x80170748u, kOverlaySc02_80170718Words },
    { 0x80170784u, 0x801707d4u, kOverlaySc02_80170784Words },
    { 0x801707d4u, 0x80170810u, kOverlaySc02_801707D4Words },
    { 0x8017084cu, 0x801708b0u, kOverlaySc02_8017084CWords },
    { 0x801708b0u, 0x80170928u, kOverlaySc02_801708B0Words },
    { 0x80170928u, 0x80170970u, kOverlaySc02_80170928Words },
    { 0x80170970u, 0x801709b8u, kOverlaySc02_80170970Words },
    { 0x801709b8u, 0x80170a00u, kOverlaySc02_801709B8Words },
    { 0x80170a00u, 0x80170a48u, kOverlaySc02_80170A00Words },
    { 0x80170a48u, 0x80170a90u, kOverlaySc02_80170A48Words },
    { 0x80170a90u, 0x80170ad8u, kOverlaySc02_80170A90Words },
    { 0x80170b14u, 0x80170b48u, kOverlaySc02_80170B14Words },
    { 0x80170b48u, 0x80170b90u, kOverlaySc02_80170B48Words },
    { 0x80170b90u, 0x80170bd8u, kOverlaySc02_80170B90Words },
    { 0x80170c14u, 0x80170c44u, kOverlaySc02_80170C14Words },
    { 0x80170c44u, 0x80170c74u, kOverlaySc02_80170C44Words },
    { 0x80170cb0u, 0x80170cf0u, kOverlaySc02_80170CB0Words },
    { 0x80170da4u, 0x80170de0u, kOverlaySc02_80170DA4Words },
    { 0x80170de0u, 0x80170e34u, kOverlaySc02_80170DE0Words },
    { 0x80170e70u, 0x80170eacu, kOverlaySc02_80170E70Words },
    { 0x80170eacu, 0x80170efcu, kOverlaySc02_80170EACWords },
    { 0x80170f38u, 0x80170f74u, kOverlaySc02_80170F38Words },
    { 0x80170f74u, 0x80170fb0u, kOverlaySc02_80170F74Words },
    { 0x80170fecu, 0x80171028u, kOverlaySc02_80170FECWords },
    { 0x80171028u, 0x80171064u, kOverlaySc02_80171028Words },
    { 0x801710a0u, 0x801710dcu, kOverlaySc02_801710A0Words },
    { 0x801710dcu, 0x80171120u, kOverlaySc02_801710DCWords },
    { 0x8017115cu, 0x8017118cu, kOverlaySc02_8017115CWords },
    { 0x8017118cu, 0x801711c0u, kOverlaySc02_8017118CWords },
    { 0x801711fcu, 0x80171238u, kOverlaySc02_801711FCWords },
    { 0x80171238u, 0x80171260u, kOverlaySc02_80171238Words },
    { 0x8017162cu, 0x801716acu, kOverlaySc02_8017162CWords },
    { 0x801717f4u, 0x80171824u, kOverlaySc02_801717F4Words },
    { 0x80171824u, 0x80171854u, kOverlaySc02_80171824Words },
    { 0x80171854u, 0x80171884u, kOverlaySc02_80171854Words },
    { 0x80171884u, 0x801718acu, kOverlaySc02_80171884Words },
    { 0x801718acu, 0x80171904u, kOverlaySc02_801718ACWords },
    { 0x80171904u, 0x80171928u, kOverlaySc02_80171904Words },
    { 0x80171928u, 0x8017196cu, kOverlaySc02_80171928Words },
    { 0x8017196cu, 0x8017197cu, kOverlaySc02_8017196CWords },
    { 0x8017197cu, 0x80171990u, kOverlaySc02_8017197CWords },
    { 0x80171990u, 0x801719a4u, kOverlaySc02_80171990Words },
    { 0x80171a04u, 0x80171a10u, kOverlaySc02_80171A04Words },
    { 0x80171a10u, 0x80171a1cu, kOverlaySc02_80171A10Words },
    { 0x80171a1cu, 0x80171a34u, kOverlaySc02_80171A1CWords },
    { 0x80171a34u, 0x80171a44u, kOverlaySc02_80171A34Words },
    { 0x80171a44u, 0x80171a58u, kOverlaySc02_80171A44Words },
    { 0x80171a58u, 0x80171a6cu, kOverlaySc02_80171A58Words },
    { 0x80171a6cu, 0x80171a80u, kOverlaySc02_80171A6CWords },
    { 0x80171b10u, 0x80171b44u, kOverlaySc02_80171B10Words },
    { 0x80171b44u, 0x80171b4cu, kOverlaySc02_80171B44Words },
    { 0x80171c64u, 0x80171cc4u, kOverlaySc02_80171C64Words },
    { 0x80171cc4u, 0x80171d1cu, kOverlaySc02_80171CC4Words },
    { 0x80171d1cu, 0x80171d78u, kOverlaySc02_80171D1CWords },
    { 0x801722ccu, 0x80172304u, kOverlaySc02_801722CCWords },
    { 0x80172310u, 0x80172358u, kOverlaySc02_80172310Words },
    { 0x80172358u, 0x801723c4u, kOverlaySc02_80172358Words },
    { 0x801723c4u, 0x80172414u, kOverlaySc02_801723C4Words },
    { 0x80172414u, 0x8017248cu, kOverlaySc02_80172414Words },
    { 0x8017248cu, 0x801724ecu, kOverlaySc02_8017248CWords },
    { 0x801724ecu, 0x8017250cu, kOverlaySc02_801724ECWords },
    { 0x8017250cu, 0x80172560u, kOverlaySc02_8017250CWords },
    { 0x80172560u, 0x80172588u, kOverlaySc02_80172560Words },
    { 0x80172588u, 0x80172590u, kOverlaySc02_80172588Words },
    { 0x80172590u, 0x801725a4u, kOverlaySc02_80172590Words },
    { 0x801725a4u, 0x801725b8u, kOverlaySc02_801725A4Words },
    { 0x801725b8u, 0x801725ccu, kOverlaySc02_801725B8Words },
    { 0x801725ccu, 0x801725e0u, kOverlaySc02_801725CCWords },
    { 0x801725e0u, 0x801725f4u, kOverlaySc02_801725E0Words },
    { 0x801725f4u, 0x80172608u, kOverlaySc02_801725F4Words },
    { 0x80172608u, 0x8017261cu, kOverlaySc02_80172608Words },
    { 0x8017261cu, 0x80172630u, kOverlaySc02_8017261CWords },
    { 0x80172630u, 0x80172644u, kOverlaySc02_80172630Words },
    { 0x80172644u, 0x80172658u, kOverlaySc02_80172644Words },
    { 0x80172658u, 0x80172664u, kOverlaySc02_80172658Words },
    { 0x80172664u, 0x80172670u, kOverlaySc02_80172664Words },
    { 0x80172670u, 0x8017267cu, kOverlaySc02_80172670Words },
    { 0x8017267cu, 0x80172688u, kOverlaySc02_8017267CWords },
    { 0x80172688u, 0x80172694u, kOverlaySc02_80172688Words },
    { 0x80172694u, 0x801726a0u, kOverlaySc02_80172694Words },
    { 0x801726a0u, 0x801726acu, kOverlaySc02_801726A0Words },
    { 0x801726acu, 0x801726b8u, kOverlaySc02_801726ACWords },
    { 0x801726b8u, 0x801726c4u, kOverlaySc02_801726B8Words },
    { 0x801726c4u, 0x801726d0u, kOverlaySc02_801726C4Words },
    { 0x801726d0u, 0x80172710u, kOverlaySc02_801726D0Words },
    { 0x80172710u, 0x80172738u, kOverlaySc02_80172710Words },
    { 0x80172738u, 0x80172760u, kOverlaySc02_80172738Words },
    { 0x80172760u, 0x80172780u, kOverlaySc02_80172760Words },
    { 0x80172780u, 0x801727d0u, kOverlaySc02_80172780Words },
    { 0x8017280cu, 0x80172844u, kOverlaySc02_8017280CWords },
    { 0x80172844u, 0x8017288cu, kOverlaySc02_80172844Words },
    { 0x80172894u, 0x801728e4u, kOverlaySc02_80172894Words },
    { 0x80172920u, 0x80172958u, kOverlaySc02_80172920Words },
    { 0x80172958u, 0x801729a8u, kOverlaySc02_80172958Words },
    { 0x801729b0u, 0x801729f0u, kOverlaySc02_801729B0Words },
    { 0x80172a2cu, 0x80172a8cu, kOverlaySc02_80172A2CWords },
    { 0x80172a8cu, 0x80172accu, kOverlaySc02_80172A8CWords },
    { 0x80172accu, 0x80172b0cu, kOverlaySc02_80172ACCWords },
    { 0x80172b14u, 0x80172b44u, kOverlaySc02_80172B14Words },
    { 0x80172b80u, 0x80172bc8u, kOverlaySc02_80172B80Words },
    { 0x80172bc8u, 0x80172c48u, kOverlaySc02_80172BC8Words },
    { 0x80172c50u, 0x80172ca0u, kOverlaySc02_80172C50Words },
    { 0x80172cdcu, 0x80172d14u, kOverlaySc02_80172CDCWords },
    { 0x80172d14u, 0x80172d60u, kOverlaySc02_80172D14Words },
    { 0x80172d68u, 0x80172dacu, kOverlaySc02_80172D68Words },
    { 0x80172de8u, 0x80172e20u, kOverlaySc02_80172DE8Words },
    { 0x80172e20u, 0x80172e8cu, kOverlaySc02_80172E20Words },
    { 0x80172e94u, 0x80172ed4u, kOverlaySc02_80172E94Words },
    { 0x80172ed4u, 0x80172efcu, kOverlaySc02_80172ED4Words },
    { 0x80172efcu, 0x80172f24u, kOverlaySc02_80172EFCWords },
    { 0x80172f24u, 0x80172f4cu, kOverlaySc02_80172F24Words },
    { 0x80172f4cu, 0x80172f9cu, kOverlaySc02_80172F4CWords },
    { 0x80172f9cu, 0x80172fecu, kOverlaySc02_80172F9CWords },
    { 0x80172fecu, 0x8017303cu, kOverlaySc02_80172FECWords },
    { 0x8017303cu, 0x80173078u, kOverlaySc02_8017303CWords },
    { 0x801730b4u, 0x801730fcu, kOverlaySc02_801730B4Words },
    { 0x801730fcu, 0x8017316cu, kOverlaySc02_801730FCWords },
    { 0x80173174u, 0x8017319cu, kOverlaySc02_80173174Words },
    { 0x801731d8u, 0x80173220u, kOverlaySc02_801731D8Words },
    { 0x8017329cu, 0x801732c4u, kOverlaySc02_8017329CWords },
    { 0x801732c4u, 0x801732f4u, kOverlaySc02_801732C4Words },
    { 0x801732f4u, 0x8017331cu, kOverlaySc02_801732F4Words },
    { 0x8017331cu, 0x8017334cu, kOverlaySc02_8017331CWords },
    { 0x8017334cu, 0x80173374u, kOverlaySc02_8017334CWords },
    { 0x80173374u, 0x801733a4u, kOverlaySc02_80173374Words },
    { 0x801733a4u, 0x801733ccu, kOverlaySc02_801733A4Words },
    { 0x801733ccu, 0x801733fcu, kOverlaySc02_801733CCWords },
    { 0x801733fcu, 0x80173460u, kOverlaySc02_801733FCWords },
    { 0x80173460u, 0x801734bcu, kOverlaySc02_80173460Words },
    { 0x80173580u, 0x801735b8u, kOverlaySc02_80173580Words },
    { 0x801735b8u, 0x801735ecu, kOverlaySc02_801735B8Words },
    { 0x801735ecu, 0x80173648u, kOverlaySc02_801735ECWords },
    { 0x801736b0u, 0x801736fcu, kOverlaySc02_801736B0Words },
    { 0x80173738u, 0x80173770u, kOverlaySc02_80173738Words },
    { 0x80173770u, 0x801737b0u, kOverlaySc02_80173770Words },
    { 0x801737b8u, 0x801737e8u, kOverlaySc02_801737B8Words },
    { 0x80173824u, 0x8017385cu, kOverlaySc02_80173824Words },
    { 0x801738dcu, 0x8017390cu, kOverlaySc02_801738DCWords },
    { 0x80173948u, 0x80173980u, kOverlaySc02_80173948Words },
    { 0x80173980u, 0x801739d8u, kOverlaySc02_80173980Words },
    { 0x801739d8u, 0x80173a20u, kOverlaySc02_801739D8Words },
    { 0x80173a28u, 0x80173a60u, kOverlaySc02_80173A28Words },
    { 0x80173b88u, 0x80173bc0u, kOverlaySc02_80173B88Words },
    { 0x80173bc0u, 0x80173c64u, kOverlaySc02_80173BC0Words },
    { 0x80173c64u, 0x80173cb4u, kOverlaySc02_80173C64Words },
    { 0x80174158u, 0x80174188u, kOverlaySc02_80174158Words },
    { 0x80174188u, 0x801741a8u, kOverlaySc02_80174188Words },
    { 0x801741a8u, 0x801741ecu, kOverlaySc02_801741A8Words },
    { 0x801741ecu, 0x80174274u, kOverlaySc02_801741ECWords },
    { 0x8017427cu, 0x801742a4u, kOverlaySc02_8017427CWords },
    { 0x801742e0u, 0x80174318u, kOverlaySc02_801742E0Words },
    { 0x80174318u, 0x80174354u, kOverlaySc02_80174318Words },
    { 0x8017435cu, 0x80174384u, kOverlaySc02_8017435CWords },
    { 0x801743c0u, 0x801743f0u, kOverlaySc02_801743C0Words },
    { 0x801743f0u, 0x80174430u, kOverlaySc02_801743F0Words },
    { 0x80174438u, 0x80174474u, kOverlaySc02_80174438Words },
    { 0x801744b0u, 0x801744e0u, kOverlaySc02_801744B0Words },
    { 0x801744e0u, 0x80174524u, kOverlaySc02_801744E0Words },
    { 0x8017452cu, 0x80174554u, kOverlaySc02_8017452CWords },
    { 0x80174554u, 0x80174584u, kOverlaySc02_80174554Words },
    { 0x80174584u, 0x801745acu, kOverlaySc02_80174584Words },
    { 0x801745acu, 0x801745dcu, kOverlaySc02_801745ACWords },
    { 0x801745dcu, 0x80174604u, kOverlaySc02_801745DCWords },
    { 0x80174604u, 0x80174630u, kOverlaySc02_80174604Words },
    { 0x80174630u, 0x80174650u, kOverlaySc02_80174630Words },
    { 0x80174650u, 0x80174674u, kOverlaySc02_80174650Words },
    { 0x80174674u, 0x80174684u, kOverlaySc02_80174674Words },
    { 0x80174684u, 0x801746a4u, kOverlaySc02_80174684Words },
    { 0x801746a4u, 0x801746dcu, kOverlaySc02_801746A4Words },
    { 0x801746dcu, 0x80174714u, kOverlaySc02_801746DCWords },
    { 0x80174714u, 0x80174754u, kOverlaySc02_80174714Words },
    { 0x80174754u, 0x80174764u, kOverlaySc02_80174754Words },
    { 0x80174764u, 0x80174774u, kOverlaySc02_80174764Words },
    { 0x80174774u, 0x80174784u, kOverlaySc02_80174774Words },
    { 0x80174784u, 0x801747acu, kOverlaySc02_80174784Words },
    { 0x801747acu, 0x801747ccu, kOverlaySc02_801747ACWords },
    { 0x80174808u, 0x8017481cu, kOverlaySc02_80174808Words },
    { 0x8017481cu, 0x80174824u, kOverlaySc02_8017481CWords },
    { 0x80174824u, 0x8017484cu, kOverlaySc02_80174824Words },
    { 0x8017484cu, 0x80174888u, kOverlaySc02_8017484CWords },
    { 0x801748c4u, 0x801748e4u, kOverlaySc02_801748C4Words },
    { 0x801748e4u, 0x801748ecu, kOverlaySc02_801748E4Words },
    { 0x801748ecu, 0x8017496cu, kOverlaySc02_801748ECWords },
    { 0x801749a8u, 0x801749c8u, kOverlaySc02_801749A8Words },
    { 0x80174b6cu, 0x80174bbcu, kOverlaySc02_80174B6CWords },
    { 0x80174bbcu, 0x80174bf4u, kOverlaySc02_80174BBCWords },
    { 0x80174c60u, 0x80174c80u, kOverlaySc02_80174C60Words },
    { 0x80174c80u, 0x80174cb0u, kOverlaySc02_80174C80Words },
    { 0x80174e9cu, 0x80174ed4u, kOverlaySc02_80174E9CWords },
    { 0x80174ed4u, 0x80174ef0u, kOverlaySc02_80174ED4Words },
    { 0x80174ef0u, 0x80174f28u, kOverlaySc02_80174EF0Words },
    { 0x80174f64u, 0x80174fbcu, kOverlaySc02_80174F64Words },
    { 0x80174fbcu, 0x80175014u, kOverlaySc02_80174FBCWords },
    { 0x80175014u, 0x8017509cu, kOverlaySc02_80175014Words },
    { 0x8017509cu, 0x80175114u, kOverlaySc02_8017509CWords },
    { 0x80175114u, 0x80175150u, kOverlaySc02_80175114Words },
    { 0x80175150u, 0x80175184u, kOverlaySc02_80175150Words },
    { 0x801751d8u, 0x80175218u, kOverlaySc02_801751D8Words },
    { 0x801752bcu, 0x80175308u, kOverlaySc02_801752BCWords },
    { 0x80175414u, 0x80175454u, kOverlaySc02_80175414Words },
    { 0x80175454u, 0x80175494u, kOverlaySc02_80175454Words },
    { 0x80175624u, 0x80175668u, kOverlaySc02_80175624Words },
    { 0x80175668u, 0x80175690u, kOverlaySc02_80175668Words },
    { 0x801757e0u, 0x80175820u, kOverlaySc02_801757E0Words },
    { 0x801787d4u, 0x80178840u, kOverlaySc02_801787D4Words },
    { 0x80178bb8u, 0x80178bf8u, kOverlaySc02_80178BB8Words },
    { 0x80179b28u, 0x80179b74u, kOverlaySc02_80179B28Words },
    { 0x80179d30u, 0x80179d78u, kOverlaySc02_80179D30Words },
    { 0x80179d78u, 0x80179dccu, kOverlaySc02_80179D78Words },
    { 0x80179dccu, 0x80179df8u, kOverlaySc02_80179DCCWords },
    { 0x80179df8u, 0x80179e1cu, kOverlaySc02_80179DF8Words },
    { 0x80179e1cu, 0x80179e48u, kOverlaySc02_80179E1CWords },
    { 0x80179e48u, 0x80179e74u, kOverlaySc02_80179E48Words },
    { 0x80179e74u, 0x80179ea0u, kOverlaySc02_80179E74Words },
    { 0x80179ea0u, 0x80179ee8u, kOverlaySc02_80179EA0Words },
    { 0x80179ee8u, 0x80179f14u, kOverlaySc02_80179EE8Words },
    { 0x80179f14u, 0x80179f44u, kOverlaySc02_80179F14Words },
    { 0x80179f44u, 0x80179f6cu, kOverlaySc02_80179F44Words },
    { 0x80179f6cu, 0x80179f98u, kOverlaySc02_80179F6CWords },
    { 0x80179f98u, 0x80179fecu, kOverlaySc02_80179F98Words },
    { 0x80179fecu, 0x8017a040u, kOverlaySc02_80179FECWords },
    { 0x8017a040u, 0x8017a094u, kOverlaySc02_8017A040Words },
    { 0x8017a0f4u, 0x8017a11cu, kOverlaySc02_8017A0F4Words },
    { 0x8017a11cu, 0x8017a144u, kOverlaySc02_8017A11CWords },
    { 0x8017a180u, 0x8017a1a8u, kOverlaySc02_8017A180Words },
    { 0x8017a1a8u, 0x8017a1d0u, kOverlaySc02_8017A1A8Words },
    { 0x8017a1d0u, 0x8017a1f8u, kOverlaySc02_8017A1D0Words },
    { 0x8017a1f8u, 0x8017a220u, kOverlaySc02_8017A1F8Words },
    { 0x8017a220u, 0x8017a248u, kOverlaySc02_8017A220Words },
    { 0x8017a248u, 0x8017a270u, kOverlaySc02_8017A248Words },
    { 0x8017a270u, 0x8017a298u, kOverlaySc02_8017A270Words },
    { 0x8017a298u, 0x8017a2c0u, kOverlaySc02_8017A298Words },
    { 0x8017a2c0u, 0x8017a2e8u, kOverlaySc02_8017A2C0Words },
    { 0x8017a2e8u, 0x8017a310u, kOverlaySc02_8017A2E8Words },
    { 0x8017a310u, 0x8017a338u, kOverlaySc02_8017A310Words },
    { 0x8017a338u, 0x8017a360u, kOverlaySc02_8017A338Words },
    { 0x8017a360u, 0x8017a388u, kOverlaySc02_8017A360Words },
    { 0x8017a388u, 0x8017a3b0u, kOverlaySc02_8017A388Words },
    { 0x8017ade8u, 0x8017ae08u, kOverlaySc02_8017ADE8Words },
    { 0x8017ae08u, 0x8017ae2cu, kOverlaySc02_8017AE08Words },
    { 0x8018129cu, 0x8018133cu, kOverlaySc02_8018129CWords },
    { 0x8018133cu, 0x80181378u, kOverlaySc02_8018133CWords },
    { 0x80181378u, 0x801814e4u, kOverlaySc02_80181378Words },
    { 0x801814e4u, 0x801816c0u, kOverlaySc02_801814E4Words },
};

static const FormatterRange kFormatterRanges21[] = {
    { 0x8012a828u, 0x8012a860u, kOverlaySc02_8012A828Words },
    { 0x8012aaacu, 0x8012aca0u, kOverlaySc02_8012AAACWords },
    { 0x8012aca0u, 0x8012ace0u, kOverlaySc02_8012ACA0Words },
    { 0x8012ad44u, 0x8012ad50u, kOverlaySc02_8012AD44Words },
    { 0x8012ad50u, 0x8012ad64u, kOverlaySc02_8012AD50Words },
    { 0x8012b14cu, 0x8012b178u, kOverlaySc02_8012B14CWords },
    { 0x8012b2ccu, 0x8012b370u, kOverlaySc02_8012B2CCWords },
    { 0x8012c218u, 0x8012c284u, kOverlaySc02_8012C218Words },
    { 0x8012c658u, 0x8012c750u, kOverlaySc02_8012C658Words },
    { 0x8012cae4u, 0x8012cb64u, kOverlaySc02_8012CAE4Words },
    { 0x8012e8e0u, 0x8012e9c0u, kOverlaySc02_8012E8E0Words },
    { 0x80143970u, 0x801439fcu, kOverlaySc02_80143970Words },
    { 0x801439fcu, 0x80143b6cu, kOverlaySc02_801439FCWords },
    { 0x80143b6cu, 0x80143cd4u, kOverlaySc02_80143B6CWords },
    { 0x80143cd4u, 0x80143d28u, kOverlaySc02_80143CD4Words },
    { 0x80143d28u, 0x80143eb4u, kOverlaySc02_80143D28Words },
    { 0x80143eb4u, 0x80143ebcu, kOverlaySc02_80143EB4Words },
    { 0x80143ebcu, 0x80144054u, kOverlaySc02_80143EBCWords },
    { 0x80144054u, 0x80144090u, kOverlaySc02_80144054Words },
    { 0x80144090u, 0x801442f8u, kOverlaySc02_80144090Words },
    { 0x801442f8u, 0x80144364u, kOverlaySc02_801442F8Words },
    { 0x80144364u, 0x80144458u, kOverlaySc02_80144364Words },
    { 0x80144458u, 0x80144558u, kOverlaySc02_80144458Words },
    { 0x80144558u, 0x8014462cu, kOverlaySc02_80144558Words },
    { 0x8014462cu, 0x801446a4u, kOverlaySc02_8014462CWords },
    { 0x801446a4u, 0x8014477cu, kOverlaySc02_801446A4Words },
    { 0x8014477cu, 0x80144880u, kOverlaySc02_8014477CWords },
    { 0x80144880u, 0x80144988u, kOverlaySc02_80144880Words },
    { 0x80144988u, 0x801449c8u, kOverlaySc02_80144988Words },
    { 0x801449c8u, 0x80144a04u, kOverlaySc02_801449C8Words },
    { 0x80144a04u, 0x80144a2cu, kOverlaySc02_80144A04Words },
    { 0x80144a2cu, 0x80144a68u, kOverlaySc02_80144A2CWords },
    { 0x80144a68u, 0x80144a90u, kOverlaySc02_80144A68Words },
    { 0x80144a90u, 0x80144a98u, kOverlaySc02_80144A90Words },
    { 0x80144a98u, 0x80144aecu, kOverlaySc02_80144A98Words },
    { 0x80144aecu, 0x80144b14u, kOverlaySc02_80144AECWords },
    { 0x80144b14u, 0x80144b9cu, kOverlaySc02_80144B14Words },
    { 0x801458e0u, 0x801458e8u, kOverlaySc02_801458E0Words },
    { 0x801458e8u, 0x80145934u, kOverlaySc02_801458E8Words },
    { 0x80145934u, 0x80145a2cu, kOverlaySc02_80145934Words },
    { 0x80145a2cu, 0x80145b24u, kOverlaySc02_80145A2CWords },
    { 0x80145b24u, 0x80145bf8u, kOverlaySc02_80145B24Words },
    { 0x80145bf8u, 0x80145c54u, kOverlaySc02_80145BF8Words },
    { 0x80145c54u, 0x80145cecu, kOverlaySc02_80145C54Words },
    { 0x801788b8u, 0x80178970u, kOverlaySc02_801788B8Words },
    { 0x8017c2b0u, 0x8017c63cu, kOverlaySc02_8017C2B0Words },
    { 0x8017c63cu, 0x8017c8b4u, kOverlaySc02_8017C63CWords },
    { 0x8017c8b4u, 0x8017c9fcu, kOverlaySc02_8017C8B4Words },
    { 0x8017c9fcu, 0x8017cb7cu, kOverlaySc02_8017C9FCWords },
    { 0x80181a24u, 0x80181a44u, kOverlaySc02_80181A24Words },
    { 0x80181b78u, 0x80181bb4u, kOverlaySc02_80181B78Words },
    { 0x80181bb4u, 0x80181c2cu, kOverlaySc02_80181BB4Words },
    { 0x80181ef0u, 0x80181f20u, kOverlaySc02_80181EF0Words },
    { 0x80182070u, 0x80182078u, kOverlaySc02_80182070Words },
    { 0x80182078u, 0x801820e0u, kOverlaySc02_80182078Words },
    { 0x801820e0u, 0x80182174u, kOverlaySc02_801820E0Words },
    { 0x80182174u, 0x801821f4u, kOverlaySc02_80182174Words },
    { 0x801821f4u, 0x80182328u, kOverlaySc02_801821F4Words },
    { 0x80182328u, 0x801824e4u, kOverlaySc02_80182328Words },
    { 0x801824e4u, 0x801825e0u, kOverlaySc02_801824E4Words },
    { 0x801825e0u, 0x80182618u, kOverlaySc02_801825E0Words },
    { 0x80182618u, 0x80182674u, kOverlaySc02_80182618Words },
    { 0x80182674u, 0x80182848u, kOverlaySc02_80182674Words },
    { 0x80182848u, 0x80182994u, kOverlaySc02_80182848Words },
    { 0x80182994u, 0x801829a0u, kOverlaySc02_80182994Words },
    { 0x801829a0u, 0x801829a8u, kOverlaySc02_801829A0Words },
    { 0x801829a8u, 0x801829bcu, kOverlaySc02_801829A8Words },
    { 0x801829bcu, 0x801829f8u, kOverlaySc02_801829BCWords },
    { 0x801829f8u, 0x80182a7cu, kOverlaySc02_801829F8Words },
    { 0x80182a7cu, 0x80182ab4u, kOverlaySc02_80182A7CWords },
    { 0x80182ab4u, 0x80182b64u, kOverlaySc02_80182AB4Words },
    { 0x80182b64u, 0x80182ba0u, kOverlaySc02_80182B64Words },
    { 0x80182ba0u, 0x80182be0u, kOverlaySc02_80182BA0Words },
    { 0x80182be0u, 0x80182c24u, kOverlaySc02_80182BE0Words },
    { 0x80182c24u, 0x80182c60u, kOverlaySc02_80182C24Words },
    { 0x80182c60u, 0x80182cf4u, kOverlaySc02_80182C60Words },
    { 0x80182cf4u, 0x801832d0u, kOverlaySc02_80182CF4Words },
    { 0x801848a8u, 0x801848e4u, kOverlaySc02_801848A8Words },
    { 0x801848e4u, 0x8018496cu, kOverlaySc02_801848E4Words },
    { 0x8018496cu, 0x80184a2cu, kOverlaySc02_8018496CWords },
    { 0x80184a2cu, 0x80184a9cu, kOverlaySc02_80184A2CWords },
    { 0x80184a9cu, 0x80184b94u, kOverlaySc02_80184A9CWords },
    { 0x80184b94u, 0x80184c24u, kOverlaySc02_80184B94Words },
};

static const FormatterRange kFormatterRanges22[] = {
    { 0x8012c194u, 0x8012c1b8u, kOverlaySc02_8012C194Words },
    { 0x8012c1b8u, 0x8012c1dcu, kOverlaySc02_8012C1B8Words },
    { 0x8012c1dcu, 0x8012c218u, kOverlaySc02_8012C1DCWords },
    { 0x80131fdcu, 0x80132018u, kOverlaySc02_80131FDCWords },
    { 0x8013221cu, 0x80132288u, kOverlaySc02_8013221CWords },
    { 0x801819e8u, 0x80181a24u, kOverlaySc02_801819E8Words },
    { 0x80181f20u, 0x80181f5cu, kOverlaySc02_80181F20Words },
    { 0x80181f5cu, 0x80181fa4u, kOverlaySc02_80181F5CWords },
    { 0x80181fa4u, 0x80182070u, kOverlaySc02_80181FA4Words },
};

static const FormatterRange kFormatterRanges23[] = {
    { 0x801320d0u, 0x801320d8u, kOverlaySc02_801320D0Words },
    { 0x80134510u, 0x801345f8u, kOverlaySc02_80134510Words },
    { 0x801345f8u, 0x801347a0u, kOverlaySc02_801345F8Words },
    { 0x801347a0u, 0x80134a28u, kOverlaySc02_801347A0Words },
    { 0x80135480u, 0x80135888u, kOverlaySc02_80135480Words },
    { 0x80135d20u, 0x80135eb0u, kOverlaySc02_80135D20Words },
    { 0x80135eb0u, 0x80136334u, kOverlaySc02_80135EB0Words },
    { 0x80136a94u, 0x80136bc4u, kOverlaySc02_80136A94Words },
    { 0x8013e448u, 0x8013e4b4u, kOverlaySc02_8013E448Words },
    { 0x80142ec0u, 0x80142f68u, kOverlaySc02_80142EC0Words },
    { 0x8014305cu, 0x801430f4u, kOverlaySc02_8014305CWords },
    { 0x80165e90u, 0x80165fa4u, kOverlaySc02_80165E90Words },
    { 0x8016ee94u, 0x8016ef78u, kOverlaySc02_8016EE94Words },
};

static const FormatterRange kFormatterRanges24[] = {
    { 0x8012853cu, 0x80128564u, kOverlaySc02_8012853CWords },
    { 0x80128564u, 0x801285d4u, kOverlaySc02_80128564Words },
    { 0x801285d4u, 0x801285e4u, kOverlaySc02_801285D4Words },
    { 0x801285e4u, 0x80128714u, kOverlaySc02_801285E4Words },
    { 0x80128714u, 0x801287b8u, kOverlaySc02_80128714Words },
    { 0x801287b8u, 0x801288e8u, kOverlaySc02_801287B8Words },
    { 0x801288e8u, 0x80128a28u, kOverlaySc02_801288E8Words },
    { 0x80128a28u, 0x80128af4u, kOverlaySc02_80128A28Words },
    { 0x80128af4u, 0x80128c14u, kOverlaySc02_80128AF4Words },
    { 0x80146074u, 0x8014607cu, kOverlaySc02_80146074Words },
    { 0x8014607cu, 0x80146128u, kOverlaySc02_8014607CWords },
    { 0x80146128u, 0x80146360u, kOverlaySc02_80146128Words },
    { 0x80146360u, 0x801463a0u, kOverlaySc02_80146360Words },
    { 0x801463a0u, 0x80146534u, kOverlaySc02_801463A0Words },
    { 0x80146534u, 0x80146554u, kOverlaySc02_80146534Words },
    { 0x80146554u, 0x80146578u, kOverlaySc02_80146554Words },
    { 0x80146578u, 0x8014659cu, kOverlaySc02_80146578Words },
    { 0x8014659cu, 0x801465c0u, kOverlaySc02_8014659CWords },
    { 0x801465c0u, 0x801465e4u, kOverlaySc02_801465C0Words },
    { 0x801465e4u, 0x80146608u, kOverlaySc02_801465E4Words },
    { 0x80146608u, 0x801466b4u, kOverlaySc02_80146608Words },
    { 0x801466b4u, 0x801466f0u, kOverlaySc02_801466B4Words },
    { 0x801466f0u, 0x80146750u, kOverlaySc02_801466F0Words },
    { 0x80146750u, 0x8014680cu, kOverlaySc02_80146750Words },
    { 0x8014680cu, 0x801468c8u, kOverlaySc02_8014680CWords },
    { 0x80146924u, 0x80146994u, kOverlaySc02_80146924Words },
    { 0x80146994u, 0x801469c8u, kOverlaySc02_80146994Words },
    { 0x801469c8u, 0x80146a6cu, kOverlaySc02_801469C8Words },
    { 0x80146a6cu, 0x80146ab4u, kOverlaySc02_80146A6CWords },
    { 0x80146ab4u, 0x80146afcu, kOverlaySc02_80146AB4Words },
    { 0x80146afcu, 0x80146b9cu, kOverlaySc02_80146AFCWords },
    { 0x80146b9cu, 0x80146c3cu, kOverlaySc02_80146B9CWords },
    { 0x80146c3cu, 0x80146c98u, kOverlaySc02_80146C3CWords },
    { 0x80146c98u, 0x80146ca0u, kOverlaySc02_80146C98Words },
    { 0x80146ca0u, 0x80146cb4u, kOverlaySc02_80146CA0Words },
    { 0x80146cb4u, 0x80146cc8u, kOverlaySc02_80146CB4Words },
    { 0x80146cc8u, 0x80146d30u, kOverlaySc02_80146CC8Words },
    { 0x80146d30u, 0x80146d80u, kOverlaySc02_80146D30Words },
    { 0x80146d80u, 0x80146d90u, kOverlaySc02_80146D80Words },
    { 0x80146d90u, 0x80146db8u, kOverlaySc02_80146D90Words },
    { 0x80146db8u, 0x80146de8u, kOverlaySc02_80146DB8Words },
    { 0x80146de8u, 0x80146df8u, kOverlaySc02_80146DE8Words },
    { 0x80146df8u, 0x80146e90u, kOverlaySc02_80146DF8Words },
    { 0x80146e90u, 0x80146e98u, kOverlaySc02_80146E90Words },
    { 0x80146e98u, 0x80146ec0u, kOverlaySc02_80146E98Words },
    { 0x80146ec0u, 0x80146f58u, kOverlaySc02_80146EC0Words },
    { 0x80146f58u, 0x80146fc4u, kOverlaySc02_80146F58Words },
    { 0x80146fc4u, 0x8014704cu, kOverlaySc02_80146FC4Words },
    { 0x8014704cu, 0x80147054u, kOverlaySc02_8014704CWords },
    { 0x80147054u, 0x80147060u, kOverlaySc02_80147054Words },
    { 0x80147060u, 0x8014706cu, kOverlaySc02_80147060Words },
    { 0x8014706cu, 0x80147078u, kOverlaySc02_8014706CWords },
    { 0x80147078u, 0x80147084u, kOverlaySc02_80147078Words },
    { 0x8014708cu, 0x80147098u, kOverlaySc02_8014708CWords },
    { 0x801470a0u, 0x801470acu, kOverlaySc02_801470A0Words },
    { 0x801470b4u, 0x801470c0u, kOverlaySc02_801470B4Words },
    { 0x801470c0u, 0x80147118u, kOverlaySc02_801470C0Words },
    { 0x80147118u, 0x80147264u, kOverlaySc02_80147118Words },
    { 0x80147264u, 0x80147290u, kOverlaySc02_80147264Words },
    { 0x80147290u, 0x801472b4u, kOverlaySc02_80147290Words },
    { 0x801472b4u, 0x801472c8u, kOverlaySc02_801472B4Words },
    { 0x801472c8u, 0x801472dcu, kOverlaySc02_801472C8Words },
    { 0x801472dcu, 0x801472f0u, kOverlaySc02_801472DCWords },
    { 0x801472f0u, 0x80147300u, kOverlaySc02_801472F0Words },
    { 0x80147300u, 0x80147324u, kOverlaySc02_80147300Words },
    { 0x80147324u, 0x80147364u, kOverlaySc02_80147324Words },
    { 0x80147364u, 0x801473dcu, kOverlaySc02_80147364Words },
    { 0x801473dcu, 0x801473ecu, kOverlaySc02_801473DCWords },
    { 0x801473ecu, 0x80147460u, kOverlaySc02_801473ECWords },
    { 0x80147460u, 0x80147478u, kOverlaySc02_80147460Words },
    { 0x80147478u, 0x801474d8u, kOverlaySc02_80147478Words },
    { 0x801474d8u, 0x801474ecu, kOverlaySc02_801474D8Words },
    { 0x801474ecu, 0x80147514u, kOverlaySc02_801474ECWords },
    { 0x80147514u, 0x80147628u, kOverlaySc02_80147514Words },
    { 0x80147628u, 0x80147718u, kOverlaySc02_80147628Words },
    { 0x80147718u, 0x80147788u, kOverlaySc02_80147718Words },
    { 0x80147788u, 0x801477a8u, kOverlaySc02_80147788Words },
    { 0x801477a8u, 0x801477c8u, kOverlaySc02_801477A8Words },
    { 0x801477c8u, 0x801477e8u, kOverlaySc02_801477C8Words },
    { 0x801477e8u, 0x80147814u, kOverlaySc02_801477E8Words },
    { 0x80147814u, 0x80147860u, kOverlaySc02_80147814Words },
    { 0x80147860u, 0x801478b8u, kOverlaySc02_80147860Words },
    { 0x801478b8u, 0x80147928u, kOverlaySc02_801478B8Words },
    { 0x80147928u, 0x80147948u, kOverlaySc02_80147928Words },
    { 0x80147948u, 0x8014799cu, kOverlaySc02_80147948Words },
    { 0x8014799cu, 0x801479bcu, kOverlaySc02_8014799CWords },
    { 0x801479bcu, 0x80147a10u, kOverlaySc02_801479BCWords },
    { 0x80147a10u, 0x80147a30u, kOverlaySc02_80147A10Words },
    { 0x80147a30u, 0x80147a84u, kOverlaySc02_80147A30Words },
    { 0x80147a84u, 0x80147aacu, kOverlaySc02_80147A84Words },
    { 0x80147aacu, 0x80147ad4u, kOverlaySc02_80147AACWords },
    { 0x80147ad4u, 0x80147b18u, kOverlaySc02_80147AD4Words },
    { 0x80147b18u, 0x80147b5cu, kOverlaySc02_80147B18Words },
    { 0x80147b5cu, 0x80147c30u, kOverlaySc02_80147B5CWords },
    { 0x80147c30u, 0x80147cc8u, kOverlaySc02_80147C30Words },
    { 0x80147cc8u, 0x80147d38u, kOverlaySc02_80147CC8Words },
    { 0x80147d38u, 0x80147dc0u, kOverlaySc02_80147D38Words },
    { 0x80147dc0u, 0x80147e44u, kOverlaySc02_80147DC0Words },
    { 0x80147e44u, 0x80147f50u, kOverlaySc02_80147E44Words },
    { 0x80147f50u, 0x80147f78u, kOverlaySc02_80147F50Words },
    { 0x80147f78u, 0x80148038u, kOverlaySc02_80147F78Words },
    { 0x80148038u, 0x80148094u, kOverlaySc02_80148038Words },
    { 0x80148094u, 0x801483e8u, kOverlaySc02_80148094Words },
    { 0x801483e8u, 0x801484b0u, kOverlaySc02_801483E8Words },
    { 0x801484b0u, 0x801484e8u, kOverlaySc02_801484B0Words },
    { 0x801484e8u, 0x80148534u, kOverlaySc02_801484E8Words },
    { 0x80148534u, 0x8014856cu, kOverlaySc02_80148534Words },
    { 0x8014856cu, 0x801485b8u, kOverlaySc02_8014856CWords },
    { 0x801485b8u, 0x80148634u, kOverlaySc02_801485B8Words },
    { 0x80148634u, 0x80148648u, kOverlaySc02_80148634Words },
    { 0x80148648u, 0x801487f4u, kOverlaySc02_80148648Words },
    { 0x801487f4u, 0x80148800u, kOverlaySc02_801487F4Words },
    { 0x80175494u, 0x801754a8u, kOverlaySc02_80175494Words },
};

static const FormatterRange kFormatterRanges25[] = {
    { 0x801284b8u, 0x801284f0u, kOverlaySc02_801284B8Words },
    { 0x801284f0u, 0x8012853cu, kOverlaySc02_801284F0Words },
    { 0x8013b568u, 0x8013b598u, kOverlaySc02_8013B568Words },
    { 0x8013c08cu, 0x8013c0f8u, kOverlaySc02_8013C08CWords },
    { 0x8013c0f8u, 0x8013c360u, kOverlaySc02_8013C0F8Words },
    { 0x8013d3d4u, 0x8013d53cu, kOverlaySc02_8013D3D4Words },
    { 0x80175308u, 0x80175414u, kOverlaySc02_80175308Words },
    { 0x801757a0u, 0x801757e0u, kOverlaySc02_801757A0Words },
    { 0x80175ab8u, 0x80175da8u, kOverlaySc02_80175AB8Words },
    { 0x80175da8u, 0x80176144u, kOverlaySc02_80175DA8Words },
    { 0x80176144u, 0x80176218u, kOverlaySc02_80176144Words },
    { 0x80176d94u, 0x80176ff4u, kOverlaySc02_80176D94Words },
    { 0x801770e0u, 0x80177340u, kOverlaySc02_801770E0Words },
    { 0x8017742cu, 0x801775e0u, kOverlaySc02_8017742CWords },
    { 0x80177784u, 0x801777bcu, kOverlaySc02_80177784Words },
    { 0x801777bcu, 0x801778a8u, kOverlaySc02_801777BCWords },
    { 0x80177940u, 0x80177ad4u, kOverlaySc02_80177940Words },
    { 0x80177b5cu, 0x80177da8u, kOverlaySc02_80177B5CWords },
    { 0x80177ea4u, 0x80177f84u, kOverlaySc02_80177EA4Words },
    { 0x80178004u, 0x80178298u, kOverlaySc02_80178004Words },
    { 0x80178298u, 0x801783d0u, kOverlaySc02_80178298Words },
    { 0x801783d0u, 0x80178438u, kOverlaySc02_801783D0Words },
};

static const FormatterRange kFormatterRanges26[] = {
    { 0x80128158u, 0x80128420u, kOverlaySc02_80128158Words },
    { 0x80129398u, 0x80129428u, kOverlaySc02_80129398Words },
    { 0x8012f14cu, 0x8012f1a4u, kOverlaySc02_8012F14CWords },
    { 0x80148800u, 0x8014880cu, kOverlaySc02_80148800Words },
    { 0x8014880cu, 0x80148818u, kOverlaySc02_8014880CWords },
    { 0x80148818u, 0x80148824u, kOverlaySc02_80148818Words },
    { 0x80148824u, 0x801488a8u, kOverlaySc02_80148824Words },
    { 0x801488a8u, 0x8014891cu, kOverlaySc02_801488A8Words },
    { 0x8014891cu, 0x80148980u, kOverlaySc02_8014891CWords },
    { 0x80148980u, 0x801489e8u, kOverlaySc02_80148980Words },
    { 0x801489e8u, 0x80148a48u, kOverlaySc02_801489E8Words },
    { 0x80148a48u, 0x80148aacu, kOverlaySc02_80148A48Words },
    { 0x80148aacu, 0x80148afcu, kOverlaySc02_80148AACWords },
    { 0x80148afcu, 0x80148c18u, kOverlaySc02_80148AFCWords },
    { 0x80148c18u, 0x80148c20u, kOverlaySc02_80148C18Words },
    { 0x80148c20u, 0x80148c34u, kOverlaySc02_80148C20Words },
    { 0x80148c34u, 0x80148c4cu, kOverlaySc02_80148C34Words },
    { 0x80148c4cu, 0x80148c64u, kOverlaySc02_80148C4CWords },
    { 0x80148c64u, 0x80148c7cu, kOverlaySc02_80148C64Words },
    { 0x80148c7cu, 0x80148c84u, kOverlaySc02_80148C7CWords },
    { 0x80148c84u, 0x80148c9cu, kOverlaySc02_80148C84Words },
    { 0x80148c9cu, 0x80148cb4u, kOverlaySc02_80148C9CWords },
    { 0x80148cb4u, 0x80148cccu, kOverlaySc02_80148CB4Words },
    { 0x80148cccu, 0x80148ce4u, kOverlaySc02_80148CCCWords },
    { 0x80148ce4u, 0x80148cecu, kOverlaySc02_80148CE4Words },
    { 0x80148cecu, 0x80148cf4u, kOverlaySc02_80148CECWords },
    { 0x80148cf4u, 0x80148d0cu, kOverlaySc02_80148CF4Words },
    { 0x80148d0cu, 0x80148d24u, kOverlaySc02_80148D0CWords },
    { 0x80148d24u, 0x80148d3cu, kOverlaySc02_80148D24Words },
    { 0x80148d3cu, 0x80148d44u, kOverlaySc02_80148D3CWords },
    { 0x80148d44u, 0x80148e54u, kOverlaySc02_80148D44Words },
    { 0x80148e54u, 0x80148f60u, kOverlaySc02_80148E54Words },
    { 0x80148f60u, 0x80148f68u, kOverlaySc02_80148F60Words },
    { 0x80148f68u, 0x80148f74u, kOverlaySc02_80148F68Words },
    { 0x80148f74u, 0x80148f80u, kOverlaySc02_80148F74Words },
    { 0x80148f80u, 0x80148f8cu, kOverlaySc02_80148F80Words },
    { 0x80148f8cu, 0x80148f98u, kOverlaySc02_80148F8CWords },
    { 0x80148f98u, 0x80148fa0u, kOverlaySc02_80148F98Words },
    { 0x80148fa0u, 0x80148facu, kOverlaySc02_80148FA0Words },
    { 0x80148facu, 0x80148fb8u, kOverlaySc02_80148FACWords },
    { 0x80148fb8u, 0x80148fc4u, kOverlaySc02_80148FB8Words },
    { 0x80148fc4u, 0x80148fd0u, kOverlaySc02_80148FC4Words },
    { 0x80148fd0u, 0x80148fd8u, kOverlaySc02_80148FD0Words },
    { 0x80148fd8u, 0x80148fe0u, kOverlaySc02_80148FD8Words },
    { 0x80148fe0u, 0x80148fecu, kOverlaySc02_80148FE0Words },
    { 0x80148fecu, 0x80148ff8u, kOverlaySc02_80148FECWords },
    { 0x80148ff8u, 0x80149004u, kOverlaySc02_80148FF8Words },
    { 0x80149004u, 0x8014900cu, kOverlaySc02_80149004Words },
    { 0x8014900cu, 0x80149020u, kOverlaySc02_8014900CWords },
    { 0x80149020u, 0x80149034u, kOverlaySc02_80149020Words },
    { 0x80149034u, 0x80149048u, kOverlaySc02_80149034Words },
    { 0x80149048u, 0x8014905cu, kOverlaySc02_80149048Words },
    { 0x8014905cu, 0x80149078u, kOverlaySc02_8014905CWords },
    { 0x80149078u, 0x801490e0u, kOverlaySc02_80149078Words },
    { 0x801490e0u, 0x801490e8u, kOverlaySc02_801490E0Words },
    { 0x801490e8u, 0x801490f0u, kOverlaySc02_801490E8Words },
    { 0x801490f0u, 0x801490f8u, kOverlaySc02_801490F0Words },
    { 0x801490f8u, 0x80149184u, kOverlaySc02_801490F8Words },
    { 0x80149184u, 0x801491c4u, kOverlaySc02_80149184Words },
    { 0x801491c4u, 0x80149204u, kOverlaySc02_801491C4Words },
    { 0x80149204u, 0x80149210u, kOverlaySc02_80149204Words },
};

static const FormatterRange kFormatterRanges27[] = {
    { 0x80017758u, 0x80017778u, kMain80017758Words },
    { 0x80017778u, 0x800178c8u, kMain80017778Words },
    { 0x800178c8u, 0x800178ecu, kMain800178C8Words },
    { 0x800178ecu, 0x80017910u, kMain800178ECWords },
    { 0x80017910u, 0x80017930u, kMain80017910Words },
    { 0x80017930u, 0x80017b98u, kMain80017930Words },
    { 0x80017b98u, 0x80017d98u, kMain80017B98Words },
    { 0x80017d98u, 0x80017dc4u, kMain80017D98Words },
    { 0x80017dc4u, 0x80017df8u, kMain80017DC4Words },
    { 0x80017df8u, 0x80017e30u, kMain80017DF8Words },
    { 0x80017e30u, 0x80017e68u, kMain80017E30Words },
    { 0x80017e68u, 0x80017e8cu, kMain80017E68Words },
    { 0x80017e8cu, 0x80017f14u, kMain80017E8CWords },
    { 0x80017f14u, 0x80018094u, kMain80017F14Words },
    { 0x80018094u, 0x80018194u, kMain80018094Words },
    { 0x80018194u, 0x8001820cu, kMain80018194Words },
    { 0x8001820cu, 0x80018384u, kMain8001820CWords },
    { 0x80018384u, 0x800183e0u, kMain80018384Words },
    { 0x80048384u, 0x800484ecu, kMain80048384Words },
    { 0x80049610u, 0x80049694u, kMain80049610Words },
    { 0x8004969cu, 0x8004974cu, kMain8004969CWords },
    { 0x80058de8u, 0x80058dfcu, kMain80058DE8Words },
    { 0x80058dfcu, 0x80058e10u, kMain80058DFCWords },
    { 0x80058e10u, 0x80058e24u, kMain80058E10Words },
    { 0x80058e24u, 0x80058e38u, kMain80058E24Words },
    { 0x80058e38u, 0x80058e4cu, kMain80058E38Words },
    { 0x80058e4cu, 0x80058e60u, kMain80058E4CWords },
    { 0x80058e60u, 0x80058e74u, kMain80058E60Words },
    { 0x80058e74u, 0x80058e88u, kMain80058E74Words },
    { 0x80058e88u, 0x80058e9cu, kMain80058E88Words },
    { 0x80058e9cu, 0x80058eb0u, kMain80058E9CWords },
    { 0x80058eb0u, 0x80058ec4u, kMain80058EB0Words },
    { 0x80058ec4u, 0x80058ee4u, kMain80058EC4Words },
    { 0x80058ee4u, 0x80058f04u, kMain80058EE4Words },
    { 0x80058f04u, 0x80058f24u, kMain80058F04Words },
    { 0x80058f24u, 0x80058f44u, kMain80058F24Words },
    { 0x80058f44u, 0x80058f70u, kMain80058F44Words },
    { 0x80058f70u, 0x80058fd0u, kMain80058F70Words },
    { 0x80058fd0u, 0x8005903cu, kMain80058FD0Words },
    { 0x8005903cu, 0x80059074u, kMain8005903CWords },
    { 0x80059074u, 0x80059188u, kMain80059074Words },
    { 0x80059188u, 0x80059234u, kMain80059188Words },
    { 0x80059234u, 0x800593b8u, kMain80059234Words },
    { 0x800593b8u, 0x800594ccu, kMain800593B8Words },
    { 0x800594ccu, 0x80059530u, kMain800594CCWords },
    { 0x80059530u, 0x800595dcu, kMain80059530Words },
    { 0x800595dcu, 0x800595ecu, kMain800595DCWords },
    { 0x800595ecu, 0x800595fcu, kMain800595ECWords },
};

static const FormatterRange kFormatterRanges28[] = {
    { 0x800cedfcu, 0x800cee40u, kOverlay800CEDFCWords },
    { 0x800cee40u, 0x800cef04u, kOverlay800CEE40Words },
    { 0x800cef04u, 0x800cef54u, kOverlay800CEF04Words },
    { 0x800cef54u, 0x800cefa8u, kOverlay800CEF54Words },
    { 0x800cefa8u, 0x800ceff4u, kOverlay800CEFA8Words },
    { 0x800ceff4u, 0x800cf038u, kOverlay800CEFF4Words },
    { 0x800cf038u, 0x800cf0c4u, kOverlay800CF038Words },
    { 0x800cf0c4u, 0x800cf114u, kOverlay800CF0C4Words },
    { 0x800cf114u, 0x800cf180u, kOverlay800CF114Words },
    { 0x800cf180u, 0x800cf290u, kOverlay800CF180Words },
    { 0x800cf290u, 0x800cf3e8u, kOverlay800CF290Words },
};

static const FormatterRange kFormatterRanges29[] = {
    { 0x8005c2c8u, 0x8005c2f8u, kGuardedClear8005C2C8Words },
    { 0x8005de78u, 0x8005e0acu, kInputDigital8005DE78Words },
    { 0x8005e13cu, 0x8005e164u, kInputDigital8005E13CWords },
    { 0x8005e1a4u, 0x8005e228u, kInputDigital8005E1A4Words },
    { 0x8005ea34u, 0x8005ea54u, kInputDigital8005EA34Words },
    { 0x8005ea54u, 0x8005ea68u, kInputDigital8005EA54Words },
    { 0x8005ea68u, 0x8005ea88u, kInputDigital8005EA68Words },
    { 0x8005ea88u, 0x8005eaa8u, kInputDigital8005EA88Words },
    { 0x8005eaa8u, 0x8005eac8u, kInputDigital8005EAA8Words },
    { 0x8005eac8u, 0x8005eae8u, kInputDigital8005EAC8Words },
    { 0x8005eb28u, 0x8005ec00u, kInputDigital8005EB28Words },
    { 0x8005ec00u, 0x8005ecc0u, kInputDigital8005EC00Words },
    { 0x8005ecc0u, 0x8005ed4cu, kInputDigital8005ECC0Words },
    { 0x8005ed4cu, 0x8005f0c8u, kInputDigital8005ED4CWords },
    { 0x8005f290u, 0x8005f384u, kInputDigital8005F290Words },
    { 0x8005f394u, 0x8005f450u, kInputDigital8005F394Words },
    { 0x8005f450u, 0x8005f6ccu, kInputDigital8005F450Words },
    { 0x8005f6ccu, 0x8005f704u, kInputDigital8005F6CCWords },
    { 0x8005fa94u, 0x8005fb70u, kInputDigital8005FA94Words },
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
    {
        uint8_t *canonical = musashi_boot_ram_span(memory, address, width);
        if (canonical) return canonical;
    }
    /* Main RAM decodes only A0..A20, so its 2 MB window repeats every 2 MB
     * across the first 8 MB of KUSEG, KSEG0 and KSEG1, and those three
     * segments alias each other (nocash's RAM mirrors). Retail member 0004
     * stores a halfword to 0x80200000 while walking a buffer to the top of
     * RAM; hardware aliases that to physical 0. The stricter
     * musashi_boot_ram_span contract is deliberately unchanged: this alias is
     * the CPU bus decode, not the boot-image API. */
    {
        uint32_t segment = address & 0xe0000000u;
        uint32_t offset = physical;
        if ((segment == 0u || segment == 0x80000000u || segment == 0xa0000000u) &&
            offset < 0x00800000u) {
            offset &= MUSASHI_RAM_SIZE - 1u;
            if (width <= MUSASHI_RAM_SIZE && offset <= MUSASHI_RAM_SIZE - width)
                return memory ? memory->bytes + offset : NULL;
        }
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

/* Generated retire table: an LWR retires when its successor is the next
 * LWL/SWL/SWR of the same copy block.
 *
 * This was 117 `(pc == H && instruction == H && merge_reg == N)` terms in a
 * single `||` expression. GCC's dominator pass spent 12 of this file's 14
 * seconds of compile time on that one function -- confirmed with
 * -fdisable-tree-dom1/2/3=merge_pending_matches, which takes the whole file
 * from 14.2s to 2.2s. 83 tests in the suite give `cc` a 30-second budget,
 * so the expression form had already made the file time out under load.
 *
 * The terms were machine-generated, and they are data: one row per site,
 * matched exactly as before on all three fields. */
typedef struct {
    uint32_t pc;
    uint32_t word;
    uint8_t reg;
} MergeRetireSite;

static const MergeRetireSite kMergeRetireSites[] = {
    { 0x800d251cu, 0x88a30007u, 2u },
    { 0x800d2524u, 0xaba20013u, 3u },
    { 0x8012a0acu, 0x88830027u, 2u },
    { 0x8012a0b4u, 0xa882001bu, 3u },
    { 0x80134268u, 0x8a630007u, 2u },
    { 0x80134270u, 0xa8a20003u, 3u },
    { 0x801349ccu, 0x8a830007u, 2u },
    { 0x801349d4u, 0xa8a20003u, 3u },
    { 0x80136ca8u, 0x88a30007u, 2u },
    { 0x80136cb0u, 0x80a40008u, 3u },
    { 0x8013d65cu, 0x88a30007u, 2u },
    { 0x8013d664u, 0xa8820003u, 3u },
    { 0x80146168u, 0x88a30007u, 2u },
    { 0x80146170u, 0xa8820003u, 3u },
    { 0x80146490u, 0x88a30007u, 2u },
    { 0x80146498u, 0xa8820003u, 3u },
    { 0x80147008u, 0x8a030007u, 2u },
    { 0x80147010u, 0xaa22008bu, 3u },
    { 0x80147530u, 0x8a030127u, 2u },
    { 0x80147538u, 0xaba20013u, 3u },
    { 0x8014be1cu, 0x8a03009fu, 2u },
    { 0x8014be24u, 0xaba20013u, 3u },
    { 0x8014c520u, 0x88e30007u, 2u },
    { 0x8014c528u, 0xa902007fu, 3u },
    { 0x8014c758u, 0x88440017u, 3u },
    { 0x8014c760u, 0xaa030167u, 4u },
    { 0x8014c868u, 0x88a30007u, 2u },
    { 0x8014c870u, 0xa8820157u, 3u },
    { 0x8014c8d0u, 0x88a30007u, 2u },
    { 0x8014c8d8u, 0xa882015fu, 3u },
    { 0x8014c8f8u, 0x88830097u, 2u },
    { 0x8014c900u, 0xa882015fu, 3u },
    { 0x8014cbacu, 0x88830007u, 2u },
    { 0x8014cbb4u, 0xa8c20003u, 3u },
    { 0x8014db78u, 0x8ba3002fu, 2u },
    { 0x8014db80u, 0xaba20033u, 3u },
    { 0x8014ea8cu, 0x8a230007u, 2u },
    { 0x8014ea94u, 0xaba20023u, 3u },
    { 0x8014f5dcu, 0x88a30007u, 2u },
    { 0x8014f5e4u, 0xaa020123u, 3u },
    { 0x8014f614u, 0x88a30007u, 2u },
    { 0x8014f61cu, 0xaa020123u, 3u },
    { 0x8014f670u, 0x88a30007u, 2u },
    { 0x8014f678u, 0xa8820003u, 3u },
    { 0x8014f6acu, 0x88a30007u, 2u },
    { 0x8014f6b4u, 0xaa020123u, 3u },
    { 0x8014f874u, 0x88a30007u, 2u },
    { 0x8014f87cu, 0xaa020123u, 3u },
    { 0x8014f8acu, 0x88a30007u, 2u },
    { 0x8014f8b4u, 0xaa020123u, 3u },
    { 0x8014f908u, 0x88a30007u, 2u },
    { 0x8014f910u, 0xa8820003u, 3u },
    { 0x8014f944u, 0x88a30007u, 2u },
    { 0x8014f94cu, 0xaa020123u, 3u },
    { 0x8014fb64u, 0x88a30007u, 2u },
    { 0x8014fb6cu, 0xa8820003u, 3u },
    { 0x8014ff20u, 0x8ba30027u, 2u },
    { 0x8014ff28u, 0xaa020083u, 3u },
    { 0x8014ff74u, 0x88a30007u, 2u },
    { 0x8014ff7cu, 0xaa020083u, 3u },
    { 0x80150008u, 0x8a430007u, 2u },
    { 0x80150010u, 0xaba20013u, 3u },
    { 0x80150080u, 0x8ba30017u, 2u },
    { 0x80150088u, 0xaba2001bu, 3u },
    { 0x801500d0u, 0x8ba3001fu, 2u },
    { 0x801500d8u, 0xaa420003u, 3u },
    { 0x801500f8u, 0x88a30007u, 2u },
    { 0x80150100u, 0xaa820003u, 3u },
    { 0x80150230u, 0x8ba30027u, 2u },
    { 0x80150238u, 0xaa020083u, 3u },
    { 0x80150284u, 0x88a30007u, 2u },
    { 0x8015028cu, 0xaa020083u, 3u },
    { 0x80150318u, 0x8a430007u, 2u },
    { 0x80150320u, 0xaba20013u, 3u },
    { 0x80150390u, 0x8ba30017u, 2u },
    { 0x80150398u, 0xaba2001bu, 3u },
    { 0x801503e0u, 0x8ba3001fu, 2u },
    { 0x801503e8u, 0xaa420003u, 3u },
    { 0x80150408u, 0x88a30007u, 2u },
    { 0x80150410u, 0xaa820003u, 3u },
    { 0x80163420u, 0x89230007u, 2u },
    { 0x80163428u, 0xaba2001bu, 3u },
    { 0x801634f4u, 0x89480007u, 2u },
    { 0x801634fcu, 0xaba2001bu, 8u },
    { 0x80172384u, 0x88a30007u, 2u },
    { 0x8017238cu, 0xa8820093u, 3u },
    { 0x801723a4u, 0x88830097u, 2u },
    { 0x801723acu, 0xa882008bu, 3u },
    { 0x80172798u, 0x88830007u, 2u },
    { 0x801727a0u, 0xa8c20003u, 3u },
    { 0x801728acu, 0x88830007u, 2u },
    { 0x801728b4u, 0xa8c20003u, 3u },
    { 0x80172c68u, 0x88830007u, 2u },
    { 0x80172c70u, 0xa8c20003u, 3u },
    { 0x80173420u, 0x8a030007u, 2u },
    { 0x80173428u, 0xa8a20003u, 3u },
    { 0x80173484u, 0x8a030007u, 2u },
    { 0x8017348cu, 0xa8a20003u, 3u },
    { 0x80179488u, 0x8ba4002fu, 2u },
    { 0x80179490u, 0xaa02000fu, 4u },
    { 0x801794e8u, 0x8ba4003fu, 2u },
    { 0x801794f0u, 0xaa02000fu, 4u },
    { 0x8017b8f8u, 0x88830007u, 2u },
    { 0x8017b900u, 0xa8c20003u, 3u },
    { 0x8017b920u, 0x8883000fu, 2u },
    { 0x8017b928u, 0xa8c20003u, 3u },
    { 0x8017c4d4u, 0x88c30007u, 2u },
    { 0x8017c4dcu, 0x88c4000bu, 3u },
    { 0x8017c4e4u, 0x88c5000fu, 4u },
    { 0x8017c4ecu, 0xa8e20003u, 5u },
    { 0x8017c554u, 0x88c30007u, 2u },
    { 0x8017c55cu, 0x88c4000bu, 3u },
    { 0x8017c564u, 0xa8e20003u, 4u },
    { 0x801826b4u, 0x8a630007u, 2u },
    { 0x801826bcu, 0xaba20013u, 3u },
    { 0x8018288cu, 0x8a630007u, 2u },
    { 0x80182894u, 0xaba20013u, 3u },
    { 0x80183f08u, 0x89829482u, 2u },
};

MUSASHI_FORMATTER_NOINLINE static int merge_retire_site(uint32_t pc, uint32_t word,
                                                        unsigned reg) {
    size_t index;

    for (index = 0; index < sizeof kMergeRetireSites / sizeof kMergeRetireSites[0]; ++index) {
        if (kMergeRetireSites[index].pc == pc
                && kMergeRetireSites[index].word == word
                && kMergeRetireSites[index].reg == reg) {
            return 1;
        }
    }
    return 0;
}

static int merge_kind_for(uint32_t pc, uint32_t instruction) {
    static const struct { uint32_t pc, word; uint8_t kind; } sites[] = {
        {0x80045720u,0x88a20003u,MERGE_LWL},
        {0x80045724u,0x98a20000u,MERGE_LWR},
        {0x8004572cu,0xaba2001bu,MERGE_SWL},
        {0x80045730u,0xbba20018u,MERGE_SWR},
        {0x800457e4u,0x8a230005u,MERGE_LWL},
        {0x800457e8u,0x9a230002u,MERGE_LWR},
        {0x800457f0u,0xa8430003u,MERGE_SWL},
        {0x800457f4u,0xb8430000u,MERGE_SWR},
        {0x80045ae4u,0x8a020005u,MERGE_LWL},
        {0x80045ae8u,0x9a020002u,MERGE_LWR},
        {0x80045af0u,0xaba2001bu,MERGE_SWL},
        {0x80045af4u,0xbba20018u,MERGE_SWR},
        {0x80045b0cu,0x8a03000du,MERGE_LWL},
        {0x80045b10u,0x9a03000au,MERGE_LWR},
        {0x80045b18u,0xa8430003u,MERGE_SWL},
        {0x80045b1cu,0xb8430000u,MERGE_SWR},
        {0x800469fcu,0x8862001fu,MERGE_LWL},
        {0x80046a00u,0x9862001cu,MERGE_LWR},
        {0x80046a08u,0xa8c20003u,MERGE_SWL},
        {0x80046a0cu,0xb8c20000u,MERGE_SWR},
        {0x80046fd0u,0x8ba4002bu,MERGE_LWL},
        {0x80046fd4u,0x9ba40028u,MERGE_LWR},
        {0x80046fdcu,0xa844001fu,MERGE_SWL},
        {0x80046fe0u,0xb844001cu,MERGE_SWR},
        {0x800cfac4u,0x9bbbbbcdu,MERGE_LWR},
        {0x800cfb04u,0x9bbbbbcdu,MERGE_LWR},
        {0x800cfb44u,0x9bbbbbcdu,MERGE_LWR},
        {0x800cfc04u,0x99ddddd0u,MERGE_LWR},
        {0x800cfc44u,0xaaddaa00u,MERGE_SWL},
        {0x800d0144u,0x9bbbbbcdu,MERGE_LWR},
        {0x800d0184u,0x9bbbbbcdu,MERGE_LWR},
        {0x800d01c4u,0x9bbbbbcdu,MERGE_LWR},
        {0x800d0284u,0x99ddddd0u,MERGE_LWR},
        {0x800d02c4u,0xaaddaa00u,MERGE_SWL},
        {0x800d11bcu,0x9a908264u,MERGE_LWR},
        {0x800d1200u,0xaa1e0000u,MERGE_SWL},
        {0x800d1334u,0xa80f0000u,MERGE_SWL},
        {0x800d1fa4u,0x98000000u,MERGE_LWR},
        {0x800d2154u,0x980391ffu,MERGE_LWR},
        {0x800d2168u,0xabababafu,MERGE_SWL},
        {0x800d229cu,0x8affffffu,MERGE_LWL},
        {0x800d2504u,0xbb080000u,MERGE_SWR},
        {0x800d2514u,0x88a20003u,MERGE_LWL},
        {0x800d2518u,0x98a20000u,MERGE_LWR},
        {0x800d251cu,0x88a30007u,MERGE_LWL},
        {0x800d2520u,0x98a30004u,MERGE_LWR},
        {0x800d2524u,0xaba20013u,MERGE_SWL},
        {0x800d2528u,0xbba20010u,MERGE_SWR},
        {0x800d252cu,0xaba30017u,MERGE_SWL},
        {0x800d2530u,0xbba30014u,MERGE_SWR},
        {0x800d2638u,0xb9140000u,MERGE_SWR},
        {0x800d27a4u,0xb927d0ffu,MERGE_SWR},
        {0x800d28f8u,0x98060000u,MERGE_LWR},
        {0x800d2a80u,0x98320800u,MERGE_LWR},
        {0x800d2d6cu,0xba4cbcffu,MERGE_SWR},
        {0x800d2f60u,0x8970666cu,MERGE_LWL},
        {0x800d3444u,0x88c2fbffu,MERGE_LWL},
        {0x800d34c0u,0xb9f3ffffu,MERGE_SWR},
        {0x800d34e8u,0xabebffffu,MERGE_SWL},
        {0x8012a0a4u,0x88820023u,MERGE_LWL},
        {0x8012a0a8u,0x98820020u,MERGE_LWR},
        {0x8012a0acu,0x88830027u,MERGE_LWL},
        {0x8012a0b0u,0x98830024u,MERGE_LWR},
        {0x8012a0b4u,0xa882001bu,MERGE_SWL},
        {0x8012a0b8u,0xb8820018u,MERGE_SWR},
        {0x8012a0bcu,0xa883001fu,MERGE_SWL},
        {0x8012a0c0u,0xb883001cu,MERGE_SWR},
        {0x80134260u,0x8a620003u,MERGE_LWL},
        {0x80134264u,0x9a620000u,MERGE_LWR},
        {0x80134268u,0x8a630007u,MERGE_LWL},
        {0x8013426cu,0x9a630004u,MERGE_LWR},
        {0x80134270u,0xa8a20003u,MERGE_SWL},
        {0x80134274u,0xb8a20000u,MERGE_SWR},
        {0x80134278u,0xa8a30007u,MERGE_SWL},
        {0x8013427cu,0xb8a30004u,MERGE_SWR},
        {0x801349c4u,0x8a820003u,MERGE_LWL},
        {0x801349c8u,0x9a820000u,MERGE_LWR},
        {0x801349ccu,0x8a830007u,MERGE_LWL},
        {0x801349d0u,0x9a830004u,MERGE_LWR},
        {0x801349d4u,0xa8a20003u,MERGE_SWL},
        {0x801349d8u,0xb8a20000u,MERGE_SWR},
        {0x801349dcu,0xa8a30007u,MERGE_SWL},
        {0x801349e0u,0xb8a30004u,MERGE_SWR},
        {0x80136ca0u,0x88a20003u,MERGE_LWL},
        {0x80136ca4u,0x98a20000u,MERGE_LWR},
        {0x80136ca8u,0x88a30007u,MERGE_LWL},
        {0x80136cacu,0x98a30004u,MERGE_LWR},
        {0x80136cb4u,0xaba2001bu,MERGE_SWL},
        {0x80136cb8u,0xbba20018u,MERGE_SWR},
        {0x80136cbcu,0xaba3001fu,MERGE_SWL},
        {0x80136cc0u,0xbba3001cu,MERGE_SWR},
        {0x8013ae98u,0x8b030003u,MERGE_LWL},
        {0x8013ae9cu,0x9b030000u,MERGE_LWR},
        {0x8013aea4u,0xa8430003u,MERGE_SWL},
        {0x8013aea8u,0xb8430000u,MERGE_SWR},
        {0x8013cc34u,0x882355a3u,MERGE_LWL},
        {0x8013cc40u,0x982355a0u,MERGE_LWR},
        {0x8013cc4cu,0x882455a7u,MERGE_LWL},
        {0x8013cc58u,0x982455a4u,MERGE_LWR},
        {0x8013cc68u,0xa8c30003u,MERGE_SWL},
        {0x8013cc6cu,0xb8c30000u,MERGE_SWR},
        {0x8013cc70u,0xa8c40007u,MERGE_SWL},
        {0x8013cc74u,0xb8c40004u,MERGE_SWR},
        {0x8013d5fcu,0x882355a3u,MERGE_LWL},
        {0x8013d5fcu,0x8823ecb3u,MERGE_LWL},
        {0x8013d608u,0x982355a0u,MERGE_LWR},
        {0x8013d608u,0x9823ecb0u,MERGE_LWR},
        {0x8013d614u,0x882455a7u,MERGE_LWL},
        {0x8013d614u,0x8824ecb7u,MERGE_LWL},
        {0x8013d620u,0x982455a4u,MERGE_LWR},
        {0x8013d620u,0x9824ecb4u,MERGE_LWR},
        {0x8013d630u,0xa8c30003u,MERGE_SWL},
        {0x8013d634u,0xb8c30000u,MERGE_SWR},
        {0x8013d638u,0xa8c40007u,MERGE_SWL},
        {0x8013d63cu,0xb8c40004u,MERGE_SWR},
        {0x8013d654u,0x88a20003u,MERGE_LWL},
        {0x8013d658u,0x98a20000u,MERGE_LWR},
        {0x8013d65cu,0x88a30007u,MERGE_LWL},
        {0x8013d660u,0x98a30004u,MERGE_LWR},
        {0x8013d664u,0xa8820003u,MERGE_SWL},
        {0x8013d668u,0xb8820000u,MERGE_SWR},
        {0x8013d66cu,0xa8830007u,MERGE_SWL},
        {0x8013d670u,0xb8830004u,MERGE_SWR},
        {0x80146160u,0x88a20003u,MERGE_LWL},
        {0x80146164u,0x98a20000u,MERGE_LWR},
        {0x80146168u,0x88a30007u,MERGE_LWL},
        {0x8014616cu,0x98a30004u,MERGE_LWR},
        {0x80146170u,0xa8820003u,MERGE_SWL},
        {0x80146174u,0xb8820000u,MERGE_SWR},
        {0x80146178u,0xa8830007u,MERGE_SWL},
        {0x8014617cu,0xb8830004u,MERGE_SWR},
        {0x80146488u,0x88a20003u,MERGE_LWL},
        {0x8014648cu,0x98a20000u,MERGE_LWR},
        {0x80146490u,0x88a30007u,MERGE_LWL},
        {0x80146494u,0x98a30004u,MERGE_LWR},
        {0x80146498u,0xa8820003u,MERGE_SWL},
        {0x8014649cu,0xb8820000u,MERGE_SWR},
        {0x801464a0u,0xa8830007u,MERGE_SWL},
        {0x801464a4u,0xb8830004u,MERGE_SWR},
        {0x80147000u,0x8a020003u,MERGE_LWL},
        {0x80147004u,0x9a020000u,MERGE_LWR},
        {0x80147008u,0x8a030007u,MERGE_LWL},
        {0x8014700cu,0x9a030004u,MERGE_LWR},
        {0x80147010u,0xaa22008bu,MERGE_SWL},
        {0x80147014u,0xba220088u,MERGE_SWR},
        {0x80147018u,0xaa23008fu,MERGE_SWL},
        {0x8014701cu,0xba23008cu,MERGE_SWR},
        {0x80147528u,0x8a020123u,MERGE_LWL},
        {0x8014752cu,0x9a020120u,MERGE_LWR},
        {0x80147530u,0x8a030127u,MERGE_LWL},
        {0x80147534u,0x9a030124u,MERGE_LWR},
        {0x80147538u,0xaba20013u,MERGE_SWL},
        {0x8014753cu,0xbba20010u,MERGE_SWR},
        {0x80147540u,0xaba30017u,MERGE_SWL},
        {0x80147544u,0xbba30014u,MERGE_SWR},
        {0x8014be14u,0x8a02009bu,MERGE_LWL},
        {0x8014be18u,0x9a020098u,MERGE_LWR},
        {0x8014be1cu,0x8a03009fu,MERGE_LWL},
        {0x8014be20u,0x9a03009cu,MERGE_LWR},
        {0x8014be24u,0xaba20013u,MERGE_SWL},
        {0x8014be28u,0xbba20010u,MERGE_SWR},
        {0x8014be2cu,0xaba30017u,MERGE_SWL},
        {0x8014be30u,0xbba30014u,MERGE_SWR},
        {0x8014c518u,0x88e20003u,MERGE_LWL},
        {0x8014c51cu,0x98e20000u,MERGE_LWR},
        {0x8014c520u,0x88e30007u,MERGE_LWL},
        {0x8014c524u,0x98e30004u,MERGE_LWR},
        {0x8014c528u,0xa902007fu,MERGE_SWL},
        {0x8014c52cu,0xb902007cu,MERGE_SWR},
        {0x8014c530u,0xa9030083u,MERGE_SWL},
        {0x8014c534u,0xb9030080u,MERGE_SWR},
        {0x8014c750u,0x88430013u,MERGE_LWL},
        {0x8014c754u,0x98430010u,MERGE_LWR},
        {0x8014c758u,0x88440017u,MERGE_LWL},
        {0x8014c75cu,0x98440014u,MERGE_LWR},
        {0x8014c760u,0xaa030167u,MERGE_SWL},
        {0x8014c764u,0xba030164u,MERGE_SWR},
        {0x8014c768u,0xaa04016bu,MERGE_SWL},
        {0x8014c76cu,0xba040168u,MERGE_SWR},
        {0x8014c860u,0x88a20003u,MERGE_LWL},
        {0x8014c864u,0x98a20000u,MERGE_LWR},
        {0x8014c868u,0x88a30007u,MERGE_LWL},
        {0x8014c86cu,0x98a30004u,MERGE_LWR},
        {0x8014c870u,0xa8820157u,MERGE_SWL},
        {0x8014c874u,0xb8820154u,MERGE_SWR},
        {0x8014c878u,0xa883015bu,MERGE_SWL},
        {0x8014c87cu,0xb8830158u,MERGE_SWR},
        {0x8014c8c8u,0x88a20003u,MERGE_LWL},
        {0x8014c8ccu,0x98a20000u,MERGE_LWR},
        {0x8014c8d0u,0x88a30007u,MERGE_LWL},
        {0x8014c8d4u,0x98a30004u,MERGE_LWR},
        {0x8014c8d8u,0xa882015fu,MERGE_SWL},
        {0x8014c8dcu,0xb882015cu,MERGE_SWR},
        {0x8014c8e0u,0xa8830163u,MERGE_SWL},
        {0x8014c8e4u,0xb8830160u,MERGE_SWR},
        {0x8014c8f0u,0x88820093u,MERGE_LWL},
        {0x8014c8f4u,0x98820090u,MERGE_LWR},
        {0x8014c8f8u,0x88830097u,MERGE_LWL},
        {0x8014c8fcu,0x98830094u,MERGE_LWR},
        {0x8014c900u,0xa882015fu,MERGE_SWL},
        {0x8014c904u,0xb882015cu,MERGE_SWR},
        {0x8014c908u,0xa8830163u,MERGE_SWL},
        {0x8014c90cu,0xb8830160u,MERGE_SWR},
        {0x8014cba4u,0x88820003u,MERGE_LWL},
        {0x8014cba8u,0x98820000u,MERGE_LWR},
        {0x8014cbacu,0x88830007u,MERGE_LWL},
        {0x8014cbb0u,0x98830004u,MERGE_LWR},
        {0x8014cbb4u,0xa8c20003u,MERGE_SWL},
        {0x8014cbb8u,0xb8c20000u,MERGE_SWR},
        {0x8014cbbcu,0xa8c30007u,MERGE_SWL},
        {0x8014cbc0u,0xb8c30004u,MERGE_SWR},
        {0x8014db70u,0x8ba2002bu,MERGE_LWL},
        {0x8014db74u,0x9ba20028u,MERGE_LWR},
        {0x8014db78u,0x8ba3002fu,MERGE_LWL},
        {0x8014db7cu,0x9ba3002cu,MERGE_LWR},
        {0x8014db80u,0xaba20033u,MERGE_SWL},
        {0x8014db84u,0xbba20030u,MERGE_SWR},
        {0x8014db88u,0xaba30037u,MERGE_SWL},
        {0x8014db8cu,0xbba30034u,MERGE_SWR},
        {0x8014ea84u,0x8a220003u,MERGE_LWL},
        {0x8014ea88u,0x9a220000u,MERGE_LWR},
        {0x8014ea8cu,0x8a230007u,MERGE_LWL},
        {0x8014ea90u,0x9a230004u,MERGE_LWR},
        {0x8014ea94u,0xaba20023u,MERGE_SWL},
        {0x8014ea98u,0xbba20020u,MERGE_SWR},
        {0x8014ea9cu,0xaba30027u,MERGE_SWL},
        {0x8014eaa0u,0xbba30024u,MERGE_SWR},
        {0x8014f5d4u,0x88a20003u,MERGE_LWL},
        {0x8014f5d8u,0x98a20000u,MERGE_LWR},
        {0x8014f5dcu,0x88a30007u,MERGE_LWL},
        {0x8014f5e0u,0x98a30004u,MERGE_LWR},
        {0x8014f5e4u,0xaa020123u,MERGE_SWL},
        {0x8014f5e8u,0xba020120u,MERGE_SWR},
        {0x8014f5ecu,0xaa030127u,MERGE_SWL},
        {0x8014f5f0u,0xba030124u,MERGE_SWR},
        {0x8014f60cu,0x88a20003u,MERGE_LWL},
        {0x8014f610u,0x98a20000u,MERGE_LWR},
        {0x8014f614u,0x88a30007u,MERGE_LWL},
        {0x8014f618u,0x98a30004u,MERGE_LWR},
        {0x8014f61cu,0xaa020123u,MERGE_SWL},
        {0x8014f620u,0xba020120u,MERGE_SWR},
        {0x8014f624u,0xaa030127u,MERGE_SWL},
        {0x8014f628u,0xba030124u,MERGE_SWR},
        {0x8014f668u,0x88a20003u,MERGE_LWL},
        {0x8014f66cu,0x98a20000u,MERGE_LWR},
        {0x8014f670u,0x88a30007u,MERGE_LWL},
        {0x8014f674u,0x98a30004u,MERGE_LWR},
        {0x8014f678u,0xa8820003u,MERGE_SWL},
        {0x8014f67cu,0xb8820000u,MERGE_SWR},
        {0x8014f680u,0xa8830007u,MERGE_SWL},
        {0x8014f684u,0xb8830004u,MERGE_SWR},
        {0x8014f6a4u,0x88a20003u,MERGE_LWL},
        {0x8014f6a8u,0x98a20000u,MERGE_LWR},
        {0x8014f6acu,0x88a30007u,MERGE_LWL},
        {0x8014f6b0u,0x98a30004u,MERGE_LWR},
        {0x8014f6b4u,0xaa020123u,MERGE_SWL},
        {0x8014f6b8u,0xba020120u,MERGE_SWR},
        {0x8014f6bcu,0xaa030127u,MERGE_SWL},
        {0x8014f6c0u,0xba030124u,MERGE_SWR},
        {0x8014f86cu,0x88a20003u,MERGE_LWL},
        {0x8014f870u,0x98a20000u,MERGE_LWR},
        {0x8014f874u,0x88a30007u,MERGE_LWL},
        {0x8014f878u,0x98a30004u,MERGE_LWR},
        {0x8014f87cu,0xaa020123u,MERGE_SWL},
        {0x8014f880u,0xba020120u,MERGE_SWR},
        {0x8014f884u,0xaa030127u,MERGE_SWL},
        {0x8014f888u,0xba030124u,MERGE_SWR},
        {0x8014f8a4u,0x88a20003u,MERGE_LWL},
        {0x8014f8a8u,0x98a20000u,MERGE_LWR},
        {0x8014f8acu,0x88a30007u,MERGE_LWL},
        {0x8014f8b0u,0x98a30004u,MERGE_LWR},
        {0x8014f8b4u,0xaa020123u,MERGE_SWL},
        {0x8014f8b8u,0xba020120u,MERGE_SWR},
        {0x8014f8bcu,0xaa030127u,MERGE_SWL},
        {0x8014f8c0u,0xba030124u,MERGE_SWR},
        {0x8014f900u,0x88a20003u,MERGE_LWL},
        {0x8014f904u,0x98a20000u,MERGE_LWR},
        {0x8014f908u,0x88a30007u,MERGE_LWL},
        {0x8014f90cu,0x98a30004u,MERGE_LWR},
        {0x8014f910u,0xa8820003u,MERGE_SWL},
        {0x8014f914u,0xb8820000u,MERGE_SWR},
        {0x8014f918u,0xa8830007u,MERGE_SWL},
        {0x8014f91cu,0xb8830004u,MERGE_SWR},
        {0x8014f93cu,0x88a20003u,MERGE_LWL},
        {0x8014f940u,0x98a20000u,MERGE_LWR},
        {0x8014f944u,0x88a30007u,MERGE_LWL},
        {0x8014f948u,0x98a30004u,MERGE_LWR},
        {0x8014f94cu,0xaa020123u,MERGE_SWL},
        {0x8014f950u,0xba020120u,MERGE_SWR},
        {0x8014f954u,0xaa030127u,MERGE_SWL},
        {0x8014f958u,0xba030124u,MERGE_SWR},
        {0x8014fb5cu,0x88a20003u,MERGE_LWL},
        {0x8014fb60u,0x98a20000u,MERGE_LWR},
        {0x8014fb64u,0x88a30007u,MERGE_LWL},
        {0x8014fb68u,0x98a30004u,MERGE_LWR},
        {0x8014fb6cu,0xa8820003u,MERGE_SWL},
        {0x8014fb70u,0xb8820000u,MERGE_SWR},
        {0x8014fb74u,0xa8830007u,MERGE_SWL},
        {0x8014fb78u,0xb8830004u,MERGE_SWR},
        {0x8014ff18u,0x8ba20023u,MERGE_LWL},
        {0x8014ff1cu,0x9ba20020u,MERGE_LWR},
        {0x8014ff20u,0x8ba30027u,MERGE_LWL},
        {0x8014ff24u,0x9ba30024u,MERGE_LWR},
        {0x8014ff28u,0xaa020083u,MERGE_SWL},
        {0x8014ff2cu,0xba020080u,MERGE_SWR},
        {0x8014ff30u,0xaa030087u,MERGE_SWL},
        {0x8014ff34u,0xba030084u,MERGE_SWR},
        {0x8014ff6cu,0x88a20003u,MERGE_LWL},
        {0x8014ff70u,0x98a20000u,MERGE_LWR},
        {0x8014ff74u,0x88a30007u,MERGE_LWL},
        {0x8014ff78u,0x98a30004u,MERGE_LWR},
        {0x8014ff7cu,0xaa020083u,MERGE_SWL},
        {0x8014ff80u,0xba020080u,MERGE_SWR},
        {0x8014ff84u,0xaa030087u,MERGE_SWL},
        {0x8014ff88u,0xba030084u,MERGE_SWR},
        {0x80150000u,0x8a420003u,MERGE_LWL},
        {0x80150004u,0x9a420000u,MERGE_LWR},
        {0x80150008u,0x8a430007u,MERGE_LWL},
        {0x8015000cu,0x9a430004u,MERGE_LWR},
        {0x80150010u,0xaba20013u,MERGE_SWL},
        {0x80150014u,0xbba20010u,MERGE_SWR},
        {0x80150018u,0xaba30017u,MERGE_SWL},
        {0x8015001cu,0xbba30014u,MERGE_SWR},
        {0x80150078u,0x8ba20013u,MERGE_LWL},
        {0x8015007cu,0x9ba20010u,MERGE_LWR},
        {0x80150080u,0x8ba30017u,MERGE_LWL},
        {0x80150084u,0x9ba30014u,MERGE_LWR},
        {0x80150088u,0xaba2001bu,MERGE_SWL},
        {0x8015008cu,0xbba20018u,MERGE_SWR},
        {0x80150090u,0xaba3001fu,MERGE_SWL},
        {0x80150094u,0xbba3001cu,MERGE_SWR},
        {0x801500c8u,0x8ba2001bu,MERGE_LWL},
        {0x801500ccu,0x9ba20018u,MERGE_LWR},
        {0x801500d0u,0x8ba3001fu,MERGE_LWL},
        {0x801500d4u,0x9ba3001cu,MERGE_LWR},
        {0x801500d8u,0xaa420003u,MERGE_SWL},
        {0x801500dcu,0xba420000u,MERGE_SWR},
        {0x801500e0u,0xaa430007u,MERGE_SWL},
        {0x801500e4u,0xba430004u,MERGE_SWR},
        {0x801500f0u,0x88a20003u,MERGE_LWL},
        {0x801500f4u,0x98a20000u,MERGE_LWR},
        {0x801500f8u,0x88a30007u,MERGE_LWL},
        {0x801500fcu,0x98a30004u,MERGE_LWR},
        {0x80150100u,0xaa820003u,MERGE_SWL},
        {0x80150104u,0xba820000u,MERGE_SWR},
        {0x80150108u,0xaa830007u,MERGE_SWL},
        {0x8015010cu,0xba830004u,MERGE_SWR},
        {0x80150228u,0x8ba20023u,MERGE_LWL},
        {0x8015022cu,0x9ba20020u,MERGE_LWR},
        {0x80150230u,0x8ba30027u,MERGE_LWL},
        {0x80150234u,0x9ba30024u,MERGE_LWR},
        {0x80150238u,0xaa020083u,MERGE_SWL},
        {0x8015023cu,0xba020080u,MERGE_SWR},
        {0x80150240u,0xaa030087u,MERGE_SWL},
        {0x80150244u,0xba030084u,MERGE_SWR},
        {0x8015027cu,0x88a20003u,MERGE_LWL},
        {0x80150280u,0x98a20000u,MERGE_LWR},
        {0x80150284u,0x88a30007u,MERGE_LWL},
        {0x80150288u,0x98a30004u,MERGE_LWR},
        {0x8015028cu,0xaa020083u,MERGE_SWL},
        {0x80150290u,0xba020080u,MERGE_SWR},
        {0x80150294u,0xaa030087u,MERGE_SWL},
        {0x80150298u,0xba030084u,MERGE_SWR},
        {0x80150310u,0x8a420003u,MERGE_LWL},
        {0x80150314u,0x9a420000u,MERGE_LWR},
        {0x80150318u,0x8a430007u,MERGE_LWL},
        {0x8015031cu,0x9a430004u,MERGE_LWR},
        {0x80150320u,0xaba20013u,MERGE_SWL},
        {0x80150324u,0xbba20010u,MERGE_SWR},
        {0x80150328u,0xaba30017u,MERGE_SWL},
        {0x8015032cu,0xbba30014u,MERGE_SWR},
        {0x80150388u,0x8ba20013u,MERGE_LWL},
        {0x8015038cu,0x9ba20010u,MERGE_LWR},
        {0x80150390u,0x8ba30017u,MERGE_LWL},
        {0x80150394u,0x9ba30014u,MERGE_LWR},
        {0x80150398u,0xaba2001bu,MERGE_SWL},
        {0x8015039cu,0xbba20018u,MERGE_SWR},
        {0x801503a0u,0xaba3001fu,MERGE_SWL},
        {0x801503a4u,0xbba3001cu,MERGE_SWR},
        {0x801503d8u,0x8ba2001bu,MERGE_LWL},
        {0x801503dcu,0x9ba20018u,MERGE_LWR},
        {0x801503e0u,0x8ba3001fu,MERGE_LWL},
        {0x801503e4u,0x9ba3001cu,MERGE_LWR},
        {0x801503e8u,0xaa420003u,MERGE_SWL},
        {0x801503ecu,0xba420000u,MERGE_SWR},
        {0x801503f0u,0xaa430007u,MERGE_SWL},
        {0x801503f4u,0xba430004u,MERGE_SWR},
        {0x80150400u,0x88a20003u,MERGE_LWL},
        {0x80150404u,0x98a20000u,MERGE_LWR},
        {0x80150408u,0x88a30007u,MERGE_LWL},
        {0x8015040cu,0x98a30004u,MERGE_LWR},
        {0x80150410u,0xaa820003u,MERGE_SWL},
        {0x80150414u,0xba820000u,MERGE_SWR},
        {0x80150418u,0xaa830007u,MERGE_SWL},
        {0x8015041cu,0xba830004u,MERGE_SWR},
        {0x80163418u,0x89220003u,MERGE_LWL},
        {0x8016341cu,0x99220000u,MERGE_LWR},
        {0x80163420u,0x89230007u,MERGE_LWL},
        {0x80163424u,0x99230004u,MERGE_LWR},
        {0x80163428u,0xaba2001bu,MERGE_SWL},
        {0x8016342cu,0xbba20018u,MERGE_SWR},
        {0x80163430u,0xaba3001fu,MERGE_SWL},
        {0x80163434u,0xbba3001cu,MERGE_SWR},
        {0x801634ecu,0x89420003u,MERGE_LWL},
        {0x801634f0u,0x99420000u,MERGE_LWR},
        {0x801634f4u,0x89480007u,MERGE_LWL},
        {0x801634f8u,0x99480004u,MERGE_LWR},
        {0x801634fcu,0xaba2001bu,MERGE_SWL},
        {0x80163500u,0xbba20018u,MERGE_SWR},
        {0x80163504u,0xaba8001fu,MERGE_SWL},
        {0x80163508u,0xbba8001cu,MERGE_SWR},
        {0x8017237cu,0x88a20003u,MERGE_LWL},
        {0x80172380u,0x98a20000u,MERGE_LWR},
        {0x80172384u,0x88a30007u,MERGE_LWL},
        {0x80172388u,0x98a30004u,MERGE_LWR},
        {0x8017238cu,0xa8820093u,MERGE_SWL},
        {0x80172390u,0xb8820090u,MERGE_SWR},
        {0x80172394u,0xa8830097u,MERGE_SWL},
        {0x80172398u,0xb8830094u,MERGE_SWR},
        {0x8017239cu,0x88820093u,MERGE_LWL},
        {0x801723a0u,0x98820090u,MERGE_LWR},
        {0x801723a4u,0x88830097u,MERGE_LWL},
        {0x801723a8u,0x98830094u,MERGE_LWR},
        {0x801723acu,0xa882008bu,MERGE_SWL},
        {0x801723b0u,0xb8820088u,MERGE_SWR},
        {0x801723b4u,0xa883008fu,MERGE_SWL},
        {0x801723b8u,0xb883008cu,MERGE_SWR},
        {0x80172790u,0x88820003u,MERGE_LWL},
        {0x80172794u,0x98820000u,MERGE_LWR},
        {0x80172798u,0x88830007u,MERGE_LWL},
        {0x8017279cu,0x98830004u,MERGE_LWR},
        {0x801727a0u,0xa8c20003u,MERGE_SWL},
        {0x801727a4u,0xb8c20000u,MERGE_SWR},
        {0x801727a8u,0xa8c30007u,MERGE_SWL},
        {0x801727acu,0xb8c30004u,MERGE_SWR},
        {0x801728a4u,0x88820003u,MERGE_LWL},
        {0x801728a8u,0x98820000u,MERGE_LWR},
        {0x801728acu,0x88830007u,MERGE_LWL},
        {0x801728b0u,0x98830004u,MERGE_LWR},
        {0x801728b4u,0xa8c20003u,MERGE_SWL},
        {0x801728b8u,0xb8c20000u,MERGE_SWR},
        {0x801728bcu,0xa8c30007u,MERGE_SWL},
        {0x801728c0u,0xb8c30004u,MERGE_SWR},
        {0x80172c60u,0x88820003u,MERGE_LWL},
        {0x80172c64u,0x98820000u,MERGE_LWR},
        {0x80172c68u,0x88830007u,MERGE_LWL},
        {0x80172c6cu,0x98830004u,MERGE_LWR},
        {0x80172c70u,0xa8c20003u,MERGE_SWL},
        {0x80172c74u,0xb8c20000u,MERGE_SWR},
        {0x80172c78u,0xa8c30007u,MERGE_SWL},
        {0x80172c7cu,0xb8c30004u,MERGE_SWR},
        {0x80173418u,0x8a020003u,MERGE_LWL},
        {0x8017341cu,0x9a020000u,MERGE_LWR},
        {0x80173420u,0x8a030007u,MERGE_LWL},
        {0x80173424u,0x9a030004u,MERGE_LWR},
        {0x80173428u,0xa8a20003u,MERGE_SWL},
        {0x8017342cu,0xb8a20000u,MERGE_SWR},
        {0x80173430u,0xa8a30007u,MERGE_SWL},
        {0x80173434u,0xb8a30004u,MERGE_SWR},
        {0x8017347cu,0x8a020003u,MERGE_LWL},
        {0x80173480u,0x9a020000u,MERGE_LWR},
        {0x80173484u,0x8a030007u,MERGE_LWL},
        {0x80173488u,0x9a030004u,MERGE_LWR},
        {0x8017348cu,0xa8a20003u,MERGE_SWL},
        {0x80173490u,0xb8a20000u,MERGE_SWR},
        {0x80173494u,0xa8a30007u,MERGE_SWL},
        {0x80173498u,0xb8a30004u,MERGE_SWR},
        {0x80179480u,0x8ba2002bu,MERGE_LWL},
        {0x80179484u,0x9ba20028u,MERGE_LWR},
        {0x80179488u,0x8ba4002fu,MERGE_LWL},
        {0x8017948cu,0x9ba4002cu,MERGE_LWR},
        {0x80179490u,0xaa02000fu,MERGE_SWL},
        {0x80179494u,0xba02000cu,MERGE_SWR},
        {0x80179498u,0xaa040013u,MERGE_SWL},
        {0x8017949cu,0xba040010u,MERGE_SWR},
        {0x801794e0u,0x8ba2003bu,MERGE_LWL},
        {0x801794e4u,0x9ba20038u,MERGE_LWR},
        {0x801794e8u,0x8ba4003fu,MERGE_LWL},
        {0x801794ecu,0x9ba4003cu,MERGE_LWR},
        {0x801794f0u,0xaa02000fu,MERGE_SWL},
        {0x801794f4u,0xba02000cu,MERGE_SWR},
        {0x801794f8u,0xaa040013u,MERGE_SWL},
        {0x801794fcu,0xba040010u,MERGE_SWR},
        {0x8017b8f0u,0x88820003u,MERGE_LWL},
        {0x8017b8f4u,0x98820000u,MERGE_LWR},
        {0x8017b8f8u,0x88830007u,MERGE_LWL},
        {0x8017b8fcu,0x98830004u,MERGE_LWR},
        {0x8017b900u,0xa8c20003u,MERGE_SWL},
        {0x8017b904u,0xb8c20000u,MERGE_SWR},
        {0x8017b908u,0xa8c30007u,MERGE_SWL},
        {0x8017b90cu,0xb8c30004u,MERGE_SWR},
        {0x8017b918u,0x8882000bu,MERGE_LWL},
        {0x8017b91cu,0x98820008u,MERGE_LWR},
        {0x8017b920u,0x8883000fu,MERGE_LWL},
        {0x8017b924u,0x9883000cu,MERGE_LWR},
        {0x8017b928u,0xa8c20003u,MERGE_SWL},
        {0x8017b92cu,0xb8c20000u,MERGE_SWR},
        {0x8017b930u,0xa8c30007u,MERGE_SWL},
        {0x8017b934u,0xb8c30004u,MERGE_SWR},
        {0x8017c4ccu,0x88c20003u,MERGE_LWL},
        {0x8017c4d0u,0x98c20000u,MERGE_LWR},
        {0x8017c4d4u,0x88c30007u,MERGE_LWL},
        {0x8017c4d8u,0x98c30004u,MERGE_LWR},
        {0x8017c4dcu,0x88c4000bu,MERGE_LWL},
        {0x8017c4e0u,0x98c40008u,MERGE_LWR},
        {0x8017c4e4u,0x88c5000fu,MERGE_LWL},
        {0x8017c4e8u,0x98c5000cu,MERGE_LWR},
        {0x8017c4ecu,0xa8e20003u,MERGE_SWL},
        {0x8017c4f0u,0xb8e20000u,MERGE_SWR},
        {0x8017c4f4u,0xa8e30007u,MERGE_SWL},
        {0x8017c4f8u,0xb8e30004u,MERGE_SWR},
        {0x8017c4fcu,0xa8e4000bu,MERGE_SWL},
        {0x8017c500u,0xb8e40008u,MERGE_SWR},
        {0x8017c504u,0xa8e5000fu,MERGE_SWL},
        {0x8017c508u,0xb8e5000cu,MERGE_SWR},
        {0x8017c54cu,0x88c20003u,MERGE_LWL},
        {0x8017c550u,0x98c20000u,MERGE_LWR},
        {0x8017c554u,0x88c30007u,MERGE_LWL},
        {0x8017c558u,0x98c30004u,MERGE_LWR},
        {0x8017c55cu,0x88c4000bu,MERGE_LWL},
        {0x8017c560u,0x98c40008u,MERGE_LWR},
        {0x8017c564u,0xa8e20003u,MERGE_SWL},
        {0x8017c568u,0xb8e20000u,MERGE_SWR},
        {0x8017c56cu,0xa8e30007u,MERGE_SWL},
        {0x8017c570u,0xb8e30004u,MERGE_SWR},
        {0x8017c574u,0xa8e4000bu,MERGE_SWL},
        {0x8017c578u,0xb8e40008u,MERGE_SWR},
        {0x801814c0u,0x89829282u,MERGE_LWL},
        {0x80181b64u,0xb8adaeb7u,MERGE_SWR},
        {0x801826acu,0x8a620003u,MERGE_LWL},
        {0x801826b0u,0x9a620000u,MERGE_LWR},
        {0x801826b4u,0x8a630007u,MERGE_LWL},
        {0x801826b8u,0x9a630004u,MERGE_LWR},
        {0x801826bcu,0xaba20013u,MERGE_SWL},
        {0x801826c0u,0xbba20010u,MERGE_SWR},
        {0x801826c4u,0xaba30017u,MERGE_SWL},
        {0x801826c8u,0xbba30014u,MERGE_SWR},
        {0x80182884u,0x8a620003u,MERGE_LWL},
        {0x80182888u,0x9a620000u,MERGE_LWR},
        {0x8018288cu,0x8a630007u,MERGE_LWL},
        {0x80182890u,0x9a630004u,MERGE_LWR},
        {0x80182894u,0xaba20013u,MERGE_SWL},
        {0x80182898u,0xbba20010u,MERGE_SWR},
        {0x8018289cu,0xaba30017u,MERGE_SWL},
        {0x801828a0u,0xbba30014u,MERGE_SWR},
        {0x80183258u,0x98826482u,MERGE_LWR},
        {0x801832c0u,0x89826c82u,MERGE_LWL},
        {0x801832ecu,0x99828482u,MERGE_LWR},
        {0x80183348u,0x8b828382u,MERGE_LWL},
        {0x8018335cu,0x9a828982u,MERGE_LWR},
        {0x80183380u,0x88827282u,MERGE_LWL},
        {0x8018339cu,0x88829382u,MERGE_LWL},
        {0x801833a8u,0x89826f82u,MERGE_LWL},
        {0x801833b8u,0x8b827282u,MERGE_LWL},
        {0x801833c0u,0x89827682u,MERGE_LWL},
        {0x801833ccu,0x89826582u,MERGE_LWL},
        {0x80183410u,0x88828382u,MERGE_LWL},
        {0x80183444u,0x88827282u,MERGE_LWL},
        {0x801834a8u,0x89827582u,MERGE_LWL},
        {0x801834c8u,0x89826382u,MERGE_LWL},
        {0x80183570u,0x89827582u,MERGE_LWL},
        {0x801839b4u,0x89826c82u,MERGE_LWL},
        {0x801839c8u,0x99828482u,MERGE_LWR},
        {0x80183a10u,0x89828c82u,MERGE_LWL},
        {0x80183a2cu,0x89828d82u,MERGE_LWL},
        {0x80183a74u,0x89826582u,MERGE_LWL},
        {0x80183a90u,0x89827182u,MERGE_LWL},
        {0x80183aa4u,0x89829882u,MERGE_LWL},
        {0x80183ab4u,0x99829082u,MERGE_LWR},
        {0x80183ad4u,0x88827282u,MERGE_LWL},
        {0x80183ad8u,0x89829282u,MERGE_LWL},
        {0x80183adcu,0x8b828e82u,MERGE_LWL},
        {0x80183b08u,0x89826a82u,MERGE_LWL},
        {0x80183b0cu,0x8b828382u,MERGE_LWL},
        {0x80183b48u,0x89829482u,MERGE_LWL},
        {0x80183b5cu,0x89829482u,MERGE_LWL},
        {0x80183b68u,0x89826c82u,MERGE_LWL},
        {0x80183b88u,0x89829382u,MERGE_LWL},
        {0x80183e84u,0x89826582u,MERGE_LWL},
        {0x80183f04u,0x99828182u,MERGE_LWR},
        {0x80183f08u,0x89829482u,MERGE_LWL},
        {0x80183f74u,0x8b827282u,MERGE_LWL},
        {0x80183f7cu,0x88827382u,MERGE_LWL},
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == instruction) return sites[i].kind;
    return MERGE_NONE;
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
    /* Generated retire table, now data. See merge_retire_site above. */
    if (cpu->merge_kind == MERGE_LWR &&
            merge_retire_site(cpu->pc, instruction, cpu->merge_reg))
        return 1;
    /* func_801347A0's two LWL/LWR pairs: the first pair's LWR into v0 is
     * retired by the second pair's LWL into v1, and that pair's LWR into v1
     * by the first SWL. */

    /* Generated: an LWR retires when its successor is the next
     * LWL/SWL/SWR of the same copy block. */
    /* Resident-image interleaved copy blocks: the compiler emits
     * LWL/LWR pairs for two registers back to back and then their SWL/SWR
     * stores, so a pending LWR is retired by the next pair's LWL (or by the
     * first store). Every entry below is that instruction's exact word at
     * that PC in artifacts/sc02-resident-20260910. */
    /* Every retire site is one row of kMergeRetireSites. These were
     * separate `||` chains of the same three-field test; see the table. */
    if (cpu->merge_kind == MERGE_LWR &&
            merge_retire_site(cpu->pc, instruction, cpu->merge_reg))
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
    /* Judge availability with the same mapping the access itself uses. The
     * guest runs its kernel stack in the 1 KB scratchpad (sp=1f8003xx), which
     * musashi_boot_ram_span refuses but cpu_ram_span maps; MMIO still fails
     * closed here because cpu_ram_span does not map it. */
    return cpu_ram_span(memory, cpu, address & ~3u, 4u) != NULL;
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
    if (formatter_range_word(kFormatterRanges0,
            sizeof kFormatterRanges0 / sizeof kFormatterRanges0[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= CD_ENTER_CRITICAL && cpu->pc < CD_ENTER_CRITICAL + 16u)
        instruction = kSys1Words[(cpu->pc - CD_ENTER_CRITICAL) / 4u];
    else if (cpu->pc >= CALLBACK_EXIT_CRITICAL && cpu->pc < CALLBACK_EXIT_CRITICAL + 16u)
        instruction = kSys2Words[(cpu->pc - CALLBACK_EXIT_CRITICAL) / 4u];
    else if (formatter_range_word(kFormatterRanges1,
            sizeof kFormatterRanges1 / sizeof kFormatterRanges1[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
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
    else if (formatter_range_word(kFormatterRanges2,
            sizeof kFormatterRanges2 / sizeof kFormatterRanges2[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
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
    else if (formatter_range_word(kFormatterRanges3,
            sizeof kFormatterRanges3 / sizeof kFormatterRanges3[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
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
    else if (g_overlay_0004_words && formatter_range_word(kFormatterRanges4,
            sizeof kFormatterRanges4 / sizeof kFormatterRanges4[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (g_overlay_0010_words && formatter_range_word(kFormatterRanges5,
            sizeof kFormatterRanges5 / sizeof kFormatterRanges5[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges6,
            sizeof kFormatterRanges6 / sizeof kFormatterRanges6[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80129cf8u && cpu->pc < 0x80129ff4u)
        instruction = kOverlaySc02_80129CF8Words[(cpu->pc - 0x80129cf8u)/4u];
    else if (cpu->pc >= 0x8012a328u && cpu->pc < 0x8012a418u)
        instruction = kOverlaySc02_8012A328Words[(cpu->pc - 0x8012a328u)/4u];
    else if (g_overlay_0010_words && formatter_range_word(kFormatterRanges7,
            sizeof kFormatterRanges7 / sizeof kFormatterRanges7[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges8,
            sizeof kFormatterRanges8 / sizeof kFormatterRanges8[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8017849cu && cpu->pc < 0x80178608u)
        instruction = kOverlaySc02_8017849CWords[(cpu->pc - 0x8017849cu)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges9,
            sizeof kFormatterRanges9 / sizeof kFormatterRanges9[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x801627e8u && cpu->pc < 0x80162834u)
        instruction = kOverlaySc02_801627E8Words[(cpu->pc - 0x801627e8u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80162af4u && cpu->pc < 0x80162b1cu)
        instruction = kOverlaySc02_80162AF4Words[(cpu->pc - 0x80162af4u)/4u];
    else if (cpu->pc >= 0x80162b1cu && cpu->pc < 0x80162cc4u)
        instruction = kOverlaySc02_80162B1CWords[(cpu->pc - 0x80162b1cu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80165c78u && cpu->pc < 0x80165ca0u)
        instruction = kOverlaySc02_80165C78Words[(cpu->pc - 0x80165c78u)/4u];
    else if (cpu->pc >= 0x80165ca0u && cpu->pc < 0x80165e2cu)
        instruction = kOverlaySc02_80165CA0Words[(cpu->pc - 0x80165ca0u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges10,
            sizeof kFormatterRanges10 / sizeof kFormatterRanges10[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80129010u && cpu->pc < 0x801290dcu)
        instruction = kOverlaySc02_80129010Words[(cpu->pc - 0x80129010u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges11,
            sizeof kFormatterRanges11 / sizeof kFormatterRanges11[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8013ca14u && cpu->pc < 0x8013cabcu)
        instruction = kOverlaySc02_8013CA14Words[(cpu->pc - 0x8013ca14u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013d330u && cpu->pc < 0x8013d3d4u)
        instruction = kOverlaySc02_8013D330Words[(cpu->pc - 0x8013d330u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80164e40u && cpu->pc < 0x80164ea4u)
        instruction = kOverlaySc02_80164E40Words[(cpu->pc - 0x80164e40u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013cabcu && cpu->pc < 0x8013cae8u)
        instruction = kOverlaySc02_8013CABCWords[(cpu->pc - 0x8013cabcu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013cae8u && cpu->pc < 0x8013cb20u)
        instruction = kOverlaySc02_8013CAE8Words[(cpu->pc - 0x8013cae8u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013cb20u && cpu->pc < 0x8013cb5cu)
        instruction = kOverlaySc02_8013CB20Words[(cpu->pc - 0x8013cb20u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x8013cb5cu && cpu->pc < 0x8013cb84u)
        instruction = kOverlaySc02_8013CB5CWords[(cpu->pc - 0x8013cb5cu)/4u];
    else if (cpu->pc >= 0x8013cb84u && cpu->pc < 0x8013cf68u)
        instruction = kOverlaySc02_8013CB84Words[(cpu->pc - 0x8013cb84u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges12,
            sizeof kFormatterRanges12 / sizeof kFormatterRanges12[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8013bcdcu && cpu->pc < 0x8013bd34u)
        instruction = kOverlaySc02_8013BCDCWords[(cpu->pc - 0x8013bcdcu)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges13,
            sizeof kFormatterRanges13 / sizeof kFormatterRanges13[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80162968u && cpu->pc < 0x80162ac0u)
        instruction = kOverlaySc02_80162968Words[(cpu->pc - 0x80162968u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges14,
            sizeof kFormatterRanges14 / sizeof kFormatterRanges14[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80166054u && cpu->pc < 0x801661ccu)
        instruction = kOverlaySc02_80166054Words[(cpu->pc - 0x80166054u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges15,
            sizeof kFormatterRanges15 / sizeof kFormatterRanges15[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80175798u && cpu->pc < 0x801757a0u)
        instruction = kOverlaySc02_80175798Words[(cpu->pc - 0x80175798u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges16,
            sizeof kFormatterRanges16 / sizeof kFormatterRanges16[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80128ed8u && cpu->pc < 0x80128facu)
        instruction = kOverlaySc02_80128ED8Words[(cpu->pc - 0x80128ed8u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges17,
            sizeof kFormatterRanges17 / sizeof kFormatterRanges17[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8012a988u && cpu->pc < 0x8012aaacu)
        instruction = kOverlaySc02_8012A988Words[(cpu->pc - 0x8012a988u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges18,
            sizeof kFormatterRanges18 / sizeof kFormatterRanges18[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x801379fcu && cpu->pc < 0x80137b80u)
        instruction = kOverlaySc02_801379FCWords[(cpu->pc - 0x801379fcu)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges19,
            sizeof kFormatterRanges19 / sizeof kFormatterRanges19[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8013a380u && cpu->pc < 0x8013a448u)
        instruction = kOverlaySc02_8013A380Words[(cpu->pc - 0x8013a380u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges20,
            sizeof kFormatterRanges20 / sizeof kFormatterRanges20[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x801816c0u && cpu->pc < 0x80181868u)
        instruction = kOverlaySc02_801816C0Words[(cpu->pc - 0x801816c0u)/4u];
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
    else if (cpu->pc >= 0x8017f53cu && cpu->pc < 0x8017f590u)
        instruction = kOverlaySc02_8017F53CWords[(cpu->pc - 0x8017f53cu)/4u];
    else if (cpu->pc >= 0x8017f590u && cpu->pc < 0x8017f5b4u)
        instruction = kOverlaySc02_8017F590Words[(cpu->pc - 0x8017f590u)/4u];
    else if (cpu->pc >= 0x8017f5b4u && cpu->pc < 0x80180d50u)
        instruction = kOverlaySc02_8017F5B4Words[(cpu->pc - 0x8017f5b4u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges21,
            sizeof kFormatterRanges21 / sizeof kFormatterRanges21[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x80181a44u && cpu->pc < 0x80181ae0u)
        instruction = kOverlaySc02_80181A44Words[(cpu->pc - 0x80181a44u)/4u];
    else if (cpu->pc >= 0x80181ae0u && cpu->pc < 0x80181b78u)
        instruction = kOverlaySc02_80181AE0Words[(cpu->pc - 0x80181ae0u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges22,
            sizeof kFormatterRanges22 / sizeof kFormatterRanges22[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (formatter_range_word(kFormatterRanges23,
            sizeof kFormatterRanges23 / sizeof kFormatterRanges23[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c890u && cpu->pc < 0x8012cae4u)
        instruction = kOverlaySc02_8012C890Words[(cpu->pc - 0x8012c890u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012c750u && cpu->pc < 0x8012c820u)
        instruction = kOverlaySc02_8012C750Words[(cpu->pc - 0x8012c750u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8013e4b4u && cpu->pc < 0x8013e558u)
        instruction = kOverlaySc02_8013E4B4Words[(cpu->pc - 0x8013e4b4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80178608u && cpu->pc < 0x8017869cu)
        instruction = kOverlaySc02_80178608Words[(cpu->pc - 0x80178608u)/4u];
    else if (cpu->pc >= 0x8017869cu && cpu->pc < 0x80178744u)
        instruction = kOverlaySc02_8017869CWords[(cpu->pc - 0x8017869cu)/4u];
    else if (cpu->pc >= 0x80178b18u && cpu->pc < 0x80178b70u)
        instruction = kOverlaySc02_80178B18Words[(cpu->pc - 0x80178b18u)/4u];
    else if (cpu->pc >= 0x80178bf8u && cpu->pc < 0x80178cbcu)
        instruction = kOverlaySc02_80178BF8Words[(cpu->pc - 0x80178bf8u)/4u];
    else if (cpu->pc >= 0x80178d40u && cpu->pc < 0x80179b28u)
        instruction = kOverlaySc02_80178D40Words[(cpu->pc - 0x80178d40u)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges24,
            sizeof kFormatterRanges24 / sizeof kFormatterRanges24[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x801754a8u && cpu->pc < 0x8017553cu)
        instruction = kOverlaySc02_801754A8Words[(cpu->pc - 0x801754a8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8016e8f0u && cpu->pc < 0x8016e918u)
        instruction = kOverlaySc02_8016E8F0Words[(cpu->pc - 0x8016e8f0u)/4u];
    else if (cpu->pc >= 0x8016e95cu && cpu->pc < 0x8016e9ecu)
        instruction = kOverlaySc02_8016E95CWords[(cpu->pc - 0x8016e95cu)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges25,
            sizeof kFormatterRanges25 / sizeof kFormatterRanges25[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (cpu->pc >= 0x8013b598u && cpu->pc < 0x8013b6a0u)
        instruction = kOverlaySc02_8013B598Words[(cpu->pc - 0x8013b598u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x80136bc4u && cpu->pc < 0x80136c1cu)
        instruction = kOverlaySc02_80136BC4Words[(cpu->pc - 0x80136bc4u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x801336e8u && cpu->pc < 0x8013373cu)
        instruction = kOverlaySc02_801336E8Words[(cpu->pc - 0x801336e8u)/4u];
    else if (g_overlay_sc02_0031_words && cpu->pc >= 0x8012944cu && cpu->pc < 0x8012956cu)
        instruction = kOverlaySc02_8012944CWords[(cpu->pc - 0x8012944cu)/4u];
    else if (cpu->pc >= 0x8012956cu && cpu->pc < 0x801298f4u)
        instruction = kOverlaySc02_8012956CWords[(cpu->pc - 0x8012956cu)/4u];
    else if (g_overlay_sc02_0031_words && formatter_range_word(kFormatterRanges26,
            sizeof kFormatterRanges26 / sizeof kFormatterRanges26[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
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
    else if (cpu->pc >= 0x8017c180u && cpu->pc < 0x8017c2b0u)
        instruction = kOverlaySc02_8017C180Words[(cpu->pc - 0x8017c180u)/4u];
    else if (g_overlay_0007_words &&
             cpu->pc >= 0x800cee2cu && cpu->pc < 0x800cf02cu)
        instruction = kOverlay800CEE2CWords[(cpu->pc - 0x800cee2cu) / 4u];
    else if (g_overlay_0007_words &&
             cpu->pc >= 0x800cf02cu && cpu->pc < 0x800d1378u)
        instruction = kOverlay800CF02CWords[(cpu->pc - 0x800cf02cu) / 4u];
    else if (formatter_range_word(kFormatterRanges27,
            sizeof kFormatterRanges27 / sizeof kFormatterRanges27[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800cefd0u && cpu->pc < 0x800cf104u)
        instruction = kOverlay0010_800CEFD0Words[(cpu->pc - 0x800cefd0u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d20c0u && cpu->pc < 0x800d21c4u)
        instruction = kOverlay0010_800D20C0Words[(cpu->pc - 0x800d20c0u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d21c4u && cpu->pc < 0x800d222cu)
        instruction = kOverlay0010_800D21C4Words[(cpu->pc - 0x800d21c4u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d22e4u && cpu->pc < 0x800d2318u)
        instruction = kOverlay0010_800D22E4Words[(cpu->pc - 0x800d22e4u)/4u];
    else if (g_overlay_0010_words &&
             cpu->pc >= 0x800d23d0u && cpu->pc < 0x800d2460u)
        instruction = kOverlay0010_800D23D0Words[(cpu->pc - 0x800d23d0u)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80167dbcu && cpu->pc < 0x80168070u)
        instruction = kOverlaySc02_80167DBCWords[(cpu->pc - 0x80167dbcu)/4u];
    else if (g_overlay_sc02_0031_words &&
             cpu->pc >= 0x80168070u && cpu->pc < 0x801681fcu)
        instruction = kOverlaySc02_80168070Words[(cpu->pc - 0x80168070u)/4u];
    /* A selected overlay must never fetch member-zero words. */
    else if (g_overlay_0004_words || g_overlay_0007_words || g_overlay_0010_words)
        return 0;
    else if (formatter_range_word(kFormatterRanges28,
            sizeof kFormatterRanges28 / sizeof kFormatterRanges28[0], cpu->pc,
            &instruction)) {
        /* value written by formatter_range_word */
    }
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
        {10, 0x8004862cu, 0x010b4021u},
        {12, 0x80012608u, 0x480d5000u},
        {13, 0x8001260cu, 0x480e5800u},
        {14, 0x80012610u, 0xa62c0000u},
        {12, 0x8001264cu, 0x480d5000u},
        {13, 0x80012650u, 0x480e5800u},
        {14, 0x80012654u, 0xa44c0000u},
        {12, 0x80012690u, 0x480d5000u},
        {13, 0x80012694u, 0x480e5800u},
        {14, 0x80012698u, 0xa44c0000u}
        ,{2, 0x80049450u, 0x03e00008u}
        ,{11, 0x80047ee0u, 0x480cd000u}
        ,{12, 0x80047ee4u, 0x480dd800u}
        ,{13, 0x80047ee8u, 0x016c5820u}
        ,{3, 0x80047f00u, 0x2401fffeu}
        ,{8, 0x80047f68u, 0x4809d000u}
        ,{9, 0x80047f6cu, 0x480ad800u}
        ,{10, 0x80047f70u, 0x01c84007u}
        /* func_800126C4's three MFC2 chains, same shape as func_80012558. */
        ,{12, 0x80012770u, 0x480d5000u}
        ,{13, 0x80012774u, 0x480e5800u}
        ,{14, 0x80012778u, 0xa62c0000u}
        ,{12, 0x800127b4u, 0x480d5000u}
        ,{13, 0x800127b8u, 0x480e5800u}
        ,{14, 0x800127bcu, 0xa44c0000u}
        ,{12, 0x800127f8u, 0x480d5000u}
        ,{13, 0x800127fcu, 0x480e5800u}
        ,{14, 0x80012800u, 0xa44c0000u}
        /* func_800123F0's three MFC2 chains. */
        ,{12, 0x8001249cu, 0x480d5000u}
        ,{13, 0x800124a0u, 0x480e5800u}
        ,{14, 0x800124a4u, 0xa62c0000u}
        ,{12, 0x800124e0u, 0x480d5000u}
        ,{13, 0x800124e4u, 0x480e5800u}
        ,{14, 0x800124e8u, 0xa44c0000u}
        ,{12, 0x80012524u, 0x480d5000u}
        ,{13, 0x80012528u, 0x480e5800u}
        ,{14, 0x8001252cu, 0xa44c0000u}
        /* func_80048FBC's three MFC2 reads of IR1..3. */
        ,{8, 0x80048ff8u, 0x48095000u}
        ,{9, 0x80048ffcu, 0x480a5800u}
        ,{10, 0x80049000u, 0xa4c80000u}
        /* func_80048EAC's three MFC2 read trios. */
        ,{11, 0x80048f14u, 0x480c5000u}
        ,{12, 0x80048f18u, 0x480d5800u}
        ,{13, 0x80048f1cu, 0x48880000u}
        ,{14, 0x80048f48u, 0x480f5000u}
        ,{15, 0x80048f4cu, 0x48185800u}
        ,{24, 0x80048f50u, 0x48880000u}
        ,{8, 0x80048f84u, 0x48095000u}
        ,{9, 0x80048f88u, 0x3108ffffu}
        /* func_8004D504's two MFC2 read trios. */
        ,{11, 0x8004d610u, 0x480cd000u}
        ,{12, 0x8004d614u, 0x480dd800u}
        ,{13, 0x8004d618u, 0x3108ffffu}
        ,{8, 0x8004d68cu, 0x4809d000u}
        ,{9, 0x8004d690u, 0x480ad800u}
        ,{10, 0x8004d694u, 0x010b4021u}
        /* func_80048B6C's two MFC2 read trios. */
        ,{11, 0x80048c08u, 0x480cd000u}
        ,{12, 0x80048c0cu, 0x480dd800u}
        ,{13, 0x80048c10u, 0x48884800u}
        ,{8, 0x80048c7cu, 0x4809d000u}
        ,{9, 0x80048c80u, 0x480ad800u}
        ,{10, 0x80048c84u, 0x010b4021u}
        ,{12, 0x80020f74u, 0x480d5000u}
        ,{13, 0x80020f78u, 0x480e5800u}
        ,{14, 0x80020f7cu, 0xa48c0000u}
        ,{12, 0x80020fb8u, 0x480d5000u}
        ,{13, 0x80020fbcu, 0x480e5800u}
        ,{14, 0x80020fc0u, 0xa48c0002u}
        ,{12, 0x80020fecu, 0x480d5000u}
        ,{13, 0x80020ff0u, 0x480e5800u}
        ,{14, 0x80020ff4u, 0xa48c0004u}
        ,{12, 0x8012edc0u, 0x480d5000u}
        ,{13, 0x8012edc4u, 0x480e5800u}
        ,{14, 0x8012edc8u, 0xa64c0000u}
        ,{12, 0x8012ee00u, 0x480d5000u}
        ,{13, 0x8012ee04u, 0x480e5800u}
        ,{14, 0x8012ee08u, 0xa44c0000u}
        ,{12, 0x8012ee40u, 0x480d5000u}
        ,{13, 0x8012ee44u, 0x480e5800u}
        ,{14, 0x8012ee48u, 0xa44c0000u}
        ,{12, 0x8012ef8cu, 0x00000000u}
        ,{12, 0x8012f020u, 0x00000000u}
        ,{12, 0x80132a74u, 0x480d5000u}
        ,{13, 0x80132a78u, 0x480e5800u}
        ,{14, 0x80132a7cu, 0xa64c0000u}
        ,{12, 0x80132ab8u, 0x480d5000u}
        ,{13, 0x80132abcu, 0x480e5800u}
        ,{14, 0x80132ac0u, 0xa44c0000u}
        ,{12, 0x80132afcu, 0x480d5000u}
        ,{13, 0x80132b00u, 0x480e5800u}
        ,{14, 0x80132b04u, 0xa44c0000u}
        ,{12, 0x80132c20u, 0x480d5000u}
        ,{13, 0x80132c24u, 0x480e5800u}
        ,{14, 0x80132c28u, 0xa62c0000u}
        ,{12, 0x80132c60u, 0x480d5000u}
        ,{13, 0x80132c64u, 0x480e5800u}
        ,{14, 0x80132c68u, 0xa44c0000u}
        ,{12, 0x80132ca0u, 0x480d5000u}
        ,{13, 0x80132ca4u, 0x480e5800u}
        ,{14, 0x80132ca8u, 0xa44c0000u}
        ,{12, 0x80133164u, 0x00000000u}
        ,{11, 0x800483f4u, 0x480c5000u}
        ,{12, 0x800483f8u, 0x480d5800u}
        ,{13, 0x800483fcu, 0x48880000u}
        ,{14, 0x80048428u, 0x480f5000u}
        ,{15, 0x8004842cu, 0x48185800u}
        ,{24, 0x80048430u, 0x48880000u}
        ,{8, 0x80048464u, 0x48095000u}
        ,{9, 0x80048468u, 0xe8cb0010u}
        ,{8, 0x800484b4u, 0x4809d000u}
        ,{9, 0x800484b8u, 0x480ad800u}
        ,{10, 0x800484bcu, 0x8c8b0014u}
        ,{3, 0x80049658u, 0xc8e00000u}
        ,{8, 0x80049680u, 0x48029800u}
        ,{2, 0x80049684u, 0x01034025u}
        ,{19, 0x80182f74u, 0x1443000au}
        ,{19, 0x80182f74u, 0x44415749u}
        ,{2, 0x800491f0u, 0x03e00008u}
        ,{12, 0x8017f8c4u, 0x00000000u}
        ,{12, 0x8017f8c4u, 0x01a00260u}
        ,{12, 0x8017fc34u, 0x00000000u}
        ,{12, 0x8017fc34u, 0x000000c2u}
        ,{12, 0x80180484u, 0x00000000u}
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
           ra == 0x80053bbcu || ra == 0x80054138u || ra == 0x800541ecu ||
           /* The two JAL sites inside the exported func_80054DCC range. */
           ra == 0x80055070u || ra == 0x80055284u ||
           /* SC02 member31 calls func_80048FBC, whose control/bank sites
            * carry that caller's return alias. */
           (g_overlay_sc02_0031_words && ra == 0x8017c248u);
}

static int gte_47d3c_caller(uint32_t ra) {
    /* 0x801338A4 is func_80133784's return alias: the SC02_031 function is
     * carved from the resident image and oracle-verified byte-for-byte, and its
     * 0x8013389C jal 0x80047D3C with an addu delay slot is the same call shape
     * as the three main-executable callers. Everything else in this gate
     * (transfer binding, no pending merge, npc/delay/branch state) still
     * applies. */
    return ra == 0x80054050u || ra == 0x800540d8u || ra == 0x800533e4u ||
           ra == 0x801338a4u ||
           /* The five JAL sites inside the exported func_80054DCC range
            * [80054DCC,800553D8) call the same leaf. */
           ra == 0x80054eccu || ra == 0x80054fd8u || ra == 0x80054fe4u ||
           ra == 0x800550b0u || ra == 0x800551a0u ||
           /* The JAL site inside the exported func_80013294 range. */
           ra == 0x800132acu ||
           /* The remaining JAL sites into this leaf (80013218, 80013340,
            * 800133D4, 80013468, 8002C7A4); each is an exact return alias
            * taken from the retail image. */
           ra == 0x80013218u || ra == 0x80013340u || ra == 0x800133d4u ||
           ra == 0x80013468u || ra == 0x8002c7a4u ||
           /* SC02 member31 JAL return aliases into this leaf. */
           (g_overlay_sc02_0031_words &&
            (ra == 0x8012a720u || ra == 0x80148894u || ra == 0x8014c66cu ||
             ra == 0x801629ccu || ra == 0x801646d4u)) ||
           /* MAIN.CD member 0010 callers of the same leaf. */
           (g_overlay_0010_words &&
            (ra == 0x800d2384u || ra == 0x800d2418u));
}

/* func_80012558 is a PSY-Q GTE library routine (26 COP2 sites: CTC2 control
 * 0..4, MTC2 data 9..11, the 4A49E012 command, MFC2 data 9..11) that the guest
 * reaches by fall-through, so RA is stale and cannot gate it. Slots:
 * 0 = control write, 1 = data read, 3 = data write, 4 = command. */

/* Shared (pc, word) site lookup for the GTE bank helpers.
 *
 * Eight of these tables used to carry their own copy of the scan. With the
 * element count visible as a constant, GCC unrolls the loop and its
 * dominator pass explores the unrolled paths: on gte_4d504_site alone that
 * cost 13.8 of this file's 14 seconds of compile time, measured with -Q,
 * and the whole file dropped to 2.2s under -fno-tree-dominator-opts. That
 * matters because 83 tests in the suite give `cc` a 30-second budget and
 * the file already timed out under load.
 *
 * Taking the count as a parameter leaves one small loop in the translation
 * unit instead of eight unrollable ones. The lookup is unchanged: first
 * entry whose pc and word both match, slot written only on a hit, and slot
 * may be null.
 */
typedef struct {
    uint32_t pc;
    uint32_t word;
    uint8_t slot;
} GteSite;

MUSASHI_FORMATTER_NOINLINE static int gte_site_lookup(const GteSite *sites, size_t count,
                           uint32_t pc, uint32_t word, unsigned *slot) {
    size_t index;

    for (index = 0; index < count; ++index) {
        if (sites[index].pc != pc || sites[index].word != word) {
            continue;
        }
        if (slot != NULL) {
            *slot = sites[index].slot;
        }
        return 1;
    }
    return 0;
}

static int gte_12558_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x800125bcu,0x48cc0000u,0}, {0x800125c0u,0x48cd0800u,0},
        {0x800125d0u,0x48cc1000u,0}, {0x800125d4u,0x48cd1800u,0},
        {0x800125d8u,0x48ce2000u,0},
        {0x800125ecu,0x488c4800u,3}, {0x800125f0u,0x488d5000u,3},
        {0x800125f4u,0x488e5800u,3},
        {0x80012600u,0x4a49e012u,4},
        {0x80012604u,0x480c4800u,1}, {0x80012608u,0x480d5000u,1},
        {0x8001260cu,0x480e5800u,1},
        {0x8001262cu,0x488c4800u,3}, {0x80012630u,0x488d5000u,3},
        {0x80012634u,0x488e5800u,3},
        {0x80012640u,0x4a49e012u,4},
        {0x80012648u,0x480c4800u,1}, {0x8001264cu,0x480d5000u,1},
        {0x80012650u,0x480e5800u,1},
        {0x80012670u,0x488c4800u,3}, {0x80012674u,0x488d5000u,3},
        {0x80012678u,0x488e5800u,3},
        {0x80012684u,0x4a49e012u,4},
        {0x8001268cu,0x480c4800u,1}, {0x80012690u,0x480d5000u,1},
        {0x80012694u,0x480e5800u,1}
        ,{0x80047ec8u,0x48884800u,3u}
        ,{0x80047eccu,0x48895000u,3u}
        ,{0x80047ed0u,0x488a5800u,3u}
        ,{0x80047ed8u,0x4aa00428u,4u}
        ,{0x80047edcu,0x480bc800u,1u}
        ,{0x80047ee0u,0x480cd000u,1u}
        ,{0x80047ee4u,0x480dd800u,1u}
        ,{0x80047ef0u,0x4882f000u,3u}
        ,{0x80047efcu,0x4803f800u,1u}
        ,{0x80047f48u,0x488d4000u,3u}
        ,{0x80047f4cu,0x48884800u,3u}
        ,{0x80047f50u,0x48895000u,3u}
        ,{0x80047f54u,0x488a5800u,3u}
        ,{0x80047f60u,0x4b90003du,4u}
        ,{0x80047f64u,0x4808c800u,1u}
        ,{0x80047f68u,0x4809d000u,1u}
        ,{0x80047f6cu,0x480ad800u,1u}
        /* func_800126C4 is the second PSY-Q GTE helper of this shape. It
         * overwrites RA with its own internal 80047948 jal (return alias
         * 800126F0) before every COP2 site, so it is admitted by exact
         * PC/word like func_80012558 rather than by caller. */
        ,{0x80012724u,0x48cc0000u,0u}
        ,{0x80012728u,0x48cd0800u,0u}
        ,{0x80012738u,0x48cc1000u,0u}
        ,{0x8001273cu,0x48cd1800u,0u}
        ,{0x80012740u,0x48ce2000u,0u}
        ,{0x80012754u,0x488c4800u,3u}
        ,{0x80012758u,0x488d5000u,3u}
        ,{0x8001275cu,0x488e5800u,3u}
        ,{0x80012768u,0x4a49e012u,4u}
        ,{0x8001276cu,0x480c4800u,1u}
        ,{0x80012770u,0x480d5000u,1u}
        ,{0x80012774u,0x480e5800u,1u}
        ,{0x80012794u,0x488c4800u,3u}
        ,{0x80012798u,0x488d5000u,3u}
        ,{0x8001279cu,0x488e5800u,3u}
        ,{0x800127a8u,0x4a49e012u,4u}
        ,{0x800127b0u,0x480c4800u,1u}
        ,{0x800127b4u,0x480d5000u,1u}
        ,{0x800127b8u,0x480e5800u,1u}
        ,{0x800127d8u,0x488c4800u,3u}
        ,{0x800127dcu,0x488d5000u,3u}
        ,{0x800127e0u,0x488e5800u,3u}
        ,{0x800127ecu,0x4a49e012u,4u}
        ,{0x800127f4u,0x480c4800u,1u}
        ,{0x800127f8u,0x480d5000u,1u}
        ,{0x800127fcu,0x480e5800u,1u}
        /* func_800123F0 is the same helper one slot earlier in the same
         * PSY-Q GTE bank (its 80047948 return alias is 8001241C). */
        ,{0x80012450u,0x48cc0000u,0u}
        ,{0x80012454u,0x48cd0800u,0u}
        ,{0x80012464u,0x48cc1000u,0u}
        ,{0x80012468u,0x48cd1800u,0u}
        ,{0x8001246cu,0x48ce2000u,0u}
        ,{0x80012480u,0x488c4800u,3u}
        ,{0x80012484u,0x488d5000u,3u}
        ,{0x80012488u,0x488e5800u,3u}
        ,{0x80012494u,0x4a49e012u,4u}
        ,{0x80012498u,0x480c4800u,1u}
        ,{0x8001249cu,0x480d5000u,1u}
        ,{0x800124a0u,0x480e5800u,1u}
        ,{0x800124c0u,0x488c4800u,3u}
        ,{0x800124c4u,0x488d5000u,3u}
        ,{0x800124c8u,0x488e5800u,3u}
        ,{0x800124d4u,0x4a49e012u,4u}
        ,{0x800124dcu,0x480c4800u,1u}
        ,{0x800124e0u,0x480d5000u,1u}
        ,{0x800124e4u,0x480e5800u,1u}
        ,{0x80012504u,0x488c4800u,3u}
        ,{0x80012508u,0x488d5000u,3u}
        ,{0x8001250cu,0x488e5800u,3u}
        ,{0x80012518u,0x4a49e012u,4u}
        ,{0x80012520u,0x480c4800u,1u}
        ,{0x80012524u,0x480d5000u,1u}
        ,{0x80012528u,0x480e5800u,1u}
        /* func_80048FBC is the exported 24-word matrix/vector leaf: five CTC2
         * control writes (rotation 0..4), two LWC2 loads of the V0 vector,
         * the 4A486012 MVMVA, three MFC2 reads of IR1..3, and the halfword
         * stores of the transformed result. Same slot convention. */
        ,{0x80048fd0u,0x48c80000u,0u}
        ,{0x80048fd4u,0x48c90800u,0u}
        ,{0x80048fd8u,0x48ca1000u,0u}
        ,{0x80048fdcu,0x48cb1800u,0u}
        ,{0x80048fe0u,0x48cc2000u,0u}
        ,{0x80048fe4u,0xc8a00000u,3u}
        ,{0x80048fe8u,0xc8a10004u,3u}
        ,{0x80048ff0u,0x4a486012u,4u}
        ,{0x80048ff4u,0x48084800u,1u}
        ,{0x80048ff8u,0x48095000u,1u}
        ,{0x80048ffcu,0x480a5800u,1u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

/* True when the instruction is one of the library routine's COP2 commands. */
static int gte_lib_command_site(uint32_t pc, uint32_t word) {
    unsigned slot = 99;
    return gte_12558_site(pc, word, &slot) && slot == 4u;
}

/* func_80047EC8 is the exported 188-byte GTE normalisation leaf: it reads
 * LZCR through MFC2, turns the count into a shift, picks a signed halfword
 * from 8007DA80, writes IR0/IR1/IR2/IR3 and closes with GPF. Its words are
 * exported and match_function-verified, and the five retail JAL sites in the
 * EXE text (return aliases 80047E84, 80047EB4, 80048018, 80048038, 80048054)
 * are its only callers. Only that leaf's integer arithmetic is admitted
 * here: the two signed SUBs and the four SRAVs. SUB keeps its signed overflow
 * trap and SRAV shifts by the low five bits of the source register. */
static int gte_47ec8_integer_caller(uint32_t ra) {
    return ra == 0x80047e84u || ra == 0x80047eb4u || ra == 0x80048018u ||
           ra == 0x80048038u || ra == 0x80048054u;
}

static int gte_47ec8_sub_site(uint32_t pc, uint32_t word) {
    return (pc == 0x80047f0cu && word == 0x01c37022u) ||
           (pc == 0x80047f28u && word == 0x01635822u);
}

static int gte_47ec8_srav_site(uint32_t pc, uint32_t word) {
    return (pc == 0x80047f2cu && word == 0x01626007u) ||
           (pc == 0x80047f70u && word == 0x01c84007u) ||
           (pc == 0x80047f74u && word == 0x01c94807u) ||
           (pc == 0x80047f78u && word == 0x01ca5007u);
}

/* func_800479E8 is the exported camera fixed-point stepper [800479E8,
 * 80047B3C). Its four SRAVs divide the running accumulators by the step
 * shift in $a3; both retail callers are JAL sites in the next camera leaf
 * (return aliases 80047BA8 and 80047BBC), so the site and the caller are
 * both pinned here. */
static int gte_47a2c_srav_site(uint32_t pc, uint32_t word, uint32_t ra) {
    if (ra != 0x80047ba8u && ra != 0x80047bbcu) return 0;
    return (pc == 0x80047a2cu && word == 0x00e31807u) ||
           (pc == 0x80047a48u && word == 0x00e21007u) ||
           (pc == 0x80047a58u && word == 0x00e31807u) ||
           (pc == 0x80047a74u && word == 0x00e21007u);
}

/* func_80047B3C's two SRAVs. Both sit after one of its own internal calls
 * (80049440 and 800479E8), so each carries that call's fixed return alias
 * rather than a caller alias. */
static int gte_47b3c_srav_site(uint32_t pc, uint32_t word, uint32_t ra) {
    return (pc == 0x80047b7cu && word == 0x00512007u && ra == 0x80047b64u) ||
           (pc == 0x80047bb0u && word == 0x00621007u && ra == 0x80047ba8u);
}

/* SRAV sites elsewhere inside exported, word-verified main-exec ranges. Every
 * entry is an exact (pc, word) pair from the retail image: the pc proves the
 * site lies in a range the native seam exports, and the word pins the operands
 * (including the shift source). A shift is defined for every value, so the
 * count is simply the low five bits of the source register. */
static int gte_exported_srav_site(uint32_t pc, uint32_t word) {
    static const struct { uint32_t pc, word; } sites[] = {
        {0x80012988u, 0x02021007u},
        {0x80012994u, 0x02031807u},
        {0x8001299cu, 0x02021007u},
        {0x8003d080u, 0x00821007u},
        {0x80041f10u, 0x00648807u},
        {0x80047a2cu, 0x00e31807u},
        {0x80047a48u, 0x00e21007u},
        {0x80047a58u, 0x00e31807u},
        {0x80047a74u, 0x00e21007u},
        {0x80047b7cu, 0x00512007u},
        {0x80047bb0u, 0x00621007u},
        {0x80047d8cu, 0x01646007u},
        {0x80047f2cu, 0x01626007u},
        {0x80047f70u, 0x01c84007u},
        {0x80047f74u, 0x01c94807u},
        {0x80047f78u, 0x01ca5007u},
        {0x8005437cu, 0x00621007u},
        {0x8005438cu, 0x00621007u},
        {0x8005439cu, 0x00621007u},
        {0x800543acu, 0x00621007u},
        {0x800543bcu, 0x00621007u},
        {0x800543ccu, 0x00621007u},
        {0x800d2074u, 0x00821007u},
        {0x800d2088u, 0x00821007u},
        {0x800d209cu, 0x00821007u},
        {0x800d2174u, 0x00821007u},
        {0x800d2188u, 0x00821007u},
        {0x800d219cu, 0x00821007u},
        {0x800d25b8u, 0x00000ec7u},
        {0x800d34d8u, 0x00061087u},
        {0x8017e614u, 0x00000047u},
        {0x8017ff74u, 0x00003087u},
        {0x801802b8u, 0x00000007u},
        {0x80180524u, 0x00070007u},
        {0x80181778u, 0x00003087u},
        {0x80181bbcu, 0x00000007u},
        {0x80181c0cu, 0x00000007u},
        {0x80181ef4u, 0x000c0047u},
        {0x80181f00u, 0x000c0047u},
        {0x80181f58u, 0x000c0047u},
        {0x80181f64u, 0x000c0047u},
        {0x8018205cu, 0x000c0047u},
        {0x80182068u, 0x000c0047u},
        {0x80182308u, 0x000c0007u},
        {0x801823bcu, 0x00120007u},
        {0x801823c8u, 0x00660007u},
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == word) return 1;
    return 0;
}

/* func_80049324 is the exported ten-word GTE vector leaf [80049324,8004934C):
 * three LWC2 loads carry a 12-byte vector into IR1..IR3, the 4AA00428 MVMVA
 * transforms it, and three SWC2 stores publish MAC1..MAC3. Its five retail
 * callers are JAL sites (return aliases 80013274, 80013308, 8001339C,
 * 80013430, 8002C710). Slots: 0 = data write, 1 = command, 2 = data read. */
static int gte_49324_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80049324u, 0xc8890000u, 0u}, {0x80049328u, 0xc88a0004u, 0u},
        {0x8004932cu, 0xc88b0008u, 0u}, {0x80049334u, 0x4aa00428u, 1u},
        {0x80049338u, 0xe8b90000u, 2u}, {0x8004933cu, 0xe8ba0004u, 2u},
        {0x80049340u, 0xe8bb0008u, 2u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

static int gte_49324_caller(uint32_t ra) {
    return ra == 0x80013274u || ra == 0x80013308u || ra == 0x8001339cu ||
           ra == 0x80013430u || ra == 0x8002c710u;
}

/* func_80048EAC is the second exported main-exec GTE bank routine
 * [80048EAC,80048FB8): five CTC2 control writes, then three rounds of an MTC2
 * pair, the 4A486012 MVMVA and an MFC2 read trio. Its callers are the audited
 * 80048D9C family, so the site is pinned by exact PC/word and the caller
 * alias. Slots match gte_48d9c_site: 0 = control write, 1 = data read,
 * 3 = data write, 4 = command. */
static int gte_48eac_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80048ec0u,0x48c80000u,0u}, {0x80048ec4u,0x48c90800u,0u},
        {0x80048ec8u,0x48ca1000u,0u}, {0x80048eccu,0x48cb1800u,0u},
        {0x80048ed0u,0x48cc2000u,0u},
        {0x80048eecu,0x48880000u,3u}, {0x80048ef0u,0x488a0800u,3u},
        {0x80048ef8u,0x4a486012u,4u},
        {0x80048f10u,0x480b4800u,1u}, {0x80048f14u,0x480c5000u,1u},
        {0x80048f18u,0x480d5800u,1u},
        {0x80048f1cu,0x48880000u,3u}, {0x80048f20u,0x488a0800u,3u},
        {0x80048f28u,0x4a486012u,4u},
        {0x80048f44u,0x480e4800u,1u}, {0x80048f48u,0x480f5000u,1u},
        {0x80048f4cu,0x48185800u,1u},
        {0x80048f50u,0x48880000u,3u}, {0x80048f54u,0x488a0800u,3u},
        {0x80048f5cu,0x4a486012u,4u},
        {0x80048f80u,0x48084800u,1u}, {0x80048f84u,0x48095000u,1u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

/* The retail call sites of func_80048EAC: five JAL sites in the executable
 * plus the member-0031 sites in the resident image. */
static int gte_48eac_caller(uint32_t ra) {
    return ra == 0x80017e1cu || ra == 0x80017e54u || ra == 0x8002c530u ||
           ra == 0x80052f20u || ra == 0x80052ffcu ||
           (g_overlay_sc02_0031_words &&
            (ra == 0x80135670u || ra == 0x80167434u || ra == 0x801679ecu ||
             ra == 0x80168704u || ra == 0x80168954u || ra == 0x80168988u ||
             ra == 0x80168e48u || ra == 0x80169150u || ra == 0x80169358u ||
             ra == 0x80169470u || ra == 0x801697b0u || ra == 0x8016994cu ||
             ra == 0x80169b08u || ra == 0x8016a7a8u || ra == 0x8016c6c4u ||
             ra == 0x8016e538u || ra == 0x8017c070u));
}

/* func_8004D504 is the third exported main-exec GTE bank routine
 * [8004D504,8004D6B4): five CTC2 control writes, then two rounds of an MTC2
 * pair, an MVMVA and an MFC2 read trio. Slots as above. */
static int gte_4d504_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x8004d558u,0x48c80000u,0u}, {0x8004d55cu,0x48c90800u,0u},
        {0x8004d560u,0x48ca1000u,0u}, {0x8004d564u,0x48cb1800u,0u},
        {0x8004d568u,0x48cc2000u,0u},
        {0x8004d5fcu,0x488b0000u,3u}, {0x8004d600u,0x488d0800u,3u},
        {0x8004d608u,0x4a406012u,4u},
        {0x8004d60cu,0x480bc800u,1u}, {0x8004d610u,0x480cd000u,1u},
        {0x8004d614u,0x480dd800u,1u},
        {0x8004d624u,0x48880000u,3u}, {0x8004d628u,0x488a0800u,3u},
        {0x8004d630u,0x4a486012u,4u},
        {0x8004d688u,0x4808c800u,1u}, {0x8004d68cu,0x4809d000u,1u},
        {0x8004d690u,0x480ad800u,1u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

static int gte_4d504_caller(uint32_t ra) {
    return ra == 0x8002c5b4u ||
           (g_overlay_sc02_0031_words &&
            (ra == 0x8012f084u || ra == 0x8012f114u || ra == 0x8012f33cu ||
             ra == 0x8012f3d4u || ra == 0x80133260u || ra == 0x80135680u ||
             ra == 0x80135784u || ra == 0x801681b4u || ra == 0x80169d74u ||
             ra == 0x8016a3f4u));
}

/* func_80048B6C is the fourth exported main-exec GTE bank routine
 * [80048B6C,80048CA4), same shape as func_8004D504. */
static int gte_48b6c_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80048bf0u,0x488b4800u,3u}, {0x80048bf4u,0x488c5000u,3u},
        {0x80048bf8u,0x488d5800u,3u}, {0x80048c00u,0x4a41e012u,4u},
        {0x80048c04u,0x480bc800u,1u}, {0x80048c08u,0x480cd000u,1u},
        {0x80048c0cu,0x480dd800u,1u},
        {0x80048c10u,0x48884800u,3u}, {0x80048c14u,0x48895000u,3u},
        {0x80048c18u,0x488a5800u,3u}, {0x80048c20u,0x4a49e012u,4u},
        {0x80048c78u,0x4808c800u,1u}, {0x80048c7cu,0x4809d000u,1u},
        {0x80048c80u,0x480ad800u,1u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

static int gte_48b6c_caller(uint32_t ra) {
    return ra == 0x8002c578u ||
           (g_overlay_sc02_0031_words &&
            (ra == 0x8013568cu || ra == 0x80135790u));
}

/* func_8004864C is the fifth exported main-exec GTE bank routine
 * [8004864C,8004867C): an MTC2 pair and its MVMVA. */
static int gte_4864c_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80048654u,0x48880000u,3u}, {0x80048658u,0x48890800u,3u},
        {0x80048660u,0x4a486012u,4u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

static int gte_4864c_caller(uint32_t ra) {
    return ra == 0x8002c568u ||
           (g_overlay_sc02_0031_words &&
            (ra == 0x801356f4u || ra == 0x80135740u || ra == 0x80136af4u));
}

/* COP2 sites inside exported ranges that the per-family tables above do not
 * name. Every entry is an exact (pc, word) pair from the retail image for that
 * pc with the transfer binding the slot requires; the live-word check in
 * formatter_fetch already proves the fetched word is the one the guest loaded.
 * Slots: 0 = control write (CTC2), 1 = data read (MFC2), 3 = data write
 * (MTC2), 4 = command, 5 = control read (CFC2). */
static int gte_bank_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80047ce8u,0x48c8e800u,0u},
        {0x80047cf4u,0x48c8f000u,0u},
        {0x80047d00u,0x48c8d000u,0u},
        {0x80047d0cu,0x48c8d800u,0u},
        {0x80047d18u,0x48c8e000u,0u},
        {0x80047d20u,0x48c0c000u,0u},
        {0x80047d24u,0x48c0c800u,0u},
        {0x800483a0u,0x48c80000u,0u},
        {0x800483a4u,0x48c90800u,0u},
        {0x800483a8u,0x48ca1000u,0u},
        {0x800483acu,0x48cb1800u,0u},
        {0x800483b0u,0x48cc2000u,0u},
        {0x800483ccu,0x48880000u,3u},
        {0x800483d0u,0x488a0800u,3u},
        {0x800483d8u,0x4a486012u,4u},
        {0x800483f0u,0x480b4800u,1u},
        {0x800483f4u,0x480c5000u,1u},
        {0x800483f8u,0x480d5800u,1u},
        {0x800483fcu,0x48880000u,3u},
        {0x80048400u,0x488a0800u,3u},
        {0x80048408u,0x4a486012u,4u},
        {0x80048424u,0x480e4800u,1u},
        {0x80048428u,0x480f5000u,1u},
        {0x8004842cu,0x48185800u,1u},
        {0x80048430u,0x48880000u,3u},
        {0x80048434u,0x488a0800u,3u},
        {0x8004843cu,0x4a486012u,4u},
        {0x80048460u,0x48084800u,1u},
        {0x80048464u,0x48095000u,1u},
        {0x80048480u,0x488d0000u,3u},
        {0x80048484u,0x488a0800u,3u},
        {0x8004848cu,0x4a486012u,4u},
        {0x800484b0u,0x4808c800u,1u},
        {0x800484b4u,0x4809d000u,1u},
        {0x800484b8u,0x480ad800u,1u},
        {0x80048500u,0x48c80000u,0u},
        {0x80048504u,0x48c90800u,0u},
        {0x80048508u,0x48ca1000u,0u},
        {0x8004850cu,0x48cb1800u,0u},
        {0x80048510u,0x48cc2000u,0u},
        {0x80048db0u,0x48c80000u,0u},
        {0x80048db4u,0x48c90800u,0u},
        {0x80048db8u,0x48ca1000u,0u},
        {0x80048dbcu,0x48cb1800u,0u},
        {0x80048dc0u,0x48cc2000u,0u},
        {0x80049160u,0x48c80000u,0u},
        {0x80049164u,0x48c90800u,0u},
        {0x80049168u,0x48ca1000u,0u},
        {0x8004916cu,0x48cb1800u,0u},
        {0x80049170u,0x48cc2000u,0u},
        {0x800491b8u,0x48c82800u,0u},
        {0x800491bcu,0x48c93000u,0u},
        {0x800491c0u,0x48ca3800u,0u},
        {0x800491ecu,0x4842d000u,5u},
        {0x80049208u,0x48c46800u,0u},
        {0x8004920cu,0x48c57000u,0u},
        {0x80049210u,0x48c67800u,0u},
        {0x80049224u,0x48c4c000u,0u},
        {0x80049228u,0x48c5c800u,0u},
        {0x8004923cu,0x48c4d000u,0u},
        {0x80049638u,0x4a280030u,4u},
        {0x80049654u,0x4843f800u,5u},
        {0x80049664u,0x4a180001u,4u},
        {0x8004967cu,0x4848f800u,5u},
        {0x80049680u,0x48029800u,1u},
        {0x800538d0u,0x48c88000u,0u},
        {0x800538d4u,0x48c98800u,0u},
        {0x800538d8u,0x48ca9000u,0u},
        {0x800538dcu,0x48cb9800u,0u},
        {0x800538e0u,0x48cca000u,0u},
        {0x80053ae4u,0x48c4a800u,0u},
        {0x80053ae8u,0x48c5b000u,0u},
        {0x80053aecu,0x48c6b800u,0u},
        {0x800cee80u,0x49462009u,1u},
        {0x800cfac4u,0x49564f4du,1u},
        {0x800cfac8u,0x49462045u,1u},
        {0x800d0dc8u,0x4a314631u,4u},
        {0x800d0dccu,0x4a514632u,4u},
        {0x800d0dd0u,0x4a524a33u,4u},
        {0x800d0dd4u,0x4a524a51u,4u},
        {0x800d0dd8u,0x4a534e73u,4u},
        {0x800d1fbcu,0x4a9ce0ffu,4u},
        {0x800d2374u,0x48000000u,1u},
        {0x800d3348u,0x4bf5ffffu,4u},
        {0x8012c004u,0x4aa00428u,4u},
        {0x8012e7acu,0x48cc0000u,0u},
        {0x8012e7b0u,0x48cd0800u,0u},
        {0x8012e7c0u,0x48cc1000u,0u},
        {0x8012e7c4u,0x48cd1800u,0u},
        {0x8012e7c8u,0x48ce2000u,0u},
        {0x8012e7d4u,0x48cc2800u,0u},
        {0x8012e7dcu,0x48cd3000u,0u},
        {0x8012e7e0u,0x48ce3800u,0u},
        {0x8012e7f4u,0x488c0000u,3u},
        {0x8012e804u,0x4a180001u,4u},
        {0x8012ed78u,0x48cc0000u,0u},
        {0x8012ed7cu,0x48cd0800u,0u},
        {0x8012ed8cu,0x48cc1000u,0u},
        {0x8012ed90u,0x48cd1800u,0u},
        {0x8012ed94u,0x48ce2000u,0u},
        {0x8012eda4u,0x488c4800u,3u},
        {0x8012eda8u,0x488d5000u,3u},
        {0x8012edacu,0x488e5800u,3u},
        {0x8012edb8u,0x4a49e012u,4u},
        {0x8012edbcu,0x480c4800u,1u},
        {0x8012edc0u,0x480d5000u,1u},
        {0x8012edc4u,0x480e5800u,1u},
        {0x8012ede4u,0x488c4800u,3u},
        {0x8012ede8u,0x488d5000u,3u},
        {0x8012edecu,0x488e5800u,3u},
        {0x8012edf8u,0x4a49e012u,4u},
        {0x8012edfcu,0x480c4800u,1u},
        {0x8012ee00u,0x480d5000u,1u},
        {0x8012ee04u,0x480e5800u,1u},
        {0x8012ee24u,0x488c4800u,3u},
        {0x8012ee28u,0x488d5000u,3u},
        {0x8012ee2cu,0x488e5800u,3u},
        {0x8012ee38u,0x4a49e012u,4u},
        {0x8012ee3cu,0x480c4800u,1u},
        {0x8012ee40u,0x480d5000u,1u},
        {0x8012ee44u,0x480e5800u,1u},
        {0x8012ee68u,0x48cc2800u,0u},
        {0x8012ee70u,0x48cd3000u,0u},
        {0x8012ee74u,0x48ce3800u,0u},
        {0x8012ee8cu,0x488c0000u,3u},
        {0x8012ee9cu,0x4a480012u,4u},
        {0x8012ef88u,0x480c9800u,1u},
        {0x8012efccu,0x48cc0000u,0u},
        {0x8012efd0u,0x48cd0800u,0u},
        {0x8012efe0u,0x48cc1000u,0u},
        {0x8012efe4u,0x48cd1800u,0u},
        {0x8012efe8u,0x48ce2000u,0u},
        {0x8012eff4u,0x48cc2800u,0u},
        {0x8012effcu,0x48cd3000u,0u},
        {0x8012f000u,0x48ce3800u,0u},
        {0x8012f014u,0x4a180001u,4u},
        {0x8012f01cu,0x484cf800u,5u},
        {0x80132a24u,0x48cc0000u,0u},
        {0x80132a28u,0x48cd0800u,0u},
        {0x80132a38u,0x48cc1000u,0u},
        {0x80132a3cu,0x48cd1800u,0u},
        {0x80132a40u,0x48ce2000u,0u},
        {0x80132a54u,0x488c4800u,3u},
        {0x80132a58u,0x488d5000u,3u},
        {0x80132a5cu,0x488e5800u,3u},
        {0x80132a68u,0x4a49e012u,4u},
        {0x80132a70u,0x480c4800u,1u},
        {0x80132a74u,0x480d5000u,1u},
        {0x80132a78u,0x480e5800u,1u},
        {0x80132a98u,0x488c4800u,3u},
        {0x80132a9cu,0x488d5000u,3u},
        {0x80132aa0u,0x488e5800u,3u},
        {0x80132aacu,0x4a49e012u,4u},
        {0x80132ab4u,0x480c4800u,1u},
        {0x80132ab8u,0x480d5000u,1u},
        {0x80132abcu,0x480e5800u,1u},
        {0x80132adcu,0x488c4800u,3u},
        {0x80132ae0u,0x488d5000u,3u},
        {0x80132ae4u,0x488e5800u,3u},
        {0x80132af0u,0x4a49e012u,4u},
        {0x80132af8u,0x480c4800u,1u},
        {0x80132afcu,0x480d5000u,1u},
        {0x80132b00u,0x480e5800u,1u},
        {0x80132b18u,0x48cc2800u,0u},
        {0x80132b20u,0x48cd3000u,0u},
        {0x80132b24u,0x48ce3800u,0u},
        {0x80132b3cu,0x488c0000u,3u},
        {0x80132b4cu,0x4a480012u,4u},
        {0x80132bd8u,0x48cc0000u,0u},
        {0x80132bdcu,0x48cd0800u,0u},
        {0x80132becu,0x48cc1000u,0u},
        {0x80132bf0u,0x48cd1800u,0u},
        {0x80132bf4u,0x48ce2000u,0u},
        {0x80132c04u,0x488c4800u,3u},
        {0x80132c08u,0x488d5000u,3u},
        {0x80132c0cu,0x488e5800u,3u},
        {0x80132c18u,0x4a49e012u,4u},
        {0x80132c1cu,0x480c4800u,1u},
        {0x80132c20u,0x480d5000u,1u},
        {0x80132c24u,0x480e5800u,1u},
        {0x80132c40u,0x488c4800u,3u},
        {0x80132c44u,0x488d5000u,3u},
        {0x80132c48u,0x488e5800u,3u},
        {0x80132c54u,0x4a49e012u,4u},
        {0x80132c5cu,0x480c4800u,1u},
        {0x80132c60u,0x480d5000u,1u},
        {0x80132c64u,0x480e5800u,1u},
        {0x80132c80u,0x488c4800u,3u},
        {0x80132c84u,0x488d5000u,3u},
        {0x80132c88u,0x488e5800u,3u},
        {0x80132c94u,0x4a49e012u,4u},
        {0x80132c9cu,0x480c4800u,1u},
        {0x80132ca0u,0x480d5000u,1u},
        {0x80132ca4u,0x480e5800u,1u},
        {0x80132cbcu,0x48cc2800u,0u},
        {0x80132cc4u,0x48cd3000u,0u},
        {0x80132cc8u,0x48ce3800u,0u},
        {0x80132cdcu,0x488c0000u,3u},
        {0x80132cecu,0x4a480012u,4u},
        {0x80133100u,0x48cc2800u,0u},
        {0x80133108u,0x48cd3000u,0u},
        {0x8013310cu,0x48ce3800u,0u},
        {0x80133118u,0x48cc0000u,0u},
        {0x8013311cu,0x48cd0800u,0u},
        {0x8013312cu,0x48cc1000u,0u},
        {0x80133130u,0x48cd1800u,0u},
        {0x80133134u,0x48ce2000u,0u},
        {0x80133148u,0x4a480012u,4u},
        {0x80133160u,0x484cf800u,5u},
        {0x8013aa98u,0x48cc0000u,0u},
        {0x8013aa9cu,0x48cd0800u,0u},
        {0x8013aaacu,0x48cc1000u,0u},
        {0x8013aab0u,0x48cd1800u,0u},
        {0x8013aab4u,0x48ce2000u,0u},
        {0x8013aac0u,0x48cc2800u,0u},
        {0x8013aac8u,0x48cd3000u,0u},
        {0x8013aaccu,0x48ce3800u,0u},
        {0x8013ac84u,0x48cc0000u,0u},
        {0x8013ac88u,0x48cd0800u,0u},
        {0x8013ac98u,0x48cc1000u,0u},
        {0x8013ac9cu,0x48cd1800u,0u},
        {0x8013aca0u,0x48ce2000u,0u},
        {0x8013acacu,0x48cc2800u,0u},
        {0x8013acb4u,0x48cd3000u,0u},
        {0x8013acb8u,0x48ce3800u,0u},
        {0x8013adecu,0x4a480012u,4u},
        {0x8013b42cu,0x4a480012u,4u},
        {0x8013b48cu,0x4a486012u,4u},
        {0x8013daa8u,0x48804000u,3u},
        {0x8013dabcu,0x4a680029u,4u},
        {0x8013e0c0u,0x4aa80428u,4u},
        {0x8013e158u,0x4aa80428u,4u},
        {0x8013e1f0u,0x4aa80428u,4u},
        {0x8013e320u,0x4aa00428u,4u},
        {0x8017f820u,0x4a280030u,4u},
        {0x8017f850u,0x4a180001u,4u},
        {0x8017f880u,0x4a280030u,4u},
        {0x8017f8b0u,0x4a180001u,4u},
        {0x8017f8c0u,0x480c9800u,1u},
        {0x8017fc28u,0x4a280030u,4u},
        {0x8017fc30u,0x484cf800u,5u},
        {0x8017fc5cu,0x4b400006u,4u},
        {0x801803a8u,0x4a180001u,4u},
        {0x80180480u,0x484cf800u,5u},
        {0x801814dcu,0x49816f82u,1u},
        {0x80182f70u,0x4853494bu,5u},
        {0x80183e14u,0x4aa00428u,4u},
        {0x80183e74u,0x48814881u,3u},
        {0x80183e78u,0x48814881u,3u},
        {0x80183e90u,0x48814081u,3u},
        {0x80183ea4u,0x48814081u,3u},
        {0x80183eb4u,0x48814081u,3u},
        {0x80183eb8u,0x48814c81u,3u},
        {0x80183ebcu,0x48814881u,3u},
        {0x80183eccu,0x48814081u,3u},
        {0x80183ed0u,0x48814c81u,3u},
        {0x80183ed4u,0x48814881u,3u},
        {0x80183eecu,0x48814881u,3u},
        {0x80183ef4u,0x48814881u,3u},
        {0x80183ef8u,0x48815c81u,3u},
        {0x80184ac8u,0x48cc0000u,0u},
        {0x80184accu,0x48cd0800u,0u},
        {0x80184adcu,0x48cc1000u,0u},
        {0x80184ae0u,0x48cd1800u,0u},
        {0x80184ae4u,0x48ce2000u,0u},
        {0x80184af0u,0x48cc2800u,0u},
        {0x80184af8u,0x48cd3000u,0u},
        {0x80184afcu,0x48ce3800u,0u},
        /* func_80020598 / func_80021174 COP2 stream. Slots match 8012E7AC. */
        {0x800207c0u,0x48cc0000u,0u},
        {0x800207c4u,0x48cd0800u,0u},
        {0x800207d4u,0x48cc1000u,0u},
        {0x800207d8u,0x48cd1800u,0u},
        {0x800207dcu,0x48ce2000u,0u},
        {0x800207ecu,0x488c4800u,3u},
        {0x800207f0u,0x488d5000u,3u},
        {0x800207f4u,0x488e5800u,3u},
        {0x80020800u,0x4a49e012u,4u},
        {0x80020804u,0x480c4800u,1u},
        {0x80020808u,0x480d5000u,1u},
        {0x8002080cu,0x480e5800u,1u},
        {0x80020828u,0x488c4800u,3u},
        {0x8002082cu,0x488d5000u,3u},
        {0x80020830u,0x488e5800u,3u},
        {0x8002083cu,0x4a49e012u,4u},
        {0x80020844u,0x480c4800u,1u},
        {0x80020848u,0x480d5000u,1u},
        {0x8002084cu,0x480e5800u,1u},
        {0x80020868u,0x488c4800u,3u},
        {0x8002086cu,0x488d5000u,3u},
        {0x80020870u,0x488e5800u,3u},
        {0x8002087cu,0x4a49e012u,4u},
        {0x80020884u,0x480c4800u,1u},
        {0x80020888u,0x480d5000u,1u},
        {0x8002088cu,0x480e5800u,1u},
        {0x800208acu,0x48cc0000u,0u},
        {0x800208b0u,0x48cd0800u,0u},
        {0x800208c0u,0x48cc1000u,0u},
        {0x800208c4u,0x48cd1800u,0u},
        {0x800208c8u,0x48ce2000u,0u},
        {0x800208d8u,0x488c4800u,3u},
        {0x800208dcu,0x488d5000u,3u},
        {0x800208e0u,0x488e5800u,3u},
        {0x800208ecu,0x4a49e012u,4u},
        {0x800208f4u,0x480c4800u,1u},
        {0x800208f8u,0x480d5000u,1u},
        {0x800208fcu,0x480e5800u,1u},
        {0x80020918u,0x488c4800u,3u},
        {0x8002091cu,0x488d5000u,3u},
        {0x80020920u,0x488e5800u,3u},
        {0x8002092cu,0x4a49e012u,4u},
        {0x80020934u,0x480c4800u,1u},
        {0x80020938u,0x480d5000u,1u},
        {0x8002093cu,0x480e5800u,1u},
        {0x80020958u,0x488c4800u,3u},
        {0x8002095cu,0x488d5000u,3u},
        {0x80020960u,0x488e5800u,3u},
        {0x8002096cu,0x4a49e012u,4u},
        {0x80020974u,0x480c4800u,1u},
        {0x80020978u,0x480d5000u,1u},
        {0x8002097cu,0x480e5800u,1u},
        {0x80020994u,0x48cc2800u,0u},
        {0x8002099cu,0x48cd3000u,0u},
        {0x800209a0u,0x48ce3800u,0u},
        {0x800209b8u,0x488c0000u,3u},
        {0x800209c8u,0x4a480012u,4u},
        {0x8002119cu,0x48cc0000u,0u},
        {0x800211a0u,0x48cd0800u,0u},
        {0x800211b0u,0x48cc1000u,0u},
        {0x800211b4u,0x48cd1800u,0u},
        {0x800211b8u,0x48ce2000u,0u},
        {0x800211c4u,0x48cc2800u,0u},
        {0x800211ccu,0x48cd3000u,0u},
        {0x800211d0u,0x48ce3800u,0u},
        {0x800211e4u,0x488c0000u,3u},
        {0x800211f4u,0x4a180001u,4u},
        {0x80021200u,0x484cf800u,5u},
        {0x80021210u,0x480c9800u,1u},
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

/* LWC2 loads inside exported ranges: hardware LWC2 writes the GTE data bank
 * (PsyCross: "sets cop2 data register value. LWC2 is the same kind" of MTC2),
 * so each site requires the write_data transfer. */
static int lwc2_site(uint32_t pc, uint32_t word) {
    static const struct { uint32_t pc, word; } sites[] = {
        {0x80048fe4u,0xc8a00000u},
        {0x80048fe8u,0xc8a10004u},
        {0x80049324u,0xc8890000u},
        {0x80049328u,0xc88a0004u},
        {0x8004932cu,0xc88b0008u},
        {0x8004945cu,0xc8800000u},
        {0x80049460u,0xc8810004u},
        {0x8004961cu,0xc8800000u},
        {0x80049620u,0xc8810004u},
        {0x80049624u,0xc8a20000u},
        {0x80049628u,0xc8a30004u},
        {0x8004962cu,0xc8c40000u},
        {0x80049630u,0xc8c50004u},
        {0x80049658u,0xc8e00000u},
        {0x8004965cu,0xc8e10004u},
        {0x800d213cu,0xcbffffffu},
        {0x800d23e8u,0xcbffffffu},
        {0x800d30d4u,0xca130000u},
        {0x8012bff0u,0xcba90000u},
        {0x8012bff4u,0xcbaa0004u},
        {0x8012bff8u,0xcbab0008u},
        {0x8012e7f8u,0xcba10008u},
        {0x8012ee90u,0xc8410008u},
        {0x8012f004u,0xc8800000u},
        {0x8012f008u,0xc8810004u},
        {0x80132b40u,0xca610008u},
        {0x80132ce0u,0xca610008u},
        {0x80133138u,0xc8800000u},
        {0x8013313cu,0xc8810004u},
        {0x80133fe8u,0xc9090000u},
        {0x80133fecu,0xc90a0004u},
        {0x80133ff0u,0xc90b0008u},
        {0x8013addcu,0xcba00000u},
        {0x8013ade0u,0xcba10004u},
        {0x8013b41cu,0xc8400000u},
        {0x8013b420u,0xc8410004u},
        {0x8013b47cu,0xc8400000u},
        {0x8013b480u,0xc8410004u},
        {0x8013daacu,0xca860000u},
        {0x8013dab0u,0xc85c0000u},
        {0x8013e0acu,0xc8490000u},
        {0x8013e0b0u,0xc84a0004u},
        {0x8013e0b4u,0xc84b0008u},
        {0x8013e144u,0xc8490000u},
        {0x8013e148u,0xc84a0004u},
        {0x8013e14cu,0xc84b0008u},
        {0x8013e1dcu,0xc8490000u},
        {0x8013e1e0u,0xc84a0004u},
        {0x8013e1e4u,0xc84b0008u},
        {0x8013e30cu,0xcba90000u},
        {0x8013e310u,0xcbaa0004u},
        {0x8013e314u,0xcbab0008u},
        {0x8017f800u,0xc8400000u},
        {0x8017f804u,0xc8410004u},
        {0x8017f808u,0xc8420008u},
        {0x8017f80cu,0xc843000cu},
        {0x8017f810u,0xc8440010u},
        {0x8017f814u,0xc8450014u},
        {0x8017f840u,0xc8400000u},
        {0x8017f844u,0xc8410004u},
        {0x8017f860u,0xc8400000u},
        {0x8017f864u,0xc8410004u},
        {0x8017f868u,0xc8420008u},
        {0x8017f86cu,0xc843000cu},
        {0x8017f870u,0xc8440010u},
        {0x8017f874u,0xc8450014u},
        {0x8017f8a0u,0xc8400000u},
        {0x8017f8a4u,0xc8410004u},
        {0x8017fc08u,0xc9c00000u},
        {0x8017fc0cu,0xc9c10004u},
        {0x8017fc10u,0xca020000u},
        {0x8017fc14u,0xca030004u},
        {0x8017fc18u,0xca440000u},
        {0x8017fc1cu,0xca450004u},
        {0x80180398u,0xca600000u},
        {0x8018039cu,0xca610004u},
        {0x80180ca0u,0xca00fdcau},
        {0x80180cc0u,0xca00fdcau},
        {0x80183e00u,0xc8490000u},
        {0x80183e04u,0xc84a0004u},
        {0x80183e08u,0xc84b0008u},
        {0x800209bcu,0xc8410008u},
        {0x800211e8u,0xc8a10008u},
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == word) return 1;
    return 0;
}

/* SWC2 stores inside exported ranges: hardware SWC2 reads the GTE data bank,
 * so each site transfers through read_data. */
static int swc2_site(uint32_t pc, uint32_t word) {
    static const struct { uint32_t pc, word; } sites[] = {
        {0x80048468u,0xe8cb0010u},
        {0x80048664u,0xe8a90000u},
        {0x80048668u,0xe8aa0004u},
        {0x8004866cu,0xe8ab0008u},
        {0x80048e98u,0xe88b0010u},
        {0x80048fa8u,0xe8ab0010u},
        {0x80049338u,0xe8b90000u},
        {0x8004933cu,0xe8ba0004u},
        {0x80049340u,0xe8bb0008u},
        {0x80049474u,0xe8ab0004u},
        {0x80049648u,0xe90c0000u},
        {0x8004964cu,0xe92d0000u},
        {0x80049650u,0xe94e0000u},
        {0x80049674u,0xe90e0000u},
        {0x80049678u,0xe9280000u},
        {0x800d21e4u,0xeaffffffu},
        {0x800d230cu,0xe8250000u},
        {0x800d268cu,0xe9ffffffu},
        {0x8012c00cu,0xe8590000u},
        {0x8012c010u,0xe85a0004u},
        {0x8012c014u,0xe85b0008u},
        {0x8012e80cu,0xe84e0000u},
        {0x8012eea0u,0xe8590000u},
        {0x8012eea4u,0xe85a0004u},
        {0x8012eea8u,0xe85b0008u},
        {0x8012ef4cu,0xe8730000u},
        {0x8012f018u,0xe8ae0000u},
        {0x80132b54u,0xe8590000u},
        {0x80132b58u,0xe85a0004u},
        {0x80132b5cu,0xe85b0008u},
        {0x80132cf4u,0xe8590000u},
        {0x80132cf8u,0xe85a0004u},
        {0x80132cfcu,0xe85b0008u},
        {0x80133150u,0xe8590000u},
        {0x80133154u,0xe85a0004u},
        {0x80133158u,0xe85b0008u},
        {0x8013400cu,0xe9190000u},
        {0x80134010u,0xe91a0004u},
        {0x80134014u,0xe91b0008u},
        {0x8013adf4u,0xe8590000u},
        {0x8013adf8u,0xe85a0004u},
        {0x8013adfcu,0xe85b0008u},
        {0x8013b434u,0xe8590000u},
        {0x8013b438u,0xe85a0004u},
        {0x8013b43cu,0xe85b0008u},
        {0x8013b494u,0xe8590000u},
        {0x8013b498u,0xe85a0004u},
        {0x8013b49cu,0xe85b0008u},
        {0x8013dac8u,0xe99d0000u},
        {0x8013e0c8u,0xe8590000u},
        {0x8013e0ccu,0xe85a0004u},
        {0x8013e0d0u,0xe85b0008u},
        {0x8013e160u,0xe8590000u},
        {0x8013e164u,0xe85a0004u},
        {0x8013e168u,0xe85b0008u},
        {0x8013e1f8u,0xe8590000u},
        {0x8013e1fcu,0xe85a0004u},
        {0x8013e200u,0xe85b0008u},
        {0x8013e328u,0xe8590000u},
        {0x8013e32cu,0xe85a0004u},
        {0x8013e330u,0xe85b0008u},
        {0x8017f830u,0xe88c0000u},
        {0x8017f834u,0xe86d0000u},
        {0x8017f838u,0xe84e0000u},
        {0x8017f858u,0xe84e0000u},
        {0x8017f890u,0xe88c0000u},
        {0x8017f894u,0xe86d0000u},
        {0x8017f898u,0xe84e0000u},
        {0x8017f8b8u,0xe84e0000u},
        {0x8017fc70u,0xe8580000u},
        {0x8017fca8u,0xe84c0000u},
        {0x8017fcacu,0xe84d0004u},
        {0x8017fcb0u,0xe84e0008u},
        {0x8017fcc0u,0xe8910000u},
        {0x8017fcc4u,0xe8720000u},
        {0x8017fcc8u,0xe8530000u},
        {0x8018038cu,0xe84c0000u},
        {0x80180390u,0xe84d0004u},
        {0x80180394u,0xe84e0008u},
        {0x801804b0u,0xe8b00000u},
        {0x801804b4u,0xe8910000u},
        {0x801804b8u,0xe8720000u},
        {0x801804bcu,0xe8530000u},
        {0x801804c4u,0xe84e0000u},
        {0x80180b30u,0xe84e0000u},
        {0x80180c68u,0xe8fa00e8u},
        {0x80180c74u,0xe8f100e8u},
        {0x801812a0u,0xe83a003fu},
        {0x801812acu,0xe8c6d4d4u},
        {0x80183e18u,0xe8590000u},
        {0x80183e1cu,0xe85a0004u},
        {0x80183e20u,0xe85b0008u},
        {0x800209d0u,0xe8590000u},
        {0x800209d4u,0xe85a0004u},
        {0x800209d8u,0xe85b0008u},
        {0x800211f8u,0xebae0000u},
    };
    unsigned i;
    for (i = 0; i < sizeof(sites)/sizeof(sites[0]); ++i)
        if (sites[i].pc == pc && sites[i].word == word) return 1;
    return 0;
}

/* func_80020F34 is the exported 53-word GTE bank leaf [80020F34,80021008):
 * three rounds of an MTC2 quad (IR0..IR3), a 4B98003D GPF, and an MFC2 trio
 * from IR1..IR3. Slots as elsewhere. */
static int gte_20f34_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80020f44u,0x48884000u,3u}, {0x80020f48u,0x48894800u,3u},
        {0x80020f4cu,0x488a5000u,3u}, {0x80020f50u,0x488b5800u,3u},
        {0x80020f5cu,0x4b98003du,4u},
        {0x80020f70u,0x480c4800u,1u}, {0x80020f74u,0x480d5000u,1u},
        {0x80020f78u,0x480e5800u,1u},
        {0x80020f88u,0x48884000u,3u}, {0x80020f8cu,0x48894800u,3u},
        {0x80020f90u,0x488a5000u,3u}, {0x80020f94u,0x488b5800u,3u},
        {0x80020fa0u,0x4b98003du,4u},
        {0x80020fb4u,0x480c4800u,1u}, {0x80020fb8u,0x480d5000u,1u},
        {0x80020fbcu,0x480e5800u,1u},
        {0x80020fccu,0x48884000u,3u}, {0x80020fd0u,0x48894800u,3u},
        {0x80020fd4u,0x488a5000u,3u}, {0x80020fd8u,0x488b5800u,3u},
        {0x80020fe4u,0x4b98003du,4u},
        {0x80020fe8u,0x480c4800u,1u}, {0x80020fecu,0x480d5000u,1u},
        {0x80020ff0u,0x480e5800u,1u}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
}

static int gte_20f34_caller(uint32_t ra) {
    return ra == 0x8001f9bcu || ra == 0x8001fd80u || ra == 0x800207b0u ||
           (g_overlay_sc02_0031_words &&
            (ra == 0x80132928u || ra == 0x80165fdcu || ra == 0x8016c0b0u));
}

/* member-0031 callers of the func_8004914C / func_800491AC GTE bank pair.
 * Every alias is the return address of a JAL into one of the two routines. */
static int gte_491_pair_caller(uint32_t ra) {
    return ra == 0x8012cfecu || ra == 0x8012d400u || ra == 0x8012d520u ||
           ra == 0x8012e348u || ra == 0x8012e5f8u || ra == 0x8012e6e8u ||
           ra == 0x8012f170u || ra == 0x8012f240u || ra == 0x8012f2acu ||
           ra == 0x8012f434u || ra == 0x8012f4c8u || ra == 0x8012f4f4u ||
           ra == 0x801356c8u || ra == 0x80136d38u || ra == 0x80144120u ||
           ra == 0x8016b25cu || ra == 0x8016e820u || ra == 0x8017badcu ||
           ra == 0x8017bbe4u ||
           ra == 0x8012cff4u || ra == 0x8012d408u || ra == 0x8012d528u ||
           ra == 0x8012e350u || ra == 0x8012e608u || ra == 0x8012e6f8u ||
           ra == 0x8012f178u || ra == 0x8012f248u || ra == 0x8012f2b4u ||
           ra == 0x8012f444u || ra == 0x8012f4d0u || ra == 0x8012f504u ||
           ra == 0x80136d40u || ra == 0x80144128u || ra == 0x8016b264u ||
           ra == 0x8016e828u || ra == 0x8017bae4u || ra == 0x8017bbecu;
}

static int gte_48d9c_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
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
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
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
           ra == 0x80054224u || ra == 0x8005425cu ||
           /* The three JAL sites inside the exported func_80054DCC range. */
           ra == 0x800552c4u || ra == 0x800552fcu ||
           /* SC02 member31 JAL return aliases into the same leaf. */
           (g_overlay_sc02_0031_words &&
            (ra == 0x8012b168u || ra == 0x8012b1a4u || ra == 0x8012b1d4u ||
             ra == 0x8012f1c0u || ra == 0x80147e24u || ra == 0x80147ec8u ||
             ra == 0x80148118u || ra == 0x80163078u || ra == 0x80163148u ||
             ra == 0x801631e8u));
}

static int gte_484ec_site(uint32_t pc, uint32_t word, unsigned *slot) {
    static const GteSite sites[] = {
        {0x80048598u, 0x488b4800u, 0}, {0x8004859cu, 0x488c5000u, 0},
        {0x800485a0u, 0x488d5800u, 0}, {0x800485b8u, 0x48884800u, 0},
        {0x800485bcu, 0x48895000u, 0}, {0x800485c0u, 0x488a5800u, 0},
        {0x800485acu, 0x480bc800u, 1}, {0x800485b0u, 0x480cd000u, 1},
        {0x800485b4u, 0x480dd800u, 1}, {0x80048620u, 0x4808c800u, 1},
        {0x80048624u, 0x4809d000u, 1}, {0x80048628u, 0x480ad800u, 1},
        {0x800485a8u, 0x4a41e012u, 2}, {0x800485c8u, 0x4a49e012u, 2}
    };
    return gte_site_lookup(sites, sizeof sites / sizeof sites[0], pc, word, slot);
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
        0x80048624u, 0x80048628u, 0x8004862cu,
        /* func_80012558's three MFC2 chains (data 9..11 each round). */
        0x80012608u, 0x8001260cu, 0x80012610u,
        0x8001264cu, 0x80012650u, 0x80012654u,
        0x80012690u, 0x80012694u, 0x80012698u
        ,0x80049450u
        ,0x80047ee0u
        ,0x80047ee4u
        ,0x80047ee8u
        ,0x80047f00u
        ,0x80047f68u
        ,0x80047f6cu
        ,0x80047f70u
        /* func_800126C4's three MFC2 chains. */
        ,0x80012770u
        ,0x80012774u
        ,0x80012778u
        ,0x800127b4u
        ,0x800127b8u
        ,0x800127bcu
        ,0x800127f8u
        ,0x800127fcu
        ,0x80012800u
        /* func_800123F0's three MFC2 chains. */
        ,0x8001249cu
        ,0x800124a0u
        ,0x800124a4u
        ,0x800124e0u
        ,0x800124e4u
        ,0x800124e8u
        ,0x80012524u
        ,0x80012528u
        ,0x8001252cu
        /* func_80048FBC's three MFC2 reads. */
        ,0x80048ff8u
        ,0x80048ffcu
        ,0x80049000u
        /* func_80048EAC's three MFC2 read trios. */
        ,0x80048f14u
        ,0x80048f18u
        ,0x80048f1cu
        ,0x80048f48u
        ,0x80048f4cu
        ,0x80048f50u
        ,0x80048f84u
        ,0x80048f88u
        /* func_8004D504's two MFC2 read trios. */
        ,0x8004d610u
        ,0x8004d614u
        ,0x8004d618u
        ,0x8004d68cu
        ,0x8004d690u
        ,0x8004d694u
        /* func_80048B6C's two MFC2 read trios. */
        ,0x80048c08u
        ,0x80048c0cu
        ,0x80048c10u
        ,0x80048c7cu
        ,0x80048c80u
        ,0x80048c84u
        ,0x80020f74u
        ,0x80020f78u
        ,0x80020f7cu
        ,0x80020fb8u
        ,0x80020fbcu
        ,0x80020fc0u
        ,0x80020fecu
        ,0x80020ff0u
        ,0x80020ff4u
        ,0x8012edc0u
        ,0x8012edc4u
        ,0x8012edc8u
        ,0x8012ee00u
        ,0x8012ee04u
        ,0x8012ee08u
        ,0x8012ee40u
        ,0x8012ee44u
        ,0x8012ee48u
        ,0x8012ef8cu
        ,0x8012f020u
        ,0x80132a74u
        ,0x80132a78u
        ,0x80132a7cu
        ,0x80132ab8u
        ,0x80132abcu
        ,0x80132ac0u
        ,0x80132afcu
        ,0x80132b00u
        ,0x80132b04u
        ,0x80132c20u
        ,0x80132c24u
        ,0x80132c28u
        ,0x80132c60u
        ,0x80132c64u
        ,0x80132c68u
        ,0x80132ca0u
        ,0x80132ca4u
        ,0x80132ca8u
        ,0x80133164u
        ,0x800483f4u
        ,0x800483f8u
        ,0x800483fcu
        ,0x80048428u
        ,0x8004842cu
        ,0x80048430u
        ,0x80048464u
        ,0x80048468u
        ,0x800484b4u
        ,0x800484b8u
        ,0x800484bcu
        ,0x80049658u
        ,0x80049680u
        ,0x80049684u
        ,0x80182f74u
        ,0x80182f74u
        ,0x800491f0u
        ,0x8017f8c4u
        ,0x8017f8c4u
        ,0x8017fc34u
        ,0x8017fc34u
        ,0x80180484u
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

/* A DIV is only admitted when the retail image carries GCC's canonical
 * divide-by-zero guard for that exact instruction: BNE divisor,$zero to the
 * instruction after BREAK 7, with a NOP in between. Every audited main-exec
 * site has that shape, and the SC02 code reaches many more divide sites than a
 * hand list can carry; a DIV without the guard stays refused. */
static int div_guard_present(MusashiBootMemory *memory, uint32_t pc, uint32_t instruction) {
    uint32_t divisor = (instruction >> 16) & 31u;
    uint32_t branch, nop, brk;
    if (!musashi_boot_read32(memory, pc + 4u, &branch) ||
        !musashi_boot_read32(memory, pc + 8u, &nop) ||
        !musashi_boot_read32(memory, pc + 12u, &brk)) return 0;
    return (branch >> 26) == 5u && ((branch >> 21) & 31u) == divisor &&
           ((branch >> 16) & 31u) == 0u && (branch & 0xffffu) == 2u &&
           nop == 0u && brk == 0x0007000du;
}

/* Opt-in refusal tracing. A walk that stops early is only useful if it names
 * the guard that stopped it, but the per-instruction guards are hot, so the
 * trace is off unless MUSASHI_TRACE_REFUSAL is set. It only prints: no gate
 * changes behaviour with the flag on or off. */
static int refusal_trace(void) {
    static int cached = -1;
    if (cached < 0) {
        const char *value = getenv("MUSASHI_TRACE_REFUSAL");
        cached = (value && value[0] && value[0] != '0') ? 1 : 0;
    }
    return cached;
}

static int formatter_refuse0(int line, uint32_t pc) {
    if (refusal_trace())
        fprintf(stderr, "native_boot: STEP_REFUSED pc=%08x line=%d\n", pc, line);
    return 0;
}

/* Same, for a load or store the memory map refused: the address is the whole
 * diagnosis, so it is reported instead of the guard's line number. */
static int access_refuse0(uint32_t pc, uint32_t address, unsigned width, int store) {
    if (refusal_trace())
        fprintf(stderr, "native_boot: ACCESS_REFUSED pc=%08x addr=%08x width=%u %s\n",
                pc, address, width, store ? "store" : "load");
    return 0;
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
        return formatter_refuse0(__LINE__, cpu->pc);
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
    if (!formatter_fetch(cpu, &instruction)) return formatter_refuse0(__LINE__, cpu->pc);
    if ((cpu->pc >= 0x80128158u && cpu->pc < 0x801fff00u) ||
        (g_overlay_0004_words && cpu->pc >= 0x800cedf8u && cpu->pc < 0x80100000u) ||
        (g_overlay_0010_words && ((cpu->pc >= 0x800d0630u && cpu->pc < 0x800d0694u) ||
                                  (cpu->pc >= 0x800d06e8u && cpu->pc < 0x800d0c48u) ||
                                  (cpu->pc >= 0x800d22e4u && cpu->pc < 0x800d2318u) ||
                                  (cpu->pc >= 0x800d21c4u && cpu->pc < 0x800d222cu) ||
                                  (cpu->pc >= 0x800d1fc8u && cpu->pc < 0x800d20c0u) ||
                                  (cpu->pc >= 0x800d02c0u && cpu->pc < 0x800d02d0u) ||
                                  (cpu->pc >= 0x800d1e20u && cpu->pc < 0x800d1e28u) ||
                                  (cpu->pc >= 0x800d18dcu && cpu->pc < 0x800d1938u) ||
                                  (cpu->pc >= 0x800d1938u && cpu->pc < 0x800d1984u) ||
                                  (cpu->pc >= 0x800d1984u && cpu->pc < 0x800d19dcu) ||
                                  (cpu->pc >= 0x800d1f58u && cpu->pc < 0x800d1f90u) ||
                                  (cpu->pc >= 0x800d0588u && cpu->pc < 0x800d0630u) ||
                                  (cpu->pc >= 0x800cf854u && cpu->pc < 0x800cf864u)))) {
        uint32_t loaded;
        if (!musashi_boot_read32(memory,cpu->pc,&loaded)) return formatter_refuse0(__LINE__, cpu->pc);
        if (loaded != instruction) {
            fprintf(stderr,"native_boot: OVERLAY_WORD_MISMATCH pc=%08x expected=%08x loaded=%08x\n",
                    cpu->pc,instruction,loaded);
            return formatter_refuse0(__LINE__, cpu->pc);
        }
    }
    if (cpu->gte_load_pending &&
        (cpu->merge_pending || cpu->gte_load_next_pc != cpu->pc ||
         cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc ||
         !gte_load_successor(cpu->gte_load_reg, cpu->pc, instruction))) return formatter_refuse0(__LINE__, cpu->pc);
    opcode = instruction >> 26;
    if (cpu->delay_slot &&
        ((opcode >= 1u && opcode <= 7u) ||
         (opcode == 0u && ((instruction & 63u) == 8u ||
                          (instruction & 63u) == 9u))))
        return formatter_refuse0(__LINE__, cpu->pc); /* Branch in a delay slot has no supported CPU semantics. */
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
          (cpu->pc == 0x80053708u && instruction == 0x00c4001au)) &&
        !div_guard_present(memory, cpu->pc, instruction)) return formatter_refuse0(__LINE__, cpu->pc);
    /* These optional debug-call branches have no admitted host target yet. */
    if (cpu->pc == 0x8005937cu || cpu->pc == 0x80059698u ||
        cpu->pc == 0x80059844u || cpu->pc == 0x8005986cu) return formatter_refuse0(__LINE__, cpu->pc);
    if (cpu->pc == 0x80042598u) {
        uint32_t table, target;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x8006cb84u,&table) || table != 0x8006cb64u ||
            !musashi_boot_read32(memory,table+0xcu,&target) || target != 0x80042718u ||
            cpu->r[2] != target) return formatter_refuse0(__LINE__, cpu->pc);
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
            return formatter_refuse0(__LINE__, cpu->pc);
        if (cpu->pc == 0x80059398u) {
            static const uint32_t pointers[4][2] = {
                {0x8006cb8cu,0x1f801074u}, {0x80072868u,0x1f8010a8u},
                {0x80072878u,0x1f8010f0u}, {0x8007285cu,0x1f801814u}
            };
            unsigned i;
            for (i=0;i<4u;++i)
                if (!musashi_boot_read32(memory,pointers[i][0],&target) ||
                    target != pointers[i][1]) return formatter_refuse0(__LINE__, cpu->pc);
        }
    }
    if (cpu->pc == 0x80059dacu) return formatter_refuse0(__LINE__, cpu->pc); /* Optional debug callback unbound. */
    if (cpu->pc == 0x8005a004u) return formatter_refuse0(__LINE__, cpu->pc); /* Optional display debug callback. */
    if (cpu->pc == 0x8005a080u || cpu->pc == 0x8005a290u ||
        cpu->pc == 0x8005a2bcu || cpu->pc == 0x8005a428u) {
        uint32_t table, target;
        unsigned reg=(cpu->pc == 0x8005a290u || cpu->pc == 0x8005a2bcu) ? 3u : 2u;
        if (instruction != ((reg << 21) | 0x0000f809u) ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+0x10u,&target) || target != 0x8005b684u ||
            cpu->r[reg] != target) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x8005b690u) {
        uint32_t address;
        if (instruction != 0xac440000u ||
            !musashi_boot_read32(memory,0x8007285cu,&address) ||
            address != 0x1f801814u || cpu->r[2] != address) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x80059df4u) {
        uint32_t table, dispatch, callback;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+8u,&dispatch) || dispatch != 0x8005b7b0u ||
            !musashi_boot_read32(memory,table+0x18u,&callback) || callback != 0x8005b710u ||
            cpu->r[2] != dispatch || cpu->r[4] != callback ||
            cpu->r[5] != cpu->r[17]+0x1cu || cpu->r[6] != 0x40u ||
            ((cpu->r[5]&3u) || !musashi_boot_ram_span(memory,cpu->r[5],0x40u))) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x8005b8bcu) {
        uint32_t callback;
        if (instruction != 0x0260f809u || cpu->r[4] != cpu->r[16] || (cpu->r[4]&3u)) return formatter_refuse0(__LINE__, cpu->pc);
        if (cpu->r[19] == 0x8005b710u) {
            if (!musashi_boot_read32(memory,0x80072758u,&callback) || callback != cpu->r[19] ||
                cpu->r[18] != 0 || cpu->r[17] != 0x40u ||
                !musashi_boot_ram_span(memory,cpu->r[4],0x40u)) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (cpu->r[19] == 0x8005af68u) {
            uint32_t table, caller, rectangle, red_green, blue;
            if (!musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
                !musashi_boot_read32(memory,table+0xcu,&callback) || callback != cpu->r[19] ||
                cpu->r[17] != 8u || !musashi_boot_ram_span(memory,cpu->r[4],8u) ||
                !musashi_boot_read32(memory,cpu->r[29]+0x20u,&caller) || caller != 0x800598fcu ||
                !musashi_boot_read32(memory,cpu->r[29]+0x1cu,&rectangle) || rectangle != cpu->r[16] ||
                !musashi_boot_read32(memory,cpu->r[29]+0x10u,&red_green) ||
                !musashi_boot_read32(memory,cpu->r[29]+0x18u,&blue) ||
                ((red_green|blue)&0xff000000u) || cpu->r[18] != (red_green|blue)) return formatter_refuse0(__LINE__, cpu->pc);
        } else return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x800598f4u) {
        uint32_t table, dispatch, callback;
        if (instruction != 0x0040f809u ||
            !musashi_boot_read32(memory,0x80072780u,&table) || table != 0x80072740u ||
            !musashi_boot_read32(memory,table+8u,&dispatch) || dispatch != 0x8005b7b0u ||
            !musashi_boot_read32(memory,table+0xcu,&callback) || callback != 0x8005af68u ||
            cpu->r[2] != dispatch || cpu->r[4] != callback || cpu->r[5] != cpu->r[19] ||
            cpu->r[6] != 8u || (cpu->r[5]&3u) ||
            !musashi_boot_ram_span(memory,cpu->r[5],8u)) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x8005b154u || cpu->pc == 0x8005b090u) {
        uint32_t address;
        if (instruction != 0x8c440000u ||
            !musashi_boot_read32(memory,0x8007285cu,&address) ||
            address != 0x1f801814u || cpu->r[2] != address) return formatter_refuse0(__LINE__, cpu->pc);
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
            if (cpu->r[3] != 0x04000002u) return formatter_refuse0(__LINE__, cpu->pc);
            break;
        case 0x8005b730u: cell=0x80072860u; expected=0x1f8010a0u; word=0xac440000u; break;
        case 0x8005b740u: cell=0x80072864u; expected=0x1f8010a4u; word=0xac400000u; break;
        default:
            cell=0x80072868u; expected=0x1f8010a8u; word=0xac430000u;
            if (cpu->r[3] != 0x01000401u) return formatter_refuse0(__LINE__, cpu->pc);
            break;
        }
        if (instruction != word || !musashi_boot_read32(memory,cell,&actual) || actual != expected ||
            cpu->r[reg] != expected) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x80042708u || cpu->pc == 0x8004270cu) {
        uint32_t address;
        if (!musashi_boot_read32(memory,0x8006cb8cu,&address) ||
            address != 0x1f801074u || cpu->r[3] != address) return formatter_refuse0(__LINE__, cpu->pc);
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
            return formatter_refuse0(__LINE__, cpu->pc);
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
                cpu->r[rs] + (uint32_t)(int32_t)signed_immediate, 1)) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (cpu->pc == 0x8004d180u &&
        (instruction != 0x0140f809u || cpu->r[10] != 0xb0u)) return formatter_refuse0(__LINE__, cpu->pc);
    if (cpu->pc == 0x8004d190u &&
        (instruction != 0x8c420018u || cpu->r[2] != 0x674u)) return formatter_refuse0(__LINE__, cpu->pc);
    if (cpu->pc == 0x8004d1acu) {
        uint32_t offset = cpu->r[2] - 0xc84u;
        if (instruction != 0xac43fffcu || offset >= 56u || (offset & 3u) ||
            cpu->r[10] != 0x8004d1d8u + offset || cpu->r[9] != 0x8004d20cu)
            return formatter_refuse0(__LINE__, cpu->pc);
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
               cpu->cpu_transfer->write_status))) return formatter_refuse0(__LINE__, cpu->pc);
    }
    if (opcode == 18u && rs != 6u) {
        /* Two admitted leaf callers: first RA54050 via JAL54048, second
         * RA540D8 via JAL540D0. Any other return alias stays refused.
         * The 80048D9C camera sites run under the six audited JAL return
         * aliases; a pending MFC2 load is fine there because the admitted
         * delay-slot successor above already published it. */
        unsigned slot = 99;
        int leaf = 0, camera = 0, camera2 = 0, transform = 0, vector_command = 0;
        int transform_leaf = 0;
        int trans_leaf = 0;
        int bank = 0;
        int lib_gte = 0;
        if (cpu->cpu_transfer) {
            /* The func_80012558 library sites carry a stale RA, so they are
             * admitted by exact PC/word with the transfer binding the site
             * needs (slot 1 = data read, 3 = data write, 4 = command). */
            unsigned lib_slot = 99;
            lib_gte = gte_12558_site(cpu->pc, instruction, &lib_slot) &&
                ((lib_slot == 1u && cpu->cpu_transfer->read_data != NULL) ||
                 (lib_slot == 3u && cpu->cpu_transfer->write_data != NULL) ||
                 (lib_slot == 4u && cpu->cpu_transfer->command != NULL));
            /* func_80133CD4's vector load completes with the 0x80133FFC GTE
             * command (word 4AA00428). RA is the same clobbered 80133FB8 as the
             * three admitted LWC2 sites, so the gate is the exact site plus a
             * bound command transfer. */
            vector_command = g_overlay_sc02_0031_words &&
                cpu->cpu_transfer->command != NULL &&
                cpu->pc == 0x80133ffcu && instruction == 0x4aa00428u &&
                cpu->r[31] == 0x80133fb8u;
            /* func_80049324's own MVMVA. The leaf is main-exec code, so the
             * gate is the exact site plus its audited caller aliases. */
            transform_leaf = cpu->cpu_transfer->command != NULL &&
                cpu->pc == 0x80049334u && instruction == 0x4aa00428u &&
                gte_49324_caller(cpu->r[31]);
            transform = g_overlay_sc02_0031_words && cpu->r[31] == 0x8012f188u &&
                (((cpu->pc == 0x8004946cu && instruction == 0x48024800u) ||
                  (cpu->pc == 0x80049470u && instruction == 0x48035000u)) ?
                     cpu->cpu_transfer->read_data != NULL :
                 (cpu->pc == 0x80049480u && instruction == 0x4842f800u) ?
                     cpu->cpu_transfer->read_control != NULL :
                 (cpu->pc == 0x80049468u && instruction == 0x4a480012u) &&
                     cpu->cpu_transfer->command != NULL);
            /* func_80049440 is the same GTE special-register leaf reached from
             * func_800128EC (RA 0x80012930); admitted by exact PC/word. */
            /* func_80048EAC's non-control sites, caller-pinned like the
             * 80048D9C family they belong to. */
            unsigned eac_slot = 99;
            unsigned bank_slot = 99;
            bank = (gte_bank_site(cpu->pc, instruction, &bank_slot) &&
                    ((bank_slot == 1u && cpu->cpu_transfer->read_data != NULL) ||
                     (bank_slot == 3u && cpu->cpu_transfer->write_data != NULL) ||
                     (bank_slot == 4u && cpu->cpu_transfer->command != NULL) ||
                     (bank_slot == 5u && cpu->cpu_transfer->read_control != NULL))) ||
                   (gte_20f34_caller(cpu->r[31]) &&
                    gte_20f34_site(cpu->pc, instruction, &bank_slot));
            int eac = cpu->cpu_transfer->command != NULL &&
                ((gte_48eac_caller(cpu->r[31]) &&
                  gte_48eac_site(cpu->pc, instruction, &eac_slot)) ||
                 (gte_4d504_caller(cpu->r[31]) &&
                  gte_4d504_site(cpu->pc, instruction, &eac_slot)) ||
                 (gte_48b6c_caller(cpu->r[31]) &&
                  gte_48b6c_site(cpu->pc, instruction, &eac_slot)) ||
                 (gte_4864c_caller(cpu->r[31]) &&
                  gte_4864c_site(cpu->pc, instruction, &eac_slot)));
            trans_leaf = eac &&
                ((eac_slot == 1u && cpu->cpu_transfer->read_data != NULL) ||
                 (eac_slot == 3u && cpu->cpu_transfer->write_data != NULL) ||
                 (eac_slot == 4u && cpu->cpu_transfer->command != NULL));
            leaf = !cpu->gte_load_pending &&
                (((cpu->pc == 0x80049440u && instruction == 0x4884f000u &&
                   cpu->cpu_transfer->write_data != NULL) ||
                  (cpu->pc == 0x8004944cu && instruction == 0x4802f800u &&
                   cpu->cpu_transfer->read_data != NULL)) ||
                 (gte_47d3c_caller(cpu->r[31]) &&
                ((cpu->pc == 0x80047d3cu && instruction == 0x4884f000u &&
                  cpu->cpu_transfer->write_data) ||
                 (cpu->pc == 0x80047d48u && instruction == 0x4802f800u &&
                  cpu->cpu_transfer->read_data))));
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
            (!leaf && !camera && !camera2 && !transform && !vector_command &&
             !transform_leaf && !trans_leaf && !bank && !lib_gte)) return formatter_refuse0(__LINE__, cpu->pc);
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
        unsigned lib_slot = 99;
        if (!cpu->cpu_transfer || !cpu->cpu_transfer->write_control) return formatter_refuse0(__LINE__, cpu->pc);
        /* The func_80012558 control writes carry a stale RA, so exact PC/word
         * plus the bound control transfer is the whole gate for them; every
         * other CTC2 site keeps its index-based caller check. */
        unsigned eac_ctl = 99;
        if ((gte_20f34_caller(cpu->r[31]) &&
             gte_20f34_site(cpu->pc, instruction, &eac_ctl) && eac_ctl == 0u) ||
            (gte_bank_site(cpu->pc, instruction, &eac_ctl) && eac_ctl == 0u) ||
            (gte_12558_site(cpu->pc, instruction, &lib_slot) && lib_slot == 0u) ||
            (gte_48eac_caller(cpu->r[31]) &&
             gte_48eac_site(cpu->pc, instruction, &eac_ctl) && eac_ctl == 0u) ||
            (gte_4d504_caller(cpu->r[31]) &&
             gte_4d504_site(cpu->pc, instruction, &eac_ctl) && eac_ctl == 0u) ||
            (gte_48b6c_caller(cpu->r[31]) &&
             gte_48b6c_site(cpu->pc, instruction, &eac_ctl) && eac_ctl == 0u)) {
            /* admitted */
        } else {
        for (i=0;i<sizeof(sites)/sizeof(sites[0]);++i)
            if (sites[i][0]==cpu->pc && sites[i][1]==instruction) break;
        if (i==sizeof(sites)/sizeof(sites[0])) return formatter_refuse0(__LINE__, cpu->pc);
        if (i < 7u) {
            /* Both retail InitGeom callers share the persistent CPU/GTE
             * owners and run the instruction-image publication themselves. */
            if (cpu->r[31] != 0x80053d08u && cpu->r[31] != 0x80014454u) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i == 12u) {
            if (cpu->r[31] != 0x80014468u && cpu->r[31] != 0x80053318u) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i < 13u) {
            if (cpu->r[31] !=
                (i < 10u ? 0x80053d18u : 0x80053d24u)) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i < 18u) {
            if (!gte_48d9c_caller(cpu->r[31])) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i < 23u) {
            if (!gte_484ec_caller(cpu->r[31])) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i < 26u) {
            if (cpu->r[31] != 0x80053b10u) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (i < 31u) {
            if (cpu->r[31] != 0x8005385cu) return formatter_refuse0(__LINE__, cpu->pc);
        } else if (!g_overlay_sc02_0031_words ||
                   !gte_491_pair_caller(cpu->r[31]) ||
                   cpu->merge_pending || cpu->gte_load_pending ||
                   cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc) return formatter_refuse0(__LINE__, cpu->pc);
        }
    }
    if (opcode == 50u || (opcode == 58u &&
                          (cpu->pc == 0x80049474u ||
                           (cpu->pc >= 0x8013400cu && cpu->pc <= 0x80134014u) ||
                           (gte_49324_caller(cpu->r[31]) &&
                            (cpu->pc >= 0x80049338u && cpu->pc <= 0x80049340u))))) {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        int load = opcode == 50u;
        /* func_80133CD4 loads a 12-byte vector into GTE data registers 9-11.
         * Its own 0x80133FB0 jal overwrote RA, so this trio is admitted by
         * exact PC/word/rt instead of by caller alias, with the same transfer
         * and CPU-state requirements as the audited transform site. */
        int vector = load && cpu->cpu_transfer && cpu->cpu_transfer->write_data &&
            ((cpu->pc == 0x80133fe8u && instruction == 0xc9090000u && rt == 9u) ||
             (cpu->pc == 0x80133fecu && instruction == 0xc90a0004u && rt == 10u) ||
             (cpu->pc == 0x80133ff0u && instruction == 0xc90b0008u && rt == 11u));
        /* func_80048FBC's V0 pair. That leaf is main-exec library code, so its
         * exact sites stand without the SC02 selection the 0x8013 sites need. */
        int library_vector = load && cpu->cpu_transfer && cpu->cpu_transfer->write_data &&
            (lwc2_site(cpu->pc, instruction) ||
             (cpu->pc == 0x80048fe4u && instruction == 0xc8a00000u && rt == 0u) ||
             (cpu->pc == 0x80048fe8u && instruction == 0xc8a10004u && rt == 1u));
        vector = vector || library_vector;
        /* The matching stores publish the transformed IR1..3 back out; same
         * clobbered RA, same exact-site discipline. */
        int store_vector = !load && cpu->cpu_transfer && cpu->cpu_transfer->read_data &&
            ((cpu->pc == 0x8013400cu && instruction == 0xe9190000u && rt == 25u) ||
             (cpu->pc == 0x80134010u && instruction == 0xe91a0004u && rt == 26u) ||
             (cpu->pc == 0x80134014u && instruction == 0xe91b0008u && rt == 27u));
        /* The 80049324 leaf is main-exec code reached from either bank, so it
         * is pinned to its own caller aliases and stands without the SC02
         * selection that the 0x8013 sites require. */
        unsigned leaf_slot = 99;
        int leaf = gte_49324_caller(cpu->r[31]) &&
            gte_49324_site(cpu->pc, instruction, &leaf_slot) &&
            ((load && leaf_slot == 0u) || (!load && leaf_slot == 2u));
        if (leaf) {
            if (load) vector = 1; else store_vector = 1;
        }
        if ((!leaf && !library_vector && !g_overlay_sc02_0031_words) ||
            (!vector && !store_vector && cpu->r[31] != 0x8012f188u) ||
            !cpu->cpu_transfer || cpu->merge_pending ||
            cpu->npc != cpu->pc+4u || cpu->delay_slot || cpu->branch_pc ||
            (address & 3u) || !cpu_ram_span(memory, cpu, address, 4u) ||
            (load ? (!cpu->cpu_transfer->write_data ||
                     !((cpu->pc == 0x8004945cu && instruction == 0xc8800000u) ||
                       (cpu->pc == 0x80049460u && instruction == 0xc8810004u))) && !vector :
                    (!cpu->cpu_transfer->read_data ||
                     (!store_vector && instruction != 0xe8ab0004u)))) return formatter_refuse0(__LINE__, cpu->pc);
    } else if (opcode == 58u) {
        /* Two admitted SWC2 stores of light-matrix control 11: 80048E98 under
         * an audited 80048D9C caller and 80048FA8 under a func_80048EAC
         * caller. No pending MFC2 load may be live: every load of those two
         * routines retires at its admitted successor. */
        int swc2 = swc2_site(cpu->pc, instruction) ||
                   (cpu->pc == 0x80048e98u && instruction == 0xe88b0010u &&
                    gte_48d9c_caller(cpu->r[31])) ||
                   (cpu->pc == 0x80048fa8u && instruction == 0xe8ab0010u &&
                    gte_48eac_caller(cpu->r[31])) ||
                   /* func_8004864C publishes IR1..IR3 back out. */
                   (gte_4864c_caller(cpu->r[31]) &&
                    ((cpu->pc == 0x80048664u && instruction == 0xe8a90000u) ||
                     (cpu->pc == 0x80048668u && instruction == 0xe8aa0004u) ||
                     (cpu->pc == 0x8004866cu && instruction == 0xe8ab0008u)));
        if (!swc2 || !cpu->cpu_transfer || cpu->merge_pending ||
            (cpu->gte_load_pending && !gte_load_successor_pc(cpu->pc)) ||
            cpu->npc != cpu->pc+4u ||
            cpu->delay_slot || cpu->branch_pc ||
            !cpu->cpu_transfer->read_data) return formatter_refuse0(__LINE__, cpu->pc);
    }
    merge_kind = merge_kind_for(cpu->pc, instruction);
    if ((opcode == 34u || opcode == 38u || opcode == 42u || opcode == 46u) &&
        merge_kind == MERGE_NONE)
        return formatter_refuse0(__LINE__, cpu->pc);
    if (!merge_pending_matches(cpu, instruction))
        return formatter_refuse0(__LINE__, cpu->pc);
    if (merge_kind == MERGE_LWL || merge_kind == MERGE_LWR ||
        merge_kind == MERGE_SWL || merge_kind == MERGE_SWR) {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        if (!merge_memory_available(memory, cpu, merge_kind, address))
            return formatter_refuse0(__LINE__, cpu->pc);
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
            return formatter_refuse0(__LINE__, cpu->pc);
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
            /* SRAV serves only the 47D8C table-index shift of the camera sqrt
             * leaf and the four normalisation shifts of the exported
             * func_80047EC8 leaf; signed variable shifts elsewhere stay
             * refused. */
            uint32_t amount;
            if (!((cpu->pc == 0x80047d8cu && instruction == 0x01646007u &&
                   gte_47d3c_caller(cpu->r[31])) ||
                  (gte_47ec8_integer_caller(cpu->r[31]) &&
                   gte_47ec8_srav_site(cpu->pc, instruction)) ||
                  gte_47a2c_srav_site(cpu->pc, instruction, cpu->r[31]) ||
                  gte_47b3c_srav_site(cpu->pc, instruction, cpu->r[31]) ||
                  gte_exported_srav_site(cpu->pc, instruction)))
                return formatter_refuse0(__LINE__, cpu->pc);
            amount = cpu->r[rs] & 31u;
            cpu->r[rd] = formatter_sra(cpu->r[rt], amount);
            break;
        }
        case 8: target_npc = cpu->r[rs]; break;
        case 9: cpu->r[rd] = cpu->pc + 8u; target_npc = cpu->r[rs]; break;
        case 13: return formatter_refuse0(__LINE__, cpu->pc);
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
            if (!cpu->r[rt]) return formatter_refuse0(__LINE__, cpu->pc);
            cpu->lo = cpu->r[rs] / cpu->r[rt]; cpu->hi = cpu->r[rs] % cpu->r[rt]; break;
        case 32: {
            /* Retail movie VLC arithmetic uses trapping ADD. Refuse an
             * overflow before publishing the destination register. */
            int64_t sum = (int64_t)(int32_t)cpu->r[rs] +
                          (int64_t)(int32_t)cpu->r[rt];
            if (sum < INT32_MIN || sum > INT32_MAX) return formatter_refuse0(__LINE__, cpu->pc);
            cpu->r[rd] = (uint32_t)sum;
            break;
        }
        case 33: cpu->r[rd] = cpu->r[rs] + cpu->r[rt]; break;
        case 34: {
            /* Trapping SUB serves the camera sqrt, movie VLC and exported
             * func_80047EC8 normalisation sites; signed overflow traps fail
             * closed instead of wrapping. */
            int64_t diff;
            if (!((g_overlay_0004_words && cpu->pc >= 0x800d3234u &&
                   cpu->pc < 0x800d3540u) ||
                  (((cpu->pc == 0x80047d68u && instruction == 0x012a4822u) ||
                    (cpu->pc == 0x80047d88u && instruction == 0x016a5822u)) &&
                   gte_47d3c_caller(cpu->r[31])) ||
                  (gte_47ec8_integer_caller(cpu->r[31]) &&
                   gte_47ec8_sub_site(cpu->pc, instruction))))
                return formatter_refuse0(__LINE__, cpu->pc);
            diff = (int64_t)(int32_t)cpu->r[rs] - (int64_t)(int32_t)cpu->r[rt];
            if (diff < INT32_MIN || diff > INT32_MAX) return formatter_refuse0(__LINE__, cpu->pc);
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
        default: return formatter_refuse0(__LINE__, cpu->pc);
        }
        break;
    case 1:
        if ((instruction & 0x001f0000u) == 0) { if ((int32_t)cpu->r[rs] < 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); }
        else if ((instruction & 0x001f0000u) == 0x00010000u) { if ((int32_t)cpu->r[rs] >= 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); }
        else return formatter_refuse0(__LINE__, cpu->pc);
        break;
    case 2: target_npc = (cpu->pc + 4u & 0xf0000000u) | ((instruction & 0x03ffffffu) << 2); break;
    case 3: cpu->r[31] = cpu->pc + 8u; target_npc = (cpu->pc + 4u & 0xf0000000u) | ((instruction & 0x03ffffffu) << 2); break;
    case 4: if (cpu->r[rs] == cpu->r[rt]) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 5: if (cpu->r[rs] != cpu->r[rt]) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 6: if ((int32_t)cpu->r[rs] <= 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 7: if ((int32_t)cpu->r[rs] > 0) target_npc = cpu->pc + 4u + (uint32_t)((int32_t)signed_immediate * 4); break;
    case 8: {
        int64_t sum = (int64_t)(int32_t)cpu->r[rs] + signed_immediate;
        if (sum < INT32_MIN || sum > INT32_MAX) return formatter_refuse0(__LINE__, cpu->pc);
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
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context)) return formatter_refuse0(__LINE__, cpu->pc);
        if (rs == 0u) {
            if (!cpu->cpu_transfer->read_status(cpu->cpu_transfer->userdata, &context, &value)) return formatter_refuse0(__LINE__, cpu->pc);
            cpu->r[rt] = value;
        } else if (!cpu->cpu_transfer->write_status(cpu->cpu_transfer->userdata,
                                                    &context, cpu->r[rt])) return formatter_refuse0(__LINE__, cpu->pc);
        break;
    }
    case 18: {
        MusashiCpuContext context;
        unsigned eac_cmd_slot = 99;
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
        } else if (rs == 18u ||
                   (cpu->pc == 0x80133ffcu && (instruction & 0x02000000u) != 0u) ||
                   (gte_bank_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   (gte_20f34_caller(cpu->r[31]) &&
                    gte_20f34_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   (cpu->pc == 0x80049334u && instruction == 0x4aa00428u &&
                    gte_49324_caller(cpu->r[31])) ||
                   (gte_48eac_caller(cpu->r[31]) &&
                    gte_48eac_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   (gte_4d504_caller(cpu->r[31]) &&
                    gte_4d504_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   (gte_48b6c_caller(cpu->r[31]) &&
                    gte_48b6c_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   (gte_4864c_caller(cpu->r[31]) &&
                    gte_4864c_site(cpu->pc, instruction, &eac_cmd_slot) &&
                    eac_cmd_slot == 4u) ||
                   ((instruction & 0x02000000u) != 0u &&
                    gte_lib_command_site(cpu->pc, instruction))) {
            /* Admitted MVMVA sites run the shared operator synchronously, no load
             * delay since later MFC2 reads observe the live bank. The SC02 SQR
             * site has CO set but rs=21, so the COP2 command bit decides there;
             * rs==18 is only the MVMVA word's own encoding. */
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
        if (!cpu_read8(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &byte)) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 1, 0);
        cpu->r[rt] = byte < 128u ? byte : 0xffffff00u | byte;
        break;
    case 33:
        if (!cpu_read16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &half)) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 2, 0);
        cpu->r[rt] = (uint32_t)(int32_t)(int16_t)half; break;
    case 35:
        if (!cpu_read32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &cpu->r[rt])) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 4, 0);
        break;
    case 36:
        if (!cpu_read8(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &byte)) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 1, 0);
        cpu->r[rt] = byte; break;
    case 37:
        if (!cpu_read16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &half)) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 2, 0);
        cpu->r[rt] = half; break;
    case 34: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        uint32_t prior = cpu->r[rt];
        if (merge_kind != MERGE_LWL ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value)) return formatter_refuse0(__LINE__, cpu->pc);
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
            !cpu_read32(memory, cpu, address & ~3u, &memory_value)) return formatter_refuse0(__LINE__, cpu->pc);
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
            return formatter_refuse0(__LINE__, cpu->pc);
        break;
    }
    case 46: {
        uint32_t address = cpu->r[rs] + (uint32_t)(int32_t)signed_immediate;
        uint32_t memory_value;
        if (merge_kind != MERGE_SWR ||
            !cpu_read32(memory, cpu, address & ~3u, &memory_value) ||
            !cpu_write32(memory, cpu, address & ~3u,
                         merge_swr_value(memory_value, cpu->r[rt], address & 3u)))
            return formatter_refuse0(__LINE__, cpu->pc);
        break;
    }
    case 40: {
        uint32_t address = cpu->r[rs] + (int32_t)signed_immediate;
        if (!cpu_write8(memory, cpu, address, cpu->r[rt])) return access_refuse0(cpu->pc, address, 1, 1);
        break;
    }
    case 41: if (!cpu_write16(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, (uint16_t)cpu->r[rt])) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 2, 1); break;
    case 43: if (!cpu_write32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, cpu->r[rt])) return access_refuse0(cpu->pc, cpu->r[rs] + (int32_t)signed_immediate, 4, 1); break;
    case 50: {
        MusashiCpuContext context;
        uint32_t value;
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context) ||
            !cpu_read32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, &value) ||
            !cpu->cpu_transfer->write_data(cpu->cpu_transfer->userdata, &context, rt, value)) return formatter_refuse0(__LINE__, cpu->pc);
        break;
    }
    case 58: {
        MusashiCpuContext context;
        uint32_t control;
        /* The SC02 transform stores data IR3; the earlier admitted site
         * retains its separate control-bank transfer. */
        if (!musashi_boot_cpu_context(cpu, MUSASHI_CPU_CONTEXT_SOURCE, &context)) goto gte_transfer_refused;
        /* SWC2 reads the GTE data bank on hardware (PsyCross: "returns cop2
         * register value. SWC2 is the same kind" of MFC2), so every admitted
         * site transfers through read_data. */
        if (!cpu->cpu_transfer->read_data(cpu->cpu_transfer->userdata,
                                          &context, rt, &control)) goto gte_transfer_refused;
        if (!cpu_write32(memory, cpu, cpu->r[rs] + (int32_t)signed_immediate, control)) goto gte_transfer_refused;
        break;
    }
    default: return formatter_refuse0(__LINE__, cpu->pc);
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
    return formatter_refuse0(__LINE__, cpu->pc);
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
        if (device->checkpoint && !device->checkpoint(device->userdata, cpu)) {
            if (refusal_trace())
                fprintf(stderr, "native_boot: RUN_REFUSED pc=%08x why=checkpoint\n", cpu->pc);
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
        if (cpu->gte_load_pending && !gte_load_successor_pc(cpu->pc)) {
            if (refusal_trace())
                fprintf(stderr, "native_boot: RUN_REFUSED pc=%08x why=gte-load-pending next=%08x reg=%d\n",
                        cpu->pc, cpu->gte_load_next_pc, cpu->gte_load_reg);
            return MUSASHI_RESETGRAPH_PREFIX_INVALID_INPUT;
        }
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
    else if (formatter_range_word(kFormatterRanges29,
            sizeof kFormatterRanges29 / sizeof kFormatterRanges29[0], pc,
            &*word)) {
        /* value written by formatter_range_word */
    }
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
