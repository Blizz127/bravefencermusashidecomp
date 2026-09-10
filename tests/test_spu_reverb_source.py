"""Actual mode4 reverb source execution with synthetic CPU/owner state."""
from pathlib import Path
import hashlib
import re
import struct
import subprocess
import tempfile
import pytest
from test_bios_event_callbacks import _generate_formatter_includes

ROOT = Path(__file__).resolve().parents[1]


def test_spu_reverb_source():
    exe = ROOT / "extracted/disc/files/SLUS_007.26"
    if not exe.exists():
        pytest.skip("pinned licensed EXE unavailable")
    image = exe.read_bytes()
    assert hashlib.sha256(image).hexdigest() == (
        "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a")
    with tempfile.TemporaryDirectory(prefix="musashi-spu-reverb-source-") as temp:
        generated = Path(temp) / "generated"
        generated.mkdir()
        _generate_formatter_includes(generated)
        for address, count in (("8002c8f4", 214), ("8003c598", 229),
                               ("8003be24", 20), ("8003b3d0", 35),
                               ("8002d1f0", 20), ("8003b45c", 318),
                               ("8003b954", 308), ("8003b280", 52)):
            words = re.findall(r"0x([0-9a-fA-F]{8})u",
                               (generated / f"{address}_words.inc").read_text())
            assert len(words) == count
            actual = struct.pack(f"<{count}I", *(int(w, 16) for w in words))
            offset = int(address, 16) - 0x80010000 + 0x800
            assert image[offset:offset + len(actual)] == actual
        probe = Path(temp) / "probe"
        subprocess.run([
            "cc", "-std=c99", "-Wall", "-Wextra", "-Werror", "-O2",
            "-Wno-parentheses", "-DMUSASHI_NATIVE_WORD_CLEAR_BINDING",
            "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
            "-I", str(ROOT / "include"), "-I", str(ROOT / "pc_port/include"),
            "-I", str(generated), str(ROOT / "tests/spu_reverb_source_probe.c"),
            *[str(ROOT / "pc_port" / name) for name in (
                "boot_memory.c", "callback_bindings.c", "bios_events.c",
                "bios_kernel.c", "irq_controller.c", "dma_controller.c", "spu_cd_audio.c")],
            str(ROOT / "src/main/80042c64.c"), "-lcrypto", "-o", str(probe),
        ], check=True, timeout=30)
        result = subprocess.run([str(probe), str(exe)], check=False, timeout=30,
                                capture_output=True, text=True)
        assert result.returncode == 0, result.stdout + result.stderr
        assert result.stdout.count("REVERB_WRITE ") == 36
        assert result.stdout.endswith("SPU_REVERB_SOURCE_PASS fixture_only=1\n")
