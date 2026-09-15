/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 02:55:18 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 21:43:05 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int	parser_light(t_light **lightll, char **line, int linenumber)
{
	t_light		*light;
	t_nodell	*head;

	if (*lightll)
	{
		parser_error(linenumber, "duplicate light declaration.");
		return (0);
	}
	head = (t_nodell *)*lightll;
	light = (t_light *)appendll(&head, sizeof(*light));
	if (!light)
		return (0);
	*lightll = (t_light *)head;
	if (!parser_vec3(&light->pos, line, linenumber))
		return (0);
	if (!parser_ratio(&light->ratio, line, linenumber))
		return (0);
	if (!parser_color(&light->color, line, linenumber))
		return (0);
	return (1);
}
