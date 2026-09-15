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
#include "linkedlist.h"
#include "libft.h"
#include "scene.h"

void	scene_destroy(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->shapell)
		destroyll((t_nodell *)scene->shapell);
	scene->shapell = NULL;
	destroyll((t_nodell *)scene->lightll);
	scene->lightll = NULL;
}

void	scene_init(t_scene *scene)
{
	scene->ambient.seen = 0;
	scene->lightll = NULL;
	scene->camera.seen = 0;
	scene->shapell = NULL;
	scene->width =  WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
}
