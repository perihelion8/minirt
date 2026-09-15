/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_intersection_pl.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:51:44 by abazzoun          #+#    #+#             */
/*   Updated: 2026/09/11 17:47:18 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_intersection.h"
#include "math/floating_point.h"

t_hit	intersect_pl(t_ray ray, const t_plane *pl)
{
	t_vec3	rel_ray;
	t_vec3	hit_point;
	double	t;
	double	ray_dot_normal;

	ray_dot_normal = vec3_dot(ray.direction, pl->normal);
	if (approximately_zero(ray_dot_normal))
		return (no_hit());
	rel_ray = vec3_subtract(pl->pos, ray.origin);
	t = vec3_dot(rel_ray, pl->normal) / ray_dot_normal;
	if (!is_positive(t))
		return (no_hit());
	hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	return (make_hit(t, hit_point, pl->normal, pl->color));
}
