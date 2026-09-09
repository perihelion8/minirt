/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:58:49 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "engine_internal.h"
#include "input/handle_key.h"
#include "renderer.h"
#include "graphicsctx.h"

static int	engine_tick(void *param)
{
	t_engine	*engine;

	engine = param;
	if (!engine->dirty)
		return (0);
	render_scene(engine->scene, graphicsctx_image(engine->graphics));
	graphicsctx_present(engine->graphics);
	engine->dirty = 0;
	return (0);
}

t_engine	*engine_create(t_scene *scene)
{
	t_engine	*engine;

	engine = malloc(sizeof(*engine));
	if (engine == NULL)
		return (NULL);
	engine->graphics = graphicsctx_create();
	if (engine->graphics == NULL)
		return (free(engine), NULL);
	engine->scene = scene;
	engine->dirty = 1;
	engine->running = 1;
	return (engine);
}

void	engine_run(t_engine *engine)
{
	graphicsctx_run(
		engine->graphics,
		handle_key,
		engine_tick,
		engine
		);
}

void	engine_stop(t_engine *engine)
{
	engine->running = 0;
	graphicsctx_stop(engine->graphics);
}

void	engine_destroy(t_engine *engine)
{
	if (engine == NULL)
		return ;
	graphicsctx_destroy(engine->graphics);
	free(engine);
}
