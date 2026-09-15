/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_running.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 09:04:49 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 10:47:47 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_internal.h"
#include "input/handle_key.h"
#include "renderer.h"

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

void	engine_run(t_engine *engine)
{
	graphicsctx_on_close(engine->graphics, handle_close, engine);
	graphicsctx_run(engine->graphics, handle_key, engine_tick, engine);
}

void	engine_stop(t_engine *engine)
{
	engine->running = 0;
	graphicsctx_stop(engine->graphics);
}
