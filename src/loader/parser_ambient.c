/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:54:28 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 20:00:44 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int	parser_ambient(t_ambient *ambient, char **line, int linenumber)
{
	if (ambient->color.r != -1)
	{
		printf("Error dup\n");
		return (0);
	}
	if (!parser_double(&ambient->ratio, line, linenumber))
		return (0);
	if (!parser_color(&ambient->color, line, linenumber))
		return (0);
	return (1);
}
