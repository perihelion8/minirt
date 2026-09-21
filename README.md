# minirt

## Camera controls

Hold keys for continuous free-flight movement:

- **W / S**: forward / backward along the camera direction.
- **A / D**: strafe left / right.
- **Arrow keys**: look left / right / up / down.
- **Space / C**: rise / descend along the world vertical axis.
- **Left Shift**: move three times faster.
- **Escape**: quit.

Keys can be combined. Diagonal movement has the same speed as straight
movement. Speed is 10 scene units per second (30 with Left Shift), and
turn speed is 1.5 radians per second. Losing focus clears held keys.
Elapsed time is capped at 0.25 seconds to avoid jumps after long stalls.
Every moving frame renders the full **960 × 720** image, including shading
and shadows. Frame rate depends on scene complexity and CPU speed.


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
