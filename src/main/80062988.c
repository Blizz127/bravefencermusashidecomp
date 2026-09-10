#include "psx_types.h"
/* Recovered from pinned retail bytes and verified byte-exact.
 * Types and names describe this recovery, not original declarations.
 * The sign-bit expression is shared with the checked native RAM binding. */
#ifdef MUSASHI_NATIVE_VBLANK
#include "musashi_vblank.h"
#define READ_INDEX() u32 index; \
    if (!result || !musashi_boot_read32(memory, 0x80072a34u, &index)) return 0
#define FINISH(value) do { *result = (value); return 1; } while (0)
int musashi_boot_call_80062988(MusashiBootMemory *memory, u32 *result) {
#else
extern s32 D_80072A34;
#define READ_INDEX() s32 index = D_80072A34
#define FINISH(value) return (value)
s32 func_80062988(void) {
#endif
    READ_INDEX();
    FINISH((u32)index >> 31);
}
