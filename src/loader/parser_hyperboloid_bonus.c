/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hyperboloid_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:58:36 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 21:28:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_hyperboloid(t_hyperboloid *hp, char **s, int linenumber)
{
	if (!parser_vec3(&hp->pos, s, linenumber))
		return (0);
	if (!parser_vec3_normal(&hp->axis, s, linenumber))
		return (0);
	hp->axis = vec3_normal(hp->axis);
	if (!parser_dimension(&hp->diameter, s, linenumber))
		return (0);
	if (!parser_dimension(&hp->height, s, linenumber))
		return (0);
	return (parser_color(&hp->color, s, linenumber));
}
