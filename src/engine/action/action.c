/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:57:02 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 14:02:00 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"
#include "../engine_internal.h"

void	action_apply(void *param, t_action action)
{
	t_engine	*engine;
	t_camera	*camera;

	engine = param;
	camera = &engine->scene->camera;
	if (action == ACTION_QUIT)
	{
		engine_stop(engine);
		return ;
	}
	if (action == ACTION_MOVE_FORWARD)
		camera_move_forward(camera, 10);
	else if (action == ACTION_MOVE_BACKWARD)
		camera_move_backward(camera, 10);
	else if (action == ACTION_ROTATE_RIGHT)
		camera_rotate_right(camera, 3.14 / 10);
	else if (action == ACTION_ROTATE_LEFT)
		camera_rotate_left(camera, 3.14 / 10);
	if (action != ACTION_NONE)
		engine->dirty = 1;
}
