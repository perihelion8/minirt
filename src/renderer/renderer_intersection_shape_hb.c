/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_shape_hb.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 20:16:52 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/20 05:03:17 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"
#include <float.h>
#include <math.h>
#include "renderer_utils.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static int	is_valid_t(double root, t_ray *ray, double height)
{
	if (isfinite(root) && is_positive(root)
		&& fabs(ray->origin.z + root * ray->direction.z) <= height / 2.0)
		return (1);
	return (0);
}

static int	solve_roots(double a, double b, double c, double *root)
{
	if (a != 0.0)
		return (solve_quadratic(a, b, c, root));
	if (b == 0.0)
		return (0);
	root[0] = -c / b;
	root[1] = root[0];
	return (1);
}

static double	calc_t(t_ray *rel_ray, t_hyperboloid *hb)
{
	double	a;
	double	b;
	double	c;
	double	root[2];

	a = rel_ray->direction.x * rel_ray->direction.x
		+ rel_ray->direction.y * rel_ray->direction.y
		- rel_ray->direction.z * rel_ray->direction.z;
	b = 2.0 * (rel_ray->origin.x * rel_ray->direction.x
			+ rel_ray->origin.y * rel_ray->direction.y
			- rel_ray->origin.z * rel_ray->direction.z);
	c = rel_ray->origin.x * rel_ray->origin.x
		+ rel_ray->origin.y * rel_ray->origin.y
		- rel_ray->origin.z * rel_ray->origin.z
		- hb->diameter * hb->diameter / 4.0;
	if (!solve_roots(a, b, c, root))
		return (-1.0);
	if (is_valid_t(root[0], rel_ray, hb->height))
		return (root[0]);
	if (is_valid_t(root[1], rel_ray, hb->height))
		return (root[1]);
	return (-1.0);
}

double	intersect_hb(t_ray *ray, t_hyperboloid *hb)
{
	t_ray	rel_ray;

	rel_ray = hb_ray_to_rel(ray, hb);
	return (calc_t(&rel_ray, hb));
}

void	hit_hb(t_ray *ray, t_hyperboloid *hb, t_hit *hit)
{
	t_vec3	rel_hit_point;

	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	rel_hit_point = vec3_subtract(hit->point, hb->pos);
	hit->normal = vec3_scale(hb->axis, 2.0 * vec3_dot(rel_hit_point, hb->axis));
	hit->normal = vec3_subtract(rel_hit_point, hit->normal);
	hit->normal = vec3_normal(hit->normal);
	hit->color = hb->color;
}
