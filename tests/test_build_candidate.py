from __future__ import annotations

import struct
import subprocess
import sys
import unittest
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "tools"
sys.path.insert(0, str(TOOLS))

import build_candidate  # noqa: E402
from retail_common import RetailError  # noqa: E402


class ToolchainTests(unittest.TestCase):
    """The PSY-Q release an executable was built with implies its ASPSX version.

    Pairings come from the PSY-Q/compiler/ASPSX release table; getting the ASPSX
    version wrong reproduces the wrong macro expansions and silently prevents a
    match, so the mapping is pinned rather than passed in loosely.
    """

    def test_known_toolchain_carries_its_aspsx_version(self) -> None:
        self.assertEqual(build_candidate.resolve_toolchain("gcc-2.7.2-psx").aspsx_version, "2.56")
        self.assertEqual(build_candidate.resolve_toolchain("gcc-2.7.2-cdk-psx").aspsx_version, "2.67")

    def test_unknown_toolchain_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            build_candidate.resolve_toolchain("clang-19")

    def test_available_names_are_reported_in_the_error(self) -> None:
        with self.assertRaises(RetailError) as caught:
            build_candidate.resolve_toolchain("nope")
        self.assertIn("gcc-2.7.2-psx", str(caught.exception))


class SymbolTableTests(unittest.TestCase):
    def test_parses_sized_text_symbols(self) -> None:
        output = "00000000 00000018 T add2\n00000018 00000040 T mul3\n"
        symbols = build_candidate.parse_nm_symbols(output)
        self.assertEqual(symbols["add2"], (0x0, 0x18))
        self.assertEqual(symbols["mul3"], (0x18, 0x40))

    def test_symbol_without_a_size_is_recorded_as_unsized(self) -> None:
        symbols = build_candidate.parse_nm_symbols("00000000 T bare\n")
        self.assertEqual(symbols["bare"], (0x0, None))

    def test_non_text_symbols_are_ignored(self) -> None:
        output = (
            "00000000 00000018 T keep\n"
            "00000000 00000004 D data_sym\n"
            "         U undefined_sym\n"
            "00000000 00000008 B bss_sym\n"
        )
        symbols = build_candidate.parse_nm_symbols(output)
        self.assertEqual(list(symbols), ["keep"])

    def test_local_text_symbols_are_kept(self) -> None:
        symbols = build_candidate.parse_nm_symbols("00000020 00000010 t static_helper\n")
        self.assertEqual(symbols["static_helper"], (0x20, 0x10))

    def test_blank_and_malformed_lines_are_skipped(self) -> None:
        symbols = build_candidate.parse_nm_symbols("\n\ngarbage\n00000000 00000004 T ok\n")
        self.assertEqual(list(symbols), ["ok"])


class SliceTests(unittest.TestCase):
    SECTION = struct.pack("<8I", *range(8))

    def test_slices_the_symbol_range(self) -> None:
        got = build_candidate.slice_symbol(self.SECTION, 0x8, 0x8)
        self.assertEqual(got, struct.pack("<2I", 2, 3))

    def test_range_past_section_end_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            build_candidate.slice_symbol(self.SECTION, 0x18, 0x20)

    def test_zero_size_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            build_candidate.slice_symbol(self.SECTION, 0x0, 0)

    def test_unaligned_size_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            build_candidate.slice_symbol(self.SECTION, 0x0, 6)

    def test_unaligned_offset_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            build_candidate.slice_symbol(self.SECTION, 0x2, 0x4)


class SubprocessInvariantTests(unittest.TestCase):
    """Child stdin must be explicit, never inherited.

    maspsx picks its input source with sys.stdin.isatty(): with a non-tty stdin
    it calls sys.stdin.readlines() and blocks forever if the parent supplies no
    input. Inheriting stdin therefore makes the harness work interactively and
    hang under CI. Both helpers also carry a timeout so a hang fails loudly.
    """

    def test_run_closes_child_stdin_and_sets_a_timeout(self) -> None:
        with mock.patch.object(build_candidate.subprocess, "run") as runner:
            runner.return_value = subprocess.CompletedProcess([], 0, b"", b"")
            build_candidate._run(["/bin/true"], "probe")
        _, kwargs = runner.call_args
        self.assertEqual(kwargs["stdin"], subprocess.DEVNULL)
        self.assertIsNotNone(kwargs.get("timeout"))

    def test_capture_closes_child_stdin_and_sets_a_timeout(self) -> None:
        with mock.patch.object(build_candidate.subprocess, "run") as runner:
            runner.return_value = subprocess.CompletedProcess([], 0, "", "")
            build_candidate._capture(["/bin/true"], "probe")
        _, kwargs = runner.call_args
        self.assertEqual(kwargs["stdin"], subprocess.DEVNULL)
        self.assertIsNotNone(kwargs.get("timeout"))

    def test_timeout_is_reported_as_a_retail_error(self) -> None:
        with mock.patch.object(build_candidate.subprocess, "run") as runner:
            runner.side_effect = subprocess.TimeoutExpired(cmd=["x"], timeout=1)
            with self.assertRaises(RetailError) as caught:
                build_candidate._run(["/bin/true"], "probe")
        self.assertIn("timed out", str(caught.exception).lower())


class CommandTests(unittest.TestCase):
    def test_cc1_command_carries_optimisation_and_gp_flags(self) -> None:
        command = build_candidate.cc1_command(
            Path("/tc/cc1"), Path("in.i"), Path("out.s"), optimization="-O2", gp="-G0"
        )
        self.assertIn("-O2", command)
        self.assertIn("-G0", command)
        self.assertIn("-mips1", command)
        self.assertIn("-mcpu=3000", command)
        self.assertEqual(command[0], "/tc/cc1")

    def test_maspsx_command_pins_the_aspsx_version_and_runs_the_assembler(self) -> None:
        command = build_candidate.maspsx_command(
            Path("/m/maspsx.py"),
            Path("in.s"),
            Path("out.o"),
            aspsx_version="2.56",
            gnu_as=Path("/usr/bin/mips-linux-gnu-as"),
        )
        self.assertIn("--aspsx-version=2.56", command)
        self.assertIn("--run-assembler", command)
        self.assertIn("-EL", command)

    def test_cpp_command_defines_the_psx_target_macros(self) -> None:
        command = build_candidate.cpp_command(Path("/tc/cpp"), Path("in.c"), includes=[Path("/sdk")])
        self.assertIn("-undef", command)
        self.assertIn("-Dmips", command)
        self.assertIn("-I/sdk", command)


if __name__ == "__main__":
    unittest.main()
