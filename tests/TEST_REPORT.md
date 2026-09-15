# Stress-test report

Date: 2026-09-15. Tested on this Linux/X11 host using GCC and Valgrind 3.24.0.

## Final result

All final runtime suites passed. No segmentation faults, sanitizer violations,
Valgrind memory errors, or leaks were observed in the final tested runs.
These are bounded tests, not proof that every possible input or platform is safe.

| Test | Final result |
| --- | --- |
| Parser corpus | 2,788 cases per run × 4 runs = 11,152 scene loads; all specified expectations passed |
| Corpus composition | 2,500 deterministic byte-mutation cases, plus valid, malformed, truncated, NUL, long-line, numeric, duplicate, missing-element, file-error, generated and large-scene cases |
| Instrumentation | Mandatory and bonus, each under ASan/UBSan/float-cast-overflow and unsuppressed Valgrind |
| Random geometry | 100,000 deterministic rays per run; 400,000 iterations across the four runs |
| Hyperboloid reference | Independent long-double roots/caps and translation/rotation invariance checks in both bonus runs |
| Targeted geometry | Side, tangent, miss, parallel, cap, inside, linear-degenerate hyperboloid intersections |
| Lighting | Color mixing, ambient once, independent shadows, blockers beyond lights, zero-strength/coincident/back-facing lights, interior sphere and 1,000 dim-light accumulation |
| Loader allocation failures | 274 injected failures across valid, mixed-shape and hyperboloid scenes; cleanup passed |
| File descriptors | Count unchanged after each corpus load/destruction |
| GUI initialization allocations | 11 Valgrind runs: baseline, four single failures, four persistent failures, two fallback failures; all clean |
| Actual executable CLI/GUI matrix | 41/41 passed: 36 CLI/display-failure cases and 5 GUI sessions |
| GUI actions | Keyboard movement/rotation, focus loss, expose restoration, unmap/remap, Escape and WM_DELETE_WINDOW |
| Rendering | 18 offscreen images generated using the production render loop; contact sheet and actual GUI frame inspected |
| Large lists | 20,000 extra shapes and 20,000 extra lights, separately; no failures |
| GCC static analyzer | 46 source files, zero warnings |
| Build checks | Fresh mandatory and bonus object builds passed; second build did not compile or relink |
| Norminette | 58 production files passed; 18 files still have findings; baseline had 19 failing files |

The single-failure GUI image test successfully exercised MiniLibX's fallback.
Persistent and paired failures then checked that fallback's own allocation cleanup.
Valgrind reported **0 bytes in 0 blocks at exit and 0 errors** for the final memory
checks. No suppressions were used. Earlier failing diagnostic logs are not presented
as final passes.

## Failures found and corrected

1. Zero-sized spheres/cylinders/hyperboloids were accepted, including zero hyperboloid height.
2. Missing whitespace after an identifier was accepted (for example, `A0.2 ...`).
3. A NUL byte could hide an invalid suffix from the parser.
4. An exposed/cleared GUI window stayed blank instead of restoring its image.
5. Extreme dimensions could produce infinite intersection distances or invalid normals.
6. A light inside a sphere did not illuminate its inner surface because the normal faced outward.
7. Truncating each light before accumulation discarded many dim lights' combined contribution.
8. MiniLibX sent uninitialized window-size hints. Valgrind traced their origin to the
   stack in `mlx_int_anti_resize_win`; zero-initializing the structure removed the warning.

The GUI driver also needed to wait for a changed frame before releasing a key under
slow instrumentation. That was a test timing issue, not an application crash.

## Remaining limitations

- Norminette is **not fully clean**. The 18 files with findings are listed in the
  archived Norminette output; formatting the entire existing codebase was outside
  this runtime-hardening pass. Standalone test harnesses are not 42-normed production files.
- Dimensions near floating-point extremes (tested down to 1e-300 and up to 1e300,
  written in decimal notation) no longer produce invalid hit data. This does not
  guarantee accurate geometry at those scales: overflowing/degenerate intersections
  can be discarded. Normal-sized geometry has the reference checks described above.
- GUI automation sends X11 events directly. It tests the same callbacks as keyboard/
  window-manager events, but does not simulate every desktop compositor or physical mouse action.
- Allocation injection covers wrapped application/static-library malloc/calloc calls,
  not failures internal to dynamically linked X11/system libraries or every OS resource failure.
- LeakSanitizer is unavailable under this host's tracing setup; leak results come from Valgrind.
- The parent repository ignores MiniLibX. Its local fix is preserved as a separate patch;
  apply it again if replacing that dependency, as explained in the test README.

## Files changed during this testing pass

