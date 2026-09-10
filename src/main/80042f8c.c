#include "psx_types.h"

/* Byte-exact C recovery of [80042F8C,80043034), shared with the native port.
 * Empty operands constrain register allocation and scheduling without emitting
 * instructions. In particular, flags precede the channel-bit calculation and
 * the disable path stores through the zero register, not the callback register.
 */
#ifdef MUSASHI_NATIVE_DMA_REGISTRATION
#include "musashi_callback_registration.h"
typedef u32 CallbackWord;
typedef u32 CallbackBase;
typedef u32 CallbackSlot;
#define REG(type, name, reg) type name
#define KEEP(value) ((void)0)
#define AFTER_READ(channel, flags) ((void)0)
#define MASK_SHIFT(flags, shift, mask) ((void)0)
#define MASK_POINTER(mask, value, control) ((void)0)
#define RETAIN_CONTROL(control) ((void)0)
#define BASE_ADDRESS 0x8006cbc4u
#define SLOT_ADDRESS(channel, base) ((u32)(channel) * 4u + (base))
#define DECLARE_CONTROL() u32 control; \
    if (!musashi_boot_read32(memory, 0x8006cbc0u, &control)) return 0
#define READ_SLOT(slot, previous) do { \
    if (!musashi_boot_read32(memory, slot, &(previous))) return 0; \
} while (0)
#define PUBLISH(slot, value) do { \
    if (!musashi_boot_write32(memory, slot, value)) return 0; \
} while (0)
#define READ_CONTROL(flags) do { \
    if (!device || !device->read32 || (control & 3u) || \
        !device->read32(device->userdata, control, &(flags))) return 0; \
} while (0)
#define WRITE_CONTROL(flags) do { \
    if (!device->write32 || !device->write32(device->userdata, control, flags)) return 0; \
} while (0)
#define CHANNEL_SHIFT(channel) (((u32)(channel) + 16u) & 31u)
#define RETURN_PREVIOUS() do { *result = previous; return 1; } while (0)

