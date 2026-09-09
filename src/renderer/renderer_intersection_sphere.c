/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_sphere.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:52:04 by abazzoun          #+#    #+#             */
/*   Updated: 2026/08/19 04:34:18 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

t_hit	intersect_sphere(t_ray ray, const t_sphere *sp)
{
	t_vec3	relative_origin;
	t_vec3	normal;
	t_vec3	point;
	double	t;

	relative_origin = vec3_subtract(ray.origin, sp->pos);
	t = quadratic_minimum_positive_root(
			vec3_length_squared(ray.direction),
			2.0 * vec3_dot(relative_origin, ray.direction),
			vec3_length_squared(relative_origin)
			- (sp->diameter * sp->diameter) / 4);
	if (!is_positive(t))
		return (no_hit());
	point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	normal = vec3_subtract(point, sp->pos);
	return (make_hit(t, point, normal, sp->color));
}
