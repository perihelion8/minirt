/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:57:41 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:15:28 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "scene.h"
# include "../src/engine/input/handle_key.h"

typedef	struct s_graphicsctx	t_graphicsctx;	
typedef	struct s_engine
{
	t_scene			*scene;
	t_graphicsctx	*graphics;
	int				dirty;
	int				running;
	int				fullscreen_pressed;
	int				keys[INPUT_COUNT];
	double			last_tick;
}								t_engine;

int			engine_init(t_engine *engine, t_scene *scene);
void		engine_toggle_fullscreen(t_engine *engine);
void		engine_run(t_engine *engine);
void		engine_stop(t_engine *engine);
void		engine_destroy(t_engine *engine);

#endif
