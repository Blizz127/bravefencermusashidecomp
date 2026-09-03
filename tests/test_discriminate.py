from __future__ import annotations

import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "tools"
sys.path.insert(0, str(TOOLS))

import discriminate  # noqa: E402
from retail_common import RetailError  # noqa: E402


RETAIL = 264  # 0x108, 66 words


def result(toolchain: str, size: int | None, ratio: float | None, opt: str = "-O2"):
    return discriminate.CandidateResult(
        toolchain=toolchain, optimization=opt, gp="-G0", size_bytes=size, ratio=ratio
    )


class ComparabilityTests(unittest.TestCase):
    def test_matching_size_is_comparable(self) -> None:
        self.assertTrue(result("a", RETAIL, 0.5).comparable)

    def test_differing_size_is_not_comparable(self) -> None:
        self.assertFalse(result("a", RETAIL + 4, None).comparable)

    def test_failed_build_is_not_comparable(self) -> None:
        self.assertFalse(result("a", None, None).comparable)


class SummaryTests(unittest.TestCase):
    """A toolchain that cannot emit the retail instruction count is eliminated.

    Instruction count is a structural check that does not depend on the
    decompiled C being byte-perfect: if a compiler cannot produce a function of
    the right length from this source at any setting, it did not build it.
    """

    def test_toolchain_reaching_retail_size_survives(self) -> None:
        summary = discriminate.summarise(
            [result("keeper", RETAIL, 0.35), result("keeper", RETAIL + 4, None, "-O1")], RETAIL
        )
        self.assertIn("keeper", summary["surviving"])
        self.assertNotIn("keeper", summary["eliminated"])

    def test_toolchain_never_reaching_retail_size_is_eliminated(self) -> None:
        summary = discriminate.summarise(
            [result("gone", RETAIL + 4, None), result("gone", RETAIL + 8, None, "-O1")], RETAIL
        )
        self.assertIn("gone", summary["eliminated"])
        self.assertNotIn("gone", summary["surviving"])

    def test_a_failed_build_alone_does_not_rescue_a_toolchain(self) -> None:
        summary = discriminate.summarise([result("gone", None, None)], RETAIL)
        self.assertIn("gone", summary["eliminated"])

    def test_best_ratio_and_its_toolchain_are_reported(self) -> None:
        summary = discriminate.summarise(
            [result("low", RETAIL, 0.20), result("high", RETAIL, 0.80)], RETAIL
        )
        self.assertEqual(summary["best"], ("high", 0.80))

    def test_spread_is_the_gap_between_best_and_worst_comparable(self) -> None:
        summary = discriminate.summarise(
            [result("low", RETAIL, 0.20), result("high", RETAIL, 0.80)], RETAIL
        )
        self.assertAlmostEqual(summary["spread"], 0.60, places=6)

    def test_a_toolchain_is_scored_by_its_best_configuration(self) -> None:
        summary = discriminate.summarise(
            [result("t", RETAIL, 0.20, "-O1"), result("t", RETAIL, 0.90, "-O2")], RETAIL
        )
        self.assertEqual(summary["best"], ("t", 0.90))

    def test_no_elimination_is_reported_as_non_discriminating(self) -> None:
        summary = discriminate.summarise(
            [result("a", RETAIL, 0.50), result("b", RETAIL, 0.50)], RETAIL
        )
        self.assertFalse(summary["discriminating"])

    def test_any_elimination_counts_as_discriminating(self) -> None:
        summary = discriminate.summarise(
            [result("a", RETAIL, 0.50), result("b", RETAIL + 4, None)], RETAIL
        )
        self.assertTrue(summary["discriminating"])

    def test_empty_results_are_refused(self) -> None:
        with self.assertRaises(RetailError):
            discriminate.summarise([], RETAIL)


class OrderingTests(unittest.TestCase):
    def test_surviving_toolchains_are_ordered_by_descending_ratio(self) -> None:
        summary = discriminate.summarise(
            [
                result("mid", RETAIL, 0.50),
                result("top", RETAIL, 0.90),
                result("bottom", RETAIL, 0.10),
            ],
            RETAIL,
        )
        self.assertEqual(summary["surviving"], ["top", "mid", "bottom"])


if __name__ == "__main__":
    unittest.main()
