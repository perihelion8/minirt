/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_fullscreen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 09:04:49 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:57:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx.h"
#include "mlx.h"
#include "mlx_int.h"

void	graphicsctx_window_setup(t_graphicsctx *ctx)
{
	t_xvar		*mlx;
	t_win_list	*win;
	XSizeHints	hints;

	mlx = ctx->mlx;
	win = ctx->win;
	hints = (XSizeHints){0};
	hints.flags = PMinSize;
	hints.min_width = 1;
	hints.min_height = 1;
	XSetWMNormalHints(mlx->display, win->window, &hints);
	XkbSetDetectableAutoRepeat(mlx->display, True, NULL);
}

void	graphicsctx_toggle_fullscreen(t_graphicsctx *ctx)
{
	t_xvar		*mlx;
	t_win_list	*win;
	XEvent		event;

	mlx = ctx->mlx;
	win = ctx->win;
	event = (XEvent){0};
	event.xclient.type = ClientMessage;
	event.xclient.window = win->window;
	event.xclient.message_type = XInternAtom(mlx->display,
			"_NET_WM_STATE", False);
	event.xclient.format = 32;
	event.xclient.data.l[0] = 2;
	event.xclient.data.l[1] = XInternAtom(mlx->display,
			"_NET_WM_STATE_FULLSCREEN", False);
	event.xclient.data.l[3] = 1;
	XSendEvent(mlx->display, mlx->root, False,
		SubstructureRedirectMask | SubstructureNotifyMask, &event);
	XFlush(mlx->display);
}

void	graphicsctx_on_resize(t_graphicsctx *ctx, t_hook hook, void *param)
{
	mlx_hook(ctx->win, ConfigureNotify, StructureNotifyMask, hook, param);
}
