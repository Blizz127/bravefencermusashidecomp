/* Registers two boot-time callbacks.
 *
 * On the entry chain: func_80010178 (the compiler-generated boot routine
 * called from crt0) calls func_800100A0, whose loop of registered
 * initializers eventually reaches this. Hand-matched for D4 because m2c's
 * output ("? func_80042610(? (*)());") needed real types before it would
 * compile, and the natural cleanup did not match at -O2 -- see below.
 */

#include "psx_types.h"

typedef void (*Callback)(void);

extern void func_8001096C(void);
extern void func_8001099C(void);
extern void func_800595FC(Callback callback);
extern void func_80042610(Callback callback);

/* This is the only function found so far that matches at -O0 rather than
 * -O2, the level identified for the rest of the executable in
 * provenance/compiler_identity.json. At -O2 GCC drops the frame pointer this
 * function does not need, producing 56 bytes against retail's 72; -O0 keeps
 * it and reproduces retail byte-for-byte. Two short, unconditional calls with
 * no other logic is exactly the kind of leaf-ish init code a build system
 * might compile at a lower level than the hot path, so this is read as a
 * genuine per-translation-unit or per-file flag difference, not a
 * decompilation error -- discriminate.py's identification was never run
 * against this function specifically, and evidently should not be assumed to
 * cover every function in the executable.
 */
void func_80010A98(void) {
    func_800595FC(func_8001099C);
    func_80042610(func_8001096C);
}
