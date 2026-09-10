#include "psx_types.h"

/* Recovered from member0012 and verified byte-exact by match_function.py.
 * Types describe the observed call/store, not original source declarations.
 * D_8011DB24 belongs to the separately loaded member0010 address range;
 * it must remain shared storage in the native port. */
extern void func_800D24A0(s32);
extern void func_8013E5E8(void);
extern void (*D_8011DB24)(void);

void func_8013E67C(void) {
    func_800D24A0(0);
    D_8011DB24 = func_8013E5E8;
}
