/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:04:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 21:22:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	parser_sphere(t_sphere **spherell, char **line, int linenumber)
{
	t_sphere	*sphere;

	sphere = spherell_append(spherell);
	if (!parser_vec3(&sphere->pos, line, linenumber))
		return (0);
	if (!parser_double(&sphere->diameter, line, linenumber))
		return(0);
	if (!parser_color(&sphere->color, line, linenumber))
		return (0);
	return (1);
}

int	parser_plane(t_plane **planell, char **line, int linenumber)
{
	t_plane	*plane;

	plane = planell_append(planell);
	if (!parser_vec3(&plane->pos, line, linenumber))
		return (0);
	if (!parser_vec3(&plane->normal, line, linenumber))
		return (0);
	if (!parser_color(&plane->color, line, linenumber))
		return (0);
	return (1);
}

int	parser_cylinder(t_cylinder **cylinderll, char **line, int linenumber)
{
	t_cylinder	*cylinder;

	cylinder = cylinderll_append(cylinderll);
	if (!parser_vec3(&cylinder->pos, line, linenumber))
		return (0);
	if (!parser_vec3(&cylinder->axis, line, linenumber))
		return (0);
	if (!parser_double(&cylinder->diameter, line, linenumber))
		return (0);
	if (!parser_double(&cylinder->height, line, linenumber))
		return (0);
	if (!parser_color(&cylinder->color, line, linenumber))
		return (0);
	vec3_basis(&cylinder->axis, &cylinder->right, &cylinder->up);
	return (1);
}
