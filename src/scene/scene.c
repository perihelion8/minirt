/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 scene.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/09/09 10:28:02 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/09/10 13:33:27 by abazzoun		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../graphicsctx/graphicsctx.h"
#include "libft.h"
#include "scene.h"

void	scene_init(t_scene *scene)
{
	scene->ambient.seen = 0;
	scene->light.seen = 0;
	scene->camera.seen = 0;
	scene->shapea = NULL;
	scene->spotlighta = NULL;
	scene->shapea_len = 0;
	scene->spotlighta_len = 0;
	scene->width = WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
}

void	scene_destroy(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->shapea);
	free(scene->spotlighta);
	scene->shapea = NULL;
	scene->spotlighta = NULL;
	scene->shapea_len = 0;
	scene->spotlighta_len = 0;
}

int	validate_scene(t_scene *scene)
{
	if (!scene->camera.seen || !scene->light.seen || !scene->ambient.seen)
		return (0);
	if (!scene->shapea_len)
		return (0);
	return (1);
}
