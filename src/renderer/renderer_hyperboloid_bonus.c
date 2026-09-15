/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_hyperboloid_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 12:58:36 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/10 21:28:22 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer_intersection.h"
#include "math/floating_point.h"
#include "math/quadratic.h"

/* Local surface: x*x + y*y - k*z*z = radius*radius. */
static double	hp_product(t_vec3 u, t_vec3 v, const t_hyperboloid *hp)
{
	double	k;

	k = hp->diameter / hp->height;
	k *= k;
	return (vec3_dot(u, v) - (1.0 + k)
		* vec3_dot(u, hp->axis) * vec3_dot(v, hp->axis));
}

static void	save_side(double t, t_ray ray, const t_hyperboloid *hp,
		t_hit *closest)
{
	t_vec3	p;
	t_vec3	normal;
	double	z;
	double	k;

	if (!is_positive(t) || (closest->hit && t >= closest->t))
		return ;
	p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	z = vec3_dot(p, hp->axis);
	if (fabs(z) > hp->height / 2.0)
		return ;
	k = hp->diameter / hp->height;
	normal = vec3_subtract(p, vec3_scale(hp->axis, (1.0 + k * k) * z));
	*closest = make_hit(t, vec3_add(p, hp->pos), normal, hp->color);
}

static void	intersect_body(t_ray ray, const t_hyperboloid *hp,
		t_hit *closest)
{
	double	a;
	double	b;
	double	c;
	double	root[2];

	a = hp_product(ray.direction, ray.direction, hp);
	b = 2.0 * hp_product(ray.origin, ray.direction, hp);
	c = hp_product(ray.origin, ray.origin, hp)
		- (hp->diameter / 2.0) * (hp->diameter / 2.0);
	if (a == 0.0)
	{
		if (b != 0.0)
			save_side(-c / b, ray, hp, closest);
		return ;
	}
	if (!solve_quadratic(a, b, c, root))
		return ;
	save_side(root[0], ray, hp, closest);
	save_side(root[1], ray, hp, closest);
}

static void	intersect_cap(t_ray ray, const t_hyperboloid *hp,
		double sign, t_hit *closest)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	radial;

	denom = vec3_dot(ray.direction, hp->axis);
	if (denom == 0.0)
		return ;
	t = (sign * hp->height / 2.0 - vec3_dot(ray.origin, hp->axis)) / denom;
	if (!is_positive(t) || (closest->hit && t >= closest->t))
		return ;
	p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	radial = vec3_subtract(p, vec3_scale(hp->axis, sign * hp->height / 2.0));
	if (vec3_length_squared(radial) > hp->diameter * hp->diameter / 2.0)
		return ;
	*closest = make_hit(t, vec3_add(p, hp->pos),
			vec3_scale(hp->axis, sign), hp->color);
}

t_hit	intersect_hp(t_ray ray, const t_hyperboloid *hp)
{
	t_hit	closest;

	ray.origin = vec3_subtract(ray.origin, hp->pos);
	closest = no_hit();
	intersect_body(ray, hp, &closest);
	intersect_cap(ray, hp, -1.0, &closest);
	intersect_cap(ray, hp, 1.0, &closest);
	return (closest);
}
