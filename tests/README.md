# miniRT stress tests

Run from the repository root on Linux with GCC, Python 3, Valgrind, and X11/MiniLibX development libraries available:

```sh
make all bonus
python3 tests/run_stress.py
python3 tests/run_extended.py
python3 tests/run_app.py --gui
python3 tests/run_gui_alloc.py
```

The last two commands open and operate test windows on the current X display.
Run GUI suites sequentially so they do not interfere with one another's focus.
For CLI tests without GUI interaction, run `python3 tests/run_app.py`.

Builds, generated scenes, PPM images, and raw logs go to `/tmp/minirt-stress`.
Override that location with `MINIRT_TEST_OUT` (use an absolute path).
The checked-in `artifacts/` directory records the completed test session; rerunning
scripts refreshes temporary results, not those archived snapshots.

## Coverage

- `stress_harness.c`: production loader, intersections, shading, renderer, allocation
  failures, descriptor counts, repeated cleanup, random geometry/reference checks.
- `run_stress.py`: deterministic malformed/binary/truncated/numeric scene corpus,
  two build variants under sanitizers and Valgrind. Nonzero exit on failures.
- `run_extended.py`: 20,000 extra shapes/lights, 18 offscreen renders, GCC static
  analysis, fresh builds and no-relink verification.
- `gui_driver.c`: discovers only newly created miniRT windows, sends X11 keyboard,
  focus, expose, map/unmap, F11 fullscreen and close events, checks image changes and process exits.
- `run_app.py`: builds real executables and tests CLI failures, display failure,
  GUI interaction, repeated fullscreen transitions, rendered fullscreen edges, Escape, WM_DELETE_WINDOW, sanitizer and Valgrind shutdown.
- `gui_alloc_harness.c` / `run_gui_alloc.py`: single and persistent malloc/calloc
  failures, plus the MiniLibX image fallback allocation paths.
- `gui_resize_harness.c`: image replacement on resize, camera aspect-ratio updates,
  unchanged-size no-op, and retaining the old image when replacement allocation fails.

These are separate test programs; they are not linked into miniRT and use normal
C test-library facilities rather than the project's restricted production API.
AddressSanitizer leak checking is disabled because of this host's tracing setup;
Valgrind performs full leak checking with no suppressions. The wrappers intercept
application and statically linked MiniLibX allocation calls, not allocators inside
shared X11/system libraries.

## MiniLibX patch

The local dependency's `mlx_int_anti_resize_win.c` initializes `XSizeHints` to zero.
This fixes an uninitialized stack value confirmed by Valgrind's origin trace.
The dependency directory is ignored by the parent repository, so the patch is
also preserved here. If you replace/reclone the dependency, apply it once:

```sh
git -C lib/mlx_linux apply ../../tests/minilibx-hints.patch
make all bonus
```

See `TEST_REPORT.md` for results, fixes, changed files, and limitations.

## Fullscreen controls

F11 toggles fullscreen; Escape quits. See [fullscreen usage](/home/polaris/Desktop/minirt/FULLSCREEN.md).
