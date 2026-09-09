# minirt

## pipeline

input -> update -> render -> display

## handle input

only update state (camera, flags, modes).

## engine

- applies input → updates camera
- triggers render

## render

- does all heavy work
- does not use MLX calls
- only fills the image buffer
- only uses camera, never modifies it

## display

just sends the image to the window.

## camera

A camera is not a position + angles. It is:

> A point in space + 3 direction vectors defining its orientation.

So instead of thinking:

- position + yaw/pitch

You think:

- origin (position)
- forward
- right
- up

Because:

- easy to compute rays
- matches OpenGL / Blender-style math
- clean separation of orientation logic

## the most important part

Every pixel is computed like:

> pixel → direction in camera space → world ray

So camera defines:

> how rays are “spread” in 3D space

## common beginner mistake

- mixing camera logic inside renderer
- recalculating basis inside every pixel
- using angles everywhere instead of vectors


## upcast and downcast in c to simulate inheritance
