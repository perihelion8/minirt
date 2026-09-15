# Hyperboloid bonus

Build with `make bonus`, then run `./miniRT_bonus hyperboloid_bonus.rt`.
The mandatory executable rejects the bonus `hy` identifier.

```text
hy center_x,center_y,center_z axis_x,axis_y,axis_z waist_diameter height R,G,B
hy 0,0,5 0,1,0 2 6 220,220,230
```

The axis must be normalized, both dimensions must be positive, and color
channels must be in [0,255]. Multiple `hy` objects are supported.

This is a capped one-sheet hyperboloid of revolution. In local coordinates,
with z along the axis, radius r = waist_diameter / 2 and h = height / 2:

`(x*x + y*y) / (r*r) - z*z / (h*h) = 1`, with `-h <= z <= h`.

The waist is at the center. Each end has radius `sqrt(2) * r` and a flat cap.
The renderer tests both quadratic roots (or the linear case), clips the body
to its height, and chooses the nearest positive body or cap intersection.
Normals come from the surface gradient. The object participates in the existing
colored lighting and shadow calculations.
