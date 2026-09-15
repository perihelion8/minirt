/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 09:04:49 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:57:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_internal.h"

void	engine_toggle_fullscreen(t_engine *engine)
{
	if (engine->fullscreen_pressed)
		return ;
	engine->fullscreen_pressed = 1;
	graphicsctx_toggle_fullscreen(engine->graphics);
}

int	engine_resize(void *param)
{
	t_engine	*engine;
	int			resized;

	engine = param;
	resized = graphicsctx_sync_size(engine->graphics);
	if (resized < 0)
		return (engine_stop(engine), 0);
	if (!resized)
		return (0);
	engine->scene->width = engine->graphics->width;
	engine->scene->height = engine->graphics->height;
	engine->scene->camera.half_viewport_height
		= engine->scene->camera.half_viewport_width
		* engine->scene->height / engine->scene->width;
	engine->last_tick = 0;
	engine->dirty = 1;
	return (0);
}