- [Makefile](/home/polaris/Desktop/minirt/Makefile) — Rebuild MiniLibX when its source/header dependencies change.
- [src/loader/parser_ratio.c](/home/polaris/Desktop/minirt/src/loader/parser_ratio.c) — Reject zero and negative dimensions.
- [src/loader/parser_utils.c](/home/polaris/Desktop/minirt/src/loader/parser_utils.c) — Require whitespace after scene identifiers.
- [src/loader/get_next_line.c](/home/polaris/Desktop/minirt/src/loader/get_next_line.c) — Reject embedded NUL bytes instead of silently truncating input.
- [src/math/vec3_metrics.c](/home/polaris/Desktop/minirt/src/math/vec3_metrics.c) — Use hypot for more stable vector lengths.
- [src/renderer/renderer_intersection_hit.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection_hit.c) — Reject non-finite hit data and zero normals.
- [src/renderer/renderer_intersection.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection.c) — Orient the closest hit normal toward the incoming ray for interior/back-face shading.
- [src/renderer/renderer_intersection_bonus.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection_bonus.c) — Apply the same normal orientation in the bonus build.
- [src/renderer/renderer_shade.c](/home/polaris/Desktop/minirt/src/renderer/renderer_shade.c) — Accumulate light contributions in double precision and convert to integer RGB only once.
- [src/engine/engine_running.c](/home/polaris/Desktop/minirt/src/engine/engine_running.c) — Mark the scene dirty after expose events.
- [src/graphicsctx/graphicsctx.h](/home/polaris/Desktop/minirt/src/graphicsctx/graphicsctx.h) — Declare the expose callback registration function.
- [src/graphicsctx/graphicsctx_run.c](/home/polaris/Desktop/minirt/src/graphicsctx/graphicsctx_run.c) — Register Expose events with MiniLibX.
- [lib/mlx_linux/mlx_int_anti_resize_win.c](/home/polaris/Desktop/minirt/lib/mlx_linux/mlx_int_anti_resize_win.c) — Initialize XSizeHints; mirrored in tests/minilibx-hints.patch because the dependency is ignored.

The `tests/` directory adds the reusable harnesses, runners, dependency patch, this
report, a README, screenshots, JSON summaries, and compressed final logs.
The following inventory also includes the multiple-light/hyperboloid changes from
the preceding requests, so every current workspace change is visible.

## Complete workspace change inventory

