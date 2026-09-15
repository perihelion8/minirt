/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:54:28 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 09:31:55 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int	parser_ambient(t_ambient *ambient, char **line, int linenumber)
{
	if (ambient->seen)
	{
		parser_error(linenumber, "duplicate ambient lighting declaration.");
		return (0);
	}
	if (!parser_ratio(&ambient->ratio, line, linenumber))
		return (0);
	if (!parser_color(&ambient->color, line, linenumber))
		return (0);
	ambient->seen = 1;
	return (1);
}
