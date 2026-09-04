#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
test_root="$(mktemp -d /tmp/musashi-m0-tests.XXXXXX)"
trap 'rm -rf -- "$test_root"' EXIT

cd "$repo_root"
python3 -m unittest discover -s tests -p 'test_*.py' -v

# SDL2 and OpenAL come from Homebrew when present. Override with
# MUSASHI_CMAKE_PREFIX to point CMake elsewhere; leave both unset to use only
# the system search path.
prefix="${MUSASHI_CMAKE_PREFIX:-}"
if [[ -z "$prefix" && -d /home/linuxbrew/.linuxbrew ]]; then
    prefix=/home/linuxbrew/.linuxbrew
fi
cmake -S . -B "$test_root/build" -DMUSASHI_BUILD_PC_PORT=ON \
    ${prefix:+-DCMAKE_PREFIX_PATH="$prefix"}
cmake --build "$test_root/build"
ctest --test-dir "$test_root/build" --output-on-failure

# Decomp-owned objects must not reference a Psy-Q callback whose return value
# truncates on 64-bit. PsyCross itself legitimately defines these, so only our
# archives are checked.
python3 tools/check_port_symbols.py \
    "$test_root/build/libmusashi_pc_port.a" \
    "$test_root/build/libmusashi_shared.a"
"$test_root/build/musashi_pc_smoke"
