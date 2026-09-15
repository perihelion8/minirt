/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:53:53 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/15 09:38:20 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "scene.h"
#include "parser.h"

static int	all_space(char **s)
{
	while (**s)
	{
		if (!ft_isspace(**s))
			return (0);
		(*s)++;
	}
	return (1);
}

static int	expect_endl(char *s, int linenumber)
{
	while (ft_isspace(*s))
		s++;
	if (*s)
	{
		unexpected(*s, linenumber);
		return (0);
	}
	return (1);
}

static int	parser_shape(t_shape **shapell, t_shape_type type, char **s,
		int linenumber)
{
	t_shape		*shape;
	t_nodell	*head;

	head = (t_nodell *)(*shapell);
	shape = (t_shape *)appendll(&head, sizeof(*shape));
	if (!shape)
		return (0);
	*shapell = (t_shape *)head;
	shape->type = type;
	if (type == PLANE)
		return (parser_plane(&shape->plane, s, linenumber));
	if (type == SPHERE)
		return (parser_sphere(&shape->sphere, s, linenumber));
	if (type == CYLINDER)
		return (parser_cylinder(&shape->cylinder, s, linenumber));
	if (type == HYPERBOLOID)
		return (parser_hyperboloid(&shape->hyperboloid, s, linenumber));
	return (0);
}

int	parser_line(t_scene *scene, char *s, int linenumber)
{
	int		ret;

	if (all_space(&s))
		return (1);
	else if (accept_identifier(&s, "A"))
		ret = parser_ambient(&scene->ambient, &s, linenumber);
	else if (accept_identifier(&s, "C"))
		ret = parser_camera(&scene->camera, &s, linenumber, scene->width,
				scene->height);
	else if (accept_identifier(&s, "L"))
		ret = parser_light(&scene->lightll, &s, linenumber);
	else if (accept_identifier(&s, "sp"))
		ret = parser_shape(&scene->shapell, SPHERE, &s, linenumber);
	else if (accept_identifier(&s, "pl"))
		ret = parser_shape(&scene->shapell, PLANE, &s, linenumber);
	else if (accept_identifier(&s, "cy"))
		ret = parser_shape(&scene->shapell, CYLINDER, &s, linenumber);
	else if (accept_identifier(&s, "hy"))
		ret = parser_shape(&scene->shapell, HYPERBOLOID, &s, linenumber);
	else
		return (unexpected(*s, linenumber), 0);
	return (ret && expect_endl(s, linenumber));
}
