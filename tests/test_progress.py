from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "tools"
sys.path.insert(0, str(TOOLS))

import progress  # noqa: E402
from retail_common import RetailError  # noqa: E402


_next_vram = [0x80012AB0]


def entry(name: str, size: int, **kw):
    """A well-formed entry. Each gets a distinct vram, since repeats are refused."""
    _next_vram[0] += 0x10
    base = {
        "name": name,
        "vram": _next_vram[0],
        "size": size,
        "source": f"src/main/{name}.c",
        "region": "main",
    }
    base.update(kw)
    return base


class SummaryTests(unittest.TestCase):
    """Progress is counted in functions of real C, never a diff percentage.

    A project counting `objdiff` match rate can report 100% while the C is
    verbatim __asm__ transcription; one such project publicly retracted exactly
    that figure. Only bytes proven to rebuild from C are counted here.
    """

    def test_counts_functions_and_bytes(self) -> None:
        summary = progress.summarise([entry("a", 0xC), entry("b", 0x20)])
        self.assertEqual(summary["function_count"], 2)
        self.assertEqual(summary["matched_bytes"], 0xC + 0x20)

    def test_groups_by_region(self) -> None:
        summary = progress.summarise(
            [entry("a", 4, region="main"), entry("b", 4, region="main_0012")]
        )
        self.assertEqual(summary["by_region"], {"main": 1, "main_0012": 1})

    def test_entry_without_a_region_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            progress.summarise([{"name": "a", "vram": 0, "size": 4, "source": "x.c"}])

    def test_empty_registry_summarises_to_zero(self) -> None:
        summary = progress.summarise([])
        self.assertEqual(summary["function_count"], 0)
        self.assertEqual(summary["matched_bytes"], 0)

    def test_a_non_positive_size_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            progress.summarise([entry("a", 0, region="main")])

    def test_duplicate_addresses_are_refused(self) -> None:
        """The same function counted twice would inflate progress."""
        with self.assertRaises(RetailError):
            progress.summarise([entry("a", 4, vram=0x80001000), entry("b", 4, vram=0x80001000)])


class LoadTests(unittest.TestCase):
    def test_reads_a_registry_file(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "matches.json"
            path.write_text(json.dumps({"schema": 1, "matches": [entry("a", 4, region="main")]}))
            self.assertEqual(len(progress.load_registry(path)), 1)

    def test_missing_registry_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            progress.load_registry(Path("/nonexistent/matches.json"))

    def test_a_registry_without_a_matches_list_is_refused(self) -> None:
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "matches.json"
            path.write_text(json.dumps({"schema": 1}))
            with self.assertRaises(RetailError):
                progress.load_registry(path)


class TrivialityTests(unittest.TestCase):
    """A count that treats a two-instruction stub as a function will mislead.

    Most functions matched early are setters, getters and empty stubs. They are
    genuine matches, but reporting only a total invites the same inflation the
    rr-decomp retraction was about, so stubs are counted separately.
    """

    def test_a_two_instruction_function_is_trivial(self) -> None:
        summary = progress.summarise([entry("stub", 8)])
        self.assertEqual(summary["trivial_count"], 1)
        self.assertEqual(summary["substantive_count"], 0)

    def test_a_larger_function_is_substantive(self) -> None:
        summary = progress.summarise([entry("real", 0x58)])
        self.assertEqual(summary["trivial_count"], 0)
        self.assertEqual(summary["substantive_count"], 1)

    def test_the_threshold_is_explicit(self) -> None:
        self.assertEqual(progress.TRIVIAL_MAX_BYTES, 8)

    def test_counts_partition_the_total(self) -> None:
        summary = progress.summarise([entry("a", 8), entry("b", 0x20), entry("c", 8)])
        self.assertEqual(
            summary["trivial_count"] + summary["substantive_count"], summary["function_count"]
        )


if __name__ == "__main__":
    unittest.main()
