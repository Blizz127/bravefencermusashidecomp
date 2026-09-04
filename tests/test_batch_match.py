from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import batch_match  # noqa: E402
from retail_common import RetailError  # noqa: E402


ASM = """\
.include "macro.inc"

.section .text, "ax"

glabel func_80012AB0
    /* 38B0 80012AB0 0800E003 */  jr         $ra
    /* 38B4 80012AB4 00000000 */   nop

glabel func_80012AB8
    /* 38B8 80012AB8 E8FFBD27 */  addiu      $sp, $sp, -0x18
    /* 38BC 80012ABC 0800E003 */  jr         $ra
    /* 38C0 80012AC0 00000000 */   nop
"""


class EnumerateTests(unittest.TestCase):
    def test_functions_are_found_with_their_addresses(self) -> None:
        funcs = batch_match.enumerate_functions(ASM)
        self.assertEqual([f.name for f in funcs], ["func_80012AB0", "func_80012AB8"])
        self.assertEqual(funcs[0].vram, 0x80012AB0)

    def test_size_is_measured_from_the_instruction_words(self) -> None:
        funcs = batch_match.enumerate_functions(ASM)
        self.assertEqual(funcs[0].size, 8)
        self.assertEqual(funcs[1].size, 12)

    def test_a_file_with_no_functions_yields_nothing(self) -> None:
        self.assertEqual(batch_match.enumerate_functions(".section .text\n"), [])


