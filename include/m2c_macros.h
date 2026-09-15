#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* Macros m2c emits under --valid-syntax, adapted for this repository.
 *
 * Derived from tools/m2c/m2c_macros.h (the upstream header shipped with the
 * pinned m2c checkout). Two deliberate differences:
 *
 * - The types come from psx_types.h, which is the only type header the
 *   Psy-Q chain can reach: cpp runs with -nostdinc.
 * - The memcpy aliases are dropped. -nostdinc provides no string.h, and a
 *   draft that needs one has to declare it itself rather than silently
 *   picking up a host prototype.
 *
 * Why this matters for matching: without --valid-syntax, m2c spells an
 * access into an untyped global `NAME.unkHHHH`, which the retail compiler
 * rejects because the sanitizer has already declared NAME a scalar. That
 * one error accounted for most of the drafts that would not compile, and a
 * draft that does not compile can never reach the oracle. M2C_FIELD keeps
 * the width m2c inferred from the load or store, so the draft compiles and
 * the oracle gets to judge it.
 *
 * None of these macros is evidence about the original source. M2C_ERROR and
 * friends evaluate to zero, which is a placeholder for an instruction m2c
 * could not model, not a recovered expression. A body using one can still
 * be compared against retail; it simply will not match until it is written
 * properly.
 */

#include "psx_types.h"

/* Unknown types */
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr) ((s8 *) (expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type) (expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions. Zero is a placeholder, not a recovered value. */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

#endif
