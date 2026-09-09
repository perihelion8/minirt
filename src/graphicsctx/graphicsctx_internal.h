/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:09 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/18 21:56:10 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSCTX_INTERNAL_H
# define GRAPHICSCTX_INTERNAL_H

# include "graphicsctx.h"
# include "image_internal.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

struct s_graphicsctx
{
	void	*mlx;
	void	*win;
	t_image	img;
	int		width;
	int		height;
};

#endif
