/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 graphicsctx.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42beirut.com>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/08/18 21:56:00 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/09/10 20:21:43 by abazzoun		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "graphicsctx.h"

t_graphicsctx	*graphicsctx_create()
{
	t_graphicsctx	*ctx;

	ctx = ft_calloc(1, sizeof(*ctx));
	if (!ctx)
		return (perror("Error\n,Malloc"), NULL);
	ctx->width = WINDOW_WIDTH;
	ctx->height = WINDOW_HEIGHT;
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
	{
		perror("Error\nMLX");
		graphicsctx_destroy(ctx);
		return (NULL);
	}
	ctx->win = mlx_new_window(ctx->mlx, ctx->width, ctx->height, "miniRT");
	if (!ctx->win)
	{
		perror("Error\nMLX");
		graphicsctx_destroy(ctx);
		return (NULL);
	}
	if (!image_init(&ctx->img, ctx->mlx, ctx->width, ctx->height))
	{
		perror("Error\nMLX");
		graphicsctx_destroy(ctx);
		return (NULL);
	}
	return (ctx);
}

void	graphicsctx_destroy(t_graphicsctx *ctx)
{
	if (!ctx)
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
	ctx->mlx = NULL;
	ctx->img.img = NULL;
	ctx->win = NULL;
	free(ctx);
}

void	graphicsctx_present(t_graphicsctx *ctx)
{
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
}

t_image	*graphicsctx_image(t_graphicsctx *ctx)
{
	return (&ctx->img);
}
