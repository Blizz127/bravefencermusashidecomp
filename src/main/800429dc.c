/* Main-exec range [800429DC,80042B30) from the SLUS executable.
 * SHA256(span)=c4f2aaefb7fdbbaf4b2a1f16ec122758ce2f73d085a9dcb13314c000a6b77468.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00A09021)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x24A5BB00)
MUSASHI_NATIVE_MIPS_WORD(0x00111080)
MUSASHI_NATIVE_MIPS_WORD(0x00452021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0024)
MUSASHI_NATIVE_MIPS_WORD(0xAFB40020)
MUSASHI_NATIVE_MIPS_WORD(0xAFB3001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x8C940000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1254003C)
MUSASHI_NATIVE_MIPS_WORD(0x02801021)
MUSASHI_NATIVE_MIPS_WORD(0x94A2FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400038)
MUSASHI_NATIVE_MIPS_WORD(0x02801021)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42CB8C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94430000)
MUSASHI_NATIVE_MIPS_WORD(0xA4400000)
MUSASHI_NATIVE_MIPS_WORD(0x12400009)
MUSASHI_NATIVE_MIPS_WORD(0x3073FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x02231804)
MUSASHI_NATIVE_MIPS_WORD(0xAC920000)
MUSASHI_NATIVE_MIPS_WORD(0x94A2002C)
MUSASHI_NATIVE_MIPS_WORD(0x02639825)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x08010AA5)
MUSASHI_NATIVE_MIPS_WORD(0xA4A2002C)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x02221004)
MUSASHI_NATIVE_MIPS_WORD(0x00021027)
MUSASHI_NATIVE_MIPS_WORD(0xAC800000)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x9463BB2C)
MUSASHI_NATIVE_MIPS_WORD(0x02629824)
MUSASHI_NATIVE_MIPS_WORD(0x00621824)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA423BB2C)
MUSASHI_NATIVE_MIPS_WORD(0x16200008)
MUSASHI_NATIVE_MIPS_WORD(0x24020004)
MUSASHI_NATIVE_MIPS_WORD(0x2E500001)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D2)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24040003)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D6)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x24020004)
MUSASHI_NATIVE_MIPS_WORD(0x16220005)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D6)
MUSASHI_NATIVE_MIPS_WORD(0x2E450001)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0x16220005)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D6)
MUSASHI_NATIVE_MIPS_WORD(0x2E450001)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0x16220003)
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D6)
MUSASHI_NATIVE_MIPS_WORD(0x2E450001)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42CB8C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4530000)
MUSASHI_NATIVE_MIPS_WORD(0x02801021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB40020)
MUSASHI_NATIVE_MIPS_WORD(0x8FB3001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
/* Byte-exact callback registration, including the 80042A40 fall-through.
 * One control-flow body; native operations use guest address words.
 * Empty tied operands constrain allocation without emitting instructions.
 * The guard/enable accesses share the live array base; disable uses the
 * separately addressed alias D_8006BB2C, as in retail.
 */
#ifdef MUSASHI_NATIVE_CALLBACK_REGISTRATION
#include "musashi_callback_registration.h"
#define KEEP(value) ((void)0)
#define BASE_ADDRESS 0x8006bb00u
#define SLOT_ADDRESS(index, base) ((u32)(index) * 4u + (base))
#define READ_SLOT(slot, value) do { \
    if (!musashi_boot_read32(memory, slot, &(value))) return 0; \
} while (0)
/* base is the fixed, supported cached-RAM address above. */
#define GUARD_CLEAR(base) (!memory->bytes[(base) - 0x80000004u] && \
                           !memory->bytes[(base) - 0x80000003u])
