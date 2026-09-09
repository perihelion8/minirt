/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphicsctx_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 03:51:37 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/19 03:52:21 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphicsctx_internal.h"

t_image	*graphicsctx_image(t_graphicsctx *ctx)
{
	return (&ctx->img);
}
