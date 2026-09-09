/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:56:00 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/19 03:54:55 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "image_internal.h"
#include "graphicsctx_internal.h"

t_graphicsctx	*graphicsctx_create(void)
{
	t_graphicsctx	*ctx;

	ctx = ft_calloc(1, sizeof(*ctx));
	if (ctx == NULL)
		return (NULL);
	ctx->width = WINDOW_WIDTH;
	ctx->height = WINDOW_HEIGHT;
	ctx->mlx = mlx_init();
	if (ctx->mlx == NULL)
		return (free(ctx), NULL);
	ctx->win = mlx_new_window(ctx->mlx, ctx->width, ctx->height, "miniRT");
	if (ctx->win == NULL)
		return (graphicsctx_destroy(ctx), NULL);
	if (!image_init(&ctx->img, ctx->mlx, ctx->width, ctx->height))
		return (graphicsctx_destroy(ctx), NULL);
	return (ctx);
}

void	graphicsctx_present(t_graphicsctx *ctx)
{
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
}

void	graphicsctx_run(t_graphicsctx *ctx, t_key_hook key_hook,
		t_loop_hook loop_hook, void *param)
{
	mlx_key_hook(ctx->win, key_hook, param);
	mlx_loop_hook(ctx->mlx, loop_hook, param);
	mlx_loop(ctx->mlx);
}

void	graphicsctx_stop(t_graphicsctx *ctx)
{
	mlx_loop_end(ctx->mlx);
}

void	graphicsctx_destroy(t_graphicsctx *ctx)
{
	if (ctx == NULL)
		return ;
	if (ctx->mlx && ctx->img.img)
		mlx_destroy_image(ctx->mlx, ctx->img.img);
	if (ctx->mlx && ctx->win)
		mlx_destroy_window(ctx->mlx, ctx->win);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	free(ctx);
}
