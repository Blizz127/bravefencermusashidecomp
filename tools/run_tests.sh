#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
test_root="$(mktemp -d /tmp/musashi-m0-tests.XXXXXX)"
trap 'rm -rf -- "$test_root"' EXIT

cd "$repo_root"
python3 -m unittest discover -s tests -p 'test_*.py' -v

cmake -S . -B "$test_root/build" -DMUSASHI_BUILD_PC_PORT=ON
cmake --build "$test_root/build"
ctest --test-dir "$test_root/build" --output-on-failure
"$test_root/build/musashi_pc_smoke"
