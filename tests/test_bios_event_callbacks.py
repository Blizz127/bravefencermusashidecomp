from pathlib import Path
import re
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]
WORD_INCLUDE = re.compile(r'#include "([^"]+_words\.inc)"')
WORD_EXPORT = re.compile(r'MUSASHI_NATIVE_MIPS_WORD\(0x[0-9A-Fa-f]{8}\)')
ASM_WORD = re.compile(r'"\.word 0x[0-9A-Fa-f]{8}')
ASM_LABELS = {
    "80044670_full_words.inc": "func_80044670",
    "80043b9c_words.inc": "func_80043B9C",
}


def _source_for_include(name):
    title = re.fullmatch(r"([0-9a-f]{8})_(sc01_0000|sc02_0031)_words.inc", name)
    if title:
        return ROOT / f"src/overlays/{title[2]}/{title[1]}.c"
    if name == "800cf02c_overlay_words.inc":
        return ROOT / "src/overlays/main_0007/800cf02c.c"
    overlay = re.fullmatch(r"([0-9a-f]{8})_overlay([0-9]{4})_words.inc", name)
    if overlay:
        source = ROOT / f"src/overlays/main_{overlay[2]}/{overlay[1]}.c"
        assert source.is_file(), source
        return source
    if name in ASM_LABELS:
        return ROOT / "asm/main.s"
    # CMake writes 80044670_words.inc from the 25-word prefix; the full
    # 263-word body is 80044670_full_words.inc from asm/main.s.
    if name == "80044670_words.inc":
        return ROOT / "src/main" / "80044670_prefix.c"
    stem = name[:-len("_words.inc")]
    direct = ROOT / "src/main" / f"{stem}.c"
    if direct.is_file():
        return direct
    prefix = ROOT / "src/main" / f"{stem}_prefix.c"
    if prefix.is_file():
        return prefix
    if name in ASM_LABELS:
        return ROOT / "asm/main.s"
    raise AssertionError(f"no audited source for {name}")


def _expected_words(source, include_name):
    if include_name in ASM_LABELS:
        text = source.read_text()
        label = ASM_LABELS[include_name]
        start = text.index(f"glabel {label}")
        end = text.index(f"endlabel {label}", start)
        return len(re.findall(r"/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/",
                              text[start:end]))
    source_text = source.read_text()
    exported = WORD_EXPORT.findall(source_text)
    return len(exported) or len(ASM_WORD.findall(source_text))


def _generate_formatter_includes(output):
    formatter = ROOT / "pc_port/mips_formatter.c"
    for name in WORD_INCLUDE.findall(formatter.read_text()):
        source = _source_for_include(name)
        expected = _expected_words(source, name)
        assert expected > 0, f"empty audited source for {name}"
        subprocess.run([
            sys.executable,
            str(ROOT / "tools/extract_asm_words.py"),
            str(source),
            str(output / name),
            "--expected-words", str(expected),
            *((["--asm-label", ASM_LABELS[name]]) if name in ASM_LABELS else []),
        ], check=True, timeout=30)


def test_bios_event_callback_executor_exact_targets_and_refusals():
    with tempfile.TemporaryDirectory(prefix="musashi-bios-event-callback-") as temp:
        probe = Path(temp) / "probe"
        generated = Path(temp) / "generated"
        generated.mkdir()
        _generate_formatter_includes(generated)
        subprocess.run([
            "cc", "-std=c99", "-Wall", "-Wextra", "-Werror",
            "-O2", "-Wno-parentheses",
            "-ffunction-sections", "-fdata-sections",
            "-Wl,--gc-sections",
            "-I", str(ROOT / "include"),
            "-I", str(ROOT / "pc_port/include"),
            "-I", str(generated),
            str(ROOT / "tests/bios_event_callback_probe.c"),
            str(ROOT / "pc_port/boot_memory.c"),
            str(ROOT / "pc_port/mips_formatter.c"),
            str(ROOT / "pc_port/bios_events.c"),
            "-lcrypto",
            "-o", str(probe),
        ], check=True, timeout=30)
        subprocess.run([str(probe)], check=True, timeout=10)
