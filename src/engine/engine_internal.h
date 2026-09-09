/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:40 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:56:40 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_INTERNAL_H
# define ENGINE_INTERNAL_H

# include "engine.h"
# include "graphicsctx.h"

struct s_engine
{
	t_scene			*scene;
	t_graphicsctx	*graphics;
	int				dirty;
	int				running;
};

#endif
