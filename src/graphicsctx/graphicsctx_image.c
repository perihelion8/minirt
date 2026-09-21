/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:15:45 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/17 08:09:23 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx.h"
#include "mlx.h"

void	graphicsctx_present(t_graphicsctx *ctx)
{
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
}

t_image	*graphicsctx_image(t_graphicsctx *ctx)
{
	return (&ctx->img);
}