- [HYPERBOLOID.md](/home/polaris/Desktop/minirt/HYPERBOLOID.md)
- [Makefile](/home/polaris/Desktop/minirt/Makefile)
- [hyperboloid_bonus.rt](/home/polaris/Desktop/minirt/hyperboloid_bonus.rt)
- [include/scene.h](/home/polaris/Desktop/minirt/include/scene.h)
- [include/scene/hyperboloid_bonus.h](/home/polaris/Desktop/minirt/include/scene/hyperboloid_bonus.h)
- [include/scene/light.h](/home/polaris/Desktop/minirt/include/scene/light.h)
- [lib/mlx_linux/mlx_int_anti_resize_win.c](/home/polaris/Desktop/minirt/lib/mlx_linux/mlx_int_anti_resize_win.c)
- [multiple_lights_bonus.rt](/home/polaris/Desktop/minirt/multiple_lights_bonus.rt)
- [src/engine/engine_running.c](/home/polaris/Desktop/minirt/src/engine/engine_running.c)
- [src/graphicsctx/graphicsctx.h](/home/polaris/Desktop/minirt/src/graphicsctx/graphicsctx.h)
- [src/graphicsctx/graphicsctx_run.c](/home/polaris/Desktop/minirt/src/graphicsctx/graphicsctx_run.c)
- [src/loader/get_next_line.c](/home/polaris/Desktop/minirt/src/loader/get_next_line.c)
- [src/loader/loader_rt.c](/home/polaris/Desktop/minirt/src/loader/loader_rt.c)
- [src/loader/parser.h](/home/polaris/Desktop/minirt/src/loader/parser.h)
- [src/loader/parser_hyperboloid_bonus.c](/home/polaris/Desktop/minirt/src/loader/parser_hyperboloid_bonus.c)
- [src/loader/parser_light.c](/home/polaris/Desktop/minirt/src/loader/parser_light.c)
- [src/loader/parser_light_bonus.c](/home/polaris/Desktop/minirt/src/loader/parser_light_bonus.c)
- [src/loader/parser_line.c](/home/polaris/Desktop/minirt/src/loader/parser_line.c)
- [src/loader/parser_line_bonus.c](/home/polaris/Desktop/minirt/src/loader/parser_line_bonus.c)
- [src/loader/parser_ratio.c](/home/polaris/Desktop/minirt/src/loader/parser_ratio.c)
- [src/loader/parser_utils.c](/home/polaris/Desktop/minirt/src/loader/parser_utils.c)
- [src/math/vec3_metrics.c](/home/polaris/Desktop/minirt/src/math/vec3_metrics.c)
- [src/renderer/renderer_hyperboloid_bonus.c](/home/polaris/Desktop/minirt/src/renderer/renderer_hyperboloid_bonus.c)
- [src/renderer/renderer_intersection.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection.c)
- [src/renderer/renderer_intersection.h](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection.h)
- [src/renderer/renderer_intersection_bonus.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection_bonus.c)
- [src/renderer/renderer_intersection_hit.c](/home/polaris/Desktop/minirt/src/renderer/renderer_intersection_hit.c)
- [src/renderer/renderer_shade.c](/home/polaris/Desktop/minirt/src/renderer/renderer_shade.c)
- [src/scene/scene.c](/home/polaris/Desktop/minirt/src/scene/scene.c)
- [tests/README.md](/home/polaris/Desktop/minirt/tests/README.md)
- [tests/TEST_REPORT.md](/home/polaris/Desktop/minirt/tests/TEST_REPORT.md)
- [tests/artifacts/app_summary.json](/home/polaris/Desktop/minirt/tests/artifacts/app_summary.json)
- [tests/artifacts/fresh-build-summary.json](/home/polaris/Desktop/minirt/tests/artifacts/fresh-build-summary.json)
- [tests/artifacts/gui-hyperboloid.png](/home/polaris/Desktop/minirt/tests/artifacts/gui-hyperboloid.png)
- [tests/artifacts/gui_alloc_summary.json](/home/polaris/Desktop/minirt/tests/artifacts/gui_alloc_summary.json)
- [tests/artifacts/large_summary.json](/home/polaris/Desktop/minirt/tests/artifacts/large_summary.json)
- [tests/artifacts/norm-baseline.log](/home/polaris/Desktop/minirt/tests/artifacts/norm-baseline.log)
- [tests/artifacts/norminette.log](/home/polaris/Desktop/minirt/tests/artifacts/norminette.log)
- [tests/artifacts/render-contact-sheet.png](/home/polaris/Desktop/minirt/tests/artifacts/render-contact-sheet.png)
- [tests/artifacts/render_summary.json](/home/polaris/Desktop/minirt/tests/artifacts/render_summary.json)
- [tests/artifacts/summary.json](/home/polaris/Desktop/minirt/tests/artifacts/summary.json)
- [tests/artifacts/test-logs.zip](/home/polaris/Desktop/minirt/tests/artifacts/test-logs.zip)
- [tests/gui_alloc_harness.c](/home/polaris/Desktop/minirt/tests/gui_alloc_harness.c)
- [tests/gui_driver.c](/home/polaris/Desktop/minirt/tests/gui_driver.c)
- [tests/minilibx-hints.patch](/home/polaris/Desktop/minirt/tests/minilibx-hints.patch)
- [tests/run_app.py](/home/polaris/Desktop/minirt/tests/run_app.py)
- [tests/run_extended.py](/home/polaris/Desktop/minirt/tests/run_extended.py)
- [tests/run_gui_alloc.py](/home/polaris/Desktop/minirt/tests/run_gui_alloc.py)
- [tests/run_stress.py](/home/polaris/Desktop/minirt/tests/run_stress.py)
- [tests/stress_harness.c](/home/polaris/Desktop/minirt/tests/stress_harness.c)

Generated build products include `miniRT`, `miniRT_bonus`, their objects, and the
rebuilt MiniLibX archives. Instrumented executables and generated test scenes live
under `/tmp/minirt-stress`.

## Evidence and rerunning

- [Test commands and harness descriptions](/home/polaris/Desktop/minirt/tests/README.md)
- [Final logs (ZIP)](/home/polaris/Desktop/minirt/tests/artifacts/test-logs.zip)
- [Headless summary](/home/polaris/Desktop/minirt/tests/artifacts/summary.json)
- [Executable/GUI summary](/home/polaris/Desktop/minirt/tests/artifacts/app_summary.json)
- [GUI allocation summary](/home/polaris/Desktop/minirt/tests/artifacts/gui_alloc_summary.json)
- [Rendered examples](/home/polaris/Desktop/minirt/tests/artifacts/render-contact-sheet.png)
- [Actual hyperboloid GUI screenshot](/home/polaris/Desktop/minirt/tests/artifacts/gui-hyperboloid.png)

Large-list timings in this run (sanitizer build; machine/load dependent):

- 20,000 extra shapes: 1.058 seconds.
- 20,000 extra lights: 0.527 seconds.
