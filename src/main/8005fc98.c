#include "psx_types.h"

extern void func_80061A80(void);

/* Byte-exact adjacent startup reset range [8005FC98,8005FCB8). */
void func_8005FC98(void) {
    func_80061A80();
}
