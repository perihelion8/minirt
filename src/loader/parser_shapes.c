/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 00:04:34 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/14 14:57:12 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	parser_sphere(t_sphere *sphere, char **s, int linenumber)
{
	if (!sphere)
		return (0);
	if (!parser_vec3(&sphere->pos, s, linenumber))
		return (0);
	if (!parser_dimension(&sphere->diameter, s, linenumber))
		return (0);
	if (!parser_color(&sphere->color, s, linenumber))
		return (0);
	return (1);
}

int	parser_plane(t_plane *plane, char **s, int linenumber)
{
	if (!plane)
		return (0);
	if (!parser_vec3(&plane->pos, s, linenumber))
		return (0);
	if (!parser_vec3_normal(&plane->normal, s, linenumber))
		return (0);
	if (!parser_color(&plane->color, s, linenumber))
		return (0);
	return (1);
}

int	parser_cylinder(t_cylinder *cylinder, char **s, int linenumber)
{
	if (!cylinder)
		return (0);
	if (!parser_vec3(&cylinder->pos, s, linenumber))
		return (0);
	if (!parser_vec3_normal(&cylinder->axis, s, linenumber))
		return (0);
	if (!parser_dimension(&cylinder->diameter, s, linenumber))
		return (0);
	if (!parser_dimension(&cylinder->height, s, linenumber))
		return (0);
	if (!parser_color(&cylinder->color, s, linenumber))
		return (0);
	vec3_basis(&cylinder->axis, &cylinder->right, &cylinder->up);
	return (1);
}
