# Recovery: promotion-pending candidate bank

`staging/` is local-only (gitignored, never committed). It holds work that is
regenerable but expensive to recompute, so a wiped `/tmp` or a dead session
does not lose it.

## What is banked

- `staging/candidates/func_*.c` — m2c outputs passed through
  `tools/batch_match.py::_sanitize`, each compiling clean under
  `gcc -fsyntax-only -std=c89 -I include`. As of 2026-09-04: **1511 files**,
  every one naming a function absent from `provenance/matches.json`.
- `staging/pend_main.txt`, `staging/pend_0012.txt` — unmatched functions as
  `name size` pairs (main 1334, main_0012 2431 at time of writing).

## What these are NOT

They are not verified matches. C89-clean only means the harness can feed
them to the Psy-Q oracle. Nothing here goes to `src/` or the registry
without an oracle MATCH. See `docs/MATCHING.md`.

## Regenerate from scratch (if staging/ is lost)

Regen lists (needs `asm/` disassembly + registry):

```sh
python3 -c "
import sys; sys.path.insert(0,'tools')
import batch_match, json, os
reg = set(json.load(open('provenance/matches.json')).keys()) if os.path.exists('provenance/matches.json') else set()
for asm, out in [('asm/main.s','staging/pend_main.txt'),('asm/overlays/main_0012/main_0012.s','staging/pend_0012.txt')]:
    funcs = [f for f in batch_match.enumerate_functions(open(asm).read()) if f.name not in reg]
    open(out,'w').write(''.join(f'{f.name} {f.size}\n' for f in funcs))
"
```

Rebuild candidates for one slice (example: main, first 50 pending):

```sh
mkdir -p /tmp/re && head -50 staging/pend_main.txt | awk '{print $1}' > /tmp/re/list.txt
while read -r f; do python3 tools/m2c/m2c.py -f "$f" asm/main.s </dev/null > /tmp/re/"$f".c 2>/dev/null; done < /tmp/re/list.txt
for f in /tmp/re/*.c; do python3 tools/batch_match.py --help >/dev/null; done
```

Gate + bank (sanitize via the repo pipeline, keep C89-clean only):

```sh
printf 'import sys\nsys.path.insert(0, "tools")\nimport batch_match\nsrc = open(sys.argv[1]).read()\nif not src.startswith("#include"):\n    src = "#include \\"psx_types.h\\"\\n\\n" + src\nsys.stdout.write(batch_match._sanitize(src))\n' > /tmp/sanone.py
for f in /tmp/re/*.c; do python3 /tmp/sanone.py "$f" > /tmp/re.g.c 2>/dev/null \
  && gcc -fsyntax-only -std=c89 -Wno-comment -I include /tmp/re.g.c 2>/dev/null \
  && cp /tmp/re.g.c staging/candidates/$(basename $f); done
```

## Promote (needs working oracle)

Probe the oracle first — it currently fails (32-bit `cc1`/`cpp` die with
SIGSYS, exit 159, under this sandbox):

```sh
tools/psyq/gcc-2.8.1-psx/cc1 < /dev/null >/dev/null 2>&1; echo "cc1 rc=$?"
```

When `rc=0` stops being 159, run the promotion sweep per `docs/MATCHING.md`
(`tools/batch_match.py --asm ... --region ...`). The sweep regenerates its
own candidates; the bank then serves as a cross-check, not the input.

## Operational notes (learned 2026-09-04)

- `/tmp` is shared and volatile: files from earlier in the day vanished
  mid-session (a second agent appears active in `/tmp`). Bank gated passes
  into `staging/` promptly; treat `/tmp` as scratch only.
- `tools/batch_match.py::_sanitize` is the single sanitizer. Test-first
  additions live in `tests/test_batch_match.py::SanitizeTests`.
