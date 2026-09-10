"""Compiled selected-ROM A0:39 InitHeap owner and checked-RAM tests."""

from pathlib import Path
import hashlib
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
ROM = Path("/var/home/blizz/Projects/xenogears-decomp-ai/disc/scph5500.bin")
EXPECTED_WORDS = bytes.fromhex(
    "01a0013c82700500009024ac80780e0021c08f00000080ac"
    "0400192701a0013c089039ac01a0013c049025ac01a0013c"
    "0800e0030c9020ac"
)


class BiosHeapTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="musashi-bios-heap-")
        cls.addClassCleanup(cls.temp.cleanup)
        cls.probe = Path(cls.temp.name) / "probe"
        subprocess.run([
            "cc", "-std=c99", "-Wall", "-Wextra", "-Werror",
            "-I", str(ROOT / "pc_port/include"),
            str(ROOT / "tests/bios_heap_probe.c"),
            str(ROOT / "pc_port/bios_heap.c"),
            str(ROOT / "pc_port/boot_memory.c"),
            "-lcrypto", "-o", str(cls.probe),
        ], check=True, stdin=subprocess.DEVNULL, timeout=30)

    def test_compiled_owner_probe(self):
        result = subprocess.run([str(self.probe)], check=True, text=True,
                                capture_output=True, timeout=10)
        self.assertEqual(result.stdout.strip(), "BIOS_HEAP_PASS")

    @staticmethod
    def _rom_words():
        if not ROM.is_file():
            raise unittest.SkipTest("selected licensed ROM is unavailable")
        data = ROM.read_bytes()
        words = data[0x1E24:0x1E5C]
        if len(words) != 56:
            raise AssertionError("selected ROM is too short for A0:39")
        if hashlib.sha256(words).hexdigest() != (
                "61509bda07b9609ebdd2cae2fdf9ab2cf154b62ab2bf6f9892b96b672f657c4b"):
            raise AssertionError("selected ROM A0:39 span hash mismatch")
        if words != EXPECTED_WORDS:
            raise AssertionError("selected ROM A0:39 bytes mismatch")
        return [int.from_bytes(words[index:index + 4], "little")
                for index in range(0, len(words), 4)]

    @staticmethod
    def _mips_init_heap(words, base, size):
        """Interpret only the pinned 14-word A0:39 leaf and its delay slot."""
        regs = [0] * 32
        regs[4] = base & 0xffffffff  # a0
        regs[5] = size & 0xffffffff  # a1
        writes = {}
        for word in words:
            opcode = (word >> 26) & 0x3f
            rs = (word >> 21) & 0x1f
            rt = (word >> 16) & 0x1f
            rd = (word >> 11) & 0x1f
            funct = word & 0x3f
            imm = word & 0xffff
            signed_imm = imm - 0x10000 if imm & 0x8000 else imm
            if opcode == 0x0f:  # LUI
                regs[rt] = (imm << 16) & 0xffffffff
            elif opcode == 0x00 and funct == 0x02:  # SRL
                regs[rd] = (regs[rt] >> ((word >> 6) & 0x1f)) & 0xffffffff
            elif opcode == 0x00 and funct == 0x00:  # SLL
                regs[rd] = (regs[rt] << ((word >> 6) & 0x1f)) & 0xffffffff
            elif opcode == 0x00 and funct == 0x21:  # ADDU
                regs[rd] = (regs[rs] + regs[rt]) & 0xffffffff
            elif opcode == 0x00 and funct == 0x08:  # JR; next word is delay
                pass
            elif opcode == 0x23:  # LW is not present in this selected leaf
                raise AssertionError("unexpected LW in selected A0:39 leaf")
            elif opcode == 0x2b:  # SW
                address = (regs[rs] + signed_imm) & 0xffffffff
                writes[address] = regs[rt] & 0xffffffff
            elif opcode == 0x09:  # ADDIU
                regs[rt] = (regs[rs] + signed_imm) & 0xffffffff
            else:
                raise AssertionError(f"unsupported selected opcode {word:08x}")
            regs[0] = 0
        return {
            "cursor": writes[0xa0009000],
            "preferred": writes[0xa0009004],
            "end": writes[0xa0009008],
            "lazy": writes[0xa000900c],
            "header": writes[base & 0xffffffff],
            "scan": 0x80123450,
            "current": 0x80123454,
        }

    def test_compiled_owner_matches_independent_selected_leaf(self):
        words = self._rom_words()
        cases = [(0x80001000, size) for size in (0, 1, 3, 4, 0x800, 0xffffffff)]
        cases.extend(((0x801ff800, 0x800), (0x801ff800, 0xffffffff)))
        for base, size in cases:
            with self.subTest(base=hex(base), size=hex(size)):
                result = subprocess.run(
                    [str(self.probe), hex(base), hex(size)], check=True,
                    text=True, capture_output=True, timeout=10)
                actual = dict(item.split("=")
                              for item in result.stdout.strip().split())
                expected = self._mips_init_heap(words, base, size)
                self.assertEqual(
                    {"cursor": int(actual["cursor"], 16),
                     "preferred": int(actual["preferred"], 16),
                     "end": int(actual["end"], 16),
                     "lazy": int(actual["lazy"], 10),
                     "header": int(actual["header"], 16),
                     "scan": int(actual["scan"], 16),
                     "current": int(actual["current"], 16)},
                    expected)

    def test_selected_rom_service_words_if_available(self):
        self._rom_words()


if __name__ == "__main__":
    unittest.main()
