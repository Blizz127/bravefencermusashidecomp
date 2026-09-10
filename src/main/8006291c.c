#include "psx_types.h"
/* Recovered from pinned retail bytes and verified byte-exact.
 * Types and names describe this recovery, not original declarations.
 * Shared control flow; native operations retain guest words and live reads. */
#ifdef MUSASHI_NATIVE_VBLANK
#include "musashi_vblank.h"
#define READ_INDEX() u32 index; \
    if (!musashi_boot_read32(memory, 0x80072a34u, &index)) return 0
#define NONNEGATIVE(index) (((index) & 0x80000000u) == 0)
#define CALL_REQUEST(index) u32 returned, target; \
    if (!musashi_boot_read32(memory, 0x80078d78u + (index) * 4u, &target) || \
        !executor || !executor->call_one || \
        !executor->call_one(executor->userdata, memory, target, \
                            0x80078d38u + (index) * 16u, &returned)) return 0
#define DECREMENT_INDEX() do { \
    u32 current; \
    if (!musashi_boot_read32(memory, 0x80072a34u, &current) || \
        !musashi_boot_write32(memory, 0x80072a34u, current - 1u)) return 0; \
} while (0)
#define COMPLETE() return 1
int musashi_boot_call_8006291c(MusashiBootMemory *memory,
    const MusashiVblankExecutor *executor) {
#else
typedef struct { u8 bytes[16]; } Request;
extern s32 D_80072A34;
extern Request D_80078D38[];
extern s32 (*D_80078D78[])(Request *);
#define READ_INDEX() s32 index = D_80072A34
#define NONNEGATIVE(index) ((index) >= 0)
#define CALL_REQUEST(index) s32 returned = D_80078D78[index](&D_80078D38[index])
#define DECREMENT_INDEX() D_80072A34--
#define COMPLETE() return
void func_8006291C(void) {
#endif
    READ_INDEX();
    if (NONNEGATIVE(index)) {
        CALL_REQUEST(index);
        if (returned) {
            DECREMENT_INDEX();
        }
    }
    COMPLETE();
}
