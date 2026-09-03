from __future__ import annotations

import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


@unittest.skipUnless(shutil.which("cmake") and shutil.which("ctest"), "CMake/CTest unavailable")
class NativeSmokeTests(unittest.TestCase):
    def test_linux_native_smoke_uses_shared_decomp_source(self) -> None:
        self.assertIn("src/shared/runtime_api.c", (ROOT / "CMakeLists.txt").read_text(encoding="utf-8"))
        with tempfile.TemporaryDirectory(prefix="musashi-native-test-") as temp:
            build = Path(temp) / "build"
            subprocess.run(
                ["cmake", "-S", str(ROOT), "-B", str(build), "-DMUSASHI_BUILD_PC_PORT=ON"],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
            )
            subprocess.run(
                ["cmake", "--build", str(build)],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
            )
            subprocess.run(
                ["ctest", "--test-dir", str(build), "--output-on-failure"],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
            )
            completed = subprocess.run(
                [str(build / "musashi_pc_smoke")],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
            )
            self.assertIn("platform=linux", completed.stdout)
            self.assertIn("le32=0x78563412", completed.stdout)


if __name__ == "__main__":
    unittest.main()