class SafetyTests(unittest.TestCase):
    """The harness must never write over a committed source.

    A previous batch overwrote a hand-written, verified source with m2c output,
    failed to build it, and deleted the file. Nothing noticed until the registry
    was re-verified. Refusing to write an existing path is the guard.
    """

    def test_an_existing_source_is_never_overwritten(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            target = Path(scratch) / "8012ab0.c"
            target.write_text("/* hand written and verified */\n")
            with self.assertRaises(RetailError):
                batch_match.promote(Path(scratch) / "candidate.c", target)
            self.assertEqual(target.read_text(), "/* hand written and verified */\n")

    def test_promotion_writes_a_new_path(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            produced = Path(scratch) / "candidate.c"
            produced.write_text("void f(void) {}\n")
            target = Path(scratch) / "new" / "8012ab0.c"
            batch_match.promote(produced, target)
            self.assertEqual(target.read_text(), "void f(void) {}\n")

    def test_an_existing_source_is_skipped_before_any_work(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            target = Path(scratch) / "8012ab0.c"
            target.write_text("x")
            self.assertFalse(batch_match.should_attempt(target))
            self.assertTrue(batch_match.should_attempt(Path(scratch) / "absent.c"))


class SourcePathTests(unittest.TestCase):
    def test_a_main_function_maps_to_its_address(self) -> None:
        path = batch_match.source_path(Path("/repo"), "main", 0x80012AB0)
        self.assertEqual(path, Path("/repo/src/main/80012ab0.c"))

    def test_an_overlay_function_maps_under_its_region(self) -> None:
        path = batch_match.source_path(Path("/repo"), "main_0012", 0x8012AD3C)
        self.assertEqual(path, Path("/repo/src/overlays/main_0012/8012ad3c.c"))


class SanitizeTests(unittest.TestCase):
    """m2c's `?` placeholder for an unseen symbol is not valid C.

    m2c cannot always tell an uncalled data symbol from a called function, so
    the sanitizer decides from the body: a declared name that is never
    followed by `(` anywhere in the function is data, not a callee.
    """

    def test_a_called_name_keeps_its_function_declaration(self) -> None:
        out = batch_match._sanitize(
            "? func_80010204();                                  /* extern */\n\n"
            "void func_80010938(void) {\n    func_80010204();\n}\n"
        )
        self.assertIn("void func_80010204();", out)
        self.assertIn("func_80010204();\n}", out)

    def test_an_uncalled_name_becomes_extern_data(self) -> None:
        """The failure this guards: an unknown symbol only ever assigned to,
        never called, must not be declared as a function -- assigning to a
        function name is not a valid lvalue."""

        out = batch_match._sanitize(
            "? D_80074778();                                     /* static */\n\n"
            "void func_80010AE0(s32 arg0) {\n    D_80074778 = arg0;\n}\n"
        )
        self.assertIn("extern s32 D_80074778;", out)
        self.assertNotIn("D_80074778()", out)

    def test_unknown_pointer_parameter_becomes_void_star(self) -> None:
        out = batch_match._sanitize(
            "? func_80014070(? *);                               /* static */\n\n"
            "void func_800128B4(void) {\n    func_80014070(0);\n}\n"
        )
        self.assertIn("void func_80014070(void *);", out)

    def test_unknown_local_variable_type_becomes_s32(self) -> None:
        out = batch_match._sanitize(
            "void func_800128B4(void) {\n    ? sp10;\n\n    func_80014070(&sp10);\n}\n"
        )
        self.assertIn("    s32 sp10;", out)

    def test_unknown_argument_list_becomes_empty_parens(self) -> None:
        out = batch_match._sanitize(
            "? func_80042610(?);                                 /* static */\n\n"
            "void func_80010938(void) {\n    func_80042610(0);\n}\n"
        )
        self.assertIn("func_80042610()", out)
        self.assertNotIn("(?)", out)

    def test_the_call_site_itself_is_left_untouched(self) -> None:
        out = batch_match._sanitize("void func_80010938(void) {\n    func_80042610(0);\n}\n")
        self.assertIn("func_80042610(0)", out)

    def test_unknown_function_pointer_local_becomes_s32(self) -> None:
        """The 65-128 bucket failure: m2c emits `? (*name)()` locals for
        callbacks (e.g. func_800100A0's ctor-loop `? (*temp_t0)();`), which
        no existing rule matches, so cpp fails on every such function."""

        out = batch_match._sanitize(
            "void func_800100A0(void) {\n    ? (*temp_t0)();\n    temp_t0();\n}\n"
        )
        self.assertIn("s32 (*temp_t0)();", out)
        self.assertNotIn("? (*temp_t0)()", out)

    def test_unknown_extern_data_declaration_becomes_s32(self) -> None:
        """`extern ? D_*;` is the same register-width-unknown data case as
        `? name;` locals, just spelled as an extern declaration."""

        out = batch_match._sanitize("extern ? D_800AF630;\nvoid f(void) {\n}\n")
        self.assertIn("extern s32 D_800AF630;", out)
        self.assertNotIn("extern ? ", out)

    def test_anonymous_function_pointer_parameter_becomes_s32(self) -> None:
        """`? (*)()` with no name — an anonymous callback parameter — is
        the residual shape the 65-128 re-sanitize found (func_8001BC6C,
        func_8001534C, func_8012F568). The named rule's `(\w+)` cannot
        match it, and the `? *` rule needs a literal `*` after `?`."""

        out = batch_match._sanitize(
            "void func_8001BC6C(? (*)(), s32);\nvoid f(void) {\n}\n"
        )
        self.assertIn("void func_8001BC6C(s32 (*)(), s32);", out)
        self.assertNotIn("? (*)()", out)

    def test_named_unknown_parameter_becomes_s32(self) -> None:
        """`? arg1` — m2c names the parameter but not its type — is the
        common residual (func_80020248, func_80045C94, func_8012F14C and
        ~20 more). Same register-width default as the bare form."""

        out = batch_match._sanitize(
            "void func_80020248(? arg1, s32 arg2, ? arg3) {\n}\n"
        )
        self.assertIn("void func_80020248(s32 arg1, s32 arg2, s32 arg3) {", out)
        self.assertNotIn("? arg", out)

    def test_function_definition_with_unknown_return_becomes_s32(self) -> None:
        """`? (*name(void))() {` is m2c's spelling of a definition whose
        return it reads as a function pointer (func_80042C90 returns the
        address func_80042D60). The body returns a register value, so a
        plain s32 definition compiles and generates identical code."""

        out = batch_match._sanitize("? (*func_80042C90(void))() {\n}\n")
        self.assertIn("s32 func_80042C90(void) {", out)

    def test_callback_prototype_keeps_its_shape_with_s32_return(self) -> None:
        """`? (*f(s32))(void *);` declares a callback factory (func_80131CA8
        stores the result in `s32 (*)()` and calls through it). Only the
        `?` becomes s32; the shape stays, so the call through the
        returned pointer is unchanged."""

        out = batch_match._sanitize(
            "? (*func_80131CF4(s32))(void *);\nvoid f(void) {\n}\n"
        )
        self.assertIn("s32 (*func_80131CF4(s32))(void *);", out)
        self.assertNotIn("? (*func_80131CF4", out)

    def test_null_macro_becomes_zero(self) -> None:
        """m2c emits NULL for null pointers (14 files in the 65-128
        bucket), but the Psy-Q chain runs cpp with -nostdinc so no hosted
        header provides it. NULL as a value is always the zero address,
        which 0 spells with identical codegen."""

        out = batch_match._sanitize(
            "s32 f(s32 *p) {\n    if (p == NULL) {\n        return NULL;\n    }\n    return 1;\n}\n"
        )
        self.assertIn("if (p == 0) {", out)
        self.assertIn("return 0;", out)
        self.assertNotIn("NULL", out)

    def test_deref_only_extern_data_becomes_pointer(self) -> None:
        """`*D = v` with no value-use means D holds an address
        (func_80042C90's `*D_8006CBBC = 0x107`). Declaring the pointer
        compiles; the s32 guess cannot dereference."""

        out = batch_match._sanitize(
            "extern s32 D_8006CBBC;\nvoid f(void) {\n    *D_8006CBBC = 0x107;\n}\n"
        )
        self.assertIn("extern s32 *D_8006CBBC;", out)

    def test_mixed_deref_and_assign_stays_s32(self) -> None:
        """`*D` plus a plain `D = v` is contradictory — no declaration
        satisfies both without knowing the layout. Leave it failing
        loudly for hand work rather than guess."""

        out = batch_match._sanitize(
            "extern s32 D;\nvoid f(void) {\n    D = 1;\n    *D = 2;\n}\n"
        )
        self.assertIn("extern s32 D;", out)
        self.assertNotIn("s32 *D;", out)

    def test_called_through_extern_becomes_function_pointer(self) -> None:
        """`(*D)(x)` calls through D, so D is a callback, not data.
        `s32 *D` would not compile there; `s32 (*D)()` does, with the
        same jalr sequence either way."""

        out = batch_match._sanitize(
            "extern s32 D;\nvoid f(void) {\n    (*D)(1);\n}\n"
        )
        self.assertIn("extern s32 (*D)();", out)

    def test_called_but_undeclared_func_gets_void_prototype(self) -> None:
        """m2c sometimes references a callee it never declares
        (D_80072780-class omissions in 4 files). A `void f();` unchecked
        prototype matches the convention used for seen-but-unknown
        callees."""

        out = batch_match._sanitize("void f(void) {\n    func_80072780(1);\n}\n")
        self.assertIn("void func_80072780();", out)

    def test_value_used_but_undeclared_data_gets_extern(self) -> None:
        out = batch_match._sanitize("void f(void) {\n    g(D_80072788);\n}\n")
        self.assertIn("extern s32 D_80072788;", out)

    def test_no_duplicate_decl_for_callback_prototype(self) -> None:
        """`s32 (*f(..))(..);` already declares f: the missing-symbol
        pass must recognise the `(*f` form as a declaration, or it
        would append a conflicting `void f();` and break a file that
        currently compiles."""

        src = "s32 (*func_80131CF4(s32))(void *);\nvoid f(void) {\n}\n"
        out = batch_match._sanitize(src)
        self.assertEqual(out.count("func_80131CF4"), 1)

    def test_no_decl_for_the_defined_function_itself(self) -> None:
        """A recursive call must not conjure a prototype that conflicts
        with the definition's return type."""

        src = "s32 target(s32 x) {\n    return target(x - 1);\n}\n"
        out = batch_match._sanitize(src)
        self.assertNotIn("void target();", out)
        self.assertNotIn("extern", out)

    def test_m2c_warning_lines_are_dropped(self) -> None:
        """m2c prints `Warning: ...` diagnostics into its stdout, which the
        harness captures as the candidate body (15+ files in the 0012
        <=64 bucket, e.g. `missing "jr $ra" in last block`). A warning is
        not C and always breaks compilation; drop those lines."""

        out = batch_match._sanitize(
            'Warning: missing "jr $ra" in last block of func_80128288 (initial).\n'
            "void func_80128288(void) {\n}\n"
        )
        self.assertNotIn("Warning:", out)
        self.assertIn("void func_80128288(void) {", out)

    def test_bare_unknown_parameter_becomes_s32(self) -> None:
        """A lone `?` parameter is an unknown word-sized argument, not the
        C89 unchecked-args `(?)` form, which keeps its own empty-parens
        mapping."""

        out = batch_match._sanitize(
            "void func_8002D4C8(?, ?);\nvoid f(void) {\n}\n"
        )
        self.assertIn("void func_8002D4C8(s32, s32);", out)
        self.assertNotIn("(?,", out)


class RegisterTests(unittest.TestCase):
    """A kill mid-sweep must not orphan a promoted match from the registry.

    Two live runs were killed by the environment partway through, and each
    time left matched sources on disk with no registry entry, requiring hand
    recovery. The registry is now written after every single promotion
    instead of once at the end, so a kill can only cost the in-flight
    function, never the ones already promoted.
    """

    def test_register_appends_and_persists_immediately(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            registry_path = Path(scratch) / "matches.json"
            registry = {"matches": []}
            entry = {"name": "func_80012AB0", "vram": 0x80012AB0, "size": 12,
                      "region": "main", "source": "src/main/80012ab0.c"}
            batch_match.register(registry, registry_path, entry)
            self.assertTrue(registry_path.is_file())
            reloaded = json.loads(registry_path.read_text())
            self.assertEqual(reloaded["matches"], [entry])

    def test_register_does_not_duplicate_an_existing_entry(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            registry_path = Path(scratch) / "matches.json"
            entry = {"name": "func_80012AB0", "vram": 0x80012AB0, "size": 12,
                      "region": "main", "source": "src/main/80012ab0.c"}
            registry = {"matches": [dict(entry)]}
            batch_match.register(registry, registry_path, entry)
            self.assertEqual(len(registry["matches"]), 1)

    def test_register_keeps_matches_sorted_by_region_then_vram(self) -> None:
        with tempfile.TemporaryDirectory() as scratch:
            registry_path = Path(scratch) / "matches.json"
            registry = {"matches": [
                {"name": "func_80012AB8", "vram": 0x80012AB8, "size": 4, "region": "main", "source": "a"},
            ]}
            batch_match.register(
                registry, registry_path,
                {"name": "func_80012AB0", "vram": 0x80012AB0, "size": 4, "region": "main", "source": "b"},
            )
            self.assertEqual([m["vram"] for m in registry["matches"]], [0x80012AB0, 0x80012AB8])


class OutcomeTests(unittest.TestCase):
    """Only an exact match is promoted; everything else leaves no trace."""

    def test_a_mismatch_is_not_promoted(self) -> None:
        self.assertFalse(batch_match.Outcome("func_x", "mismatch").promoted)

    def test_a_match_is_promoted(self) -> None:
        self.assertTrue(batch_match.Outcome("func_x", "match").promoted)

    def test_a_build_failure_is_not_promoted(self) -> None:
        self.assertFalse(batch_match.Outcome("func_x", "build-failed").promoted)


if __name__ == "__main__":
    unittest.main()
