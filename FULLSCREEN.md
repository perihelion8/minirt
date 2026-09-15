# Fullscreen

Press **F11** to enter or leave fullscreen in either `miniRT` or `miniRT_bonus`.
Press **Escape** to quit, including while fullscreen.

```sh
make all bonus
./miniRT_bonus hyperboloid_bonus.rt
```

The window starts at 960×720. Fullscreen uses the monitor's actual dimensions.
The renderer creates a matching image and updates the camera's aspect ratio,
keeping the horizontal field of view unchanged. Returning to windowed mode
restores the previous window geometry. Windowed resizing is also supported.

The old image is retained until its replacement is successfully allocated.
If resizing cannot allocate an image, the program reports the error and closes
cleanly. Repeated F11 key-press events are ignored until the key is released;
focus loss clears held keys.

This implementation targets the project's Linux MiniLibX backend and a window
manager supporting the [EWMH fullscreen protocol](https://specifications.freedesktop.org/wm/latest/ar01s05.html).
The small X11 bridge lives in `src/graphicsctx/graphicsctx_fullscreen.c`; image
replacement lives in `src/graphicsctx/graphicsctx_resize.c`.

Run the regression suites using the commands in `tests/README.md`.
