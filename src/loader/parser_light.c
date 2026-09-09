/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:55:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 20:01:04 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int	parser_light(t_light *light, char **line, int linenumber)
{
	if (light->color.r != -1)
	{
		printf("Error dup\n");
		return (0);
	}
	if (!parser_vec3(&light->pos, line, linenumber))
		return (0);
	if (!parser_double(&light->ratio, line, linenumber))
		return (0);
	if (!parser_color(&light->color, line, linenumber))
		return (0);
	return (1);
}
