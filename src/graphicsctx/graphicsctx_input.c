/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 11:41:29 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/17 08:16:21 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx.h"
#include "mlx.h"
#include <X11/X.h>

void	graphicsctx_on_key(t_graphicsctx *ctx, t_key_hook press_hook,
			t_key_hook release_hook, void *param)
{
	mlx_hook(ctx->win, KeyPress, KeyPressMask, press_hook, param);
	mlx_hook(ctx->win, KeyRelease, KeyReleaseMask, release_hook, param);
}

void	graphicsctx_on_focus(t_graphicsctx *ctx, t_hook focus_hook, void *param)
{
	mlx_hook(ctx->win, FocusOut, FocusChangeMask, focus_hook, param);
}
