/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:57:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 09:52:59 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser_vec3(t_vec3 *vec, char **s, int linenumber)
{
	if (!parser_double(&vec->x, s, linenumber))
		return (0);
	if (!expect(s, ',', linenumber))
		return (0);
	if (!parser_double(&vec->y, s, linenumber))
		return (0);
	if (!expect(s, ',', linenumber))
		return (0);
	if (!parser_double(&vec->z, s, linenumber))
		return (0);
	return (1);
}

int	parser_vec3_normal(t_vec3 *vec, char **s, int linenumber)
{
	if (parser_vec3(vec, s, linenumber))
	{
		if (!vec3_isnormal(*vec))
		{
			parser_error(linenumber,
				"orientation, axis and normal vectors must be normalized.");
			return (0);
		}
		return (1);
	}
	return (0);
}
