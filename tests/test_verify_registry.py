from __future__ import annotations

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import verify_registry  # noqa: E402
from retail_common import RetailError  # noqa: E402

TARGETS = {
    "main": {"kind": "executable", "identity": "provenance/exe_identity.json"},
    "ov": {"kind": "blob", "file": "extracted/overlays/main/0007.bin", "base": 0x800CEDF8, "sha256": "ab" * 32},
}
MAIN_ENTRY = {"name": "func_80012AB0", "vram": 0x80012AB0, "size": 12, "region": "main", "source": "src/main/80012ab0.c"}
OV_ENTRY = {"name": "func_800CF3B0", "vram": 0x800CF3B0, "size": 88, "region": "ov", "source": "src/overlays/x.c"}


class PlanTests(unittest.TestCase):
    def test_build_links_at_the_function_address(self) -> None:
        build, _ = verify_registry.plan(MAIN_ENTRY, TARGETS, Path("/scratch/c.bin"))
        self.assertIn("--link-base", build)
        self.assertEqual(build[build.index("--link-base") + 1], "0x80012AB0")
        self.assertEqual(build[build.index("--symbol") + 1], "func_80012AB0")

    def test_executable_match_uses_no_blob_arguments(self) -> None:
        _, match = verify_registry.plan(MAIN_ENTRY, TARGETS, Path("/scratch/c.bin"))
        self.assertNotIn("--retail-file", match)
        self.assertEqual(match[match.index("--size") + 1], "0xC")
        self.assertEqual(match[match.index("--candidate") + 1], "/scratch/c.bin")

    def test_blob_match_carries_file_base_and_hash(self) -> None:
        _, match = verify_registry.plan(OV_ENTRY, TARGETS, Path("/scratch/c.bin"))
        self.assertEqual(match[match.index("--retail-file") + 1], "extracted/overlays/main/0007.bin")
        self.assertEqual(match[match.index("--base") + 1], "0x800CEDF8")
        self.assertEqual(match[match.index("--sha256") + 1], "ab" * 32)

    def test_an_unknown_region_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            verify_registry.plan({**MAIN_ENTRY, "region": "nowhere"}, TARGETS, Path("/s"))

    def test_an_unknown_target_kind_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            verify_registry.plan(MAIN_ENTRY, {"main": {"kind": "hologram"}}, Path("/s"))


if __name__ == "__main__":
    unittest.main()
