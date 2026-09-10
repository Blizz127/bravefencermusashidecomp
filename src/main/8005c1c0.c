#include "psx_types.h"

/* Byte-exact mode-zero device query [8005C1C0,8005C29C). The volatile
 * pointers preserve the retail MMIO boundary; native device semantics must
 * be supplied by an explicit platform adapter. */
#ifdef MUSASHI_NATIVE_DEVICE_BINDING
#include "musashi_boot_memory.h"
static u32 query_pointer(MusashiBootMemory *memory, u32 cell) {
    u32 address;
    musashi_boot_read32(memory, cell, &address);
    return address;
}
#define GPU_STATUS_READ() (status_address = query_pointer(memory, 0x80072858u), device->read32(device->userdata, status_address))
#define GPU_STATUS_WRITE(value) device->write32(device->userdata, status_address, (value))
#define GPU_CONTROL_READ() device->read32(device->userdata, query_pointer(memory, 0x8007285cu))
#define GPU_CONTROL_WRITE(value) device->write32(device->userdata, query_pointer(memory, 0x8007285cu), (value))
#define GPU_REFRESH_DISCARD() do { \
    status_address = query_pointer(memory, 0x80072858u); \
    control_address = query_pointer(memory, 0x8007285cu); \
    (void)device->read32(device->userdata, status_address); \
} while (0)
#define GPU_CONTROL_SAVED_READ() device->read32(device->userdata, control_address)
#define GPU_CONTROL_SAVED_WRITE(value) device->write32(device->userdata, control_address, (value))
s32 func_8005C1C0_native(s32 mode, MusashiBootMemory *memory,
                        const MusashiGpuDevice *device) {
    u32 status_address, control_address;
#else
extern volatile u32 *D_80072858, *D_8007285C;
#define GPU_STATUS_READ() (*D_80072858)
#define GPU_STATUS_WRITE(value) (*D_80072858 = (value))
#define GPU_CONTROL_READ() (*D_8007285C)
#define GPU_CONTROL_WRITE(value) (*D_8007285C = (value))
#define GPU_REFRESH_DISCARD() ((void)GPU_STATUS_READ())
#define GPU_CONTROL_SAVED_READ() GPU_CONTROL_READ()
#define GPU_CONTROL_SAVED_WRITE(value) GPU_CONTROL_WRITE(value)
s32 func_8005C1C0(s32 mode) {
#endif
    GPU_CONTROL_WRITE(0x10000007);
    if ((GPU_STATUS_READ() & 0xffffff) != 2) {
        GPU_STATUS_WRITE((GPU_CONTROL_READ() & 0x3fff) | 0xe1001000);
        GPU_REFRESH_DISCARD();
        if (!(GPU_CONTROL_SAVED_READ() & 0x1000)) {
            return 0;
        } else {
            if (!(mode & 8)) {
                return 1;
            } else {
                GPU_CONTROL_SAVED_WRITE(0x20000504);
                return 2;
            }
        }
    }
    if (!(mode & 8))
        return 3;
    GPU_CONTROL_WRITE(0x09000001);
    return 4;
}
#undef GPU_STATUS_READ
#undef GPU_STATUS_WRITE
#undef GPU_CONTROL_READ
#undef GPU_CONTROL_WRITE
#undef GPU_REFRESH_DISCARD
#undef GPU_CONTROL_SAVED_READ
#undef GPU_CONTROL_SAVED_WRITE
