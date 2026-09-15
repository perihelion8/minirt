/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_running.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 09:04:49 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:57:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "engine_internal.h"
#include "action/action.h"
#include "input/handle_key.h"
#include "renderer.h"

static double	elapsed_time(t_engine *engine)
{
	struct timeval	now;
	double			current;
	double			elapsed;

	if (gettimeofday(&now, NULL) != 0)
		return (0);
	current = now.tv_sec + now.tv_usec / 1000000.0;
	elapsed = 0;
	if (engine->last_tick != 0)
		elapsed = current - engine->last_tick;
	engine->last_tick = current;
	if (elapsed < 0)
		elapsed = 0;
	if (elapsed > 0.25)
		elapsed = 0.25;
	return (elapsed);
}

static int	engine_tick(void *param)
{
	t_engine	*engine;

	engine = param;
	if (!engine->running)
		return (0);
	action_update(engine, elapsed_time(engine));
	if (!engine->dirty)
		return (0);
	render_scene(engine->scene, graphicsctx_image(engine->graphics));
	graphicsctx_present(engine->graphics);
	engine->dirty = 0;
	return (0);
}

static int	engine_expose(void *param)
{
	t_engine	*engine;

	engine = param;
	engine->dirty = 1;
	return (0);
}

void	engine_run(t_engine *engine)
{
	graphicsctx_on_resize(engine->graphics, engine_resize, engine);
	graphicsctx_on_expose(engine->graphics, engine_expose, engine);
	graphicsctx_on_input(engine->graphics, handle_key_release,
		handle_focus_out, engine);
	graphicsctx_on_close(engine->graphics, handle_close, engine);
	graphicsctx_run(engine->graphics, handle_key, engine_tick, engine);
}

void	engine_stop(t_engine *engine)
{
	engine->running = 0;
	graphicsctx_stop(engine->graphics);
}
