/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_sp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:04 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 13:53:47 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static double	calc_t(t_vec3 rel_ray_o, t_vec3 ray_direction, double radius)
{
	double	a;
	double	b;
	double	c;
	double	root[2];

	a = vec3_length_squared(ray_direction);
	b = 2.0 * vec3_dot(rel_ray_o, ray_direction);
	c = vec3_length_squared(rel_ray_o) - (radius * radius);
	if (!solve_quadratic(a, b, c, root))
		return (-1.0);
	if (is_positive(root[0]) &&
		(!is_positive(root[1]) || root[0] < root[1]))
			return (root[0]);
	if (is_positive(root[1]))
		return (root[1]);
	return (-1.0);
}

t_hit	intersect_sp(t_ray ray, const t_sphere *sp)
{
	t_vec3	rel_ray_o;
	t_vec3	hit_surface;
	t_vec3	hit_point;
	double	t;

	rel_ray_o = vec3_subtract(ray.origin, sp->pos);
	t = calc_t(rel_ray_o, ray.direction, sp->diameter / 2.0);
	if (!is_positive(t))
		return (no_hit());
	hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	hit_surface = vec3_normal(vec3_subtract(hit_point, sp->pos));
	return (make_hit(t, hit_point, hit_surface, sp->color));
}
