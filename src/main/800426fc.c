/* Exact retail word export for [800426FC,80042718); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x8c63cb8c)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0xa4640000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Byte-exact register exchange. The pinned pointer targets 1F801074.
 * The read precedes the write and the old halfword is zero-extended.
 * Native execution requires the corresponding platform boundary. */
#ifdef MUSASHI_NATIVE_DEVICE_BINDING
#include "musashi_gpu_device.h"
#define MASK_READ() device->read16(device->userdata, mask_address)
#define MASK_WRITE(value) device->write16(device->userdata, mask_address, (u16)(value))
/* Caller snapshots the guest pointer cell for this exchange. */
s32 func_800426FC_native(s32 value, const MusashiGpuDevice *device,
                         u32 mask_address) {
#else
extern volatile u16 *D_8006CB8C;
#define MASK_READ() (*D_8006CB8C)
#define MASK_WRITE(value) (*D_8006CB8C = (value))
s32 func_800426FC(s32 value) {
#endif
    u16 previous = MASK_READ();
    MASK_WRITE(value);
    return previous;
}
#undef MASK_READ
#undef MASK_WRITE
#endif
