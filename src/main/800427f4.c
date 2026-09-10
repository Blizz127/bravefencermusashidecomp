#include "psx_types.h"
/* Byte-exact interrupt dispatcher with shared native dispatch control flow.
 * Empty tied operands preserve retail register allocation and load order.
 * The initial memory clobber keeps the active-flag store before the mask
 * pointer load. No instructions are supplied by these constraints.
 * Callback slots are loaded after acknowledgement; never pre-copy the table.
 * Native device accesses are checked; BIOS return-context handling remains
 * an explicit pending boundary, never an assumed successful return.
 * MMIO/callback ordering is verified for the pinned PS1 binary, not portable
 * C: a native binding must sequence the tail reads and use shared RAM aliases.
 */
#ifdef MUSASHI_NATIVE_IRQ_DISPATCH
#include "musashi_irq_dispatch.h"
typedef u32 Callback;
#define READ32(a,v) do { if (!musashi_boot_read32(memory,a,&(v))) return 0; } while (0)
#define READ16(a,v) do { u16 half; if (!musashi_boot_read16(memory,a,&half)) return 0; (v)=half; } while (0)
#define WRITE16(a,v) do { if (!musashi_boot_write16(memory,a,(u16)(v))) return 0; } while (0)
#define WRITE32(a,v) do { if (!musashi_boot_write32(memory,a,(v))) return 0; } while (0)
#define DEVICE_READ(a,v) do { u16 half; if (!device || !device->read16 || ((a)&1u) || \
    !device->read16(device->userdata,a,&half)) { return 0; } (v)=half; } while (0)
#define DEVICE_WRITE(a,v) do { if (!device || !device->write16 || ((a)&1u) || \
    !device->write16(device->userdata,a,(u16)(v))) return 0; } while (0)
#define LOAD_STATUS() READ32(0x8006cb88u,status)
#define LOAD_MASK() READ32(0x8006cb8cu,mask)
#define LOAD_ENABLED() READ16(0x8006bb2cu,enabled)
#define ACTIVE(v) WRITE16(0x8006bafeu,v)
#define IRQ_READ() DEVICE_READ(status,irq)
#define MASK_READ() do { u32 value; DEVICE_READ(mask,value); sampled=value & enabled; } while (0)
#define ACK() do { u32 address; READ32(0x8006cb88u,address); DEVICE_WRITE(address,~(one<<index)); } while (0)
#define CALLBACK_LOAD() READ32(slot,callback)
#define CALLBACK_CALL() do { if (!device || !device->execute || \
    !device->execute(device->userdata,memory,callback)) return 0; } while (0)
#define DIAGNOSTIC(format,a,b,count) do { if (!device || !device->diagnostic || \
    !device->diagnostic(device->userdata,memory,format,a,b,count)) return 0; } while (0)
#define FIRST_SLOT u32 first = 0x8006bb00u
#define SLOT_TYPE u32
#define SLOT_NEXT() (slot += 4u)
#define ONE u32 one = 1
/* Both retail exits invoke 8005CED8 after their preceding side effects. The
 * platform owns the exception frame, so it must explicitly accept that return
 * rather than treating the game save record as a host continuation. */
