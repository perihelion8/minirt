/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:07:12 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "engine_internal.h"

int	engine_init(t_engine *engine, t_scene *scene)
{
	handle_focus_out(engine);
	engine->graphics = graphicsctx_create();
	if (!engine->graphics)
	{
		engine_destroy(engine);
		return (0);
	}
	engine->scene = scene;
	engine->dirty = 1;
	engine->running = 1;
	return (1);
}

void	engine_destroy(t_engine *engine)
{
	if (engine->graphics)
		graphicsctx_destroy(engine->graphics);
	engine->graphics = NULL;
}

