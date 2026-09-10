#include "psx_types.h"

/* One reset body for retail and native builds. Only memory/device accesses
 * differ; the native build retains the retail call and observation order. */
#ifdef MUSASHI_NATIVE_DEVICE_BINDING
#include "musashi_boot_memory.h"

extern s32 func_800426FC_native(s32, const MusashiGpuDevice *, u32);
extern s32 func_8005C1C0_native(s32, MusashiBootMemory *, const MusashiGpuDevice *);

static u32 reset_read_word(MusashiBootMemory *memory, u32 address) {
    u32 value;
    musashi_boot_read32(memory, address, &value);
    return value;
}
static void reset_or_device(MusashiBootMemory *memory,
                             const MusashiGpuDevice *device,
                             u32 cell, u32 bits) {
    u32 address = reset_read_word(memory, cell);
    u32 value = device->read32(device->userdata, address);
    device->write32(device->userdata, address, value | bits);
}
#define RAM_READ(address, symbol) reset_read_word(memory, address)
#define RAM_WRITE(address, symbol, value) musashi_boot_write32(memory, address, value)
#define DEVICE_OR(cell, symbol, bits) reset_or_device(memory, device, cell, bits)
#define DEVICE_WRITE(cell, symbol, value) device->write32(device->userdata, reset_read_word(memory, cell), value)
#define CLEAR(address, symbol, count) musashi_boot_call_8005c29c(memory, address, 0, count)
#define func_800426FC(value) func_800426FC_native(value, device, reset_read_word(memory, 0x8006cb8cu))
#define func_8005C1C0(mode) func_8005C1C0_native(mode, memory, device)
s32 func_8005BD7C_native(s32 mode, MusashiBootMemory *memory,
                        const MusashiGpuDevice *device) {
#else
extern s32 func_800426FC(s32);
extern void func_8005C29C(u8 *, s32, u32);
extern s32 func_8005C1C0(s32);
extern volatile s32 D_80072890;
extern s32 D_8007288C, D_8007289C;
extern volatile u32 *D_80072868, *D_80072878, *D_8007285C;
extern u8 D_80078874[], D_800C5510[];
#define RAM_READ(address, symbol) (symbol)
#define RAM_WRITE(address, symbol, value) ((symbol) = (value))
#define DEVICE_OR(cell, symbol, bits) (*(symbol) = *(symbol) | (bits))
#define DEVICE_WRITE(address, symbol, value) (*(symbol) = (value))
#define CLEAR(address, symbol, count) func_8005C29C(symbol, 0, count)
s32 func_8005BD7C(s32 mode) {
#endif
    s32 previous = func_800426FC(0);
    RAM_WRITE(0x80072890u, D_80072890, 0);
    RAM_WRITE(0x8007289cu, D_8007289C, previous);
    RAM_WRITE(0x8007288cu, D_8007288C, RAM_READ(0x80072890u, D_80072890));
    switch (mode & 7) {
    case 0:
    case 5:
        DEVICE_WRITE(0x80072868u, D_80072868, 0x401);
        DEVICE_OR(0x80072878u, D_80072878, 0x800);
        DEVICE_WRITE(0x8007285cu, D_8007285C, 0);
        CLEAR(0x80078874u, D_80078874, 0x100);
        CLEAR(0x800c5510u, D_800C5510, 0x1800);
        break;
    case 1:
    case 3:
        DEVICE_WRITE(0x80072868u, D_80072868, 0x401);
        DEVICE_OR(0x80072878u, D_80072878, 0x800);
        DEVICE_WRITE(0x8007285cu, D_8007285C, 0x02000000);
        DEVICE_WRITE(0x8007285cu, D_8007285C, 0x01000000);
        break;
    }
    func_800426FC(RAM_READ(0x8007289cu, D_8007289C));
    if ((mode & 7) == 0)
        return func_8005C1C0(mode);
    return 0;
}
#undef RAM_READ
#undef RAM_WRITE
#undef DEVICE_OR
#undef DEVICE_WRITE
#undef CLEAR
#ifdef MUSASHI_NATIVE_DEVICE_BINDING
#undef func_800426FC
#undef func_8005C1C0
#endif
