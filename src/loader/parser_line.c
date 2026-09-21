/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 21:53:53 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/19 23:52:07 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "scene.h"
#include "parser.h"
#include "loader_rt.h"

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

static t_shape	*shapell_append(t_shapell **shapell, t_shape_type type)
{
	t_nodell	*head;
	t_shapell	*node;

	head = (t_nodell *)(*shapell);
	node = (t_shapell *)appendll(&head, sizeof(*node));
	if (!node)
		return (NULL);
	*shapell = (t_shapell *)head;
	node->shape.type = type;
	return (&node->shape);
}

static int	parser_shape(t_shapell **shapell, t_shape_type type, char **s,
				int linenumber)
{
	t_shape		*shape;

	shape = shapell_append(shapell, type);
	if (!shape)
		return (0);
	if (type == PLANE)
		return (parser_plane(&shape->plane, s, linenumber));
	if (type == SPHERE)
		return (parser_sphere(&shape->sphere, s, linenumber));
	if (type == CYLINDER)
		return (parser_cylinder(&shape->cylinder, s, linenumber));
	if (type == HYPERB)
		return (parser_hyperboloid(&shape->hyperboloid, s, linenumber));
	return (0);
}

static int	parser_spotlightll(t_spotlightll **spotlightll, char **s,
				int linenumber)
{
	t_nodell		*head;
	t_spotlightll	*node;

	head = (t_nodell *)(*spotlightll);
	node = (t_spotlightll *)appendll(&head, sizeof(*node));
	if (!node)
		return (0);
	*spotlightll = (t_spotlightll *)head;
	return (parser_spotlight(&node->spotlight, s, linenumber));
}

int	parser_line(t_scene *scene, t_loader_rt *loader, char *s)
{
	int	ret;

	if (all_space(&s))
		return (1);
	else if (accept_identifier(&s, "A", loader->linenumber))
		ret = parser_ambient(&scene->ambient, &s, loader->linenumber);
	else if (accept_identifier(&s, "C", loader->linenumber))
		ret = parser_camera(&scene->camera, &s, loader->linenumber);
	else if (accept_identifier(&s, "L", loader->linenumber))
		ret = parser_light(&scene->light, &s, loader->linenumber);
	else if (accept_identifier(&s, "sl", loader->linenumber))
		ret = parser_spotlightll(&loader->spotlightll, &s, loader->linenumber);
	else if (accept_identifier(&s, "sp", loader->linenumber))
		ret = parser_shape(&loader->shapell, SPHERE, &s, loader->linenumber);
	else if (accept_identifier(&s, "pl", loader->linenumber))
		ret = parser_shape(&loader->shapell, PLANE, &s, loader->linenumber);
	else if (accept_identifier(&s, "cy", loader->linenumber))
		ret = parser_shape(&loader->shapell, CYLINDER, &s, loader->linenumber);
	else if (accept_identifier(&s, "hb", loader->linenumber))
		ret = parser_shape(&loader->shapell, HYPERB, &s, loader->linenumber);
	else
		return (unexpected(*s, loader->linenumber), 0);
	if (!ret)
		return (0);
	return (expect_endl(s, loader->linenumber));
}