#define RETURN_PREVIOUS() do { *result = previous; return 1; } while (0)
#define MASK_DISABLE(value) do { \
    u32 address; u16 sampled; \
    if (!device || !device->read16 || !device->write16 || \
        !musashi_boot_read32(memory, 0x8006cb8cu, &address) || (address & 1u) || \
        !device->read16(device->userdata, address, &sampled) || \
        !device->write16(device->userdata, address, 0)) return 0; \
    value = sampled; \
} while (0)
#define PUBLISH(slot, value) do { \
    if (!musashi_boot_write32(memory, slot, value)) return 0; \
} while (0)
#define ENABLE_OR(base, bit) do { \
    u16 enabled; \
    if (!musashi_boot_read16(memory, (base) + 44u, &enabled) || \
        !musashi_boot_write16(memory, (base) + 44u, enabled | (bit))) return 0; \
} while (0)
#define ENABLE_AND(bit) do { \
    u16 enabled; \
    if (!musashi_boot_read16(memory, 0x8006bb2cu, &enabled) || \
        !musashi_boot_write16(memory, 0x8006bb2cu, enabled & (bit))) return 0; \
} while (0)
#define INDEX_BIT(index) (1u << ((u32)(index) & 31u))
#define BIOS_B0(disabled) do { \
    if (!device->b0_5b || !device->b0_5b(device->userdata, disabled)) return 0; \
} while (0)
#define BIOS_C0(channel, disabled) do { \
    if (!device->c0_0a || !device->c0_0a(device->userdata, channel, disabled)) return 0; \
} while (0)
#define RELOAD_IRQ(irq) do { \
    if (!musashi_boot_read32(memory, 0x8006cb8cu, &(irq))) return 0; \
} while (0)
#define RESTORE_IRQ(irq, value) do { \
    if ((irq & 1u) || !device->write16(device->userdata, irq, (u16)(value))) return 0; \
} while (0)

int musashi_boot_call_800429dc(MusashiBootMemory *memory,
    const MusashiCallbackRegistrationDevice *device, s32 index,
    u32 callback, u32 *result) {
    s32 index_reg = index;
    u32 callback_reg = callback;
    u32 base, slot, previous, mask, irq;
    if (!memory || !result) return 0;
#else
extern u32 D_8006BB00[];
extern u16 D_8006BB2C;
extern volatile u16 *D_8006CB8C;
extern void func_8005CF48(s32), func_8005CF58(s32, s32);
#define KEEP(value) asm("" : "=r"(value) : "0"(value))
#define BASE_ADDRESS D_8006BB00
#define SLOT_ADDRESS(index, base) ((u32 *)(((index) << 2) + (u32)(base)))
#define READ_SLOT(slot, value) ((value) = *(slot))
#define GUARD_CLEAR(base) (!*(u16 *)((base) - 1))
#define RETURN_PREVIOUS() return previous
#define MASK_DISABLE(value) do { value = *D_8006CB8C; *D_8006CB8C = 0; } while (0)
#define PUBLISH(slot, value) (*(slot) = (value))
#define ENABLE_OR(base, bit) (*(u16 *)((base) + 11) |= (bit))
#define ENABLE_AND(bit) (D_8006BB2C &= (bit))
#define INDEX_BIT(index) (1u << (index))
#define BIOS_B0(disabled) func_8005CF48(disabled)
#define BIOS_C0(channel, disabled) func_8005CF58(channel, disabled)
#define RELOAD_IRQ(irq) ((irq) = D_8006CB8C)
#define RESTORE_IRQ(irq, value) (*(irq) = (value))

u32 func_800429DC(s32 index, u32 callback) {
    register s32 index_reg asm("s1") = index;
    u32 callback_reg = callback;
    register volatile u32 *base asm("a1");
    u32 *slot;
    u32 previous;
    u32 mask;
    register volatile u16 *irq asm("v0");
#endif
    KEEP(index_reg);
    base = BASE_ADDRESS;
    KEEP(base);
    slot = SLOT_ADDRESS(index_reg, base);
    READ_SLOT(slot, previous);
    if (callback_reg == previous)
        RETURN_PREVIOUS();
    if (GUARD_CLEAR(base))
        RETURN_PREVIOUS();
    MASK_DISABLE(mask);
    if (callback_reg) {
        u32 bit = INDEX_BIT(index_reg);
        PUBLISH(slot, callback_reg);
        mask |= bit;
        ENABLE_OR(base, bit);
    } else {
        u32 bit = ~INDEX_BIT(index_reg);
        PUBLISH(slot, 0);
        mask &= bit;
        ENABLE_AND(bit);
    }
    if (index_reg == 0) {
        s32 disabled = callback_reg == 0;
        BIOS_B0(disabled);
        BIOS_C0(3, disabled);
    }
    if (index_reg == 4)
        BIOS_C0(0, callback_reg == 0);
    if (index_reg == 5)
        BIOS_C0(1, callback_reg == 0);
    if (index_reg == 6)
        BIOS_C0(2, callback_reg == 0);
    RELOAD_IRQ(irq);
    KEEP(irq);
    RESTORE_IRQ(irq, mask);
    RETURN_PREVIOUS();
}
#endif
