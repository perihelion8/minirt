/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_spotlight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 19:47:14 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 00:24:02 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

int	parser_spotlight(t_spotlight *spot, char **line, int linenumber)
{
	if (!parser_vec3(&spot->pos, line, linenumber))
		return (0);
	if (!parser_vec3_normal(&spot->direction, line, linenumber))
		return (0);
	if (!parser_ratio(&spot->brightness, line, linenumber))
		return (0);
	if (!parser_color(&spot->color, line, linenumber))
		return (0);
	if (!parser_int(&spot->angle, line, linenumber))
		return (0);
	if (spot->angle < 0 || spot->angle > 180)
	{
		parser_error(linenumber, "spot angle must be between 0 and 180");
		return (0);
	}
	spot->cutoff_cos = cos(spot->angle * (acos(-1.0) / 360.0));
	return (1);
}
