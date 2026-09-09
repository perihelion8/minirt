/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:55:56 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 21:20:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int parser_camera(t_camera *camera, char **line, int linenumber)
{
	if (camera->fov > -10.0)
	{
		printf("Error dup cam\n");
		return (0);
	}
	if (!parser_vec3(&camera->pos, line, linenumber))
		return (0);
	if (!parser_vec3(&camera->forward, line, linenumber))
		return (0);
	if (!parser_double(&camera->fov, line, linenumber))
		return (0);
	vec3_basis(&camera->forward, &camera->right, &camera->up);
	return (1);
}
