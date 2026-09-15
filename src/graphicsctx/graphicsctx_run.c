/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 03:51:37 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 10:09:18 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx.h"
#include "mlx.h"
#include <X11/X.h>

void	graphicsctx_run(t_graphicsctx *ctx, t_key_hook key_hook,
			t_hook loop_hook, void *param)
{
	mlx_hook(ctx->win, KeyPress, KeyPressMask, key_hook, param);
	mlx_loop_hook(ctx->mlx, loop_hook, param);
	mlx_loop(ctx->mlx);
}

void	graphicsctx_stop(t_graphicsctx *ctx)
{
	mlx_loop_end(ctx->mlx);
}

void	graphicsctx_on_close(t_graphicsctx *ctx, t_hook close_hook,
			void *param)
{
	mlx_hook(ctx->win, DestroyNotify, 0, close_hook, param);
}

void	graphicsctx_on_input(t_graphicsctx *ctx, t_key_hook release_hook,
			t_hook focus_hook, void *param)
{
	mlx_hook(ctx->win, KeyRelease, KeyReleaseMask, release_hook, param);
	mlx_hook(ctx->win, FocusOut, FocusChangeMask, focus_hook, param);
}