static int native_return_from_exception(const MusashiIrqDispatchDevice *device) {
    if (device && device->return_from_exception) {
        if (!device->return_from_exception(device->userdata)) return 0;
        return MUSASHI_IRQ_CONTEXT_RETURN_DELEGATED;
    }
    return MUSASHI_IRQ_CONTEXT_RETURN_PENDING;
}
int musashi_boot_call_800427f4(MusashiBootMemory *memory,
    const MusashiIrqDispatchDevice *device) {
    u32 pending, sampled, enabled, status, irq, mask, guard;
    if (!memory) return 0;
    READ16(0x8006bafcu,guard);
    if (!guard) {
        LOAD_STATUS(); IRQ_READ();
        DIAGNOSTIC(0x80073558u,irq,0,1);
        return native_return_from_exception(device);
    }
#else
typedef void (*Callback)(void);
extern u8 D_8006BAFC[];
extern u16 D_8006BAFE, D_8006BB2C;
extern volatile u16 *D_8006CB88, *D_8006CB8C;
extern s32 D_8006CB94;
extern char D_80073558[], D_80073574[];
extern void func_8005C604(char *, ...), func_8005CED8(void);

void func_800427F4(void) {
    u8 *state = D_8006BAFC;
    register u32 pending asm("s0");
    register u32 sampled asm("v0");
    register u32 enabled asm("v1");
    register volatile u16 *status asm("a0");
    register u32 irq asm("a0");
    register volatile u16 *mask asm("v0");
    if (*(u16 *)state == 0) {
        func_8005C604(D_80073558, *D_8006CB88);
        func_8005CED8();
    }
#define LOAD_STATUS() (status = D_8006CB88)
#define LOAD_MASK() (mask = D_8006CB8C)
#define LOAD_ENABLED() (enabled = D_8006BB2C)
#define ACTIVE(v) (D_8006BAFE = (v))
#define IRQ_READ() (irq = *status)
#define MASK_READ() (sampled = *mask & enabled)
#define ACK() (*D_8006CB88 = ~(one << index))
#define CALLBACK_LOAD() (callback = *slot)
#define CALLBACK_CALL() callback()
#define FIRST_SLOT Callback *first = (Callback *)(state + 4)
#define SLOT_TYPE Callback *
#define SLOT_NEXT() (++slot)
#define ONE register u32 one asm("s3") = 1
#endif
    LOAD_STATUS();
    LOAD_ENABLED();
    ACTIVE(1);
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(enabled), "=r"(status) : "0"(enabled), "1"(status) : "memory");
#endif
    LOAD_MASK();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(mask) : "0"(mask));
#endif
    IRQ_READ();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(irq), "=r"(mask) : "0"(irq), "1"(mask));
#endif
    enabled = enabled & irq;
    MASK_READ();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(sampled) : "0"(sampled));
#endif
    pending = sampled;
    if (sampled) {
        ONE;
        FIRST_SLOT;
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(one) : "0"(one));
#endif
        do {
            s32 index = 0;
            SLOT_TYPE slot;
            if (pending) {
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(pending) : "0"(pending));
#endif
                slot = first;
dispatch_bit:
                    if (index >= 11)
                        goto rescan;
                    if (pending & 1) {
                        Callback callback;
                        ACK();
                        CALLBACK_LOAD();
                        if (callback)
                            CALLBACK_CALL();
                    }
                    SLOT_NEXT();
                    pending >>= 1;
                    ++index;
                if (pending & 0xffff)
                    goto dispatch_bit;
            }
rescan:
            LOAD_STATUS();
            LOAD_ENABLED();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(enabled), "=r"(status) : "0"(enabled), "1"(status));
#endif
            LOAD_MASK();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(mask) : "0"(mask));
#endif
            IRQ_READ();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(irq), "=r"(mask) : "0"(irq), "1"(mask));
#endif
            enabled = enabled & irq;
            MASK_READ();
#ifndef MUSASHI_NATIVE_IRQ_DISPATCH
    asm("" : "=r"(sampled) : "0"(sampled));
#endif
            pending = sampled;
        } while (sampled);
    }
#ifdef MUSASHI_NATIVE_IRQ_DISPATCH
    /* Retail snapshots both pointers before either device read, and retains
     * them for diagnostic arguments even if a provider changes the RAM cells. */
    LOAD_STATUS(); LOAD_MASK(); IRQ_READ();
    DEVICE_READ(mask,sampled);
    if (irq & sampled) {
        u32 previous;
        READ32(0x8006cb94u,previous);
        WRITE32(0x8006cb94u,previous + 1u);
        if (previous >= 0x801u && previous < 0x80000000u) {
            IRQ_READ(); DEVICE_READ(mask,sampled);
            DIAGNOSTIC(0x80073574u,irq,sampled,2);
            LOAD_STATUS();
            WRITE32(0x8006cb94u,0);
            DEVICE_WRITE(status,0);
        }
    } else {
        WRITE32(0x8006cb94u,0);
    }
    ACTIVE(0);
    return native_return_from_exception(device);
#else
    if (*D_8006CB88 & *D_8006CB8C) {
        s32 previous = D_8006CB94;
        D_8006CB94 = (u32)previous + 1u;
        if (previous >= 0x801) {
            func_8005C604(D_80073574, *D_8006CB88, *D_8006CB8C);
            D_8006CB94 = 0;
            *D_8006CB88 = 0;
        }
    } else {
        D_8006CB94 = 0;
    }
    D_8006BAFE = 0;
    func_8005CED8();
#endif
}
