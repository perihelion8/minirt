/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_cy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:09 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/12 13:58:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "cylinder_transforms.h"
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static double	square(double n)
{
	return (n * n);
}

static void	save_side_hit(double t, t_ray rel_ray,
		const t_cylinder *cy, t_hit *closest)
{
	t_vec3	rel_hit_point;
	t_vec3	hit_point;
	t_vec3	hit_surface;

	rel_hit_point.z = rel_ray.origin.z + t * rel_ray.direction.z;
	if (!is_positive(t) || fabs(rel_hit_point.z) > cy->height / 2.0)
		return ;
	rel_hit_point.x = rel_ray.origin.x + t * rel_ray.direction.x;
	rel_hit_point.y = rel_ray.origin.y + t * rel_ray.direction.y;
	hit_surface = vec3_add(vec3_scale(cy->right, rel_hit_point.x),
			vec3_scale(cy->up, rel_hit_point.y));
	hit_point = cy_pointtoabs(cy, rel_hit_point);
	if (!closest->hit || t < closest->t)
		*closest = make_hit(t, hit_point, hit_surface, cy->color);
}

static void	intersect_body(t_ray rel_ray, const t_cylinder *cy, t_hit *closest)
{
	double	root[2];
	double	radius;
	double	a;
	double	b;
	double	c;

	radius = cy->diameter / 2.0;
	a = square(rel_ray.direction.x) + square(rel_ray.direction.y);
	b = 2.0 * (rel_ray.origin.x * rel_ray.direction.x
			+ rel_ray.origin.y * rel_ray.direction.y);
	c = square(rel_ray.origin.x) + square(rel_ray.origin.y) - square(radius);
	if (!solve_quadratic(a, b, c, root))
		return ;
	if (!approximately_zero(root[0]))
		save_side_hit(root[0], rel_ray, cy, closest);
	if (!approximately_zero(root[1]))
		save_side_hit(root[1], rel_ray, cy, closest);
}

static void	intersect_cap(t_ray rel_ray, const t_cylinder *cy,
		double sign, t_hit *closest)
{
	t_vec3	rel_hit_point;
	t_vec3	hit_point;
	t_vec3	hit_surface;
	double	t;

	if (approximately_zero(rel_ray.direction.z))
		return ;
	t = (sign * cy->height / 2.0 - rel_ray.origin.z) / rel_ray.direction.z;
	if (!is_positive(t) || (closest->hit && t >= closest->t))
		return ;
	rel_hit_point.x = rel_ray.origin.x + t * rel_ray.direction.x;
	rel_hit_point.y = rel_ray.origin.y + t * rel_ray.direction.y;
	rel_hit_point.z = sign * cy->height / 2.0;
	if (square(rel_hit_point.x) + square(rel_hit_point.y)
		> square(cy->diameter / 2))
		return ;
	hit_point = cy_pointtoabs(cy, rel_hit_point);
	hit_surface = vec3_scale(cy->axis, sign);
	*closest = make_hit(t, hit_point, hit_surface, cy->color);
}

t_hit	intersect_cy(t_ray ray, const t_cylinder *cy)
{
	t_ray	rel_ray;
	t_hit	closest;

	rel_ray = cy_raytorel(ray, cy);
	closest = no_hit();
	closest.t = DBL_MAX;
	intersect_body(rel_ray, cy, &closest);
	intersect_cap(rel_ray, cy, -1.0, &closest);
	intersect_cap(rel_ray, cy, 1.0, &closest);
	return (closest);
}