int musashi_boot_call_80042f8c(MusashiBootMemory *memory,
    const MusashiDmaCallbackRegistrationDevice *device, s32 index,
    u32 callback, u32 *result) {
#else
typedef s32 CallbackWord;
typedef s32 *CallbackBase;
typedef volatile s32 *CallbackSlot;
extern s32 D_8006CBC4[];
extern volatile u32 *D_8006CBC0;
#define REG(type, name, reg) register type name asm(reg)
#define KEEP(value) asm("" : "=r"(value) : "0"(value))
#define AFTER_READ(channel, flags) asm("" : "=r"(channel) : "0"(channel), "r"(flags))
#define MASK_SHIFT(flags, shift, mask) \
    asm("" : "=r"(flags), "=r"(shift) : "0"(flags), "1"(shift), "r"(mask))
#define MASK_POINTER(mask, value, control) \
    asm("" : "=r"(mask), "=r"(value) : "0"(mask), "1"(value), "r"(control))
#define RETAIN_CONTROL(control) asm volatile("" : : "r"(control))
#define BASE_ADDRESS D_8006CBC4
#define SLOT_ADDRESS(channel, base) ((CallbackSlot)(((channel) << 2) + (u32)(base)))
#define DECLARE_CONTROL() REG(volatile u32 *, control, "a1") = D_8006CBC0
#define READ_SLOT(slot, previous) ((previous) = *(slot))
#define PUBLISH(slot, value) (*(slot) = (value))
#define READ_CONTROL(flags) ((flags) = *control)
#define WRITE_CONTROL(flags) (*control = (flags))
#define CHANNEL_SHIFT(channel) ((channel) + 16)
#define RETURN_PREVIOUS() return previous

s32 func_80042F8C(s32 index, s32 callback) {
#endif
    REG(s32, channel, "a2") = index;
    REG(CallbackBase, base, "v1");
    REG(CallbackSlot, slot, "v1");
    REG(CallbackWord, previous, "a3");
    REG(CallbackWord, value, "a0");
#ifdef MUSASHI_NATIVE_DMA_REGISTRATION
    if (!memory || !result) return 0;
#endif
    KEEP(channel);
    base = BASE_ADDRESS;
    KEEP(base);
    slot = SLOT_ADDRESS(channel, base);
    KEEP(slot);
    READ_SLOT(slot, previous);
    KEEP(previous);
    value = callback;
    KEEP(value);
    if (value != previous) {
        if (value) {
            DECLARE_CONTROL();
            REG(u32, mask, "v0") = 0x00ffffff;
            REG(u32, flags, "a0");
            REG(s32, shift, "v1");
            u32 bits;
            PUBLISH(slot, value);
            READ_CONTROL(flags);
            AFTER_READ(channel, flags);
            shift = CHANNEL_SHIFT(channel);
            flags &= mask;
            MASK_SHIFT(flags, shift, mask);
            bits = (1u << shift) | 0x00800000;
            KEEP(bits);
            WRITE_CONTROL(flags | bits);
            RETAIN_CONTROL(control);
        } else {
            DECLARE_CONTROL();
            REG(u32, mask, "v0") = 0x00ff0000;
            REG(u32, flags, "v1");
            REG(s32, shift, "a0");
            MASK_POINTER(mask, value, control);
            mask |= 0xffff;
            PUBLISH(slot, 0);
            READ_CONTROL(flags);
            AFTER_READ(channel, flags);
            shift = CHANNEL_SHIFT(channel);
            flags &= mask;
            MASK_SHIFT(flags, shift, mask);
            WRITE_CONTROL((flags | 0x00800000) & ~(1u << shift));
            RETAIN_CONTROL(control);
        }
    }

    RETURN_PREVIOUS();
}
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
/* Retail word export for [80042F8C,80043034); EXE-verified. */
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x3c038007)
MUSASHI_NATIVE_MIPS_WORD(0x2463cbc4)
MUSASHI_NATIVE_MIPS_WORD(0x00061080)
MUSASHI_NATIVE_MIPS_WORD(0x00431821)
MUSASHI_NATIVE_MIPS_WORD(0x8c670000)
MUSASHI_NATIVE_MIPS_WORD(0x00a02021)
MUSASHI_NATIVE_MIPS_WORD(0x10870020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800010)
MUSASHI_NATIVE_MIPS_WORD(0x3c0200ff)
MUSASHI_NATIVE_MIPS_WORD(0x3c058007)
MUSASHI_NATIVE_MIPS_WORD(0x8ca5cbc0)
MUSASHI_NATIVE_MIPS_WORD(0x3442ffff)
MUSASHI_NATIVE_MIPS_WORD(0xac640000)
MUSASHI_NATIVE_MIPS_WORD(0x8ca40000)
MUSASHI_NATIVE_MIPS_WORD(0x24c30010)
MUSASHI_NATIVE_MIPS_WORD(0x00822024)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00621004)
MUSASHI_NATIVE_MIPS_WORD(0x3c030080)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x00822025)
MUSASHI_NATIVE_MIPS_WORD(0xaca40000)
MUSASHI_NATIVE_MIPS_WORD(0x08010c0b)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c058007)
MUSASHI_NATIVE_MIPS_WORD(0x8ca5cbc0)
MUSASHI_NATIVE_MIPS_WORD(0x3442ffff)
MUSASHI_NATIVE_MIPS_WORD(0xac600000)
MUSASHI_NATIVE_MIPS_WORD(0x8ca30000)
MUSASHI_NATIVE_MIPS_WORD(0x24c40010)
MUSASHI_NATIVE_MIPS_WORD(0x00621824)
MUSASHI_NATIVE_MIPS_WORD(0x3c020080)
MUSASHI_NATIVE_MIPS_WORD(0x00621825)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00821004)
MUSASHI_NATIVE_MIPS_WORD(0x00021027)
MUSASHI_NATIVE_MIPS_WORD(0x00621824)
MUSASHI_NATIVE_MIPS_WORD(0xaca30000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00e01021)
#endif
