#!/bin/sh
# Fetch everything needed to build matching candidates: the candidate compilers
# and the maspsx assembler shim.
#
# The compilers are GPL rebuilds of old GCC from decompals/old-gcc, not Sony
# Psy-Q binaries, so they are freely redistributable. Nothing here is tracked,
# because it is large and this script reproduces it exactly.
#
# The registry in tools/build_candidate.py pairs each compiler with its ASPSX
# assembler version; keep the two in step when adding a compiler here.
#
# Run from the repository root:
#   ./tools/fetch_toolchains.sh [compiler-destination]   (default: tools/psyq)

set -eu

BASE="https://github.com/decompals/old-gcc/releases/download"
DEST="${1:-tools/psyq}"

# maspsx reproduces ASPSX macro expansion between cc1 and GNU as. Pinned so a
# change in its expansion behaviour cannot silently alter match results.
MASPSX_REPO="https://github.com/mkst/maspsx.git"
MASPSX_COMMIT="746b895f02929ecd148af7b1f4ff05b69f973878"
MASPSX_DIR="tools/maspsx"

mkdir -p "$DEST"

fetch_maspsx() {
    if [ -f "$MASPSX_DIR/maspsx.py" ]; then
        echo "maspsx already present"
        return
    fi
    echo "fetching maspsx"
    git clone --quiet "$MASPSX_REPO" "$MASPSX_DIR"
    git -C "$MASPSX_DIR" checkout --quiet "$MASPSX_COMMIT"
}

fetch_maspsx

fetch() {
    name="$1"
    url="$2"
    if [ -x "$DEST/$name/cc1" ]; then
        echo "$name already present"
        return
    fi
    echo "fetching $name"
    mkdir -p "$DEST/$name"
    tmp="$(mktemp)"
    if curl -fsSL "$url" -o "$tmp"; then
        tar xzf "$tmp" -C "$DEST/$name"
        rm -f "$tmp"
    else
        rm -f "$tmp"
        echo "ERROR: failed to download $name from $url" >&2
        return 1
    fi
}

# PSY-Q 3.5
fetch gcc-2.6.0-psx     "$BASE/0.12/gcc-2.6.0-psx.tar.gz"
# PSY-Q 4.0
fetch gcc-2.7.2-psx     "$BASE/0.13/gcc-2.7.2-psx.tar.gz"
# PSY-Q 4.1
fetch gcc-2.7.2-cdk-psx "$BASE/0.15/gcc-2.7.2-cdk.tar.gz"
# PSY-Q 4.3
fetch gcc-2.8.0-psx     "$BASE/0.12/gcc-2.8.0-psx.tar.gz"
# PSY-Q 4.4
fetch gcc-2.8.1-psx     "$BASE/0.12/gcc-2.8.1-psx.tar.gz"
# PSY-Q 4.5
fetch gcc-2.91.66-psx   "$BASE/0.12/gcc-2.91.66-psx.tar.gz"

echo
echo "compilers under $DEST:"
for dir in "$DEST"/*/; do
    name="$(basename "$dir")"
    if [ -x "$dir/cc1" ]; then
        echo "  $name"
    else
        echo "  $name (INCOMPLETE: no cc1)"
    fi
done
echo "assembler shim: $MASPSX_DIR @ $MASPSX_COMMIT"
