#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
test_root="$(mktemp -d /tmp/musashi-m0-tests.XXXXXX)"
trap 'rm -rf -- "$test_root"' EXIT

cd "$repo_root"

# SDL2 and OpenAL come from Homebrew when present. Override with
# MUSASHI_CMAKE_PREFIX to point CMake elsewhere; leave both unset to use only
# the system search path.
prefix="${MUSASHI_CMAKE_PREFIX:-}"
if [[ -z "$prefix" && -d /home/linuxbrew/.linuxbrew ]]; then
    prefix=/home/linuxbrew/.linuxbrew
fi

# Homebrew can leave the unversioned SDL2 include tree without SDL_main.h while
# a versioned keg keeps a complete CMake config. Prefer that config so the
# native smoke build in the Python tests still resolves usable headers; an
# explicit SDL2_DIR already in the environment wins over this discovery.
if [[ -z "${SDL2_DIR:-}" && -n "$prefix" ]]; then
    for candidate in "$prefix"/Cellar/sdl2-compat/*/lib/cmake/SDL2; do
        if [[ -e "$candidate/SDL2Config.cmake" ]]; then
            export SDL2_DIR="$candidate"
            break
        fi
    done
fi

python3 -m unittest discover -s tests -p 'test_*.py' -v

# A CMAKE_PREFIX_PATH search overrides an environment SDL2_DIR, and Homebrew's
# unversioned lib/cmake/SDL2 resolves its include directory to the incomplete
# unversioned tree. Pass the versioned config as a cache entry so the search
# cannot replace it.
cmake_args=(-DMUSASHI_BUILD_PC_PORT=ON)
if [[ -n "$prefix" ]]; then
    cmake_args+=(-DCMAKE_PREFIX_PATH="$prefix")
fi
if [[ -n "${SDL2_DIR:-}" ]]; then
    cmake_args+=(-DSDL2_DIR="$SDL2_DIR")
fi

cmake -S . -B "$test_root/build" "${cmake_args[@]}"
cmake --build "$test_root/build"
ctest --test-dir "$test_root/build" --output-on-failure

# Decomp-owned objects must not reference a Psy-Q callback whose return value
# truncates on 64-bit. PsyCross itself legitimately defines these, so only our
# archives are checked.
python3 tools/check_port_symbols.py \
    --allow-vsync-discard \
    "$test_root/build/libmusashi_pc_port.a" \
    "$test_root/build/libmusashi_shared.a"
"$test_root/build/musashi_pc_smoke"
