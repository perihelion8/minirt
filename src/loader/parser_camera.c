/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:55:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/18 02:01:32 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "parser.h"

int	parser_camera(t_camera *camera, char **s, int linenumber)
{
	if (camera->seen)
	{
		parser_error(linenumber, "duplicate camera declaration.");
		return (0);
	}
	if (!parser_vec3(&camera->pos, s, linenumber))
		return (0);
	if (!parser_vec3_normal(&camera->forward, s, linenumber))
		return (0);
	if (!parser_int(&camera->fov, s, linenumber))
		return (0);
	if (camera->fov < 0 || camera->fov > 180)
	{
		parser_error(linenumber, "field of view must be between 0 and 180.");
		return (0);
	}
	camera->seen = 1;
	vec3_basis(&camera->forward, &camera->right, &camera->up);
	return (1);
}
