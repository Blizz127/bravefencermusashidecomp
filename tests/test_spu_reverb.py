"""Real owned reverb RAM, unknown-history, signal and transaction checks."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def test_spu_reverb():
    with tempfile.TemporaryDirectory(prefix="musashi-spu-reverb-") as temp:
        probe = Path(temp) / "probe"
        subprocess.run([
            "cc", "-std=c99", "-Wall", "-Wextra", "-Werror", "-O2",
            "-I", str(ROOT / "pc_port/include"),
            str(ROOT / "tests/spu_reverb_probe.c"),
            str(ROOT / "pc_port/spu_cd_audio.c"), "-o", str(probe),
        ], check=True, timeout=30)
        result = subprocess.run([str(probe)], check=True, timeout=30,
                                capture_output=True, text=True)
        assert result.stdout == "SPU_REVERB_PASS\n"
