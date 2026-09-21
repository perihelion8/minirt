/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 03:51:37 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 01:44:44 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx.h"
#include "mlx.h"
#include <X11/X.h>

static int	handle_expose(void *param)
{
	graphicsctx_present(param);
	return (0);
}

void	graphicsctx_run(t_graphicsctx *ctx, t_hook loop_hook,
			t_hook close_hook, void *param)
{
	mlx_expose_hook(ctx->win, handle_expose, ctx);
	mlx_hook(ctx->win, DestroyNotify, 0, close_hook, param);
	mlx_loop_hook(ctx->mlx, loop_hook, param);
	mlx_loop(ctx->mlx);
}

void	graphicsctx_stop(t_graphicsctx *ctx)
{
	mlx_loop_end(ctx->mlx);
}
