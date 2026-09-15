/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_resize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 09:04:49 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:57:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "graphicsctx.h"
#include "mlx.h"
#include "mlx_int.h"

static int	replace_image(t_graphicsctx *ctx, int width, int height)
{
	t_image	image;

	if (width <= 0 || height <= 0 || width > INT_MAX / 4 - 32
		|| height > INT_MAX / ((width + 32) * 4))
		return (printf("Error\nWindow dimensions are too large.\n"), -1);
	image = (t_image){0};
	if (!image_init(&image, ctx->mlx, width, height))
		return (perror("Error\nResizing image"), -1);
	mlx_destroy_image(ctx->mlx, ctx->img.img);
	ctx->img = image;
	ctx->width = width;
	ctx->height = height;
	return (1);
}

int	graphicsctx_sync_size(t_graphicsctx *ctx)
{
	t_xvar				*mlx;
	t_win_list			*win;
	XWindowAttributes	attributes;

	mlx = ctx->mlx;
	win = ctx->win;
	if (!XGetWindowAttributes(mlx->display, win->window, &attributes))
		return (-1);
	if (attributes.width == ctx->width && attributes.height == ctx->height)
		return (0);
	return (replace_image(ctx, attributes.width, attributes.height));
}
