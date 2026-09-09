/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_cylinder.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:09 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/09 17:45:30 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

static double	square(double n)
{
	return (n * n);
}

static void	save_side_hit(double t, t_component_of_ray component,
		const t_cylinder *cy, t_hit *closest)
{
	t_vec3	point;
	t_vec3	normal;
	double	x;
	double	y;
	double	z;

	z = component.origin_forward + t * component.direction_forward;
	if (!is_positive(t) || fabs(z) > cy->height / 2.0)
		return ;
	x = component.origin_right + t * component.direction_right;
	y = component.origin_up + t * component.direction_up;
	normal = vec3_add(vec3_scale(cy->right, x), vec3_scale(cy->up, y));
	point = to_world_point(cy, x, y, z);
	if (!closest->hit || t < closest->t)
		*closest = make_hit(t, point, normal, cy->color);
}

static void	intersect_body(t_component_of_ray component,
		const t_cylinder *cy, t_hit *closest)
{
	double	root1;
	double	root2;
	double	radius;

	radius = cy->diameter / 2.0;
	if (!solve_quadratic(
			square(component.direction_right) + square(component.direction_up),
			2.0 * (component.origin_right * component.direction_right
				+ component.origin_up * component.direction_up),
			square(component.origin_right) + square(component.origin_up)
			- square(radius),
			&root1,
			&root2
		))
		return ;
	if (!approximately_zero(root1))
		save_side_hit(root1, component, cy, closest);
	if (!approximately_zero(root2))
		save_side_hit(root2, component, cy, closest);
}

static void	intersect_cap(t_component_of_ray component, const t_cylinder *cy,
		double sign, t_hit *closest)
{
	t_vec3	point;
	t_vec3	normal;
	double	t;
	double	x;
	double	y;
	double	radius;

	radius = cy->diameter / 2.0;
	if (approximately_zero(component.direction_forward))
		return ;
	t = (sign * cy->height / 2.0 - component.origin_forward)
		/ component.direction_forward;
	if (!is_positive(t) || (closest->hit && t >= closest->t))
		return ;
	x = component.origin_right + t * component.direction_right;
	y = component.origin_up + t * component.direction_up;
	if (x * x + y * y > radius * radius)
		return ;
	point = to_world_point(cy, x, y, sign * cy->height / 2.0);
	normal = vec3_scale(cy->axis, sign);
	*closest = make_hit(t, point, normal, cy->color);
}

t_hit	intersect_cylinder(t_ray ray, const t_cylinder *cy)
{
	t_component_of_ray	component_of_ray;
	t_hit				closest;

	component_of_ray = to_cylinder_space(ray, cy);
	closest = no_hit();
	closest.t = DBL_MAX;
	intersect_body(component_of_ray, cy, &closest);
	intersect_cap(component_of_ray, cy, -1.0, &closest);
	intersect_cap(component_of_ray, cy, 1.0, &closest);
	return (closest);
}
