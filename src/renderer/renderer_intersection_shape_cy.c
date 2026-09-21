/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_shape_cy.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:09 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 12:38:54 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "renderer_utils.h"
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static int	is_valid_t(double root, t_ray *ray, double height)
{
	if (is_positive(root)
		&& fabs(ray->origin.z + root * ray->direction.z) <= height / 2.0)
		return (1);
	return (0);
}

static double	calc_t(t_ray *rel_ray, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	double	root[2];

	a = rel_ray->direction.x * rel_ray->direction.x
		+ rel_ray->direction.y * rel_ray->direction.y;
	b = 2.0 * (rel_ray->origin.x * rel_ray->direction.x
			+ rel_ray->origin.y * rel_ray->direction.y);
	c = rel_ray->origin.x * rel_ray->origin.x
		+ rel_ray->origin.y * rel_ray->origin.y
		- cy->diameter * cy->diameter / 4.0;
	if (!solve_quadratic(a, b, c, root))
		return (-1.0);
	if (is_valid_t(root[0], rel_ray, cy->height))
		return (root[0]);
	if (is_valid_t(root[1], rel_ray, cy->height))
		return (root[1]);
	return (-1.0);
}

double	intersect_cy(t_ray *ray, t_cylinder *cy)
{
	t_ray	rel_ray;

	rel_ray = cy_ray_to_rel(ray, cy);
	return (calc_t(&rel_ray, cy));
}

void	hit_cy(t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	rel_hit_point;

	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	rel_hit_point = vec3_subtract(hit->point, cy->pos);
	hit->normal = vec3_normal(vec3_subtract(rel_hit_point,
				vec3_scale(cy->axis, vec3_dot(rel_hit_point, cy->axis))));
	hit->color = cy->color;
}
