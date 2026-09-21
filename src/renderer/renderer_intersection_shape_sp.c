/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_shape_sp.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:04 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 04:56:40 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static double	calc_t(t_vec3 *rel_ray_origin, t_vec3 *ray_direction,
					double radius)
{
	double	a;
	double	b;
	double	c;
	double	root[2];

	a = vec3_length_squared(*ray_direction);
	b = 2.0 * vec3_dot(*rel_ray_origin, *ray_direction);
	c = vec3_length_squared(*rel_ray_origin) - (radius * radius);
	if (!solve_quadratic(a, b, c, root))
		return (-1.0);
	if (is_positive(root[0]))
		return (root[0]);
	if (is_positive(root[1]))
		return (root[1]);
	return (-1.0);
}

double	intersect_sp(t_ray *ray, t_sphere *sp)
{
	double	t;
	t_vec3	rel_ray_origin;

	rel_ray_origin = vec3_subtract(ray->origin, sp->pos);
	t = calc_t(&rel_ray_origin, &ray->direction, sp->diameter / 2.0);
	if (t != -1.0)
		return (t);
	return (-1.0);
}

void	hit_sp(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = vec3_normal(vec3_subtract(hit->point, sp->pos));
	hit->color = sp->color;
}
