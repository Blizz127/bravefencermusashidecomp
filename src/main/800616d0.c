/* Main-exec range [800616D0,80061770) from the SLUS executable.
 * SHA256(span)=e9dfc0faa835c0282b2857fa874f3c1a0b047e1387848ef07419d4447a1f9aeb.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C018A62)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440001F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C018A47)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C018A62)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400019)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x24638C80)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC228C88)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048008)
MUSASHI_NATIVE_MIPS_WORD(0x24848CC4)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428C84)
MUSASHI_NATIVE_MIPS_WORD(0x3C068008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC68CC0)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC228CC8)
MUSASHI_NATIVE_MIPS_WORD(0xAC600000)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC208C84)
MUSASHI_NATIVE_MIPS_WORD(0x10C00006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C840000)
MUSASHI_NATIVE_MIPS_WORD(0x3C058008)
MUSASHI_NATIVE_MIPS_WORD(0x8CA58CC8)
MUSASHI_NATIVE_MIPS_WORD(0x00C0F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
/* Recovered from pinned retail bytes and verified byte-exact.
 * Types and names describe this recovery, not original declarations.
 * Shared control flow with checked native guest-word operations. */
#ifdef MUSASHI_NATIVE_VBLANK
#include "musashi_vblank.h"
typedef u32 StatePointer;
typedef u32 Completion;
typedef u32 StateWord;
#define D_80078C80 0x80078c80u
#define D_80078C84 0x80078c84u
#define D_80078C88 0x80078c88u
#define D_80078CC4 0x80078cc4u
#define D_80078CC8 0x80078cc8u
#define ADDRESS(name) (name)
#define QUERY(name) do { \
    if (!musashi_boot_call_80062988(memory, &name)) return 0; \
} while (0)
#define PROCESS() do { if (!musashi_boot_call_8006291c(memory, executor)) return 0; } while (0)
#define STORE(address, value) do { \
    if (!musashi_boot_write32(memory, address, value)) return 0; \
} while (0)
#define READ(address, name) do { \
    if (!musashi_boot_read32(memory, address, &name)) return 0; \
} while (0)
#define STORE_GLOBAL(name, value) STORE(ADDRESS(name), value)
#define READ_GLOBAL(name, value) READ(ADDRESS(name), value)
#define READ_CALLBACK(callback) do { \
    if (!musashi_boot_read32(memory, 0x80078cc0u, &callback)) return 0; \
} while (0)
#define CALL(callback, first, second) do { \
    if (!executor || !executor->call_two || \
        !executor->call_two(executor->userdata, memory, callback, first, second)) return 0; \
} while (0)
#define COMPLETE() return 1
int musashi_boot_call_800616d0(MusashiBootMemory *memory,
    const MusashiVblankExecutor *executor) {
#else
typedef volatile s32 *StatePointer;
typedef void (*Completion)(s32, s32);
typedef s32 StateWord;
extern s32 func_80062988(void);
extern void func_8006291C(void);
extern volatile s32 D_80078C80, D_80078C84, D_80078C88, D_80078CC4, D_80078CC8;
extern void (*D_80078CC0)(s32, s32);
#define ADDRESS(name) (&name)
#define QUERY(name) ((name) = func_80062988())
#define PROCESS() func_8006291C()
#define STORE(address, value) (*(address) = (value))
#define READ(address, name) ((name) = *(address))
#define STORE_GLOBAL(name, value) ((name) = (value))
#define READ_GLOBAL(name, value) ((value) = (name))
#define READ_CALLBACK(callback) ((callback) = D_80078CC0)
#define CALL(callback, first, second) callback(first, second)
#define COMPLETE() return
void func_800616D0(void) {
#endif
    StateWord before;
    QUERY(before);
    if (before == 0) {
        StateWord after;
        PROCESS();
        QUERY(after);
        if (after != 0) {
            StateWord pending_first, pending_second;
            Completion callback;
            StatePointer pending = ADDRESS(D_80078C80);
            StatePointer saved = ADDRESS(D_80078CC4);
            STORE_GLOBAL(D_80078C88, 1);
            READ(pending, pending_first);
            STORE(saved, pending_first);
            READ_GLOBAL(D_80078C84, pending_second);
            READ_CALLBACK(callback);
            STORE_GLOBAL(D_80078CC8, pending_second);
            STORE(pending, 0);
            STORE_GLOBAL(D_80078C84, 0);
            if (callback) {
                StateWord first, second;
                READ(saved, first);
                READ_GLOBAL(D_80078CC8, second);
                CALL(callback, first, second);
            }
        }
    }
    COMPLETE();
}
#endif
