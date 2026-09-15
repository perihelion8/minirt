/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:57:02 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:08:15 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include <math.h>

static int	look(t_camera *camera, int *keys, double seconds)
{
	double	yaw;
	double	pitch;
	t_vec3	forward;

	yaw = (keys[INPUT_YAW_RIGHT] - keys[INPUT_YAW_LEFT]) * seconds;
	pitch = (keys[INPUT_PITCH_UP] - keys[INPUT_PITCH_DOWN]) * seconds;
	if (yaw == 0 && pitch == 0)
		return (0);
	camera_rotate_right(camera, yaw * 1.5);
	forward = vec3_add(vec3_scale(camera->forward, cos(pitch * 1.5)),
			vec3_scale(camera->up, sin(pitch * 1.5)));
	camera->forward = vec3_normal(forward);
	camera->up = vec3_normal(vec3_cross(camera->forward, camera->right));
	return (1);
}

void	action_update(t_engine *engine, double seconds)
{
	t_camera	*camera;
	t_vec3		movement;
	int			*keys;
	double		speed;

	camera = &engine->scene->camera;
	keys = engine->keys;
	if (look(camera, keys, seconds))
		engine->dirty = 1;
	movement = vec3_scale(camera->forward,
			keys[INPUT_FORWARD] - keys[INPUT_BACKWARD]);
	movement = vec3_add(movement, vec3_scale(camera->right,
			keys[INPUT_RIGHT] - keys[INPUT_LEFT]));
	movement.y += keys[INPUT_UP] - keys[INPUT_DOWN];
	if (vec3_length_squared(movement) == 0 || seconds <= 0)
		return ;
	speed = 10.0 * (1 + 2 * keys[INPUT_FAST]);
	camera->pos = vec3_add(camera->pos,
			vec3_scale(vec3_normal(movement), speed * seconds));
	engine->dirty = 1;
}
