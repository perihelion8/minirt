#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	fov;
}				t_camera;

void	camera_move_forward(t_camera *camera, double distance);
void	camera_move_backward(t_camera *camera, double distance);
void	camera_rotate_right(t_camera *camera, double angle);
void	camera_rotate_left(t_camera *camera, double angle);

#endif
