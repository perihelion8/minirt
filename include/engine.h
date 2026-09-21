/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:57:41 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 04:48:00 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "scene.h"
# include "../src/engine/engine_input.h"

typedef struct s_graphicsctx	t_graphicsctx;	
typedef struct s_engine
{
	t_scene			*scene;
	t_graphicsctx	*graphics;
	int				dirty;
	int				running;
	double			last_tick;
	int				keycodes[INPUT_COUNT];
	int				keypressed[INPUT_COUNT];
}								t_engine;

int			engine_init(t_engine *engine, t_scene *scene);
void		engine_run(t_engine *engine);
void		engine_stop(t_engine *engine);
void		engine_destroy(t_engine *engine);

#endif
