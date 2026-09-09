/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:50:48 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:50:49 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene/camera.h"

void	camera_move_forward(t_camera *camera, double distance)
{
	t_vec3	movement;

	movement = vec3_scale(camera->forward, distance);
	camera->pos = vec3_add(camera->pos, movement);
}

void	camera_move_backward(t_camera *camera, double distance)
{
	camera_move_forward(camera, -distance);
}

void	camera_rotate_right(t_camera *camera, double angle)
{
	t_vec3	old_forward;
	t_vec3	old_right;
	double	cos_angle;
	double	sin_angle;

	old_forward = camera->forward;
	old_right = camera->right;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	camera->forward = vec3_add(
			vec3_scale(old_forward, cos_angle),
			vec3_scale(old_right, sin_angle));
	camera->right = vec3_subtract(
			vec3_scale(old_right, cos_angle),
			vec3_scale(old_forward, sin_angle));
	camera->forward = vec3_normalize(camera->forward);
	camera->right = vec3_normalize(camera->right);
}

void	camera_rotate_left(t_camera *camera, double angle)
{
	camera_rotate_right(camera, -angle);
}
