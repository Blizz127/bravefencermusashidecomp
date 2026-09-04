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
